#ifndef MillisExt_h
#define MillisExt_h

#include <Arduino.h> 

#endif

struct MillisExt {
public:
	MillisExt(unsigned long initialMs);
	MillisExt operator+ (const MillisExt& m);
	MillisExt operator+ (unsigned long ms);
	MillisExt operator- (const MillisExt& m);
	MillisExt operator- (unsigned long ms);
	bool operator< (const MillisExt& m);
	bool operator<= (const MillisExt& m);
	bool operator== (const MillisExt& m);
	bool operator> (const MillisExt& m);
	bool operator>= (const MillisExt& m);
	bool operator!= (const MillisExt& m);
	void checkRollOver();
	char* print();
	double getTotalMillisecond();
private:
	static unsigned long globalLastRead;
	static int globalRollOverCount;
	int rollOverCount;
	unsigned long ms;
};