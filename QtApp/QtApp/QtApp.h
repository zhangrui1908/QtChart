#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtApp.h"
#include "QChart.h"
#include "QChartView.h"
#include "QSplineSeries.h"

#include "filterThread.h"

QT_CHARTS_USE_NAMESPACE

class QtApp : public QMainWindow
{
	Q_OBJECT

public:
	QtApp(QWidget *parent = Q_NULLPTR);
	~QtApp();

public Q_SLOTS:

	void filter_result(const int *filterResult, const int size);

private:
	Ui::QtAppClass ui;

	QChart *_qChart;
	QChartView *_qChartView;
	QSplineSeries *_qSplineSeries;

	filterThread *_filterThread;
};
