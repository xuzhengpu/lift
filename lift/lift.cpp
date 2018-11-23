// lift.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "ElevatorLift.h"
#include <time.h>
#include "Passenger.h"
//设定全局变量
ElevatorLift * E[10];             //电梯指针 
Passenger * P[1000];              //乘客指针
unsigned int K;                   //电梯的最大载客数量         10<K<18
unsigned int N;                   //乘客数量                   0<N<1000
unsigned int M;                   //初始等待时间    （分钟）   0<M<10
unsigned int L;                   //乘客的乘梯次数             1<L<10
unsigned int S;                   //电梯速度    单位 :秒/层    1<s<5
unsigned int T;                   //乘客上下电梯的时间         2<T<10

//主函数
int main()
{
	E[0] = new ElevatorLift();

	for (int i = 0; i < N; i++)
	{
		P[i] = new Passenger(M,L,E);
	}



	VOID CALLBACK myTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime ); 
	MSG msg;
	//设定定时器，定时执行任务
	SetTimer(NULL,1,1000, (TIMERPROC)myTimerProc);  
	//声明不同电梯的指针
	
	
	//主循环
	while(true)
	{
		
		if (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}

	KillTimer(NULL,1);
	return 0;

}

VOID CALLBACK myTimerProc(
	HWND hwnd, // handle of window for timer messages
	UINT uMsg, // WM_TIMER message
	UINT idEvent, // timer identifier
	DWORD dwTime // current system time
)
{
	
	SYSTEMTIME NowTime;
	GetLocalTime(&NowTime);
	Time nowtime(NowTime.wHour, NowTime.wMinute, NowTime.wSecond);
	nowtime + 10;
	printf("%d:%d:%d\n", NowTime.wHour, NowTime.wMinute, NowTime.wSecond);
	printf("%d:%d:%d\n", nowtime.hour, nowtime.minute, nowtime.second);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
