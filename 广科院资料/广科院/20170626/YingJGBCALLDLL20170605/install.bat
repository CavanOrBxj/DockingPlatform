@echo off
cd %~sdp0
::��ȡjavaָ��汾
java -version 2>%temp%\test.txt
findstr "64-Bit" %temp%\test.txt>>%temp%\test.txt
::��ȡjdkλ��
if %errorlevel%==0 (set flag=0) else (set flag=1)
::��ȡ�û������豸�����ͣ��û���������ֻ��Ϊ0����1
set /p ver=�������豸��
echo �豸���ͣ�%ver% 
::�û�����0ʱ��ʹ��sjj1313;�û�����1ʱ��Ϊʹ��sjj1507
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
::�˳�
:q
del %temp%\test.txt
pause
exit