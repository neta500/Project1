#pragma once
#include <iostream>
#include <thread>
#include <spdlog/spdlog.h>
#include <array>
#include <vector>
#include <mutex>
#include <future>
#include "Random.h"

class JobResult
{
public:
	void SetJobIndex(const int index) { _jobIndex = index; }

	void Clear()
	{
		_killCount = 0;
		_completedJobCount = 0;
		_maxJobCount = 0;
	}

	void Update(const int killCount)
	{
		_killCount += killCount;
		_completedJobCount++;
		spdlog::info("[UPDATE] jobIndex: {}, killCount: {}, completedCount: {}", _jobIndex, killCount, _completedJobCount);
	}

	bool IsUsable() const
	{
		return _maxJobCount == 0;
	}

	bool IsCompleted() const
	{
		return _completedJobCount == _maxJobCount;
	}

	int GetKillCount() const { return _killCount; }
	int GetJobIndex() const { return _jobIndex; }
	void SetMaxJobCount(const int count) { _maxJobCount = count; }

private:
	int _jobIndex = 0;
	int _killCount = 0;
	int _completedJobCount = 0;
	std::atomic<int> _maxJobCount = 0;
};

class OJTManager
{
	static constexpr int MAX_JOB_COUNT = 100;
public:
	OJTManager()
	{
		for (int index = 0; index < _resultArray.size(); ++index)
		{
			_resultArray[index].SetJobIndex(index);
		}
	}

	std::optional<int> GetUsableJobIndex() const
	{
		std::scoped_lock lock(_mutex);

		for (const auto& result : _resultArray)
		{
			if (result.IsUsable())
			{
				return result.GetJobIndex();
			}
		}

		return std::nullopt;
	}

	void KillAll()
	{
		const auto jobIndex = GetUsableJobIndex();
		if (jobIndex.has_value() == false)
		{
			spdlog::error("[ERROR] JOB FULL");
			return;
		}

		const auto index = jobIndex.value();
		constexpr int jobCount = 30;
		_resultArray[index].SetMaxJobCount(jobCount);

		for (auto i = 0; i < jobCount; ++i)
		{
			std::thread([index](OJTManager* ojtManager)
				{
					ojtManager->OnKillAll(index, Random::GetRandomInt(1, 100));
				}, this).detach();
		}
	}

	void OnKillAll(const int jobIndex, const int killCount)
	{
		std::scoped_lock lock(_mutex);
		JobResult& result = _resultArray[jobIndex];
		result.Update(killCount);
		if (result.IsCompleted())
		{
			spdlog::info("[COMPLETE] jobIndex: {}, killCount: {}", jobIndex, result.GetKillCount());
			result.Clear();
		}
	}

private:
	mutable std::recursive_mutex _mutex{};
	std::array<JobResult, MAX_JOB_COUNT> _resultArray;
};

OJTManager manager{};

void Function()
{
	manager.KillAll();
}