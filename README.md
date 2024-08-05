此项目为使用UE5 GameplayAbilitySystem开发的游戏。

UE版本：5.4.3

# Gameplay Ability System（GAS）文档

## 基础概念和基本使用

#### **基础概念**

| 模块                        | 解释         |
| --------------------------- | ------------ |
| AbilitySystemComponent(ASC) | 技能系统组件 |
| Attribute                   | 属性         |
| AttributeSet                | 属性集       |
| GameplayAbility(GA)         | 玩法技能     |
| GameplayEffect(GE)          | 玩法效果     |
| GameplayCue(GC)             | 玩法提示     |
| AbilityTask                 | 技能任务     |
|                             |              |



#### GameplayEffect

##### UGameplayEffect概述

GamelayEffect(GE)是修改自身或者目标Attribute和GameplayTag的容器。这是编辑器中定义的数据**资产**，驱动所有相关功能。它只是一个描述游戏效果的数据类，不应该在其中添加额外的逻辑。GE在使用时一般不实例化，在运行时不可修改，而是把GE的CDO包进FGameplayEffectSpec作为运行时的GE。

持续类型：`即刻(Instant)`, `持续(Duration)`和`无限(Infinite)`.

GE的子项：

- Components:增减Tag
- Modifers：修改属性值
- Executions：修改属性值。它是一种更加强力、更加灵活的修改属性值的方法。当Modifier满足不了需求时使用，缺点是**不可预测**。

![](C:\Users\darylye\Documents\Unreal Projects\MiniGame\assets\GE_CDO_Details.png)







UGameplayEffectSpec概述

```c++
USTRUCT(BlueprintType)
struct GAMEPLAYABILITIES_API FGameplayEffectSpec
{
    GENERATED_USTRUCT_BODY()
        
    /** GameplayEffect定义. 这个Spec指向的静态数据. */
	UPROPERTY()
	TObjectPtr<const UGameplayEffect> Def;
    
    /** Map of set by caller magnitudes */
	TMap<FName, float>			SetByCallerNameMagnitudes;
	TMap<FGameplayTag, float>	SetByCallerTagMagnitudes;
    .....
}

```

GameplayEffectSpec是Gameplay Effect Specification，它可以看作是GameplayEffect的实例，里面保存着这个Spec所代表的`const`**只读**GameplayEffect的智能指针`Def`，以及描述这个GameplayEffect的运行时信息（等级、创建者....）。我们可以在Spec被应用到目标前，在运行时(Runtime)对其进行创建和修改。我们可以使用下面这个蓝图节点`MakeOutgoingGameplayEffectSpec`手动从GE Class创建出Spec。

![image-20240806010654895](assets/Make Outgoing Gameplay Effect Spec.png)



我们可以在**外部**向GameplayEffectSpec添加与` FName`或`FGameplayTag`相关联的**浮点值**，他们存储在TMap `SetByCallerNameMagnitudes`和`SetByCallerTagMagnitudes`。当我们在计算修改属性值时，我们通过SetByCaller的节点（如下图所示）向Spec中传入外部的数值进行。在MiniGame的项目中，对不同命中骨骼造成不同伤害的功能，就是通过SetByCaller在外部把伤害系数传进GameplayEffectSpec，在Modifier的Custom Caculation Class取得该系数并与攻击力相乘得到扣血量实现的。

![image-20240806012546838](assets/SetByCaller.png)

# 浅析GAS的预测和网络同步机制

GAS的高阶目标：

GAS希望**避免**在GA本身包含"如果是权威：执行 X。否则：执行 X 的预测版本”"这样的逻辑。

![image-20240805112210694](C:\Users\darylye\Documents\Unreal Projects\MiniGame\assets\DoXPredictively.png)

它期望给开发者提供：

- 透明的网络同步
- 透明的**GA**级别（实施技能时）的预测



以下参考自GameplayPrediction.h

目前支持预测的内容：

- 第一个GameplayAbility的激活（和带有警告的链式激活）

- 触发的事件
- GameplayEffect的应用
  - Attribute修改（除了：Execution目前无法预测，仅Modifier的修改支持预测）
  - GameplayTag修改

- GameplayCue事件(既包括来自预测的“GameplayEffect”)
- 蒙太奇（支持预测和同步纠正）
- 移动（内置于UE的“UCharacterMovement”)

不支持预测的内容：

- GameplayEffect移除
- GameplayEffect周期效果（dots ticking)















