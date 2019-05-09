#pragma once

#include <QThread>
#include <vector>

class filterThread : public QThread
{
	Q_OBJECT

public:
	filterThread();
	~filterThread();

signals:

	void send_filter_result(const int *filterResult, const int size);

protected:

	void run();

private:

	std::vector<int> _listOfFilterResult;
};
