---
title: "Force single instance of the C# application"
last_modified_at: 2023-09-19T17:34:00+09:00
categories:
    - C#
tags:
    - [C#, .net]
excerpt: "If your exe shouldn't be launched more than once, check this out"
toc: true
---

## Quick Snippet

```cpp
static class MainProgram
{
    // Windows specific
    [DllImport("user32.dll")]
    static extern bool SetForegroundWindow(IntPtr hWnd);

    static void Main(string[] args)
    {
        ApplicationRun();
    }

    [STAThread]
    static void ApplicationRun()
    {
        bool createdNew;
        using (Mutex mutex = new Mutex(true, "TestProgram", out createdNew))
        {
            if (createdNew)
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new MainGUI());
            }
            else
            {
                Process current = Process.GetCurrentProcess();
                foreach (Process process in Process.GetProcessesByName(current.ProcessName))
                {
                    if (process.Id != current.Id)
                    {
                        SetForegroundWindow(process.MainWindowHandle);
                        break;
                    }
                }
            }
        }
    }
}
```

## How it works

### 1. Define named mutex

The first step is to spawn a Mutex with a specific name.

```cpp
using (Mutex mutex = new Mutex(true, "TestProgram", out createdNew))
{
}
```

This mutex is called `named system mutex`. It is not like an `unnammed mutex` or a local mutex. Check the reference below.

>Mutexes are of two types: **local mutexes**, which are unnamed, and **named system mutexes**. **A local mutex exists only within your process**. It can be used by any thread in your process that has a reference to the Mutex object that represents the mutex. Each unnamed Mutex object represents a separate local mutex.
>
> **Named system mutexes are visible throughout the operating system, and can be used to synchronize the activities of processes**. You can create a Mutex object that represents a named system mutex by using a constructor that accepts a name. The operating-system object can be created at the same time, or it can exist before the creation of the Mutex object. You can create multiple Mutex objects that represent the same named system mutex, and you can use the OpenExisting method to open an existing named system mutex.
[Microsoft Docs Reference](https://learn.microsoft.com/en-us/dotnet/api/system.threading.mutex?view=net-7.0)

By defining the name of the mutex, this is visible overall in the system.

I used a random name here but ideally, GUID of the application would be a better fit.

### 2. Check if the mutex exists or not

By passing the `out parameter createdNew`, we know that the mutex has never been created or not. If the new mutex creation was successful, you are a root process. Just go ahead and run the main GUI thread.

### 3. SetForegroundWindow

If not, it is not the first attempt to run the application. You can simply do any feedback you want but I would use `SetForegroundWindow()` function in Windows.

If you are using Linux, you should have proper API equivalent to the function.

First, import the function from user32.dll.

```cpp
[DllImport("user32.dll")]
static extern bool SetForegroundWindow(IntPtr hWnd);
```

And then, search for the same process ID from existing processes. If it matches with the process ID, bring it front.

```cpp
Process current = Process.GetCurrentProcess();
foreach (Process process in Process.GetProcessesByName(current.ProcessName))
{
    if (process.Id != current.Id)
    {
        SetForegroundWindow(process.MainWindowHandle);
        break;
    }
}
```

Happy hacking!
