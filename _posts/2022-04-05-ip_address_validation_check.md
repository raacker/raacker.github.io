---
title: "C++ IP Address validation check"
last_modified_at: 2022-04-05T23:39:00-08:00
categories:
    - C++
tags:
    - [C++]
excerpt: "A code snippet of how to validate IP address string in C++"
---

No talk.

IP Address validation? you know what you are doing and what you need. 

```cpp
bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(),
        [](unsigned char c) { return !std::isdigit(c) && (c != '.'); }) == s.end();
}
bool checkIPDigit(const std::string& s)
{
    if (!is_number(s)) return false;
    int _v = std::stoi(s);
    if (_v < 0 || _v > 255)
        return false;
    return true;
}

#include <regex>
#include <string>
bool validateIPAddress(std::string& s)
{
    std::regex reg("\\.");
    std::sregex_token_iterator iter(s.begin(), s.end(), reg, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> sections(iter, end);
    if (sections.size() != 4) return false;

    for (std::string v : sections)
    {
        if (!checkIPDigit(v)) return false;
    }

    return true;
}
```

Happy Hacking!