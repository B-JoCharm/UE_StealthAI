\# UE\_StealthAI



\## 프로젝트 개요

Unreal Engine 5 C++ 기반 잠입 액션 게임 프로토타입.

AI 시스템(시야 감지, 순찰, 추격)과 C++/Blueprint 협업 구조를 포트폴리오 목적으로 구현.



\## 브랜치 전략

| 브랜치 | 내용 |

|---|---|

| `main` | 안정적인 빌드 유지 |

| `feature/player-character` | 플레이어 캐릭터 |

| `feature/base-map` | 기본 맵 구성 |

| `feature/ai-character` | AI 캐릭터 기본 구조 |

| `feature/ai-patrol` | 순찰 시스템 |

| `feature/ai-detection` | 시야 감지 시스템 |

| `feature/behavior-tree` | Behavior Tree 적용 |

| `feature/game-rules` | 게임 목표/실패 조건 |



\## C++ / Blueprint 역할 분리

\- \*\*C++\*\*: 게임 로직, AI 시스템, 기반 클래스 설계

\- \*\*Blueprint\*\*: Mesh/애니메이션 연결, 수치 튜닝, 연출

