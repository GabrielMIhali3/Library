#include <QApplication>
#include <QPushButton>
#include "Tests/Tests.h"
#include "UI/LibraryUI.h"
#include "Service/ServiceBooksRead.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //Tests::run_all_tests();
    FileRepositoryBooksRead repoBooks{"C:/Users/mihal/CLionProjects/Library/FileBooksRead"};
    ServiceBooksRead serviceBooksRead{&repoBooks};
    FileRepositoryBook repo{"C:/Users/mihal/CLionProjects/Library/Library"};
    Service service{&repo, &serviceBooksRead};
    LibraryUI gui{&service, &serviceBooksRead};

    gui.show();
    return a.exec();
}
