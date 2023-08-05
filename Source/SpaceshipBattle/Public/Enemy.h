//Ԥ����
#pragma once//��֤ͷ�ļ�ֻ������һ��
#include "CoreMinimal.h"//����һ������UE4���ı�̻������ձ��������
#include "GameFramework/Pawn.h"//���½����ʱ��ѡ������Pawn��Ϊ���ࣨ�������ﱣ��ľ���PawnԴ�����ͷ�ļ���
#include "Enemy.generated.h"//�뷴������йأ������������ͷ�ļ������·���
//ǰ������
class USphereComponent;//������ײ
class ASpaceShip;//ս����
class AShipGameMode;//ս����Ϸģʽ��
class AEnemySpawner;//������
//������
UCLASS()
class SPACESHIPBATTLE_API AEnemy : public APawn
{
	GENERATED_BODY()
public:
	//���캯������
	AEnemy();
protected:
	//������ײ�������
	UPROPERTY(VisibleAnywhere,Category="Component")
	USphereComponent* CollisionComp;
	//�������������
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* ShipSM;
	//��Ϸ��ʼ��������
	virtual void BeginPlay() override;
	//�ƶ���ս����������
	void MoveTowardsPlayer(float DeltaTime);
	//ս�������
	ASpaceShip* SpaceShip;
	//�ٶȱ���
	float Speed = 300.0f;
	//ս����Ϸģʽ�����
	AShipGameMode* MyGameMode;
	//���������
	AEnemySpawner* EnemySpawner;
	//��ը���ӱ���
	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* ExplosionParticle;
	//������ɫ��������
	UFUNCTION(BlueprintImplementableEvent)
	void SetColor();
	//���ɱ�ը��������
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnExplosion();
public:	
	//��Ϸÿ֡��������
	virtual void Tick(float DeltaTime) override;
	//������뺯������
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//������������
	void OnDeath();
};