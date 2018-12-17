#include <QtWidgets>

#include "include/MainWindow.h"

MainWindow::MainWindow() :
	textEdit(new QTextEdit)
{
	//setCentralWidget(textEdit);

	createActions();
	createStatusBar();
	// createDockWindows();
	createSplitterWindows();

	setWindowTitle("Dock Widgets");

	newLetter();
}

void MainWindow::createActions()
{
	//new file
	QToolBar *fileToolBar = addToolBar("&File");
	const QIcon newIcon = QIcon::fromTheme("document-new");
	QAction *newAct = new QAction(newIcon, "&New", this);
	newAct->setStatusTip("Create a new file");
	connect(newAct, &QAction::triggered, this, &MainWindow::newLetter);
	//fileMenu->addAction(newAct);
	fileToolBar->addAction(newAct);

	viewMenu = menuBar()->addMenu("&View");

}

void MainWindow::createStatusBar()
{
	statusBar()->showMessage("Ready");
}

void MainWindow::createDockWindows()
{
	QDockWidget *dock = new QDockWidget("Live graph", this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	// customerList = new QListWidget(dock);
	// customerList->addItems(QStringList()
	// 	<<"John Doe" << "Jane Doe");

	QVector<double> x(101), y(101);
	for (int i=0; i<101; i++){
		x[i] = i/50.0 - 1;
		y[i] = x[i]*x[i];
	}
	livePlot = new QCustomPlot(dock);
	livePlot->addGraph();
	livePlot->graph(0)->setData(x,y);
	livePlot->xAxis->setRange(-1,1);
	livePlot->yAxis->setRange(0,1);
	livePlot->replot();

	dock->setWidget(livePlot);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	viewMenu->addAction(dock->toggleViewAction());

	// QDockWidget *dock2 = new QDockWidget("Text edit", this);
	// dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	// dock2->setWidget(textEdit);
	// addDockWidget(Qt::LeftDockWidgetArea, dock2);
	// viewMenu->addAction(dock2->toggleViewAction());
}

void MainWindow::createSplitterWindows()
{
	QSplitter *split = new QSplitter(this);

	// QVector<double> x(101), y(101);
	// for (int i=0; i<101; i++){
	// 	x[i] = i/50.0 - 1;
	// 	y[i] = x[i]*x[i];
	// }
	// livePlot = new QCustomPlot(split);
	// livePlot->addGraph();
	// livePlot->graph(0)->setData(x,y);
	// livePlot->xAxis->setRange(-1,1);
	// livePlot->yAxis->setRange(0,1);
	// livePlot->replot();

	livePlot = new QCustomPlot(this);
	livePlot->addGraph();
	livePlot->graph(0)->setPen(QPen(QColor(40,110,255)));

	QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
	timeTicker -> setTimeFormat("%h:%m:%s");
	livePlot->xAxis->setTicker(timeTicker);
	livePlot->axisRect()->setupFullAxesBox();
	livePlot->yAxis->setRange(-1.5, 1.5);

	connect(livePlot->xAxis, SIGNAL(rangeChanged(QCPRange)), livePlot->xAxis2, SLOT(setRange(QCPRange)));
	connect(livePlot->yAxis, SIGNAL(rangeChanged(QCPRange)), livePlot->xAxis2, SLOT(setRange(QCPRange)));

	split->addWidget(livePlot);
	setCentralWidget(split);


	split->addWidget(textEdit);
	// //split->addWidget(textEdit2);
	split->setStretchFactor(0,1);
	QTimer *dataTimer = new QTimer;
	connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));

	dataTimer->start(0);
}	

void MainWindow::newLetter()
{
	textEdit->clear();
}

void MainWindow::realtimeDataSlot()
{
	static QTime time(QTime::currentTime());
	// calculate two new data points:
	double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
	static double lastPointKey = 0;
	if (key-lastPointKey > 0.002) // at most add point every 2 ms
	{
	  // add data to lines:
	  livePlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
	  //livePlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
	  // rescale value (vertical) axis to fit the current data:
	  livePlot->graph(0)->rescaleValueAxis();
	  //ui->customPlot->graph(1)->rescaleValueAxis(true);
	  lastPointKey = key;
	}
	// make key axis range scroll with the data (at a constant range size of 8):
	// livePlot->xAxis->setRange(key, 8, Qt::AlignRight);
	livePlot->xAxis->setRange(0, key+5);
	livePlot->replot();
	 
	// calculate frames per second:
	static double lastFpsKey;
	static int frameCount;
	++frameCount;
	if (key-lastFpsKey > 2) // average fps over 2 seconds
	{
	  statusBar()->showMessage(
	        QString("%1 FPS, Total Data points: %2")
	        .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
	        .arg(livePlot->graph(0)->data()->size())
	        , 0);
	  lastFpsKey = key;
	  frameCount = 0;
	}
}







