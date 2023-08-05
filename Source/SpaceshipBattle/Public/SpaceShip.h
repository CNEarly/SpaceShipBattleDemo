//预处理
#pragma once//保证头文件只被编译一次
#include "CoreMinimal.h"//包含一套来自UE4核心编程环境的普遍存在类型
#include "GameFramework/Pawn.h"//在新建类的时候选择了以Pawn作为父类（所以这里保存的就是Pawn源代码的头文件）
#include "SpaceShip.generated.h"//与反射机制有关（必须放在所有头文件的最下方）
//前向声明
class USphereComponent;//球体碰撞
class UCameraComponent;//摄像机
class USpringArmComponent;//弹簧臂
class ABullet;//子弹类
class USoundCue;//音效
//战机类
UCLASS()
class SPACESHIPBATTLE_API ASpaceShip : public APawn
{
	GENERATED_BODY()
public:
	//构造函数声明
	ASpaceShip();
protected:
	//球体碰撞组件变量
	UPROPERTY(VisibleAnywhere,Category="Component")
	USphereComponent* CollisionComp;
	//网格体组件变量
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* ShipSM;
	//摄像机组件变量
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComp;
	//弹簧臂组件变量
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComp;
	//玩家控制器类变量
	APlayerController* PC;
	//子弹类型变量
	UPROPERTY(EditAnywhere,Category="Fire")
	TSubclassOf<ABullet> Bullet;
	//子弹发射位置组件变量
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SpawnPoint;
	//战机速度变量
	UPROPERTY(EditAnywhere,Category="Move")
	float Speed;
	//射击间隔时间管理器变量
	FTimerHandle TimerHandle_BetweenShot;
	//游戏开始函数声明
	virtual void BeginPlay() override;
	//射击间隔变量
	UPROPERTY(EditAnywhere, Category = "Fire")
	float TimeBetweenShot;
	//重启游戏时间管理器变量
	FTimerHandle TimerHandle_Restart;
	//阵亡音效变量
	UPROPERTY(EditAnywhere,Category="Sound")
	USoundCue* GameOverCue;
	//射击音效变量
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* ShootCue;
	//推进粒子组件变量
	UPROPERTY(VisibleAnywhere,Category="Component")
	UParticleSystemComponent* ThrusterParticleComp;
	//爆炸粒子变量
	UPROPERTY(EditAnywhere,Category="Particle")
	UParticleSystem* ExplosionParticle;
	//阵亡变量（布尔）
	bool bDead;
	//上下移动变量（布尔）
	bool bUpMove;
	//左右移动变量（布尔）
	bool bRightMove;
	//朝向光标函数实现
	void LookAtCursor();
	//上下移动函数实现
	void MoveUp(float Value);
	//左右移动函数实现
	void MoveRight(float Value);
	//移动函数实现
	void Move();
	//开火函数声明
	void Fire();
	//开始开火函数声明
	void StartFire();
	//停止开火函数声明
	void EndFire();
	//重启关卡函数声明
	void RestartLevel();
	//阵亡函数声明
	void OnDeath();
public:	
	//游戏每帧函数声明
	virtual void Tick(float DeltaTime) override;
	//玩家输入函数声明
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//碰撞函数声明
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//获取阵亡状态函数
	FORCEINLINE bool GetBDead() 
	{
		return bDead;//返回阵亡变量
	}
};