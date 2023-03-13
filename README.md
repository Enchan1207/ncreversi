# ncreversi

## Overview

Simple reversi game with ncurses UI.

<img style="max-height: 300px;" src="https://user-images.githubusercontent.com/51850597/224651108-eb8854ba-6a39-49c3-94b9-1e75014615e3.png">

Arrow key to move cursor, and space key to put stone.

<img style="max-height: 300px;" src="https://user-images.githubusercontent.com/51850597/224651102-a581b3ab-e98e-40aa-8cee-a143919ccc64.png">

Computer decides place to put stone automatically.

<img style="max-height: 300px;" src="https://user-images.githubusercontent.com/51850597/224651112-fcf0ff8f-420a-4c61-bf6b-fc71d9f1ced3.png">

When the game is over, the result and winner will be displayed.

<img style="max-height: 300px;" src="https://user-images.githubusercontent.com/51850597/224651114-4c1ac600-28b7-4910-8fe7-e9c12828d09c.png">

## Installation

**NOTE:** You need CMake and ncurses to build this game.

After clone this repository, please execute commands shown below. The built executables will be created at `./build/src/ncreversi`.

```
mkdir build
cd build
cmake ..
cmake --build .
```

## Dependencies

Main logic of this game is based on [Enchan1207/flipstone](https://github.com/Enchan1207/flipstone), the core library of reversi written in C++.
If you find logic-related glitches or bugs, please contact to this repository.

## License

This repository is published under [MIT License](LICENSE).
