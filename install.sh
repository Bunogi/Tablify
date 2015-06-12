#!/usr/bin/bash

echo "Making build directory..."
mkdir build
echo "Changing to build directory.."
cd build
echo "Running qmake.."
qmake ..
echo "Compiling and linking.."
make

currentdir=$(pwd)
echo "Making symbolic link in /usr/bin to $currentdir/tablify.."
sudo ln -s $currentdir/tablify /usr/bin
echo "Making config directory.."
mkdir ~/.config/tablify
echo "Making empty stylesheet in ~/.config/stylesheet.qss"
echo "" > ~/.config/tablify/stylesheet.qss
echo "Done!"
