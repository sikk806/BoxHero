![image](https://github.com/sikk806/BoxHero/assets/54883267/8b8c6a71-e61b-45a4-b006-3a84c8f7c5e5)# BoxHero (구제목 : DarkSorcery)

#### __개발 기간__ : 2024 - 03 - 14 ~ (현재 진행중)
#### > 이후 개발 목표 : 2016 - 06 - 13 데모 개발 완료.
#### __참여 인원__ : 개인 개발
#### __사용한 기술__ : Unreal Engine 5.1, C++
#### __게임 요약__ : RPG, 보스 레이드, 싱글플레이
___
## 아키텍쳐
![Architecture](https://github.com/sikk806/BoxHero/assets/54883267/dfe12569-4c8e-47e8-9e94-5f49aab89e0b)
___
## 주요 개발 사항
1. Slots

2. Skills - Factory & Singleton Pattern
2-1. Factory Pattern
2-2. Singleton Pattern
3. AI Attack
Behavior Tree (DSCharacterTrashMob)

```C++
// AI/BTTask_Attack.cpp
AIPawn->SetAttackDelegate(OnAttackDelegate);
AIPawn->AttackByAI();

/*
Character/DSCharacterTrashMob, DSCharacterMidBoss
-> DSCharacterEnemy에서 모두 처리할 수 있도록 변경 예정(코드 재사용성을 높이기 위함.)
*/
void ADSCharacterTrashMob::AttackByAI()
{
  // For Play Attack Montage Function.
	AttackBegin();
}
```
___
## 남은 구현 목록
