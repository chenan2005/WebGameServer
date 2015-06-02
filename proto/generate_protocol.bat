@echo off
setlocal ENABLEDELAYEDEXPANSION
set x=%~dp0
for /f %%i in ('dir /s/a:-d/b *.proto') do (
	rem echo %%i ...
	set y=%%i
	set z=!y:%x%=!
	echo !z!
  ..\tools\protoc --cpp_out=../protocol  !z!
  ..\tools\protoc --plugin=protoc-gen-as3=..\tools\protoc-gen-as3.bat --as3_out=..\as3protocol !z!
)
pause
