#pragma once

#include <memory>

enum class Eligibility;

class AbstractEligibilityService
{
public:
    virtual ~AbstractEligibilityService() {}
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual void setAccountNumber(std::size_t number) = 0;
    virtual Eligibility getEligibility() const = 0;
};
