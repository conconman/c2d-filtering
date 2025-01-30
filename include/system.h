#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <iostream>

class System
{
    public:
        System(std::string name, int order);
        ~System(){};
        
        void get_info();
    private:
        std::string name;
        int order;
};

#endif // SYSTEM_H