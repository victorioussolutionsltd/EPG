#pragma once

#include "gmock/gmock.h"
#include "../Interfaces/AbstractEligibilityService.h"

enum class Eligibility;

class EligibilityServiceMock : public AbstractEligibilityService
{
public:
    MOCK_METHOD0(connect, void());
    MOCK_METHOD0(disconnect, void());
    MOCK_METHOD1(setAccountNumber, void(std::size_t number));
    MOCK_CONST_METHOD0(getEligibility, Eligibility());
};
