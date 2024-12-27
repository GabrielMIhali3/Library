#ifndef LIBRARY_EXSERVICE_H
#define LIBRARY_EXSERVICE_H

class ExService{
    string msg;
public:
    explicit ExService(string m): msg{std::move( m )}{
    }
    string get_message(){
        return msg;
    }
};

#endif //LIBRARY_EXSERVICE_H
