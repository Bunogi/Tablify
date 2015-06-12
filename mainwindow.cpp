//Standard includes
#include <iostream>
#include <vector>
#include <string>

//Third party includes
#include <boost/algorithm/string.hpp>

//QT specific includes
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QList>
#include <QDir>
#include <QTableWidgetItem>
#include <QStandardPaths>
#include <QKeyEvent>
#include <QSortFilterProxyModel>

//Custom headers
#include "arguments.h"

MainWindow::MainWindow(QWidget *parent, std::vector<std::string> input, std::vector<std::string> colNames) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QString path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/tablify/stylesheet.qss";
	QFile styleFile(path);

	styleFile.open(QFile::ReadOnly);

	if(styleFile.pos() == 0)
	{
		QString styleSheet(QLatin1String(styleFile.readAll()));
		qApp->setStyleSheet(styleSheet);
	}
	styleFile.close();

	resize(minWidthArg.getValue(), minHeightArg.getValue());

	QStandardItemModel *model = new QStandardItemModel;

	for(unsigned int iii = 0; iii < colNames.size(); iii++) //Name our columns
		model->setHorizontalHeaderItem(iii, new QStandardItem(colNames[iii].c_str()));

	for(unsigned int iii = 0; iii < input.size(); iii++) //Put input in the table
	{
		std::string line;

		line = input[iii];

		QList<QString> QStringList;

		std::vector<std::string> strs;
		boost::split(strs, line, boost::is_any_of( formatArg.getValue() ));

		for(unsigned int kkk = 0; kkk < strs.size(); kkk++)
		{
			QStringList.append(QString(strs[kkk].c_str()));
		}

		QList<QStandardItem*> list;

		for(int jjj = 0; jjj < QStringList.size(); jjj++)
		{
			QStandardItem *tmp;

			tmp = new QStandardItem(QStringList[jjj]);

			list.append(tmp);
		}

		model->appendRow(list);
	}

	ui->lineEdit->installEventFilter(this);
	QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel;
	proxyModel->setSourceModel(model);
	proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
	ui->tableView->setModel(proxyModel);
	ui->tableView->resizeColumnsToContents();

	if(hideColArg.isSet() and hideColArg.getValue() <= ui->tableView->model()->columnCount())
		ui->tableView->hideColumn(hideColArg.getValue());

	ui->tableView->selectRow(0);

}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
	int row = index.row();

	QString output = ui->tableView->model()->data(ui->tableView->model()->index( row, returnArg.getValue() )).toString();

	std::cout<< qPrintable(output) << "\n";
	if(not closeArg.getValue())
		exit(0);
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
	if(target == ui->lineEdit and event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

		QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
		QModelIndex index = indexes.at(0);
		int row = index.row();
		int rowCount = ui->tableView->model()->rowCount();

		switch(keyEvent->key())
		{
		case Qt::Key_Down:
			for(int iii = row + 1; iii <= rowCount; iii++)
			{
				if(not ui->tableView->isRowHidden(iii))
				{
					ui->tableView->selectRow(iii);
					return true;
				}
			}
			return false;
		case Qt::Key_Up:
			for(int iii = row - 1; iii >= 0; iii--)
			{
				if(not ui->tableView->isRowHidden(iii))
				{
					ui->tableView->selectRow(iii);
					return true;
				}
			}
			break;
		case Qt::Key_End:
			for(int iii = rowCount - 1; iii >= 0; --iii)
			{
				if(not ui->tableView->isRowHidden(iii))
				{
					ui->tableView->selectRow(iii);
					return true;
				}
			}
			break;
		case Qt::Key_Home:
			for(int iii = 0; iii < rowCount; iii++)
			{
				if(not ui->tableView->isRowHidden(iii))
				{
					ui->tableView->selectRow(iii);
					return true;
				}
			}
			break;
		case Qt::Key_PageDown:
			{
			QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_PageDown, Qt::NoModifier);
			QCoreApplication::postEvent(ui->tableView, event);
			return true;
			}
		case Qt::Key_PageUp:
			{
			QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_PageUp, Qt::NoModifier);
			QCoreApplication::postEvent(ui->tableView, event);
			return true;
			}
	}
	}
	return false;
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
	int rows = ui->tableView->model()->rowCount();
	int cols = ui->tableView->model()->columnCount();

	for(int iii = 0; iii < rows; iii++)
	{
		ui->tableView->setRowHidden(iii, true); //Unhide everything.
	}

	//Search through the entire table for the inputted text.
	//Hides everything that doesn't match.
	for(int iii = 0; iii < rows; iii++)
	{
		for(int jjj = 0; jjj < cols; jjj++)
		{
			QString current = ui->tableView->model()->data(ui->tableView->model()->index(iii, jjj)).toString();
			if(current.contains(arg1, Qt::CaseInsensitive))
			{
				ui->tableView->setRowHidden(iii, false);
				break;
			}
		}
	}

	for(int iii = 0; iii < rows; iii++)
	{
		if(not ui->tableView->isRowHidden(iii))
		{
			ui->tableView->selectRow(iii);
			break;
		}
	}
}

void MainWindow::on_lineEdit_returnPressed()
{
	QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();

	QModelIndex index = indexes.at(0);

	int row = index.row();

	QString output = ui->tableView->model()->data(ui->tableView->model()->index( row, returnArg.getValue() )).toString();

	std::cout<< qPrintable(output) << "\n";
	if(not closeArg.getValue())
		exit(0);
}
