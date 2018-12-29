# escape-the-maze
Project for CS3520

[![Build Status](https://travis-ci.com/jackfrys/escape-the-maze.svg?branch=master)](https://travis-ci.com/jackfrys/escape-the-maze)

# Building and Running
Be sure the dependencies are installed: `sdl2`, `sdl2_image`, and `sdl2_mixer`. They can be easily installed via Homebrew on macOS:

```
$ brew install sdl2
$ brew install sdl2_image
$ brew install sdl2_mixer
```

Then compile and run the project:
```
$ make main
$ ./main
```

## Tests
Be sure the `CxxTest` library is installed. It can be easily installed by running the `install_cxx` script:
```
$ ./install_cxx
```

Then compile the run the tests:
```
$ make test
$ ./test
```
