@echo off
rem ---------------------------------------------------------------
rem Description: Windows XP doesn't have Unix like sleep command...
rem Copyright 2006, by Navid Mohaghegh, All Rights Reserved.
rem License: LGPL
rem ---------------------------------------------------------------

if "%1"=="" (ping -n 2 127.0.0.1>nul
) else (ping -n %1% 127.0.0.1>nul )
