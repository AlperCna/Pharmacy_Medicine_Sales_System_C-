#ifndef USER_HPP
#define USER_HPP

#include <iostream>

class User {
public:
    User(const std::string& username, const std::string& password);
    virtual ~User();  // Virtual destructor for polymorphism

    virtual void displayMenu() const = 0;  // Pure virtual function

protected:
    std::string username;
    std::string password;
};

#endif // USER_HPP
