# ShootWonban

ShootWonban은 플레이어가 날아가는 원반을 총으로 쏘아 맞추는 1인칭 클레이 사격 게임입니다. 이 프로젝트는 UE5를 사용하여 개발되며, 게임의 기획 및 주요 기능에 대한 내용을 아래에 정리하였습니다.

## 프로젝트 정보

- **프로젝트 기간**: 2024.08.05 ~ 2024.08.20
- **참여 인원**: 2명

## 주요 기능

### 1. 원반 스폰
- **스폰 위치**: 다양한 위치에서 원반을 생성합니다.
- **스폰 타이밍**: 일정 시간 간격으로 원반을 스폰합니다.

### 2. 원반 이동
- **포물선 이동**: 원반이 포물선을 그리며 이동합니다.

### 3. 사용자 입력 처리
- **총 쏘기**: 마우스 좌클릭으로 총을 쏩니다.
- **카메라 확대 및 조준**: 마우스 우클릭 시 카메라가 확대됩니다.

### 4. UI 구성
- **메인 메뉴**: 시작, 가이드, 종료 버튼 포함
- **인게임 UI**: 웨이브 정보, 남은 원반 수, 남은 총알 수 표시
- **게임 종료 화면**: 최종 점수 및 다시 시작 버튼 포함

### 5. 점수 계산
- 플레이어가 맞춘 원반의 수에 따라 점수를 계산합니다.

### 6. 패배 조건
- 남은 총알 수가 0이 되면 게임이 종료됩니다.
