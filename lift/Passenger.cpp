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

			 break;
	     case  TAKE:
			  //更新当前乘坐电梯的楼层                               
			 //当前状态为乘坐，则查看是否到达目的楼层 ，将状态置为 “离开”或“停止”
	         if (GetNowFloor() == NextFloor)
			 {   
				 times--;
				 switch (times)
				 {
				 case 0:
					 status = OVER;
				 case 1:
					 status = LEAVE;
					 NextFloor = 1;
				 default :
					 status = LEAVE;
					 NextFloor = (rand() % (40 - 1)) + 1 + 1;
				 }


		     }
			 break;
		 case LEAVE:
			 //当前状态为离开，则查看是否到下次开始乘梯的时间 ，将状态置为 “等待”
			 SYSTEMTIME NowTime;
			 GetLocalTime(&NowTime);
			 if (NowTime.wSecond == NextTime.second && NowTime.wMinute == NextTime.minute &&NowTime.wHour == NextTime.hour)
			 {
				 //改变状态
				 status = WAIT;        
				 //选择乘坐的电梯
				//获得当前所有电梯所在楼层和状态 

			 }
			 break;
		 case OVER:
			 break;
	}
		
}
