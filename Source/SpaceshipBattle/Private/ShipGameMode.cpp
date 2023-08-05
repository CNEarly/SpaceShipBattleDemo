#include "Public/ShipGameMode.h"//战机游戏模式类
//构造函数实现
AShipGameMode::AShipGameMode() 
{
	Score = 0;//分数初始化为0
}
//增加敌人数量函数实现
void AShipGameMode::IncreaseScore()
{
	Score++;//击败敌人分数增加
}