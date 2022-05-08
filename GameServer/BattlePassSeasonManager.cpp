#include "pch.h"
#include "BattlePassSeasonManager.h"

void BattlePassSeasonManager::LoadManager()
{
	if (false == LoadSeasonData())
	{
		spdlog::error("BattlePassSeasonManager::LoadSeasonData failed");
		return;
	}

	if (false == LoadRewardData())
	{
		spdlog::error("BattlePassSeasonManager::LoadRewardData failed");
	}

	mLoadSuccess = true;
}

void BattlePassSeasonManager::StartManager()
{
	if (true == mLoadSuccess)
	{
		OnTick();
	}
}

bool BattlePassSeasonManager::IsSeasonNow() const
{
	READ_LOCK;
	return mCurrentSeasonData.mSeasonId > 0;
}

bool BattlePassSeasonManager::IsValidSeason(const int seasonId) const
{
	READ_LOCK;

	if (mSeasonMap.contains(seasonId))
	{
		return true;
	}

	return false;
}

bool BattlePassSeasonManager::StartBattlePassSeason(const int seasonId)
{
	WRITE_LOCK;

	if (const auto seasonData = mSeasonMap.find(seasonId);
		seasonData != mSeasonMap.cend())
	{
		mCurrentSeasonData = seasonData->second;

		spdlog::info("BattlePass Season Start: {} StartDate: {} EndDate: {}",
			seasonId, mCurrentSeasonData.mBeginDate.ToString(), mCurrentSeasonData.mEndDate.ToString());
	}

	return false;
}

void BattlePassSeasonManager::EndBattlePassSeason()
{
	WRITE_LOCK;
		
	spdlog::info("BattlePass Season End: {}", mCurrentSeasonData.mSeasonId);
	mCurrentSeasonData = BattlePassSeasonData{};
}

bool BattlePassSeasonManager::InsertSeasonData(const BattlePassSeasonData& seasonData)
{
	WRITE_LOCK;

	if (mSeasonMap.contains(seasonData.mSeasonId))
	{
		spdlog::error("InsertSeasonData failed. (Duplicate BattlePass SeasonId: {})", seasonData.mSeasonId);
		return false;
	}

	if (false == mRewardMap.contains(seasonData.mRewardId))
	{
		spdlog::error("InsertSeasonData failed. (Not Exists BattlePass RewardId: {})", seasonData.mRewardId);
		return false;
	}

	//DBCommand<SP::InsertBattlePassSeason> dbCommand
	//{
	//	seasonData.mSeasonId,
	//	seasonData.mBeginDate,
	//	seasonData.mEndDate,
	//	seasonData.mRewardId
	//};

	//if (dbCommand.Execute())
	//{
	//	mSeasonMap.emplace(seasonData.mSeasonId, seasonData);
	//	return true;
	//}

	return false;
}

bool BattlePassSeasonManager::DeleteSeasonData(const int seasonId)
{
	WRITE_LOCK;

	if (false == mSeasonMap.contains(seasonId))
	{
		spdlog::error("DeleteSeasonData failed. (Invalid SeasonId: {})", seasonId);
		return false;
	}

	//DBCommand<SP::DeleteBattlePassSeason> dbCommand{ seasonId };

	//if (dbCommand.Execute())
	//{
	//	mSeasonMap.erase(seasonId);

	//	spdlog::info("BattlePassSeason deleted. SeasonId: {}", seasonId);

	//	if (mCurrentSeasonData.mSeasonId == seasonId)
	//	{
	//		EndBattlePassSeason();
	//	}

	//	return true;
	//}

	return false;
}

bool BattlePassSeasonManager::UpdateSeasonData(const int prevSeasonId, const BattlePassSeasonData& seasonData)
{
	WRITE_LOCK;

	if (false == mSeasonMap.contains(prevSeasonId))
	{
		spdlog::error("UpdateBattlePassSeason failed. (Invalid SeasonId: {})", prevSeasonId);
		return false;
	}

	//DBCommand<SP::UpdateBattlePassSeason> dbCommand
	//{
	//	prevSeasonId,
	//	seasonData.mSeasonId,
	//	seasonData.mBeginDate,
	//	seasonData.mEndDate,
	//	seasonData.mRewardId
	//};

	//if (dbCommand.Execute())
	//{
	//	if (mCurrentSeasonData.mSeasonId == prevSeasonId && seasonData.mSeasonId == prevSeasonId)
	//	{
	//		mCurrentSeasonData.mEndDate = seasonData.mEndDate;
	//	}

	//	if (const auto& foundSeason = mSeasonMap.find(prevSeasonId); foundSeason != mSeasonMap.cend())
	//	{
	//		foundSeason->second.mEndDate = seasonData.mEndDate;
	//	}
	//	else
	//	{
	//		mSeasonMap.erase(prevSeasonId);
	//		mSeasonMap.emplace(seasonData.mSeasonId, seasonData);
	//	}

	//	return true;
	//}

	return false;
}

bool BattlePassSeasonManager::InsertRewardData(const BattlePassRewardData& rewardData)
{
	WRITE_LOCK;

	if (mRewardMap.contains(rewardData.mRewardId))
	{
		spdlog::error("InsertBattlePassReward failed. (Duplicate RewardId: {})", rewardData.mRewardId);
		return false;
	}

	//for (const auto& reward : rewardData.mRewardMap | std::views::values)
	//{
	//	DBCommand<SP::InsertBattlePassReward> dbCommand
	//	{
	//		rewardData.mRewardId,
	//		static_cast<int>(reward.mType),
	//		reward.mLevel,
	//		reward.mItemId,
	//		reward.mItemAmount
	//	};

	//	if (false == dbCommand.Execute())
	//	{
	//		return false;
	//	}
	//}

	//mRewardMap.emplace(rewardData.mRewardId, rewardData);	

	return true;
}

bool BattlePassSeasonManager::DeleteRewardData(const std::string& rewardId)
{
	WRITE_LOCK;

	if (false == mRewardMap.contains(rewardId))
	{
		spdlog::error("DeleteBattlePassReward failed. (Invalid RewardId: {})", rewardId);
		return false;
	}

	//DBCommand<SP::DeleteBattlePassReward> dbCommand{ rewardId };

	//if (dbCommand.Execute())
	//{
	//	mRewardMap.erase(rewardId);
	//	return true;
	//}

	return false;
}

OptionalRef<const BattlePassSeasonData> BattlePassSeasonManager::GetSeasonData(const int seasonId) const
{
	READ_LOCK;

	if (const auto& seasonData = mSeasonMap.find(seasonId);
		seasonData != mSeasonMap.cend())
	{
		return std::ref(seasonData->second);
	}

	return std::nullopt;
}

void BattlePassSeasonManager::OnTick()
{
	spdlog::info("BattlePassSeasonManager::CheckInterval");

	if (IsSeasonNow())
	{
		if (true == CheckSeasonEnd())
		{
			EndBattlePassSeason();
		}
	}
	else
	{
		if (const auto startableSeasonId = GetStartableSeasonId(DateTime::Now());
			startableSeasonId.has_value())
		{
			StartBattlePassSeason(startableSeasonId.value());
		}
	}

	DoTimer(TickInterval, &BattlePassSeasonManager::OnTick);
}

bool BattlePassSeasonManager::LoadSeasonData()
{
	/*int seasonId;
	DateTime beginDate;
	DateTime endDate;
	std::string rewardId;

	WRITE_LOCK;*/

	//DBCommand<SP::LoadBattlePassSeason> dbCommand
	//{
	//	seasonId,
	//	beginDate,
	//	endDate,
	//	rewardId
	//};

	//if (dbCommand.Execute())
	//{
	//	while (dbCommand.Fetch())
	//	{
	//		mSeasonMap.emplace(seasonId, BattlePassSeasonData{ seasonId, beginDate, endDate, rewardId });
	//	}

	//	return true;
	//}

	return false;
}

bool BattlePassSeasonManager::LoadRewardData()
{
	std::string rewardId;
	int rewardType = 0;
	int rewardLevel = 0;
	int itemId = 0;
	int itemAmount = 0;

	const auto emplacePair = std::pair{
					std::pair{ static_cast<BattlePassType>(rewardType), rewardLevel},
					BattlePassReward
					{
						static_cast<BattlePassType>(rewardType),
						rewardLevel,
						itemId,
						itemAmount
					} };

	WRITE_LOCK;

	//DBCommand<SP::LoadBattlePassReward> dbCommand
	//{
	//	rewardId,
	//	rewardType,
	//	rewardLevel,
	//	itemId,
	//	itemAmount
	//};

	//if (dbCommand.Execute())
	//{
	//	while (dbCommand.Fetch())
	//	{
	//		if (const auto& rewardData = mRewardMap.find(rewardId); rewardData != mRewardMap.cend())
	//		{
	//			rewardData->second.mRewardMap.emplace(emplacePair);
	//		}
	//		else
	//		{
	//			const auto& [newRewardData, success] = mRewardMap.emplace(rewardId, BattlePassRewardData{});
	//			if (success)
	//			{
	//				newRewardData->second.mRewardId = rewardId;
	//				newRewardData->second.mRewardMap.emplace(emplacePair);
	//			}
	//		}
	//	}

	//	return true;
	//}

	return false;
}

bool BattlePassSeasonManager::CheckSeasonEnd()
{
	READ_LOCK;

	if (mCurrentSeasonData.mEndDate <= DateTime::Now())
	{
		return true;
	}

	return false;
}

std::optional<int> BattlePassSeasonManager::GetStartableSeasonId(const DateTime & currentTime) const
{
	READ_LOCK;

	const auto season = std::ranges::find_if(mSeasonMap,
		[currentTime](const auto& seasonIter)
		{
			return seasonIter.second.mBeginDate <= currentTime && currentTime <= seasonIter.second.mEndDate;
		});

	if (season != mSeasonMap.cend())
	{
		return season->second.mSeasonId;
	}

	return std::nullopt;
}
