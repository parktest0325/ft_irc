# ft_irc
RFC 1459 문서를 기반으로 구현되는 채팅서버   
https://datatracker.ietf.org/doc/html/rfc1459

<br>

## 구현할 기능 
### 서버
순서대로 구현해도 괜찮을듯 싶다.
- 내 서버의 유저끼리만 통신가능한 서버
- 서버 종료, 유저 강퇴 기능이 있는 서버운영자 구현
- ft_irc 보너스과제였던 Bot기능
- 서버끼리의 연결 및 통신 기능 (서버운영자)
- 이미지 전송이나 AI Bot 기능 등 추가기능

### 클라이언트
- 일단 nc 로 기능테스트 하다가 서버의 첫번째 목표가 구현되면 작업 시작

<br>

## 구성
### Server
- 다른 사람이 구현한 채팅서버와 연결할 수 있어야 한다.
- 클라이언트의 정보를 가지고 있으며, 다른서버의 클라이언트에 메시지를 전달할때 서버가 중계해준다. (라우팅 테이블같은 느낌)

### Operator
- 서버의 운영자이다.
- 서버를 종료할 수 있고, 다른 서버와 연결할 수 있는 기능이 있다.

### Channels
- 첫 클라이언트가 접근할때 채널이 생성된다.
- 채널 이름은 & 또는 #으로 시작한다.
- 공백(' ')과 쉼표(',')를 포함할 수 없다
- 초대 전용인 경우 초대를 받아야만 참여할 수 있다.

### Channels Operator
- 채널 운영자는 여러명일 수 있고, 
- KICK, MODE, INVITE, TOPIC 명령을 추가로 사용할 수 있다.

### Channel User
- 그냥 메시지만 가능한유저

### Message


<br>

## 명령어

