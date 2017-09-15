/* file: Parameter.java */
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
 * @ingroup sum_of_functions
 * @{
 */
package com.intel.daal.algorithms.optimization_solver.sum_of_functions;

import com.intel.daal.services.DaalContext;
import com.intel.daal.data_management.data.DataCollection;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data.Factory;
import com.intel.daal.data_management.data.Factory;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__OPTIMIZATION_SOLVER__SUM_OF_FUNCTIONS__PARAMETER"></a>
 * @brief Parameters of the Sum of functions algorithm
 */
public class Parameter extends com.intel.daal.algorithms.optimization_solver.objective_function.Parameter {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    long cCreatedParameter;

    /**
     * Constructs the parameter for the sum of functions algorithm
     * @param context       Context to manage the sum of functions algorithm
     * @param cParameter    Pointer to C++ implementation of the parameter
     */
    public Parameter(DaalContext context, long cParameter) {
        super(context, cParameter);
    }

    /**
     * Constructs the parameter for the sum of functions algorithm
     * @param numberOfTerms The number of terms in the function that can be represented as sum
     * @param context       Context to manage the sum of functions algorithm
     */
    public Parameter(long numberOfTerms, DaalContext context) {
        super(context);
        this.cCreatedParameter = cCreateParameter(numberOfTerms);
        this.cObject = this.cCreatedParameter;
    }

    /**
     * Sets the numeric table of size 1 x m where m is batch size that represent
     * a batch of indices used to compute the function results, e.g.,
     * value of the sum of the functions. If no indices are provided,
     * all terms will be used in the computations.
     * @param batchIndices The numeric table of size 1 x m where m is batch size that represent
     * a batch of indices used to compute the function results, e.g.,
     * value of the sum of the functions. If no indices are provided,
     * all terms will be used in the computations.
     */
    public void setBatchIndices(NumericTable batchIndices) {
        cSetBatchIndices(this.cObject, batchIndices.getCObject());
    }

    /**
     * Gets the numeric table of size 1 x m where m is batch size that represent
     * a batch of indices used to compute the function results, e.g.,
     * value of the sum of the functions. If no indices are provided,
     * all terms will be used in the computations.
     * @return The numeric table of size 1 x m where m is batch size that represent
     * a batch of indices used to compute the function results, e.g.,
     * value of the sum of the functions. If no indices are provided,
     * all terms will be used in the computations.
     */
    public NumericTable getBatchIndices() {
        return (NumericTable)Factory.instance().createObject(getContext(), cGetBatchIndices(this.cObject));
    }

    /**
     * Sets the number of terms in the function
     * @param numberOfTerms The number of terms in the function
     */
    public void setNumberOfTerms(long numberOfTerms) {
        cSetNumberOfTerms(this.cObject, numberOfTerms);
    }

    /**
     * Gets the number of terms in the function
     * @return The number of terms in the function
     */
    public long getNumberOfTerms() {
        return cGetNumberOfTerms(this.cObject);
    }

    /**
     * Sets parameter pointer for algorithm in native side
     * @param cParameter The address of the native parameter object
     * @param cAlgorithm The address of the native algorithm object
     */
    public void setCParameter(long cParameter, long cAlgorithm) {
        this.cObject = cParameter;
        cSetCParameter(this.cObject, cAlgorithm);
    }

    /**
    * Releases memory allocated for the native parameter object
    */
    @Override
    public void dispose() {
        if(this.cCreatedParameter != 0) {
            cParameterDispose(this.cCreatedParameter);
            this.cCreatedParameter = 0;
        }
    }

    private native void cSetBatchIndices(long parAddr, long batchIndicesAddr);
    private native long cGetBatchIndices(long parAddr);
    private native void cSetNumberOfTerms(long parAddr, long numberOfTerms);
    private native long cGetNumberOfTerms(long parAddr);
    private native long cCreateParameter(long numberOfTerms);
    private native void cParameterDispose(long cCreatedParameter);
    private native void cSetCParameter(long cParameter, long cAlgorithm);
}
/** @} */
