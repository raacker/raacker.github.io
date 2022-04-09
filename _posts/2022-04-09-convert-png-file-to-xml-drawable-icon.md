---
title: "Convert PNG file to XML drawable icon"
last_modified_at: 2022-04-09T00:28:00-08:00
categories:
    - Android
tags:
    - [Android, Mobile]
excerpt: "How to generate XML icon, drawable file from png files"
---

Easy and very short to go. 

The whole reason why you are converting a png file into xml is just because you need a vector image. SVG is a graphics format (Scalable Vector Graphics). Thus, you need another representation of your image to keep (at least something) in a correct scale.

1. Prepare your PNG files. Better to be at higher resolution if it's possible.

2. Use web converter or any tools to convert png files to svg files. There are many if you google them :)

3. Use neat website [SVG to Vector Drawable](https://svg2vector.com/)

Just make sure you are using correct width and height unit (mostly dp) and there won't be many chances you really need to change Bitmap tracer preset. 


GG pngs