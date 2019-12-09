# CLSTL

## Description

This is the CodeLog Standard Template Library or CLSTL.

## Contributing

See [Contributing](CONTRIBUTING.md) for details on how to contribute to the project.

## Building

### Windows

* On Windows, type `cmake . -G <your-generator-here>` to build the CMake project and then import it into your favourite IDE.

### Linux

* On Linux, run either of the build scripts, cd into the directory generated and type `make` to compile the project.

## Installing

### Windows

1. Compile the project
2. Copy everything inside the 'include' folder and the compiled binary to your desired project.

### Linux

#### Arch Linux

* On Arch just install the AUR package 'libclstl'

#### Other distros

1. Build the project as described in 'Building'
2. In the build directory use `sudo make install` to install the library.
