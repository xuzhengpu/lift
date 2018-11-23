#include "pch.h"
#include "Time.h"


Time::Time()
{
	this->hour = 0;
	this->minute = 0;
	this->second = 0;
}

Time::Time(unsigned int hour, unsigned int minute, unsigned int second)
{
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}



Time Time::operator+ (unsigned int sec)
{
	Time time;
	if (sec < 0)
		return time;
	this->second = this->second + sec;
	if (this->second >= 60)
	{
		this->minute = this->minute + this->second / 60;
		this->second = this->second % 60;
		if (this ->minute >= 60)
		{
			this->hour = this->hour + this->minute / 60;
			this->minute = this->minute % 60;
			if (this->hour >= 24)
			{
				this->hour = this->hour - 24;
			}
		}
	}
	time.hour = this->hour;
	time.minute = this->minute ;
	time.second=this->second;
	return time;
}




Time::~Time()
{
}
