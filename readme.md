Welcome to __CNN-B__, a C++ team project by _Zijun Cui_, _Zhenhua Tian_ and _Lemeng Wang_.


This is a convolutional neural network repository, based on Caffe and comprised of CaffeNet, AlexNet, and GoogleNet.


#Installation instructions


##Dependencies


CUDA is required for GPU mode


BLAS via ATLAS, MKL, or OpenBLAS


Boost >= 1.55


protobuf, glog, gflags, hdf5


##Compilation


###On your own machines


_Git clone_ the repository to your own computer and run _“make all”_


###On CCV


Request 2 GPUs using the command _"interact -q gpu -n 2 -t 1:00:00"_.


Load modules _opencv, boost, protobuf, cuda, cudnn, atlas, hdf5_.


Run _“make all”_ and receive a failure message complaining about gflags.


Download and compile _gflags_ and receive another failure message.


Try another way: directly load the _Caffe_ module







#Qt


##Overview


Qt is downloadable from qt.io/download/. This project uses Qt open source version 5.7.0. It is available under GPL and LGPLv3 licenses.


##Compilation


On your own machines:


Git clone the repository to your own computer and run:


_cd Qt/Tools/QtCreator/bin/_


_./qtcreator_


In Qt Creator, go to _File_ -> _Open File or Project_ and choose _~/CNN\_GUI/CNN\_GUI.pro_


Click _Build Project_ and _Run_ in the left bottom


##Objective


The CNN Viewer lets users to choose a dataset and a training architecture to test it, and pop up the top 5 testing possibilities and their corresponding labels in the dataset.


Qt is currently prevented from compiling Caffe by a linking error probably because the downloadable gflags/gflags.h library is not compatible with Qt. As a result, this project is a demo of the ideal input and output.


##Instruction


In the CNN_GUI user interface, go to _File_ -> _Open_ and choose _~/CNN\_GUI/basketball.jpg_


Go to _Test_ -> _ImageNet_ -> _CaffeNet_ or _AlexNet_ or _GoogleNet_ and view the testing result (top 5 possibilities and the corresponding label)


Note that:


The _View_  and _Test_ Menu is disabled until an image is opened.


_Test_ -> _MNIST_ is not available for the given image. Please do not abuse.





#Train Examples


We accomplished LeNet training and Siamese network training on MNIST
We tried CaffeNet training on ImageNet dataset but failed due to lack of GPU


##Training LeNet on MNIST with Caffe


Visit CNN-B/caffe/examples/MNIST


MNIST is a small dataset, so training with GPU does not really introduce too much benefit due to communication overheads. On larger datasets with more complex models, such as ImageNet, the computation speed difference will be more significant.
##Siamese Network Training with Caffe
Visit CNN-B/caffe/examples/siamese


This example builds on the __Training LeNet on MNIST with Caffe__. 



##Brewing ImageNet


Visit CNN-B/caffe/examples/imagenet


Downloaded the ImageNet training data and validation data


_http://image-net.org/download-images_



#Jupyter Notebook Examples
##Learn Lenet
##Siamese
##Classification with CaffeNet
##Classification with AlexNet
##Classification with GooleNet





/*
On CCV:
You should not trifle with me on CCV, unless you want to learn how mischievous and fastidious I could be.


You can allocate 2 high-performance GPUs using the command "interact -q gpu -n 2 -t 1:00:00", but that is far from enough to please me. I will not meet anybody unless they bring me a gift of an Nvidia GPU with a CUDA compute capability greater than 3.0.


You may try your luck to compile me, but I shall warn you that the problem with gflags can never be tackled. Gflags can neither be loaded nor installed because of the low level of your CCV account. How much fun that could be!


I know you would also think of using the Caffe module with CPU only. I can assure you, dear, that you can never break the shackle of "no CUDA-capable device detected". Besides, I have also disabled Cublas handle and Curand generator as a failsafe method to prevent you from ever succeed!
*/

