# Programming 4 - Bubble Bobble
## Bauwen De Ron
Github: https://github.com/BauwenDR/Programming4-BubbleBobble

[![Build Status](https://github.com/BauwenDR/Programming4-BubbleBobble/actions/workflows/cmake.yml/badge.svg)](https://github.com/BauwenDR/Programming4-BubbleBobble/actions/workflows/cmake.yml)
[![Build Status](https://github.com/BauwenDR/Programming4-BubbleBobble/actions/workflows/emscripten.yml/badge.svg)](https://github.com/BauwenDR/Programming4-BubbleBobble/actions/workflows/emscripten.yml)

This repository contains my Programming 4 Demo and Exam assignments.
The assignment was to recreate the arcade game 'Bubble Bobble' using Minigin as a template.
Throughout the course we were provided programming patters and advice for transforming the starting project into a propper game engine.

## Controls
### Keyboard
#### Player 1
**A/D**: Walk left/ right
**Z**: Jump
**X**: Attack

#### Player 2
**LEFT/RIGHT**: Walk left/ right
**UP**: Jump
**DOWN**: Attack

### Gamepad
**DPAD-LEFT/DPAD-RIGHT**: Walk left/ right
**A**: Jump
**X**: Attack

## Specifics/ Design choices
- Sound system: SDL3 (core) - On a separate thread through an Event Queue
- Service locator for audio
- Level format: JSON
- State pattern: Bubble component (Shot, floating, static, wind current)
- High scores: Sqlite (not available for webbuilds)
- Command pattern for player and ui input
- Event Queue for:
  - New stage ready
  - High score changed
  - An enemy has died
  - A player has died
- Observer pattern for:
  - Collision Handling (on enter, stay & exit)
  - On jump
  - On attack
  - On object destroyed
  - ...
- GameLoop pattern (no fixed time)
- Component based game engine

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
make
```

In order to run the application simply use the following command.
Because threading required SharedArrayBuffer, and browsers have locked those behind security policies just running any http server will not suffice.
```shell
emrun index.html
```

To be more specific. These headers need to be added to the requests. (Using nginx config as an example)
GitHub pages do not allow these headers to be set (or any headers to be modified for any matter). So the GitHub page is currently broken.
I currently use a hacky workaround, this is not guaranteed to work (tested with http-server js executable; and it worked there) no guarantees.
```nginx
add_header Cross-Origin-Opener-Policy "same-origin" always;
add_header Cross-Origin-Embedder-Policy "require-corp" always;
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
