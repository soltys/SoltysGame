#https://github.com/microsoft/vswhere/wiki/Find-VC

$path = vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if ($path) {
    $path = join-path $path 'Common7\Tools\vsdevcmd.bat'
    if (test-path $path) {
        cmd /s /c """$path"" $args && set" | Where-Object { $_ -match '(\w+)=(.*)' } | ForEach-Object {
            $null = new-item -force -path "Env:\$($Matches[1])" -value $Matches[2]
        }
    }
}