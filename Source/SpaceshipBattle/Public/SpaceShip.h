//Ԥ����
#pragma once//��֤ͷ�ļ�ֻ������һ��
#include "CoreMinimal.h"//����һ������UE4���ı�̻������ձ��������
#include "GameFramework/Pawn.h"//���½����ʱ��ѡ������Pawn��Ϊ���ࣨ�������ﱣ��ľ���PawnԴ�����ͷ�ļ���
#include "SpaceShip.generated.h"//�뷴������йأ������������ͷ�ļ������·���
//ǰ������
class USphereComponent;//������ײ
class UCameraComponent;//�����
class USpringArmComponent;//���ɱ�
class ABullet;//�ӵ���
class USoundCue;//��Ч
//ս����
UCLASS()
class SPACESHIPBATTLE_API ASpaceShip : public APawn
{
	GENERATED_BODY()
public:
	//���캯������
	ASpaceShip();
protected:
	//������ײ�������
	UPROPERTY(VisibleAnywhere,Category="Component")
	USphereComponent* CollisionComp;
	//�������������
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* ShipSM;
	//������������
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComp;
	//���ɱ��������
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComp;
	//��ҿ����������
	APlayerController* PC;
	//�ӵ����ͱ���
	UPROPERTY(EditAnywhere,Category="Fire")
	TSubclassOf<ABullet> Bullet;
	//�ӵ�����λ���������
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SpawnPoint;
	//ս���ٶȱ���
	UPROPERTY(EditAnywhere,Category="Move")
	float Speed;
	//������ʱ�����������
	FTimerHandle TimerHandle_BetweenShot;
	//��Ϸ��ʼ��������
	virtual void BeginPlay() override;
	//����������
	UPROPERTY(EditAnywhere, Category = "Fire")
	float TimeBetweenShot;
	//������Ϸʱ�����������
	FTimerHandle TimerHandle_Restart;
	//������Ч����
	UPROPERTY(EditAnywhere,Category="Sound")
	USoundCue* GameOverCue;
	//�����Ч����
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* ShootCue;
	//�ƽ������������
	UPROPERTY(VisibleAnywhere,Category="Component")
	UParticleSystemComponent* ThrusterParticleComp;
	//��ը���ӱ���
	UPROPERTY(EditAnywhere,Category="Particle")
	UParticleSystem* ExplosionParticle;
	//����������������
	bool bDead;
	//�����ƶ�������������
	bool bUpMove;
	//�����ƶ�������������
	bool bRightMove;
	//�����꺯��ʵ��
	void LookAtCursor();
	//�����ƶ�����ʵ��
	void MoveUp(float Value);
	//�����ƶ�����ʵ��
	void MoveRight(float Value);
	//�ƶ�����ʵ��
	void Move();
	//����������
	void Fire();
	//��ʼ����������
	void StartFire();
	//ֹͣ����������
	void EndFire();
	//�����ؿ���������
	void RestartLevel();
	//������������
	void OnDeath();
public:	
	//��Ϸÿ֡��������
	virtual void Tick(float DeltaTime) override;
	//������뺯������
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//��ײ��������
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//��ȡ����״̬����
	FORCEINLINE bool GetBDead() 
	{
		return bDead;//������������
	}
};