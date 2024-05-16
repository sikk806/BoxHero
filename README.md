![Skill](https://github.com/sikk806/BoxHero/assets/54883267/dfcb202d-b9c3-4e74-a2d0-dc8551fbdf55)# 📦BoxHero

#### __프로젝트 명__ : BoxHero (구제목 : DarkSorcery)
#### __개발 기간__ : 2024 - 03 - 14 ~ (현재 진행중)
#### __참여 인원__ : 개인 개발
#### __사용한 기술__ : <img src="https://img.shields.io/badge/Unreal_Engine-0E1128?style=for-the-badge&logo=UnrealEngine&logoColor=0E1128">
#### __게임 요약__ : RPG, 보스 레이드, 싱글플레이
___
## 아키텍쳐
![Architecture](https://github.com/sikk806/BoxHero/assets/54883267/dfe12569-4c8e-47e8-9e94-5f49aab89e0b)
___
## 일부 개발 완료된 사항
1. Slots
- SkillSlot to QuickSkillSlot
![Slots](https://github.com/sikk806/BoxHero/assets/54883267/23a50744-6f51-44c3-a39c-6b0b04ad3ac2)
- Dragging The Slot
![DropSlot](https://github.com/sikk806/BoxHero/assets/54883267/8fc7a1df-c69f-43ff-ad51-fc1748999153)
DSSlotWidget을 따로 구현하여 슬롯이 필요한 모든 곳에 적용 가능하도록 구조 설계
슬롯을 Drag 시 DSDragSlot 클래스에 데이터를 담고, Drop 시 DSDragSlot의 데이터를 DSSlotWidget에 전달
![SlotDiagram](https://github.com/sikk806/BoxHero/assets/54883267/67d9167f-362d-408f-aa82-876128e810a2)

2. Skills - Factory & Singleton Pattern
![Skill](https://github.com/sikk806/BoxHero/assets/54883267/ff61b070-c5d4-4fda-ba3c-c30d7e18c492)
2-1. Factory Pattern
- 스킬(Actor로 구현)들을 스폰할 때 사용.
- CharacterPlayer과 CharacterMonster 각자의 SkillFactory 보유
2-2. Singleton Pattern
- 주로 Slot에서 사용
- Slot 변경이 잦을 수 있기 때문에 Singleton 패턴 사용
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

// 
```
___
## 구현 예정
__이후 개발 목표 : 2016 - 06 - 13 데모 개발 완료.__
1. Quick Slot - Item (Potion)
2. Character(Player, Enemy) Rest Skills
3. Boss Hidden Pattern
4. Save / Load
5. UI - Main, Option, Boss Select
