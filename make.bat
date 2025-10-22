mkdir debug
cd debug
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvarsamd64_x86.bat"
cmake -S ../Coding -B . -G "Visual Studio 16 2019" -A x64 -DCMAKE_CONFIGURATION_TYPES=debug
cmake --build . --config debug -- /m
cd ..
pause