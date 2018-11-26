#pragma once
#include <Windows.h>
#include "Time.h"
constexpr auto Max = 41;   //楼层数目

class ElevatorLift
{
    public:
		
	ElevatorLift( int S, int K, int T,Time *tm);
	~ElevatorLift();
	virtual void action();
    char * GetStatus();
	void UpdateNowFloor();        //更新当前电梯所在楼层
	void ChangeStatus();          //改变电梯运行状态
	void Run();                   //电梯运行
	void UpdateDestination();     //更新下一站的目的楼层
	int  call();                  //查看是否有人呼叫电梯
	int IsTake();

	bool IsUp();
	bool IsDown();
   // private:
		enum Status
		{
			STOP,    // 停止  
			UP,      // 向上运行
			DOWN,    // 向下运行
			UPSTOP,  // 上行过程中的暂停
			DOWNSTOP // 下行过程中的暂停
		};
		 Status status;
		 int   NextFloor;    //电梯下一次需要停留的楼层
		 int   NowFloor;     //当前电梯所在楼层
		 int  Up[41];        //电梯外部，记录乘客上行呼叫的楼层   Up[i]的数值代表第i层上行的乘客数量
		 int  Down[41];      //电梯外部，记录乘客下行呼叫的楼层
		 int  InsideUp[41];  //电梯内部，设置乘客上行目的楼层的数组
		 int  InsideDown[41];//电梯内部，设置乘客下行目的楼层的数组
		 int   people;       //当前电梯的人数
		 int   capacity;      //当前电梯的容量
		 float nowfloor;               //用于计算当前楼层
		 float  speed;                 //电梯当前运行的速度
		 long vacant;                  //电梯空闲时间
		 long busy;                    //电梯运行的时间
		 Time NextStart;               //电梯停靠以后下一次的启动时间
		 Time Start;
		 Time Over;
		 Time * nowtime;
		 unsigned int StopTime;        //电梯停靠的时间
		 friend class Passenger;       //将自身数据提供给乘客
		 char str[10];
	
};

