#pragma once
class Time
{
	
    public:
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	Time();
	Time( int hour, int minute, int second );
	Time operator + (int sec);   //ʱ��+����λΪ��
	long operator - (Time & sub);
	void set( int hour,int minute,  int second);
	//void operator =(Time &time);
	~Time();
};

