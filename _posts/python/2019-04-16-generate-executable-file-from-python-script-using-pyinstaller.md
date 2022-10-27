---
title: "Generate exe file from Python script using pyinstaller"
last_modified_at: 2019-04-16T20:34:41+09:00
categories:
    - Python
tags:
    - [Python, Windows]
toc: true
excerpt: Generate executable file from python script. You also can enable UAC as default!
---

If you have a python script but you don't want to make your users (or non technical customers) life such hard dealing with python compiler, you can just simply generate exe file for them. 

What we can use in this case is "pyinstaller".
<br/>

## 1. Install pyinstaller

```bash
$ pip install pyinstaller
```

For detailed options, check this [pyinstaller link](https://pyinstaller.readthedocs.io/en/stable/usage.html#options)

Basically you can just do

## 2. Create an exe file

```bash
$ pyinstaller.exe your_file.py
```

Then it will generate exe file out of your script. But what you see is not going to be... just simple exe.

The output without *--onefile* option is all the intermediate files of compile time. Add *--onefile* to create a single exe file.

You can add --icon option to assign your fancy icon or you can hide consoles by --noconsole if you have some GUI.


<br/>
<br/>

## 3. Add UAC option
.... Well if that was all, I wouldn't write this post :p 

My exe was trying to access "Program Files" to adjust some of config file I installed. But that means I need privildge elevation or UAC control (User Access Control) or "Run as Administrator".

It is not straightforward to use all the commands as you want.

Here's my workaround to make it work. [Reference](https://stackoverflow.com/questions/43068920/pyinstaller-uac-not-working-in-onefile-mode)

If you don't use --onefile option, then you still have a chance to generate privildge program with --uac-admin option.

```bash
$ pyinstaller your_file.py --uac-admin
```

Then you can just extract your file which you need including .manifest file. Just write a batch script to process them automatically after building exe file

## 4. Put them all in batch script!

```bash
SET installer_name=MyUACInstaller

pyinstaller.exe --onefile --icon=./my_uac_installer.ico --noconsole %installer_name%.py
pyinstaller.exe --uac-admin %installer_name%.py
cp ./dist/%installer_name%/%installer_name%.exe.manifest ./
cp ./dist/%installer_name%.exe ./
rmdir /S /Q pycache
rmdir /S /Q build
rmdir /S /Q dist
del %installer_name%.spec
PAUSE
```

Then it will remain your beautiful .exe file and .manifest only!

Happy Hacking