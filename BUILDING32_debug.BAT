windres -i pathlib.rc -o pathlibres.o --target=pe-i386 -DUNICODE
g++ -c -DBUILDING_PATHLIB pathlib.cpp -I"include" -std=c++14 -m32 -O0 -g -fexceptions -Wall -DUNICODE
g++ -shared -o pathlib32.dll -lmingw32 pathlib.o pathlibres.o -Wl,--out-implib,libpathlib32.a -DUNICODE
pause
windres -i register.rc -o registerres.o --target=pe-i386 -DUNICODE
g++ register.cpp -I"include" -std=c++14 -m32 -O0 -g -fexceptions -Wall -DUNICODE -Wl,-subsystem,console -o register32.exe -lmingw32 registerres.o -L. -lpathlib32
pause
windres -i unregister.rc -o unregisterres.o --target=pe-i386 -DUNICODE
g++ unregister.cpp -I"include" -std=c++14 -m32 -O0 -g -fexceptions -Wall -DUNICODE -Wl,-subsystem,console -o unregister32.exe -lmingw32 unregisterres.o -L. -lpathlib32
del /s *.obj
del /s *.o
pause
