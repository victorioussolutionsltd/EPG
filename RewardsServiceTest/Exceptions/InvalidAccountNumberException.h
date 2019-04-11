#pragma once
#include <exception>
#include <iostream>

class InvalidAccountNumberException : public std::exception
{
public:
    const char * what () const throw ()
    {
        return "Invalid account number exception";
    }
};
