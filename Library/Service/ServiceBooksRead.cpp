//
// Created by mihal on 29.10.2024.
//

#include "ServiceBooksRead.h"

void ServiceBooksRead::AddReadBook(int id, const string& title, const string& author, const string& description, int year_of_publication) {
    Book book(id, title, author, description, year_of_publication);

    try{
        validationBook.ValidationBook(book);
    }catch (ExValidation&msg){
        throw ExService(msg.get_message());
    }

    try{
        repo->addReadBook(book);
        observable->notify();
    }catch (ExRepository&msg){
        throw ExService(msg.get_message());
    }
}

void ServiceBooksRead::DeleteReadBook(int id) {
    try {
        repo->deleteReadBook(id);
        observable->notify();
    }catch (ExRepository&msg){
        throw ExService(msg.get_message());
    }
}

const vector<Book> &ServiceBooksRead::GetBooksRead() {
    return repo->getBooksRead();
}
