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

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "WinReg.hpp"
#include "findci.hpp"
#ifndef BUILDING_STATIC
#include "pathlib.hpp"
#endif
#include <iostream>
#include <vector>

using namespace std;
using namespace winreg;

void replaceAllW(wstring& str, wstring& from, wstring& to)
{
    int indexreplace;
	bool checker = true;
		
	while(checker)
	{
		indexreplace = findci(str, from);
		if(indexreplace != -1)
		{
			str.replace(indexreplace, from.length(), to);
		}
		else
		{
			checker = false;
			break;
		}
	}
}







wstring __cdecl pathLibLicense()
{
	wstring license = L"MIT License"
		L"\n"
		L"\nCopyright (c) 2020 by MegaFox"
		L"\n"
		L"\nPermission is hereby granted, free of charge, to any person obtaining a copy"
		L"\nof this software and associated documentation files (the \"Software\"), to deal"
		L"\nin the Software without restriction, including without limitation the rights"
		L"\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell"
		L"\ncopies of the Software, and to permit persons to whom the Software is"
		L"\nfurnished to do so, subject to the following conditions:"
		L"\n"
		L"\nThe above copyright notice and this permission notice shall be included in all"
		L"\ncopies or substantial portions of the Software."
		L"\n"
		L"\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR"
		L"\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,"
		L"\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE"
		L"\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER"
		L"\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,"
		L"\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE"
		L"\nSOFTWARE.\n";
	return license;
}

int pathLibRegisterCore(wstring curdir, int type)
{
	int result = 2;
	
	if(curdir == L"")
	{
		return 1;
	}
	
	if(curdir.back() == L'\0')
	{
		curdir.pop_back();
	}
	wstring comp = L";" + curdir + L";";
	wstring curdirslash;
	wstring compslash;
	if(curdir.back() == L'\\')
	{
		curdirslash = curdir;
		curdirslash.pop_back();
		compslash = L";" + curdirslash + L";";
	}
	else
	{
		curdirslash = curdir;
		curdirslash += L"\\";
		compslash = L";" + curdirslash + L";";
	}
	
	wstring envir;
	HKEY hkeym;
	
	if(type == 1)
	{
		envir = L"Environment";
		hkeym = HKEY_CURRENT_USER;
	}
	else
	{
		envir = L"System\\CurrentControlSet\\Control\\Session Manager\\Environment";
		hkeym = HKEY_LOCAL_MACHINE;
	}
	
	RegKey key{hkeym, envir};
	
	wstring cache = key.GetExpandStringValue(L"Path");
	wstring cachecmp;
	
	int index;
	int indexslash;
	
	if(cache == L"")
	{
		index = -1;
		indexslash = -1;
	}
	else
	{
		int breaksifnull = 0;
		while(cache.back() == L'\0')
		{
			cache.pop_back();
			if(cache.length() < 1)
			{
				breaksifnull = 1;
				break;
			}
		}
		if(breaksifnull == 0)
		{
			cachecmp = cache;
			if(cachecmp.front() != L';')
			{
				cachecmp = L";" + cachecmp;
			}
			if(cachecmp.back() != L';')
			{
				cachecmp += L";";
			}
			
			index = findci(cachecmp, comp);
			indexslash = findci(cachecmp, compslash);
		}
		else
		{
			index = -1;
			indexslash = -1;
		}
	}
	
	if(index == -1 && indexslash == -1)
	{	
		wstring empreg = L"";
		int empregnul = 0;
		if(cache.find_first_not_of(L'\0') == wstring::npos)
		{
			empregnul = 1;
		}
		
		if(cache == empreg || empregnul == 1)
		{
			const wstring processed = curdir;
			key.SetExpandStringValue(L"Path", processed);
			key.Close();
		}
		else
		{
			if(cache.front() == L';')
			{
				const wstring processed = L";" + curdir + cache + L"";
				key.SetExpandStringValue(L"Path", processed);
				key.Close();
			}
			else
			{
				const wstring processed = curdir + L";" + cache + L"";
				key.SetExpandStringValue(L"Path", processed);
				key.Close();
			}
		}
		
		result = 0;
	}
	else
	{
		key.Close();
		result = 1;
	}
	return result;
}

int pathLibUnregisterCore(wstring curdir, int type)
{
	int result = 2;
	
	if(curdir == L"")
	{
		return 1;
	}
	
	if(curdir.back() == L'\0')
	{
		curdir.pop_back();
	}
	wstring comp = L";" + curdir + L";";
	wstring curdirslash;
	wstring compslash;
	if(curdir.back() == L'\\')
	{
		curdirslash = curdir;
		curdirslash.pop_back();
		compslash = L";" + curdirslash + L";";
	}
	else
	{
		curdirslash = curdir;
		curdirslash += L"\\";
		compslash = L";" + curdirslash + L";";
	}
	
	wstring envir;
	HKEY hkeym;
	
	if(type == 1)
	{
		envir = L"Environment";
		hkeym = HKEY_CURRENT_USER;
	}
	else
	{
		envir = L"System\\CurrentControlSet\\Control\\Session Manager\\Environment";
		hkeym = HKEY_LOCAL_MACHINE;
	}
	
	RegKey key{hkeym, envir};
	
	wstring cache = key.GetExpandStringValue(L"Path");
	
	
	int index;
	int indexslash;
	int left = 0;
	int right = 0;
	
	if(cache == L"")
	{
		index = -1;
		indexslash = -1;
	}
	else
	{
		int breaksifnull = 0;
		while(cache.back() == L'\0')
		{
			cache.pop_back();
			if(cache.length() < 1)
			{
				breaksifnull = 1;
				break;
			}
		}
		if(breaksifnull == 0)
		{
			if(cache.front() == L';')
			{
				left = 1;
			}
			else
			{
				cache = L";" + cache;
			}
			if(cache.back() == L';')
			{
				right = 1;
			}
			else
			{
				cache += L";";
			}
			
			index = findci(cache, comp);
			indexslash = findci(cache, compslash);
		}
		else
		{
			left = 1;
			right = 1;
			cache = L";;";
			index = -1;
			indexslash = -1;
		}
	}
	
	if(index != -1 || indexslash != -1)
	{
		wstring empc = L";";
		replaceAllW(cache, comp, empc);
		replaceAllW(cache, compslash, empc);
		
		if(left == 0 && cache.length() > 0)
		{
			cache.erase(0, 1);
		}
		if(right == 0 && cache.length() > 0)
		{
			cache.pop_back();
		}
		
		left = 0;
		right = 0;
		
		cache += L"\0";
		
		
		key.SetExpandStringValue(L"Path", cache);
		key.Close();
		
		result = 0;
	}
	else
	{
		key.Close();
		result = 1;
	}
	return result;
}




int __cdecl pathLibRegisterSystem(wstring curdir)
{
	return pathLibRegisterCore(curdir, 0);
}

int __cdecl pathLibUnregisterSystem(wstring curdir)
{
	return pathLibUnregisterCore(curdir, 0);
}



int __cdecl pathLibRegisterUser(wstring curdir)
{
	return pathLibRegisterCore(curdir, 1);
}

int __cdecl pathLibUnregisterUser(wstring curdir)
{
	return pathLibUnregisterCore(curdir, 1);
}






int __cdecl pathLibRegisterSystemComp(wchar_t *curdir)
{
	wstring compatible(curdir);
	return pathLibRegisterCore(compatible, 0);
}

int __cdecl pathLibUnregisterSystemComp(wchar_t *curdir)
{
	wstring compatible(curdir);
	return pathLibUnregisterCore(compatible, 0);
}



int __cdecl pathLibRegisterUserComp(wchar_t *curdir)
{
	wstring compatible(curdir);
	return pathLibRegisterCore(compatible, 1);
}

int __cdecl pathLibUnregisterUserComp(wchar_t *curdir)
{
	wstring compatible(curdir);
	return pathLibUnregisterCore(compatible, 1);
}
