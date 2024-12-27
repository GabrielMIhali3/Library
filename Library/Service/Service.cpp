//
// Created by mihal on 26.09.2024.
//

#include <algorithm>
#include <set>
#include "Service.h"

void Service::AddBook(int id, const string& title, const string& author, const string& description, int year_of_publication) {
    Book book(id, title, author, description, year_of_publication);

    if (serviceBooksRead != nullptr)
        for (const auto& i: serviceBooksRead->GetBooksRead())
            if (i.get_id() == id)
                throw ExService{"Existent ID"};

    try{
        validation.ValidationBook(book);
    }catch (ExValidation&msg){
        throw ExService(msg.get_message());
    }

    try{
        repo->addBook(book);
        undo.push_back(std::make_unique<UndoAdd>(*repo, book));
        observable->notify();
    }catch (ExRepository&msg){
        throw ExService(msg.get_message());
    }
}

void Service::DeleteBook(int id) {
    try {
        Book book = repo->searchBook(id);
        repo->deleteBook(id);
        undo.push_back(std::make_unique<UndoDelete>(*repo, book));
        observable->notify();
    }catch (ExRepository&msg){
        throw ExService(msg.get_message());
    }
}

void Service::ModifyBook(int id, const string& title, const string& author, const string& description, int year_of_publication) {
    Book book(id, title, author, description, year_of_publication);


    try{
        validation.ValidationBook(book);
    }catch (ExValidation&msg){
        throw ExService(msg.get_message());
    }

    try{
        Book bookUnchanged = repo->searchBook(id);
        repo->modifyBook(book);
        undo.push_back(std::make_unique<UndoModify>(*repo, bookUnchanged));
        observable->notify();
    }catch (ExRepository&msg){
        throw ExService(msg.get_message());
    }


}

const Book &Service::SearchBook(int id) {
    try{
        return repo->searchBook(id);
    }catch (ExRepository&msg){
        throw ExService(msg.get_message());
    }
}

const vector<Book> &Service::GetAll() {
    return repo->getAll();
}

vector<Book> Service::SortAscendingByDate(vector<Book> list) {
    std::sort(list.begin(), list.end(), [&](Book&b1, Book&b2){
        return b1.get_year_of_publication() < b2.get_year_of_publication();
    });
    return list;

}

vector<Book> Service::SortDescendingByDate(vector<Book> list) {
    std::sort(list.begin(), list.end(), [&](Book&b1, Book&b2){
        return b1.get_year_of_publication() > b2.get_year_of_publication();
    });
    return list;
}

vector<Book> Service::FilterByAuthor(vector<Book> list, const string& Author) {
    vector<Book> result;
    std::copy_if(list.begin(), list.end(), std::back_inserter(result), [&](Book&b){
        return b.get_author() == Author;
    });
    return result;
}

vector<Book> Service::FilterByDate(vector<Book> list, int date) {
    vector<Book> result;
    std::copy_if(list.begin(), list.end(), std::back_inserter(result), [&](Book&b){
        return b.get_year_of_publication() == date;
    });
    return result;
}

vector<Book> Service::GetBooksUnread() {
    if (serviceBooksRead == nullptr)
        throw ExService{"ServiceBooksRead is not initialized."};

    vector<Book> booksRead = serviceBooksRead->GetBooksRead();
    vector<Book> books = repo->getAll();
    vector<Book> result;
    copy_if(books.begin(), books.end(), std::back_inserter(result), [&](Book&book){
        return std::find_if(booksRead.begin(), booksRead.end(), [&](Book&book2){
            return book.get_id() == book2.get_id();
        }) == booksRead.end();
    });
    return result;
}

void Service::Undo() {
    if (undo.empty())
        throw ExService{"There aren't operations!"};

    undo.back()->DoUndo();
    undo.pop_back();
    observable->notify();
}

