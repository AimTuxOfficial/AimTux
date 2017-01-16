#pragma once

template <class T, class I = int> class CUtlMemory
{
	public:
		T& operator[](I i)
		{
			return m_pMemory[i];
		}
	protected:
		T* m_pMemory;
		int m_nAllocationCount;
		int m_nGrowSize;
};
