#pragma once

template <class T, class A = CUtlMemory<T>> class CUtlVector
{
	typedef A CAllocator;

	public:
		T& operator[](int i)
		{
			return m_Memory[i];
		}

		int Count() const
		{
			return m_Size;
		}
	protected:
		CAllocator m_Memory;
		int m_Size;
		T* m_pElements;
};
