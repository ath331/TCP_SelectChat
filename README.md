# TCP_SelectChat


port = 9999


전체 구조

![image](https://user-images.githubusercontent.com/39950003/109120193-fbe0bf80-7788-11eb-9389-a9725e17ef53.png)




1. Client가 Server에 접속하면 Server는 Session을 할당하여 Client와 매칭 시킨다.
2. Session은 Client와 recv, send, 명령어해석 등을 관리한다.
3. Client가 전송한 데이터는 매칭된 Session에 쌓이고 (1Byte씩) Enter(개행문자)입력시 쌓여있는 데이터를 해석하여 명령어인지 채팅인지 분석한다.
4. 명령어라면 알맞은 처리를 채팅이라면 해당 Client가 존재하는 방에 채팅을 뿌려준다.
