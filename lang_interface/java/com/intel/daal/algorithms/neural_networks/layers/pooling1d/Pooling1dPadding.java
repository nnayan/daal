/* file: Pooling1dPadding.java */
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
 * @ingroup pooling1d
 * @{
 */
package com.intel.daal.algorithms.neural_networks.layers.pooling1d;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__NEURAL_NETWORKS__LAYERS__POOLING1D__POOLING1DPADDING"></a>
 * \brief Data structure representing the number of data elements to implicitly add
 *        to each side of the 1D subtensor on which one-dimensional pooling is performed
 */
public final class Pooling1dPadding {
    private long[] size;     /*!< Array of numbers of data elements to implicitly add to each size of
                                  the 1D subtensor on which one-dimensional pooling is performed */
    /**
    * Constructs Padding with parameters
    * @param first  Number of data elements to add to the the first dimension of the 1D subtensor
    */
    public Pooling1dPadding(long first) {
        size = new long[1];
        size[0] = first;
    }

    /**
    *  Sets the array of numbers of data elements to implicitly add to each size of
    *  the one-dimensional subtensor on which one-dimensional pooling is performed
    * @param first  Number of data elements to add to the the first dimension of the 1D subtensor
    */
    public void setSize(long first) {
        size[0] = first;
    }

    /**
    *  Gets the array of numbers of data elements to implicitly add to each size of
    *  the one-dimensional subtensor on which one-dimensional pooling is performed
    * @return Array of numbers of data elements to implicitly add to each size of
    *         he one-dimensional subtensor on which one-dimensional pooling is performed
    */
    public long[] getSize() {
        return size;
    }
}
/** @} */
