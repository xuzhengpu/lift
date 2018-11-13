#include "pch.h"
#include "ElevatorLift.h"


ElevatorLift::ElevatorLift()
{
}


ElevatorLift::~ElevatorLift()
{
}

void ElevatorLift::action()
{
	UpdateNowFloor();    // ���µ�ǰ��������¥��
	UpdateDestination(); // ���µ�����һվ��Ŀ��¥��
	Status();            // �жϵ�ǰ����״̬
	Run();               // ��������
}

void ElevatorLift::UpdateNowFloor()
{
	// elevation ����ǰ���ݵײ��������߶�   hight ����¥ÿ��ĸ߶�
	double ans;
	ans = fmod(elevation, hight) / hight;
	//������ݵײ���¥��ƽ��ľ���С��¥��߶ȵ�20%����˵�������¥�㣬  ��Ӧ��������
	if (ans <= 0.2)
	{

		//���� elevation =4.1   high=2   fmod(elevation,hight�� =0.1< 0.2 
		   //(int)elevation/hight=2 �����Ŀǰ�ײ�������¥
		NowFloor = (int)elevation / hight + 1; //��������¥��λ��=���ݸ߶ȳ���¥��߶��ټ�һ
	}
	//������ݵײ���¥��ƽ��ľ������¥��߶ȵ�80%����˵����������Ҫ�������һ�㣬  ��Ӧ��������
	if (ans >= 0.8)
	{
		/*
		 ����˵����elevation=9.9�� high=2 fmod(elevation,hight��=1.9>1.8
		 (int)elevation/hight=5 �����Ŀǰ�ײ�������¥
		*/
		NowFloor = (int)elevation / hight + 2;
	}
}

void ElevatorLift::ChangeStatus()
{
	if (status != STOP)   //���Ϊ����״̬�����Ƿ���Ҫȥͣ����
	{
		if (NextFloor == NowFloor)
		{
			status = STOP;
			nextstarttime = sys.second + 10;

		}
	}
	else                //���Ϊ��ͣ״̬�����Ƿ���Ҫȥ��������
	{
		if (nextstarttime == sys)
		{
			status = getfangxiang()
			next = getnextfloor()
		}
	}
}

void ElevatorLift::Run()
{
	if (status == UP)      //���������������
	{
		elevation += speed / 10;    //���ӵ��ݸ߶�     
		//speedΪ����ÿ��������ٶ� ����Ϊ������0.1��ѭ��һ�Σ�������ȡspeed/10��Ϊʮ��֮һ����ٶ�    

	}
	else if (status == DOWN)   //��������
	{
		elevation -= speed / 10;   //
	}
	else
	{
		elevation = elevation; //���������ͣ  ��λ�ñ��ֲ���
	}
}
