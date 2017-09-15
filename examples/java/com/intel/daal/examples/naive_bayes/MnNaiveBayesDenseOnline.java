/* file: MnNaiveBayesDenseOnline.java */
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
 //     Java example of Na_ve Bayes classification in the online processing mode.
 //
 //     The program trains the Na_ve Bayes model on a supplied training data set
 //     in dense format and then performs classification of previously unseen
 //     data.
 ////////////////////////////////////////////////////////////////////////////////
 */

/**
 * <a name="DAAL-EXAMPLE-JAVA-MULTINOMIALNAIVEBAYESDENSEONLINE">
 * @example MnNaiveBayesDenseOnline.java
 */

package com.intel.daal.examples.naive_bayes;

import com.intel.daal.algorithms.classifier.prediction.ModelInputId;
import com.intel.daal.algorithms.classifier.prediction.NumericTableInputId;
import com.intel.daal.algorithms.classifier.prediction.PredictionResult;
import com.intel.daal.algorithms.classifier.prediction.PredictionResultId;
import com.intel.daal.algorithms.classifier.training.InputId;
import com.intel.daal.algorithms.classifier.training.TrainingResultId;
import com.intel.daal.algorithms.multinomial_naive_bayes.Model;
import com.intel.daal.algorithms.multinomial_naive_bayes.prediction.*;
import com.intel.daal.algorithms.multinomial_naive_bayes.training.*;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data.HomogenNumericTable;
import com.intel.daal.data_management.data.MergedNumericTable;
import com.intel.daal.data_management.data_source.DataSource;
import com.intel.daal.data_management.data_source.FileDataSource;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

class MnNaiveBayesDenseOnline {

    /* Input data set parameters */
    private static final String trainDatasetFileName = "../data/online/naivebayes_train_dense.csv";

    private static final String testDatasetFileName  = "../data/online/naivebayes_test_dense.csv";

    private static final int  nFeatures          = 20;
    private static final int  nTrainObservations = 2000;
    private static final long nClasses           = 20;

    /* Parameters for the Na_ve Bayes algorithm */
    private static TrainingResult   trainingResult;
    private static PredictionResult predictionResult;
    private static NumericTable     testGroundTruth;

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {

        trainModel();

        testModel();

        printResults();

        context.dispose();
    }

    private static void trainModel() throws java.io.FileNotFoundException, java.io.IOException {
        /* Initialize FileDataSource to retrieve the input data from a .csv file */
        FileDataSource trainDataSource = new FileDataSource(context, trainDatasetFileName,
                DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                DataSource.NumericTableAllocationFlag.NotAllocateNumericTable);

        /* Create Numeric Tables for training data and labels */
        NumericTable trainData = new HomogenNumericTable(context, Float.class, nFeatures, 0, NumericTable.AllocationFlag.DoNotAllocate);
        NumericTable trainGroundTruth = new HomogenNumericTable(context, Float.class, 1, 0, NumericTable.AllocationFlag.DoNotAllocate);
        MergedNumericTable mergedData = new MergedNumericTable(context);
        mergedData.addNumericTable(trainData);
        mergedData.addNumericTable(trainGroundTruth);

        /* Create algorithm objects to train the Na_ve Bayes model */
        TrainingOnline algorithm = new TrainingOnline(context, Float.class, TrainingMethod.defaultDense, nClasses);

        /* Pass a training data set and dependent values to the algorithm */
        algorithm.input.set(InputId.data, trainData);
        algorithm.input.set(InputId.labels, trainGroundTruth);

        while (trainDataSource.loadDataBlock(nTrainObservations, mergedData) == nTrainObservations) {

            /* Train the Na_ve Bayes model */
            algorithm.compute();
        }

        /* Retrieve the algorithm results */
        trainingResult = algorithm.finalizeCompute();
    }

    private static void testModel() throws java.io.FileNotFoundException, java.io.IOException {
        FileDataSource testDataSource = new FileDataSource(context, testDatasetFileName,
                DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                DataSource.NumericTableAllocationFlag.NotAllocateNumericTable);

        /* Create Numeric Tables for testing data and labels */
        NumericTable testData = new HomogenNumericTable(context, Float.class, nFeatures, 0, NumericTable.AllocationFlag.DoNotAllocate);
        testGroundTruth = new HomogenNumericTable(context, Float.class, 1, 0, NumericTable.AllocationFlag.DoNotAllocate);
        MergedNumericTable mergedData = new MergedNumericTable(context);
        mergedData.addNumericTable(testData);
        mergedData.addNumericTable(testGroundTruth);

        /* Retrieve the data from an input file */
        testDataSource.loadDataBlock(mergedData);

        /* Create algorithm objects to predict Na_ve Bayes values with the defaultDense method */
        PredictionBatch algorithm = new PredictionBatch(context, Float.class, PredictionMethod.defaultDense, nClasses);

        /* Pass a testing data set and the trained model to the algorithm */
        algorithm.input.set(NumericTableInputId.data, testData);
        Model model = trainingResult.get(TrainingResultId.model);
        algorithm.input.set(ModelInputId.model, model);

        /* Compute the prediction results */
        predictionResult = algorithm.compute();
    }

    private static void printResults() throws java.io.FileNotFoundException, java.io.IOException {
        NumericTable expected = testGroundTruth;
        NumericTable prediction = predictionResult.get(PredictionResultId.prediction);
        Service.printClassificationResult(expected, prediction, "Ground truth", "Classification results",
                "NaiveBayes classification results (first 20 observations):", 20);
    }
}
