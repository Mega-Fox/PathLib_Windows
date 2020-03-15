windres -i pathlib.rc -o pathlibres.o --target=pe-x86-64 -DUNICODE
g++ -c -DBUILDING_PATHLIB pathlib.cpp -I"include" -std=c++14 -m64 -Os -s -fno-rtti -fexceptions -Wall -DNDEBUG -DUNICODE
g++ -shared -o pathlib64.dll pathlib.o pathlibres.o -Wl,--out-implib,libpathlib64.a -DUNICODE
pause
windres -i register.rc -o registerres.o --target=pe-x86-64 -DUNICODE
g++ register.cpp -I"include" -std=c++14 -m64 -Os -s -fno-rtti -fexceptions -Wall -DNDEBUG -DUNICODE -Wl,-s -Wl,-subsystem,console -o register64.exe registerres.o -L. -lpathlib64
pause
windres -i unregister.rc -o unregisterres.o --target=pe-x86-64 -DUNICODE
g++ unregister.cpp -I"include" -std=c++14 -m64 -Os -s -fno-rtti -fexceptions -Wall -DNDEBUG -DUNICODE -Wl,-s -Wl,-subsystem,console -o unregister64.exe unregisterres.o -L. -lpathlib64
del /s *.obj
del /s *.o
pause
