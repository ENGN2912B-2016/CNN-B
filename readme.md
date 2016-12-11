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







__Qt__


__Overview__


Qt is a C++ toolkit for cross-platform application development and is downloadable from qt.io/download/. This project uses Qt open source version 5.7.0. It is available under GPL and LGPLv3 licenses.


__Compilation__


On your own machines:


Git clone the repository to your own computer and run:


_cd Qt/Tools/QtCreator/bin/_


./qtcreator


In Qt Creator, go to _File_ -> _Open File or Project_ and choose _~/CNN\_GUI/CNN\_GUI.pro_


Click _Build Project_ and _Run_ in the left bottom


__Objective__


The CNN Viewer shows how to choose, display, save and adjust an image. Then it let users to choose a dataset and a training architecture to test it, and pop up the top 5 testing possibilities and their corresponding labels in the dataset.


Qt is currently unable to compile Caffe probably because the downloadable gflags/gflags.h library is not compatible with Qt. This project is a demo of the ideal input and output.


__Instruction__


In the CNN_GUI user interface, go to _File_ -> _Open_ and choose _~/CNN\_GUI/basketball.jpg


Go to _Test_ -> _ImageNet_ -> _CaffeNet_ or _AlexNet_ or _GoogleNet_ and view the testing result (top 5 possibilities and the corresponding label)


Note that:


The _View_  and _Test_ Menu is disabled until an image is opened.


_Test_ -> _MNIST_ is not available for the given image.











__Train Examples__




__Training LeNet on MNIST with Caffe__




assume that your Caffe installation is located at CAFFE_ROOT


first download and convert the data format from the MNIST website


To do this, simply run the following commands:


_cd $CAFFE_ROOT_

_./data/mnist/get_mnist.sh_

_./examples/mnist/create_mnist.sh_


If it complains that _wget_ or _gunzip_ are not installed, you need to install them respectively. 


After running the script there should be two datasets _mnist_train_lmdb_ and _mnist_test_lmdb_.


defined the layers in  _$CAFFE_ROOT/examples/mnist/lenet_train_test.prototxt_


defined the solver in _$CAFFE_ROOT/examples/mnist/lenet_solver.prototxt_


To train the model, simply run _train_lenet.sh_, or the following command directly:


_cd $CAFFE_ROOT_

_./examples/mnist/train_lenet.sh_

And after a few minutes, you are done!


_I1203 solver.cpp:84] Testing net_

_I1203 solver.cpp:111] Test score #0: 0.9897_

_I1203 solver.cpp:111] Test score #1: 0.0324599_


_I1203 solver.cpp:126] Snapshotting to lenet_iter_10000_

_I1203 solver.cpp:133] Snapshotting solver state to lenet_iter_10000.solverstate_

_I1203 solver.cpp:78] Optimization Done_


The final model, stored as a binary protobuf file, is stored at


_lenet_iter_10000_


All the training was carried out on the GPU. In fact, if you would like to do training on CPU, you can simply change one line in _lenet_solver.prototxt_:


_# solver mode: CPU or GPU_

_solver_mode: CPU_


MNIST is a small dataset, so training with GPU does not really introduce too much benefit due to communication overheads. On larger datasets with more complex models, such as ImageNet, the computation speed difference will be more significant.




__Siamese Network Training with Caffe__


This example shows how you can use weight sharing and a contrastive loss function to learn a model using a siamese network in Caffe.


This example builds on the __Training LeNet on MNIST with Caffe__. 


The guide specifies all paths and assumes all commands are executed from the root caffe directory


First download and convert the data from the MNIST website. To do this, simply run the following commands:


_./data/mnist/get_mnist.sh_

_./examples/siamese/create_mnist_siamese.sh_


After running the script there should be two datasets, 


_./examples/siamese/mnist_siamese_train_leveldb_


_./examples/siamese/mnist_siamese_test_leveldb_


Define the model that we want to train using the siamese network. Use the convolutional net defined in _./examples/siamese/mnist_siamese.prototxt_. This model is almost exactly the same as the LeNet model, the only difference is that we have replaced the top layers that produced probabilities over the 10 digit classes with a linear “feature” layer that produces a 2 dimensional vector.


Define the siamese network used for training. The resulting network is defined in _./examples/siamese/mnist_siamese_train_test.prototxt_


Nothing special needs to be done to the solver besides pointing it at the correct model file. The solver is defined in _./examples/siamese/mnist_siamese_solver.prototxt_


To train the model, simply run 


_./examples/siamese/train_mnist_siamese.sh_


Draw the model and siamese networks by running the following commands that draw the DAGs defined in the .prototxt files:


./python/draw_net.py \

    ./examples/siamese/mnist_siamese.prototxt \

    ./examples/siamese/mnist_siamese.png

./python/draw_net.py \

    ./examples/siamese/mnist_siamese_train_test.prototxt \

    ./examples/siamese/mnist_siamese_train_test.png





__Brewing ImageNet__


The guide specifies all paths and assumes all commands are executed from the root caffe directory.
By “ImageNet” we here mean the ILSVRC12 challenge, but you can easily train on the whole of ImageNet as well, just with more disk space, and a little longer training time.
We assume that you already have downloaded the ImageNet training data and validation data


Download: http://image-net.org/download-images


and they are stored on your disk like:


_/path/to/imagenet/train/n01440764/n01440764_10026.JPEG_

_/path/to/imagenet/val/ILSVRC2012_val_00000001.JPEG_




Prepare some auxiliary data for training. 


This data can be downloaded by:


_./data/ilsvrc12/get_ilsvrc_aux.sh_


The model requires us to subtract the image mean from each image, so we have to compute the mean, the mean computation can be carried out as


_./examples/imagenet/make_imagenet_mean.sh_


which will make _data/ilsvrc12/imagenet_mean.binaryproto_


To train


_./build/tools/caffe train --solver=models/bvlc_reference_caffenet/solver.prototxt_













Jupyter Notebook Examples
Learn Lenet
Siamese
Classification with CaffeNet
Classification with AlexNet
Classification with GooleNet





/*
On CCV:
You should not trifle with me on CCV, unless you want to learn how mischievous and fastidious I could be.


You can allocate 2 high-performance GPUs using the command "interact -q gpu -n 2 -t 1:00:00", but that is far from enough to please me. I will not meet anybody unless they bring me a gift of an Nvidia GPU with a CUDA compute capability greater than 3.0.


You may try your luck to compile me, but I shall warn you that the problem with gflags can never be tackled. Gflags can neither be loaded nor installed because of the low level of your CCV account. How much fun that could be!


I know you would also think of using the Caffe module with CPU only. I can assure you, dear, that you can never break the shackle of "no CUDA-capable device detected". Besides, I have also disabled Cublas handle and Curand generator as a failsafe method to prevent you from ever succeed!
*/

