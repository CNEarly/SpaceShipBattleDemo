//预处理
#include "Public/EnemySpawner.h"//生成敌人类
#include "Components/BoxComponent.h"//盒体碰撞
#include "Kismet/KismetMathLibrary.h"//数学库
#include "Kismet/GameplayStatics.h"//游戏状态
#include "Public/SpaceShip.h"//战机类
#include "Engine/World.h"//世界
#include "Public/Enemy.h"//敌人类
#include "TimerManager.h"//时间管理器
//构造函数实现
AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;//开启tick函数

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));//实例化碰撞组件
	RootComponent = SpawnArea;//设置根组件
	SpawnInterval = 2.0f;//敌人生成间隔为2s
	MaxEnemyNum = 30;//最大敌人数量为30
	CurrentEnemyCount = 0;//当前敌人计数为0
}
//游戏开始函数实现
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();	
	SpaceShip=Cast<ASpaceShip>( UGameplayStatics::GetPlayerPawn(this,0));//战机类型检测
	GetWorldTimerManager().SetTimer(TimerHandle_Spawn,this,&AEnemySpawner::SpawnEnemy,SpawnInterval,true,0.0f);//开启敌人生成定时器
}
//获取生成位置函数实现
FVector AEnemySpawner::GetGenerateLocation()
{
	float Distance=0;//敌人生成位置与玩家位置距离变量
	FVector Location;//敌人生成位置变量
	while (Distance < MinimumDistanceToPlayer)//敌人生成位置与玩家位置距离小于敌人与玩家最小距离
	{
		Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->Bounds.Origin, SpawnArea->Bounds.BoxExtent);//盒体内获取随机坐标
		Distance = (Location - SpaceShip->GetActorLocation()).Size();//计算距离
	}
	return Location;//返回生成位置
}
//生成敌人函数实现
void AEnemySpawner::SpawnEnemy()
{
	if (SpaceShip->GetBDead() == false&&CurrentEnemyCount<MaxEnemyNum)//战机未阵亡且当前敌人计数小于最大
	{
		FActorSpawnParameters SpawnParameters;//生成范围变量
		GetWorld()->SpawnActor<AEnemy>(Enemy, GetGenerateLocation(), FRotator::ZeroRotator, SpawnParameters);//生成敌人
		CurrentEnemyCount++;//当前敌人计数+1
	}
}
//游戏每帧函数实现
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//减少敌人数量函数实现
void AEnemySpawner::DecreaseEnemyCount()
{
	if (CurrentEnemyCount > 0)//当敌人数量大于1时
	{
		CurrentEnemyCount--;//当前敌人数量-1
		UE_LOG(LogTemp,Warning,TEXT("%s"),*FString::SanitizeFloat(CurrentEnemyCount));//打印日志记录敌人数量
	}
}