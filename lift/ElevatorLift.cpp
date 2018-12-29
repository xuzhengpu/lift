#include "pch.h"

#include "ElevatorLift.h"
#include <math.h>
#include <time.h>
ElevatorLift::ElevatorLift()
{
}
ElevatorLift::ElevatorLift(int S, int K, int T, Time *tm)
{
	status = STOP;                       //��ʼ����ֹͣ
	NowFloor = (rand() % (40 - 1)) + 1;  // ������ɵ���ͣ��λ�� 
	NextFloor = NowFloor;                //����ֹͣʱĿ��¥���뵱ǰ¥��һ��
	nowfloor = NowFloor;                 //���ڼ����λ��
	speed = 1 / (float)S;                  //�����ٶ�  s�ĵ�λΪ��/��   speed ��λΪ ��/��
	StopTime = T;                        // ÿ���˿����µ��ݵ�ʱ��  
	capacity = K;                        //���ݵ�����
	people = 0;                          //��ǰ���ݵ�����
	vacant = 0;                            //���ݿ���ʱ��
	busy = 0;                              //��������ʱ��
	nowtime = tm;
	Over = *nowtime;
	//��ʼ��
	for (int i = 0; i < 41; i++)
	{

		Up[i] = 0;
		Down[i] = 0;
		InsideUp[i] = 0;
		InsideDown[i] = 0;
	}

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

char * ElevatorLift::GetStatus()
{

	switch (status)
	{
	case UP:
		strcpy_s(str, "��");
		break;
	case UPSTOP:
		strcpy_s(str, "��ͣ");
		break;
	case DOWN:
		strcpy_s(str, "��");
		break;
	case DOWNSTOP:
		strcpy_s(str, "��ͣ");
		break;
	case STOP:
		strcpy_s(str, "ͣ");
		break;
	default:
		break;
	}
	return str;
}

int ElevatorLift::GetNextFloor()
{
	return NextFloor;
}

int ElevatorLift::GetNowFloor()
{
	return NowFloor;
}

int ElevatorLift::Getpeople()
{
	return people;
}

int ElevatorLift::Getbusy()
{
	return busy;
}

int ElevatorLift::Getvacant()
{
	return vacant;
}

void ElevatorLift::SetUp(int floor, int n)
{
	Up[floor] += n;
}

void ElevatorLift::SetDown(int floor, int n)
{
	Down[floor] += n;
}

void ElevatorLift::SetInsideUp(int floor, int n)
{
	InsideUp[floor] += n;
}

void ElevatorLift::SetInsideDown(int floor, int n)
{
	InsideDown[floor] += n;
}





void ElevatorLift::UpdateNowFloor()
{
	NowFloor = (int)nowfloor;
}
void ElevatorLift::UpdateDestination()
{
	switch (status)
	{
	case UP:
		for (int i = NowFloor; i < Max; i++)   //�ӵ�ǰ¥����һ�㿪ʼ��ѯ�������ͣ����¼��ȡ�����¥��ΪĿ��¥��
		{
			if (Up[i] || InsideUp[i])
			{
				NextFloor = i;
				break;
			}
		}
		break;
	case UPSTOP:
		for (int i = NowFloor; i < Max; i++)   //�ӵ�ǰ¥�㿪ʼ��ѯ�������ͣ����¼��ȡ�����¥��ΪĿ��¥��
		{
			if (Up[i] || InsideUp[i] || Down[i])
			{
				NextFloor = i;
				break;
			}
		}
		break;
	case DOWN:
		for (int i = NowFloor; i > 0; i--)   //�ӵ�ǰ¥�㿪ʼ��ѯ�������ͣ����¼��ȡ�����¥��ΪĿ��¥��
		{
			if (Down[i] || InsideDown[i])
			{
				NextFloor = i;
				break;
			}
		}
		break;
	case DOWNSTOP:
		for (int i = NowFloor; i > 0; i--)   //�ӵ�ǰ¥�㿪ʼ��ѯ�������ͣ����¼��ȡ�����¥��ΪĿ��¥��
		{
			if (Down[i] || InsideDown[i] || Up[i])
			{
				NextFloor = i;
				break;
			}
		}
		break;
	case STOP:


		if (IsTake())                   //�������ͣ�������Ժ���Ŀ��¥��
		{
			NextFloor = IsTake();
		}
		else
		{                                //û�˳����Ļ�����ѯ����
			if (call())                  //������˺��е���
				NextFloor = call();
		}
		break;
	default:
		break;
	}

}

void ElevatorLift::ChangeStatus()
{
	switch (status)
	{
	case STOP:                         //״̬Ϊֹͣ�������Ƿ�ı�״̬�����ϡ����¡�

		if (NextFloor != NowFloor)    //�������Ŀ��¥���뵱ǰ¥�㲻һ�£�����Ҫ��������
		{
			if (NextFloor - NowFloor > 0)
			{
				status = UP;
				vacant += (*nowtime - Over);
				Start = *nowtime;
			}
			else
			{
				status = DOWN;
				vacant += (*nowtime - Over);
				Start = *nowtime;
			}
		}
		break;
	case UP:          //״̬Ϊ�������У������Ƿ�ı�״̬������ͣ��
		if (NextFloor == NowFloor)     //�������ͣ��¥��
		{
			status = UPSTOP;
			NextStart = (*nowtime + (1 + Up[NowFloor] + InsideUp[NowFloor])*StopTime);  //����ͣ��ʱ��
			InsideUp[NowFloor] = 0;                                               //�˿����µ���

		}
		break;
	case UPSTOP:
		if (NextStart.hour == nowtime->hour&&NextStart.minute == nowtime->minute&&NextStart.second == nowtime->second)
		{
			if (NextFloor > NowFloor)
			{
				status = UP;
			}
			else
			{
				status = STOP;
				busy += (*nowtime - Start);
				Over = *nowtime;
			}
		}
		break;
	case DOWN:
		if (NextFloor == NowFloor)     //�������ͣ��¥��
		{
			status = DOWNSTOP;
			NextStart = (*nowtime + (1 + Down[NowFloor] + InsideDown[NowFloor])*StopTime);  //����ͣ��ʱ��
			InsideDown[NowFloor] = 0;
		}
		break;
	case DOWNSTOP:

		if (NextStart.hour == nowtime->hour&&NextStart.minute == nowtime->minute&&NextStart.second == nowtime->second)
		{
			if (NextFloor >= NowFloor)
			{
				status = STOP;
				busy += (*nowtime - Start);
				Over = *nowtime;
			}
			else
			{
				status = DOWN;
			}
		}
		break;

	default:
		break;
	}
}

void ElevatorLift::Run()
{


	if (status == UP)      //���������������
	{

		nowfloor += speed;    //speedΪ����ÿ��������ٶ�
		//int temp = 0;
		//for (int i = NowFloor; i < 41; i++)
		//{
		//	temp += InsideUp[i];
		//}//ͳ������
		//people = temp;
	}
	else if (status == DOWN)   //��������
	{
		nowfloor -= speed;//
		//int temp = 0;
		//for (int i = NowFloor; i > 0; i--)
		//{
		//	temp += InsideDown[i];
		//}//ͳ������
		//people = temp;
	}
	else if (status == UPSTOP)
	{
		//int temp = 0;
		//for (int i = NowFloor; i < 41; i++)
		//{
		//	temp += InsideUp[i];
		//}//ͳ������
		//people = temp;                            // 1.�����ƶ�
											// 2.ʹ����λ����¥�������ƽ
	}
	else if (status == DOWNSTOP)   //��������
	{
		//int temp = 0;
		//for (int i = NowFloor; i > 0; i--)
		//{
		//	temp += InsideDown[i];
		//}//ͳ������
		//people = temp;
	}
	else
	{

	}

}


int ElevatorLift::call()
{
	for (int i = 1; i < Max; i++)
	{
		if (Up[i] || Down[i])
			return i;
	}
	return 0;
}

int ElevatorLift::IsTake()
{
	for (int i = 1; i < Max; i++)
	{
		if (InsideUp[i] || InsideDown[i])
			return i;
	}
	return 0;
}





E1::E1(int S, int K, int T, Time * tm)
{
	status = STOP;                       //��ʼ����ֹͣ
	NowFloor = (rand() % (40 - 1)) + 1;  // ������ɵ���ͣ��λ�� 
	NextFloor = NowFloor;                //����ֹͣʱĿ��¥���뵱ǰ¥��һ��
	nowfloor = NowFloor;                 //���ڼ����λ��
	speed = 1 / (float)S;                  //�����ٶ�  s�ĵ�λΪ��/��   speed ��λΪ ��/��
	StopTime = T;                        // ÿ���˿����µ��ݵ�ʱ��  
	capacity = K;                        //���ݵ�����
	people = 0;                          //��ǰ���ݵ�����
	vacant = 0;                            //���ݿ���ʱ��
	busy = 0;                              //��������ʱ��
	nowtime = tm;
	Over = *nowtime;
	//��ʼ��
	for (int i = 0; i < 41; i++)
	{

		Up[i] = 0;
		Down[i] = 0;
		InsideUp[i] = 0;
		InsideDown[i] = 0;
	}
}

E4::E4(int S, int K, int T, Time * tm)
{
	status = STOP;                       //��ʼ����ֹͣ
	NowFloor = (rand() % (40 - 1)) + 1;  // ������ɵ���ͣ��λ�� 
	NextFloor = NowFloor;                //����ֹͣʱĿ��¥���뵱ǰ¥��һ��
	nowfloor = NowFloor;                 //���ڼ����λ��
	speed = 1 / (float)S;                  //�����ٶ�  s�ĵ�λΪ��/��   speed ��λΪ ��/��
	StopTime = T;                        // ÿ���˿����µ��ݵ�ʱ��  
	capacity = K;                        //���ݵ�����
	people = 0;                          //��ǰ���ݵ�����
	vacant = 0;                            //���ݿ���ʱ��
	busy = 0;                              //��������ʱ��
	nowtime = tm;
	Over = *nowtime;
	//��ʼ��
	for (int i = 0; i < 41; i++)
	{

		Up[i] = 0;
		Down[i] = 0;
		InsideUp[i] = 0;
		InsideDown[i] = 0;
	}
}

E2::E2(int S, int K, int T, Time * tm)
{
	status = STOP;                       //��ʼ����ֹͣ
	NowFloor = (rand() % (40 - 1)) + 1;  // ������ɵ���ͣ��λ�� 
	NextFloor = NowFloor;                //����ֹͣʱĿ��¥���뵱ǰ¥��һ��
	nowfloor = NowFloor;                 //���ڼ����λ��
	speed = 1 / (float)S;                  //�����ٶ�  s�ĵ�λΪ��/��   speed ��λΪ ��/��
	StopTime = T;                        // ÿ���˿����µ��ݵ�ʱ��  
	capacity = K;                        //���ݵ�����
	people = 0;                          //��ǰ���ݵ�����
	vacant = 0;                            //���ݿ���ʱ��
	busy = 0;                              //��������ʱ��
	nowtime = tm;
	Over = *nowtime;
	//��ʼ��
	for (int i = 0; i < 41; i++)
	{

		Up[i] = 0;
		Down[i] = 0;
		InsideUp[i] = 0;
		InsideDown[i] = 0;
	}
}

E3::E3(int S, int K, int T, Time * tm)
{
	status = STOP;                       //��ʼ����ֹͣ
	NowFloor = (rand() % (40 - 1)) + 1;  // ������ɵ���ͣ��λ�� 
	NextFloor = NowFloor;                //����ֹͣʱĿ��¥���뵱ǰ¥��һ��
	nowfloor = NowFloor;                 //���ڼ����λ��
	speed = 1 / (float)S;                  //�����ٶ�  s�ĵ�λΪ��/��   speed ��λΪ ��/��
	StopTime = T;                        // ÿ���˿����µ��ݵ�ʱ��  
	capacity = K;                        //���ݵ�����
	people = 0;                          //��ǰ���ݵ�����
	vacant = 0;                            //���ݿ���ʱ��
	busy = 0;                              //��������ʱ��
	nowtime = tm;
	Over = *nowtime;
	//��ʼ��
	for (int i = 0; i < 41; i++)
	{

		Up[i] = 0;
		Down[i] = 0;
		InsideUp[i] = 0;
		InsideDown[i] = 0;
	}
}


void E1::SetUp(int floor, int n)
{
	if ((floor <= 40 && 25 <= floor) || floor == 1)
	{
		Up[floor] += n;
	}
}

void E1::SetDown(int floor, int n)
{
	if ((floor <= 40 && 25 <= floor) || floor == 1)
	{
		Down[floor] += n;
	}
}

void E1::SetInsideUp(int floor, int n)
{
	if ((floor <= 40 && 25 <= floor) || floor == 1)
	{
		InsideUp[floor] += n;
	}
}

void E1::SetInsideDown(int floor, int n)
{
	if ((floor <= 40 && 25 <= floor) || floor == 1)
	{
		InsideDown[floor] += n;
	}
}

void E2::SetUp(int floor, int n)
{
	if (floor <= 25 && 1 <= floor)
	{
		Up[floor] += n;
	}
}

void E2::SetDown(int floor, int n)
{
	if (floor <= 25 && 1 <= floor)
	{
		Down[floor] += n;
	}
}

void E2::SetInsideUp(int floor, int n)
{
	if (floor <= 25 && 1 <= floor)
	{
		InsideUp[floor] += n;
	}
}

void E2::SetInsideDown(int floor, int n)
{
	if (floor <= 25 && 1 <= floor)
	{
		InsideDown[floor] += n;
	}
}

void E3::SetUp(int floor, int n)
{
	if (floor % 2 ==  0 || floor == 1)
	{
		Up[floor] += n;
	}
}

void E3::SetDown(int floor, int n)
{
	if (floor % 2 == 0 || floor==1)
	{
		Down[floor] += n;
	}
}

void E3::SetInsideUp(int floor, int n)
{
	if (floor % 2 == 0 || floor == 1)
	{
		InsideUp[floor] += n;
	}
}

void E3::SetInsideDown(int floor, int n)
{
	if (floor % 2 == 0 || floor == 1)
	{
		InsideDown[floor] += n;
	}
}

void E4::SetUp(int floor, int n)
{
	if (floor % 2 == 1)
	{
		Up[floor] += n;
	}
}

void E4::SetDown(int floor, int n)
{
	if (floor % 2 == 1)
	{
		Down[floor] += n;
	}
}

void E4::SetInsideUp(int floor, int n)
{
	if (floor % 2 == 1)
	{
		InsideUp[floor] += n;
	}
}

void E4::SetInsideDown(int floor, int n)
{
	if (floor % 2 == 1)
	{
		InsideDown[floor] += n;
	}
}


