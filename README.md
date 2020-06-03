# 리눅스 소켓 프로그래밍
#### 2020학년도 1학기 성균관대학교 컴퓨터교육과 리눅스시스템 Term Project

텀 프로젝트의 주제는 '소켓 프로그래밍'입니다. 최종 목표는 소캣을 사용하여 대용량 파일을 송/수신하는 프로그램을 만드는 것 입니다.

## 🛠 개발 환경

- MacOS (FreeBSD)
- clang 11.0.0

## 🎯 프로젝트 목표

- TCP를 이용해 지정된 영화 파일을 서버에서 클라이언트로 전송하도록 구현하시오.
1. 클라이언트는 서버에게 접속하여 Hello Server 메시지를 전송
2. 서버는 미리 지정된 영화 파일 (예로 1GB의 test.mp4 파일)을 접속한 Client로 발송하되, 1460 바이트의 패킷으로 나누어 계속 전달
3. 클라이언트는 서버로부터 받아들인 패킷들을 메모리 버퍼 또는 파일버퍼에 모았다가 최종 file write를 하여 저장함.
4. 그 후, debug를 위해 원본 파일과 받은 파일의 내용 및 사이즈가 같은지 비교 (예: cmp나 diff 명령어 사용).

본 내용을 리눅스 상에서 구현하여, 리눅스 환경에서 compile 및 link를 하고, 이를 하나의 머신 (본인의 laptop에서 서버 클라이언트 모두 띄우고 IP를 127.0.0.1로 세팅해도 무방)에서 테스트 하거나, 하나 이상의 머신 (예로 친구 리눅스; IP는 미리 알 아야 함. 예로 친구의 DOS CMD시스템에서 ipconfig 명령어로 알 수 있음)에서 테스트한 내용을 보고서로 제출함.

> 출처 : Term Project: Linux System(Socket Programming) by Eun-Seok Ryu

## 💻 프로젝트 실행방법
프로젝트는 `make` 을 사용합니다.

#### 모든 프로그램을 컴파일하기

```bash
$ make
$ (또는) make all
```

#### 특정 프로그램(서버, 클라이언트)만 컴파일하기

```bash
$ make client (또는 server)
```

#### 컴파일된 오브젝트 파일 지우기, 프로그램까지 다 지우기

```bash
$ make clean
$ (또는) make fclean
```

## 📒 레퍼런스

- [이 리포지토리](https://github.com/Eleveres/simple_sockets)를 기반으로 코드를 수정, 추가하여 제작했습니다.
Thanks @Eleveres, owner of origin repo, for this wonderful code 😄
