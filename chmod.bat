@echo off
set /p folder=input foldername:
Cacls %folder% /t /e /c /g users:F 