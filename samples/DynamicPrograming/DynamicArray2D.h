#pragma once
#include <cassert>

template <typename T>
class DynamicArray2D
{
private:
	uint16_t m_nRows;
	uint16_t m_nCols;
	T* m_data = nullptr;
public:

	class Line
	{
	private:
		T* m_data;
		uint16_t m_nCols;
	public:
		Line(T* data, uint16_t nCols): m_data(data), m_nCols(nCols) {}
	
		T& operator[](uint16_t col)
		{
			assert(col < m_nCols);			
			return m_data[col];
		}
	};

	DynamicArray2D(uint16_t rows, uint16_t cols) :m_nRows(rows), m_nCols(cols)
	{
		m_data = new T[m_nCols*m_nRows];
	}
	~DynamicArray2D()
	{
		delete m_data;
	}
	Line operator[](uint16_t row)
	{
		assert(row < m_nRows);
		return Line(m_data + (row*m_nCols), m_nCols);
	}
	T* begin()
	{
		return m_data;
	}
	T* end()
	{
		return m_data + (m_nCols * m_nRows);
	}
};
