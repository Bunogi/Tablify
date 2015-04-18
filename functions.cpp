#include <QModelIndex>

void returnSelected(const QModelIndex &index)
{

	int row = index.row();

	QString hi = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();

	std::cout<< qPrintable(hi) << "\n";
	exit(0);
}
