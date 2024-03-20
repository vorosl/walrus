# WALRUS: WebAssembly Lightweight RUntime

[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Actions Status](https://github.com/Samsung/walrus/actions/workflows/actions.yml/badge.svg)](https://github.com/Samsung/walrus/actions)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/26942/badge.svg)](https://scan.coverity.com/projects/samsung-walrus)

This project aims to provide a lightweight WebAssembly runtime engine. It now fully supports WebAssembly specs with an simple interpreter, but we plan to optimize interpreting as well as adopting JIT compiler for better performance.

## Cloning

Clone as normal, but don't forget to get the submodules as well:

```console
$ git clone --recursive https://github.com/Samsung/walrus
$ cd walrus
$ git submodule update --init
```

This will fetch the testsuite and gtest repos, which are needed for some tests.

## Building using CMake

You'll need [CMake](https://cmake.org). You can then run CMake, the normal way:

```console
$ cmake -H. -Bout/release/x64 -DWALRUS_ARCH=x64 -DWALRUS_HOST=linux -DWALRUS_MODE=release -DWALRUS_OUTPUT=shell -GNinja
$ ninja -Cout/release/x64
$ ./out/release/x64/walrus test.wasm // run walrus executable
```

This will produce build files using CMake's default build generator. Read the
CMake documentation for more information.

## Perf

You'll need [Perf](https://perf.wiki.kernel.org/index.php/Main_Page).

0. To compile with perf support, use `-DWALRUS_JITPERF=1`

1. Run Walrus with: `sudo perf record -k 1 walrus --jit --perf WALRUS_PARAMETERS`

    It'll generates 2 files:
   - perf.data - it is generated by perf
   - jit-XXXXXX.dump - JITDump file, XXXXXX is the PID of process, and it contains details of jitted functions

2. After that you should chown these 2 files
   
3. Inject JITDump file into `perf.data` with `perf inject --jit -i perf.data -o perf.data.jitted` 
   
    It'll generate many shared object files, and `perf.data.jitted`

4. View the report with `perf report -i perf.data.jitted`