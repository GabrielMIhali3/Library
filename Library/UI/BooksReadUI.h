#ifndef LIBRARY_BOOKSREADUI_H
#define LIBRARY_BOOKSREADUI_H

#include <QHBoxLayout>
#include <QListView>
#include "../Service/Service.h"
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QWidget>
#include "../Service/ServiceBooksRead.h"
#include <QAbstractListModel>
#include "MyListModel.h"
#include "Observer.h"

class BooksReadUI: public QWidget, public Observer{
public:
    explicit BooksReadUI(ServiceBooksRead* sBooksRead, Service* s){
        serviceBooksRead = sBooksRead;
        service = s;
        modelRead = new MyListModel{serviceBooksRead->GetBooksRead()};
        modelUnread = new MyListModel{service->GetBooksUnread()};
        lstRead->setModel(modelRead);
        lstUnread->setModel(modelUnread);

        initGUI();
        initConnect();

        serviceBooksRead->observable->addObserver(this);
    }

    ~BooksReadUI(){
        serviceBooksRead->observable->removeObserver(this);
    }

private:
    ServiceBooksRead* serviceBooksRead;
    Service* service;

    QHBoxLayout* lyMain = new QHBoxLayout{};

    MyListModel* modelRead;
    MyListModel* modelUnread;
    QListView* lstUnread  = new QListView;
    QListView* lstRead  = new QListView;

    QPushButton* btnAddReadBook = new QPushButton{"&Add"};
    QPushButton* btnDeleteReadBook = new QPushButton{"&Delete"};


    int idAdd = -1;
    int idDelete = -1;

    void initGUI();

    void loadData(const vector<Book>& booksRead, const vector<Book>& booksUnread);

    void initConnect();

    void update() override;

};

#endif //LIBRARY_BOOKSREADUI_H
