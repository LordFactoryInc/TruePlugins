// (c) Lord Factory Inc.

#pragma once

#include "CoreMinimal.h"

namespace TrueCommon
{
	/**
	 * An array wrapper with a feature for retrieving a random item from the array.
	 * Each item can be retrieved only once.
	 */
	template<typename T>
	class TRandomQueue
	{
	public:
		void Reserve(int32 InSize)
		{
			mArray.Reserve(InSize);
		}

		int32 Num() const
		{
			return mArray.Num();
		}

		void Add(const T& InItem)
		{
			mArray.Add(InItem);
		}

		const T PopRandom()
		{
			int32 index = FMath::RandHelper(mArray.Num());
			T result = mArray[index];
			mArray.RemoveAtSwap(index, 1, false);
			return result;
		}

	private:
		TArray<T> mArray;
	};

	/**
	 * An array wrapper with a feature for retrieving a random item from the array.
	 * The same item cannot be retrieved more then once if there are other items remaining in the array.
	 */
	template<typename T>
	class TRandomArraySelector
	{
	public:
		void Reserve(int32 InSize)
		{
			mArray.Reserve(InSize);
			mAlreadyReturnedItems.Reserve(InSize);
		}

		int32 Num() const
		{
			return mArray.Num() + mAlreadyReturnedItems.Num();
		}

		void Assign(const TArray<T>& InArray)
		{
			mArray = InArray;
			mAlreadyReturnedItems.Empty(InArray.Num());
		}

		void Assign(TArray<T>&& InArray)
		{
			mArray = std::move(InArray);
			mAlreadyReturnedItems.Empty(InArray.Num());
		}

		void Empty()
		{
			mArray.Empty();
			mAlreadyReturnedItems.Empty();
		}

		void Add(const T& InItem)
		{
			mArray.Add(InItem);
		}

		const T& Front() const
		{
			return mArray[0];
		}

		const T GetRandom()
		{
			int32 index = FMath::RandHelper(mArray.Num());
			T result = mArray[index];

			if (mArray.Num() == 1)
			{
				// We are returning the last element.
				// So do not add it to the already returned items.
				// Just swap these arrays
				// to avoid returning the same item twice in a row (in the next call)

				Swap(mArray, mAlreadyReturnedItems);
			}
			else
			{
				mArray.RemoveAtSwap(index, 1, false);

				mAlreadyReturnedItems.Reserve(mArray.Num());
				mAlreadyReturnedItems.Add(result);
			}

			return result;
		}

	private:
		TArray<T> mArray;
		TArray<T> mAlreadyReturnedItems;
	};
}