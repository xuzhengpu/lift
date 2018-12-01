#pragma once
#include <Windows.h>
#include "Time.h"
constexpr auto Max = 41;   //¥����Ŀ

class ElevatorLift
{
public:
	ElevatorLift();
	ElevatorLift(int S, int K, int T, Time *tm);
	~ElevatorLift();
	void action();
	void UpdateNowFloor();                //���µ�ǰ��������¥��
	void ChangeStatus();                  //�ı��������״̬
	void Run();                           //��������
	void UpdateDestination();     //������һվ��Ŀ��¥��
	int  call();                          //�鿴�Ƿ����˺��е���
	int IsTake();
	char * GetStatus();                   //get����
	int GetNextFloor();
	int GetNowFloor();
	int Getpeople();
	int Getbusy();
	int Getvacant();
	virtual void SetUp(int floor, int n);
	virtual void SetDown(int floor, int n);
	virtual void SetInsideUp(int floor, int n);
	virtual void SetInsideDown(int floor, int n);
protected:
	enum Status
	{
		STOP,    // ֹͣ  
		UP,      // ��������
		DOWN,    // ��������
		UPSTOP,  // ���й����е���ͣ
		DOWNSTOP // ���й����е���ͣ
	};
	Status status;
	int     NextFloor;				//������һ����Ҫͣ����¥��
	int     NowFloor;				//��ǰ��������¥��
	int     Up[41];					//�����ⲿ����¼�˿����к��е�¥��   Up[i]����ֵ�����i�����еĺ��е��ݵĳ˿�����
	int     Down[41];			    //�����ⲿ����¼�˿����к��е�¥��
	int     InsideUp[41];			//�����ڲ������ó˿�����Ŀ��¥�������
	int     InsideDown[41];			//�����ڲ������ó˿�����Ŀ��¥�������
	int     people;					//��ǰ���ݵ�����
	int     capacity;				//��ǰ���ݵ�����
	float   nowfloor;               //���ڼ��㵱ǰ¥��
	float   speed;                  //���ݵ�ǰ���е��ٶ�
	long	vacant;					//���ݿ���ʱ��
	long	busy;				    //�������е�ʱ��
	Time	NextStart;				//����ͣ���Ժ���һ�ε�����ʱ��
	Time	Start;                  //����������ʱ��
	Time	Over;                   //����ֹͣ��ʱ��
	Time	* nowtime;              //��ǰʱ��ָ��
	unsigned int StopTime;			//����ͣ����ʱ��
	friend class Passenger;		    //�����������ṩ���˿�
	char str[10];                   //���ڴ�ŵ�ǰ״̬��

};

class E1 :public ElevatorLift      //25-24¥��ĵ���
{
public:

	E1(int S, int K, int T, Time *tm);
	void SetUp(int floor, int n);
	void SetDown(int floor, int n);
	void SetInsideUp(int floor, int n);
	void SetInsideDown(int floor, int n);
};
class E2 :public ElevatorLift      //1-25¥��ĵ���
{
public:
	E2(int S, int K, int T, Time *tm);
	void SetUp(int floor, int n);
	void SetDown(int floor, int n);
	void SetInsideUp(int floor, int n);
	void SetInsideDown(int floor, int n);
};
class E3 :public ElevatorLift     //ż��¥��ĵ���
{
public:
	E3(int S, int K, int T, Time *tm);
	void SetUp(int floor, int n);
	void SetDown(int floor, int n);
	void SetInsideUp(int floor, int n);
	void SetInsideDown(int floor, int n);
};
class E4 :public ElevatorLift    //����¥��ĵ���
{
public:
	E4(int S, int K, int T, Time *tm);
	void SetUp(int floor, int n);
	void SetDown(int floor, int n);
	void SetInsideUp(int floor, int n);
	void SetInsideDown(int floor, int n);
};