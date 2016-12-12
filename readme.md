Welcome to __CNN-B__, a repository for the C++ team project by _Zijun Cui_, _Zhenhua Tian_ and _Lemeng Wang_.


This is a Caffe-based Object Classification project. Three convolutional neural networks--CaffeNet, AlexNet, and GoogleNet--have been used to study the relationship between the accuracy of classification and the size of an object. The classifications have been performed on images of 6 different objects: a trash bin, a basketball, a screw, a pen, a printer, and a monitor. Each object is taken with 10 difference scales. The result is that the smaller an object is in a photo, the lower probability the correct description has to lie on top of the prediction results. Qt interface has been integrated into Caffe, fulfilling functions of image input, network customization, and prediction output.


Our own images can be found in the folder `~/examples/Images`


3 _ipynb_ files have been created for the classification computation:


```
~/examples/Classification_CaffeNet.ipynb


~/examples/Classification_AlexNet.ipynb


~/examples/Classification_GoogleNet.ipynb
```


 Code for Qt interface can be found in the folder `~/qt-interface/Classification-GUI`






Detailed instructions are shown as follows.






#Installation instructions


##Dependencies


CUDA is required for GPU mode


BLAS via ATLAS, MKL, or OpenBLAS


Boost >= 1.55


protobuf, glog, gflags, hdf5


##Compilation


###On your own machines


####Install Caffe


_Git clone_ the repository to your own computer and run _“make all”_


####Install Qt interface


Git clone the repository to your own computer and run:


_cd Qt/Tools/QtCreator/bin/_


_./qtcreator_


In Qt Creator, go to _File_ -> _Open File or Project_ and choose _~/CNN\_GUI/CNN\_GUI.pro_


Click _Build Project_ and _Run_ in the left bottom


###On CCV


Request 2 GPUs using the command _"interact -q gpu -n 2 -t 1:00:00"_.


Load modules _opencv, boost, protobuf, cuda, cudnn, atlas, hdf5_.


Run _“make all”_ and receive a failure message complaining about gflags.


Download and compile _gflags_ and receive another failure message.


Try another way: directly load the _Caffe_ module


According to CCV staff, Caffe requires Nvidia GPUs of CUDA compute capability > 3.0, to which our CCV accounts do not have access.


no CUDA-capable device detected



#Qt interface


##Objective


The CNN Viewer lets users to choose a dataset and a training architecture to test it, and pop up the top 5 testing possibilities and their corresponding labels in the dataset.


Qt is currently prevented from compiling Caffe by a linking error probably because the downloadable gflags/gflags.h library is not compatible with Qt. As a result, this project is a demo of the ideal input and output.


##Instruction


In the CNN_GUI user interface, go to _File_ -> _Open_ and choose _~/CNN\_GUI/basketball.jpg_ (It’s adjustable in _View_ Menu)


Go to _Test_ -> _ImageNet_ -> _CaffeNet_ or _AlexNet_ or _GoogleNet_ and view the testing result


Note that:


The _View_  and _Test_ Menu is disabled until an image is opened.


_Test_ -> _MNIST_ is not available for the given image. Please do not abuse.





##Training Examples


We accomplished LeNet training and Siamese network training with MNIST dataset both on GPU and CPU 


GPU: GeForce GT 750M


CPU: CORE i5 3230


We tried CaffeNet training with ImageNet dataset but failed due to CCV


###Training LeNet on MNIST with Caffe


Follow our instructions in CNN-B/caffe/examples/MNIST


Training time compare:


GPU: 6 mins 37 seconds


CPU: 16 mins 47 seconds
###Siamese Network Training with Caffe


Follow our instructions in CNN-B/caffe/examples/siamese


This example builds on the __Training LeNet on MNIST with Caffe__. 


GPU: 4 mins 50 seconds 


CPU: 39 mins 2 seconds


###Brewing ImageNet


Follow our instructions in CNN-B/caffe/examples/imagenet


Downloaded the ImageNet training data and validation data


_http://image-net.org/download-images_


To download all origin images, 138GB is needed.


##Testing Examples
###Object Classification with Python Interface
Assume you have compiled _caffe_ and _pycaffe_ successfully. 
__To run _.ipynb_ files with jupyter notebook__


```
cd $CNN-B/examples  jupyter notebook
```


After you open jupyter notebook with browser, you can run _Classification_XXXNet.ipynb_ files we provided to do object classification. 


To test your image, simply change the path to where your image located


```
image = caffe.io.load_image(caffe_root + 'examples/images/basketball/5.JPG')
```


__To run _.ipynb_files with command line__


```
cd $CNN-B/examples  jupyter nbconvert --to notebook --execute Classification_XXXNet.ipynb
```


After computation, you will get top 5 possible predictions. Following is an output example from Classification_CaffeNet.ipynb


```
probabilities:
[(0.90265167, 'n02802426 basketball'),
 (0.0089489967, 'n04277352 spindle'),
 (0.0064962064, 'n04254680 soccer ball'),
 (0.0051468485, 'n04026417 purse'),
 (0.0050535896, 'n03249569 drum, membranophone, tympan')]
```



