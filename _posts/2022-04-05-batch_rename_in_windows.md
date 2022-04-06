---
title: "Batch rename in Windows"
last_modified_at: 2022-04-06T00:05:00-08:00
categories:
    - Windows
tags:
    - [Windows, Snippets, Visual Studio]
excerpt: "How to rename multiple files at once"
---

It's actually not that easy task to do in any operating systems even though it looks easy?

So let's say if you have multiple debug libs of OpenCV or any libraries that has postfix or prefix name. But I find it is pretty bad to maintain all of them in project configurations because you always have to change the "actual" lib file names rather than changing path and configurations. 

Thanksfully, those debug lib files will always have a similar naming convensions like ***d.lib or so. 

Let's just convert them all to have same naming as release library.

```bash
# get-childitem {targets} | foreach { rename-item $_ $_.Name.Replace({file_pattern}, {new_pattern}) }
get-childitem *d.lib | foreach { rename-item $_ $_.Name.Replace("d.lib", ".lib") }
```

In Linux, you can use [*rename*](https://www.cyberciti.biz/faq/linux-rename-file/) command

```bash
# rename 's/{file_pattern}/{new_pattern} {targets}'
# ex)
rename 's/_2018_report.txt/_report.txt/' *_2018_report.txt
```

Happy Hacking!