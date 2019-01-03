@echo off
cd %~sdp0
::获取java指令版本
java -version 2>%temp%\test.txt
findstr "64-Bit" %temp%\test.txt>>%temp%\test.txt
::获取jdk位数
if %errorlevel%==0 (set flag=0) else (set flag=1)
::获取用户输入设备的类型，用户输入数据只能为0或者1
set /p ver=请输入设备：
echo 设备类型：%ver% 
::用户输入0时候使用sjj1313;用户输入1时候为使用sjj1507
if %ver%==0 (if %flag%==0 (goto d1507c64) else (goto d1507c32))
if %ver%==1 (if %flag%==0 (goto d1313c64) else (goto d1313c32))
::echo choice sjj1507 



:d1507c64
copy .\sjj1507\win64\*.* C:\Windows\SysWOW64\
copy .\sjj1507\win64\*.* C:\Windows\SysWOW64\
::echo "d1507c64-1"
::echo "d1507c64-2"
goto q
:d1507c32
copy .\sjj1507\win32\*.* C:\Windows\System32\
copy .\sjj1507\win32\*.* C:\Windows\System32\
::echo "d1507c32-1"
::echo "d1507c32-2"
goto q
:d1313c64
copy .\sjj1313\windows_x64\*.* C:\Windows\SysWOW64\
copy .\sjj1313\windows_x64\*.* C:\Windows\SysWOW64\
::echo "d1313c64-1"
::echo "d1313c64-2"
goto q
:d1313c32
copy .\sjj1313\windows_x32\*.* C:\Windows\System32\
copy .\sjj1313\windows_x32\*.* C:\Windows\System32\
::echo "d1313c32-1"
::echo "d1313c32-2"
goto q
::退出
:q
del %temp%\test.txt
pause
exit