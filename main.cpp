//Standard includes
#include <string>
#include <vector>

//Third party includes
#include <tclap/CmdLine.h>

//QT specific includes
#include "mainwindow.h"
#include <QApplication>
#include <QtGui>

//These need to be global
TCLAP::CmdLine cmd("Format, and search through text in a table.", ' ', "0.9-master");
TCLAP::ValueArg<int> returnArg("r", "returncolumn", "Set the column to return data from. The output of this program will be the value inside ( <selected row>, <value of -r> ) ", false, 0, "column");
TCLAP::ValueArg<std::string> formatArg("f", "format", "The format character. This is where the input is split. Defaults to tab(\\t)", false, "\t", "format");
TCLAP::ValueArg<int> minWidthArg("W", "width", "Starting width of the window.", false, 800, "width");
TCLAP::ValueArg<int> minHeightArg("H", "height", "Starting height of the window.", false, 300, "height");
TCLAP::ValueArg<int> hideColArg("c", "hideCol", "Hide column n", false, -1, "Hidden colum");
TCLAP::SwitchArg closeArg("n", "noclose", "Do not close program after selecting");
TCLAP::UnlabeledMultiArg<std::string> colArg("names", "The names for the collumns, each name you type in will create a new column.",  true, "column names");

int main(int argc, char *argv[])
{
	try {

	cmd.add(returnArg);
	cmd.add(formatArg);
	cmd.add(minWidthArg);
	cmd.add(minHeightArg);
	cmd.add(hideColArg);
	cmd.add(closeArg);

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
