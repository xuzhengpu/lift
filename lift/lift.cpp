// lift.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "ElevatorLift.h"
#include <time.h>
#include "Passenger.h"
using namespace std;
//设定全局变量
ElevatorLift * E[10];             //电梯指针 
Passenger * P[1000];              //乘客指针
Time Nowtime;
 int K=6;                   //电梯的最大载客数量         10<K<18
 int N;                   //乘客数量                   0<N<1000
 int M=30;                   //初始等待时间    （分钟）   0<M<10
 int L=4;                   //乘客的乘梯次数             1<L<10
 int S=1;                   //电梯速度    单位 :秒/层    1<s<5
 int T=2;                   //乘客上下电梯的时间         2<T<10
void GuideInput();
void Show();
//主函数
int main()
{
	//GuideInput();
	SYSTEMTIME NowTime;
	GetLocalTime(&NowTime);
	Nowtime.set(NowTime.wHour, NowTime.wMinute, NowTime.wSecond);
	E[0] = new ElevatorLift(S,K,T,&Nowtime);
	P[0] = new Passenger(M, L, E,&Nowtime);
	/*P[1] = new Passenger(M, L, E);
	P[2] = new Passenger(M, L, E);
	P[3] = new Passenger(M, L, E); 
	P[4] = new Passenger(M, L, E);*/

	/*for (int i = 0; i < N; i++)
	{
		P[i] = new Passenger(M,L,E);
	}
    */


	VOID CALLBACK myTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime ); 
	MSG msg;
	//设定定时器，定时执行任务
	SetTimer(NULL,1,1000, (TIMERPROC)myTimerProc);  
	//声明不同电梯的指针
	
	
	//主循环
	while(true)
	{
		Show();
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
	Nowtime=Nowtime + 1;
	for (int i = 0; i < 1; i++)
	{
		P[i]->action();
	}
	E[0]->action();
	
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
	printf("1号电梯：\n当前状态：%s   当前楼层：%d    目标楼层:%d  当前人数：%d\n",E[0]->GetStatus(),E[0]->NowFloor , E[0]->NextFloor,E[0]->people);
	printf("-------------------------------------------------------------------\n");
	for (int i = 0; i < 1; i++)
	{
		printf("%d号乘客：\n当前状态:%s   当前楼层: %d   目标楼层:%d  次数：%d\n",i, P[i]->GetStatus(), P[i]->NowFloor, P[i]->NextFloor,P[i]->times);
		printf("    下一次乘梯时间：%d:%d:%d\n ", P[i]->NextTime.hour, P[i]->NextTime.minute, P[i]->NextTime.second);
		printf("**********************************************************************\n");
	}


}
