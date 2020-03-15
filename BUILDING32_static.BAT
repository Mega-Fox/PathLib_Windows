windres -i pathlib.rc -o pathlibres.o --target=pe-i386 -DUNICODE
g++ -c -DBUILDING_PATHLIB pathlib.cpp -I"include" -std=c++14 -m32 -Os -s -fno-rtti -fexceptions -Wall -DNDEBUG -DUNICODE
g++ -shared -static -static-libgcc -static-libstdc++ -o pathlib32.dll -lmingw32 pathlib.o pathlibres.o -Wl,--out-implib,libpathlib32.a -DUNICODE
pause
windres -i register.rc -o registerres.o --target=pe-i386 -DUNICODE
g++ -DBUILDING_STATIC register.cpp -I"include" -std=c++14 -m32 -static -static-libgcc -static-libstdc++ -Os -s -fno-rtti -fexceptions -Wall -DNDEBUG -DUNICODE -Wl,-s -Wl,-subsystem,console -o register32.exe -lmingw32 registerres.o
pause
windres -i unregister.rc -o unregisterres.o --target=pe-i386 -DUNICODE
g++ -DBUILDING_STATIC unregister.cpp -I"include" -std=c++14 -m32 -static -static-libgcc -static-libstdc++ -Os -s -fno-rtti -fexceptions -Wall -DNDEBUG -DUNICODE -Wl,-s -Wl,-subsystem,console -o unregister32.exe -lmingw32 unregisterres.o
del /s *.obj
del /s *.o
pause
