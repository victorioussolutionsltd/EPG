#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <memory>

#include "../Mocks/AccountMock.h"
#include "../Mocks/EligibilityServiceMock.h"

#include "../Interfaces/AbstractEligibilityService.h"
#include "../Exceptions/InvalidAccountNumberException.h"

#include "../RewardsService.h"
#include "../ChannelEnums.h"
#include "../RewardEnums.h"
#include "../EligibilityEnums.h"


std::shared_ptr<AccountMock> produceAccountMockWithInvalidNumber()
{
    std::shared_ptr<AccountMock> accountMock = std::make_shared<AccountMock>();

    EXPECT_CALL(*accountMock, getAccountNumber())
          .Times(testing::AtLeast(1));

    ON_CALL(*accountMock, getAccountNumber())
          .WillByDefault(testing::Return(0));

    return accountMock;
}

struct RewardsServiceTest : testing::Test
{
    std::shared_ptr<EligibilityServiceMock> eligiblityServiceMock;
    std::unique_ptr<RewardsService> rewardsService;

    RewardsServiceTest() :
        eligiblityServiceMock(std::make_shared<EligibilityServiceMock>()),
        rewardsService(new RewardsService(eligiblityServiceMock))
    {
    }

    virtual ~RewardsServiceTest()
    {
    }


    void setupForInvalidAccountNumber()
    {
        EXPECT_CALL(*eligiblityServiceMock, connect())
              .Times(testing::AtLeast(1));

        rewardsService->connect();
        rewardsService->setAccount(produceAccountMockWithInvalidNumber());
    }

};

TEST_F(RewardsServiceTest, relevantRewardsForCustomerPortfolio)
{
    std::shared_ptr<AccountMock> accountMock = std::make_shared<AccountMock>();

    EXPECT_CALL(*eligiblityServiceMock, connect())
          .Times(testing::AtLeast(1));

    rewardsService->connect();
    rewardsService->setAccount(accountMock);

    EXPECT_CALL(*accountMock, getAccountNumber())
          .Times(testing::AtLeast(1));

    ON_CALL(*accountMock, getAccountNumber())
          .WillByDefault(testing::Return(10));

    EXPECT_CALL(*accountMock, getChannelSubscriptions())
          .Times(testing::AtLeast(1));

    ON_CALL(*accountMock, getChannelSubscriptions())
            .WillByDefault(testing::Return(std::set<Channel>({Channel::SPORTS, Channel::KIDS})));

    EXPECT_CALL(*eligiblityServiceMock, setAccountNumber(10))
          .Times(testing::AtLeast(1));

    EXPECT_CALL(*eligiblityServiceMock, getEligibility())
          .Times(testing::AtLeast(1));

    ON_CALL(*eligiblityServiceMock, getEligibility())
            .WillByDefault(testing::Return(Eligibility::CUSTOMER_ELIGIBLE));


    const auto rewards = rewardsService->getRewards();
    std::set<Reward> expectedRewards { Reward::CHAMPIONS_LEAGUE_FINAL_TICKET };
    EXPECT_EQ(expectedRewards, rewards);
}

TEST_F(RewardsServiceTest, noRewardsForIneligibleCustomer)
{
    std::shared_ptr<AccountMock> accountMock = std::make_shared<AccountMock>();

    EXPECT_CALL(*accountMock, getAccountNumber())
          .Times(testing::AtLeast(1));

    ON_CALL(*accountMock, getAccountNumber())
          .WillByDefault(testing::Return(11));

    EXPECT_CALL(*eligiblityServiceMock, setAccountNumber(11))
          .Times(testing::AtLeast(1));

    EXPECT_CALL(*eligiblityServiceMock, connect())
          .Times(testing::AtLeast(1));

    rewardsService->connect();
    rewardsService->setAccount(accountMock);


    EXPECT_CALL(*eligiblityServiceMock, getEligibility())
          .Times(testing::AtLeast(1));

    ON_CALL(*eligiblityServiceMock, getEligibility())
            .WillByDefault(testing::Return(Eligibility::CUSTOMER_INELIGIBLE));

    const auto rewards = rewardsService->getRewards();
    EXPECT_EQ(0, rewards.size());
}


TEST_F(RewardsServiceTest, noRewardsWhenServiceTechnicalFailure)
{
    std::shared_ptr<AccountMock> accountMock = std::make_shared<AccountMock>();

    EXPECT_CALL(*accountMock, getAccountNumber())
          .Times(testing::AtLeast(1));

    ON_CALL(*accountMock, getAccountNumber())
          .WillByDefault(testing::Return(10));

    EXPECT_CALL(*eligiblityServiceMock, setAccountNumber(10))
          .Times(testing::AtLeast(1));

    rewardsService->setAccount(accountMock);

    EXPECT_CALL(*eligiblityServiceMock, getEligibility())
          .Times(testing::AtLeast(1));

    std::set<Reward> rewards = rewardsService->getRewards();

    EXPECT_EQ(0, rewards.size());
}

TEST_F(RewardsServiceTest, noRewardsWhenAccountNumberIsInvalid)
{
    setupForInvalidAccountNumber();

    EXPECT_CALL(*eligiblityServiceMock, setAccountNumber(0))
          .Times(testing::AtLeast(1));

    EXPECT_CALL(*eligiblityServiceMock, getEligibility())
          .Times(testing::AtLeast(1));

    const auto rewards = rewardsService->getRewards();

    EXPECT_EQ(0, rewards.size());
}


TEST_F(RewardsServiceTest, userNotificationWhenAccountNumberIsInvalid)
{
    setupForInvalidAccountNumber();

    EXPECT_CALL(*eligiblityServiceMock, setAccountNumber(0))
          .Times(testing::AtLeast(1));

    ON_CALL(*eligiblityServiceMock, getEligibility())
            .WillByDefault(testing::Return(Eligibility::CUSTOMER_INELIGIBLE));

    EXPECT_CALL(*eligiblityServiceMock, getEligibility())
      .Times(1)
      .WillRepeatedly(testing::Throw(InvalidAccountNumberException()));


    rewardsService->getRewards();

    EXPECT_EQ("The account number is invalid", rewardsService->getLastStatus());
}

