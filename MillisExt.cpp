#include "MillisExt.h"

unsigned long MillisExt::globalLastRead = 0;
int MillisExt::globalRollOverCount = 0;

MillisExt::MillisExt(unsigned long initialMs) {
	ms = initialMs;
	rollOverCount = globalRollOverCount;
	checkRollOver();
}

void MillisExt::checkRollOver() {
	unsigned long now = millis();
	if(now < globalLastRead)
		globalRollOverCount++;
	globalLastRead = now;
}

double MillisExt::getTotalMillisecond() {
	return (double)ms+(double)rollOverCount*(2^32);
}

char* MillisExt::print() {	
	char print[100];
	snprintf(print, 100, "%lu(%d)", ms, rollOverCount);
	return print;
}

MillisExt MillisExt::operator+(const MillisExt& m)
{
	MillisExt tmp(0);
	tmp.rollOverCount = this->rollOverCount + m.rollOverCount;
	tmp.ms = this->ms + m.ms;
	if(tmp.ms < this->ms)
		tmp.rollOverCount++;
	return tmp;
}

MillisExt MillisExt::operator+(const unsigned long ms)
{
	MillisExt tmp(0);
	tmp.rollOverCount = this->rollOverCount;
	tmp.ms = this->ms + ms;
	if(tmp.ms < ms)
		tmp.rollOverCount++;
	return tmp;
}

MillisExt MillisExt::operator-(const MillisExt& m)
{
	MillisExt tmp(0);
	tmp.rollOverCount = this->rollOverCount - m.rollOverCount;
	tmp.ms = this->ms - m.ms;
	if(tmp.ms > this->ms)
		tmp.rollOverCount--;
	return tmp;
}

MillisExt MillisExt::operator-(const unsigned long ms)
{
	MillisExt tmp(0);
	tmp.rollOverCount = this->rollOverCount;
	tmp.ms = this->ms - ms;
	if(tmp.ms > this->ms) {
		tmp.rollOverCount--;
	}
	return tmp;
}

bool MillisExt::operator==(const MillisExt& m)
{
	if(this->rollOverCount != m.rollOverCount) return false;
	return this->ms == m.ms;
}

bool MillisExt::operator!=(const MillisExt& m)
{
	if(this->rollOverCount != m.rollOverCount) return true;
	return this->ms != m.ms;
}

bool MillisExt::operator<(const MillisExt& m)
{
	if(this->rollOverCount > m.rollOverCount) return false;
	if(this->rollOverCount < m.rollOverCount) return true;
	return this->ms < m.ms;
}

bool MillisExt::operator<=(const MillisExt& m)
{
	if(this->rollOverCount > m.rollOverCount) return false;
	if(this->rollOverCount < m.rollOverCount) return true;
	return this->ms <= m.ms;
}

bool MillisExt::operator>(const MillisExt& m)
{
	if(this->rollOverCount < m.rollOverCount) return false;
	if(this->rollOverCount > m.rollOverCount) return true;
	return this->ms > m.ms;
}

bool MillisExt::operator>=(const MillisExt& m)
{
	if(this->rollOverCount < m.rollOverCount) return false;
	if(this->rollOverCount > m.rollOverCount) return true;
	return this->ms >= m.ms;
}