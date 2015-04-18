//Standard includes
#include <string>
#include <vector>
#include <iostream>

//Third party includes
#include <tclap/CmdLine.h>

//QT specific includes
#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QTableWidget>

//These need to be global
TCLAP::CmdLine cmd("Format text in a table", ' ', "0.5");
TCLAP::ValueArg<int> returnArg("r", "returncollumn", "Column to return data from", false, 0, "column");
TCLAP::ValueArg<std::string> formatArg("f", "format", "The format character.", false, "\t", "format");
TCLAP::UnlabeledMultiArg<std::string> colArg("names", "The names for the collumns. Add as many as you want.", true, "column names");

int main(int argc, char *argv[])
{
	try {

	cmd.add(returnArg);
	cmd.add(colArg);
	cmd.add(formatArg);

	cmd.parse(argc, argv);

	std::vector<std::string> columnNames = colArg.getValue();

	std::vector<std::string> inputList;

	for(std::string line; std::getline(std::cin, line);)
	{

		inputList.push_back(line); //Read from stdin and shove it into the inputList vector.
	}

	QApplication a(argc, argv);
	MainWindow w(NULL, inputList, columnNames);
	w.show();

	return a.exec();
	} catch(TCLAP::ArgException &e) { std::cout<< "Error: " << e.error() << " for " << e.argId() << "\n"; exit(1); }

}