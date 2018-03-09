#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

class Person
{
public:
    Person();
    ~Person();

    Person(const char* first_name, const char* last_name, int year);
    Person(Person& person);
    Person& Person::operator=(Person& person);

    bool setFirstName(const char* first_name);
    bool setLastName(const char* last_name);
    bool setYearOfBirth(const int year);
    bool display();

    char* getFirstName();
    char* getLastName();
    int getYearOfBirth();
    int getCount();

    int raiseCount();


private:
    char* first_name_;
    char* last_name_;
    int year_of_birth_;
    static int count_;
};

