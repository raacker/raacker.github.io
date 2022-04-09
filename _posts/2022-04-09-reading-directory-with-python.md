---
title: "Reading directory with Python"
last_modified_at: 2022-04-09T00:42:00-08:00
categories:
    - Python
tags:
    - [Python, Snippet]
excerpt: "Yet another way of reading directory in alphanumerical order"
---

Another snippet series of "How to read my directory in a correct alphanumerical way"!

It's a lot shorter than c++ verions for sure.

```python
import os
import re

def atoi(text):
    return int(text) if text.isdigit() else text

def natural_keys(text):
    return [ atoi(c) for c in re.split(r'(\d+)', text) ]

if __name__ == "__main__":
    for root, _, files in os.walk(dirpath):
        files.sort(key=natural_keys)
```
