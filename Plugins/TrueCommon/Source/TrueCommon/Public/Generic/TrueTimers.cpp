// (c) Lord Factory Inc.

#include "TrueTimers.h"

using namespace std::chrono;

namespace TrueCommon
{
	TSimpleTimer::TSimpleTimer()
	{
		Reset();
	}

	void TSimpleTimer::Reset()
	{
		mLastTime = steady_clock::now();
	}

	template<typename TOut, typename TDuration>
	TOut TSimpleTimer::TickDuration()
	{
		TTimePoint now = steady_clock::now();
		TOut delta = duration_cast<duration<TOut, TDuration>>(now - mLastTime).count();
		mLastTime = now;
		return delta;
	}

	float TSimpleTimer::Tick()
	{
		float delta = TickMS() / 1000.0;
		return delta;
	}

	uint32_t TSimpleTimer::TickMS()
	{
		return TickDuration<uint32_t, std::milli>();
	}

	uint64_t TSimpleTimer::TickUS()
	{
		return TickDuration<uint64_t, std::micro>();
	}

	uint64_t TSimpleTimer::TickNS()
	{
		return TickDuration<uint64_t, std::nano>();
	}

	template<typename TOut, typename TDuration>
	TOut TSimpleTimer::ElapsedDuration() const
	{
		TTimePoint now = steady_clock::now();
		TOut delta = duration_cast<duration<TOut, TDuration>>(now - mLastTime).count();
		return delta;
	}

	float TSimpleTimer::Elapsed() const
	{
		float delta = ElapsedMS() / 1000.0;
		return delta;
	}

	uint32_t TSimpleTimer::ElapsedMS() const
	{
		return ElapsedDuration<uint32_t, std::milli>();
	}

	uint64_t TSimpleTimer::ElapsedUS() const
	{
		return ElapsedDuration<uint64_t, std::micro>();
	}

	uint64_t TSimpleTimer::ElapsedNS() const
	{
		return ElapsedDuration<uint64_t, std::nano>();
	}
}