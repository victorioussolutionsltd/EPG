#include "EligibilityService.h"
#include "EligibilityEnums.h"
#include "Exceptions/TechnicalFailureException.h"
#include "Exceptions/InvalidAccountNumberException.h"


#include <set>

struct EligibilityService::Private
{
    std::size_t accountNumber { 0 };
    bool connected { false };
};

EligibilityService::EligibilityService() :
    d(new Private)
{

}

EligibilityService::~EligibilityService()
{

}

void EligibilityService::connect()
{
    d->connected = true;
}

void EligibilityService::disconnect()
{
    d->connected = false;
}

void EligibilityService::setAccountNumber(std::size_t number)
{
    d->accountNumber = number;
}

Eligibility EligibilityService::getEligibility() const
{
    if (!d->connected)
    {
        throw TechnicalFailureException();
    }

    if (d->accountNumber < 1 )
    {
        throw InvalidAccountNumberException();
    }

    Eligibility result { Eligibility::CUSTOMER_INELIGIBLE };

    switch (d->accountNumber)
    {
    case 10: result = Eligibility::CUSTOMER_ELIGIBLE; break;
    default: break;
    }

    return result;
}
