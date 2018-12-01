#pragma once
#include <stdlib.h>
#include "Time.h"
#include <Windows.h>
#include "ElevatorLift.h"
#include <time.h>
#include "Group.h"
class Passenger
{

public:
	Passenger();
	Passenger(int M, int L, ElevatorLift * E[], Time *tm);    //���캯��
	~Passenger();
	void action();											  //�˿͵Ļ			
	void Select(int &group, int &which);                      //����ѡ�˵ĵ�����
	char * GetStatus();	                                      //get�ŷ�
	int getstatus();
	int GetNextFloor();
	int GetNowFloor();
	int Getwhich();
	int Gettimes();
	int Getgroup();
	int GetTotal();
	Time   NextTime;                      //��һ�γ���ʱ��
private:
	enum Status
	{
		TAKE,     // ����  
		LEAVE,    // �뿪
		WAIT,     // �ȴ�
		OVER      // ֹͣ���ݻ
	};
	Status status;                        //�˿�״̬
	int    WaitTime;                      //�˿ͳ��εȴ�ʱ��
	int    NowFloor;                      //��ǰ¥��
	int    NextFloor;                     //Ŀ��¥��
	int    which;                         //�����ĵ���
	int    group;                         //ѡ�������
	long   Total;                         //�ܼƵȴ�ʱ��   ����λ����)
	char   str[10];                       //��ŵ���״̬���ַ���
	Time   *nowtime;                      //��ǰʱ��ָ��
	ElevatorLift * e[10];                 //���ݵ�ָ��
	Group * g[5];                         //�������ָ��
	unsigned int times;                   //�ܳ��ݴ���


};

