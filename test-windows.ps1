
$build_type = "Release"

if (Test-Path .\build) {
    Remove-Item .\build -Recurse -Force
}

cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build build --config $build_type
Clear-Host
.\build\Release\TD_Logging.exe