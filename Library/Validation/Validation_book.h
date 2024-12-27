//
// Created by mihal on 23.09.2024.
//

#ifndef LIBRARY_VALIDATION_BOOK_H
#define LIBRARY_VALIDATION_BOOK_H

#include "../domain/Book.h"

class ExValidation{
    string msg;
public:
    explicit ExValidation(string msg):msg{std::move( msg )}{

    }
    string get_message(){
        return msg;
    }
};

class Validation_book{
public:
    /**
     * This function checks if the book's parameters are valid.
     * */
    void ValidationBook(Book& b);

};

#endif //LIBRARY_VALIDATION_BOOK_H
