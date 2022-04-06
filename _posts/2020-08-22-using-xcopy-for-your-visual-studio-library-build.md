---
title: "Using xcopy for your Visual Studio library build"
last_modified_at: 2020-08-22T12:10:50-08:00
categories:
    - C++
tags:
    - [C++, Visual Studio]
---

If you are building a C++ library, leveraging "build event" is very useful to organize your output directory. 

ex)

```bash
xcopy /Y /F /D "$(TargetDir)$(TargetName).dll" "$(ProjectDir)..\Output\bin\$(PlatformTarget)\$(Configuration)\"
xcopy /Y /F /D "$(TargetDir)$(TargetName).lib" "$(ProjectDir)..\Output\lib\$(PlatformTarget)\$(Configuration)\"
xcopy /Y /F /D "$(TargetDir)$(TargetName).pdb" "$(ProjectDir)..\Output\pdb\$(PlatformTarget)\$(Configuration)\"
```

[xcopy document](https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/xcopy)


### Additional hacks

1. If you don't want to see the copy messages all the time, add 1>nul

It will show you messages only when an error occured.

```bash
xcopy /Y /F /D "$(TargetDir)$(TargetName).dll" "$(ProjectDir)..\Output\bin\$(PlatformTarget)\$(Configuration)\" 1>nul
```

2. Force copy

Sometimes you might want to make sure the library is being built and build event copies all the binaries correctly.

This usually happens to me when I have separate libraries for testing and there is an another main program that pulls the library binaries out.
But as you know well, build event only gets fired when the project is "actually being updated". 

If you want to copy the libraries anytime, you can put 

```bash
<DisableFastUpToDateCheck>true</DisableFastUpToDateCheck>
```

option under your .vcproj file to disable auto up-to-date check. Then you don't have to keep typing spacebar and deleting to copy your main application code.

> A boolean value that applies to Visual Studio only. The Visual Studio build manager uses a process called FastUpToDateCheck to determine whether a project must be rebuilt to be up to date. This process is faster than using MSBuild to determine this. Setting the DisableFastUpToDateCheck property to true lets you bypass the Visual Studio build manager and force it to use MSBuild to determine whether the project is up to date.


Reference:[Always run post build event commands in visual studio 2017](https://stackoverflow.com/questions/51228443/always-run-post-build-event-commands-in-visual-studio-2017/51230663)

Happy hacking!
