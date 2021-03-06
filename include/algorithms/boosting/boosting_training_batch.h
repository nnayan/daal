/* file: boosting_training_batch.h */
/*******************************************************************************
* Copyright 2014-2018 Intel Corporation
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
//  Implementation of base classes defining interface for training models
//  of the Boosting algorithms in batch mode.
//--
*/

#ifndef __BOOSTING_TRAINING_BATCH_H__
#define __BOOSTING_TRAINING_BATCH_H__

#include "algorithms/algorithm.h"
#include "algorithms/classifier/classifier_training_batch.h"
#include "algorithms/boosting/boosting_model.h"

namespace daal
{
namespace algorithms
{
namespace boosting
{
/**
 * \brief Contains classes for training %boosting models.
 */
namespace training
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{
/**
 * @defgroup boosting_training Training
 * \copydoc daal::algorithms::boosting::training
 * @ingroup boosting
 * @{
 */
/**
 * @defgroup boosting_training_batch Batch
 * @ingroup boosting_training
 * @{
 */
/**
 * <a name="DAAL-CLASS-ALGORITHMS__BOOSTING__TRAINING__BATCH"></a>
 * \brief %Base class for training models of %boosting algorithms in the batch processing mode
 *
  * \par Enumerations
 *      - \ref classifier::training::InputId  Identifiers of input objects for %boosting algorithms
 *      - \ref classifier::training::ResultId Result identifiers for %boosting algorithm training
 *
 * \par References
 *      - \ref classifier::training::interface1::Input "classifier::training::Input" class
 *      - \ref classifier::training::interface1::Result "classifier::training::Result" class
 */
class DAAL_EXPORT Batch : public classifier::training::Batch
{
public:
    typedef classifier::training::Batch super;

    typedef super::InputType                InputType;
    typedef algorithms::boosting::Parameter ParameterType;
    typedef super::ResultType               ResultType;

    virtual ~Batch() {}

    /**
     * Returns a pointer to the newly allocated %boosting classifier training algorithm with a copy of input objects
     * and parameters of this %boosting classifier training algorithm
     * \return Pointer to the newly allocated algorithm
     */
    services::SharedPtr<Batch> clone() const
    {
        return services::SharedPtr<Batch>(cloneImpl());
    }

protected:
    virtual Batch * cloneImpl() const DAAL_C11_OVERRIDE = 0;
};
/** @} */
/** @} */
} // namespace interface1
using interface1::Batch;

} // namespace daal::algorithms::boosting::training
}
}
}
#endif // __BOOSTING_TRAINING_BATCH_H__
