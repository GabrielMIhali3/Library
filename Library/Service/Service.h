#ifndef LIBRARY_SERVICE_H
#define LIBRARY_SERVICE_H

#include <memory>
#include "../Repository/RepositoryBook.h"
#include "../Validation/Validation_book.h"
#include "ServiceBooksRead.h"
#include "Undo.h"


class Service{
private:
    RepositoryBook* repo{nullptr};
    Validation_book validation;
    ServiceBooksRead* serviceBooksRead{};
    vector<std::unique_ptr<Undo>> undo;
public:
    Observable *observable = Observable::getInstance();

    explicit Service(RepositoryBook* repository): repo{repository}{}
    explicit Service(RepositoryBook* repository, ServiceBooksRead* s): repo{repository}, serviceBooksRead{s}{}

    /**
     * This function adds a new book in the list, but this
     * new book is validated and then it adds to the list.
     * If the new card is not valid or exists, then this function throws an exception
     * */
    void AddBook(int id, const string& title, const string& author, const string& description, int year_of_publication);


    /**
     * This function deletes an existing book to the list.
     * If it doesn't exist, this function throws an exception
     * */
    void DeleteBook(int id);


    /**
     * This function modifies an existing book, but this
     * book is validated and then it modifies to the list.
     * If the new card is not valid or exists, then this function throws an exception
     * */
    void ModifyBook(int id, const string& title, const string& author, const string& description, int year_of_publication);


    const Book& SearchBook(int id);


    const vector<Book>& GetAll();

    static vector<Book> SortAscendingByDate(vector<Book> list);

    static vector<Book> SortDescendingByDate(vector<Book> list);

    static vector<Book> FilterByAuthor(vector<Book> list, const string& Author);

    static vector<Book> FilterByDate(vector<Book> list, int date);

    vector<Book> GetBooksUnread();

    void Undo();
};

#endif //LIBRARY_SERVICE_H
