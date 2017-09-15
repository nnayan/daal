/* file: layer_forward.h */
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
//  Implementation of neural network layer.
//--
*/

#ifndef __LAYER_FORWARD_H__
#define __LAYER_FORWARD_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer_forward_types.h"
#include "layer_forward_container_base.h"

namespace daal
{
namespace algorithms
{
/**
 * \brief Contains classes for training and prediction using neural network
 */
namespace neural_networks
{
/**
 * \brief Contains classes for neural network layers
 */
namespace layers
{
/**
 * \brief Contains classes for the forward stage of the neural network layer
 */
namespace forward
{
namespace interface1
{
/**
 * @ingroup layers_forward
 * @{
 */
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__FORWARD__LAYERIFACE"></a>
 *  \brief Abstract class which defines interface for the layer
 */
class LayerIface : public daal::algorithms::Analysis<batch>
{
public:
    virtual ~LayerIface() {};

    /**
     * Returns the structure that contains results of the layer
     * \return Structure that contains results of the layer
     */
    virtual forward::ResultPtr getLayerResult() = 0;

    /**
     * Returns the structure that contains input objects of the layer
     * \return Structure that contains input objects of the layer
     */
    virtual Input *getLayerInput() = 0;

    /**
     * Returns the structure that contains parameters of the layer
     * \return Structure that contains parameters of the layer
     */
    virtual Parameter *getLayerParameter() = 0;

    /**
     * Returns a pointer to the newly allocated forward neural network layer with a copy of input objects
     * and parameters of this layer
     * \return Pointer to the newly allocated forward layer
     */
    daal::algorithms::neural_networks::layers::forward::LayerIfacePtr clone() const
    {
        return LayerIfacePtr(cloneImpl());
    }

    /**
     * Allocates memory buffers needed for the computations
     */
    virtual services::Status allocateResult() = 0;

    /**
     * Allocates memory buffers needed for the computations
     */
    virtual services::Status allocateInput() = 0;

    /**
     * Initializes values of weights and biases if needed
     */
    virtual services::Status initializeInput() = 0;
    /**
     * Connects two layers in neural network by getting tensor with value
     * from the result of the previous layer and adding it to the input object of this layer algorithm
     * \param[in] result        Structure that contains results of the previous layer
     * \param[in] resultIndex   Index of the tensor with value in the structure that contains
     *                          results of the previous layer
     * \param[in] inputIndex    Index in the input object of this layer algorithm
     *                          where the tensor with value should be placed
     */
    virtual services::Status addInput(forward::ResultPtr result, size_t resultIndex, size_t inputIndex) = 0;

    /**
     * Returns the layer that corresponds to this layer on the prediction stage
     * \return The layer that corresponds to this layer on the prediction stage
     */
    virtual layers::forward::LayerIfacePtr getLayerForPrediction() const = 0;

protected:
    virtual LayerIface *cloneImpl() const = 0;
};

typedef services::SharedPtr<LayerIface> LayerIfacePtr;
/** @} */
/**
 * @ingroup layers_forward
 * @{
 */
/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__FORWARD__LAYERIFACEIMPL"></a>
 *  \brief Implements the abstract interface LayerIface. LayerIfaceImpl is, in turn, the base class
 *         for the classes interfacing the layers.
 */
class LayerIfaceImpl : public LayerIface
{
public:
    virtual ~LayerIfaceImpl() {};

    /**
     * Allocates memory buffers needed for the computations
     */
    virtual services::Status allocateInput() DAAL_C11_OVERRIDE
    {
        this->_ac->setArguments(this->_in, this->_res, this->_par);
        LayerContainerIfaceImpl *ac = dynamic_cast<LayerContainerIfaceImpl *>(_ac);
        return ac->allocateInput();
    }

    /**
     * Initializes values of weights and biases if needed
     */
    virtual services::Status initializeInput() DAAL_C11_OVERRIDE
    {
        this->_ac->setArguments(this->_in, this->_res, this->_par);
        setParameter();
        LayerContainerIfaceImpl *ac = dynamic_cast<LayerContainerIfaceImpl *>(_ac);
        return ac->initializeInput();
    }

    /**
     * \copydoc LayerIface::addInput
     */
    virtual services::Status addInput(forward::ResultPtr result, size_t resultIndex, size_t inputIndex) DAAL_C11_OVERRIDE
    {
        return getLayerInput()->addData(result->getValue(resultIndex), inputIndex);
    }

    /**
     * Returns the layer that corresponds to this layer on the prediction stage
     * \return The layer that corresponds to this layer on the prediction stage
     */
    virtual layers::forward::LayerIfacePtr getLayerForPrediction() const DAAL_C11_OVERRIDE
    {
        return this->clone();
    }

protected:
    virtual void setParameter() DAAL_C11_OVERRIDE
    {
        if(this->getLayerParameter())
        {
            this->getLayerParameter()->weightsInitializer->getParameter()->layer = services::SharedPtr<LayerIface>(this, services::EmptyDeleter());
            this->getLayerParameter()->biasesInitializer->getParameter()->layer = services::SharedPtr<LayerIface>(this, services::EmptyDeleter());
        }
    }
};

typedef services::SharedPtr<LayerIfaceImpl> LayerIfaceImplPtr;
/** @} */
} // namespace interface1
using interface1::LayerIface;
using interface1::LayerIfacePtr;
using interface1::LayerIfaceImpl;
using interface1::LayerIfaceImplPtr;

} // namespace forward
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal
#endif
