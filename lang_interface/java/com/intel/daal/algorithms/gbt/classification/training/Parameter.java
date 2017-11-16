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
 * @ingroup gbt_classification_training
 */
/**
 * @brief Contains classes of the gradient boosted trees classification algorithm training
 */
package com.intel.daal.algorithms.gbt.classification.training;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-CLASS-ALGORITHMS__GBT__CLASSIFICATION__TRAINING__PARAMETER"></a>
 * @brief Base class for parameters of the gradient boosted trees classification training algorithm
 */
public class Parameter extends com.intel.daal.algorithms.classifier.Parameter {

    public Parameter(DaalContext context, long cParameter) {
        super(context, cParameter);
    }

    /**
     * Returns maximal number of iterations parameter of the gradient boosted trees training algorithm
     * @return Number of iterations
     */
    public long getMaxIterations() {
        return cGetMaxIterations(this.cObject);
    }

    /**
     * Sets maximal number of iterations for the gradient boosted trees training algorithm
     * @param n Number of iterations
     */
    public void setMaxIterations(long n) {
        cSetMaxIterations(this.cObject, n);
    }

    /**
     * Returns fraction of observations used for a training of one tree, 0 to 1.
     * Default is 1 (sampling without replacement)
     * @return Fraction of observations
     */
    public double getObservationsPerTreeFraction() {
        return cGetObservationsPerTreeFraction(this.cObject);
    }

    /**
     * Sets fraction of observations used for a training of one tree, 0 to 1
     * @param value Fraction of observations
     */
    public void setObservationsPerTreeFraction(double value) {
        cSetObservationsPerTreeFraction(this.cObject, value);
    }

    /**
     * Returns number of features tried as possible splits by the gradient boosted trees classification training algorithm
     * If 0 then sqrt(p) is used, where p is the total number of features.
     * @return Number of features
     */
    public long getFeaturesPerNode() {
        return cGetFeaturesPerNode(this.cObject);
    }

    /**
     * Sets the number of features tried as possible splits by gradient boosted trees classification training algorithm.
     * If 0 then sqrt(p) is used, where p is the total number of features.
     * @param value Number of features
     */
    public void setFeaturesPerNode(long value) {
        cSetFeaturesPerNode(this.cObject, value);
    }

    /**
     * Returns maximal tree depth. Default is 0 (unlimited)
     * @return Maximal tree depth
     */
    public long getMaxTreeDepth() {
        return cGetMaxTreeDepth(this.cObject);
    }

    /**
     * Sets maximal tree depth. Default is 0 (unlimited)
     * @param value Maximal tree depth
     */
    public void setMaxTreeDepth(long value) {
        cSetMaxTreeDepth(this.cObject, value);
    }

    /**
     * Returns minimal number of samples per node. Default is 1
     * @return Minimal number of samples
     */
    public long getMinObservationsInLeafNode() {
        return cGetMinObservationsInLeafNode(this.cObject);
    }

    /**
     * Sets minimal number of samples per node. Default is 1
     * @param value Minimal number of samples
     */
    public void setMinObservationsInLeafNode(long value) {
        cSetMinObservationsInLeafNode(this.cObject, value);
    }

    /**
     * Sets the engine to be used by the algorithm
     * @param engine to be used by the algorithm
     */
    public void setEngine(com.intel.daal.algorithms.engines.BatchBase engine) {
        cSetEngine(cObject, engine.cObject);
    }

    /**
     * Returns shrinkage parameter (learning rate) of the training procedure
     * Scales the contribution of each tree by a factor (0, 1].
     * Default is 0.3
     * @return Shrinkage value
     */
    public double getShrinkage() {
        return cGetShrinkage(this.cObject);
    }

    /**
     * Sets shrinkage parameter value
     * @param value Shrinkage value
     */
    public void setShrinkage(double value) {
        cSetShrinkage(this.cObject, value);
    }

    /**
     * Returns loss regularization parameter of the training procedure.
     * Min loss reduction required to make a further partition on a leaf node of the tree.
     * Range: [0, inf). Default is 0
     * @return minSplitLoss value
     */
    public double getMinSplitLoss() {
        return cGetMinSplitLoss(this.cObject);
    }

    /**
     * Sets minSplitLoss parameter value
     * @param value minSplitLoss value
     */
    public void setMinSplitLoss(double value) {
        cSetMinSplitLoss(this.cObject, value);
    }

    /**
     * Returns lambda parameter of the training procedure (L2 regularization on weights lambda)
     * Range: [0, inf). Default is 1
     * @return lambda value
     */
    public double getLambda() {
        return cGetLambda(this.cObject);
    }

    /**
     * Sets lambda parameter value
     * @param value lambda value
     */
    public void setLambda(double value) {
        cSetLambda(this.cObject, value);
    }

    private native long cGetMaxIterations(long parAddr);
    private native void cSetMaxIterations(long parAddr, long value);

    private native void   cSetObservationsPerTreeFraction(long parAddr, double value);
    private native double cGetObservationsPerTreeFraction(long parAddr);

    private native long cGetFeaturesPerNode(long parAddr);
    private native void cSetFeaturesPerNode(long parAddr, long value);

    private native long cGetMaxTreeDepth(long parAddr);
    private native void cSetMaxTreeDepth(long parAddr, long value);

    private native long cGetMinObservationsInLeafNode(long parAddr);
    private native void cSetMinObservationsInLeafNode(long parAddr, long value);

    private native void cSetEngine(long cObject, long cEngineObject);

    private native void   cSetShrinkage(long parAddr, double value);
    private native double cGetShrinkage(long parAddr);

    private native void   cSetMinSplitLoss(long parAddr, double value);
    private native double cGetMinSplitLoss(long parAddr);

    private native void   cSetLambda(long parAddr, double value);
    private native double cGetLambda(long parAddr);
}
/** @} */
