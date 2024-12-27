#ifndef LIBRARY_REPOSITORYBOOK_H
#define LIBRARY_REPOSITORYBOOK_H

#include "../domain/Book.h"

class ExRepository{
    string msg;
public:
    explicit ExRepository(string m): msg{std::move( m )}{
    }
    string get_message(){
        return msg;
    }
};

class RepositoryBook{
protected:
    vector<Book> list;
public:
    /**
     * This function adds a new book to the list.
     * */
    virtual void addBook(const Book& book);


    /**
     * This function modifies an existing book.
     * */
    virtual void modifyBook(const Book& book);


    /**
     * This function deletes an existing book.
     * */
    virtual void deleteBook(int id);


    /**
     * This function searches for an existing book
     * */
    virtual const Book& searchBook(int id);


    /**
     * This function returns the list of books
     * */
    virtual const vector<Book>& getAll();

    virtual ~RepositoryBook() = default;
};

class FileRepositoryBook:public RepositoryBook{
private:
    string file_path;

    void readAll();
    void writeAll();

public:
    explicit FileRepositoryBook(string filePath);

    void addBook(const Book &book) override;

    void modifyBook(const Book &book) override;

    void deleteBook(int id) override;

    const Book &searchBook(int id) override;

    const vector<Book> &getAll() override;
};

#endif //LIBRARY_REPOSITORYBOOK_H
