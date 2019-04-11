#include "RewardsService.h"
#include "RewardEnums.h"
#include "AbstractAccount.h"
#include "RewardEnums.h"
#include "RewardsFactory.h"
#include "EligibilityService.h"
#include "EligibilityEnums.h"
#include "Exceptions/TechnicalFailureException.h"
#include "Exceptions/InvalidAccountNumberException.h"

#include "AbstractEligibilityService.h"

#include <stdexcept>

namespace
{
    const auto INFORMATION_FOR_THE_USER = "The account number is invalid";
}

struct RewardsService::Private
{
    std::shared_ptr<AbstractAccount> account;
    RewardsFactory rewardsFactory;
    std::shared_ptr<AbstractEligibilityService> eligibleService;
    std::string lastMessage;
    bool isUserEligible { false };

    void checkEligibility();
};

RewardsService::RewardsService(std::shared_ptr<AbstractEligibilityService> eligibilityService) :
    d(new Private)
{
    d->eligibleService = eligibilityService;
}

RewardsService::~RewardsService()
{

}

void RewardsService::connect()
{
    d->eligibleService->connect();
}

void RewardsService::setAccount(const std::shared_ptr<AbstractAccount> account)
{
    d->account = account;
}

void RewardsService::Private::checkEligibility()
{
    try
    {
        isUserEligible = eligibleService->getEligibility() == Eligibility::CUSTOMER_ELIGIBLE;
    }
    catch(InvalidAccountNumberException& )
    {
        lastMessage = INFORMATION_FOR_THE_USER;
    }
    catch(TechnicalFailureException& )
    {

    }
    catch (...)
    {

    }
}

std::set<Reward> RewardsService::getRewards() const
{
    d->lastMessage.clear();

    d->eligibleService->setAccountNumber(d->account->getAccountNumber());

    d->checkEligibility();

    std::set<Reward> rewards;

    if (d->isUserEligible)
    {
        for (const auto& channel : d->account->getChannelSubscriptions())
        {
            const auto rewardForChannel = d->rewardsFactory.getRewardForChannel(channel);
            if(!rewardForChannel.empty())
            {
                rewards.insert(*rewardForChannel.begin());
            }
        }
    }

    return rewards;
}

std::string RewardsService::getLastStatus() const
{
    return d->lastMessage;
}
