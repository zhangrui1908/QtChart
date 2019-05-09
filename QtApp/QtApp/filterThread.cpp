#include "filterThread.h"
#include <random>

#include "cppToOc.h"
#include "ecgrawdata.hpp"

#define DATA_LENGTH 200

filterThread::filterThread()
: QThread()
, _listOfFilterResult(DATA_LENGTH)
{
}

filterThread::~filterThread()
{
}

void filterThread::run()
{
	int data_in[DATA_LENGTH] = { 0 };
	int data_out[DATA_LENGTH] = { 0 };
	int *result = NULL;

	resetFiltrtBuffer();

#if 0
	for (int i = 0; i < 75; i++) 
	{
		memcpy(data_in, &ecg_raw_data[i * DATA_LENGTH], DATA_LENGTH * sizeof(int));
		result = filter(data_in, data_out, DATA_LENGTH);
		if (NULL != result && DATA_LENGTH == _listOfFilterResult.size())
		{
			memcpy(_listOfFilterResult.data(), result, sizeof(int)*_listOfFilterResult.size());

			emit send_filter_result(_listOfFilterResult.data(), _listOfFilterResult.size(), i);
		}
		else
		{
			continue;
		}
	}
#endif

	//data input
	/*for (int i = 0; i < DATA_LENGTH; i++)
	{
		std::default_random_engine e;
		std::uniform_int_distribution<int> id(0, 2147483647);
		data_in[i] = id(e);
	}*/
	
	for (int i = 0; i < 75; i++)
	{
		memcpy(data_in, &ecg_raw_data[i * DATA_LENGTH], DATA_LENGTH * sizeof(int));
	}

	result = filter(data_in, data_out, DATA_LENGTH);

	memcpy(_listOfFilterResult.data(), data_out, sizeof(int)*_listOfFilterResult.size());

	emit send_filter_result(_listOfFilterResult.data(), _listOfFilterResult.size());
}