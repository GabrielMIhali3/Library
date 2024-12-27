#ifndef LIBRARY_TESTS_H
#define LIBRARY_TESTS_H

class Tests{
private:
    static void domain_tests();
    static void validation_tests();
    static void repository_tests();
    static void service_tests();
public:
    static void run_all_tests(){
        domain_tests();
        validation_tests();
        repository_tests();
        service_tests();
    }
};

#endif //LIBRARY_TESTS_H
