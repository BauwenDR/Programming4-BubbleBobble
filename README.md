# Programming 4 - Bubble Bobble

[![Build Status](https://github.com/BauwenDR/Programming4-BubbleBobble/actions/workflows/cmake.yml/badge.svg)](https://github.com/BauwenDR/Programming4-BubbleBobble/actions/workflows/cmake.yml)
[![Build Status](https://github.com/BauwenDR/Programming4-BubbleBobble/actions/workflows/emscripten.yml/badge.svg)](https://github.com/BauwenDR/Programming4-BubbleBobble/actions/workflows/emscripten.yml)

This repository contains my Programming 4 Demo and Exam assignments.
The assignment was to recreate the arcade game 'Bubble Bobble' using Minigin as a template.
Throughout the course we were provided programming patters and advice for transforming the starting project into a propper game engine.

The Demo can be viewed at: [https://bauwendr.github.io/Programming4-BubbleBobble/](https://bauwendr.github.io/Programming4-BubbleBobble/)

## Windows version (Visual Studio)
- Open the root folder in Visual Studio 2026; this will be recognized as a cmake project.

## Linux/ macOS (And non Visual Studio Windows)
- Install CMake 
- Install CMake and CMake Tools extensions in Visual Code
- Open the root folder in Visual Code,  this will be recognized as a cmake project.

## Emscripten (web) version
### On Windows
For installing all the needed tools on Windows I recommend using [Chocolatey](https://chocolatey.org/). You can then run the following in a terminal to install what is needed:
```shell
choco install -y cmake
choco install -y emscripten
choco install -y ninja
choco install -y python
```

In a terminal, navigate to the root folder. Run this: 
```shell
mkdir build_web
cd build_web
emcmake cmake ..
emmake ninja
```

To be able to see the webpage you can start a python webserver in the build_web folder
```shell
python -m http.server
```

Then browse to http://localhost:8000 and you're good to go.

### On OSX
On Mac you can use homebrew

```shell
brew install cmake
brew install emscripten
brew install python
```

In a terminal on OSX, navigate to the root folder. Run this: 
```shell
mkdir build_web
cd build_web
emcmake cmake .. -DCMAKE_OSX_ARCHITECTURES=""
emmake make
```

To be able to see the webpage you can start a python webserver in the build_web folder
```shell
python3 -m http.server
```

Then browse to http://localhost:8000 and you're good to go.
