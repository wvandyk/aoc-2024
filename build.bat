@echo off
call C:\"Program Files"\"Microsoft Visual Studio"\2022\Community\VC\Auxiliary\Build\vcvarsall.bat x64

@REM CC=clang
@REM CFLAGS=-march=x86-64 -std=c++20 -Wall -Wno-missing-braces -g -O3 -mmmx -msse -msse2 -msse3 -msse4.1 -msse4.2 -ffp-contract=fast -fno-exceptions -fno-math-errno -fvectorize -target x86_64-pc-windows-msvc -fsanitize=undefined
@REM LIBS=-Wl,-SUBSYSTEM:WINDOWS,User32.lib,Gdi32.lib,Winmm.lib
@REM SRCDIR=src
@REM OUTDIR=build

@REM CC=clang
@REM CFLAGS=-O0 -march=x86-64 -std=c99 -Wall -Wno-gnu-folding-constant -Wno-missing-braces -g -mmmx -msse -msse2 -msse3 -mavx -mavx2 -ffp-contract=fast -fno-exceptions -fno-math-errno -fvectorize -target x86_64-pc-windows-msvc -fsanitize=undefined
@REM LIBDIR=-Lvendor\SDL2-2.30.5\lib\x64
@REM INCDIR=-Ivendor\SDL2-2.30.5\include
@REM LIBS=-Wl,-SUBSYSTEM:WINDOWS,User32.lib,Gdi32.lib,Winmm.lib,SDL2.lib,SDL2main.lib,Shell32.lib
@REM SRCDIR=src
@REM OUTDIR=build

echo Compiling main.cpp...
clang src\main.cpp -o build\aoc2024.exe -std=c++20 -g -O0 -Wall -Wno-writable-strings -Wno-deprecated-declarations --target=x86_64-pc-windows-msvc -l User32.lib -l Gdi32.lib
echo Done!
echo/