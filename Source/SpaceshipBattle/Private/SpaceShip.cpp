//Ԥ����
#include "Public/SpaceShip.h"//ս����
#include "Components/StaticMeshComponent.h"//���������
#include "Components/SphereComponent.h"//������ײ���
#include "Camera/CameraComponent.h"//��������
#include "GameFramework/PlayerController.h"//��ҿ�����
#include "Kismet/KismetMathLibrary.h"//��ѧ��
#include "GameFramework/SpringArmComponent.h"//���ɱ����
#include "Public/Misc/App.h"//���洦��
#include "Engine/World.h"//����
#include "Public/Bullet.h"//�ӵ���ͷ�ļ�
#include "Public/Enemy.h"//������ͷ�ļ�
#include "Kismet/GameplayStatics.h"//��Ϸ״̬
#include "TimerManager.h"//ʱ�������
#include "Sound/SoundCue.h"//��Ч
#include "Particles/ParticleSystemComponent.h"//������Ч���
#include "Particles/ParticleSystem.h"//������Ч
//���캯��ʵ��
ASpaceShip::ASpaceShip()
{
	PrimaryActorTick.bCanEverTick = true;//����tick����

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));//ʵ������ײ���
	RootComponent = CollisionComp;//��ײ�������Ϊ�����

	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));//ʵ�������������
	ShipSM->SetupAttachment(RootComponent);//����������󶨸����

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));//ʵ�������ɱ����
	SpringArmComp->SetupAttachment(RootComponent);//���ɱ�����󶨸����

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));//ʵ������������
	CameraComp->SetupAttachment(SpringArmComp);//���������󶨵��ɱ����

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));//ʵ��������λ�ó������
	SpawnPoint->SetupAttachment(ShipSM);//����λ�ó�����������������

	ThrusterParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrusterParticle"));//ʵ�����ƽ����������
	ThrusterParticleComp->SetupAttachment(RootComponent);//�ƽ�����������󶨸����

	Speed = 2500.0f;//�����ٶ�
	TimeBetweenShot = 0.2f;//���÷�����
	bDead = false;//��������
}
//��Ϸ��ʼ����ʵ��
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
	PC =Cast<APlayerController>(GetController());//�ñ������ջ�ȡ������ҿ�����
	PC->bShowMouseCursor = true;//���ƿ�����ʾ���
}
//�����꺯��ʵ��
void ASpaceShip::LookAtCursor()
{
	FVector MouseLocation, MouseDirection;//���λ�úͷ������
	PC->DeprojectMousePositionToWorld(MouseLocation,MouseDirection);//�����λ��ͶӰ������
	FVector TargetLocation = FVector(MouseLocation.X, MouseLocation.Y, GetActorLocation().Z);//�����λ��ͶӰ����ս������
	FRotator Rotator= UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),TargetLocation);//������תֵ
	SetActorRotation(Rotator);//����ս����ת
}
//�����ƶ�����ʵ��
void ASpaceShip::MoveUp(float Value)
{
	if (Value != 0)//�����ƶ����η�0 
	{
		bUpMove = true;//�����ƶ�Ϊ��
	}
	else//�����ƶ�����Ϊ0 
	{
		bUpMove = false;//�����ƶ�Ϊ��
	}
	AddMovementInput(FVector::ForwardVector,Value);//����ƶ�����
}
//�����ƶ�����ʵ��
void ASpaceShip::MoveRight(float Value)
{
	if (Value != 0)//�����ƶ����η�0 
	{
		bRightMove = true;//�����ƶ�Ϊ��
	}
	else//�����ƶ�����Ϊ0 
	{
		bRightMove = false;//�����ƶ�Ϊ��
	}
	AddMovementInput(FVector::RightVector,Value);//����ƶ�����
}
//�ƶ�����ʵ��
void ASpaceShip::Move()
{
	AddActorWorldOffset(ConsumeMovementInputVector()*Speed*FApp::GetDeltaTime(), true);//��ȡһ֡���ƶ�����������λ������������
	//FApp::GetDeltaTime();//��ȡһ֡��ʱ��
}
//������ʵ��
void ASpaceShip::Fire()
{
	if (Bullet&&!bDead)//�ӵ�Ϊ����Ϊ����
	{
		FActorSpawnParameters SpawnParams;//���䷶Χ��������
		GetWorld()->SpawnActor<ABullet>(Bullet, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation(), SpawnParams);//�����ӵ���
		if (ShootCue)//�����ЧΪ��
		{
			UGameplayStatics::PlaySoundAtLocation(this, ShootCue, GetActorLocation());//���������Ч
		}
	}
}
//��ʼ������ʵ��
void ASpaceShip::StartFire()
{
	GetWorldTimerManager().SetTimer(TimerHandle_BetweenShot, this, &ASpaceShip::Fire, TimeBetweenShot, true, 0.0f);//��������ʱ������
}
//ֹͣ������ʵ��
void ASpaceShip::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BetweenShot);//��������ʱ��ֹͣ
}
//�����ؿ�����ʵ��
void ASpaceShip::RestartLevel()
{
	UGameplayStatics::OpenLevel(this,"MainMap");//���´򿪵�ǰ�ؿ�
}
//��������ʵ��
void ASpaceShip::OnDeath()
{
	bDead = true;//��������Ϊ��
	CollisionComp->SetVisibility(false,true);
	if (GameOverCue)//ս����ЧΪ��
	{
		UGameplayStatics::PlaySoundAtLocation(this, GameOverCue, GetActorLocation());//����ս����Ч
	}
	if (ExplosionParticle)//��ը��ЧΪ��
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation(), FRotator::ZeroRotator, true);//���ű�ը��Ч
		GetWorldTimerManager().SetTimer(TimerHandle_Restart, this, &ASpaceShip::RestartLevel, 2.0f, false);//������Ϸ��ʱ������
	}
}
//��Ϸÿ֡����ʵ��
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bDead)//δ����
	{
		if (bUpMove || bRightMove)//�����ƶ����������ƶ�
		{
			ThrusterParticleComp->Activate();//�ƻ���������Ч����
		}
		else//δ�����ƶ����������ƶ�
		{
			ThrusterParticleComp->Deactivate();//�ƻ���������Ч����
		}

		LookAtCursor();//���ó����꺯��
		Move();//�����ƶ�����
	}
	else //����
	{
		ThrusterParticleComp->Deactivate();//�ƻ���������Ч����
	}
}
//������뺯��ʵ��
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp",this,&ASpaceShip::MoveUp);//��ӳ�������ƶ�
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceShip::MoveRight);//��ӳ�������ƶ�

	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&ASpaceShip::StartFire);//����ӳ�䰴������
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASpaceShip::EndFire);//����ӳ���ɼ�ͣ��
}
//��ײ����ʵ��
void ASpaceShip::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);//��ײ����������
	if (Enemy)//����Ϊ�� 
	{
		Enemy->Destroy();//��������
		OnDeath();//ս��������������
		//Destroy();ս������
	}
}