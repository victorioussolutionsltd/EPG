#pragma once
#include <exception>
#include <iostream>

class TechnicalFailureException : public std::exception
{
public:

    const char * what () const throw ()
    {
        return "Technical failure exception";
    }
};
