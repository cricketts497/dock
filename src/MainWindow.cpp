#include <QtWidgets>

#include "include/MainWindow.h"

MainWindow::MainWindow() :
	textEdit(new QTextEdit)
{
	setCentralWidget(textEdit);

	createActions();
	createStatusBar();
	createDockWindows();

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
	QDockWidget *dock = new QDockWidget("Customers", this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	customerList = new QListWidget(dock);
	customerList->addItems(QStringList()
		<<"John Doe" << "Jane Doe");
	dock->setWidget(customerList);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	viewMenu->addAction(dock->toggleViewAction());
}

void MainWindow::newLetter()
{
	textEdit->clear();
}






