//预处理
#pragma once//编译一次
#include "CoreMinimal.h"//核心编程环境
#include "GameFramework/Actor.h"//Actor源代码
#include "EnemySpawner.generated.h"//反射机制
//前向声明
class AEnemy;//敌人类
class UBoxComponent;//盒体碰撞
class ASpaceShip;//战机类
//生成类
UCLASS()
class SPACESHIPBATTLE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
public:	
	//构造函数声明
	AEnemySpawner();
protected:
	//游戏开始函数声明
	virtual void BeginPlay() override;
	//敌人类型变量
	UPROPERTY(EditAnywhere,Category="Enemy")
	TSubclassOf<AEnemy> Enemy;
	//盒体碰撞组件变量
	UPROPERTY(VisibleAnywhere,Category="Component")
	UBoxComponent* SpawnArea;
	//获取生成位置函数声明
	FVector GetGenerateLocation();
	//与玩家最小距离变量
	float MinimumDistanceToPlayer = 1200.0f;
	//战机类
	ASpaceShip* SpaceShip;
	//生成敌人函数声明
	void SpawnEnemy();
	//生成敌人时间管理器变量
	FTimerHandle TimerHandle_Spawn;
	//生成敌人间隔变量
	float SpawnInterval;
	//最大敌人数量变量
	UPROPERTY(EditAnywhere,Category="Spawn")
	int MaxEnemyNum;
	//当前敌人数量变量
	int CurrentEnemyCount;
public:	
	//游戏每帧函数声明
	virtual void Tick(float DeltaTime) override;
	//减少敌人数量函数声明
	void DecreaseEnemyCount();
};
