---
title: "Convert PNG file to XML drawable icon"
last_modified_at: 2022-04-09T00:28:00-08:00
categories:
    - Android
tags:
    - [Android, Mobile]
excerpt: "How to generate XML icon, drawable file from png files"
---

Updated: Dec 13, 2022

I saw lots of traffics on this article but I noticed this page doesn't cover the problem enough.

And one more things to update, the original post of this was actually 4 years old 😅.

> If you are reading this article, I would assume you know what you are doing. But let me go through this part.
>
> I want you to keep in mind that converting png to svg, eventually to XML, is not a good solution. You *better* avoid this. Always try to look for svg format for sure. And keep .ai file or figma files to generate svg at any time. SVG does a very important role in multi-resolution world, which PNG or JPG cannot do.
>
> Converting PNG to SVG is possible and sometimes you don't have a nice option to choose rather than this way. Still, you should be aware of problems with resolutions.

1. Prepare PNG or JPG files. Any of your static images. I assume most of them are icon images but try to optain as high resolultion as possible.

2. We must convert images to SVG first. There are several options I've tried. But `Adobe Express` was the best option so far.

    - [Adobe Express](https://www.adobe.com/express/feature/image/convert/png-to-svg)
      - Web upload version. It works pretty nice. But you need a sign-up.
    - [SVGCode](https://github.com/tomayac/SVGcode)
      - Progressive Web app based. Sorta okay.

3. Once you have SVG files, it's literally done because XML is just another format of describing Vectorized images.

   - [Android Studio](https://stackoverflow.com/questions/46456867/converting-svg-file-to-android-vector-drawable-xml-while-keeping-the-group-struc)
     - Open Asset Studio. You can load SVG or PSD file. And the program will auto convert for you.
   - [SVG to Vector Drawable](https://svg2vector.com/)
     - If you want to manually convert your images (I suppose you barely need to), you can try this web site. I used this a lot before the Android Studio added Asset Studio support. Just make sure you are using correct width and height unit (mostly dp) and there won't be many chances you really need to change Bitmap tracer preset.

Happy Hacking 😁
