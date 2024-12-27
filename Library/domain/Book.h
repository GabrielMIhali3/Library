#ifndef LIBRARY_BOOK_H
#define LIBRARY_BOOK_H

#include <iostream>
#include <utility>
#include <vector>

using namespace std;


class Book{
private:
    int id{};
    string title;
    string author;
    string description;
    int year_of_publication{};
public:
    Book(int id, string title, string author, string description, int year_of_publication):id{id}, title{std::move(title)}, author{std::move(author)}, description{std::move(description)}, year_of_publication{year_of_publication}{}

    [[nodiscard]] int get_id() const{
        return id;
    };

    [[nodiscard]] string get_title() const{
        return title;
    }

    [[nodiscard]] string get_author() const{
        return author;
    }

    [[nodiscard]] string get_description() const{
        return description;
    }

    [[nodiscard]] int get_year_of_publication() const{
        return year_of_publication;
    }

    bool operator<(const Book& ot) const{
        return id < ot.id;
    }
};

#endif //LIBRARY_BOOK_H
