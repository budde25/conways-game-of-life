# Game of Life

 [![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)  

This is an C implementation of the classic Conways Game of life. This was all programmed in C and features displaying a variable screen sized game of life. It supports creating your own initial states by adding files to the patterns folder. 

## Getting started

The app requires nucurses to compile. Alternativly you can download the precomiled binary and run it.

### Compilation
`gcc life.c -o life -lncurses` to compile output file will be named life.

### Usage
`./life -list` will list all pattern files including user created ones.  
`./life <pattern>` will start the program with the provided pattern.  

### Creating Patterns
To create a pattern simply create a new file in the patterns directory. Then begin listing coordinates one per line comma seperated for your initial condition. The coordonate 0,0 will be centered in the screen so make your coordinates relative to it.

## Created With
* [NCurses](https://invisible-island.net/ncurses/announce.html#h2-overview) - A C library that allows creation of Tuis.

## Author
Ethan Budd

## Acknowlagements
* [Conways Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)
