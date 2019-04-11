#pragma once

#include <memory>
#include <set>

#include "AbstractAccount.h"

enum class Channel;

class Account : AbstractAccount
{
public:
    Account();
    virtual ~Account();

    void setAccountNumber(std::size_t number);
    std::size_t getAccountNumber() const;

    void setChannelSubscriptions(const std::set<Channel> &channelSubscriptions);
    std::set<Channel> getChannelSubscriptions() const;

private:

    std::size_t accountNumber { 0 };
    std::set<Channel> subscriptions;
};
