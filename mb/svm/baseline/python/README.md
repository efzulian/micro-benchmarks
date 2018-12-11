We provide both simple Python interface and scikit-learn wrapper interface. Before you use the Python interface, you must build ThunderSVM.

## Instructions for building ThunderSVM
* Please refer to [Installation](http://thundersvm.readthedocs.io/en/latest/how-to.html) for building ThunderSVM.

* Then, under ```./build/lib/``` of the ThunderSVM root directory, you should be able to see a library of ThunderSVM (e.g., ```libthundersvm.so``` on Linux machines).

* After you have successfully done the above two steps, it is ready to start using Python interfaces.

## Simple Python interface:
### Methods
By default, the directory for storing the training data and results is the working directory.

*svm_read_problem('file_name')*:\
	read data from *file_name*.\
*return: (labels, instances)*

*svm_train(labels, instances, 'model_file_name', parameters)*:\
	train the SVM model and save the result to *model_file_name*.

*svm_predict(labels, instances, 'model_file_name', 'output_file_name', parameters)*:\
	use the SVM model saved in *model_file_name* to predict the labels of the given instances and store the results to *output_file_name*.

### Examples
```python
from svm import *
y,x = svm_read_problem('../dataset/mnist.scale')
svm_train(y,x,'mnist.scale.model','-s 0 -t 2 -g 0.125 -c 10 -e 0.001')
y,x=svm_read_problem('../dataset/mnist.scale.t')
svm_predict(y,x,'mnist.scale.model','mnist.scale.out')
```

## Scikit-learn wrapper interface
### Usage
The usage of thundersvm scikit interface is similar to scikit.svm.

##### SVM classification
*class SVC(kernel = 2, degree = 3, gamma = 'auto', coef0 = 0.0, cost = 1.0, tol = 0.001, probability = False, class_weight = None, shrinking = False, cache_size = None, verbose = False, max_iter = -1, n_cores = -1, random_state = None, decison_function_shape = 'ovo')*

*class NuSVC(kernel = 2, degree = 3, gamma = 'auto', coef0 = 0.0, nu = 0.5, tol = 0.001, probability = False, shrinking = False, cache_size = None, verbose = False, max_iter = -1, n_cores = -1, random_state = None, decison_function_shape = 'ovo')*

##### One-class SVMs

*class OneClassSVM(kernel = 2, degree = 3, gamma = 'auto', coef0 = 0.0, nu = 0.5, tol = 0.001, shrinking = False, cache_size = None, verbose = False, max_iter = -1, n_cores = -1, random_state = None)*

##### SVM regression
class SVR(kernel = 2, degree = 3, gamma = 'auto', coef0 = 0.0, cost = 1.0, epsilon = 0.1, tol = 0.001, probability = False, shrinking = False, cache_size = None, verbose = False, max_iter = -1, n_cores = -1)

*class NuSVR(kernel = 2, degree = 3, gamma = 'auto', coef0 = 0.0, nu = 0.5, cost = 1.0, tol = 0.001, probability = False, shrinking = False,  cache_size = None, verbose = False, max_iter = -1, n_cores = -1)*


### Parameters
*kernel*: int, optional(default=2)\
    set type of kernel function\
                    	0 -- linear: u'*v\
                    	1 -- polynomial: (gamma*u'*v + coef0)^degree\
                    	2 -- radial basis function: exp(-gamma*|u-v|^2)\
                    	3 -- sigmoid: tanh(gamma*u'*v + coef0)\
                    	4 -- precomputed kernel (kernel values in training_set_file)

*degree*: int, optional(default=3)\
    set degree in kernel function

*gamma*: float, optional(default='auto')\
    set gamma in kernel function (auto:1/num_features)

*coef0*: float, optional(default=0.0)\
    set coef0 in kernel function

*cost*: float, optional(default=1.0)\
    set the parameter C of C-SVC, epsilon-SVR, and nu-SVR

*nu*: float, optional(default=0.5)\
    set the parameter nu of nu-SVC, one-class SVM, and nu-SVR

*epsilon*: float, optional(default=0.1)\
    set the epsilon in loss function of epsilon-SVR

*tol*: float, optional(default=0.001)\
    set tolerance of termination criterion (default 0.001)

*probability*: boolean, optional(default=False)\
    whether to train a SVC or SVR model for probability estimates, True or False

*class_weight*:  {dict, ‘balanced’}, optional(default=None)\
    set the parameter C of class i to weight*C, for C-SVC

*shrinking*: boolean, optional (default=False, Not support yet for True)\
    Whether to use the shrinking heuristic. .

*cache_size*: float, optional, Not support yet.\
    Specify the size of the kernel cache (in MB).

*verbose*: bool(default=False)\
    Enable verbose output. Note that this setting takes advantage of a per-process runtime setting in libsvm that, if enabled, may not work properly in a multithreaded context.

*max_iter*: int, optional (default=-1)\
    Hard limit on iterations within solver, or -1 for no limit.

*n_cores*: int, optional (default=-1)\
    The number of cpu cores to be used, or -1 for maximum.

*decision_function_shape*: ‘ovo’, default=’ovo’, Not support yet for 'ovr'\
    Only for classifier. Whether to return a one-vs-rest (‘ovr’) decision function of shape (n_samples, n_classes) as all other classifiers, or the original one-vs-one (‘ovo’) decision function of libsvm which has shape (n_samples, n_classes * (n_classes - 1) / 2).

*random_state*: int, RandomState instance or None, optional (default=None), Not support yet\
    The seed of the pseudo random number generator to use when shuffling the data. If int, random_state is the seed used by the random number generator; If RandomState instance, random_state is the random number generator; If None, the random number generator is the RandomState instance used by np.random.

### Attributes
*support_vectors_*: array-like, shape = [n_SV, n_features]\
    Support vectors.

*n_support_*: array-like, dtype=int32, shape = [n_class]\
    Number of support vectors for each class.

*dual_coef_*: array, shape = [n_class-1, n_SV]\
    Coefficients of the support vector in the decision function. For multiclass, coefficient for all 1-vs-1 classifiers. The layout of the coefficients in the multiclass case is somewhat non-trivial.

*intercept_*: array, shape = [n_class * (n_class-1) / 2]\
    Constants in decision function.



### Examples
```python
from thundersvmScikit import *
from sklearn.datasets import *
x,y = load_svmlight_file("path to training dataset")
clf = SVC()
clf.fit(x,y)

x2,y2=load_svmlight_file("path to test dataset")
clf.predict(x2)
clf.score(x2,y2)

from sklearn.model_selection import *
scores = cross_val_score(clf,x,y,cv=5)
```

### Methods
*fit(X, y)*:\
Fit the SVM model according to the given training data.

*get_params([deep])*:\
Get parameters for this estimator.

*predict(X)*:\
Perform classification on samples in X.

*score(X, y)*:\
Returns the mean accuracy on the given test data and labels.

*set_params(****params)*:\
Set the parameters of this estimator.

*decision_function(X)*:\
Return distance of the samples X to the separating hyperplane. Only for SVC, NuSVC and OneClassSVM.

