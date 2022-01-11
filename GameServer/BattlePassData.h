#pragma once
#include <map>
#include <unordered_map>
#include "DateTime.h"

enum class BattlePassType
{
	Normal = 0,
	Premium = 1
};

enum class BattlePassRewardState
{
	CannotReceive = 0,
	CanReceive = 1,
	Received = 2
};

class BattlePassReward
{
public:
	BattlePassReward(const BattlePassType type, const int level, const int itemId, const int itemAmount)
		: mType(type), mLevel(level), mItemId(itemId), mItemAmount(itemAmount)
	{		
	}

	BattlePassType mType = BattlePassType::Normal;
	int mLevel = 0;
	int mItemId = 0;
	int mItemAmount = 0;
};

class BattlePassRewardData
{
public:
	std::string mRewardId{};
	std::map<std::pair<BattlePassType, int>, BattlePassReward> mRewardMap;
};

class BattlePassSeasonData
{
public:
	BattlePassSeasonData() = default;
	BattlePassSeasonData(const int seasonId, const DateTime& beginDate, const DateTime& endDate, const std::string& rewardId)
		: mSeasonId(seasonId), mBeginDate(beginDate), mEndDate(endDate), mRewardId(rewardId) {}

	int mSeasonId = 0;
	DateTime mBeginDate{};
	DateTime mEndDate{};

	std::string mRewardId{};
};

class BattlePassAccountData
{
public:
	int mSeasonId = 0;
	int mLevel = 1;
	int mTotalExp = 1;
	int mDailyExp = 0;

	std::unordered_map<std::pair<BattlePassType, int>, BattlePassRewardState> mAccountRewardMap;
};

