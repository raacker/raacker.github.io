---
title: "Ask Privilege elevation in Windows batch"
last_modified_at: 2023-09-19T18:20:00-08:00
categories:
    - scripting
tags:
    - [Windows, CMD, Batch]
excerpt: "Get admin access to do more cool sh**"
---

## Quick Snippet

```batch
@echo off

:: BatchGotAdmin
:-------------------------------------
REM  --> Check for permissions
IF "%PROCESSOR_ARCHITECTURE%" EQU "amd64" (
>nul 2>&1 "%SYSTEMROOT%\SysWOW64\cacls.exe" "%SYSTEMROOT%\SysWOW64\config\system"
) ELSE (
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
)

REM --> If error flag set, we do not have admin.
if '%errorlevel%' NEQ '0' (
    echo Requesting administrative privileges...
    goto UACPrompt
) else ( goto gotAdmin )

:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    set params= %*
    echo UAC.ShellExecute "cmd.exe", "/c ""%~s0"" %params:"=""%", "", "runas", 1 >> "%temp%\getadmin.vbs"

    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
    exit /B

:gotAdmin
    pushd "%CD%"
    CD /D "%~dp0"
:--------------------------------------    

Pause

:exit
```

This snippet lets you get an administrator privilege elevation so that you can modify registry key, install a program, etc.

## How it works

### 1. Attempt to run system level application cacls.exe

```batch
IF "%PROCESSOR_ARCHITECTURE%" EQU "amd64" (
>nul 2>&1 "%SYSTEMROOT%\SysWOW64\cacls.exe" "%SYSTEMROOT%\SysWOW64\config\system"
) ELSE (
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
)
```

[cacls.exe](https://learn.microsoft.com/en-us/windows-server/administration/windows-commands/cacls) is a system program that lets you see the access of a specific file.

Since you are accessing system level program, it will return error code if you don't have a right access it.

### 2. If you don't have, show UAC prompt

```batch
if '%errorlevel%' NEQ '0' (
    echo Requesting administrative privileges...
    goto UACPrompt
) else ( goto gotAdmin )
```

Check the error code. If there was an error running cacls.exe, run a vbs script which helps you getting the privilege access.

```batch
:UACPrompt
    echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
    set params= %*
    echo UAC.ShellExecute "cmd.exe", "/c ""%~s0"" %params:"=""%", "", "runas", 1 >> "%temp%\getadmin.vbs"

    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
    exit /B
```

Happy hacking!
