
## How to run

```bash
g++ --std=c++17 -g $(find . -type f -iregex ".*\.cpp") -I ./Dependencies/alpaca/include -o result  
```

## Result

```bash
Name : Haven
Address : Vancouver
Tel : 236-567-1234

Name : Ken
Address : Burnaby
Tel : 236-765-4321

Name : Haven
Address : Vancouver
Tel : 236-567-1234
```
