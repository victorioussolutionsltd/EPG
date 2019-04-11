#pragma once

#include "gmock/gmock.h"
#include "../Interfaces/AbstractAccount.h"


class AccountMock : public AbstractAccount
{
public:
    MOCK_METHOD1(setAccountNumber, void(std::size_t));
    MOCK_CONST_METHOD0(getAccountNumber, std::size_t());
    MOCK_METHOD1(setChannelSubscriptions, void(const std::set<Channel> &));
    MOCK_CONST_METHOD0(getChannelSubscriptions, std::set<Channel>());
};

