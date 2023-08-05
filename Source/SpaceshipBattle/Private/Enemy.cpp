//预处理
#include "Public/Enemy.h"//敌人类
#include "Components/SphereComponent.h"//球体碰撞
#include "Components/StaticMeshComponent.h"//网格体
#include "Kismet/GameplayStatics.h"//游戏状态
#include "Public/SpaceShip.h"//战机类
#include "Kismet/KismetMathLibrary.h"//数学库
#include "Public/ShipGameMode.h"//战机游戏模式类
#include "Public/EnemySpawner.h"//生成类
#include "Particles/ParticleSystem.h"//粒子特效
//构造函数实现
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;//开启tick函数

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));//实例化碰撞组件
	RootComponent = CollisionComp;//设置根组件

	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));//实例化网格体组件
	ShipSM->SetupAttachment(RootComponent);//绑定根组件
}
//游戏开始函数实现
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SpaceShip= Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this,0));//战机类型检测
	SetColor();//设置敌人颜色
	MyGameMode= Cast<AShipGameMode>(UGameplayStatics::GetGameMode(this));//游戏模式类型检测
	TArray<AActor*> EnemySpawnerArray;//敌人生成数组
	UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawner::StaticClass(), EnemySpawnerArray);//获取敌人类的所有对象
	EnemySpawner = Cast<AEnemySpawner>(EnemySpawnerArray[0]);//生成敌人类型检测
}
//移动至战机函数实现
void AEnemy::MoveTowardsPlayer(float DeltaTime)
{
	FVector Direction = (SpaceShip->GetActorLocation() - GetActorLocation()).GetSafeNormal();//获取玩家方向
	AddActorWorldOffset(Direction*Speed*DeltaTime, true);//设置敌人的位移
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), SpaceShip->GetActorLocation()));//设置敌人的旋转
}
//阵亡函数实现
void AEnemy::OnDeath()
{
	MyGameMode->IncreaseScore();//游戏模式类调用分数增加函数
	EnemySpawner->DecreaseEnemyCount();//敌人生成类调用减少敌人计数函数
	SpawnExplosion();//生成爆炸
	Destroy();//销毁敌人
}
//游戏每帧函数实现
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpaceShip->GetBDead() == false)//战机未阵亡
	{
		MoveTowardsPlayer(DeltaTime);//移动至战机位置
	}
}
//玩家输入函数实现
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}