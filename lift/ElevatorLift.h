#pragma once
#include <Windows.h>
#include "Time.h"
constexpr auto Max = 41;;    //¥����Ŀ
enum Status
{
	STOP, // ��ͣ  
	UP,   // ��������
	DOWN  // ��������
};
class ElevatorLift
{
    public:
	ElevatorLift();
	~ElevatorLift();
	virtual void action();
	
	void UpdateNowFloor();        //���µ�ǰ��������¥��
	void ChangeStatus();         //�ı��������״̬
	void Run();                  //��������
	void UpdateDestination();    //������һվ��Ŀ��¥��
	bool IsTake();               //�鿴�Ƿ����˳�������
	bool IsUp();
	bool IsDown();
    private:
		Status status;
		Status oldstatus;
		bool  Up[100];                 //��������ʱ��ͣ��¥���¼
		bool  Down[100];               //��������ʱ��ͣ��¥���¼
		unsigned  int   NextFloor;    //������һ����Ҫͣ����¥��
		unsigned  int   NowFloor;     //��ǰ��������¥��
		unsigned  int  speed;         //���ݵ�ǰ���е��ٶ�
		double  elevation;            //���ݵ�ǰ�ĸ߶�
		double  hight;                //�������ڴ�¥��¥��߶�
		Time NextStart;               //����ͣ���Ժ���һ�ε�����ʱ��
		unsigned int StopTime;        //����ͣ����ʱ��

};

