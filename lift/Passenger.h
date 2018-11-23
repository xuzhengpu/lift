#pragma once
#include <stdlib.h>
#include "Time.h"
#include <Windows.h>
#include "ElevatorLift.h"

class Passenger
{

    public:
	Passenger();
	Passenger(unsigned int M,unsigned int L,ElevatorLift *E[] )        //���캯��
	{
		NextFloor= (rand() % (40 - 1)) + 1 + 1;  //�������Ŀ��¥��
		status=LEAVE;                            //״̬Ϊ�뿪״̬
		NowFloor = 1;                            //��ʼ¥��Ϊ1
		WaitTime = M*60;                         //�˿ͳ��εȴ�ʱ��
		Total =0;                                //�ܼƵȴ�ʱ��
		times = L+1;                             //�ܳ��ݴ���  
		SYSTEMTIME NowTime;
		GetLocalTime(&NowTime);
		Time nowtime(NowTime.wHour, NowTime.wMinute, NowTime.wSecond);
		NextTime = nowtime + WaitTime;           //�趨��һ�γ��ݵ�ʱ��
		for (int i = 0; i < 10; i++)
		{
			e[i] = E[i];
		}
	}
	~Passenger();
	void action();                             //�˿͵Ļ
	unsigned int GetNowFloor();                //��õ�ǰ���е��ݵ�״̬
	unsigned  int Select();                    //����ѡ�˵ĵ�����
     private:
		enum Status
	{
		TAKE,     // ����  
		LEAVE,    // �뿪
		WAIT,     // �ȴ�
		OVER      // ֹͣ���ݻ
	};
	Status status;                     //�˿�״̬
	unsigned int WaitTime;             //�˿ͳ��εȴ�ʱ��
	unsigned int NowFloor;             //��ǰ¥��
	unsigned int NextFloor;            //Ŀ��¥��
	unsigned int which;               //�����ĵ���
    long Total;                        //�ܼƵȴ�ʱ��   ����λ����)
	unsigned int times;                //�ܳ��ݴ���
	Time  NextTime;                    //��һ�γ���ʱ��
	ElevatorLift * e[10];              //���ݵ�ָ��
};

