//Ԥ����
#pragma once//����һ��
#include "CoreMinimal.h"//���ı�̻���
#include "GameFramework/Actor.h"//ActorԴ����
#include "Bullet.generated.h"//�������
//ǰ������
class UProjectileMovementComponent;//�������ƶ�
//�ӵ���
UCLASS()
class SPACESHIPBATTLE_API ABullet : public AActor
{
	GENERATED_BODY()	
public:	
	//���캯������
	ABullet();
protected:
	//��Ϸ��ʼ��������
	virtual void BeginPlay() override;
	//���������
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* RootComp;
	//�������������
	UPROPERTY(VisibleAnywhere,Category="Component")
	UStaticMeshComponent* BulletSM;
	//�������ƶ��������
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UProjectileMovementComponent* ProjectileMovementComp;
public:	
	//��Ϸÿ֡��������
	virtual void Tick(float DeltaTime) override;
	//��ײ��������
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};