$project_name=Split-Path -Leaf (Get-Location)
$build_path="./build/mingw/debug"
if(!(Test-Path -Path $build_path)){
    mkdir $build_path
}
cd $build_path
cmake -G "MinGW Makefiles" ../../..
cmake --build .
cd ../../..
cp "$build_path/$project_name.exe" "./bin/$project_name-mingw-debug.exe"
$bin_res_path="./bin/res"
if(!(Test-Path -Path $bin_res_path)){
    mkdir $bin_res_path
}
cp ./res/* $bin_res_path
& "./bin/$project_name-mingw-debug.exe"
