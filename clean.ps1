function rmrf($path) { Remove-Item $path -Recurse -Force }
$mingw_build_path="./build/mingw/"
if(Test-Path -Path $mingw_build_path){
    rmrf $mingw_build_path
}
$msvc_build_path="./build/msvc/"
if(Test-Path -Path $msvc_build_path){
    rmrf $msvc_build_path
}
rmrf ./bin/*.exe
