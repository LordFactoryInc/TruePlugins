// (c) Lord Factory Inc.

#pragma once

#include <type_traits>

namespace TrueCommon
{
	/**
	 * Switches the state with a delay. Skips the state if it was switched back during the delay.
	 */

	template<typename T>
	class TDelayedStateSwitcher
	{
	public:

		typedef typename std::conditional<sizeof(T) <= sizeof(size_t), T, const T&>::type TParameter;

	public:

		TDelayedStateSwitcher(float InDelay = 1.0f)
			: mState()
			, mNextState()
			, mDelay(InDelay)
			, mLastStateChangeTime(0)
		{}

		TDelayedStateSwitcher(TParameter InState, float InDelay)
			: mState(InState)
			, mNextState(InState)
			, mDelay(InDelay)
			, mLastStateChangeTime(0)
		{}

		void Reset(TParameter InState)
		{
			mState = InState;
			mNextState = InState;
			mLastStateChangeTime = 0;
		}

		float GetDelay() const { return mDelay; }
		void SetDelay(float InDelay) { mDelay = InDelay; }

		TParameter GetNext() const { return mNextState; }
		TParameter GetDelayed() const { return mState; }

		operator TParameter() const { return mState; }

		// Returns true if the state has been changed
		bool Update(TParameter InNextState, float InCurrentTime)
		{
			if (InNextState != mNextState)
			{
				mNextState = InNextState;
				mLastStateChangeTime = InCurrentTime;
			}

			if (mState != mNextState && InCurrentTime - mLastStateChangeTime >= mDelay)
			{
				mState = mNextState;
				return true;
			}

			return false;
		}

	private:
		T mState;
		T mNextState;
		float mDelay;
		float mLastStateChangeTime;
	};
}