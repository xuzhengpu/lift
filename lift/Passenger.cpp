#include "pch.h"
#include "Passenger.h"

Passenger::Passenger()
{
}

Passenger::Passenger(int M, int L, ElevatorLift * E[], Time * tm)
{
	NextFloor = (rand() % (40 - 1)) + 1 + 1;            //�������Ŀ��¥��
	status = LEAVE;                                     //״̬Ϊ�뿪״̬
	NowFloor = 1;                                       //��ʼ¥��Ϊ1
	WaitTime = (rand() % (M * 60 - 1)) + 1;               //�˿ͳ��εȴ�ʱ��
	Total = 0;                                          //�ܼƵȴ�ʱ��
	times = L + 1;                                      //�ܳ��ݴ���  
	nowtime = tm;
	NextTime = (*nowtime + WaitTime);                   //�趨��һ�γ��ݵ�ʱ��
	for (int i = 0; i < 10; i++)
	{
		e[i] = E[i];
	}
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
		if (e[which]->people < e[which]->capacity)
		{   //�����������δ��
			if (e[which]->NowFloor == NowFloor)
			{   //ѡ���ĵ���¥����˿�����¥��һ��
				if (((NextFloor - NowFloor) > 0 && (e[which]->NextFloor - e[which]->NowFloor) >= 0) ||
					((NextFloor - NowFloor) < 0 && (e[which]->NextFloor - e[which]->NowFloor) <= 0))
				{   //���ҷ���һ��
					status = TAKE;
					//ͳ�Ƶȴ�
					Total = Total + (*nowtime - NextTime);
					//�趨�������ݵ�Ŀ��¥��
					if ((NextFloor - NowFloor) > 0)
					{
						e[which]->SetInsideUp(NextFloor, 1);   //����Ŀ��¥��
						e[which]->SetUp(NowFloor, -1);         //��������
					}
					else if ((NextFloor - NowFloor) < 0)
					{
						e[which]->SetInsideDown(NextFloor, 1);  //����Ŀ��¥��
						e[which]->SetDown(NowFloor, -1);        //��������
					}
					else
					{

					}
				}
			}
		}
		break;
	case  TAKE:
		NowFloor = e[which]->NowFloor;        //���µ�ǰ�������ݵ�¥��                               
	   //��ǰ״̬Ϊ��������鿴�Ƿ񵽴�Ŀ��¥�� ����״̬��Ϊ ���뿪����ֹͣ��
		if (NowFloor == NextFloor)
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
				NextTime = (*nowtime + 10);
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
				NextTime = (*nowtime + ((rand() % 111) + 10));     //������һ�γ���ʱ��,���ͣ��10-120��
				break;
			}


		}
		break;
	case LEAVE:
		//��ǰ״̬Ϊ�뿪����鿴�Ƿ��´ο�ʼ���ݵ�ʱ�� ����״̬��Ϊ ���ȴ���

		if (nowtime->second == NextTime.second && nowtime->minute == NextTime.minute &&nowtime->hour == NextTime.hour)
		{
			//�ı�״̬
			status = WAIT;
			//ѡ������ĵ�����,�����
			Select(group, which);
			//���õ���ͣ��¥��
			if ((NextFloor - NowFloor) > 0)
			{

				e[which]->SetUp(NowFloor, 1);    //Up[this->NowFloor] += 1;
			}
			else
			{
				e[which]->SetDown(NowFloor, 1);  //Down[this->NowFloor] += 1;
			}

		}
		break;
	case OVER:
		break;
	}

}
char * Passenger::GetStatus()
{
	switch (status)
	{

	case  WAIT:
		strcpy_s(str, "�ȴ�");
		break;
	case  TAKE:
		strcpy_s(str, "����");
		break;
	case LEAVE:
		strcpy_s(str, "�뿪");
		break;
	case OVER:
		strcpy_s(str, "����");
		break;
	}
	return str;
}

int Passenger::getstatus()
{
	return status;
}

int Passenger::GetNextFloor()
{
	return NextFloor;
}

int Passenger::GetNowFloor()
{
	return NowFloor;
}

int Passenger::Getwhich()
{
	return which + 1;
}

int Passenger::Gettimes()
{
	return times;
}

int Passenger::Getgroup()
{
	return group + 1;
}

int Passenger::GetTotal()
{
	return Total;
}

void  Passenger::Select(int & group, int & which)
{
	int select[10];                  //�趨����Ȩ������
	for (int i = 0; i < 10; i++)      //��ʼ��
	{
		select[i] = 0;
	}
	select[0] = 1;
	select[1] = 1;
	//�����ǰ¥����Ŀ��¥��Ϊ1,25-40
	if (((25 <= NowFloor && NowFloor <= 40) || NowFloor == 1) && ((25 <= NextFloor && NextFloor <= 40) || NextFloor == 1))
	{
		select[2] += 1;
		select[3] = 1;
	}
	//�����ǰ¥����Ŀ��¥��Ϊ1-25
	if ((1 <= NowFloor && NowFloor <= 25) && (1 <= NextFloor && NextFloor <= 25))
	{
		select[4] += 1;
		select[5] = 1;
	}
	//�����ǰ¥����Ŀ��¥��Ϊż��
	if ((NowFloor % 2 == 0 || NowFloor == 1) && (NextFloor % 2 == 0 || NextFloor == 1))
	{
		select[6] += 1;
		select[7] = 1;
	}
	//�����ǰ¥����Ŀ��¥��Ϊ����
	if ((NowFloor % 2 == 1) && (NextFloor % 2 == 1))
	{
		select[8] += 1;
		select[9] = 1;
	}

	// ��һ��ѡ��
	int direction = NextFloor - NowFloor;  //�趨���ݷ���  >0 ���� <0����
	for (int i = 0; i < 10; i++)
	{
		//�����������ĵ�������ѡ��
		if (select[i])
		{
			//����˿�Ҫȥ����
			if (direction > 0)
			{
				//�������ͣ
				if (e[i]->NextFloor - e[i]->NowFloor == 0)
				{
					select[i] = select[i] + 40 - abs((NowFloor - e[i]->NowFloor));   //����Խ����Ȩ��Խ��
				}
				//�����������
				else if (e[i]->NextFloor - e[i]->NowFloor > 0)
				{
					//���ҵ���λ�õ��ڳ˿�λ��
					if (e[i]->NowFloor <= NowFloor)
					{
						select[i] = select[i] + 40 - abs((NowFloor - e[i]->NowFloor));   //����Խ����Ȩ��Խ��	
					}
					else   //����λ�ø��ڳ˿�
					{
						select[i] = select[i] - abs((NowFloor - e[i]->NowFloor));
					}
				}
				//�����������
				else
				{
					//���ҵ���λ�ø��ڳ˿�λ��
					if (e[i]->NowFloor >= NowFloor)
					{
						select[i] = select[i] - abs((NowFloor - e[i]->NowFloor));   //����Խ����Ȩ��Խ��	
					}
					else   //����λ�õ��ڳ˿�
					{
						select[i] = select[i] + abs((NowFloor - e[i]->NowFloor));
					}
				}
			}
			else   //����˿�Ҫȥ����
			{
				//�������ͣ
				if (e[i]->NextFloor - e[i]->NowFloor == 0)
				{
					select[i] = select[i] + 40 - abs((NowFloor - e[i]->NowFloor));   //����Խ����Ȩ��Խ��
				}
				//�����������
				else if (e[i]->NextFloor - e[i]->NowFloor > 0)
				{
					//���ҵ���λ�õ��ڳ˿�λ��
					if (e[i]->NowFloor <= NowFloor)
					{
						select[i] = select[i] - abs((NowFloor - e[i]->NowFloor));   //����Խ����Ȩ��Խ��	
					}
					else   //����λ�ø��ڳ˿�
					{
						select[i] = select[i] + abs((NowFloor - e[i]->NowFloor));
					}
				}
				//�����������
				else
				{
					//���ҵ���λ�ø��ڳ˿�λ��
					if (e[i]->NowFloor >= NowFloor)
					{
						select[i] = select[i] + 40 - abs((NowFloor - e[i]->NowFloor));   //����Խ����Ȩ��Խ��	
					}
					else   //����λ�õ��ڳ˿�
					{
						select[i] = select[i] - abs((NowFloor - e[i]->NowFloor));
					}
				}

			}
		}
	}

	//��select������ȡ���ֵ���±꣬��Ϊ����ѡ�������
	int max = 10;
	for (int i = 9; i >= 0; i--)
	{
		if (select[i] != 0 && (select[max] < select[i]))
		{
			max = i;
		}
	}
	which = max;
	group = (max / 2);

}

