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
#include "findci.hpp"
#ifdef BUILDING_STATIC
#include "pathlib.cpp"
#else
#include "pathlib.hpp"
#endif
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	wstring cmdline = GetCommandLineW();
	if(cmdline.back() == '\0')
	{
		cmdline.pop_back();
	}
	cmdline += L" ";
	wstring helpwg = L"-help ";
	wstring infowg = L"-info ";
	wstring informationwg = L"-information ";
	wstring faqwg = L"-faq ";
	wstring guidewg = L"-guide ";
	wstring licensewg = L"-license ";
	wstring pathwg = L"-path=\"";
	wstring systemwg = L"-system ";
	wstring userwg = L"-user ";
	wstring invisiblewg = L"-invisible ";
	int indexhelp = findci(cmdline, helpwg);
	int indexinfo = findci(cmdline, infowg);
	int indexinformation = findci(cmdline, informationwg);
	int indexfaq = findci(cmdline, faqwg);
	int indexguide = findci(cmdline, guidewg);
	int indexlicense = findci(cmdline, licensewg);
	int indexpath = findci(cmdline, pathwg);
	
	int indexsystem = findci(cmdline, systemwg);
	int isyst = 1;
	int indexuser = findci(cmdline, userwg);
	int iusr = 0;
	if(indexuser != -1)
	{
		isyst = 0;
		iusr = 1;
	}
	if(indexsystem != -1)
	{
		isyst = 1;
		iusr = 0;
	}
	if(indexuser != -1 && indexsystem != -1)
	{
		isyst = 1;
		iusr = 1;
	}
	
	int indexinvisible = findci(cmdline, invisiblewg);
	if(indexhelp != -1 || indexinfo != -1 || indexinformation != -1 || indexfaq != -1 || indexguide != -1)
	{
		if(indexinvisible == -1)
		{
		wcout << L"Usage: register -option\n"
		L"Options:\n"
		L"  -help                   Display this information.\n"
		L"  -info                   Display this information.\n"
		L"  -information            Display this information.\n"
		L"  -faq                    Display this information.\n"
		L"  -guide                  Display this information.\n"
		L"  -license                Display license.\n"
		L"  -path=\"C:\\MegaFox\\lib\"  Override value added to PATH variable.\n"
		L"  -system                 Add value to only system PATH variable.\n"
		L"  -user                   Add value to only user PATH variable.\n"
		L"  -system -user           Add value to system and user PATH variable.\n"
		L"  -invisible              Disable output and waiting.\n"
		L"\nBy default, this program should be run from a directory that should be added to PATH variable.\n"
		L"\nThis program uses my high-precision algorithm for editing PATH variable and modifed WinReg library by GiovanniDicanio (https://github.com/GiovanniDicanio/WinReg).\n"
		L"Program supports Windows XP and newer.\n"
		L"\nBy using this program you agree to terms of license.\n"
		L"Author - MegaFox (https://4pda.ru/forum/index.php?showuser=4964705).\n" << endl;
		system("PAUSE");
		}
		return 0;
	}
	if(indexlicense != -1)
	{
		if(indexinvisible == -1)
		{
		wcout << pathLibLicense() << endl;
		system("PAUSE");
		}
		return 0;
	}
	
	DWORD bufSize = 10000;
	TCHAR buffer[10000];
	GetCurrentDirectory(bufSize, buffer);
	wstring curdir(&buffer[0]);
	if(indexpath != -1)
	{
		wstring cmdpath = cmdline;
		indexpath += 7;
		cmdpath.erase(0, indexpath);
		
		wstring empwg = L"\" ";
		int indexquot = findci(cmdpath, empwg);
		if(indexquot != -1)
		{
			cmdpath.erase(indexquot, cmdpath.length());
			curdir = cmdpath;
			if(indexinvisible == -1)
			{
			wcout << L"You selected custom path to folder." << endl;
			wcout << L"Adding custom directory to PATH. Please wait..." << L"\n" << endl;
			}
		}
	}
	else
	{
		if(indexinvisible == -1)
		{
			wcout << L"Adding current directory to PATH. Please wait..." << L"\n" << endl;
		}
	}
	
	int resul = 1;
	if(iusr == 1 && isyst == 1)
	{
		int locresulu;
		int locresuls;
		locresulu = pathLibRegisterUser(curdir);
		locresuls = pathLibRegisterSystem(curdir);
		if(locresulu == 0 || locresuls == 0)
		{
			resul = 0;
		}
		else
		{
			resul = 1;
		}
	}
	else
	{
		if(iusr == 1)
		{
			resul = pathLibRegisterUser(curdir);
		}
		if(isyst == 1)
		{
			resul = pathLibRegisterSystem(curdir);
		}
	}
	
	if(resul == 0)
	{
		if(indexinvisible == -1)
		{
			wcout << L"Directory successfully added to PATH! Author - MegaFox (https://4pda.ru/forum/index.php?showuser=4964705)" << L"\n" << endl;
		}
	}
	if(resul == 1)
	{
		if(indexinvisible == -1)
		{
			wcout << L"This directory is already registered!" << L"\n" << endl;
		}
	}
	
	
	
	if(indexinvisible == -1)
	{
		system("PAUSE");
	}
	return 0;
}
