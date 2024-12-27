//
// Created by mihal on 05.11.2024.
//

#ifndef LIBRARY_UNDO_H
#define LIBRARY_UNDO_H

#include "../Repository/RepositoryBook.h"

class Undo{
public:
    virtual void DoUndo() = 0;

    virtual ~Undo() = default;
};

class UndoAdd:public Undo{
private:
    RepositoryBook& repo;
    Book book;
public:
    UndoAdd(RepositoryBook& repo, const Book& b):repo{repo}, book{b}{}
    void DoUndo() override;
};

class UndoDelete:public Undo{
private:
    RepositoryBook& repo;
    Book book;
public:
    UndoDelete(RepositoryBook& repo, const Book& b):repo{repo}, book{b}{}
    void DoUndo() override;
};

class UndoModify:public Undo{
private:
    RepositoryBook& repo;
    Book book;
public:
    UndoModify(RepositoryBook& repo, const Book& b):repo{repo}, book{b}{}
    void DoUndo() override;
};

#endif //LIBRARY_UNDO_H
