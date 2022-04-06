---
title: "Pass key event to a specific process"
last_modified_at: 2019-07-15T00:05:55-07:00
categories:
    - CPP
tags:
    - csharp
---

Let's just go straightforward how to make "KeyEvent" to a specific process using C#.

1) Import libraries

{% highlight C# %}
using System.Diagnostics;
using System.Linq;
using System.Windows.Forms;
{% endhighlight %}

You need Windows.Forms to call SendKeys class method. If your program says it cannot find it, try "Add Reference" on your project properties.

(Optional) SetForegroundWindow

If you want to force bring the process, define this dll function

{% highlight C# %}
[DllImport("User32.dll")]
static extern int SetForegroundWindow(IntPtr point);
{% endhighlight %}

2) Generate Process and Send command

{% highlight C# %}
Process p = Process.GetProcessesByName("Notepad").FirstOrDefault();
 if (p != null)
 {
     IntPtr h = p.MainWindowHandle;
     SetForegroundWindow(h);
     SendKeys.SendWait("abcde");
     SendKeys.SendWait("^z");
}
{% endhighlight %}

First, find the process by name. ex) Notepad.

Second, if process was able to find "Notepad" process, call SetForegroundWindow() and call SendKeys.SendWait().

You can just pass String in certain way like "^z" will do Ctrl + Z like undo.

Check this link for more key combi info

[Key combination Reference](https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.sendkeys.send?view=netframework-4.8)  

Happy Hacking!
