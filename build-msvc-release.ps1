$project_name=Split-Path -Leaf (Get-Location)
$build_path="./build/msvc/release"
if(!(Test-Path -Path $build_path)){
    mkdir $build_path
}
cd $build_path
cmake -G "Visual Studio 17 2022" ../../..
cmake --build . --config Release
cd ../../..
cp "$build_path/Release/$project_name.exe" "./bin/$project_name-msvc-release.exe"
$bin_res_path="./bin/res"
if(!(Test-Path -Path $bin_res_path)){
    mkdir $bin_res_path
}
cp ./res/* $bin_res_path
& "./bin/$project_name-msvc-release.exe"
