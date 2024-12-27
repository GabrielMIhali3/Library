#ifndef LIBRARY_REPOSITORYBOOKSREAD_H
#define LIBRARY_REPOSITORYBOOKSREAD_H

#include <utility>

#include "RepositoryBook.h"
#include "../domain/Book.h"

class RepositoryBooksRead{
protected:
    vector<Book> booksRead;

public:
    virtual void addReadBook(const Book& book);

    virtual void deleteReadBook(int id);

    virtual const vector<Book>& getBooksRead();

    ~RepositoryBooksRead() = default;
};

class FileRepositoryBooksRead: public RepositoryBooksRead{
private:
    string file_path;

    void readAll();
    void writeAll();

public:
    explicit FileRepositoryBooksRead(string file_path): RepositoryBooksRead(), file_path{std::move(file_path)}{}

    void addReadBook(const Book &book) override;

    void deleteReadBook(int id) override;

    const vector <Book> &getBooksRead() override;
};

#endif //LIBRARY_REPOSITORYBOOKSREAD_H
