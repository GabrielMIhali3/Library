//
// Created by mihal on 05.11.2024.
//

#include "Undo.h"

void UndoAdd::DoUndo() {
    repo.deleteBook(book.get_id());
}

void UndoDelete::DoUndo() {
    repo.addBook(book);
}

void UndoModify::DoUndo() {
    repo.modifyBook(book);
}
