// lift.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "ElevatorLift.h"
#include <time.h>
#include "Passenger.h"
#include "Group.h"
using namespace std;
//设定全局变量
ElevatorLift  * E[10];                //电梯指针 
Passenger     * P[1000];              //乘客指针
Group         * G[5];                 //电梯组指针
Time Nowtime;
int K = 13;                   //电梯的最大载客数量         10<K<18
int N = 200;                 //乘客数量                   0<N<1000
int M = 2;                  //初始等待时间    （分钟）   0<M<10
int L = 4;                   //乘客的乘梯次数             1<L<10
int S = 1;                   //电梯速度    单位 :秒/层    1<s<5
int T = 1;                   //乘客上下电梯的时间         2<T<10
void GuideInput();
void Show();
void over();
void summary();
bool IsOver();
//主函数
int main()
{
	srand((int)time(0));
	//GuideInput();
	SYSTEMTIME NowTime;
	GetLocalTime(&NowTime);
	Nowtime.set(NowTime.wHour, NowTime.wMinute, NowTime.wSecond);
	E[0] = new ElevatorLift(S, K, T, &Nowtime);
	E[1] = new ElevatorLift(S, K, T, &Nowtime);
	E[2] = new E1(S, K, T, &Nowtime);
	E[3] = new E1(S, K, T, &Nowtime);
	E[4] = new E2(S, K, T, &Nowtime);
	E[5] = new E2(S, K, T, &Nowtime);
	E[6] = new E3(S, K, T, &Nowtime);
	E[7] = new E3(S, K, T, &Nowtime);
	E[8] = new E4(S, K, T, &Nowtime);
	E[9] = new E4(S, K, T, &Nowtime);
	for (int i = 0; i < 5; i++)
	{
		G[i] = new Group(E[2*i], E[2*i + 1]);
	}
	for (int i = 0; i < N; i++)
	{
		P[i] = new Passenger(M, L, E, &Nowtime);
	}

	VOID CALLBACK myTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
	MSG msg;
	//设定定时器，定时执行任务
	SetTimer(NULL, 1, 1000, (TIMERPROC)myTimerProc);
	bool flag = true;
	//主循环
	while (flag)
	{
		if (IsOver())
		{
			flag = false;
		}
		Show();
		if (GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
	KillTimer(NULL, 1);
	summary();
	return 0;

}



VOID CALLBACK myTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	Nowtime = Nowtime + 1;
	//电梯组行动
	for (int i = 0; i < 5; i++)
	{
		G[i]->action();
	}
	// 乘客活动
	for (int i = 0; i < N; i++)
	{
		P[i]->action();
	}
}


void GuideInput()
{
	cout << "请输入乘客数量：" << endl;
	cin >> N;
	cout << "请输入电梯的最大载客数量：" << endl;
	cin >> K;
	cout << "请输入初始等待时间：" << endl;
	cin >> M;
	cout << "请输入乘客的乘梯次数：" << endl;
	cin >> L;
	cout << "请输入电梯的速度（单位:秒/层）：" << endl;
	cin >> S;
	cout << "请输入每名乘客上下电梯的时间  ：" << endl;
	cin >> T;
}

void Show()
{
	system("cls");
	cout << "当前时间" << endl;
	printf("%d:%d:%d\n", Nowtime.hour, Nowtime.minute, Nowtime.second);

printf("乘客ID   当前状态    当前楼层    目标楼层   组号   电梯号   剩余乘梯次数 \n");
	for (int i = 0; i < N; i++)
	{
		printf("%2d         %s         %2d          %2d       %2d       %2d        %2d\n"
			, i + 1, P[i]->GetStatus(), P[i]->GetNowFloor(), P[i]->GetNextFloor(), P[i]->Getgroup(), P[i]->Getwhich(), P[i]->Gettimes());
		//printf("    下一次乘梯时间：%d:%d:%d\n ", P[i]->NextTime.hour, P[i]->NextTime.minute, P[i]->NextTime.second);

	}

	
	printf("-------------------------------------------------------------------\n");


printf("电梯号  当前状态 当前楼层  目标楼层  当前人数：\n");
	for (int i = 0; i < 10; i++)
	{
		printf(" %2d       %4s       %2d        %2d       %2d\n"
			, i + 1, E[i]->GetStatus(), E[i]->GetNowFloor(), E[i]->GetNextFloor(), E[i]->Getpeople());

	}
	
}
void over()
{
	system("cls");

	for (int i = 0; i < 10; i++)
	{
		printf("%d号电梯：\n当前状态：%s   当前楼层：%d    目标楼层:%d  当前人数：%d\n", i + 1, E[i]->GetStatus(), E[i]->GetNowFloor(), E[i]->GetNextFloor(), E[i]->Getpeople());
		printf("-------------------------------------------------------------------\n");
	}
	for (int i = 0; i < N; i++)
	{
		printf("%d号乘客：\n当前状态: %s   当前楼层: %d    目标楼层:%d   次数：%d\n", i, P[i]->GetStatus(), P[i]->GetNowFloor(), P[i]->GetNextFloor(), P[i]->Gettimes());
		printf("组号：%d ，电梯号 ：%d\n", P[i]->Getgroup(), P[i]->Getwhich());
		printf("    下一次乘梯时间：%d:%d:%d\n ", P[i]->NextTime.hour, P[i]->NextTime.minute, P[i]->NextTime.second);
		printf("**********************************************************************\n");
	}
}
void summary()
{
	system("cls");
	cout << "当前时间" << endl;
	printf("%d:%d:%d\n", Nowtime.hour, Nowtime.minute, Nowtime.second);
	printf("电梯号  忙碌时间(秒)  空闲时间(秒)    \n");
	for (int i = 0; i < 10; i++)
	{

		printf("%2d        %3d            %3d\n", i + 1, E[i]->Getbusy(), E[i]->Getvacant());

	}
	printf("**********************************************************************\n");
	printf("乘客ID   等待时间（秒） \n");
	for (int i = 0; i < N; i++)
	{
		printf("%2d        %3d\n", i + 1, P[i]->GetTotal());
	}

}
bool IsOver()
{

	for (int i = 0; i < N; i++)
	{
		if (P[i]->getstatus() !=3 )
		{
			return false;
		}
	}
	return true;
}