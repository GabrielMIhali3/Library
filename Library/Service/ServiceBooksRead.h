#ifndef LIBRARY_SERVICEBOOKSREAD_H
#define LIBRARY_SERVICEBOOKSREAD_H

#include "../Repository/RepositoryBooksRead.h"
#include "../Validation/Validation_book.h"
#include "ExService.h"
#include "../UI/Observer.h"

class ServiceBooksRead{
private:
    RepositoryBooksRead* repo{};
    Validation_book validationBook;
public:
    Observable *observable = Observable::getInstance();
    explicit ServiceBooksRead(RepositoryBooksRead* repo): repo{repo}{}

    void AddReadBook(int id, const string& title, const string& author, const string& description, int year_of_publication);

    void DeleteReadBook(int id);

    const vector<Book>& GetBooksRead();

};

#endif //LIBRARY_SERVICEBOOKSREAD_H
