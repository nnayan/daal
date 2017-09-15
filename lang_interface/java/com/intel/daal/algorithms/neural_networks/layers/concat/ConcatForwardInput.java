/* file: ConcatForwardInput.java */
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

/**
 * @defgroup concat_forward Forward Concat Layer
 * @brief Contains classes for the forward concat layer
 * @ingroup concat
 * @{
 */
package com.intel.daal.algorithms.neural_networks.layers.concat;

import com.intel.daal.algorithms.neural_networks.layers.ForwardInputLayerDataId;
import com.intel.daal.data_management.data.Factory;
import com.intel.daal.data_management.data.Tensor;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__CONCAT__CONCATFORWARDINPUT"></a>
 * @brief %Input object for the forward concat layer
 */
public class ConcatForwardInput extends com.intel.daal.algorithms.neural_networks.layers.ForwardInput {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    public ConcatForwardInput(DaalContext context, long cObject) {
        super(context, cObject);
    }

    /**
     * Sets the input object of the forward concat layer
     * @param id    Identifier of the input object
     * @param val   Value of the input object
     * @param index ConcatIndex of the input object
     */
    public void set(ForwardInputLayerDataId id, Tensor val, long index) {
        if (id == ForwardInputLayerDataId.inputLayerData) {
            cSetInput(cObject, id.getValue(), val.getCObject(), index);
        }
        else {
            throw new IllegalArgumentException("Incorrect ConcatForwardInputLayerDataId");
        }
    }

    /**
     * Returns the input object of the forward concat layer
     * @param id    Identifier of the input object
     * @param index ConcatIndex of the input object
     * @return Input object that corresponds to the given identifier
     */
    public Tensor get(ForwardInputLayerDataId id, long index) {
        if (id == ForwardInputLayerDataId.inputLayerData) {
            return (Tensor)Factory.instance().createObject(getContext(), cGetInput(cObject, id.getValue(), index));
        }
        else {
            throw new IllegalArgumentException("id unsupported");
        }
    }

    private native void cSetInput(long cObject, int id, long ntAddr, long index);
    private native long cGetInput(long cObject, int id, long index);
}
/** @} */
