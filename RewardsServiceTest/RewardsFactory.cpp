#include "RewardsFactory.h"
#include "RewardEnums.h"
#include "ChannelEnums.h"

RewardsFactory::RewardsFactory()
{

}

std::set<Reward> RewardsFactory::getRewardForChannel(Channel channel) const
{
    std::set<Reward> result;

    switch (channel)
    {
    case Channel::SPORTS: result.insert(Reward::CHAMPIONS_LEAGUE_FINAL_TICKET); break;
    case Channel::MUSIC:  result.insert(Reward::KARAOKE_PRO_MICROPHONE); break;
    case Channel::MOVIES: result.insert(Reward::PIRATES_OF_THE_CARIBBEAN_COLLECTION); break;
    }

    return result;
}
