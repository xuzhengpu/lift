#pragma once
#include <Windows.h>
#include "Time.h"
constexpr auto Max = 41;   //¥����Ŀ

class ElevatorLift
{
    public:
		
	ElevatorLift( int S, int K, int T,Time *tm);
	~ElevatorLift();
	virtual void action();
    char * GetStatus();
	void UpdateNowFloor();        //���µ�ǰ��������¥��
	void ChangeStatus();          //�ı��������״̬
	void Run();                   //��������
	void UpdateDestination();     //������һվ��Ŀ��¥��
	int  call();                  //�鿴�Ƿ����˺��е���
	int IsTake();

	bool IsUp();
	bool IsDown();
   // private:
		enum Status
		{
			STOP,    // ֹͣ  
			UP,      // ��������
			DOWN,    // ��������
			UPSTOP,  // ���й����е���ͣ
			DOWNSTOP // ���й����е���ͣ
		};
		 Status status;
		 int   NextFloor;    //������һ����Ҫͣ����¥��
		 int   NowFloor;     //��ǰ��������¥��
		 int  Up[41];        //�����ⲿ����¼�˿����к��е�¥��   Up[i]����ֵ�����i�����еĳ˿�����
		 int  Down[41];      //�����ⲿ����¼�˿����к��е�¥��
		 int  InsideUp[41];  //�����ڲ������ó˿�����Ŀ��¥�������
		 int  InsideDown[41];//�����ڲ������ó˿�����Ŀ��¥�������
		 int   people;       //��ǰ���ݵ�����
		 int   capacity;      //��ǰ���ݵ�����
		 float nowfloor;               //���ڼ��㵱ǰ¥��
		 float  speed;                 //���ݵ�ǰ���е��ٶ�
		 long vacant;                  //���ݿ���ʱ��
		 long busy;                    //�������е�ʱ��
		 Time NextStart;               //����ͣ���Ժ���һ�ε�����ʱ��
		 Time Start;
		 Time Over;
		 Time * nowtime;
		 unsigned int StopTime;        //����ͣ����ʱ��
		 friend class Passenger;       //�����������ṩ���˿�
		 char str[10];
	
};

