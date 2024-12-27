//
// Created by mihal on 29.10.2024.
//

#include <fstream>
#include "RepositoryBooksRead.h"

void RepositoryBooksRead::addReadBook(const Book &book) {
    for (const auto & i : booksRead)
        if (i.get_id() == book.get_id())
            throw ExRepository{"Existent ID"};
    booksRead.push_back(book);
}

void RepositoryBooksRead::deleteReadBook(int id) {
    int position = -1;
    for (int i = 0; i < booksRead.size(); i ++)
        if (booksRead[i].get_id() == id)
            position = i;
    if (position == -1)
        throw ExRepository{"Nonexistent ID"};
    booksRead.erase(booksRead.begin() + position);

}

const vector <Book> &RepositoryBooksRead::getBooksRead() {
    return booksRead;
}


void FileRepositoryBooksRead::addReadBook(const Book &book) {
    readAll();
    RepositoryBooksRead::addReadBook(book);
    writeAll();
}

void FileRepositoryBooksRead::deleteReadBook(int id) {
    readAll();
    RepositoryBooksRead::deleteReadBook(id);
    writeAll();
}

const vector<Book> &FileRepositoryBooksRead::getBooksRead() {
    readAll();
    return RepositoryBooksRead::getBooksRead();
}

void FileRepositoryBooksRead::readAll() {
    ifstream f(file_path);
    if (!f.is_open()){
        throw ExRepository("\nEroare la deschiderea fisierului!");
    }
    int id;
    string title;
    string author;
    string description;
    int year_of_publication;
    FileRepositoryBooksRead::booksRead.clear();
    while (f >> id >> title >> author >> description >> year_of_publication){
        Book book(id, title, author, description, year_of_publication);
        FileRepositoryBooksRead::booksRead.push_back(book);
    }
    f.close();

}

void FileRepositoryBooksRead::writeAll() {
    ofstream g(file_path);
    if (!g.is_open()){
        throw ExRepository("\nEroare la deschiderea fisierului!");
    }
    for (const auto& book: FileRepositoryBooksRead::booksRead){
        g << book.get_id() << "\n";
        g << book.get_title() << "\n";
        g << book.get_author() << "\n";
        g << book.get_description() << "\n";
        g << book.get_year_of_publication() << "\n";
    }
    g.close();
}
