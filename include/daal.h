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

#ifndef __DAAL_H__
#define __DAAL_H__

#include "services/daal_defines.h"
#include "services/daal_memory.h"
#include "services/base.h"
#include "services/env_detect.h"
#include "services/library_version_info.h"
#include "data_management/compression/bzip2compression.h"
#include "data_management/compression/compression.h"
#include "data_management/compression/compression_stream.h"
#include "data_management/compression/lzocompression.h"
#include "data_management/compression/rlecompression.h"
#include "data_management/compression/zlibcompression.h"
#include "data_management/data_source/csv_feature_manager.h"
#include "data_management/data_source/data_source.h"
#include "data_management/data_source/data_source_utils.h"
#include "data_management/data_source/file_data_source.h"
#include "data_management/data_source/string_data_source.h"
#include "data_management/data/aos_numeric_table.h"
#include "data_management/data/csr_numeric_table.h"
#include "data_management/data/data_archive.h"
#include "services/collection.h"
#include "data_management/data/data_block.h"
#include "data_management/data/factory.h"
#include "data_management/data/data_serialize.h"
#include "services/daal_shared_ptr.h"
#include "data_management/data/data_collection.h"
#include "data_management/data/input_collection.h"
#include "data_management/data/data_dictionary.h"
#include "data_management/data/data_utils.h"
#include "data_management/data/homogen_tensor.h"
#include "data_management/data/homogen_numeric_table.h"
#include "data_management/data/merged_numeric_table.h"
#include "data_management/data/row_merged_numeric_table.h"
#include "data_management/data/matrix.h"
#include "data_management/data/numeric_table.h"
#include "data_management/data/soa_numeric_table.h"
#include "data_management/data/symmetric_matrix.h"
#include "algorithms/classifier/classifier_training_types.h"
#include "algorithms/classifier/classifier_training_batch.h"
#include "algorithms/classifier/classifier_predict_types.h"
#include "algorithms/classifier/classifier_predict.h"
#include "algorithms/classifier/classifier_model.h"
#include "algorithms/kmeans/kmeans_types.h"
#include "algorithms/kmeans/kmeans_batch.h"
#include "algorithms/kmeans/kmeans_distributed.h"
#include "algorithms/kmeans/kmeans_init_types.h"
#include "algorithms/kmeans/kmeans_init_batch.h"
#include "algorithms/kmeans/kmeans_init_distributed.h"
#include "algorithms/naive_bayes/multinomial_naive_bayes_training_batch.h"
#include "algorithms/naive_bayes/multinomial_naive_bayes_training_online.h"
#include "algorithms/naive_bayes/multinomial_naive_bayes_training_distributed.h"
#include "algorithms/naive_bayes/multinomial_naive_bayes_predict.h"
#include "algorithms/naive_bayes/multinomial_naive_bayes_model.h"
#include "algorithms/naive_bayes/multinomial_naive_bayes_quality_metric_set_batch.h"
#include "algorithms/naive_bayes/multinomial_naive_bayes_quality_metric_set_types.h"
#include "algorithms/linear_regression/linear_regression_model.h"
#include "algorithms/linear_regression/linear_regression_ne_model.h"
#include "algorithms/linear_regression/linear_regression_predict.h"
#include "algorithms/linear_regression/linear_regression_qr_model.h"
#include "algorithms/linear_regression/linear_regression_training_distributed.h"
#include "algorithms/linear_regression/linear_regression_training_batch.h"
#include "algorithms/linear_regression/linear_regression_training_online.h"
#include "algorithms/linear_regression/linear_regression_quality_metric_set_batch.h"
#include "algorithms/linear_regression/linear_regression_quality_metric_set_types.h"
#include "algorithms/linear_regression/linear_regression_single_beta_batch.h"
#include "algorithms/linear_regression/linear_regression_single_beta_types.h"
#include "algorithms/linear_regression/linear_regression_group_of_betas_batch.h"
#include "algorithms/linear_regression/linear_regression_group_of_betas_types.h"
#include "algorithms/boosting/logitboost_model.h"
#include "algorithms/boosting/logitboost_predict.h"
#include "algorithms/boosting/logitboost_training_batch.h"
#include "algorithms/boosting/logitboost_training_types.h"
#include "algorithms/boosting/logitboost_quality_metric_set_batch.h"
#include "algorithms/boosting/logitboost_quality_metric_set_types.h"
#include "algorithms/association_rules/apriori.h"
#include "algorithms/association_rules/apriori_types.h"
#include "algorithms/cholesky/cholesky.h"
#include "algorithms/cholesky/cholesky_types.h"
#include "algorithms/stump/stump_model.h"
#include "algorithms/stump/stump_predict.h"
#include "algorithms/stump/stump_training_batch.h"
#include "algorithms/stump/stump_training_types.h"
#include "algorithms/boosting/brownboost_model.h"
#include "algorithms/boosting/brownboost_predict.h"
#include "algorithms/boosting/brownboost_training_batch.h"
#include "algorithms/boosting/brownboost_training_types.h"
#include "algorithms/boosting/brownboost_quality_metric_set_batch.h"
#include "algorithms/boosting/brownboost_quality_metric_set_types.h"
#include "algorithms/svd/svd_types.h"
#include "algorithms/svd/svd_batch.h"
#include "algorithms/svd/svd_online.h"
#include "algorithms/svd/svd_distributed.h"
#include "algorithms/pca/pca_types.h"
#include "algorithms/pca/pca_batch.h"
#include "algorithms/pca/pca_online.h"
#include "algorithms/pca/pca_distributed.h"
#include "algorithms/kernel_function/kernel_function_types.h"
#include "algorithms/kernel_function/kernel_function_types_linear.h"
#include "algorithms/kernel_function/kernel_function_types_rbf.h"
#include "algorithms/kernel_function/kernel_function.h"
#include "algorithms/kernel_function/kernel_function_linear.h"
#include "algorithms/kernel_function/kernel_function_rbf.h"
#include "algorithms/svm/svm_model.h"
#include "algorithms/svm/svm_train_types.h"
#include "algorithms/svm/svm_train.h"
#include "algorithms/svm/svm_predict_types.h"
#include "algorithms/svm/svm_predict.h"
#include "algorithms/svm/svm_quality_metric_set_batch.h"
#include "algorithms/svm/svm_quality_metric_set_types.h"
#include "algorithms/em/em_gmm.h"
#include "algorithms/em/em_gmm_types.h"
#include "algorithms/em/em_gmm_init_batch.h"
#include "algorithms/em/em_gmm_init_types.h"
#include "algorithms/outlier_detection/outlier_detection_multivariate_types.h"
#include "algorithms/outlier_detection/outlier_detection_multivariate.h"
#include "algorithms/outlier_detection/outlier_detection_univariate_types.h"
#include "algorithms/outlier_detection/outlier_detection_univariate.h"
#include "algorithms/outlier_detection/outlier_detection_bacon_types.h"
#include "algorithms/outlier_detection/outlier_detection_bacon.h"
#include "algorithms/multi_class_classifier/multi_class_classifier_model.h"
#include "algorithms/multi_class_classifier/multi_class_classifier_train.h"
#include "algorithms/multi_class_classifier/multi_class_classifier_predict.h"
#include "algorithms/multi_class_classifier/multi_class_classifier_quality_metric_set_batch.h"
#include "algorithms/multi_class_classifier/multi_class_classifier_quality_metric_set_types.h"
#include "algorithms/moments/low_order_moments_batch.h"
#include "algorithms/moments/low_order_moments_online.h"
#include "algorithms/moments/low_order_moments_distributed.h"
#include "algorithms/moments/low_order_moments_types.h"
#include "algorithms/covariance/covariance_batch.h"
#include "algorithms/covariance/covariance_online.h"
#include "algorithms/covariance/covariance_distributed.h"
#include "algorithms/covariance/covariance_types.h"
#include "algorithms/weak_learner/weak_learner_model.h"
#include "algorithms/weak_learner/weak_learner_predict.h"
#include "algorithms/weak_learner/weak_learner_training_batch.h"
#include "algorithms/distance/correlation_distance.h"
#include "algorithms/distance/correlation_distance_types.h"
#include "algorithms/distance/cosine_distance.h"
#include "algorithms/distance/cosine_distance_types.h"
#include "algorithms/boosting/adaboost_model.h"
#include "algorithms/boosting/adaboost_predict.h"
#include "algorithms/boosting/adaboost_training_batch.h"
#include "algorithms/boosting/adaboost_training_types.h"
#include "algorithms/boosting/adaboost_quality_metric_set_batch.h"
#include "algorithms/boosting/adaboost_quality_metric_set_types.h"
#include "algorithms/qr/qr_types.h"
#include "algorithms/qr/qr_batch.h"
#include "algorithms/qr/qr_online.h"
#include "algorithms/qr/qr_distributed.h"
#include "algorithms/pivoted_qr/pivoted_qr_types.h"
#include "algorithms/pivoted_qr/pivoted_qr_batch.h"
#include "algorithms/boosting/boosting_model.h"
#include "algorithms/boosting/boosting_predict.h"
#include "algorithms/boosting/boosting_training_batch.h"
#include "algorithms/quantiles/quantiles_types.h"
#include "algorithms/quantiles/quantiles_batch.h"
#include "algorithms/implicit_als/implicit_als_model.h"
#include "algorithms/implicit_als/implicit_als_predict_ratings_batch.h"
#include "algorithms/implicit_als/implicit_als_predict_ratings_distributed.h"
#include "algorithms/implicit_als/implicit_als_predict_ratings_types.h"
#include "algorithms/implicit_als/implicit_als_training_batch.h"
#include "algorithms/implicit_als/implicit_als_training_distributed.h"
#include "algorithms/implicit_als/implicit_als_training_types.h"
#include "algorithms/implicit_als/implicit_als_training_init_batch.h"
#include "algorithms/implicit_als/implicit_als_training_init_distributed.h"
#include "algorithms/implicit_als/implicit_als_training_init_types.h"
#include "algorithms/algorithm.h"
#include "algorithms/algorithm_base.h"
#include "algorithms/algorithm_types.h"
#include "algorithms/analysis.h"
#include "algorithms/model.h"
#include "algorithms/prediction.h"
#include "algorithms/training.h"
#include "algorithms/algorithm_quality_metric_batch.h"
#include "algorithms/algorithm_quality_metric_set_types.h"
#include "algorithms/algorithm_quality_metric_set_batch.h"
#include "algorithms/neural_networks/neural_networks_training.h"
#include "algorithms/neural_networks/neural_networks_prediction.h"
#include "algorithms/neural_networks/neural_networks_training_model.h"
#include "algorithms/neural_networks/neural_networks_training_distributed.h"
#include "algorithms/neural_networks/neural_networks_prediction_model.h"
#include "algorithms/neural_networks/neural_networks_types.h"
#include "algorithms/neural_networks/layers/layer.h"
#include "algorithms/neural_networks/layers/layer_types.h"
#include "algorithms/neural_networks/layers/pooling1d/average_pooling1d_layer.h"
#include "algorithms/neural_networks/layers/pooling1d/average_pooling1d_layer_types.h"
#include "algorithms/neural_networks/layers/pooling1d/maximum_pooling1d_layer.h"
#include "algorithms/neural_networks/layers/pooling1d/maximum_pooling1d_layer_types.h"
#include "algorithms/neural_networks/layers/pooling2d/average_pooling2d_layer.h"
#include "algorithms/neural_networks/layers/pooling2d/average_pooling2d_layer_types.h"
#include "algorithms/neural_networks/layers/pooling2d/maximum_pooling2d_layer.h"
#include "algorithms/neural_networks/layers/pooling2d/maximum_pooling2d_layer_types.h"
#include "algorithms/neural_networks/layers/pooling2d/stochastic_pooling2d_layer.h"
#include "algorithms/neural_networks/layers/pooling2d/stochastic_pooling2d_layer_types.h"
#include "algorithms/neural_networks/layers/spatial_pooling2d/spatial_average_pooling2d_layer.h"
#include "algorithms/neural_networks/layers/spatial_pooling2d/spatial_average_pooling2d_layer_types.h"
#include "algorithms/neural_networks/layers/spatial_pooling2d/spatial_maximum_pooling2d_layer.h"
#include "algorithms/neural_networks/layers/spatial_pooling2d/spatial_maximum_pooling2d_layer_types.h"
#include "algorithms/neural_networks/layers/spatial_pooling2d/spatial_stochastic_pooling2d_layer.h"
#include "algorithms/neural_networks/layers/spatial_pooling2d/spatial_stochastic_pooling2d_layer_types.h"
#include "algorithms/neural_networks/layers/pooling3d/average_pooling3d_layer.h"
#include "algorithms/neural_networks/layers/pooling3d/average_pooling3d_layer_types.h"
#include "algorithms/neural_networks/layers/pooling3d/maximum_pooling3d_layer.h"
#include "algorithms/neural_networks/layers/pooling3d/maximum_pooling3d_layer_types.h"
#include "algorithms/neural_networks/layers/relu/relu_layer.h"
#include "algorithms/neural_networks/layers/relu/relu_layer_types.h"
#include "algorithms/neural_networks/layers/tanh/tanh_layer.h"
#include "algorithms/neural_networks/layers/tanh/tanh_layer_types.h"
#include "algorithms/neural_networks/layers/logistic/logistic_layer.h"
#include "algorithms/neural_networks/layers/logistic/logistic_layer_types.h"
#include "algorithms/neural_networks/layers/smoothrelu/smoothrelu_layer.h"
#include "algorithms/neural_networks/layers/smoothrelu/smoothrelu_layer_types.h"
#include "algorithms/neural_networks/layers/abs/abs_layer.h"
#include "algorithms/neural_networks/layers/abs/abs_layer_types.h"
#include "algorithms/neural_networks/layers/reshape/reshape_layer.h"
#include "algorithms/neural_networks/layers/reshape/reshape_layer_types.h"
#include "algorithms/neural_networks/layers/prelu/prelu_layer.h"
#include "algorithms/neural_networks/layers/prelu/prelu_layer_types.h"
#include "algorithms/neural_networks/layers/eltwise_sum/eltwise_sum_layer.h"
#include "algorithms/neural_networks/layers/eltwise_sum/eltwise_sum_layer_types.h"
#include "algorithms/neural_networks/layers/fullyconnected/fullyconnected_layer.h"
#include "algorithms/neural_networks/layers/fullyconnected/fullyconnected_layer_types.h"
#include "algorithms/neural_networks/layers/convolution2d/convolution2d_layer.h"
#include "algorithms/neural_networks/layers/convolution2d/convolution2d_layer_types.h"
#include "algorithms/neural_networks/layers/transposed_conv2d/transposed_conv2d_layer.h"
#include "algorithms/neural_networks/layers/transposed_conv2d/transposed_conv2d_layer_types.h"
#include "algorithms/neural_networks/layers/softmax/softmax_layer.h"
#include "algorithms/neural_networks/layers/softmax/softmax_layer_types.h"
#include "algorithms/neural_networks/layers/dropout/dropout_layer.h"
#include "algorithms/neural_networks/layers/dropout/dropout_layer_types.h"
#include "algorithms/neural_networks/layers/batch_normalization/batch_normalization_layer.h"
#include "algorithms/neural_networks/layers/batch_normalization/batch_normalization_layer_types.h"
#include "algorithms/neural_networks/layers/lrn/lrn_layer.h"
#include "algorithms/neural_networks/layers/lrn/lrn_layer_types.h"
#include "algorithms/neural_networks/layers/locallyconnected2d/locallyconnected2d_layer.h"
#include "algorithms/neural_networks/layers/locallyconnected2d/locallyconnected2d_layer_types.h"
#include "algorithms/neural_networks/layers/split/split_layer.h"
#include "algorithms/neural_networks/layers/split/split_layer_types.h"
#include "algorithms/neural_networks/layers/concat/concat_layer.h"
#include "algorithms/neural_networks/layers/concat/concat_layer_types.h"
#include "algorithms/neural_networks/layers/loss/loss_layer.h"
#include "algorithms/neural_networks/layers/loss/softmax_cross_layer.h"
#include "algorithms/neural_networks/layers/loss/softmax_cross_layer_types.h"
#include "algorithms/neural_networks/layers/loss/logistic_cross_layer.h"
#include "algorithms/neural_networks/layers/loss/logistic_cross_layer_types.h"
#include "algorithms/neural_networks/initializers/initializer.h"
#include "algorithms/neural_networks/initializers/uniform/uniform_initializer.h"
#include "algorithms/neural_networks/initializers/uniform/uniform_initializer_types.h"
#include "algorithms/neural_networks/initializers/xavier/xavier_initializer.h"
#include "algorithms/neural_networks/initializers/xavier/xavier_initializer_types.h"
#include "algorithms/neural_networks/initializers/gaussian/gaussian_initializer.h"
#include "algorithms/neural_networks/initializers/gaussian/gaussian_initializer_types.h"
#include "algorithms/neural_networks/initializers/truncated_gaussian/truncated_gaussian_initializer.h"
#include "algorithms/neural_networks/initializers/truncated_gaussian/truncated_gaussian_initializer_types.h"
#include "algorithms/math/relu.h"
#include "algorithms/math/relu_types.h"
#include "algorithms/math/smoothrelu.h"
#include "algorithms/math/smoothrelu_types.h"
#include "algorithms/math/abs.h"
#include "algorithms/math/abs_types.h"
#include "algorithms/math/softmax.h"
#include "algorithms/math/softmax_types.h"
#include "algorithms/sorting/sorting_types.h"
#include "algorithms/sorting/sorting_batch.h"
#include "algorithms/math/logistic.h"
#include "algorithms/math/logistic_types.h"
#include "algorithms/math/tanh.h"
#include "algorithms/math/tanh_types.h"
#include "algorithms/optimization_solver/objective_function/objective_function_batch.h"
#include "algorithms/optimization_solver/objective_function/objective_function_types.h"
#include "algorithms/optimization_solver/objective_function/precomputed_batch.h"
#include "algorithms/optimization_solver/objective_function/precomputed_types.h"
#include "algorithms/optimization_solver/objective_function/sum_of_functions_batch.h"
#include "algorithms/optimization_solver/objective_function/sum_of_functions_types.h"
#include "algorithms/optimization_solver/objective_function/mse_batch.h"
#include "algorithms/optimization_solver/objective_function/mse_types.h"
#include "algorithms/optimization_solver/optimization_solver_batch.h"
#include "algorithms/optimization_solver/sgd/sgd_batch.h"
#include "algorithms/optimization_solver/sgd/sgd_types.h"
#include "algorithms/optimization_solver/lbfgs/lbfgs_batch.h"
#include "algorithms/optimization_solver/lbfgs/lbfgs_types.h"
#include "algorithms/optimization_solver/adagrad/adagrad_batch.h"
#include "algorithms/optimization_solver/adagrad/adagrad_types.h"
#include "algorithms/normalization/zscore.h"
#include "algorithms/normalization/zscore_types.h"
#include "algorithms/normalization/minmax.h"
#include "algorithms/normalization/minmax_types.h"
#include "algorithms/ridge_regression/ridge_regression_model.h"
#include "algorithms/ridge_regression/ridge_regression_ne_model.h"
#include "algorithms/ridge_regression/ridge_regression_predict.h"
#include "algorithms/ridge_regression/ridge_regression_training_batch.h"
#include "algorithms/ridge_regression/ridge_regression_training_online.h"
#include "algorithms/ridge_regression/ridge_regression_training_distributed.h"
#include "algorithms/neural_networks/layers/lcn/lcn_layer.h"
#include "algorithms/neural_networks/layers/lcn/lcn_layer_types.h"
#include "algorithms/k_nearest_neighbors/kdtree_knn_classification_model.h"
#include "algorithms/k_nearest_neighbors/kdtree_knn_classification_predict.h"
#include "algorithms/k_nearest_neighbors/kdtree_knn_classification_training_batch.h"
#include "algorithms/k_nearest_neighbors/kdtree_knn_classification_training_types.h"
#include "algorithms/k_nearest_neighbors/kdtree_knn_classification_predict_types.h"
#include "algorithms/decision_tree/decision_tree_classification_model.h"
#include "algorithms/decision_tree/decision_tree_classification_predict.h"
#include "algorithms/decision_tree/decision_tree_classification_training_batch.h"
#include "algorithms/decision_tree/decision_tree_classification_training_types.h"
#include "algorithms/decision_tree/decision_tree_classification_predict_types.h"
#include "algorithms/decision_tree/decision_tree_regression_model.h"
#include "algorithms/decision_tree/decision_tree_regression_predict.h"
#include "algorithms/decision_tree/decision_tree_regression_training_batch.h"
#include "algorithms/decision_tree/decision_tree_regression_training_types.h"
#include "algorithms/decision_tree/decision_tree_regression_predict_types.h"
#include "algorithms/decision_forest/decision_forest_classification_model.h"
#include "algorithms/decision_forest/decision_forest_classification_predict.h"
#include "algorithms/decision_forest/decision_forest_classification_training_batch.h"
#include "algorithms/decision_forest/decision_forest_regression_model.h"
#include "algorithms/decision_forest/decision_forest_regression_predict.h"
#include "algorithms/decision_forest/decision_forest_regression_training_batch.h"
#include "algorithms/decision_forest/decision_forest_regression_training_types.h"
#include "algorithms/regression/regression_training_batch.h"
#include "algorithms/regression/regression_predict.h"
#include "algorithms/linear_model/linear_model_training_batch.h"
#include "algorithms/linear_model/linear_model_predict.h"
#include "algorithms/distributions/distribution.h"
#include "algorithms/distributions/distribution_types.h"
#include "algorithms/distributions/uniform/uniform.h"
#include "algorithms/distributions/uniform/uniform_types.h"
#include "algorithms/distributions/normal/normal.h"
#include "algorithms/distributions/normal/normal_types.h"
#include "algorithms/distributions/bernoulli/bernoulli.h"
#include "algorithms/distributions/bernoulli/bernoulli_types.h"
#include "algorithms/engines/engine.h"
#include "algorithms/engines/mt19937/mt19937.h"
#include "algorithms/engines/mt19937/mt19937_types.h"

#endif /* #ifndef __DAAL_H__ */
