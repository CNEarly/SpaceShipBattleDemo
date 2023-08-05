//预处理
#pragma once//编译一次
#include "CoreMinimal.h"//核心编程环境
#include "GameFramework/GameModeBase.h"//GameModeBase源代码
#include "ShipGameMode.generated.h"//反射机制
//战机游戏模式类
UCLASS()
class SPACESHIPBATTLE_API AShipGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	//构造函数声明
	AShipGameMode();
	//分数变量
	UPROPERTY(BlueprintReadOnly)
	int Score;
public:
	//增加敌人数量函数声明
	void IncreaseScore();
};