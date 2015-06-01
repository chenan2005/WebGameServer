@echo off
setlocal ENABLEDELAYEDEXPANSION
set x=%~dp0
set protocompile=..\3rdparty\protobuf-2.4.1\protoc.exe
set genas3plugin=..\tools\protoc-gen-as3-1.1.4\protoc-gen-as3.bat
set cppout=..\protocol
set as3out=..\as3protocol
for /f %%i in ('dir /s/a:-d/b *.proto') do (
	rem echo %%i ...
	set y=%%i
	set z=!y:%x%=!
	echo !z!
	if not exist %as3out% md %as3out%
	..\3rdparty\protobuf-2.4.1\protoc.exe --cpp_out=%cppout%  !z!
	..\3rdparty\protobuf-2.4.1\protoc.exe --plugin=protoc-gen-as3=%genas3plugin% --as3_out=%as3out% !z!
)
pause
