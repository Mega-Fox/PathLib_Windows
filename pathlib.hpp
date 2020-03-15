/*MIT License

Copyright (c) 2020 by MegaFox

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#ifndef PATHLIB_HPP
#define PATHLIB_HPP

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_PATHLIB
#define PATHLIB __declspec(dllexport)
#else
#define PATHLIB __declspec(dllimport)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

PATHLIB wstring __cdecl pathLibLicense();
PATHLIB int __cdecl pathLibRegisterSystem(wstring curdir);
PATHLIB int __cdecl pathLibUnregisterSystem(wstring curdir);
PATHLIB int __cdecl pathLibRegisterUser(wstring curdir);
PATHLIB int __cdecl pathLibUnregisterUser(wstring curdir);
PATHLIB int __cdecl pathLibRegisterSystemComp(wchar_t *curdir);
PATHLIB int __cdecl pathLibUnregisterSystemComp(wchar_t *curdir);
PATHLIB int __cdecl pathLibRegisterUserComp(wchar_t *curdir);
PATHLIB int __cdecl pathLibUnregisterUserComp(wchar_t *curdir);

#ifdef __cplusplus
}
#endif



#endif  // PATHLIB_HPP