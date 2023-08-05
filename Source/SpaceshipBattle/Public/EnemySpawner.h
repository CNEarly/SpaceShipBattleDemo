//Ԥ����
#pragma once//����һ��
#include "CoreMinimal.h"//���ı�̻���
#include "GameFramework/Actor.h"//ActorԴ����
#include "EnemySpawner.generated.h"//�������
//ǰ������
class AEnemy;//������
class UBoxComponent;//������ײ
class ASpaceShip;//ս����
//������
UCLASS()
class SPACESHIPBATTLE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
public:	
	//���캯������
	AEnemySpawner();
protected:
	//��Ϸ��ʼ��������
	virtual void BeginPlay() override;
	//�������ͱ���
	UPROPERTY(EditAnywhere,Category="Enemy")
	TSubclassOf<AEnemy> Enemy;
	//������ײ�������
	UPROPERTY(VisibleAnywhere,Category="Component")
	UBoxComponent* SpawnArea;
	//��ȡ����λ�ú�������
	FVector GetGenerateLocation();
	//�������С�������
	float MinimumDistanceToPlayer = 1200.0f;
	//ս����
	ASpaceShip* SpaceShip;
	//���ɵ��˺�������
	void SpawnEnemy();
	//���ɵ���ʱ�����������
	FTimerHandle TimerHandle_Spawn;
	//���ɵ��˼������
	float SpawnInterval;
	//��������������
	UPROPERTY(EditAnywhere,Category="Spawn")
	int MaxEnemyNum;
	//��ǰ������������
	int CurrentEnemyCount;
public:	
	//��Ϸÿ֡��������
	virtual void Tick(float DeltaTime) override;
	//���ٵ���������������
	void DecreaseEnemyCount();
};
