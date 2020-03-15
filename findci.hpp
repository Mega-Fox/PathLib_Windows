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

#ifndef FINDCI_HPP
#define FINDCI_HPP

#include <locale>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename charT>
struct my_equal
{
    my_equal(const std::locale& loc) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2)
	{
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

template<typename T>
int findci(const T& str1, const T& str2, const std::locale& loc = std::locale())
{
	setlocale(LC_ALL, "");
    typename T::const_iterator it = std::search(str1.begin(), str1.end(), str2.begin(), str2.end(), my_equal<typename T::value_type>(loc));
    if(it != str1.end()) return it - str1.begin();
    else return -1;
}

#endif // FINDCI_HPP
