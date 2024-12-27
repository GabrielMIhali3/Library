//
// Created by mihal on 23.09.2024.
//

#include <cassert>
#include <fstream>
#include "Tests.h"
#include "../Validation/Validation_book.h"
#include "../Repository/RepositoryBook.h"
#include "../Service/Service.h"

void Tests::domain_tests() {
    Book b1{1, "title1", "author1", "description1", 2020};

    assert(b1.get_id() == 1);
    assert(b1.get_title() == "title1");
    assert(b1.get_author() == "author1");
    assert(b1.get_description() == "description1");
    assert(b1.get_year_of_publication() == 2020);
}

void Tests::validation_tests() {
    Book b1{1, "title1", "author1", "description1", 2020};
    Book b2{-1, "", "", "", -2020};

    Validation_book val;
    val.ValidationBook(b1);

    try{
        val.ValidationBook(b2);
    }catch(ExValidation&msg){
        assert(msg.get_message() == "Invalid ID!\nInvalid title!\nInvalid author!\nInvalid description!\nInvalid year of publication!\n");
    }
}

void Tests::repository_tests() {
    Book b1{1, "title1", "author1", "description1", 2020};
    Book b2{2, "title2", "author2", "description2", 2022};
    Book b3{3, "title3", "author3", "description3", 2010};
    Book b4{4, "title4", "author4", "description4", 2021};

    RepositoryBook repo;

    repo.addBook(b1);
    assert(repo.getAll().size() == 1);
    repo.addBook(b2);
    repo.addBook(b3);
    repo.addBook(b4);
    assert(repo.getAll().size() == 4);

    try{
        repo.addBook(b2);
        assert(false);
    }catch (ExRepository&msg){
        assert(msg.get_message() == "Existent ID");
    }

    try {
        repo.deleteBook(5);
        assert(false);
    } catch (ExRepository&msg){
        assert(msg.get_message() == "Nonexistent ID");
    }
    repo.deleteBook(2);
    assert(repo.getAll().size() == 3);
    Book bModif{3, "t3", "a3", "description3", 2010};
    repo.modifyBook(bModif);
    Book bM3 = repo.searchBook(3);
    assert(bM3.get_id() == 3);
    assert(bM3.get_title() == "t3");
    assert(bM3.get_year_of_publication() == 2010);
    try {
        repo.modifyBook(b2);
        assert(false);
    } catch (ExRepository&msg){
        assert(msg.get_message() == "Nonexistent ID");
    }
    try {
        repo.searchBook(2);
        assert(false);
    } catch (ExRepository&msg){
        assert(msg.get_message() == "Nonexistent ID");
    }

    RepositoryBooksRead repoR;
    repoR.addReadBook(b1);
    repoR.addReadBook(b2);
    repoR.addReadBook(b3);
    repoR.addReadBook(b4);
    assert(repoR.getBooksRead().size() == 4);
    try {
        repoR.deleteReadBook(5);
        assert(false);
    } catch (ExRepository&msg){
        assert(msg.get_message() == "Nonexistent ID");
    }
    repoR.deleteReadBook(2);
    assert(repoR.getBooksRead().size() == 3);
}

void Tests::service_tests() {
    ofstream g("C:/Users/mihal/CLionProjects/Library/Tests/libraryTest");
    g << "";
    g.close();
    FileRepositoryBook repo{"C:/Users/mihal/CLionProjects/Library/Tests/libraryTest"};
    Service service(&repo);

    service.AddBook(1, "title1", "author1", "description1", 2020);
    service.AddBook(2, "title2", "author2", "description2", 2022);
    service.AddBook(3, "title3", "author3", "description3", 2016);
    service.AddBook(4, "title4", "author4", "description4", 1999);

    assert(service.GetAll().size() == 4);
    try{
        service.AddBook(1, "title1", "author1", "description1", 2020);
        assert(false);
    }catch (ExService&msg){
        assert(msg.get_message() == "Existent ID");
    }

    try{
        service.AddBook(-1, "", "", "", -11);
        assert(false);
    }catch (ExService&msg){
        assert(msg.get_message() == "Invalid ID!\nInvalid title!\nInvalid author!\nInvalid description!\nInvalid year of publication!\n");
    }

    service.DeleteBook(3);
    assert(service.GetAll().size() == 3);

    try{
        service.DeleteBook(3);
        assert(false);
    }catch (ExService&msg){
        assert(msg.get_message() == "Nonexistent ID");
    }

    service.ModifyBook(2, "title2", "1234", "description2123", 2022);
    Book b = service.SearchBook(2);
    assert(b.get_id() == 2);
    assert(b.get_description() == "description2123");
}
