# BoxHero ### (구제목 : DarkSorcery)

#### __개발 기간__ : 2024 - 03 - 14 ~ (현재 진행중)
#### > 이후 개발 목표 : 2016 - 06 - 13 데모 개발 완료.
#### __참여 인원__ : 개인 개발
#### __사용한 기술__ : Unreal Engine 5.1, C++
#### __게임 요약__ : RPG, 보스 레이드, 싱글플레이
___
## 아키텍쳐
![Architecture](https://github.com/sikk806/BoxHero/assets/54883267/dfe12569-4c8e-47e8-9e94-5f49aab89e0b)
___
## 개발 중인 사항
1. Slots
- SkillSlot to QuickSkillSlot
![Slots](https://github.com/sikk806/BoxHero/assets/54883267/23a50744-6f51-44c3-a39c-6b0b04ad3ac2)
- Dragging The Slot
![DropSlot](https://github.com/sikk806/BoxHero/assets/54883267/8fc7a1df-c69f-43ff-ad51-fc1748999153)
DSSlotWidget을 따로 구현하여 슬롯이 필요한 모든 곳에 적용 가능하도록 구조 설계
슬롯을 Drag 시 DSDragSlot 클래스에 데이터를 담고, Drop 시 DSDragSlot의 데이터를 DSSlotWidget에 전달
![SlotDiagram](https://github.com/sikk806/BoxHero/assets/54883267/67d9167f-362d-408f-aa82-876128e810a2)

2. Skills - Factory & Singleton Pattern
2-1. Factory Pattern
2-2. Singleton Pattern
3. AI Attack
Behavior Tree (DSCharacterTrashMob)
![BT](https://github.com/sikk806/BoxHero/assets/54883267/31bc31fd-4e50-4a48-ac9b-485af0809e1d)
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
