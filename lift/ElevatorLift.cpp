#include "pch.h"
#include "ElevatorLift.h"


ElevatorLift::ElevatorLift()
{
}


ElevatorLift::~ElevatorLift()
{
}

void ElevatorLift::action()
{
	UpdateNowFloor();    // 更新当前电梯所在楼层
	UpdateDestination(); // 更新电梯下一站的目的楼层
	Status();            // 判断当前电梯状态
	Run();               // 电梯运行
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
		NowFloor = (int)elevation / hight + 1; //电梯所处楼层位置=电梯高度除以楼层高度再加一
	}
	//如果电梯底部与楼层平面的距离大于楼层高度的80%，则说明电梯马上要到达更高一层，  对应电梯上行
	if (ans >= 0.8)
	{
		/*
		 举例说明：elevation=9.9， high=2 fmod(elevation,hight）=1.9>1.8
		 (int)elevation/hight=5 则电梯目前底部靠近六楼
		*/
		NowFloor = (int)elevation / hight + 2;
	}
}

void ElevatorLift::ChangeStatus()
{
	if (status != STOP)   //如果为运行状态，则看是否需要去停下来
	{
		if (NextFloor == NowFloor)
		{
			status = STOP;
			nextstarttime = sys.second + 10;

		}
	}
	else                //如果为暂停状态，则看是否需要去重新启动
	{
		if (nextstarttime == sys)
		{
			status = getfangxiang()
			next = getnextfloor()
		}
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
		elevation = elevation; //如果电梯暂停  则位置保持不变
	}
}
