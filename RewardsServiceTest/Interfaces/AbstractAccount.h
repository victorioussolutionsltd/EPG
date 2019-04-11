#pragma once

#include <set>

enum class Channel;


class AbstractAccount
{
public:
    virtual ~AbstractAccount() {}

    virtual void setAccountNumber(std::size_t number) = 0;
    virtual std::size_t getAccountNumber() const = 0;

    virtual void setChannelSubscriptions(const std::set<Channel> &channelSubscriptions) = 0;
    virtual std::set<Channel> getChannelSubscriptions() const = 0;
};

