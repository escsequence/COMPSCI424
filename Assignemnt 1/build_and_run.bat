:: Assignment 1 build_and_run.bat
:: Compiles and then executes the Assignment
@echo off
cls
g++ assignment1.cpp version1.cpp version2.cpp -o Assignment1.exe
.\Assignment1.exe
pause
