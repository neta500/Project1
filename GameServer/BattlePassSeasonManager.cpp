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
	return false;
}

bool BattlePassSeasonManager::DeleteSeasonData(const int seasonId)
{
	return false;
}

bool BattlePassSeasonManager::UpdateSeasonData(const int prevSeasonId, const BattlePassSeasonData& seasonData)
{
	return false;
}

bool BattlePassSeasonManager::InsertRewardData(const BattlePassRewardData& rewardData)
{
	return false;
}

bool BattlePassSeasonManager::DeleteRewardData(const std::wstring& rewardId)
{
	return false;
}

bool BattlePassSeasonManager::UpdateRewardData(const BattlePassRewardData& rewardData)
{
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
	return false;
}

bool BattlePassSeasonManager::LoadRewardData()
{
	return false;
}

bool BattlePassSeasonManager::CheckSeasonEnd()
{
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
