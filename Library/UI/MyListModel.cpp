//
// Created by mihal on 30.10.2024.
//

#include "MyListModel.h"


int MyListModel::rowCount(const QModelIndex &parent) const {
    return list.size();
}

QVariant MyListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole){
        const auto& book = list[index.row()];
        return QString::number(book.get_id()) + ", " + QString::fromStdString(book.get_title()) + ", " + QString::fromStdString(book.get_author()) + ", " + QString::fromStdString(book.get_description()) + ", " + QString::number(book.get_year_of_publication());
    }
    if (role == Qt::UserRole){
        const auto& book = list[index.row()];
        return QString::number(book.get_id());
    }

    return {};
}

void MyListModel::setBook(const vector<Book> &lst) {
    emit layoutAboutToBeChanged();
    this->list = lst;
    emit layoutChanged();
}


