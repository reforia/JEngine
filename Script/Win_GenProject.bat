@echo off
pushd ..\
call ThirdParty\bin\premake\premake5 vs2019
popd
PAUSE