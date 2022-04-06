---
title: "Reading Directory in Windows"
last_modified_at: 2020-08-22T10:32:50-08:00
categories:
    - C++
tags:
    - [C++]
toc: true
---

Sometimes, it is very painful to do a very small simple thing. Like a... reading all files inside of your directory! Everything you easily do in your cmd, "ls -la \| grep .jpg", can haven a bit of flaws for your c++ program.

Well, if you google "read directory in windows", there are so many stackoverflows you can look up for and lots of available options.

[How can I get the list of files in a directory using C or C++?](https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c)

You can use boost, c++17's filesystem, Win32 API or dirent.h snippet. We will go through Win32 API this time.

If you want to get to-go snippet, just scroll to the bottom for full version.

Our test directory structure looks like this
```bash
P1.txt   P11.txt  P13.txt  P3.txt  P5.txt  P7.txt  P9.txt
P10.txt  P12.txt  P2.txt   P4.txt  P6.txt  P8.txt
```

## 1) Read directory

Reading directory is just simple. Get File Handle of your directory using <b>FindFirstFileW</b> and loop through <b>FindNextFileW</b>

```cpp
#include <windows.h>
#include <vector>
#include <string>
int main()
{
    std::string dirPath = "C:\\Users\\haven\\git\\test\\*";
    std::vector<std::string> result;
    WIN32_FIND_DATA fileInformation;

    HANDLE handle = ::FindFirstFile(dirPath.c_str(), &fileInformation);

    // If handle is invalid, that means path does not exist.
    if (handle == INVALID_HANDLE_VALUE) return false;

    do
    {
        // Skip the self-directory
        if (fileInformation.cFileName[0] == '.') continue;

        result.push_back(fileInformation.cFileName);

    } while (::FindNextFile(handle, &fileInformation));
}
```

Not too hard right?

## 2) Filter files based on extensions

If you want to filter your files, add extension pattern at the end of your dir path.

```cpp
std::string pattern = ".txt";
std::string dirPath = "C:\\Users\\haven\\git\\test\\";
std::string searchPath = dirPath + "*" + pattern);
```

## 3) Check if the path is exist. And also specify the path is directory or file

Once you walk through directory path, they are all existing paths. But you can double check whether file exists or not. Also if your directory is full of files and directories, you might also want to filter out to files or directories.

```cpp
bool exists(const std::string& name)
{
    DWORD ftyp = GetFileAttributes(name.c_str());
    return ftyp != INVALID_FILE_ATTRIBUTES;
}

bool isDirectory(const std::string& path)
{
    if (!exists(path)) return false;

    DWORD ftyp = GetFileAttributes(path.c_str());
    return ftyp & FILE_ATTRIBUTE_DIRECTORY;
}
```

## 4) Sort your names in natural order.

If you followed the snippets, you might already saw that result seems not right.

The order is very wrong! Alphanumerically, it will be sorted out but natually it cannot handle mixed characters. Here is the solution.

[How to sort file names with numbers and alphabets in order in C?](https://stackoverflow.com/questions/13856975/how-to-sort-file-names-with-numbers-and-alphabets-in-order-in-c)

```cpp
int strcasecmp_withNumbers(const void *void_a, const void *void_b) {
    const char *a = (const char *)void_a;
    const char *b = (const char *)void_b;

    if (!a || !b) { // if one doesn't exist, other wins by default
        return a ? 1 : b ? -1 : 0;
    }
    if (isdigit(*a) && isdigit(*b)) { // if both start with numbers
        char *remainderA;
        char *remainderB;
        long valA = strtol(a, &remainderA, 10);
        long valB = strtol(b, &remainderB, 10);
        if (valA != valB)
            return valA - valB;
        // if you wish 7 == 007, comment out the next two lines
        else if (remainderB - b != remainderA - a) // equal with diff lengths
            return (int)((remainderB - b) - (remainderA - a)); // set 007 before 7
        else // if numerical parts equal, recurse
            return strcasecmp_withNumbers(remainderA, remainderB);
    }
    if (isdigit(*a) || isdigit(*b)) { // if just one is a number
        return isdigit(*a) ? -1 : 1; // numbers always come first
    }
    while (*a && *b) { // non-numeric characters
        if (isdigit(*a) || isdigit(*b))
            return strcasecmp_withNumbers(a, b); // recurse
        if (tolower(*a) != tolower(*b))
            return tolower(*a) - tolower(*b);
        a++;
        b++;
    }
    return *a ? 1 : *b ? -1 : 0;
}

bool natural_less(const std::string& lhs, const std::string& rhs)
{
    return strcasecmp_withNumbers(lhs.c_str(), rhs.c_str()) < 0;
}

// then add

#include <algorithm>
std::sort(result.begin(), result.end(), natural_less);
```


## 5) Full code with refactored interface!

```cpp
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>

enum Types
{
    FileOnly,
    DirectoryOnly,
    Both
};

int strcasecmp_withNumbers(const void *void_a, const void *void_b) {
    const char *a = (const char *)void_a;
    const char *b = (const char *)void_b;

    if (!a || !b) { // if one doesn't exist, other wins by default
        return a ? 1 : b ? -1 : 0;
    }
    if (isdigit(*a) && isdigit(*b)) { // if both start with numbers
        char *remainderA;
        char *remainderB;
        long valA = strtol(a, &remainderA, 10);
        long valB = strtol(b, &remainderB, 10);
        if (valA != valB)
            return valA - valB;
        // if you wish 7 == 007, comment out the next two lines
        else if (remainderB - b != remainderA - a) // equal with diff lengths
            return (int)((remainderB - b) - (remainderA - a)); // set 007 before 7
        else // if numerical parts equal, recurse
            return strcasecmp_withNumbers(remainderA, remainderB);
    }
    if (isdigit(*a) || isdigit(*b)) { // if just one is a number
        return isdigit(*a) ? -1 : 1; // numbers always come first
    }
    while (*a && *b) { // non-numeric characters
        if (isdigit(*a) || isdigit(*b))
            return strcasecmp_withNumbers(a, b); // recurse
        if (tolower(*a) != tolower(*b))
            return tolower(*a) - tolower(*b);
        a++;
        b++;
    }
    return *a ? 1 : *b ? -1 : 0;
}

bool natural_less(const std::string& lhs, const std::string& rhs)
{
    return strcasecmp_withNumbers(lhs.c_str(), rhs.c_str()) < 0;
}

std::string combinePath(const std::string& left, const std::string& right)
{
    return left + "\\" + right;
}

bool exists(const std::string& name)
{
    DWORD ftyp = GetFileAttributes(name.c_str());
    return ftyp != INVALID_FILE_ATTRIBUTES;
}

bool isDirectory(const std::string& path)
{
    if (!exists(path)) return false;

    DWORD ftyp = GetFileAttributes(path.c_str());
    return ftyp & FILE_ATTRIBUTE_DIRECTORY;
}

bool ReadDirectory(
    const std::string& dir,
    std::vector<std::string>& result,
    const Types type = Types::Both,
    const std::string& pattern = std::string())
{
    WIN32_FIND_DATA fileInformation;

    std::string searchPath = combinePath(dir, "*" + pattern);

    HANDLE handle = ::FindFirstFile(searchPath.c_str(), &fileInformation);
    if (handle == INVALID_HANDLE_VALUE) return false;

    do
    {
        if (fileInformation.cFileName[0] == '.') continue;

        const std::string fullPath = combinePath(dir, fileInformation.cFileName);

        if (type == Types::DirectoryOnly && !isDirectory(fullPath))
        {
            continue;
        }
        else if (type == Types::FileOnly && isDirectory(fullPath))
        {
            continue;
        }
        result.push_back(fullPath);

    } while (::FindNextFile(handle, &fileInformation));

    std::sort(result.begin(), result.end(), natural_less);

    return true;
}

bool ReadDirectory(
    const std::string& dir,
    std::vector<std::string>& result,
    const std::string& pattern)
{
    return ReadDirectory(dir, result, Types::Both, pattern);
}
```


## 6) Wide string (unicode) version

```cpp
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>

enum Types
{
    FileOnly,
    DirectoryOnly,
    Both
};

int strcasecmp_withNumbers_W(const wchar_t* a, const wchar_t* b) {
    if (!a || !b) { // if one doesn't exist, other wins by default
        return a ? 1 : b ? -1 : 0;
    }

    if (iswdigit(*a) && iswdigit(*b)) { // if both start with numbers
        wchar_t *remainderA;
        wchar_t *remainderB;
        long valA = wcstol(a, &remainderA, 10);
        long valB = wcstol(b, &remainderB, 10);
        if (valA != valB)
            return valA - valB;
        // if you wish 7 == 007, comment out the next two lines
        else if (remainderB - b != remainderA - a) // equal with diff lengths
            return (int)((remainderB - b) - (remainderA - a)); // set 007 before 7
        else // if numerical parts equal, recurse
            return strcasecmp_withNumbers_W(remainderA, remainderB);
    }
    if (iswdigit(*a) || iswdigit(*b)) { // if just one is a number
        return iswdigit(*a) ? -1 : 1; // numbers always come first
    }
    while (*a && *b) { // non-numeric characters
        if (iswdigit(*a) || iswdigit(*b))
            return strcasecmp_withNumbers_W(a, b); // recurse
        if (towlower(*a) != towlower(*b))
            return towlower(*a) - towlower(*b);
        a++;
        b++;
    }
    return *a ? 1 : *b ? -1 : 0;
}

bool natural_less_W(const std::wstring& lhs, const std::wstring& rhs)
{
    return strcasecmp_withNumbers_W(lhs.c_str(), rhs.c_str()) < 0;
}

std::wstring combinePath(const std::wstring& left, const std::wstring& right)
{
    return left + L"\\" + right;
}

bool exists(const std::wstring& name)
{
    DWORD ftyp = GetFileAttributesW(name.c_str());
    return ftyp != INVALID_FILE_ATTRIBUTES;
}

bool isDirectory(const std::wstring& path)
{
    if (!exists(path)) return false;

    DWORD ftyp = GetFileAttributesW(path.c_str());
    return ftyp & FILE_ATTRIBUTE_DIRECTORY;
}

bool ReadDirectoryW(
    const std::wstring& dir,
    std::vector<std::wstring>& result,
    const Types type = Types::Both,
    const std::wstring& pattern = std::wstring())
{
    WIN32_FIND_DATAW fileInformation;

    std::wstring searchPath = combinePath(dir, L"*" + pattern);

    HANDLE handle = ::FindFirstFileW(searchPath.c_str(), &fileInformation);
    if (handle == INVALID_HANDLE_VALUE) return false;

    do
    {
        if (fileInformation.cFileName[0] == '.') continue;

        const std::wstring fullPath = combinePath(dir, fileInformation.cFileName);

        if (type == Types::DirectoryOnly && !isDirectory(fullPath))
        {
            continue;
        }
        else if (type == Types::FileOnly && isDirectory(fullPath))
        {
            continue;
        }
        result.push_back(fullPath);

    } while (::FindNextFileW(handle, &fileInformation));

    std::sort(result.begin(), result.end(), natural_less_W);

    return true;
}

bool ReadDirectoryW(
    const std::wstring& dir,
    std::vector<std::wstring>& result,
    const std::wstring& pattern)
{
    return ReadDirectoryW(dir, result, Types::Both, pattern);
}
```

Now you got a powerful Copy+C,V tool you can use anywhere!

Happy Hacking!
