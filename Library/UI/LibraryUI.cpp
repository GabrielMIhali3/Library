//
// Created by mihal on 15.10.2024.
//

#include <QFormLayout>
#include <QMessageBox>
#include "LibraryUI.h"

void LibraryUI::initGUI() {
    setLayout(lyMain);

    auto *stLy = new QVBoxLayout;

    stLy->addWidget(lst);
    lyMain->addLayout(stLy);

    auto* sortBtn = new QHBoxLayout;
    stLy->addLayout(sortBtn);
    sortBtn->addWidget(btnBooks);
    sortBtn->addWidget(btnSortAscendingByDate);
    sortBtn->addWidget(btnSortDescendingByDate);

    auto* filterBtn = new QHBoxLayout;
    stLy->addLayout(filterBtn);
    filterBtn->addWidget(btnFilterByAuthor);
    filterBtn->addWidget(btnFilterByDate);

    auto *drLy = new QVBoxLayout;
    lyMain->addLayout(drLy);
    auto* formLy = new QFormLayout;
    formLy->addRow("ID:", textID);
    formLy->addRow("Title:", textTitle);
    formLy->addRow("Author:", textAuthor);
    formLy->addRow("Description:", textDescription);
    formLy->addRow("Year:", textYear);
    drLy->addLayout(formLy);

    auto* btnLy = new QHBoxLayout;
    btnLy->addWidget(btnAddBook);
    btnLy->addWidget(btnDeleteBook);
    btnLy->addWidget(btnModifyBook);
    btnLy->addWidget(btnSearchBook);
    drLy->addLayout(btnLy);

    auto* btnUndoLy = new QHBoxLayout{};
    btnUndoLy->addWidget(btnUndo);
    drLy->addLayout(btnUndoLy);

    auto* btnBooksReadLy = new QHBoxLayout;
    stLy->addLayout(btnBooksReadLy);
    btnBooksReadLy->addWidget(btnBooksRead);
}

void LibraryUI::loadData(const vector<Book> &books) {
    model->setBook(books);
    setText();
}

void LibraryUI::initConnect() {
    QObject::connect(btnAddBook, &QPushButton::clicked, [&](){
        int id = textID->text().toInt();
        string title = textTitle->text().toStdString();
        string author = textAuthor->text().toStdString();
        string description = textDescription->text().toStdString();
        int year_of_publication = textYear->text().toInt();

        try{
            service->AddBook(id, title, author, description, year_of_publication);
            loadData(service->GetAll());
        }catch (ExService&msg){
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg.get_message()));
        }
    });

    QObject::connect(btnDeleteBook, &QPushButton::clicked, [&](){
        int id = textID->text().toInt();

        try{
            service->DeleteBook(id);
            loadData(service->GetAll());
        }catch (ExService&msg){
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg.get_message()));
        }
    });

    QObject::connect(btnModifyBook, &QPushButton::clicked, [&](){
        int id = textID->text().toInt();
        string title = textTitle->text().toStdString();
        string author = textAuthor->text().toStdString();
        string description = textDescription->text().toStdString();
        int year_of_publication = textYear->text().toInt();

        try{
            service->ModifyBook(id, title, author, description, year_of_publication);
            loadData(service->GetAll());
        }catch (ExService&msg){
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg.get_message()));
        }
    });

    QObject::connect(btnSearchBook, &QPushButton::clicked, [&](){
        int id = textID->text().toInt();

        try{
            Book book = service->SearchBook(id);
            QString item = "ID: " + QString::number(book.get_id()) +
                    "\nTitle: " + QString::fromStdString(book.get_title()) +
                    "\nAuthor: " + QString::fromStdString(book.get_author()) +
                    "\nDescription: " + QString::fromStdString(book.get_description()) +
                    "\nYear: " + QString::number(book.get_year_of_publication());
            QMessageBox::about(this, "Book found!", item);
        }catch (ExService&msg){
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg.get_message()));
        }
    });

    QObject::connect(lst->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
        if (lst->selectionModel()->selectedIndexes().isEmpty()){
            return;
        }
        auto selIndex = lst->selectionModel()->selectedIndexes().at(0);
        Book book = service->SearchBook(selIndex.data(Qt::UserRole).toString().toInt());
        textID->setText(QString::number(book.get_id()));
        textTitle->setText(QString::fromStdString(book.get_title()));
        textAuthor->setText(QString::fromStdString(book.get_author()));
        textDescription->setText(QString::fromStdString(book.get_description()));
        textYear->setText(QString::number(book.get_year_of_publication()));
    });

    QObject::connect(btnSortAscendingByDate, &QPushButton::clicked, [&](){
        try{
            loadData(Service::SortAscendingByDate(service->GetAll()));
        }catch (ExService&msg){
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg.get_message()));
        }
    });

    QObject::connect(btnSortDescendingByDate, &QPushButton::clicked, [&](){
        try{
            loadData(Service::SortDescendingByDate(service->GetAll()));
        }catch (ExService&msg){
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg.get_message()));
        }
    });

    QObject::connect(btnBooks, &QPushButton::clicked, [&](){
        loadData(service->GetAll());
    });

    QObject::connect(btnFilterByAuthor, &QPushButton::clicked, [&](){
        string author = textAuthor->text().toStdString();
        if (author.empty())
            warning("Empty author textfield!");
        else
            loadData(Service::FilterByAuthor(service->GetAll(), author));
    });
    QObject::connect(btnFilterByDate, &QPushButton::clicked, [&](){
        int year_of_publication = textYear->text().toInt();
        if (year_of_publication == 0)
            warning("Empty year textfield!");
        else
            loadData(Service::FilterByDate(service->GetAll(), year_of_publication));
    });

    QObject::connect(btnBooksRead, &QPushButton::clicked, [&](){
        auto* guiBookRead = new BooksReadUI{serviceBooksRead, service};
        guiBookRead->show();
    });

    QObject::connect(btnUndo, &QPushButton::clicked, [&](){
        try{
            service->Undo();
            loadData(service->GetAll());
        }catch (ExService&msg){
            QMessageBox::warning(this, "Warning", QString::fromStdString(msg.get_message()));
        }
    });
}

void LibraryUI::update() {
    loadData(service->GetAll());
}
