#pragma once
class Time
{
	
    public:
	bool onoff;   //决定时间是否有效
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	Time();
	Time(unsigned int hour,unsigned int minute,unsigned int second );
	Time operator + (unsigned int sec);   //时间+，单位为秒
	long operator - (Time & sub);
	//void operator =(Time &time);
	~Time();
};

