//预处理
#pragma once//编译一次
#include "CoreMinimal.h"//核心编程环境
#include "GameFramework/Actor.h"//Actor源代码
#include "Bullet.generated.h"//反射机制
//前向声明
class UProjectileMovementComponent;//发射物移动
//子弹类
UCLASS()
class SPACESHIPBATTLE_API ABullet : public AActor
{
	GENERATED_BODY()	
public:	
	//构造函数声明
	ABullet();
protected:
	//游戏开始函数声明
	virtual void BeginPlay() override;
	//根组件变量
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* RootComp;
	//网格体组件变量
	UPROPERTY(VisibleAnywhere,Category="Component")
	UStaticMeshComponent* BulletSM;
	//发射物移动组件变量
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UProjectileMovementComponent* ProjectileMovementComp;
public:	
	//游戏每帧函数声明
	virtual void Tick(float DeltaTime) override;
	//碰撞函数声明
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};