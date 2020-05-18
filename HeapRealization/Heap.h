#pragma once
#ifndef HEAP
#define HEAP
#include <algorithm>


template<class T, class Comp = std::greater<T>>
class Heap
{
private:
	size_t _size, capacity;
	T* arr;
	bool (*comparator)(T a, T b) = nullptr;
	void heapify_up(size_t i);
	void heapify_down(size_t i);
	Comp comp;
public:
	T& operator[](size_t ind);
	Heap(size_t capacity);
	void insert(T x);
	T* data();
	size_t size();
	T pop();
	T head();
	void remove(size_t ind);
	class Iterator {
	public:
		Iterator(T* iter) : iter(iter) {};
		Iterator& operator++()
		{
			iter++;
			return *this;
		}
		bool operator != (const Iterator& x) const
		{
			return iter != x.iter;
		}

		T operator*() const
		{
			return *iter;
		}
	private:
		T* iter;
	};
	Iterator begin()
	{
		return Iterator(arr);
	}
	Iterator end()
	{
		return Iterator(arr + _size);
	}
};

template <class T, class Comp>
Heap<T, Comp>::Heap(size_t size) : capacity(size), comp(Comp())
{
	arr = new T[capacity];
	this->_size = 0;
}

template <class T, class Comp>
void Heap<T, Comp>::insert(T x)
{
	arr[_size] = x;
	if (_size >= 1 && comp(arr[_size - 1], arr[_size]))
		heapify_up(_size);
	_size++;
}

template <class T, class Comp>
void Heap<T, Comp>::heapify_up(size_t i)
{
	size_t j;
	T tmp;
	while (i > 0)
	{
		j = i / 2;
		if (comp(arr[j],arr[i]))
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i = j;
		}
		else
			break;
	}
}

template<class T, class Comp>
T* Heap<T, Comp>::data()
{
	return arr;
}

template<class T, class Comp>
T& Heap<T, Comp>::operator[](size_t ind)
{
	if (ind >= _size || ind < 0)
		throw 2;
	else
		return arr[ind];
}

template<class T, class Comp>
size_t Heap<T, Comp>::size()
{
	return _size;
}

template<class T, class Comp>
void Heap<T, Comp>::heapify_down(size_t i)
{
	size_t n = _size,j;
	size_t left, right;
	if (2 * i > n)
		return;
	else if (2 * i < n)
	{
		left = 2 * i;
		right = 2 * i + 1;
		j = comp(arr[right],arr[left]) ? left : right;
	}	
	else if (2 * i == n)
		j = 2 * i - 1;
	if (comp(arr[i],arr[j]))
	{
		std::swap(arr[i], arr[j]);
		heapify_down(j);
	}
}

template<class T, class Comp>
T Heap<T, Comp>::pop()
{
	T result = arr[0];
	arr[0] = arr[_size - 1];
	_size--;
	heapify_down(0);
	return result;
}

template<class T, class Comp>
T Heap<T,Comp>::head()
{
	return arr[0];
}

template<class T, class Comp>
void Heap<T, Comp>::remove(size_t ind)
{
	if (ind < 0 || ind > _size)
		throw 2;
	arr[ind] = arr[_size - 1];
	_size--;
	heapify_down(ind);
}

#endif // !HEAP

