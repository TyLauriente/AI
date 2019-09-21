#ifndef DYNAMICARRAY_INCLUDED_HEADER
#define DYNAMICARRAY_INCLUDED_HEADER

#include<iostream>

template<typename Type>
class Dynamic2DArray
{
public:
	Dynamic2DArray()
		: m_loaded(false)
		, m_rows(0)
		, m_columns(0)
		, m_size(0)
		, m_array(nullptr)
	{}
	Dynamic2DArray(int rows, int columns)
		: m_loaded(true)
		, m_rows(rows)
		, m_columns(columns)
		, m_size(rows*columns)
		, m_array(new Type[m_size])
	{
	}
	~Dynamic2DArray() 
	{
		delete[] m_array;
	}

	//Load array after object initialization
	void Load(int rows, int columns)
	{
		if (!m_loaded && m_array == nullptr)
		{
			m_rows = rows;
			m_columns = columns;
			m_size = m_rows * m_columns;
			m_array = new Type[m_size];
			m_loaded = true;
		}
	}
	
	//Converts a given row and column to a 1 Dimensional array position
	int ConvertToPos(int row, int column) const
	{
		if (m_loaded)
		{
			return (row * m_columns) + column;
		}
		else
		{
			return 0;
		}
	}

	void Set(int row, int column, Type value)
	{
		if (m_loaded)
		{
			if (row >= 0 && row < m_rows && column >= 0 && column < m_columns)
			{
				m_array[ConvertToPos(row, column)] = value;
			}
			else
			{
				std::cout << "Error In Dynamic2DArray: Array index out of bounds" << std::endl;
			}
		}
	}

	void Set(int pos, Type value)
	{
		if (m_loaded)
		{
			if (pos >= 0 && pos < m_size)
			{
				m_array[pos] = value;
			}
			else
			{
				std::cout << "Error In Dynamic2DArray: Array index out of bounds" << std::endl;
			}
		}
	}

	Type Get(int row, int column)
	{
		if (row >= 0 && row < m_rows && column >= 0 && column < m_columns)
		{
			return m_array[ConvertToPos(row, column)];
		}
		else
		{
			return m_array[0];
		}
	}

	Type Get(int pos)
	{
		if (m_loaded)
		{
			if (pos >= 0 && pos < m_size)
			{
				return m_array[pos];
			}
			else
			{
				return m_array[0];
			}
		}
		else
		{
			throw;
		}
	}

	int GetRows() const
	{
		return m_rows;
	}

	int GetColumns() const
	{
		return m_columns;
	}

private:
	bool m_loaded;
	int m_rows;
	int m_columns;
	int m_size;
	Type* m_array;
};

#endif