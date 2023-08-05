//Ԥ����
#include "Public/Enemy.h"//������
#include "Components/SphereComponent.h"//������ײ
#include "Components/StaticMeshComponent.h"//������
#include "Kismet/GameplayStatics.h"//��Ϸ״̬
#include "Public/SpaceShip.h"//ս����
#include "Kismet/KismetMathLibrary.h"//��ѧ��
#include "Public/ShipGameMode.h"//ս����Ϸģʽ��
#include "Public/EnemySpawner.h"//������
#include "Particles/ParticleSystem.h"//������Ч
//���캯��ʵ��
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;//����tick����

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));//ʵ������ײ���
	RootComponent = CollisionComp;//���ø����

	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipSM"));//ʵ�������������
	ShipSM->SetupAttachment(RootComponent);//�󶨸����
}
//��Ϸ��ʼ����ʵ��
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SpaceShip= Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this,0));//ս�����ͼ��
	SetColor();//���õ�����ɫ
	MyGameMode= Cast<AShipGameMode>(UGameplayStatics::GetGameMode(this));//��Ϸģʽ���ͼ��
	TArray<AActor*> EnemySpawnerArray;//������������
	UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawner::StaticClass(), EnemySpawnerArray);//��ȡ����������ж���
	EnemySpawner = Cast<AEnemySpawner>(EnemySpawnerArray[0]);//���ɵ������ͼ��
}
//�ƶ���ս������ʵ��
void AEnemy::MoveTowardsPlayer(float DeltaTime)
{
	FVector Direction = (SpaceShip->GetActorLocation() - GetActorLocation()).GetSafeNormal();//��ȡ��ҷ���
	AddActorWorldOffset(Direction*Speed*DeltaTime, true);//���õ��˵�λ��
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), SpaceShip->GetActorLocation()));//���õ��˵���ת
}
//��������ʵ��
void AEnemy::OnDeath()
{
	MyGameMode->IncreaseScore();//��Ϸģʽ����÷������Ӻ���
	EnemySpawner->DecreaseEnemyCount();//������������ü��ٵ��˼�������
	SpawnExplosion();//���ɱ�ը
	Destroy();//���ٵ���
}
//��Ϸÿ֡����ʵ��
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpaceShip->GetBDead() == false)//ս��δ����
	{
		MoveTowardsPlayer(DeltaTime);//�ƶ���ս��λ��
	}
}
//������뺯��ʵ��
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}