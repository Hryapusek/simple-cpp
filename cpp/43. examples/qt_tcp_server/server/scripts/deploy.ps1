Set-Variable -Name QtPath -Value "D:\Qt5\5.15.2\mingw81_64"
Set-Variable -Name MinGWPath -Value "D:\Qt5\Tools\mingw810_64"

Copy-Item $QtPath\bin\*.dll .\build
Copy-Item -Recurse $QtPath\plugins .\build
Copy-Item -Recurse $QtPath\plugins\platforms .\build
Copy-Item -Recurse $QtPath\plugins\platforms .\build\bin
Copy-Item -Recurse $QtPath\qml .\build

Copy-Item $MinGWPath\bin\*.dll .\build
