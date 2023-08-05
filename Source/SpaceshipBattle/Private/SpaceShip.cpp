//预处理
#include "Public/SpaceShip.h"//战机类
#include "Components/StaticMeshComponent.h"//网格体组件
#include "Components/SphereComponent.h"//球体碰撞组件
#include "Camera/CameraComponent.h"//摄像机组件
#include "GameFramework/PlayerController.h"//玩家控制器
#include "Kismet/KismetMathLibrary.h"//数学库
#include "GameFramework/SpringArmComponent.h"//弹簧臂组件
#include "Public/Misc/App.h"//引擎处理
#include "Engine/World.h"//世界
#include "Public/Bullet.h"//子弹类头文件
#include "Public/Enemy.h"//敌人类头文件
#include "Kismet/GameplayStatics.h"//游戏状态
#include "TimerManager.h"//时间管理器
#include "Sound/SoundCue.h"//音效
#include "Particles/ParticleSystemComponent.h"//粒子特效组件
#include "Particles/ParticleSystem.h"//粒子特效
//构造函数实现
ASpaceShip::ASpaceShip()
{
	PrimaryActorTick.bCanEverTick = true;//开启tick函数

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));//实例化碰撞组件
	RootComponent = CollisionComp;//碰撞组件设置为根组件

	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));//实例化网格体组件
	ShipSM->SetupAttachment(RootComponent);//网格体组件绑定根组件

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));//实例化弹簧臂组件
	SpringArmComp->SetupAttachment(RootComponent);//弹簧臂组件绑定根组件

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));//实例化摄像机组件
	CameraComp->SetupAttachment(SpringArmComp);//摄像机组件绑定弹簧臂组件

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));//实例化发射位置场景组件
	SpawnPoint->SetupAttachment(ShipSM);//发射位置场景组件绑定网格体组件

	ThrusterParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrusterParticle"));//实例化推进器粒子组件
	ThrusterParticleComp->SetupAttachment(RootComponent);//推进器粒子组件绑定根组件

	Speed = 2500.0f;//设置速度
	TimeBetweenShot = 0.2f;//设置发射间隔
	bDead = false;//设置阵亡
}
//游戏开始函数实现
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
	PC =Cast<APlayerController>(GetController());//用变量接收获取到的玩家控制器
	PC->bShowMouseCursor = true;//控制开启显示光标
}
//朝向光标函数实现
void ASpaceShip::LookAtCursor()
{
	FVector MouseLocation, MouseDirection;//光标位置和方向变量
	PC->DeprojectMousePositionToWorld(MouseLocation,MouseDirection);//将光标位置投影到世界
	FVector TargetLocation = FVector(MouseLocation.X, MouseLocation.Y, GetActorLocation().Z);//将光标位置投影到与战机共面
	FRotator Rotator= UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),TargetLocation);//计算旋转值
	SetActorRotation(Rotator);//设置战机旋转
}
//上下移动函数实现
void ASpaceShip::MoveUp(float Value)
{
	if (Value != 0)//上下移动传参非0 
	{
		bUpMove = true;//上下移动为真
	}
	else//上下移动传参为0 
	{
		bUpMove = false;//上下移动为假
	}
	AddMovementInput(FVector::ForwardVector,Value);//添加移动输入
}
//左右移动函数实现
void ASpaceShip::MoveRight(float Value)
{
	if (Value != 0)//左右移动传参非0 
	{
		bRightMove = true;//左右移动为真
	}
	else//左右移动传参为0 
	{
		bRightMove = false;//左右移动为假
	}
	AddMovementInput(FVector::RightVector,Value);//添加移动输入
}
//移动函数实现
void ASpaceShip::Move()
{
	AddActorWorldOffset(ConsumeMovementInputVector()*Speed*FApp::GetDeltaTime(), true);//获取一帧内移动的向量，在位置上增加增量
	//FApp::GetDeltaTime();//获取一帧的时间
}
//开火函数实现
void ASpaceShip::Fire()
{
	if (Bullet&&!bDead)//子弹为真且为阵亡
	{
		FActorSpawnParameters SpawnParams;//发射范围参数变量
		GetWorld()->SpawnActor<ABullet>(Bullet, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation(), SpawnParams);//发射子弹类
		if (ShootCue)//射击音效为真
		{
			UGameplayStatics::PlaySoundAtLocation(this, ShootCue, GetActorLocation());//播放射击音效
		}
	}
}
//开始开火函数实现
void ASpaceShip::StartFire()
{
	GetWorldTimerManager().SetTimer(TimerHandle_BetweenShot, this, &ASpaceShip::Fire, TimeBetweenShot, true, 0.0f);//开火间隔定时器开启
}
//停止开火函数实现
void ASpaceShip::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BetweenShot);//开火间隔定时器停止
}
//重启关卡函数实现
void ASpaceShip::RestartLevel()
{
	UGameplayStatics::OpenLevel(this,"MainMap");//重新打开当前关卡
}
//阵亡函数实现
void ASpaceShip::OnDeath()
{
	bDead = true;//阵亡设置为真
	CollisionComp->SetVisibility(false,true);
	if (GameOverCue)//战败音效为真
	{
		UGameplayStatics::PlaySoundAtLocation(this, GameOverCue, GetActorLocation());//播放战败音效
	}
	if (ExplosionParticle)//爆炸特效为真
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation(), FRotator::ZeroRotator, true);//播放爆炸特效
		GetWorldTimerManager().SetTimer(TimerHandle_Restart, this, &ASpaceShip::RestartLevel, 2.0f, false);//重启游戏定时器开启
	}
}
//游戏每帧函数实现
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bDead)//未阵亡
	{
		if (bUpMove || bRightMove)//上下移动或者左右移动
		{
			ThrusterParticleComp->Activate();//推机器粒子特效开启
		}
		else//未上下移动或者左右移动
		{
			ThrusterParticleComp->Deactivate();//推机器粒子特效结束
		}

		LookAtCursor();//调用朝向光标函数
		Move();//调用移动函数
	}
	else //阵亡
	{
		ThrusterParticleComp->Deactivate();//推机器粒子特效结束
	}
}
//玩家输入函数实现
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp",this,&ASpaceShip::MoveUp);//轴映射上下移动
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceShip::MoveRight);//轴映射左右移动

	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&ASpaceShip::StartFire);//操作映射按键开火
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASpaceShip::EndFire);//操作映射松键停火
}
//碰撞函数实现
void ASpaceShip::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);//碰撞检测敌人类型
	if (Enemy)//敌人为真 
	{
		Enemy->Destroy();//敌人销毁
		OnDeath();//战机调用阵亡函数
		//Destroy();战机销毁
	}
}