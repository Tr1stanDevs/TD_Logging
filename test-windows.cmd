@echo off
rmdir build
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build --config Release
.\build\Release\TD_Logging.exe