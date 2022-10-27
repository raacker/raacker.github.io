---
title: "How to batch convert heic files to jpg or other image formats"
last_modified_at: 2022-04-05T23:47:00-08:00
categories:
    - Python
tags:
    - [Python, Snippets]
excerpt: "heic to jpg. iPhone images are heic formats. Please give me jpgs... "
toc: true
---

No talks needed! Just go jump in for the snippet.

## 1. Check your image files' depth bit

If you are not using Windows, you can skip this part.

If you see the images' properties, you can see what is "Bit depth" of your file.

Mostly, it will be 32 for the most of modern phones unless you changed some settings (because 32 bits means it's RGBA)

## 2. Install ImageMagick

Install a proper ImageMagick build depends on your operating system. [ImageMagick](https://imagemagick.org/script/download.php#windows)

If you are using Windows, you need to download a specific build that supports higher depth bit as we checked at #1. If you have images of 24 or 32 bits, just download 16 bits binary.

After installation, just make sure that you can access to "magick" binary through your command prompt. You might need to set system environment variable.

## 3. Run python script

Put the script along with your images and run it.

Reference: [heictojpg.py](https://github.com/mpapazog/heic-to-jpg/blob/master/heictojpg.py)

```python
import os, subprocess

directory = '.'

for filename in os.listdir(directory):
    if filename.lower().endswith(".heic"): 
        print('Converting %s...' % os.path.join(directory, filename))
        subprocess.run(["magick", "%s" % filename, "%s" % (filename[0:-5] + '.jpg')])
        continue
```

Happy Hacking!