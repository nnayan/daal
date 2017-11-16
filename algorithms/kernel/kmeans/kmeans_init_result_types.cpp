/* file: kmeans_init_result_types.cpp */
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
//  Implementation of kmeans classes.
//--
*/

#include "algorithms/kmeans/kmeans_init_types.h"
#include "daal_defines.h"
#include "serialization_utils.h"
#include "daal_strings.h"

using namespace daal::data_management;
using namespace daal::services;

namespace daal
{
namespace algorithms
{
namespace kmeans
{
namespace init
{
namespace interface1
{

__DAAL_REGISTER_SERIALIZATION_CLASS(Result, SERIALIZATION_KMEANS_INIT_RESULT_ID);

Result::Result() : daal::algorithms::Result(lastResultId + 1) {}

/**
 * Returns the result of computing initial clusters for the K-Means algorithm
 * \param[in] id   Identifier of the result
 * \return         Result that corresponds to the given identifier
 */
NumericTablePtr Result::get(ResultId id) const
{
    return staticPointerCast<NumericTable, SerializationIface>(Argument::get(id));
}

/**
 * Sets the result of computing initial clusters for the K-Means algorithm
 * \param[in] id    Identifier of the result
 * \param[in] ptr   Pointer to the object
 */
void Result::set(ResultId id, const NumericTablePtr &ptr)
{
    Argument::set(id, ptr);
}

/**
* Checks the result of computing initial clusters for the K-Means algorithm
* \param[in] input   %Input object for the algorithm
* \param[in] par     %Parameter of the algorithm
* \param[in] method  Computation method of the algorithm
*/
services::Status Result::check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *par, int method) const
{
    const DistributedStep2MasterInput* masterInput = dynamic_cast<const DistributedStep2MasterInput*>(input);
    size_t nFeatures = 0;
    if(masterInput)
    {
        data_management::DataCollection* coll = masterInput->get(partialResults).get();
        for(size_t i = 0; i < coll->size(); ++i)
        {
            data_management::NumericTable* partClusters = static_cast<PartialResult *>((*coll)[i].get())->get(partialClusters).get();
            if(partClusters)
            {
                nFeatures = partClusters->getNumberOfColumns();
                break;
            }
        }
    }
    else
        nFeatures = (static_cast<const Input *>(input))->get(data)->getNumberOfColumns();

    const Parameter *kmPar = static_cast<const Parameter *>(par);
    const int unexpectedLayouts = (int)packed_mask;
    return checkNumericTable(get(centroids).get(), centroidsStr(), unexpectedLayouts, 0, nFeatures, kmPar->nClusters);
}

/**
* Checks the result of computing initial clusters for the K-Means algorithm
* \param[in] pres    Partial results of the algorithm
* \param[in] par     %Parameter of the algorithm
* \param[in] method  Computation method of the algorithm
*/
services::Status Result::check(const daal::algorithms::PartialResult *pres, const daal::algorithms::Parameter *par, int method) const
{
    size_t inputFeatures = const_cast<PartialResult *>(static_cast<const PartialResult *>(pres))->get(
                            partialClusters)->getNumberOfColumns();
    const Parameter *kmPar = static_cast<const Parameter *>(par);

    int unexpectedLayouts = (int)packed_mask;
    return checkNumericTable(get(centroids).get(), centroidsStr(), unexpectedLayouts, 0, inputFeatures, kmPar->nClusters);
}

} // namespace interface1
} // namespace init
} // namespace kmeans
} // namespace algorithm
} // namespace daal
