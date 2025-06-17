@echo off

echo ----------Input File----------

set /p input=
echo %input%.exe

echo ----------Compling----------
g++ -finput-charset=utf-8 -fexec-charset=gbk %input%.cpp -o %input%.exe^
    -lopengl32 -lglew32 -lglfw3 -lgdi32 

echo ----------Running----------
%input%.exe

echo ----------End----------
pause
