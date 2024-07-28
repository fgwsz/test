$root_path=Split-Path $ExecutionPath -Parent
$build_path="$root_path/build/windows"
if(Test-Path -Path $build_path){
    Remove-Item $build_path -Recurse -Force
}
