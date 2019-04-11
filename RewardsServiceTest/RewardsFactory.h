#pragma once
#include <set>

enum class Reward;
enum class Channel;

class RewardsFactory
{
public:
    RewardsFactory();
    std::set<Reward> getRewardForChannel(Channel channel) const;

};
