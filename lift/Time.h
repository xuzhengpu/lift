#pragma once
class Time
{
	
    public:
	bool onoff;   //����ʱ���Ƿ���Ч
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	Time();
	Time(unsigned int hour,unsigned int minute,unsigned int second );
	Time operator + (unsigned int sec);   //ʱ��+����λΪ��
	//void operator =(Time &time);
	~Time();
};

