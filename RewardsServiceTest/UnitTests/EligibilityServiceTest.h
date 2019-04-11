#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <memory>

#include "../EligibilityService.h"
#include "../EligibilityEnums.h"
#include "../Exceptions/TechnicalFailureException.h"
#include "../Exceptions/InvalidAccountNumberException.h"

struct EligibilityServiceTest : testing::Test
{
    std::unique_ptr<EligibilityService> eligibilityService;

    EligibilityServiceTest() :
        eligibilityService(new EligibilityService())
    {
    }
};

TEST_F(EligibilityServiceTest, isCustomerNumer10thEligible)
{
    std::size_t customerNumber = 10;
    eligibilityService->connect();
    eligibilityService->setAccountNumber(customerNumber);
    EXPECT_EQ(Eligibility::CUSTOMER_ELIGIBLE, eligibilityService->getEligibility());
}

TEST_F(EligibilityServiceTest, customer1000000IsNotEligible)
{
    std::size_t customerNumber = 1000000;
    eligibilityService->connect();
    eligibilityService->setAccountNumber(customerNumber);
    EXPECT_EQ(Eligibility::CUSTOMER_INELIGIBLE, eligibilityService->getEligibility());
}

TEST_F(EligibilityServiceTest, throwExceptionWhenSuppliedAccountNumberInvalid)
{
    std::size_t customerNumber = 0;
    eligibilityService->connect();
    eligibilityService->setAccountNumber(customerNumber);

    EXPECT_THROW({
                     try
                     {
                         eligibilityService->getEligibility();
                     }
                     catch( const InvalidAccountNumberException& )
                     {
                         throw;
                     }
                 }, std::exception );
}

TEST_F(EligibilityServiceTest, throwExceptionWhenTechnicalError)
{
    std::size_t customerNumber = 10;
    eligibilityService->setAccountNumber(customerNumber);

    EXPECT_THROW({
                     try
                     {
                         eligibilityService->getEligibility();
                     }
                     catch( const TechnicalFailureException& )
                     {
                         throw;
                     }
                 }, std::exception );
}
