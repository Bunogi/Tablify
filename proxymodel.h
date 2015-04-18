#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

//We need this in several functions throughout mainwindow.cpp, there was no other way.
QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();

#endif // PROXYMODEL_H

