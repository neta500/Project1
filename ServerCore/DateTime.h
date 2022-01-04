#pragma once
#include <chrono>

class DateTime
{
public:
	DateTime() = default;
	~DateTime() = default;

	static DateTime Now();
	static DateTime UtcNow();

	DateTime& operator=(const DateTime& right);
	bool operator >(const DateTime& right) const;
	bool operator <(const DateTime& right) const;
	bool operator >=(const DateTime& right) const;
	bool operator <=(const DateTime& right) const;
	bool operator ==(const DateTime& right) const;
	bool operator !=(const DateTime& right) const;

private:
	std::chrono::system_clock::time_point mTimePoint{};
};