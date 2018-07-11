#pragma once
const int SIZE = 200;

class Averager
{
public:
	Averager();
	void addNum(double addedNum);
	double getAverage();

private:
	int counter = 0;
	double array[SIZE];

};


