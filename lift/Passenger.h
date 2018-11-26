#pragma once
#include <stdlib.h>
#include "Time.h"
#include <Windows.h>
#include "ElevatorLift.h"
#include <time.h>
class Passenger
{

    public:
	Passenger();
	Passenger( int M, int L,ElevatorLift *E[],Time *tm )        //构造函数
	{
		srand((int)time(0));
		NextFloor= (rand() % (40 - 1)) + 1 + 1;  //随机生成目标楼层
		status=LEAVE;                            //状态为离开状态
		NowFloor = 1;                            //初始楼层为1
		WaitTime = 5;                           //乘客初次等待时间
		Total =0;                                //总计等待时间
		times = L+1;                             //总乘梯次数  
		nowtime = tm;
		NextTime = (*nowtime + WaitTime);           //设定下一次乘梯的时间
		for (int i = 0; i < 10; i++)
		{
			e[i] = E[i];
		}
	}
	~Passenger();
	void action();                             //乘客的活动
	//unsigned int GetNowFloor();                //获得当前所有电梯的状态
	unsigned  int Select();                    //决策选乘的电梯组
	char * GetStatus();
   //  private:
		enum Status
	{
		TAKE,     // 乘坐  
		LEAVE,    // 离开
		WAIT,     // 等待
		OVER      // 停止乘梯活动
	};
	Status status;                     //乘客状态
	int WaitTime;             //乘客初次等待时间
	int NowFloor;             //当前楼层
	int NextFloor;            //目标楼层
	int which;               //乘坐的电梯
    long Total;                        //总计等待时间   （单位：秒)
	unsigned int times;                //总乘梯次数
	Time  NextTime;                    //下一次乘梯时间
	Time *nowtime;
	ElevatorLift * e[10];              //电梯的指针
	char str[10];
};

