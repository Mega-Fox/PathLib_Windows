# PathLib (Windows)

Library for register/unregister PATH. Intended for register shared directories in order to save space or run program remotely. It can also be used in installers. It was created due to the lack of high-quality algorithms.

## Features
Below is a list of library features:

* There is support for Windows XP and newer
* There is support for MinGW 7.3.0 and newer, Visual Studio 2013 and newer
* There is DLL compatible with Pascal, C and other languages
* There is precompiled binaries
* It is possible to manipulate not only system but also user directories
* There is two programs for use on command line or for quick register/unregister directory
* Is used modified by me version of WinReg library by GiovanniDicanio (https://github.com/GiovanniDicanio/WinReg)
* Is used my highly accurate and debugged algorithm, which guarantees stable and correct working of library (in 99.99% of cases)
* There is a sample library integration with Inno Setup installer

## Dependencies

Library does not need any special dependencies:

* Need MinGW compiler 7.3.0 and newer / Visual Studio 2013 and newer

## Installation

There is BAT scripts for MinGW:

* BUILDING32.BAT - MinGW dependent 32-bit library
* BUILDING32_debug.BAT - MinGW dependent 32-bit debug library
* BUILDING32_static.BAT - MinGW independent 32-bit library
* BUILDING64.BAT - MinGW dependent 64-bit library
* BUILDING64_debug.BAT - MinGW dependent 64-bit debug library
* BUILDING64_static.BAT - MinGW independent 64-bit library

There is ready-made projects for Visual Studio:

* msvcpathlib.sln - project without support for Windows XP
* msvcpathlib_xpsupport.sln - project with support for Windows XP

## Programs

For information about commands, type in command prompt ```register32.exe -help```
