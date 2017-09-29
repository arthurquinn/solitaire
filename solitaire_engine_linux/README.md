# Solitaire Linux

To compile on a linux platform, do the following:

    sudo apt update
    sudo apt install cmake
    sudo apt install build-essential

Navigate to the root folder run the following commands:

    mkdir build
    cd build
    cmake ..
    make

Finally, you should have a `solitaire` executable inside the build folder.
