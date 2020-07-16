@echo off
start clean.bat
g++ "src/engine.cpp" "src/glad.c" -o game.exe -I "include" "src/pluto.h" -O2 -Wl,-subsystem,windows -L "lib" -lglfw3 -lopengl32 -lgdi32
g++ "src/engine.cpp" "src/glad.c" -o game_debug.exe -I "include" "src/pluto.h" -O2 -L "lib" -lglfw3 -lopengl32 -lgdi32
pause