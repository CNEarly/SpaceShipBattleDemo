//Ԥ����
#include "Public/EnemySpawner.h"//���ɵ�����
#include "Components/BoxComponent.h"//������ײ
#include "Kismet/KismetMathLibrary.h"//��ѧ��
#include "Kismet/GameplayStatics.h"//��Ϸ״̬
#include "Public/SpaceShip.h"//ս����
#include "Engine/World.h"//����
#include "Public/Enemy.h"//������
#include "TimerManager.h"//ʱ�������
//���캯��ʵ��
AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;//����tick����

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));//ʵ������ײ���
	RootComponent = SpawnArea;//���ø����
	SpawnInterval = 2.0f;//�������ɼ��Ϊ2s
	MaxEnemyNum = 30;//����������Ϊ30
	CurrentEnemyCount = 0;//��ǰ���˼���Ϊ0
}
//��Ϸ��ʼ����ʵ��
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();	
	SpaceShip=Cast<ASpaceShip>( UGameplayStatics::GetPlayerPawn(this,0));//ս�����ͼ��
	GetWorldTimerManager().SetTimer(TimerHandle_Spawn,this,&AEnemySpawner::SpawnEnemy,SpawnInterval,true,0.0f);//�����������ɶ�ʱ��
}
//��ȡ����λ�ú���ʵ��
FVector AEnemySpawner::GetGenerateLocation()
{
	float Distance=0;//��������λ�������λ�þ������
	FVector Location;//��������λ�ñ���
	while (Distance < MinimumDistanceToPlayer)//��������λ�������λ�þ���С�ڵ����������С����
	{
		Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->Bounds.Origin, SpawnArea->Bounds.BoxExtent);//�����ڻ�ȡ�������
		Distance = (Location - SpaceShip->GetActorLocation()).Size();//�������
	}
	return Location;//��������λ��
}
//���ɵ��˺���ʵ��
void AEnemySpawner::SpawnEnemy()
{
	if (SpaceShip->GetBDead() == false&&CurrentEnemyCount<MaxEnemyNum)//ս��δ�����ҵ�ǰ���˼���С�����
	{
		FActorSpawnParameters SpawnParameters;//���ɷ�Χ����
		GetWorld()->SpawnActor<AEnemy>(Enemy, GetGenerateLocation(), FRotator::ZeroRotator, SpawnParameters);//���ɵ���
		CurrentEnemyCount++;//��ǰ���˼���+1
	}
}
//��Ϸÿ֡����ʵ��
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//���ٵ�����������ʵ��
void AEnemySpawner::DecreaseEnemyCount()
{
	if (CurrentEnemyCount > 0)//��������������1ʱ
	{
		CurrentEnemyCount--;//��ǰ��������-1
		UE_LOG(LogTemp,Warning,TEXT("%s"),*FString::SanitizeFloat(CurrentEnemyCount));//��ӡ��־��¼��������
	}
}