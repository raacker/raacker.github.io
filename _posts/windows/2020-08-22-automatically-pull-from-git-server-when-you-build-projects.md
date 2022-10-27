---
title: "Automatically pull from git server when you build Projects"
last_modified_at: 2020-08-22T12:32:50-08:00
categories:
    - C++
tags:
    - [C++, Windows, Visual Studio]
---

This time, let's setup a new project to run a batch file which will pull and update your git repo automatically with only one click. I will use ssh-agent and public key to access my private git repositories. If you are using github to do the same, please refer to github access guide.

You can use this hack if you have multiple git dependencies in your project and they are frequently updated.

**0) Prerequisites**

To run ssh-agent in a easy way, we better to install git-bash. Well I'm sure you already installed git-bash if you are a windows user :)

[https://git-scm.com/downloads](https://git-scm.com/downloads)

**1) Create a batch file**

```bash
:: Use %userprofile% to get your home directory.
set default_ssh_key_path=%userprofile%\.ssh\pub_key

:: Need to install windows git-bash for this script.
:: Located under "C:\\Program Files\\Git\\cmd"
call start-ssh-agent.cmd

:: Add your public key to ssh-agent so that you only enter your passphrase once during this batch run
ssh-add %default_ssh_key_path%

:: Get absolute path of your batch file
FOR %%i IN ("%0") DO (
set filedrive=%%~di
set filepath=%%~pi
)
set batchpath=%filedrive%%filepath%

set Repo_Path=%[YOUR_PATH]%
if not exist "%Repo_Path%" git clone git@PATH:your_repo.git %Repo_Path%
:: If you want to pull specific branch, for example develop branch.
:: if not exist "%Repo_Path%" git clone --single-branch --branch develop git@PATH:your_repo.git %Repo_Path%
cd %Repo_Path%

:: You might want to reset any working copies before pull command.
:: git reset --hard HEAD
git pull origin develop
```

You need to set repo path you are referring to.

**2) Create a new project and add call command to build event**

start /wait "YOUR_BATCH_FILE_PATH"

**3) All Set!**

Now when you want to reset your external git repo, just build this project then it will pull everything in a easy manner.

Happy Hacking!
