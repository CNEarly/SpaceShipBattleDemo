#include "Public/ShipGameMode.h"//ս����Ϸģʽ��
//���캯��ʵ��
AShipGameMode::AShipGameMode() 
{
	Score = 0;//������ʼ��Ϊ0
}
//���ӵ�����������ʵ��
void AShipGameMode::IncreaseScore()
{
	Score++;//���ܵ��˷�������
}