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

//Custom headers
#include "arguments.h"

MainWindow::MainWindow(QWidget *parent, std::vector<std::string> input, std::vector<std::string> colNames) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	resize(minWidthArg.getValue(), minHeightArg.getValue());

	QStandardItemModel *model = new QStandardItemModel(0, 0, this);

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
			QStandardItem *tmp = new QStandardItem(QStringList[jjj]);
			/*
			if(QStringList[jjj].toInt() == 0)
				tmp->setData(QVariant(QStringList[jjj].toInt()));
			else
				tmp->setData(QVariant(QStringList[jjj]));
			*/

			list.append(tmp);
		}

		model->appendRow(list);
	}

	if(hideColArg.getValue() > -1 and hideColArg.getValue() <= ui->tableView->model()->rowCount())
		ui->tableView->setColumnHidden(hideColArg.getValue(), true);

	ui->tableView->setModel(model);
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
	if(not closeArg.getValue())
		exit(0);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
	if(arg1 == "" or arg1 == " ") //Do not search for spaces or nothing.
	{
		return;
	}

	unsigned int rows = ui->tableView->model()->rowCount();
	unsigned int cols = ui->tableView->model()->columnCount();

	for(unsigned int iii = 0; iii < rows; iii++)
	{
		ui->tableView->setRowHidden(iii, true); //Hide everything.
	}

	//Search through the entire table for the inputted text.
	//Unhides the matches it finds.
	for(unsigned int iii = 0; iii < rows; iii++)
	{
		for(unsigned int jjj = 0; jjj < cols; jjj++)
		{
			QString current = ui->tableView->model()->data(ui->tableView->model()->index(iii, jjj)).toString();
			if(current.contains(arg1, Qt::CaseInsensitive))
			{
				ui->tableView->setRowHidden(iii, false);
				break;
			}
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
