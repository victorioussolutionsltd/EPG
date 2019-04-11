#pragma once

#include <memory>
#include "AbstractEligibilityService.h"

enum class Eligibility;

class EligibilityService : public AbstractEligibilityService
{
public:
    EligibilityService();
    virtual ~EligibilityService();
    void connect();
    void disconnect();
    void setAccountNumber(std::size_t number);
    Eligibility getEligibility() const;

private:
    struct Private;
    std::unique_ptr<Private> d;
};
