/* file: lcn_layer_forward_types.h */
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
//  Implementation of the forward local contrast normalization layer.
//--
*/

#ifndef __LCN_LAYER_FORWARD_TYPES_H__
#define __LCN_LAYER_FORWARD_TYPES_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "data_management/data/homogen_tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer_forward_types.h"
#include "algorithms/neural_networks/layers/lcn/lcn_layer_types.h"

namespace daal
{
namespace algorithms
{
namespace neural_networks
{
namespace layers
{
namespace lcn
{
/**
 * @defgroup lcn_layers_forward Forward Local contrast normalization (LCN) Layer
 * \copydoc daal::algorithms::neural_networks::layers::lcn::forward
 * @ingroup lcn_layers
 * @{
 */
/**
 * \brief Contains classes for the forward local contrast normalization layer
 */
namespace forward
{
/**
 * \brief Contains version 1.0 of Intel(R) Data Analytics Acceleration Library (Intel(R) DAAL) interface.
 */
namespace interface1
{

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__LCN__FORWARD__INPUT"></a>
 * \brief %Input objects for the forward local contrast normalization layer
 */
class DAAL_EXPORT Input : public layers::forward::Input
{
public:
    typedef layers::forward::Input super;
    /**
     * Default constructor
     */
    Input();

    /** Copy constructor */
    Input(const Input& other);

    virtual ~Input() {}

    /**
     * Sets an input object for the forward local contrast normalization layer
     */
    using layers::forward::Input::set;
    /**
     * Returns an input object for the forward local contrast normalization layer
    */
    using layers::forward::Input::get;

    /**
     * Returns dimensions of weights tensor
     * \return Dimensions of weights tensor
     */
    virtual const services::Collection<size_t> getWeightsSizes(const layers::Parameter *parameter) const DAAL_C11_OVERRIDE;

    /**
     * Returns dimensions of biases tensor
     * \return Dimensions of biases tensor
     */
    virtual const services::Collection<size_t> getBiasesSizes(const layers::Parameter *parameter) const DAAL_C11_OVERRIDE;

    /**
     * Checks input object of the forward local contrast normalization layer
     * \param[in] parameter %Parameter of layer
     * \param[in] method    Computation method of the layer
     *
     * \return Status of computations
     */
    services::Status check(const daal::algorithms::Parameter *parameter, int method) const DAAL_C11_OVERRIDE;
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__LCN__RESULT"></a>
 * \brief Results obtained with the compute() method of the forward local contrast normalization layer
 *        in the batch processing mode
 */
class DAAL_EXPORT Result : public layers::forward::Result
{
public:
    DECLARE_SERIALIZABLE_CAST(Result);
    /**
     * Default constructor
     */
    Result();

    virtual ~Result() {}

    /**
     * Returns the result of the forward local contrast normalization layer
     */
    using layers::forward::Result::get;

    /**
     * Sets the result of the forward local contrast normalization layer
     */
    using layers::forward::Result::set;

    /**
     * Returns dimensions of value tensor
     * \return Dimensions of value tensor
     */
    virtual const services::Collection<size_t> getValueSize(const services::Collection<size_t> &inputSize,
                                                            const daal::algorithms::Parameter *par, const int method) const DAAL_C11_OVERRIDE;

    /**
     * Allocates memory to store the result of forward  local contrast normalization layer
     * \param[in] input     %Input object for the algorithm
     * \param[in] parameter %Parameter of forward local contrast normalization layer
     * \param[in] method    Computation method for the layer
     *
     * \return Status of computations
     */
    template <typename algorithmFPType>
    DAAL_EXPORT services::Status allocate(const daal::algorithms::Input *input, const daal::algorithms::Parameter *parameter, const int method);

    /**
     * Returns the result of forward local contrast normalization layer
     * \param[in] id   Identifier of the result
     * \return         Result that corresponds to the given identifier
     */
    data_management::TensorPtr get(LayerDataId id) const;

    /**
     * Sets the result of forward local contrast normalization layer
     * \param[in] id     Identifier of the result
     * \param[in] value  Result
     */
    void set(LayerDataId id, const data_management::TensorPtr &value);

    /**
     * Checks the result of the forward local contrast normalization layer
     * \param[in] input   %Input object of the layer
     * \param[in] par     %Parameter of the layer
     * \param[in] method  Computation method of the layer
     *
     * \return Status of computations
     */
    services::Status check(const daal::algorithms::Input *input, const daal::algorithms::Parameter *par, int method) const DAAL_C11_OVERRIDE;

protected:
    void getSigmaDimensions(const Input *in, const Parameter *algParameter, services::Collection<size_t> &sigmaDims) const;
    void getCDimensions(const Input *in, const Parameter *algParameter, services::Collection<size_t> &cDims) const;

    /** \private */
    template<typename Archive, bool onDeserialize>
    services::Status serialImpl(Archive *arch)
    {
        daal::algorithms::Result::serialImpl<Archive, onDeserialize>(arch);

        return services::Status();
    }

    services::Status serializeImpl(data_management::InputDataArchive  *arch) DAAL_C11_OVERRIDE
    {
        serialImpl<data_management::InputDataArchive, false>(arch);

        return services::Status();
    }

    services::Status deserializeImpl(const data_management::OutputDataArchive *arch) DAAL_C11_OVERRIDE
    {
        serialImpl<const data_management::OutputDataArchive, true>(arch);

        return services::Status();
    }
};
typedef services::SharedPtr<Result> ResultPtr;

} // namespace interface1
using interface1::Input;
using interface1::Result;
using interface1::ResultPtr;

} // namespace forward
/** @} */
} // namespace lcn
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal

#endif
