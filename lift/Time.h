#pragma once
class Time
{
	
    public:
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	Time();
	Time(unsigned int hour,unsigned int minute,unsigned int second );
	Time operator + (unsigned int sec);   //时间+，单位为秒
	//void operator =(Time &time);
	~Time();
};

