Welcome to __CNN-B__, a repository for the C++ team project by _Zijun Cui_, _Zhenhua Tian_ and _Lemeng Wang_.


## Summary


This is a Caffe-based Object Classification project. Three convolutional neural networks--CaffeNet, AlexNet, and GoogleNet--have been used to study the relationship between the accuracy of classification and the size of an object. The classifications have been performed on images of 6 different objects: a trash bin, a basketball, a screw, a pen, a printer, and a monitor. Each object is taken with 10 difference scales. The result is that the smaller an object is in a photo, the lower probability the correct description has to lie on top of the prediction results. Qt interface has been integrated into Caffe, fulfilling functions of image input, network customization, and prediction output.


Our own images can be found in the folder `~/examples/Images`


3 _ipynb_ files have been created for the classification computation:


```
~/examples/Classification_CaffeNet.ipynb
~/examples/Classification_AlexNet.ipynb
~/examples/Classification_GoogleNet.ipynb
```


Code for Qt interface can be found in the folder `~/qt-interface/CNN-GUI`


__Our test result:__


![Image 1]
(Picture1.png)


The _x_-axis stands for the scale. 1 is the biggest size and 10 is the smallest one.


The _y_-axis stands for the probability. The biggest probability is linearly curved to be 1. For each _x_, the average probabilities of 6 objects have been calculated.


From the chart it is obvious that the probability of the correct classifications decreases as the sizes of the objects get smaller.


Detailed instructions for our codes are as follows.


##Installation instructions


###Dependencies


CUDA, BLAS, Boost >= 1.55, protobuf, glog, gflags, hdf5


According to CCV staff, Caffe requires Nvidia GPUs of CUDA compute capability > 3.0, to which our CCV accounts do not have access.


###CNN-B Compilation


####On your own machines


Install caffe:


_http://caffe.berkeleyvision.org/installation.html_


Install Qt:


_https://www.qt.io/_


####On Center for Computation and Visualization-Brown University


Request 2 GPUs using the command `"interact -q gpu -n 2 -t 1:00:00"`.


Load modules _opencv, boost, protobuf, cuda, cudnn, atlas, hdf5_.


Run _“make all”_ and receive a failure message complaining about gflags.


Download and compile _gflags_ and receive another failure message.


Try another way: directly loading the _Caffe_ module.


Try training networks and receive an error message _“no CUDA-capable device detected”_.


Reach the conclusion that you can neither train networks nor test networks due to the aforementioned CUDA compute capability problem.


##Qt interface


###Objective


The CNN Viewer lets users to choose a dataset and a defined architecture to accomplish training a convolutional neural network with chosen dataset. After training, user can upload an image to do object classification. The interface will pop up the top 5 testing possibilities and their corresponding labels.


Qt is currently prevented from compiling Caffe by a linking error probably because the downloadable gflags/gflags.h library is not compatible with Qt. As a result, this project is a demo of the ideal input and output.


###Instruction


Run Qt creator:


```
cd qt-interface/Tools/QtCreator/bin/
./qtcreator
```


In Qt Creator:


```
File -> Open File or Project -> ~/CNN_GUI/CNN_GUI.pro
Build Project
Run
```


Once you succeed in running our CNN-GUI


```
File -> Open -> ~/CNN_GUI/basketball.jpg (It’s adjustable in View Menu)
Test -> ImageNet -> CaffeNet or AlexNet or GoogleNet 
```


After the test, a result window will automatically pop up.


__Error Handling__:


You cannot use  _View_  and _Test_ Menu if you are not providing an image.


##CNN Training Examples


These examples are accomplished on our own machine instead of on CCV


We accomplished LeNet training and Siamese network training with MNIST dataset both on GPU and CPU 


GPU: GeForce GT 750M (CUDA Compute Capability = 3.0)


CPU: Intel Core i5-3230M Processor (up to 3.20 GHz)


We tried CaffeNet training with ImageNet dataset but failed due to the aforementioned CUDA compute capability problem with CCV.


###Training LeNet on MNIST with Caffe


Follow our instructions in _CNN-B/examples/MNIST_


Training time comparison:


```
GPU: 6 mins 37 seconds
CPU: 16 mins 47 seconds
```
###Siamese Network Training with Caffe


Follow our instructions in _CNN-B/examples/siamese_


This example builds on the __Training LeNet on MNIST with Caffe__. 


Training time comparison:


```
GPU: 4 mins 50 seconds 
CPU: 39 mins 2 seconds
```


###Brewing ImageNet


Follow our instructions in _CNN-B/examples/imagenet_


Downloaded the ImageNet training data and validation data


_http://image-net.org/download-images_


To download all origin images, 138GB is needed.


##CNN Testing Examples


These examples are accomplished on our own machine instead of on CCV


###Object Classification with Python Interface
Assume you have compiled _caffe_ and _pycaffe_ successfully. 


__To run _.ipynb_ files with jupyter notebook__


```
cd $CNN-B/examples  jupyter notebook
```


Open jupyter notebook with browser. Then you can run _Classification_XXXNet.ipynb_ files to do object classification. 


__To run _.ipynb_files with command line__


```
cd $CNN-B/examples  jupyter nbconvert --to notebook --execute Classification_XXXNet.ipynb
```


To test your image, simply change the path to where your image is located


```
image = caffe.io.load_image(caffe_root + 'examples/images/basketball/5.JPG')
```


When computation finish, you will get top 5 possible classifications. Following is an output example from Classification_CaffeNet.ipynb


```
probabilities:
[(0.90265167, 'n02802426 basketball'),
 (0.0089489967, 'n04277352 spindle'),
 (0.0064962064, 'n04254680 soccer ball'),
 (0.0051468485, 'n04026417 purse'),
 (0.0050535896, 'n03249569 drum, membranophone, tympan')]
```

