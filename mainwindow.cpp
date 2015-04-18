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
#include <QTableWidgetItem>
#include <QSortFilterProxyModel>

//Custom headers
#include "arguments.h"
#include "proxymodel.h"

MainWindow::MainWindow(QWidget *parent, std::vector<std::string> input, std::vector<std::string> colNames) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	setMinimumHeight(minHeightArg.getValue());
	setMinimumWidth(minWidthArg.getValue());

	ui->setupUi(this);


	QStandardItemModel *model = new QStandardItemModel(0, 0, this);

	for(int iii = 0; iii < colNames.size(); iii++)
		model->setHorizontalHeaderItem(iii, new QStandardItem(colNames[iii].c_str()));

	for(int iii = 0; iii < input.size(); iii++) //Put input in the table
	{
		std::string line;

		line = input[iii];

		QList<QString> QStringList;

		std::vector<std::string> strs;
		boost::split(strs, line, boost::is_any_of( formatArg.getValue() ));

		for(int kkk = 0; kkk < strs.size(); kkk++)
		{
				QStringList.append(QString(strs[kkk].c_str()));
		}

		QList<QStandardItem*> list;

		for(int jjj = 0; jjj < QStringList.size(); jjj++)
		{
			list.append(new QStandardItem(QStringList[jjj]));
		}

		model->appendRow(list);
	}

	//Used for filtering
	proxyModel->setSourceModel(model);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	proxyModel->setDynamicSortFilter(true);
	//Placeholder
	proxyModel->setFilterKeyColumn(filterColArg.getValue());

	ui->tableView->setModel(proxyModel);
	ui->tableView->horizontalHeader()->setStretchLastSection(true);
	ui->tableView->resizeColumnsToContents();

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
	exit(0);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
	if(arg1 == "" or arg1 == " ") //Do not search for spaces or nothing.
	{
		proxyModel->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
		return;
	}

	proxyModel->setFilterRegExp(QRegExp(arg1, Qt::CaseInsensitive, QRegExp::FixedString));

	/*
	int rows = ui->tableView->model()->rowCount();
	int cols = ui->tableView->model()->columnCount();

	//Search through the entire table for the inputted text.
	//Selects the first entry it finds.
	for(int iii = 0; iii < cols; iii++)
	{
		for(int jjj = 0; jjj < rows; jjj++)
		{
			QString current = ui->tableView->model()->data(ui->tableView->model()->index(jjj, iii)).toString();
			if(current.contains(arg1, Qt::CaseInsensitive))
			{
				ui->tableView->selectRow(jjj);
				return;
			}
		}
	}
	*/
}

void MainWindow::on_lineEdit_returnPressed()
{
	QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();

	QModelIndex index = indexes.at(0);

	int row = index.row();

	QString output = ui->tableView->model()->data(ui->tableView->model()->index( row, returnArg.getValue() )).toString();

	std::cout<< qPrintable(output) << "\n";
	exit(0);
}
