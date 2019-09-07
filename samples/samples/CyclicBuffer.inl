#pragma once
#include <vector>
#include <assert.h>

template <typename T>
class CyclicBuffer
{
public:
	CyclicBuffer(unsigned int maxSize = 0) : m_nMaxSize(maxSize)
	{
	}

	inline void push_back(const T& data)
	{
		if (arrData.size() < m_nMaxSize)
			arrData.push_back(data);
		else
			arrData[m_nWritePos] = data;

		++m_nWritePos;
		m_nWritePos %= m_nMaxSize;
	}

	inline unsigned int get_size() const
	{
		return arrData.size();
	}

	
	T get_data(unsigned int nPos) const
	{
		assert(nPos < get_size());
		auto read_pos = (m_nWritePos + nPos) % get_size();
		assert(read_pos < get_size());
		return arrData[read_pos];
	}

private:
	unsigned int m_nWritePos = 0;
	unsigned int m_nMaxSize;
	std::vector<T> arrData;
};


