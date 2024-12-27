#ifndef LIBRARY_LIBRARYUI_H
#define LIBRARY_LIBRARYUI_H

#include "BooksReadUI.h"

class LibraryUI: public QWidget, public Observer{
public:
    explicit LibraryUI(Service* s, ServiceBooksRead* sB){
        service = s;
        service->observable->addObserver(this);
        serviceBooksRead = sB;
        model = new MyListModel(service->GetAll());
        lst->setModel(model);
        initGUI();
        loadData(service->GetAll());
        initConnect();
    }

    ~LibraryUI(){
        service->observable->removeObserver(this);
    }

private:
    Service* service;
    ServiceBooksRead* serviceBooksRead;

    QHBoxLayout* lyMain = new QHBoxLayout{};
    QListView* lst  = new QListView;
    MyListModel* model;

    QLineEdit* textID = new QLineEdit;
    QLineEdit* textTitle = new QLineEdit;
    QLineEdit* textAuthor = new QLineEdit;
    QLineEdit* textDescription = new QLineEdit;
    QLineEdit* textYear = new QLineEdit;

    QPushButton* btnAddBook = new QPushButton{"&Add"};
    QPushButton* btnDeleteBook = new QPushButton{"&Delete"};
    QPushButton* btnModifyBook = new QPushButton{"&Modify"};
    QPushButton* btnSearchBook = new QPushButton{"&Search"};
    QPushButton* btnBooks = new QPushButton{"&Books"};
    QPushButton* btnBooksRead = new QPushButton{"&Books Read"};

    QPushButton* btnSortAscendingByDate = new QPushButton{"Sort ascending by date"};
    QPushButton* btnSortDescendingByDate = new QPushButton{"Sort descending by date"};

    QPushButton* btnFilterByDate = new QPushButton{"Filter by date"};
    QPushButton* btnFilterByAuthor = new QPushButton{"Filter by author"};

    QPushButton* btnUndo = new QPushButton{"&Undo"};

    void setText() {
        textID->setText("");
        textTitle->setText("");
        textAuthor->setText("");
        textDescription->setText("");
        textYear->setText("");
    }

    void warning(const string& msg){
        QMessageBox::warning(this, "Warning", QString::fromStdString(msg));
    }

    void initGUI();

    void loadData(const vector<Book>& books);

    void initConnect();

    void update() override;
};

#endif //LIBRARY_LIBRARYUI_H
