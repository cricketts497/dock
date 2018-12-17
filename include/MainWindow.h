#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class QListWidget;
class QTextEdit;

class MainWindow: public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

private slots:
	void newLetter();

private:
	void createActions();
	void createStatusBar();
	void createDockWindows();

	QTextEdit *textEdit;
	QListWidget *customerList;

	QMenu *viewMenu;
};

#endif //MAIN_WINDOW_H