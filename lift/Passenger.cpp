#include "pch.h"
#include "Passenger.h"

Passenger::Passenger()
{
}


Passenger::~Passenger()
{
}

void Passenger::action()
{

	switch (status)
	{

	case  WAIT:
		//当前状态为等待，则查看电梯是否到达当前楼层，将状态置为 “乘坐”
		if (e[which]->NowFloor == NowFloor)
		{
			//如果选定的电梯楼层与乘客所在楼层一致
			if (((NextFloor - NowFloor) > 0 && (e[which]->NextFloor - e[which]->NowFloor) >= 0) ||
				((NextFloor - NowFloor) < 0 && (e[which]->NextFloor - e[which]->NowFloor) <= 0))
			{
				//并且方向一致

				status = TAKE;
				//统计等待

				Total = Total + (*nowtime - NextTime);
				//设定乘坐电梯的目标楼层
				if ((NextFloor - NowFloor) > 0)
				{
					e[which]->InsideUp[NextFloor]++;   //设置目标楼层
					e[which]->Up[this->NowFloor]--;    //撤销呼叫
				}
				else if ((NextFloor - NowFloor) < 0)
				{
					e[which]->InsideDown[NextFloor]++;   //设置目标楼层
					e[which]->Down[this->NowFloor]--;    //撤销呼叫
				}
				else
				{

				}
			}
		}
		break;
	case  TAKE:
		NowFloor = e[which]->NowFloor;        //更新当前乘坐电梯的楼层                               
	   //当前状态为乘坐，则查看是否到达目的楼层 ，将状态置为 “离开”或“停止”
		if (NowFloor == NextFloor)
		{
			times--;
			switch (times)
			{
			case 0:
				status = OVER;
				break;
			case 1:
				status = LEAVE;
				NextFloor = 1;
				NextTime = (*nowtime + 10);
				break;
			default:
				status = LEAVE;
				srand((int)time(0));
				//设定新的目标楼层
				int temp = ((rand() % 40) + 1);
				while (temp == NowFloor)    //如果取出的数是当前楼层，则重新取随机数，直到不同
				{
					temp = ((rand() % 40) + 1);
				}
				NextFloor = temp;
				NextTime = (*nowtime + 15);                           //生成下一次乘梯时间
				break;
			}


		}
		break;
	case LEAVE:
		//当前状态为离开，则查看是否到下次开始乘梯的时间 ，将状态置为 “等待”
		
		if (nowtime->second == NextTime.second && nowtime->minute == NextTime.minute &&nowtime->hour == NextTime.hour)
		{
			//改变状态
			status = WAIT;
			//选择乘坐的电梯组
			which = 0;
			//设置电梯停靠楼层
			if ((NextFloor - NowFloor) > 0)
			{
				e[which]->Up[this->NowFloor] += 1;
			}
			else
			{
				e[which]->Down[this->NowFloor] += 1;
			}
		}
		break;
	case OVER:
		break;
	}

}

unsigned int Passenger::Select()
{
	int select[10] = { 0 };        //设定决策权重数组
	select[0] += 1;
	select[1] += 1;
	//如果当前楼层与目标楼层为1,25-40
	if ((25 <= NowFloor <= 40 || NowFloor == 1) && (25 <= NextFloor <= 40 || NextFloor == 1))
	{
		select[2] += 1;
		select[3] += 1;
	}
	//如果当前楼层与目标楼层为1-25
	if ((1 <= NowFloor <= 25) && (1 <= NextFloor <= 25))
	{
		select[4] += 1;
		select[5] += 1;
	}
	//如果当前楼层与目标楼层为偶数
	if ((NowFloor % 2 == 0 || NowFloor == 1) && (NextFloor % 2 == 0 || NextFloor == 1))
	{
		select[6] += 1;
		select[7] += 1;
	}
	//如果当前楼层与目标楼层为奇数
	if ((NowFloor % 2 == 1) && (NextFloor % 2 == 1))
	{
		select[8] += 1;
		select[9] += 1;
	}

	// 进一步选择
	int direction = NextFloor - NowFloor;  //设定乘梯方向  >0 向上 <0向下
	for (int i = 0; i < 10; i++)
	{
		//在满足条件的电梯中选择
		if (select[i])
		{
			//电梯运行方向与乘客方向一致向上
			if ((e[i]->NextFloor - e[i]->NowFloor) >= 0 && direction > 0)
			{
				//并且电梯楼层低于乘客楼层
				if (e[i]->NowFloor < NowFloor)
				{
					select[i] += (NowFloor - e[i]->NowFloor);      //设置权重为距离
					//数值越大,电梯位置距离乘客越远
				}

			}
			else if ((e[i]->NextFloor - e[i]->NowFloor) <= 0 && direction < 0)
			{
				// 电梯运行方向与乘客方向一致向下
				//并且电梯楼层高于乘客所在楼层
				if (e[i]->NowFloor > NowFloor)
				{
					select[i] += (e[i]->NowFloor - NowFloor);     //设置权重
				}
			}
			else
			{
			}

		}
	}
	//在select数组中，数值越小，代表可选择电梯中，电梯位置距离乘客越近
	//在select数组中取最小非零值的下标，即为最优选择电梯
	int min = 0;
	for (int i = 1; i < 10; i++)
	{
		if (select[i] > 0 && select[min] > select[i])
		{
			min = i;
		}
	}
	return min;
}

char * Passenger::GetStatus()
{
	switch (status)
	{

	case  WAIT:
		strcpy_s(str, "等待");
		break;
	case  TAKE:
		strcpy_s(str, "乘坐");
		break;
	case LEAVE:
		strcpy_s(str, "离开");
		break;
	case OVER:
		strcpy_s(str, "结束");
		break;
	}
	return str;
}

