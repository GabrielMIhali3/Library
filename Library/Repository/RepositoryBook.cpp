#include "RepositoryBook.h"

#include <utility>
#include <fstream>

void RepositoryBook::addBook(const Book &book) {
    for (const auto & i : list)
        if (i.get_id() == book.get_id())
            throw ExRepository("Existent ID");
    list.push_back(book);
}

void RepositoryBook::modifyBook(const Book &book) {
    int poz = -1;
    for (int i = 0; i < list.size(); i ++)
        if (list[i].get_id() == book.get_id())
            poz = i;
    if (poz == -1)
        throw ExRepository("Nonexistent ID");
    else
        list[poz] = book;
}

void RepositoryBook::deleteBook(int id) {
    int poz = -1;
    for (int i = 0; i < list.size(); i ++)
        if (list[i].get_id() == id)
            poz = i;
    if (poz == -1)
        throw ExRepository("Nonexistent ID");
    else
        list.erase(list.begin() + poz);
}

const Book &RepositoryBook::searchBook(int id) {
    int poz = -1;
    for (int i = 0; i < list.size(); i ++)
        if (list[i].get_id() == id)
            poz = i;
    if (poz > -1)
        return list[poz];
    else
        throw ExRepository("Nonexistent ID");
}

const vector<Book> &RepositoryBook::getAll() {
    return list;
}

FileRepositoryBook::FileRepositoryBook(string filePath) : RepositoryBook(),file_path(std::move(filePath)) {}

void FileRepositoryBook::addBook(const Book &book) {
    readAll();
    RepositoryBook::addBook(book);
    writeAll();
}

void FileRepositoryBook::modifyBook(const Book &book) {
    readAll();
    RepositoryBook::modifyBook(book);
    writeAll();
}

void FileRepositoryBook::deleteBook(int id) {
    readAll();
    RepositoryBook::deleteBook(id);
    writeAll();
}

const Book &FileRepositoryBook::searchBook(int id) {
    readAll();
    return RepositoryBook::searchBook(id);
}

const vector<Book> &FileRepositoryBook::getAll() {
    readAll();
    return RepositoryBook::getAll();
}

void FileRepositoryBook::readAll() {
    ifstream f(file_path);
    if (!f.is_open()){
        throw ExRepository("\nEroare la deschiderea fisierului!");
    }
    int id;
    string title;
    string author;
    string description;
    int year_of_publication;
    RepositoryBook::list.clear();
    while (f >> id >> title >> author >> description >> year_of_publication){
        Book book(id, title, author, description, year_of_publication);
        RepositoryBook::list.push_back(book);
    }
    f.close();
}

void FileRepositoryBook::writeAll() {
    ofstream g(file_path);
    if (!g.is_open()){
        throw ExRepository("\nEroare la deschiderea fisierului!");
    }
    for (const auto& book: RepositoryBook::list){
        g << book.get_id() << "\n";
        g << book.get_title() << "\n";
        g << book.get_author() << "\n";
        g << book.get_description() << "\n";
        g << book.get_year_of_publication() << "\n";
    }
    g.close();
}
