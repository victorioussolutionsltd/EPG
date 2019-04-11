#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <memory>

#include "../Account.h"
#include "../ChannelEnums.h"

struct AccountTest : testing::Test
{
    std::unique_ptr<Account> account;

    AccountTest() :
        account(new Account())
    {
    }

    virtual ~AccountTest()
    {
    }
};

TEST_F(AccountTest, setAccountNumber)
{
    account->setAccountNumber(10);
    EXPECT_EQ(10, account->getAccountNumber());
}

TEST_F(AccountTest, setTwoChannelSubscriptions)
{
    const std::set<Channel> twoSubscriptions { Channel::SPORTS, Channel::KIDS };
    account->setChannelSubscriptions(twoSubscriptions);
    EXPECT_EQ(twoSubscriptions, account->getChannelSubscriptions());
}

TEST_F(AccountTest, setFiveChannelSubscriptions)
{
    const std::set<Channel> fiveSubscriptions { Channel::SPORTS, Channel::KIDS, Channel::MUSIC, Channel::NEWS, Channel::MOVIES };
    account->setChannelSubscriptions(fiveSubscriptions);
    EXPECT_EQ(fiveSubscriptions, account->getChannelSubscriptions());
}

