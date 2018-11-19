#include "pch.h"
#include "ElevatorLift.h"
#include <math.h>

ElevatorLift::ElevatorLift()
{
}


ElevatorLift::~ElevatorLift()
{
}

void ElevatorLift::action()
{
	UpdateNowFloor();       // 更新当前电梯所在楼层
	UpdateDestination();    // 更新电梯下一站的目的楼层
	ChangeStatus();         // 判断改变当前电梯状态
	Run();                  // 电梯运行
}


void ElevatorLift::UpdateNowFloor()
{
	// elevation 代表当前电梯底部的所处高度   hight 代表楼每层的高度
	double ans;
	ans = fmod(elevation, hight) / hight;
	//如果电梯底部与楼层平面的距离小于楼层高度的20%，则说明到达该楼层，  对应电梯下行
	if (ans <= 0.2)
	{

		//举例 elevation =4.1   high=2   fmod(elevation,hight） =0.1< 0.2 
		   //(int)elevation/hight=2 则电梯目前底部靠近三楼
		NowFloor = (int)(elevation / hight) + 1; //电梯所处楼层位置=电梯高度除以楼层高度再加一
	}
	//如果电梯底部与楼层平面的距离大于楼层高度的80%，则说明电梯马上要到达更高一层，  对应电梯上行
	if (ans >= 0.8)
	{
		/*
		 举例说明：elevation=9.9， high=2 fmod(elevation,hight）=1.9>1.8
		 (int)elevation/hight=5 则电梯目前底部靠近六楼
		*/
		NowFloor = (int)(elevation / hight) + 2;
	}
}

void ElevatorLift::ChangeStatus()
{
	if (status != STOP)   //如果为运行状态，则看是否需要去停下来
	{
		if (NextFloor == NowFloor)
		{
			oldstatus = status;  //存储电梯停止前的状态
			status = STOP;	     //改变电梯状态
			if (oldstatus == UP)
				Up[NowFloor] = false;   //	清除记录
			else
			{
				Down[NowFloor] = false;   //清除记录
			}
			if (!IsTake())
			{
				NextFloor = 0;      //电梯停下来以后如没人乘坐电梯，目标楼层置为0  关闭下次启动时间
				NextStart.onoff = false;
			}
			if(NextStart.onoff = true)
			{
				SYSTEMTIME NowTime;
				GetLocalTime(&NowTime);
				Time nowtime(NowTime.wHour,NowTime.wMinute,NowTime.wSecond);
				NextStart=nowtime +  StopTime;
			}
			

		}
	}
	else                //如果为暂停状态，则看是否需要去重新启动
	{
		 //如果目标楼层为0，则说明没人乘坐电梯，不启动
		//如果目标楼层不为0 ，则启动电梯
		if (NextFloor!=0)        
		{
			if (NextStart.onoff == true)     // 如果电梯的目标时间打开
			{
				SYSTEMTIME NowTime;
			GetLocalTime(&NowTime);

			if (NextStart.hour == NowTime.wHour&&NextStart.minute == NowTime.wMinute&&NextStart.second == NowTime.wSecond)
			{  
				//如果时间到了，则改变电梯到运行状态
				status = oldstatus;
				oldstatus = STOP;
				UpdateDestination();  //取得下一次停靠的楼层
			}
			}
			else
			{
				if (NextFloor - NowFloor > 0)
				{
					status = UP;
					NextStart.onoff == true;
				}
				else
				{
					status = DOWN;
					NextStart.onoff == true;
				}
			}
		}
	     //如果电梯记录没有人乘坐，则不改变暂停状态
	}
}

void ElevatorLift::Run()
{
	if (status == UP)      //如果电梯向上运行
	{
		elevation += speed / 10;    //增加电梯高度     
		//speed为电梯每秒的运行速度 ，因为程序间隔0.1秒循环一次，故这里取speed/10，为十分之一秒的速度    

	}
	else if (status == DOWN)   //向下运行
	{
		elevation -= speed / 10;   //
	}
	else
	{  
		                                    // 1.电梯制动
		elevation =( NowFloor - 1)*hight;   // 2.使电梯位置与楼层地面相平
	}
}

void ElevatorLift::UpdateDestination()
{
	if (status == UP)     //如果电梯向上运行，则在上行记录查询下一次停靠位置
	{    
		
		for (int i = 1; i < Max; i++)
		{
			if (Up[i] == true)
			{
				NextFloor = i;
				break;
			}
		}
	}
    else if(status == DOWN)    //如果电梯下行，则在下行记录查询下一次停靠位置
	{
		for (int i = Max; i > 0; i--)
		{
			if (Down[i] == true)
			{
				NextFloor = i;
				break;
			}
		}
	}
	else                    //如果电梯暂停，则在上下记录都查询
	{
		if (!IsTake())    //如果没人乘坐电梯，则目标楼层置为0  并关闭下次开启时间
		{
			NextFloor = 0;
			NextStart.onoff = false;
		}
		if (IsUp() == false && IsDown() == true)    //上行空，下行非空
		{
			for (int i = Max; i > 0; i--)
			{
				if (Down[i] == true)
				{
					NextFloor = i;
					NextStart.onoff = false;    //关闭下次启动时间时间
					break;
				}
			}

		}
		if(IsUp() == true && IsDown() == false)    //上行非空，下行空
		{
			for (int i = 1; i < Max; i++)   
			{
				if (Up[i] == true)
				{
					NextFloor = i;
					NextStart.onoff = false;
					break;
				}
			}
		}
		
	}
}

bool ElevatorLift::IsTake()
{
	for (int i = 1; i < Max; i++)
	{
		if (Up[i] == true || Down[i] == true)
			return true;
	}
	return false;
}

bool ElevatorLift::IsUp()
{
	for (int i = 1; i < Max; i++)
	{
		if (Up[i] == true)
			return true;
	}
	return false;
}

bool ElevatorLift::IsDown()
{
	for (int i = 1; i < 41; i++)
	{
		if (Down[i] == true)
			return true;
	}
	return false;
}