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
				 case 1:
					 status = LEAVE;
					 NextFloor = 1;
				 default :
					 status = LEAVE;
					 NextFloor = (rand() % (40 - 1)) + 1 + 1;
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
				//��õ�ǰ���е�������¥���״̬ 

			 }
			 break;
		 case OVER:
			 break;
	}
		
}
