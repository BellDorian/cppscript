# enable_string.ps1

$BuildDir = "build"
$InstallDir = Join-Path $BuildDir "install"

if (!(Test-Path $BuildDir)) {
    New-Item -ItemType Directory -Path $BuildDir | Out-Null
}

Push-Location $BuildDir
try {
    cmake .. -DCMAKE_INSTALL_PREFIX=$InstallDir
    cmake --build . --config Release
    cmake --install . --config Release

    Write-Output "`n========================="
    Write-Output "C-Script (cpps) build & install complete!"
    Write-Output ""
    Write-Output "Include path for headers: $InstallDir\include"
    Write-Output "Library path for linking: $InstallDir\lib"
    Write-Output ""
    Write-Output "Example usage with cl/g++:"
    Write-Output "g++ -std=c++20 -I $InstallDir\include -L $InstallDir\lib -lcpps your_main.cpp -o your_app"
    Write-Output "========================="
}
finally {
    Pop-Location
}
