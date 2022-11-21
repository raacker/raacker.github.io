
## How to run

```bash
g++ --std=c++14 -g $(find . -type f -iregex ".*\.cpp") -o result 
```

## Result

```
[Comm] AirCanada-Boing 737 EngineOn
[Comm] AirCanada-Boing 737 Move to Runaway 0
[Comm] AirCanada-Boing 737 Set Speed to 1000
[Comm] AirCanada-Boing 737 Landing Gear Up
[Comm] AirCanada-Boing 737 Departed
[Comm] KoreanAir-Boing 737 EngineOn
[Comm] KoreanAir-Boing 737 Move to Runaway 1
[Comm] KoreanAir-Boing 737 Set Speed to 1000
[Comm] KoreanAir-Boing 737 Landing Gear Up
[Comm] KoreanAir-Boing 737 Departed
```