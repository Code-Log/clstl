# CLSTL

## Description

This is the CodeLog Standard Template Library or CLSTL.

## Contributing

See [Contributing](CONTRIBUTING.md) for details on how to contribute to the project.

## Building

### Prerequisites

* CMake, Clang (Linux only)

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

#### Ubuntu / Debian

1. Add the CodeLog PPA to your system.

```bash
sudo add-apt-repository ppa:codeloginc/public
```

2. Update your package lists.

```bash
sudo apt-get update
```

3. Install the package.

```bash
sudo apt-get install libclstl-dev
```

#### Other distros

1. Build the project as described in 'Building'
2. In the build directory use make to install the library.

```bash
sudo make install
```
