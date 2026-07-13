// (c) Lord Factory Inc.

#pragma once

#include <chrono>
#include <functional>

namespace TrueCommon
{
	/**
	 * A convenient wrapper to the std::steady_clock
	 */
	class TSimpleTimer
	{
	public:
		TSimpleTimer();

		void Reset();

		/**
		 * Returns an elapsed time since last tick/reset and resets.
		 */

		float Tick(); // Seconds

		uint32_t TickMS();
		uint64_t TickUS();
		uint64_t TickNS();

		/**
		 * Elapsed time since last tick/reset
		 */

		float Elapsed() const; // Seconds

		uint32_t ElapsedMS() const;
		uint64_t ElapsedUS() const;
		uint64_t ElapsedNS() const;

	private:
		template <typename TOut, typename TDuration>
		TOut TickDuration();

		template <typename TOut, typename TDuration>
		TOut ElapsedDuration() const;

	private:
		typedef std::chrono::steady_clock::time_point TTimePoint;
		TTimePoint mLastTime;
	};

	/**
	 * Scoped Timer - calls user specified func on destruction
	 */

	class TScopedTimer
	{
	public:
		typedef std::function<void(const TSimpleTimer&)> TOnDestructionFunc;

	public:
		TScopedTimer(const TOnDestructionFunc& InOnDestruction)
			: mOnDestruction(InOnDestruction)
		{}

		~TScopedTimer()
		{
			mOnDestruction(mTimer);
		}

	private:
		TOnDestructionFunc mOnDestruction;
		TSimpleTimer mTimer;
	};
}