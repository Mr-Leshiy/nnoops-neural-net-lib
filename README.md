![CI](https://github.com/Mr-Leshiy/nnoops-lib/workflows/CI/badge.svg)

# Nnoops neural net library
Library for building, training neural networks.

## Build Linux
```sh
mkdir build
cd build
cmake ..
```
## Build Windows
```sh
mkdir build
cd build
cmake ..
```
## CMake Flags

|     Flag   | Usage | Description | Default value |
| :---: | :---: | :--- | :---: |
| CLANG_TIDY | -DCLANG_TIDY=[ON / OFF] | Enable clang-tidy checks during compilation | <font style="color: red">OFF</font> |
| ASAN | -DASAN=[ON / OFF] | Enable Address Sanitizer | <font style="color: red">OFF</font> |
| UBSAN | -DUBSAN=[ON / OFF] | Enable Undefined Behavior Sanitizer | <font style="color: red">OFF</font> |
| WERROR | -DWERROR=[ON / OFF] | Treat warnings as errors | <font style="color: green">ON</font> |
| TESTING | -DTESTING=[ON / OFF] | Build tests | <font style="color: green">ON</font> |
| BENCH | -DBENCH=[ON / OFF] | Build benchmarks | <font style="color: red">OFF</font> |
| NEURAL_NET_TESTING | -DNEURAL_NET_TESTING=[ON / OFF] | Build neural net tests | <font style="color: red">OFF</font> |
