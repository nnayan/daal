/* file: PCATransformDenseBatch.java */
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
 //     Java example of PCA transformation algorithm
 ////////////////////////////////////////////////////////////////////////////////
 */

package com.intel.daal.examples.pca_transform;

import com.intel.daal.algorithms.pca.*;
import com.intel.daal.algorithms.pca.transform.*;
import com.intel.daal.data_management.data.NumericTable;
import com.intel.daal.data_management.data.KeyValueDataCollection;
import com.intel.daal.data_management.data_source.DataSource;
import com.intel.daal.data_management.data_source.FileDataSource;
import com.intel.daal.examples.utils.Service;
import com.intel.daal.services.DaalContext;

/**
 * <a name="DAAL-EXAMPLE-JAVA-PCATRANSFORMDENSEBATCH">
 * @example PCATransformDenseBatch.java
 */

class PCATransformDenseBatch {
    private static final String dataset = "../data/batch/pca_transform.csv";

    private static DaalContext context = new DaalContext();

    public static void main(String[] args) throws java.io.FileNotFoundException, java.io.IOException {
        /* Retrieve the input data */
        FileDataSource dataSource = new FileDataSource(context, dataset,
                                                       DataSource.DictionaryCreationFlag.DoDictionaryFromContext,
                                                       DataSource.NumericTableAllocationFlag.DoAllocateNumericTable);
        dataSource.loadDataBlock();
        NumericTable input = dataSource.getNumericTable();

        /* Create a PCA algorithm */
        Batch algorithm =
            new Batch(context, Float.class, Method.correlationDense);

        /* Set an input object for the algorithm */
        algorithm.input.set(InputId.data, input);

        /* Compute PCA */
        Result result = algorithm.compute();

        /* Create a PCA transform algorithm */
        TransformBatch transformAlgorithm = new TransformBatch(context, Float.class, TransformMethod.defaultDense, 2);

        /* Set an input object for the algorithm */
        transformAlgorithm.input.set(TransformInputId.data, input);

        /* Set eigenvectors for the algorithm */
        transformAlgorithm.input.set(TransformInputId.eigenvectors, result.get(ResultId.eigenVectors));

        /* Compute PCA transfromation */
        TransformResult transformResult = transformAlgorithm.compute();

        /* Print the results of stage */
        Service.printNumericTable("First 4 rows of the input data:", input, 4);
        Service.printNumericTable("First 4 rows of the PCA transformation result:",
             transformResult.get(TransformResultId.transformedData), 4);

        context.dispose();
    }
}
