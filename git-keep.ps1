$folder_path=Get-Location
Get-ChildItem -Recurse -Directory $folder_path|ForEach-Object{
    $folder=$_.FullName
    $files=Get-ChildItem $folder
    if ($files.Count -eq 0){
        $file_name = Join-Path -Path $folder -ChildPath ".gitkeep"
        New-Item -Path $file_name -ItemType "file" -Force
    }
}
