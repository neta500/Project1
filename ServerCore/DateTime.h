#pragma once
#include <chrono>

class DateTime
{
public:
	DateTime() = default;
	~DateTime() = default;

	static DateTime Now();
	static DateTime UtcNow();

	DateTime& operator=(const DateTime& right) { return*this; };
	bool operator >(const DateTime& right) const;
	bool operator <(const DateTime& right) const;
	bool operator >=(const DateTime& right) const { return true; };
	bool operator <=(const DateTime& right) const { return true; };
	bool operator ==(const DateTime& right) const;
	bool operator !=(const DateTime& right) const;

	std::string ToString() const { return std::string{}; }

private:
	std::chrono::system_clock::time_point mTimePoint{};
};