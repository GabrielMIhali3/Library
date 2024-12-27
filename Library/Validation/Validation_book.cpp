#include "Validation_book.h"

void Validation_book::ValidationBook(Book &b) {
    string error;

    if (b.get_id() < 0)
        error += "Invalid ID!\n";
    if (b.get_title().empty())
        error += "Invalid title!\n";
    if (b.get_author().empty())
        error += "Invalid author!\n";
    if (b.get_description().empty())
        error += "Invalid description!\n";
    if (b.get_year_of_publication() < 0)
        error += "Invalid year of publication!\n";

    if (!error.empty())
        throw ExValidation(error);
}
