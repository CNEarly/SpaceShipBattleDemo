//预处理
#include "Public/Bullet.h"//子弹类
#include "Components/StaticMeshComponent.h"//网格体
#include "Components/SceneComponent.h"//场景
#include "GameFramework/ProjectileMovementComponent.h"//发射物移动
#include "Public/Enemy.h"//敌人类
#include "Engine/BlockingVolume.h"//阻挡体积
#include "Kismet/GameplayStatics.h"//游戏状态
//构造函数实现
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;//开启tick函数

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));//实例化根组件
	RootComponent = RootComp;//设置根组件
	BulletSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletSM"));//实例化网格体组件
	BulletSM->SetupAttachment(RootComponent);//绑定根组件
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));//实例化发射物移动组件
}
//游戏开始函数实现
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}
//游戏每帧函数实现
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//碰撞函数实现
void ABullet::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AEnemy* Enemy= Cast<AEnemy>(OtherActor);//碰撞检测敌人类型
	if (Enemy)//敌人为真 
	{
		Enemy->OnDeath();//敌人调用阵亡函数
		Destroy();//子弹销毁
	}
	else if (Cast<ABlockingVolume>(OtherActor))//碰撞检测其他类型
	{
		Destroy();//子弹销毁
	}

}