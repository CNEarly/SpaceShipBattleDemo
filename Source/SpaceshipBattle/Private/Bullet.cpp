//Ԥ����
#include "Public/Bullet.h"//�ӵ���
#include "Components/StaticMeshComponent.h"//������
#include "Components/SceneComponent.h"//����
#include "GameFramework/ProjectileMovementComponent.h"//�������ƶ�
#include "Public/Enemy.h"//������
#include "Engine/BlockingVolume.h"//�赲���
#include "Kismet/GameplayStatics.h"//��Ϸ״̬
//���캯��ʵ��
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;//����tick����

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));//ʵ���������
	RootComponent = RootComp;//���ø����
	BulletSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletSM"));//ʵ�������������
	BulletSM->SetupAttachment(RootComponent);//�󶨸����
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));//ʵ�����������ƶ����
}
//��Ϸ��ʼ����ʵ��
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}
//��Ϸÿ֡����ʵ��
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//��ײ����ʵ��
void ABullet::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AEnemy* Enemy= Cast<AEnemy>(OtherActor);//��ײ����������
	if (Enemy)//����Ϊ�� 
	{
		Enemy->OnDeath();//���˵�����������
		Destroy();//�ӵ�����
	}
	else if (Cast<ABlockingVolume>(OtherActor))//��ײ�����������
	{
		Destroy();//�ӵ�����
	}

}