---
title: "맥에서 마우스 정확도 높이기"
last_modified_at: 2023-08-20T20:34:00+09:00
categories:
    - Mac
tags:
    - [Mac, Setup, DevEnv]
excerpt: "맥에서 마우스 포인터 정확도, 적중률을 더 높여보자!"
toc: true
---

## 결론

[SteelSeries ExactMouse Tool](https://downloads.steelseriescdn.com/drivers/tools/steelseries-exactmouse-tool.dmg) 깔아서 쓰세요.

## 나의 MX Master S3...

이번에 한국에 돌아오면서 마우스를 새로 구하게 되었습니다. 그동안 로지텍의 g305를 정말 잘 사용해왔는데 한국와서 사용하다보니 오른손목이 너무 아프더라구요?? 지금 쓰는 책상이 문제인건지... 후... 이유는 찾지 못한채 계속 늘어가는 손목 통증에 결국 버티컬 마우스를 사용해보자는 결론이 났었습니다.

가장 잘 써왔던건 로지텍의 Lift 였는데요, 제 손이 좀 더 크다보니 작다는 느낌을 지우기 어려웠습니다.

![lift](/_posts/mac/2023-08-20-mac-mouse-pointer-accuracy/images/lift.png)

그렇게 당근하게된 MX Master 3S. 와 뭐 버튼도 많고 Horizontal scroll 이 있질 않나, 무한 스크롤도 있고 대박 예감?

MX Vertical처럼 딱 손을 세우고 쓰는건 아니지만 그래도 적당한 각도로 휘어진 형태는 나름 편하다고 느낄 정도였습니다.

![이제 잘 적응한 MX Master 3S...](/_posts/mac/2023-08-20-mac-mouse-pointer-accuracy/images/mx_master_3s.jpg)
이제 잘 적응한 MX Master 3S...

## 마우스 포인터가 자꾸 어긋난다?

그런데 사용을 시작한지 2일쯤 되었을까요? 제 마우스의 정확도가 상당히 떨어졌음을 실감합니다. 나이탓이겠죠. 그래도 소싯적 스타크래프트 APM 300은 나오던 사람인데... 하면서 아쉬워 했지만.

근데 왠걸, 윈도우도 연결해서 써봤더니 제 손은 여전한 노련미를 펼치고 있었습니다. 코드 사이를 선택하고, 창을 닫는 정확도는 여전하더라구요. 아... 맥 또 너야? 맥또너?

## 마우스는 가속이 항상 문제입니다

글쎄요, 분명! 가속을 잘 활용하고 적응하신 분들도 많을 것이라고 생각합니다. 적은 마우스 움직임만으로도 화면을 크게 넘나들 수 있을터이니 좋아하시는 분들도 많을 것 같아요. 그런데 마우스 포인터의 정확성에 민감하신 분들(저)이라면 그 미묘한 차이에 불편함을 적잖이 느낄 것입니다.

단순하게 구글에 검색만 해봐도 이 맥에서의 가속도를 없애기위한 노력이 많습니다.

- `LinearMouse`라는 앱으로도 컨트롤이 가능합니다.
- `defaults write .GlobalPreferences com.apple.mouse.scaling -1`을 터미널에서 치면 적용되는 설정
- `SteelSeries ExactMouse Tool`이라는 앱도 있습니다.

제 기억에는 몇개가 더 있었던 것 같은데, 재부팅도 몇번 해보고 이런저런 설정 열심히 만져보다가 결국 정착하고 만족하고 쓰는 방법은

`SteelSeries ExactMouse Tool`입니다.

## SteelSeries ExactMouse Tool 깔기

단순합니다. 이 유지보수가 오랫동안 되지 않아서 이미지도 깨지는 앱을 깔아서 항상 데몬이 실행되도록 해주면 됩니다.

여전히 다운로드는 문제없이 받을 수 있습니다.

[https://downloads.steelseriescdn.com/drivers/tools/steelseries-exactmouse-tool.dmg](https://downloads.steelseriescdn.com/drivers/tools/steelseries-exactmouse-tool.dmg)

다운 받고 `Steelseries ExactMouse: Always On`, `Start on Log on` 을 체크해서 마무리해주면 단순하게 끝납니다.

사실 프로그램 자체가 하는 일은 내부 OS 레벨에서 마우스 가속도를 막는 것입니다. 위에 적어놓은 설정등을요. 그런데 묘하게도 체감상 그 설정등이 정확하게 적용되는 느낌적인 느낌이 몇번을 시도해도 바뀌지 않더라구요. 그렇게 정착하게 된 것이 ExactMouse 입니다.

아직 윈도우와 비교하면 여전히 약간의 느낌을 가끔 받는데요, 불편함을 느낄 수준은 전혀 아니어서 충분히 사용하게 되었습니다.

마우스 고민된다면... ExactMouse, 깔아보세요!