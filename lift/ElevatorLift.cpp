#include "pch.h"
#include "ElevatorLift.h"
#include <math.h>

ElevatorLift::ElevatorLift()
{
}


ElevatorLift::~ElevatorLift()
{
}

void ElevatorLift::action()
{
	UpdateNowFloor();       // ���µ�ǰ��������¥��
	UpdateDestination();    // ���µ�����һվ��Ŀ��¥��
	ChangeStatus();         // �жϸı䵱ǰ����״̬
	Run();                  // ��������
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
		NowFloor = (int)(elevation / hight) + 1; //��������¥��λ��=���ݸ߶ȳ���¥��߶��ټ�һ
	}
	//������ݵײ���¥��ƽ��ľ������¥��߶ȵ�80%����˵����������Ҫ�������һ�㣬  ��Ӧ��������
	if (ans >= 0.8)
	{
		/*
		 ����˵����elevation=9.9�� high=2 fmod(elevation,hight��=1.9>1.8
		 (int)elevation/hight=5 �����Ŀǰ�ײ�������¥
		*/
		NowFloor = (int)(elevation / hight) + 2;
	}
}

void ElevatorLift::ChangeStatus()
{
	if (status != STOP)   //���Ϊ����״̬�����Ƿ���Ҫȥͣ����
	{
		if (NextFloor == NowFloor)
		{
			oldstatus = status;  //�洢����ֹͣǰ��״̬
			status = STOP;	     //�ı����״̬
			if (oldstatus == UP)
				Up[NowFloor] = false;   //	�����¼
			else
			{
				Down[NowFloor] = false;   //�����¼
			}
			if (!IsTake())
			{
				NextFloor = 0;      //����ͣ�����Ժ���û�˳������ݣ�Ŀ��¥����Ϊ0  �ر��´�����ʱ��
				NextStart.onoff = false;
			}
			if(NextStart.onoff = true)
			{
				SYSTEMTIME NowTime;
				GetLocalTime(&NowTime);
				Time nowtime(NowTime.wHour,NowTime.wMinute,NowTime.wSecond);
				NextStart=nowtime +  StopTime;
			}
			

		}
	}
	else                //���Ϊ��ͣ״̬�����Ƿ���Ҫȥ��������
	{
		 //���Ŀ��¥��Ϊ0����˵��û�˳������ݣ�������
		//���Ŀ��¥�㲻Ϊ0 ������������
		if (NextFloor!=0)        
		{
			if (NextStart.onoff == true)     // ������ݵ�Ŀ��ʱ���
			{
				SYSTEMTIME NowTime;
			GetLocalTime(&NowTime);

			if (NextStart.hour == NowTime.wHour&&NextStart.minute == NowTime.wMinute&&NextStart.second == NowTime.wSecond)
			{  
				//���ʱ�䵽�ˣ���ı���ݵ�����״̬
				status = oldstatus;
				oldstatus = STOP;
				UpdateDestination();  //ȡ����һ��ͣ����¥��
			}
			}
			else
			{
				if (NextFloor - NowFloor > 0)
				{
					status = UP;
					NextStart.onoff == true;
				}
				else
				{
					status = DOWN;
					NextStart.onoff == true;
				}
			}
		}
	     //������ݼ�¼û���˳������򲻸ı���ͣ״̬
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
		                                    // 1.�����ƶ�
		elevation =( NowFloor - 1)*hight;   // 2.ʹ����λ����¥�������ƽ
	}
}

void ElevatorLift::UpdateDestination()
{
	if (status == UP)     //��������������У��������м�¼��ѯ��һ��ͣ��λ��
	{    
		
		for (int i = 1; i < Max; i++)
		{
			if (Up[i] == true)
			{
				NextFloor = i;
				break;
			}
		}
	}
    else if(status == DOWN)    //����������У��������м�¼��ѯ��һ��ͣ��λ��
	{
		for (int i = Max; i > 0; i--)
		{
			if (Down[i] == true)
			{
				NextFloor = i;
				break;
			}
		}
	}
	else                    //���������ͣ���������¼�¼����ѯ
	{
		if (!IsTake())    //���û�˳������ݣ���Ŀ��¥����Ϊ0  ���ر��´ο���ʱ��
		{
			NextFloor = 0;
			NextStart.onoff = false;
		}
		if (IsUp() == false && IsDown() == true)    //���пգ����зǿ�
		{
			for (int i = Max; i > 0; i--)
			{
				if (Down[i] == true)
				{
					NextFloor = i;
					NextStart.onoff = false;    //�ر��´�����ʱ��ʱ��
					break;
				}
			}

		}
		if(IsUp() == true && IsDown() == false)    //���зǿգ����п�
		{
			for (int i = 1; i < Max; i++)   
			{
				if (Up[i] == true)
				{
					NextFloor = i;
					NextStart.onoff = false;
					break;
				}
			}
		}
		
	}
}

bool ElevatorLift::IsTake()
{
	for (int i = 1; i < Max; i++)
	{
		if (Up[i] == true || Down[i] == true)
			return true;
	}
	return false;
}

bool ElevatorLift::IsUp()
{
	for (int i = 1; i < Max; i++)
	{
		if (Up[i] == true)
			return true;
	}
	return false;
}

bool ElevatorLift::IsDown()
{
	for (int i = 1; i < 41; i++)
	{
		if (Down[i] == true)
			return true;
	}
	return false;
}