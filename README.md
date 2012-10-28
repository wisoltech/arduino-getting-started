# arduino-getting-started

Getting started with Arduino on Linux and CMake. 

Read more at http://wisol.ch/w/articles/2012-10-26-arduino-setup.html

## Requirements & Compilation

This project targets the Arduino environment. It requires the Arduino SDK and CMake.

Clone the repository and make board specific settings in CMakeLists.txt.

Connect your Arduino board. Then compile and download the code with

	$ cd build
	$ cmake ..
	$ make download
