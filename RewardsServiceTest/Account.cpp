#include "Account.h"

Account::Account()
{

}

Account::~Account()
{

}

void Account::setAccountNumber(std::size_t number)
{
    accountNumber = number;
}

std::size_t Account::getAccountNumber() const
{
    return accountNumber;
}

void Account::setChannelSubscriptions(const std::set<Channel>& channelSubscriptions)
{
    subscriptions = channelSubscriptions;
}

std::set<Channel> Account::getChannelSubscriptions() const
{
    return subscriptions;
}
