#include "pch.h"
#include "Passenger.h"


Passenger::Passenger()
{
}


Passenger::~Passenger()
{
}

void Passenger::action()
{

	switch (status)
	{

	case  WAIT:
		//��ǰ״̬Ϊ�ȴ�����鿴�����Ƿ񵽴ﵱǰ¥�㣬��״̬��Ϊ ��������
		if (e[which]->NowFloor == NowFloor)
		{
			//���ѡ���ĵ���¥����˿�����¥��һ��
			status = TAKE;
			//ͳ�Ƶȴ�
			SYSTEMTIME NowTime;
			GetLocalTime(&NowTime);
			Time nowtime(NowTime.wHour, NowTime.wMinute, NowTime.wSecond);
			Total = Total + (nowtime - NextTime);
			//�趨�������ݵ�Ŀ��¥��
			if ((NextFloor - NowFloor) > 0)
			{
				e[which]->InsideUp[NextFloor]++;
			}
			else
			{
				e[which]->InsideDown[NextFloor]++;
			}
			
		}
		break;
	case  TAKE:
		//���µ�ǰ�������ݵ�¥��                               
	   //��ǰ״̬Ϊ��������鿴�Ƿ񵽴�Ŀ��¥�� ����״̬��Ϊ ���뿪����ֹͣ��
		if (GetNowFloor() == NextFloor)
		{
			times--;
			switch (times)
			{
			case 0:
				status = OVER;
				break;
			case 1:
				status = LEAVE;
				NextFloor = 1;
				break;
			default:
				status = LEAVE;
				//�趨�µ�Ŀ��¥��
				int temp = ((rand() % 40) + 1);
				while (temp == NowFloor)    //���ȡ�������ǵ�ǰ¥�㣬������ȡ�������ֱ����ͬ
				{
					temp = ((rand() % 40) + 1);
				}
				NextFloor = temp;
				break;
			}


		}
		break;
	case LEAVE:
		//��ǰ״̬Ϊ�뿪����鿴�Ƿ��´ο�ʼ���ݵ�ʱ�� ����״̬��Ϊ ���ȴ���
		SYSTEMTIME NowTime;
		GetLocalTime(&NowTime);
		if (NowTime.wSecond == NextTime.second && NowTime.wMinute == NextTime.minute &&NowTime.wHour == NextTime.hour)
		{
			//�ı�״̬
			status = WAIT;
			//ѡ������ĵ���
			which = Select();
			//���õ���ͣ��¥��
			if ((NextFloor - NowFloor) > 0)
			{
				e[which]->Up[which] = true;
			}
			else
			{
				e[which]->Down[which] = true;
			}
		}
		break;
	case OVER:
		break;
	}

}

unsigned int Passenger::Select()
{
	int select[10] = { 0 };        //�趨����Ȩ������
	select[0] += 1;
	select[1] += 1;
	//�����ǰ¥����Ŀ��¥��Ϊ1,25-40
	if ((25 <= NowFloor <= 40 || NowFloor == 1) && (25 <= NextFloor <= 40 || NextFloor == 1))
	{
		select[2] += 1;
		select[3] += 1;
	}
	//�����ǰ¥����Ŀ��¥��Ϊ1-25
	if ((1 <= NowFloor <= 25) && (1 <= NextFloor <= 25))
	{
		select[4] += 1;
		select[5] += 1;
	}
	//�����ǰ¥����Ŀ��¥��Ϊż��
	if ((NowFloor % 2 == 0 || NowFloor == 1) && (NextFloor % 2 == 0 || NextFloor == 1))
	{
		select[6] += 1;
		select[7] += 1;
	}
	//�����ǰ¥����Ŀ��¥��Ϊ����
	if ((NowFloor % 2 == 1) && (NextFloor % 2 == 1))
	{
		select[8] += 1;
		select[9] += 1;
	}

	// ��һ��ѡ��
	int direction = NextFloor - NowFloor;  //�趨���ݷ���  >0 ���� <0����
	for (int i = 0; i < 10; i++)
	{
		//�����������ĵ�����ѡ��
		if (select[i])
		{
			//�������з�����˿ͷ���һ������
			if ((e[i]->NextFloor - e[i]->NowFloor) >= 0 && direction > 0)
			{
				//���ҵ���¥����ڳ˿�¥��
				if (e[i]->NowFloor < NowFloor)
				{
					select[i] += (NowFloor - e[i]->NowFloor);      //����Ȩ��Ϊ����
					//��ֵԽ��,����λ�þ���˿�ԽԶ
				}

			}
			else if ((e[i]->NextFloor - e[i]->NowFloor) <= 0 && direction < 0)
			{
				// �������з�����˿ͷ���һ������
				//���ҵ���¥����ڳ˿�����¥��
				if (e[i]->NowFloor > NowFloor)
				{
					select[i] += (e[i]->NowFloor - NowFloor);     //����Ȩ��
				}
			}
			else
			{
			}

		}
	}
	//��select�����У���ֵԽС�������ѡ������У�����λ�þ���˿�Խ��
	//��select������ȡ��С����ֵ���±꣬��Ϊ����ѡ�����
	int min = 0;
	for (int i = 1; i < 10; i++)
	{
		if (select[i] > 0 && select[min] > select[i])
		{
			min = i;
		}
	}
	return min;
}

