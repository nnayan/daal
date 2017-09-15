/* file: PReLULayerDenseBatch.java */
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
 //  Content:
 //     Java example of prelu layer in the batch processing mode
 ////////////////////////////////////////////////////////////////////////////////
 */

package com.intel.daal.examples.neural_networks;

import com.intel.daal.algorithms.neural_networks.layers.prelu.*;
import com.intel.daal.algorithms.neural_networks.layers.ForwardResultId;
import com.intel.daal.algorithms.neural_networks.layers.ForwardResultLayerDataId;
import com.intel.daal.algorithms.neural_networks.layers.ForwardInputId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardResultId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardInputId;
import com.intel.daal.algorithms.neural_networks.layers.BackwardInputLayerDataId;
import com.intel.daal.data_management.data.Tensor;
import com.intel.daal.data_management.data.HomogenTensor;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-EXAMPLE-JAVA-PRELULAYERBATCH">
 * @example PReLULayerDenseBatch.java
 */
class PReLULayerDenseBatch {
    private static final String datasetFileName = "../data/batch/layer.csv";
    private static final String weightsFileName = "../data/batch/layer.csv";

    /* Prelu layer parameters */
    private static final long dataDimension    = 0;  /* Starting data dimension index to apply weight */
    private static final long weightsDimension = 2;  /* Number of weight dimensions */

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {
        /* Read datasetFileName from a file and create a tensor to store forward input data */
        Tensor data    = Service.readTensorFromCSV(context, datasetFileName);
        Tensor weights = Service.readTensorFromCSV(context, weightsFileName);

        /* Create an algorithm to compute forward prelu layer results using default method */
        PreluForwardBatch preluLayerForward = new PreluForwardBatch(context, Float.class, PreluMethod.defaultDense);

        /* Set algorithm parameters */
        preluLayerForward.parameter.setDataDimension(dataDimension);
        preluLayerForward.parameter.setWeightsDimension(weightsDimension);
        preluLayerForward.parameter.setWeightsAndBiasesInitializationFlag(true);

        /* Set input objects for the forward prelu layer */
        preluLayerForward.input.set(ForwardInputId.data, data);
        preluLayerForward.input.set(ForwardInputId.weights, weights);

        /* Compute forward prelu layer results */
        PreluForwardResult forwardResult = preluLayerForward.compute();

        /* Print the results of the forward prelu layer */
        Service.printTensor("Forward prelu layer result (first 5 rows):", forwardResult.get(ForwardResultId.value), 5, 0);

        /* Get the size of forward prelu layer output */
        int nSize = (int)forwardResult.get(ForwardResultId.value).getSize();
        long[] dims = forwardResult.get(ForwardResultId.value).getDimensions();

        /* Create a tensor with backward input data */
        double[] backData = new double[nSize];
        Tensor tensorDataBack = new HomogenTensor(context, dims, backData, 0.01);

        /* Create an algorithm to compute backward prelu layer results using default method */
        PreluBackwardBatch preluLayerBackward = new PreluBackwardBatch(context, Float.class, PreluMethod.defaultDense);

        /* Set algorithm parameters */
        preluLayerBackward.parameter.setDataDimension(dataDimension);
        preluLayerBackward.parameter.setWeightsDimension(weightsDimension);

        /* Set input objects for the backward prelu layer */
        preluLayerBackward.input.set(BackwardInputId.inputGradient, tensorDataBack);
        preluLayerBackward.input.set(BackwardInputLayerDataId.inputFromForward, forwardResult.get(ForwardResultLayerDataId.resultForBackward));

        /* Compute backward prelu layer results */
        PreluBackwardResult backwardResult = preluLayerBackward.compute();

        /* Print the results of the backward prelu layer */
        Service.printTensor("Backward prelu layer result (first 5 rows):", backwardResult.get(BackwardResultId.gradient), 5, 0);
        Service.printTensor("Weights derivative (first 5 rows):", backwardResult.get(BackwardResultId.weightDerivatives), 5, 0);

        context.dispose();
    }
}
