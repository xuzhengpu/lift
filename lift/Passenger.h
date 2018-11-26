#pragma once
#include <stdlib.h>
#include "Time.h"
#include <Windows.h>
#include "ElevatorLift.h"
#include <time.h>
class Passenger
{

    public:
	Passenger();
	Passenger( int M, int L,ElevatorLift *E[],Time *tm )        //���캯��
	{
		srand((int)time(0));
		NextFloor= (rand() % (40 - 1)) + 1 + 1;  //�������Ŀ��¥��
		status=LEAVE;                            //״̬Ϊ�뿪״̬
		NowFloor = 1;                            //��ʼ¥��Ϊ1
		WaitTime = 5;                           //�˿ͳ��εȴ�ʱ��
		Total =0;                                //�ܼƵȴ�ʱ��
		times = L+1;                             //�ܳ��ݴ���  
		nowtime = tm;
		NextTime = (*nowtime + WaitTime);           //�趨��һ�γ��ݵ�ʱ��
		for (int i = 0; i < 10; i++)
		{
			e[i] = E[i];
		}
	}
	~Passenger();
	void action();                             //�˿͵Ļ
	//unsigned int GetNowFloor();                //��õ�ǰ���е��ݵ�״̬
	unsigned  int Select();                    //����ѡ�˵ĵ�����
	char * GetStatus();
   //  private:
		enum Status
	{
		TAKE,     // ����  
		LEAVE,    // �뿪
		WAIT,     // �ȴ�
		OVER      // ֹͣ���ݻ
	};
	Status status;                     //�˿�״̬
	int WaitTime;             //�˿ͳ��εȴ�ʱ��
	int NowFloor;             //��ǰ¥��
	int NextFloor;            //Ŀ��¥��
	int which;               //�����ĵ���
    long Total;                        //�ܼƵȴ�ʱ��   ����λ����)
	unsigned int times;                //�ܳ��ݴ���
	Time  NextTime;                    //��һ�γ���ʱ��
	Time *nowtime;
	ElevatorLift * e[10];              //���ݵ�ָ��
	char str[10];
};

