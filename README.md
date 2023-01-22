# Aldebaran
### 한국교통대학교 TAURUS / Korea National University of Transportation TAURUS team

### taurus_measuring_system

##### About Software
이 프로그램은 국립한국교통대학교 TAURUS 팀에서 데이터 계측을 위해 제작되었습니다.
무단 수정 및 배포를 금지하며, 비영리/개인적인 용도에 한하여 사용이 가능합니다.
소프트웨어는 C++[Arduino IDE]을 기반으로 제작되었습니다.

##### How to use
Arduino IDE를 이용하여 아두이노 보드에 코드를 업로드 합니다.
SD카드를 탑재합니다. 정상적으로 탑재된 경우 하단처럼 부저음이 두번 출력됩니다.
장치 동작 버튼을 ON으로 전환합니다.
부저음이 길게 두번 출력되면 측정이 시작됩니다.

### taurus_igntion_system

##### About Software
이 프로그램은 국립한국교통대학교 TAURUS 팀에서 원격 고체엔진 점화를 위해 제작되었습니다.
무단 수정 및 배포를 금지하며, 비영리/개인적인 용도에 한하여 사용이 가능합니다.
소프트웨어는 Python[Thonny IDE]을 기반으로 제작되었습니다.

##### How to use
Thonny IDE를 이용하여 Raspberry pi pico 보드에 코드를 업로드 합니다.
블루투스 송신 장치를 이용하여 점화기 시스템에 연결합니다.
명령어를 이용하여 점화기를 조작합니다.

##### Command List
| 명령어 | 사용용도 |
| ------- | -------------- |
| .launch. | 릴레이를 OFF[전원 연결]으로 변환 |
| .reset. | 릴레이를 ON[전원 차단]로 변환 |
