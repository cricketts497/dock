#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QTimer>

class QListWidget;
class QTextEdit;

class MainWindow: public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

private slots:
	void newLetter();
	void realtimeDataSlot();

private:
	void createActions();
	void createStatusBar();
	void createDockWindows();
	void createSplitterWindows();

	QTextEdit *textEdit;
	//QListWidget *customerList;
	QCustomPlot *livePlot;
	QTimer *dataTimer;

	QMenu *viewMenu;
};

#endif //MAIN_WINDOW_H