//预处理
#pragma once//保证头文件只被编译一次
#include "CoreMinimal.h"//包含一套来自UE4核心编程环境的普遍存在类型
#include "GameFramework/Pawn.h"//在新建类的时候选择了以Pawn作为父类（所以这里保存的就是Pawn源代码的头文件）
#include "Enemy.generated.h"//与反射机制有关（必须放在所有头文件的最下方）
//前向声明
class USphereComponent;//球体碰撞
class ASpaceShip;//战机类
class AShipGameMode;//战机游戏模式类
class AEnemySpawner;//生成类
//敌人类
UCLASS()
class SPACESHIPBATTLE_API AEnemy : public APawn
{
	GENERATED_BODY()
public:
	//构造函数声明
	AEnemy();
protected:
	//球体碰撞组件变量
	UPROPERTY(VisibleAnywhere,Category="Component")
	USphereComponent* CollisionComp;
	//网格体组件变量
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* ShipSM;
	//游戏开始函数声明
	virtual void BeginPlay() override;
	//移动至战机函数声明
	void MoveTowardsPlayer(float DeltaTime);
	//战机类变量
	ASpaceShip* SpaceShip;
	//速度变量
	float Speed = 300.0f;
	//战机游戏模式类变量
	AShipGameMode* MyGameMode;
	//生成类变量
	AEnemySpawner* EnemySpawner;
	//爆炸粒子变量
	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* ExplosionParticle;
	//设置颜色函数声明
	UFUNCTION(BlueprintImplementableEvent)
	void SetColor();
	//生成爆炸函数声明
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnExplosion();
public:	
	//游戏每帧函数声明
	virtual void Tick(float DeltaTime) override;
	//玩家输入函数声明
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//阵亡函数声明
	void OnDeath();
};