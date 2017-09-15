/* file: implicit_als_partial_model_fpt.cpp */
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
//  Implementation of the class defining the implicit als model
//--
*/

#include "implicit_als_model.h"

namespace daal
{
namespace algorithms
{
namespace implicit_als
{

using namespace daal::data_management;

template<typename modelFPType>
DAAL_EXPORT services::Status PartialModel::initialize(const Parameter &parameter, size_t size)
{
    services::Status s;

    const size_t nFactors = parameter.nFactors;
    _factors = HomogenNumericTable<modelFPType>::create(nFactors, size, NumericTableIface::doAllocate, &s);
    DAAL_CHECK_STATUS_VAR(s);

    _indices = HomogenNumericTable<int>::create(1, size, NumericTableIface::doAllocate, &s);
    DAAL_CHECK_STATUS_VAR(s);

    int *indicesData = HomogenNumericTable<int>::cast(_indices)->getArray();
    const int iSize = (int)size;
    for (int i = 0; i < iSize; i++)
    {
        indicesData[i] = i;
    }

    return s;
}

template<typename modelFPType>
DAAL_EXPORT services::Status PartialModel::initialize(const Parameter &parameter, size_t offset,
                                                      const NumericTablePtr &indices)
{
    DAAL_CHECK(indices, services::ErrorNullInputNumericTable);

    services::Status s;
    const size_t nFactors = parameter.nFactors;
    const size_t size = indices->getNumberOfRows();

    _factors = HomogenNumericTable<modelFPType>::create(nFactors, size, NumericTableIface::doAllocate, &s);
    DAAL_CHECK_STATUS_VAR(s);

    _indices = HomogenNumericTable<int>::create(1, size, NumericTableIface::doAllocate, &s);
    DAAL_CHECK_STATUS_VAR(s);

    BlockDescriptor<int> block;
    indices->getBlockOfRows(0, size, readOnly, block);
    const int *srcIndicesData = block.getBlockPtr();
    DAAL_CHECK_MALLOC(srcIndicesData);

    int *dstIndicesData = HomogenNumericTable<int>::cast(_indices)->getArray();
    const int iOffset = (int)offset;
    for (size_t i = 0; i < size; i++)
    {
        dstIndicesData[i] = srcIndicesData[i] + iOffset;
    }

    indices->releaseBlockOfRows(block);
    return s;
}

/**
 * Constructs a partial implicit ALS model of a specified size
 * \param[in] parameter Implicit ALS parameters
 * \param[in] size      Model size
 * \param[in] dummy     Dummy variable for the templated constructor
 * \DAAL_DEPRECATED_USE{ Model::create }
 */
template<typename modelFPType>
DAAL_EXPORT PartialModel::PartialModel(const Parameter &parameter, size_t size, modelFPType dummy)
{
    initialize<modelFPType>(parameter, size);
}

/**
 * Constructs a partial implicit ALS model from the indices of factors
 * \param[in] parameter Implicit ALS parameters
 * \param[in] offset    Index of the first factor in the partial model
 * \param[in] indices   Pointer to the numeric table with the indices of factors
 * \param[in] dummy     Dummy variable for the templated constructor
 * \DAAL_DEPRECATED_USE{ Model::create }
 */
template<typename modelFPType>
DAAL_EXPORT PartialModel::PartialModel(const Parameter &parameter, size_t offset,
                                       data_management::NumericTablePtr indices, modelFPType dummy)
{
    initialize<modelFPType>(parameter, offset, indices);
}

template<typename modelFPType>
DAAL_EXPORT PartialModel::PartialModel(const Parameter &parameter, size_t size, modelFPType dummy, services::Status &st)
{
    st |= initialize<modelFPType>(parameter, size);
}

template<typename modelFPType>
DAAL_EXPORT PartialModel::PartialModel(const Parameter &parameter, size_t offset,
                                       const data_management::NumericTablePtr &indices,
                                       modelFPType dummy, services::Status &st)
{
    st |= initialize<modelFPType>(parameter, offset, indices);
}

/**
 * Constructs a partial implicit ALS model from the indices of factors
 * \param[in] parameter Implicit ALS parameters
 * \param[in] offset    Index of the first factor in the partial model
 * \param[in] indices   Pointer to the numeric table with the indices of factors
 * \param[out] stat     Status of the model construction
 * \return Partial implicit ALS model with the specified indices and factors
 */
template<typename modelFPType>
DAAL_EXPORT PartialModelPtr PartialModel::create(const Parameter &parameter, size_t offset,
                                                 const data_management::NumericTablePtr &indices,
                                                 services::Status *stat)
{
    DAAL_DEFAULT_CREATE_IMPL_EX(PartialModel, parameter, offset, indices, (modelFPType)0);
}

/**
 * Constructs a partial implicit ALS model of a specified size
 * \param[in] parameter Implicit ALS parameters
 * \param[in] size      Model size
 * \param[out] stat     Status of the model construction
 * \return Partial implicit ALS model of a specified size
 */
template<typename modelFPType>
DAAL_EXPORT PartialModelPtr PartialModel::create(const Parameter &parameter, size_t size,
                                                 services::Status *stat)
{
    DAAL_DEFAULT_CREATE_IMPL_EX(PartialModel, parameter, size, (modelFPType)0);
}

template DAAL_EXPORT PartialModel::PartialModel(const Parameter&, size_t, DAAL_FPTYPE);
template DAAL_EXPORT PartialModel::PartialModel(const Parameter&, size_t,
                                                NumericTablePtr, DAAL_FPTYPE);
template DAAL_EXPORT PartialModel::PartialModel(const Parameter&, size_t,
                                                DAAL_FPTYPE, services::Status&);
template DAAL_EXPORT PartialModel::PartialModel(const Parameter&, size_t,
                                                const NumericTablePtr&,
                                                DAAL_FPTYPE, services::Status&);

template DAAL_EXPORT PartialModelPtr PartialModel::create<DAAL_FPTYPE>(const Parameter&, size_t,
                                                                       const NumericTablePtr&,
                                                                       services::Status*);
template DAAL_EXPORT PartialModelPtr PartialModel::create<DAAL_FPTYPE>(const Parameter&, size_t,
                                                                       services::Status*);

template DAAL_EXPORT services::Status PartialModel::initialize<DAAL_FPTYPE>(const Parameter &parameter, size_t size);
template DAAL_EXPORT services::Status PartialModel::initialize<DAAL_FPTYPE>(const Parameter &parameter, size_t offset,
                                                                            const NumericTablePtr &indices);

}// namespace implicit_als
}// namespace algorithms
}// namespace daal
