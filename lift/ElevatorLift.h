#pragma once

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
	int GetNext();               //ȡ����һ��ͣ��¥��
	Status GetStatus();         // ȡ�õ���Ŀǰ����״̬
	void Change();             //�ı�������з���
	void UpdateNowFloor();
	void ChangeStatus();
	void Run();
	void UpdateDestination();
    private:
		Status status;
		bool  Up[41];                 //��������ʱ��ͣ��¥���¼
		bool  Down[41];               //��������ʱ��ͣ��¥���¼
		unsigned  int   NextFloor;    //������һ����Ҫͣ����¥��
		unsigned  int   NowFloor;     //��ǰ��������¥��
		unsigned  int  speed;         //���ݵ�ǰ���е��ٶ�
		double  elevation;            //���ݵ�ǰ�ĸ߶�
		double  hight;                //�������ڴ�¥��¥��߶�
};

