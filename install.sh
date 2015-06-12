#!/usr/bin/bash

echo "Making build directory..."
mkdir build
echo "Changing to build directory.."
cd build
echo "Running qmake.."
qmake ..
echo "Compiling and linking.."
make

echo "Making symbolic link in /usr/bin.."
if [ -f /usr/bin/tablify ]; then
	echo "/usr/bin/tablify already exists, skipping"
else
	currentdir=$(pwd)
	sudo ln -s $currentdir/tablify /usr/bin
	echo "Made symbolic link in /usr/bin to $currentdir/tablify.."
fi

if [ ! -f ~/.config/tablify/stylesheet.qss ]; then
	echo "~/.config/tablify/stylesheet.qss not found, adding empty file"
	mkdir ~/.config/tablify
	echo "" > ~/.config/tablify/stylesheet.qss
else
	echo "~/.config/tablify/stylesheet already exists, skipping.."
fi

echo "Done!"
