/* file: layer_forward_container_base.h */
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
//  Base container of neural network forward layer.
//--
*/

#ifndef __LAYER_FORWARD_CONTAINER_BASE_H__
#define __LAYER_FORWARD_CONTAINER_BASE_H__

#include "algorithms/algorithm.h"
#include "data_management/data/tensor.h"
#include "services/daal_defines.h"
#include "algorithms/neural_networks/layers/layer_forward_types.h"

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
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__FORWARD__LAYERCONTAINERIFACEIMPL"></a>
 * \brief Provides methods of base container for forward layers.
 *        This class is associated with the daal::algorithms::neural_networks::layers::forward::LayerContainerIfaceImpl class
 */
class DAAL_EXPORT LayerContainerIfaceImpl : public AnalysisContainerIface<batch>
{
public:
    LayerContainerIfaceImpl(daal::services::Environment::env *daalEnv = 0) : AnalysisContainerIface<batch>(daalEnv) {}

    /**
     * \copydoc daal::data_management::interface1::SerializationIface::getSerializationTag()
     */
    virtual services::Status setupCompute()
    {
        return services::Status();
    }

    virtual services::Status resetCompute()
    {
        return services::Status();
    }

    /**
     * Allocates weights and biases tensors if they exist
     */
    virtual services::Status allocateInput();

    /**
     * Initializes values of weights and biases
     */
    virtual services::Status initializeInput();

protected:
    virtual services::Status completeInput();
};

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__FORWARD__ALGORITHMDISPATCHLAYERCONTAINER"></a>
 * \brief Implements a container to dispatch forward layers to cpu-specific implementations.
 *
 *
 * \tparam sse2Container        Implementation for Intel(R) Streaming SIMD Extensions 2 (Intel(R) SSE2)
 * \tparam ssse3Container       Implementation for Supplemental Streaming SIMD Extensions 3 (SSSE3)
 * \tparam sse42Container       Implementation for Intel(R) Streaming SIMD Extensions 42 (Intel(R) SSE42)
 * \tparam avxContainer         Implementation for Intel(R) Advanced Vector Extensions (Intel(R) AVX)
 * \tparam avx2Container        Implementation for Intel(R) Advanced Vector Extensions 2 (Intel(R) AVX2)
 * \tparam avx512_micContainer  Implementation for Intel(R) Xeon Phi(TM) processors/coprocessors based on Intel(R) Advanced Vector
 *                              Extensions 512 (Intel(R) AVX512)
 * \tparam avx512Container      Implementation for Intel(R) Xeon(R) processors based on Intel AVX-512
 */
template<ComputeMode mode,
         typename sse2Container
         DAAL_KERNEL_SSSE3_ONLY(typename ssse3Container)
         DAAL_KERNEL_SSE42_ONLY(typename sse42Container)
         DAAL_KERNEL_AVX_ONLY(typename avxContainer)
         DAAL_KERNEL_AVX2_ONLY(typename avx2Container)
         DAAL_KERNEL_AVX512_mic_ONLY(typename avx512_micContainer)
         DAAL_KERNEL_AVX512_ONLY(typename avx512Container)
         >
class DAAL_EXPORT AlgorithmDispatchLayerContainer : public LayerContainerIfaceImpl
{
public:
    /** Default constructor. Constructs empty container */
    AlgorithmDispatchLayerContainer(daal::services::Environment::env *daalEnv);
    virtual ~AlgorithmDispatchLayerContainer() { delete _cntr; }

    virtual services::Status compute() DAAL_C11_OVERRIDE
    {
        _cntr->setArguments(this->_in, this->_res, this->_par);
        return _cntr->compute();
    }

    virtual services::Status setupCompute() DAAL_C11_OVERRIDE
    {
        _cntr->setArguments(this->_in, this->_res, this->_par);
        return _cntr->setupCompute();
    }

    virtual services::Status resetCompute() DAAL_C11_OVERRIDE
    {
        return _cntr->resetCompute();
    }

    virtual services::Status allocateInput() DAAL_C11_OVERRIDE
    {
        _cntr->setArguments(this->_in, this->_res, this->_par);
        return _cntr->allocateInput();
    }

    virtual services::Status initializeInput() DAAL_C11_OVERRIDE
    {
        _cntr->setArguments(this->_in, this->_res, this->_par);
        return _cntr->initializeInput();
    }
protected:
    LayerContainerIfaceImpl *_cntr;
};

#define __DAAL_ALGORITHM_LAYER_CONTAINER(ContainerTemplate, ...)     \
    layers::forward::AlgorithmDispatchLayerContainer<batch,          \
    ContainerTemplate<__VA_ARGS__, sse2>                             \
    DAAL_KERNEL_SSSE3_CONTAINER(ContainerTemplate, __VA_ARGS__)      \
    DAAL_KERNEL_SSE42_CONTAINER(ContainerTemplate, __VA_ARGS__)      \
    DAAL_KERNEL_AVX_CONTAINER(ContainerTemplate, __VA_ARGS__)        \
    DAAL_KERNEL_AVX2_CONTAINER(ContainerTemplate, __VA_ARGS__)       \
    DAAL_KERNEL_AVX512_mic_CONTAINER(ContainerTemplate, __VA_ARGS__) \
    DAAL_KERNEL_AVX512_CONTAINER(ContainerTemplate, __VA_ARGS__)>

/** @} */

} // namespace interface1

using interface1::AlgorithmDispatchLayerContainer;
using interface1::LayerContainerIfaceImpl;

} // namespace forward
} // namespace layers
} // namespace neural_networks
} // namespace algorithms
} // namespace daal
#endif
