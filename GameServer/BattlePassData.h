#pragma once
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
	BattlePassType mType;
	int mLevel;
	int mItemId;
	int mItemAmount;
};

class BattlePassRewardData
{
public:
	std::string mRewardId;
	std::unordered_map<std::pair<BattlePassType, int>, BattlePassReward> mRewardMap;
};

class BattlePassSeasonData
{
public:
	int mSeasonId = 0;
	DateTime mBeginDate;
	DateTime mEndDate;

	std::wstring mRewardId;
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

