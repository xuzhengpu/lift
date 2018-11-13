#pragma once

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
	int GetNext();               //取得下一次停靠楼层
	Status GetStatus();         // 取得电梯目前运行状态
	void Change();             //改变电梯运行方向
	void UpdateNowFloor();
	void ChangeStatus();
	void Run();
	void UpdateDestination();
    private:
		Status status;
		bool  Up[41];                 //电梯上行时的停留楼层记录
		bool  Down[41];               //电梯下行时的停留楼层记录
		unsigned  int   NextFloor;    //电梯下一次需要停留的楼层
		unsigned  int   NowFloor;     //当前电梯所在楼层
		unsigned  int  speed;         //电梯当前运行的速度
		double  elevation;            //电梯当前的高度
		double  hight;                //电梯所在大楼的楼层高度
};

