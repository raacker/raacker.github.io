---
title: "Print colored text in Windows CMD"
last_modified_at: 2022-08-07T17:43:00-08:00
categories:
    - scripting
tags:
    - [Windows, CMD, Batch]
excerpt: ""
---

Dealing with bash in Linux environment is pretty easier than Windows, simple scripts or even any commands.

When I was writing a library release script using msbuild and zip compression, I needed a proper way of showing colors as feedbacks of build result or any error occurance.

There were lots of options, surprisingly😅, but some of them are using powershell commands or the method doesn't work with .bat file at vanila windows environment. And also, I needed to make it as functions so that I can reuse them at any time.

Here, this is the final result of my green and red color echo printing functions that works in any circumstances.

Please find other color options in [Color palette](https://gist.githubusercontent.com/mlocati/fdabcaeb8071d5c75a2d51712db24011/raw/b710612d6320df7e146508094e84b92b34c77d48/win10colors.cmd)


```batch
:PRINT_GREEN 
	echo [32m%~1[0m
EXIT /B 0
:PRINT_RED
	echo [31m%~1[0m
EXIT /B 0
:CHECK_ERROR_LEVEL
	if not %errorlevel%==0 goto RELEASE_FAILED
	CALL :PRINT_GREEN "%~1"
EXIT /B 0
```

"EXIT /B 0" means you exit the procedure of batch file with errorcode, zero.

[Batch file errorlevels](https://www.manageengine.com/products/desktop-central/batch-file-errorlevels.html)

which means, you use "CALL" command to make a subroutine and exit the label at the end. Find extra details from [this page.](https://ss64.com/nt/call.html)

At the end, used the functions this way.

```batch
CALL :CHECK_ERROR_LEVEL "C++ Example Project build successful"
CALL :CHECK_ERROR_LEVEL "C# Example Project build successful"

:RELEASE_FAILED
CALL :PRINT_RED "Build Failed"
goto END
```

Reference
- [Stackoverflow : How to echo with different colors in the windows command line](https://stackoverflow.com/questions/2048509/how-to-echo-with-different-colors-in-the-windows-command-line)
