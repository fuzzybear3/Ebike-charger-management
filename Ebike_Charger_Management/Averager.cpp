#include "Averager.h"

Averager::Averager()
{
}

void Averager::addNum(double addedNum)
{
	counter++;
	if (counter >= SIZE)
	{
		counter = 0;
	}

	array[counter] = addedNum;


}

double Averager::getAverage()
{
	double total = 0;

	for (int i = 0; i < SIZE; i++)
	{
		total += array[i];
	}

	return total / SIZE;
}
