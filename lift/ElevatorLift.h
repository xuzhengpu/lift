#pragma once
#include <Windows.h>
#include "Time.h"
constexpr auto Max = 41;;    //楼层数目
enum Status
{
	STOP, // 暂停  
	UP,   // 向上运行
	DOWN  // 向下运行
};
class ElevatorLift
{
    public:
	ElevatorLift();
	~ElevatorLift();
	virtual void action();
	
	void UpdateNowFloor();        //更新当前电梯所在楼层
	void ChangeStatus();         //改变电梯运行状态
	void Run();                  //电梯运行
	void UpdateDestination();    //更新下一站的目的楼层
	bool IsTake();               //查看是否有人乘坐电梯
	bool IsUp();
	bool IsDown();
    private:
		Status status;
		Status oldstatus;
		bool  Up[100];                 //电梯上行时的停留楼层记录
		bool  Down[100];               //电梯下行时的停留楼层记录
		unsigned  int   NextFloor;    //电梯下一次需要停留的楼层
		unsigned  int   NowFloor;     //当前电梯所在楼层
		unsigned  int  speed;         //电梯当前运行的速度
		double  elevation;            //电梯当前的高度
		double  hight;                //电梯所在大楼的楼层高度
		Time NextStart;               //电梯停靠以后下一次的启动时间
		unsigned int StopTime;        //电梯停靠的时间

};

