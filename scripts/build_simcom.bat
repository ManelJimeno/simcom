set OLD_PATH=%PATH%

IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
IF EXIST "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars64.bat" call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars64.bat"

set PATH=%CD%\build\bin\lib;%PATH%
echo %PATH%
echo.


cmake -S. -Bbuild -G "Ninja"
cmake --build build --config Release --target server
cmake --build build --config Release --target client
cmake --build build --config Release --target u_test_1

C:\Users\Manel\projects\mikeli\repos\simcom\build\bin\u_test_1.exe


set PATH=%OLD_PATH%
