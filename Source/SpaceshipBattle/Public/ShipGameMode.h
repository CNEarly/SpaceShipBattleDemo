//Ԥ����
#pragma once//����һ��
#include "CoreMinimal.h"//���ı�̻���
#include "GameFramework/GameModeBase.h"//GameModeBaseԴ����
#include "ShipGameMode.generated.h"//�������
//ս����Ϸģʽ��
UCLASS()
class SPACESHIPBATTLE_API AShipGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	//���캯������
	AShipGameMode();
	//��������
	UPROPERTY(BlueprintReadOnly)
	int Score;
public:
	//���ӵ���������������
	void IncreaseScore();
};