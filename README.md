# memory-module-loader

memory-module-loader is an implementation of a Windows loader that can load dynamic-link libraries (DLLs) directly from memory.

The loader exposed by the Windows operating system can only load modules from disk via `LoadLibrary` or `LoadLibraryEx`. However, it is entirely possible to load libraries from memory instead. This is one such implementation. This loader supports loading resources. as well.

# Authors
* Originally forked by Benjamin Dagana from https://github.com/fancycode/MemoryModule circa summer 2016.
* Updated by Ateeq Sharfuddin to support TLS.
* Updated by Jonathan Lim to support AMD64.
* Updated by Ateeq Sharfuddin to include example and documentation.

# License
Please review the file LICENSE in this repository.

# Details
1. The cloader project compiles into a static library.
1. As an example, a small sample dll is provided.
1. A sample executable is provided that links with the cloader. This executable loads sample-dll and calls a function.

## Building from source
Open cloader.sln in Visual Studio 2019 and build the solution. The output will be placed under the `bin` directory.

## Functions
### LoadModuleFromMemory
Similar to `LoadLibrary`, but loads the module from memory instead.
### _GetProcAddress
Similar to `GetProcAddress`, but usable only for modules loaded by `LoadModuleFromMemory`.
### FreeLibraryResources
Similar to `FreeLibrary`, but use only for modules loaded by `LoadModuleFromMemory`.
### _FindResource
Similar to `FindResource`, but use only to find resources in modules loaded by `LoadModuleFromMemory`.
### _LoadResource
Similar to `LoadResource`, but use only to load resources in modules loaded by `LoadModuleFromMemory`. In this case, you do not need to call `LockResource`: This function simply returns you the address of the resource instead of an HGLOBAL object.
### _SizeofResource
Similar to SizeofResource, but use only for resources in modules loaded by `LoadModuleFromMemory`.

## Layout
```
memory-module-loader
|   cloader.sln
|   LICENSE
|   README.md
|
\---src
    +---cloader
    |       cloader.vcxproj
    |       cloader.vcxproj.filters
    |       common.h
    |       moduleloader.c
    |       moduleloader.h
    |
    +---sample-dll
    |       common.h
    |       dllmain.cpp
    |       sample-dll.c
    |       sample-dll.def
    |       sample-dll.vcxproj
    |       sample-dll.vcxproj.filters
    |
    \---sample-exe
            sample-exe.c
            sample-exe.vcxproj
            sample-exe.vcxproj.filters
```
