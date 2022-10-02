@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
mkdir run_tree
pushd run_tree
cl -Zi /I ..\dependencies\SDL2\include ..\src\main.cpp SDL2.lib SDL2main.lib Shell32.lib Kernel32.lib /link /ENTRY:main /LIBPATH:..\dependencies\SDL2\lib /DEBUG:FULL
popd
