/* file: outlierdetection_multivariate_dense_default_impl.i */
/*******************************************************************************
* Copyright 2014-2017 Intel Corporation
* All Rights Reserved.
*
* If this  software was obtained  under the  Intel Simplified  Software License,
* the following terms apply:
*
* The source code,  information  and material  ("Material") contained  herein is
* owned by Intel Corporation or its  suppliers or licensors,  and  title to such
* Material remains with Intel  Corporation or its  suppliers or  licensors.  The
* Material  contains  proprietary  information  of  Intel or  its suppliers  and
* licensors.  The Material is protected by  worldwide copyright  laws and treaty
* provisions.  No part  of  the  Material   may  be  used,  copied,  reproduced,
* modified, published,  uploaded, posted, transmitted,  distributed or disclosed
* in any way without Intel's prior express written permission.  No license under
* any patent,  copyright or other  intellectual property rights  in the Material
* is granted to  or  conferred  upon  you,  either   expressly,  by implication,
* inducement,  estoppel  or  otherwise.  Any  license   under such  intellectual
* property rights must be express and approved by Intel in writing.
*
* Unless otherwise agreed by Intel in writing,  you may not remove or alter this
* notice or  any  other  notice   embedded  in  Materials  by  Intel  or Intel's
* suppliers or licensors in any way.
*
*
* If this  software  was obtained  under the  Apache License,  Version  2.0 (the
* "License"), the following terms apply:
*
* You may  not use this  file except  in compliance  with  the License.  You may
* obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
*
*
* Unless  required  by   applicable  law  or  agreed  to  in  writing,  software
* distributed under the License  is distributed  on an  "AS IS"  BASIS,  WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
* See the   License  for the   specific  language   governing   permissions  and
* limitations under the License.
*******************************************************************************/

/*
//++
//  Implementation of multivariate outlier detection
//--
*/

#ifndef __MULTIVARIATE_OUTLIER_DETECTION_DENSE_DEFAULT_IMPL_I__
#define __MULTIVARIATE_OUTLIER_DETECTION_DENSE_DEFAULT_IMPL_I__

#include "numeric_table.h"
#include "outlier_detection_multivariate_types.h"
#include "service_numeric_table.h"
#include "service_math.h"
#include "service_blas.h"
#include "service_lapack.h"
#include "outlierdetection_multivariate_kernel.h"

namespace daal
{
namespace algorithms
{
namespace multivariate_outlier_detection
{
namespace internal
{

using namespace daal::internal;
using namespace daal::services;
using namespace daal::data_management;

template <typename algorithmFPType, Method method, CpuType cpu>
inline void OutlierDetectionKernel<algorithmFPType, method, cpu>::
mahalanobisDistance(const size_t nFeatures,
                    const size_t nVectors,
                    const algorithmFPType *data,
                    const algorithmFPType *location,
                    const algorithmFPType *invScatter,
                    algorithmFPType *distance,
                    algorithmFPType *buffer)
{
    algorithmFPType *dataCen            = buffer;
    algorithmFPType *dataCenInvScatter  = buffer + nFeatures * nVectors;

    DAAL_INT dim = (DAAL_INT)nFeatures;
    DAAL_INT n   = (DAAL_INT)nVectors;
    char side = 'L';
    char uplo = 'U';
    algorithmFPType one  = (algorithmFPType)1.0;
    algorithmFPType zero = (algorithmFPType)0.0;
    DAAL_INT info;

    const algorithmFPType *dataPtr    = data;
    algorithmFPType *dataCenPtr = dataCen;
    for (size_t i = 0; i < nVectors; i++, dataPtr += nFeatures, dataCenPtr += nFeatures)
    {
        PRAGMA_IVDEP
        PRAGMA_VECTOR_ALWAYS
        for (size_t j = 0; j < nFeatures; j++)
        {
            dataCenPtr[j] = dataPtr[j] - location[j];
        }
    }

    Blas<algorithmFPType, cpu>::xsymm(&side, &uplo, &dim, &n, &one, invScatter, &dim, dataCen, &dim, &zero,
                                      dataCenInvScatter, &dim);

    dataCenPtr = dataCen;
    algorithmFPType *dataCenInvScatterPtr = dataCenInvScatter;
    for (size_t i = 0; i < nVectors; i++, dataCenPtr += nFeatures, dataCenInvScatterPtr += nFeatures)
    {
        distance[i] = zero;
        PRAGMA_IVDEP
        PRAGMA_VECTOR_ALWAYS
        for (size_t j = 0; j < nFeatures; j++)
        {
            distance[i] += dataCenPtr[j] * dataCenInvScatterPtr[j];
        }
    }
}

template <typename algorithmFPType, Method method, CpuType cpu>
inline Status OutlierDetectionKernel<algorithmFPType, method, cpu>::
computeInternal(const size_t nFeatures,
                const size_t nVectors,
                NumericTable &dataTable,
                NumericTable &resultTable,
                const algorithmFPType *locationArray,
                const algorithmFPType *scatterArray,
                const algorithmFPType thresholdValue,
                algorithmFPType *buffer)
{
    ReadRows<algorithmFPType, cpu> dataBlock(dataTable);
    WriteOnlyRows<algorithmFPType, cpu> resultBlock(resultTable);

    algorithmFPType one  = (algorithmFPType)1.0;
    algorithmFPType zero = (algorithmFPType)0.0;
    algorithmFPType *invScatter = buffer;

    for (size_t i = 0; i < nFeatures * nFeatures; i++)
    {
        invScatter[i] = scatterArray[i];
    }

    /* Calculate inverse of data variance-covariance matrix */
    DAAL_INT dim = (DAAL_INT)nFeatures;
    char uplo = 'U';
    DAAL_INT info;
    Lapack<algorithmFPType, cpu>::xpotrf(&uplo, &dim, invScatter, &dim, &info);
    DAAL_CHECK(info == 0, ErrorOutlierDetectionInternal);

    Lapack<algorithmFPType, cpu>::xpotri(&uplo, &dim, invScatter, &dim, &info);
    DAAL_CHECK(info == 0, ErrorOutlierDetectionInternal);

    size_t nBlocks = nVectors / blockSize;
    if (nBlocks * blockSize < nVectors)
    {
        nBlocks++;
    }

    /* Process input data table in blocks */
    for (size_t iBlock = 0; iBlock < nBlocks; iBlock++)
    {
        size_t startRow = iBlock * blockSize;
        size_t nRowsInBlock = blockSize;
        if (startRow + nRowsInBlock > nVectors)
        {
            nRowsInBlock = nVectors - startRow;
        }
        DAAL_INT n = (DAAL_INT)nRowsInBlock;

        const algorithmFPType *data = dataBlock.next(startRow, nRowsInBlock);
        DAAL_CHECK_BLOCK_STATUS(dataBlock)

        algorithmFPType *weight = resultBlock.next(startRow, nRowsInBlock);
        DAAL_CHECK_BLOCK_STATUS(resultBlock)

        /* Calculate mahalanobis distances for a block of observations */
        mahalanobisDistance(nFeatures, nRowsInBlock, data, locationArray, invScatter, weight,
                            buffer + nFeatures * nFeatures);

        for (size_t i = 0; i < nRowsInBlock; i++)
        {
            if (Math<algorithmFPType, cpu>::sSqrt(weight[i]) > thresholdValue)
            {
                weight[i] = zero;
            }
            else
            {
                weight[i] = one;
            }
        }
    }
    return Status();
}

template <typename algorithmFPType, Method method, CpuType cpu>
Status OutlierDetectionKernel<algorithmFPType, method, cpu>::
compute(NumericTable &dataTable,
        NumericTable *locationTable,
        NumericTable *scatterTable,
        NumericTable *thresholdTable,
        NumericTable &resultTable)
{
    size_t nFeatures = dataTable.getNumberOfColumns();
    size_t nVectors  = dataTable.getNumberOfRows();

    TArray<algorithmFPType, cpu> locationPtr, scatterPtr, thresholdPtr;
    ReadRows<algorithmFPType, cpu> locationBlock(locationTable), scatterBlock(scatterTable), thresholdBlock(thresholdTable);

    algorithmFPType *locationArray =  (locationTable) ?   const_cast<algorithmFPType *>(locationBlock.next(0, 1)) :        locationPtr.reset(nFeatures);
    algorithmFPType *scatterArray =   (scatterTable) ?    const_cast<algorithmFPType *>(scatterBlock.next(0, nFeatures)) : scatterPtr.reset(nFeatures * nFeatures);
    algorithmFPType *thresholdArray = (thresholdTable) ?  const_cast<algorithmFPType *>(thresholdBlock.next(0, 1)) :       thresholdPtr.reset(1);

    DAAL_CHECK(locationArray && scatterArray && thresholdArray, ErrorMemoryAllocationFailed)

    if(!locationTable || !scatterTable || !thresholdTable)
    {
        defaultInitialization(locationArray, scatterArray, thresholdArray, nFeatures);
    }

    /* Allocate memory for storing intermediate results */
    size_t bufferSize = nFeatures * nFeatures + 2 * nFeatures * nVectors;
    TArray<algorithmFPType, cpu> bufferPtr(bufferSize);
    DAAL_CHECK(bufferPtr.get(), ErrorMemoryAllocationFailed)

        /* Calculate results */
    return computeInternal(nFeatures, nVectors, dataTable, resultTable,
                           locationArray,
                           scatterArray,
                           thresholdArray[0],
                           bufferPtr.get());
}

template <typename algorithmFPType, Method method, CpuType cpu>
void OutlierDetectionKernel<algorithmFPType, method, cpu>::defaultInitialization(
    algorithmFPType *locationArray,
    algorithmFPType *scatterArray,
    algorithmFPType *thresholdArray,
    const size_t nFeatures)
{
    for(size_t i = 0; i < nFeatures; i++)
    {
        locationArray[i]  = 0.0;
        for(size_t j = 0; j < nFeatures; j++)
        {
            scatterArray[i * nFeatures + j] = 0.0;
        }
        scatterArray[i * nFeatures + i]   = 1.0;
    }
    thresholdArray[0] = 3.0;
}

} // namespace internal

} // namespace multivariate_outlier_detection

} // namespace algorithms

} // namespace daal

#endif
