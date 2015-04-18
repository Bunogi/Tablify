#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <string>

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0, std::vector<std::string> input={""}, std::vector<std::string> colNames = {""});
	~MainWindow();

private slots:
	void on_tableView_doubleClicked(const QModelIndex &index);

	void on_lineEdit_textChanged(const QString &arg1);

	void on_lineEdit_returnPressed();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
