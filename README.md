# [Win32API] 오목
<br>

## 프로젝트 소개
<div>
<img width="400" src="https://github.com/parkSihyeong46/Omok/blob/main/README_Image/Play1.PNG?raw=true"/>
<img width="400" src="https://github.com/parkSihyeong46/Omok/blob/main/README_Image/Play2.PNG?raw=true"/>
</div>

### 개요
이전의 프로젝트들에 비해 더 나은 구조를 설계하여 게임을 제작하는 것을 목적으로 제작

<br>

### 기술 스택
* Cpp

* Win api

* Visual Studio

<br>

## 시연 영상
<details>
  <summary>Play1 - victory</summary>
  <img width="976" src="https://github.com/parkSihyeong46/Omok/blob/main/README_Image/cut1.gif?raw=true"/>
</details>
<details>
  <summary>Play2 - sequence</summary>
  <img width="976" src="https://github.com/parkSihyeong46/Omok/blob/main/README_Image/cut2.gif?raw=true"/>
</details>
<details>
  <summary>Play3 - function</summary>
  <img width="976" src="https://github.com/parkSihyeong46/Omok/blob/main/README_Image/cut3.gif?raw=true"/>
</details>

<br/>

## 아쉬운 점
네트워크 기능을 이용해 멀티 플레이를 지원했었으면 하는 아쉬움이 있다.

아쉽게도 싱글 플레이를 염두해 두고 제작한 프로젝트인 만큼 네트워크를 적용하기엔 리펙토링을 할 코드가 많기도 하고

다음 진행할 프로젝트에서 네트워크 기능을 적용할 예정이기 때문에 프로젝트를 여기서 마무리 하기로 했다.

<br/>

## 배운 점
자세한 설계 없이 닥치는대로 추가만 하여 만든 나의 예전 개발 방식을 탈피하고자 고민했다.

게임의 출력 순서를 생각하니 SceneMgr - Scene - Object의 구조가 이상적이라 생각해 해당 구조를 적용했다.

그 결과 전과 다르게 확장성과 유지보수성이 좋아졌고, 출력 구조에 대해 한번 더 생각해 볼 수 있는 좋은 경험이었다.
