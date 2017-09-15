/* file: regression_predict.h */
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
//  Implementation of the interface for the regression model-based prediction
//--
*/

#ifndef __REGRESSION_PREDICT_H__
#define __REGRESSION_PREDICT_H__

#include "algorithms/algorithm.h"
#include "algorithms/regression/regression_predict_types.h"

namespace daal
{
namespace algorithms
{
namespace regression
{
namespace prediction
{
namespace interface1
{
/**
 * @defgroup base_regression_prediction_batch Batch
 * @ingroup base_regression_prediction
 * @{
 */
/**
 * <a name="DAAL-CLASS-ALGORITHMS__REGRESSION__PREDICTION__BATCH"></a>
 * \brief Provides methods to run implementations of the regression model-based prediction
 *
 * \par References
 *      - \ref regression::interface1::Model "regression::Model" class
 *      - \ref training::interface1::Batch "training::Batch" class
 */
class Batch : public daal::algorithms::Prediction
{
public:
    virtual ~Batch() {}
    virtual Input* getInput() = 0;

    /**
     * Registers user-allocated memory to store the result of the regression model-based prediction
     * \param[in] res    Structure to store the result of the regression model-based prediction
     *
     * \return Status of computations
     */
    services::Status setResult(const ResultPtr& res)
    {
        DAAL_CHECK(res, services::ErrorNullResult)
        _result = res;
        _res = _result.get();
        return services::Status();
    }

    /**
     * Returns the structure that contains the result of the regression model-based prediction
     * \return Structure that contains the result of the the regression model-based prediction
     */
    ResultPtr getResult() { return _result; }

protected:
    ResultPtr _result;
};
/** @} */
}
using interface1::Batch;
}
}
}
}
#endif
