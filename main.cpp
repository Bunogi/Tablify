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
TCLAP::CmdLine cmd("Format text in a table", ' ', "0.7-dev");
TCLAP::ValueArg<int> returnArg("r", "returncollumn", "Column to return data from", false, 0, "column");
TCLAP::ValueArg<std::string> formatArg("f", "format", "The format character.", false, "\t", "format");
TCLAP::ValueArg<int> minWidthArg("W", "width", "The minimum width of the window.", false, 800, "width");
TCLAP::ValueArg<int> minHeightArg("H", "height", "The minimum height of the window.", false, 300, "height");
TCLAP::ValueArg<int> filterColArg("c", "filtercolumn", "the column to filter by.", false, 0, "filter");
TCLAP::UnlabeledMultiArg<std::string> colArg("names", "The names for the collumns. Add as many as you want.", true, "column names");

int main(int argc, char *argv[])
{
	try {

	cmd.add(returnArg);
	cmd.add(formatArg);
	cmd.add(minWidthArg);
	cmd.add(minHeightArg);
	cmd.add(filterColArg);

	cmd.add(colArg);

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
