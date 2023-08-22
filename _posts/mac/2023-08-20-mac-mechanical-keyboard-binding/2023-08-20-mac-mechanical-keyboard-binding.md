---
title: "맥에서 기계식 키보드 매핑하기 (feat. 한영키 바꾸기)"
last_modified_at: 2023-08-20T16:34:00+09:00
categories:
    - Mac
tags:
    - [Mac, Setup, DevEnv]
excerpt: "키보드 레이아웃이 다른 맥에서 윈도우 기계식 키보드 세팅해보기"
toc: true
---

## 윈도우용 레이아웃으로 맞춰보자

이 글은 최소한의 노력과 최소한의 렉 등 불필요한 것 없이 세팅을 맞추는 것을 다룹니다.

맥에서 키보드 레이아웃을 바꾸는 방법은 다양합니다. 검색해보면 1번과 2번 방식을 정말 많이 볼 수 있습니다. 각자 가진 장단점이 조금은 명확합니다만, 최종적으로 제가 선택하는 결론은 1번과 3번 조합이에요. 둘다의 장점을 최대한 얻는 방법으로요.

가능한 옵션으로는 다음과 같습니다.

1) 맥에서 직접 키 레이아웃을 바꾸기

- 가장 간편합니다. 이미 맥북에서 제공하는 설정이라서요.
- 맥에서 직접 바꾸는 것은 오히려 어떤 키가 어떤 키여야 하는지 좀 헷갈리는 편입니다.
- 다른 키보드로 사용하려고 하면 다시 설정해줘야 합니다. (노트북과 외부키보드 역시 운영체제 입장에서는 다른 키보드입니다)

2) [Karabiner-Element](https://karabiner-elements.pqrs.org/)

- Daemon을 실행해서 동작하는 방식이기에 새로운 키보드 프로필, 다양한 인풋 처리 등에 자유롭습니다. 소프트웨어가 컨트롤하는 범위 안에서는 모든게 자유로우니까요.
- 키매핑 방식으로 인해 인풋렉이 실제로 존재합니다. 입력한 키 이벤트가 Karabiner-element를 통해서 다른 입력으로 redirection되는 방식이기 때문에 어느정도 빠르게 친 입력은 인풋렉을 충분히 느낄 정도입니다.
- 별다른 설치를 하고 이것저것 세팅해야하는 번거로움이 있습니다.

3) plist 파일로 OS레벨에서 키 입력 자체를 바꾸기

- 잘 따라하면 어렵지 않게 할 수 있습니다. 별도의 세팅이 추가적으로 필요하지도 않구요.
- 준물리적으로 키를 바꾸는 것이라서 어느 키보드를 사용해도 동일한 인풋이 됩니다. 대신 이 말은 어느 키보드를 사용하더라도 고정적으로 바뀌기 때문에 특정 경우에 따라서는 불편할 수 있고 문제가 발생할 수도 있습니다.

## 1. plist 파일로 입력 바꾸기

맥은 Sierra부터 [hidutil](https://developer.apple.com/library/archive/technotes/tn2450/_index.html#//apple_ref/doc/uid/DTS40017618-CH1-KEY_TABLE_USAGES)이라는 툴을 공식적으로 지원합니다.

이 툴에 세팅을 적용해주면 키보드 매핑 자체를 OS 레벨에서 적용해주는 것이구요.

이 세팅을 부팅시마다 적용시켜 주기위해

```bash
/Library/LaunchAgents
~/Library/LaunchAgents
```

둘 다 잘 동작하니 아무 폴더 안에다가 세팅을 만들어서 넣어줄 것입니다.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>Label</key>
    <string>com.local.KeyRemapping</string>
    <key>ProgramArguments</key>
    <array>
        <string>/usr/bin/hidutil</string>
        <string>property</string>
        <string>--set</string>
        <string>{"UserKeyMapping":[

            {
              "HIDKeyboardModifierMappingSrc": 0x7000000E6,
              "HIDKeyboardModifierMappingDst": 0x70000006E
            }

        ]}</string>
    </array>
    <key>RunAtLoad</key>
    <true/>
</dict>
</plist>
```

이런식으로 .plist 확장자를 가지는 XML 파일로 세팅을 만들어주면 맥이 부팅하는 과정에서 이를 읽고 적용하는 방식입니다.

여기서 가장 쉽게 매핑 값을 만들 수 있는 방법은 [hidutil key remapping generator for MacOS](https://hidutil-generator.netlify.app/)입니다. 어느키가 존재하는지 쉽게 보는 방법은 위의 hidutil document 페이지에서 키들을 찾아보는 방법이고 아니라면 웹사이트가 제공하는 콤보박스를 사용해서 매핑을 선택하면 됩니다.

## 2. 한영키 만들기

Right Option키는 일반적으로 윈도우 키보드에서 스페이스바 오른쪽에 위치한 Alt키 입니다.

```bash
{
    "HIDKeyboardModifierMappingSrc": 0x7000000E6,
    "HIDKeyboardModifierMappingDst": 0x70000006D
}
```

맥북 키보드에서는 스페이스바 오른쪽에 Command키가 위치하고 있으니 노트북에서도 비슷한 위치에 놓고 싶으시다면 Right Command 역시 F18에 매핑해도 괜찮습니다. 저는 Right Option키만 사용하기로 했습니다.

위의 .plist 파일을 설정한 뒤, 저장하고 재부팅을 하면 해당 키는 설정해놓은 입력 키 이벤트로 변경이 됩니다. 어느 키보드를 사용하더라도 동일하게 리매핑이 됩니다. 이제 `Settings -> Keyboards -> Keyboard Shortcuts... -> Input Sources`로 들어가줍니다.

![Input source to f18](/_posts/mac/2023-08-20-mac-mechanical-keyboard-binding/images/change_input_source.png)

위 처럼 Input Sources에서 `Select the previous input source`를 꺼주고 `Select next source in input menu`의 키 값을 더블 클릭한 뒤, 저희가 방금 바꾼 키를 누르면 F18로 입력됩니다.

한영키를 눌러보시면 이젠 Ctrl + Space나 Tab키 같은 한영 변환을 안해도 됩니다.

## 3. Ctrl, Alt 키바인딩 바꾸기

그리고 맥북을 노트북으로 사용할 떄는 원래 가지고 있던 키 바인딩을 그대로 쓰려고 했습니다.

만약, 노트북 키보드나 외부키보드 모두 매핑을 맞추고 싶다면 hidutil 매핑 값을 바꾸도록 해주면 되구요. 각자 다른 매핑으로 쓰고 싶다면 Modifier Keys에 들어가서 아래처럼 바꿔주면 됩니다.

![Input source to f18](/_posts/mac/2023-08-20-mac-mechanical-keyboard-binding/images/mechanical_keyboard.png)

윈도우 키보드 레이아웃에 맞게

- 윈도우 Ctrl 키 -> 맥 Command
- 윈도우 Alt 키 -> 맥 Control

로 바꿔줍니다. 이렇게하면 외부키보드가 연결 되었을 때 자동으로 위 매핑이 사용됩니다.

윈도우키 같은 경우에는 맥에서 Option Key로 되어있는데 그대로 사용하는게 가장 편하다고 느꼈습니다.

위만큼만 설정 해주시고 추가적으로 원하는 바인딩은 추가만 해준다음 노트북을 재부팅하면 키매핑이 잘 바뀐 것을 보실 수 있습니다.

## 4. (추가) 노트북에서 원화키값을 백틱키값으로 바꿔주기

마크다운을 작성하다보면 백틱(`)을 쓸 일이 정말 많이 생깁니다. 그런데 맥북에서 한글 입력 상태에서는 백틱이 아닌 원화가 입력됩니다. 강제로 Option 키를 누르면서 백틱을 입력하는  방법도 있는데 이건 우리가 생각하는 생산성에 위배되죠.

hidutil은 키보드 인풋 이벤트 매핑을 바꿔줬다면 이번에는 `DefaultKeybinding`라는 파일을 만들어 입력되는 캐릭터 값 자체를 바꿔주는 방법입니다.

```bash
touch ~\Library\KeyBindings\DefaultKeyBinding.dict
```

를 하여 .dict 파일을 만든 다음, 그 안에

```json
{
    "₩" = ("insertText:", "`");
}
```

위 처럼 `₩` 캐릭터를 \` 로 바꿔주는 것입니다.

이 역시  재부팅을 해주면 바로 적용이 되고 한글입력, 영어입력 상관없이 사용할 수 있습니다.

### 참고자료

[레오폴드 매핑하기](https://chillog.page/148)
[Mac 한글 키보드에서 항상 원화(₩)대신 백틱(`) 입력되게 하기](https://www.korecmblog.com/blog/backtick-fix)
