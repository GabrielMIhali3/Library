//
// Created by mihal on 29.10.2024.
//

#include <set>
#include "BooksReadUI.h"

void BooksReadUI::initGUI() {
    setLayout(lyMain);

    auto* stLy = new QVBoxLayout;
    stLy->addWidget(lstUnread);
    auto* midLy = new QVBoxLayout;
    auto* drLy = new QHBoxLayout;
    drLy->addWidget(lstRead);

    midLy->addWidget(btnAddReadBook);
    midLy->addWidget(btnDeleteReadBook);

    lyMain->addLayout(stLy);
    lyMain->addLayout(midLy);
    lyMain->addLayout(drLy);
}

void BooksReadUI::loadData(const vector<Book> &booksRead, const vector<Book> &booksUnread) {
    modelRead->setBook(booksRead);
    modelUnread->setBook(booksUnread);

    lstUnread->selectionModel()->clearSelection();
    lstRead->selectionModel()->clearSelection();
}

void BooksReadUI::initConnect() {
    QObject::connect(lstUnread->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
        if (lstUnread->selectionModel()->selectedIndexes().isEmpty()){
            idAdd = -1;
            return;
        }
        auto selIndex = lstUnread->selectionModel()->selectedIndexes().at(0);
        idAdd = selIndex.data(Qt::UserRole).toString().toInt();
    });

    QObject::connect(lstRead->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
        if (lstRead->selectionModel()->selectedIndexes().isEmpty()){
            idDelete = -1;
            return;
        }
        auto selIndex = lstRead->selectionModel()->selectedIndexes().at(0);
        idDelete = selIndex.data(Qt::UserRole).toString().toInt();
    });

    QObject::connect(btnAddReadBook, &QPushButton::clicked, [&](){
        if (idAdd != -1){
            try{
                Book book = service->SearchBook(idAdd);
                serviceBooksRead->AddReadBook(book.get_id(), book.get_title(), book.get_author(), book.get_description(), book.get_year_of_publication());
                loadData(serviceBooksRead->GetBooksRead(), service->GetBooksUnread());
            }catch (ExService&msg){
                QMessageBox::warning(this, "Warning", QString::fromStdString(msg.get_message()));
            }
        }
    });

    QObject::connect(btnDeleteReadBook, &QPushButton::clicked, [&](){
        if (idDelete != -1){
            try{
                serviceBooksRead->DeleteReadBook(idDelete);
                loadData(serviceBooksRead->GetBooksRead(), service->GetBooksUnread());
            }catch (ExService&msg){
                QMessageBox::warning(this, "Warning", QString::fromStdString(msg.get_message()));
            }
        }
    });
}

void BooksReadUI::update() {
    loadData(serviceBooksRead->GetBooksRead(), service->GetBooksUnread());
}

