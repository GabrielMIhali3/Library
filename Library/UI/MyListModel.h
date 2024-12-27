//
// Created by mihal on 30.10.2024.
//

#ifndef LIBRARY_MYLISTMODEL_H
#define LIBRARY_MYLISTMODEL_H

#include <QAbstractListModel>
#include "../Service/ServiceBooksRead.h"

class MyListModel: public QAbstractListModel{
private:
    vector<Book> list;
public:
    explicit MyListModel(const vector<Book>& lst):list{lst}{}

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void setBook(const vector<Book>& lst);
};


#endif //LIBRARY_MYLISTMODEL_H
