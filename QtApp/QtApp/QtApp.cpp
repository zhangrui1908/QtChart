#include "QtApp.h"

#include "QValueAxis.h"
#include "QSplineSeries.h"

QtApp::QtApp(QWidget *parent)
: QMainWindow(parent)
, _qChart(nullptr)
, _qChartView(nullptr)
, _qSplineSeries(nullptr)
, _filterThread(nullptr)
{
	ui.setupUi(this);

	//init
	_qChart = new QChart();
	_qChart->legend()->hide();
	_qChart->setTitle("Qt Chart");

	QValueAxis *axisX = new QValueAxis;
	axisX->setRange(0, 200);
	axisX->setTickCount(10);
	_qChart->addAxis(axisX, Qt::AlignBottom);

	_qSplineSeries = new QSplineSeries;
	*_qSplineSeries << QPointF(1, 5) << QPointF(3.5, 18) << QPointF(4.8, 7.5) << QPointF(10, 2.5);
	_qChart->addSeries(_qSplineSeries);

	QValueAxis *axisY = new QValueAxis;
	axisY->setRange(-50, 50);
	//axisY->setLinePenColor(_qSplineSeries->pen().color());

	_qChart->addAxis(axisY, Qt::AlignLeft);
	_qSplineSeries->attachAxis(axisX);
	_qSplineSeries->attachAxis(axisY);

	/*QList<QPointF> points;
	points << QPointF(1, 0.5) << QPointF(1.5, 4.5) << QPointF(2.4, 2.5) << QPointF(4.3, 12.5)
		<< QPointF(5.2, 3.5) << QPointF(7.4, 16.5) << QPointF(8.3, 7.5) << QPointF(10, 17);
	series->replace(points);*/
	/*series = new QSplineSeries;
	*series << QPointF(1, 0.5) << QPointF(1.5, 4.5) << QPointF(2.4, 2.5) << QPointF(4.3, 12.5)
		<< QPointF(5.2, 3.5) << QPointF(7.4, 16.5) << QPointF(8.3, 7.5) << QPointF(10, 17);
	_qChart->addSeries(series);*/


	_qChartView = new QChartView(_qChart);
	_qChartView->setRenderHint(QPainter::Antialiasing);

	this->setCentralWidget(_qChartView);

	_filterThread = new filterThread();
	if (!_filterThread->isRunning())
		_filterThread->start();

	//thread:
	QObject::connect(_filterThread, SIGNAL(send_filter_result(const int *, const int)),
						this, SLOT(filter_result(const int *, const int)), Qt::QueuedConnection);

}

QtApp::~QtApp()
{
	if (NULL != _filterThread)
	{
		_filterThread->disconnect(this);
		_filterThread->exit();
		_filterThread->deleteLater();
		_filterThread = NULL;
	}
}

void QtApp::filter_result(const int *filterResult, const int size)
{
	if (NULL == filterResult || 0 == size)
		return;

	if (nullptr != _qSplineSeries)
	{
		QList<QPointF> points;
		for (int i = 0; i < size; i++)
		{
			points << QPointF(i, filterResult[i]);
		}
		_qSplineSeries->replace(points);

	}
}