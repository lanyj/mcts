#pragma once


class CMove {
public:
	virtual CMove* clone() = 0;
	virtual void toString() = 0;
	virtual bool equals(CMove* m) = 0;
	virtual ~CMove();
};