#include<iostream>
template<class T>
class Queue
{
public:

	Queue(int size = 0);
	~Queue();
	Queue(const Queue&);
	void pushBack(const T&);
	T& front();
	const T& front() const;
	void popFront();
	int size() const;
	Queue& operator=(const Queue&);

	class Iterator;
	class ConstIterator;

	Iterator begin()
	{
		return Iterator(this, 0);
	}

	Iterator end()
	{
		return Iterator(this, size());
	}

	ConstIterator begin() const
	{
		return ConstIterator(this, 0);
	}

	ConstIterator end() const
	{
		return ConstIterator(this, size());
	}

	class EmptyQueue {};

private:
	T* m_arr;
	int m_size;
	int m_maxQueueSize;
};

template<class T>
class Queue<T>::Iterator {
public:
	Iterator(const Iterator&) = default;
	Iterator& operator=(const Iterator&) = default;

	T& operator*();
	Iterator& operator++();
	Iterator operator++(int);
	bool operator==(const Iterator& it) const;
	bool operator!=(const Iterator& it) const;

	class InvalidOperation {};

private:
	Queue<T>* queue;
	int index;
	Iterator(Queue<T>* queue, int index) : queue(queue), index(index)
	{}
	friend class Queue<T>;

};

template<class T>
class Queue<T>::ConstIterator {
public:
	ConstIterator(const ConstIterator&) = default;
	ConstIterator& operator=(const ConstIterator&) = default;

	const T& operator*() const;
	ConstIterator& operator++();
	ConstIterator operator++(int);
	bool operator==(const ConstIterator& it) const;
	bool operator!=(const ConstIterator& it) const;

	class InvalidOperation {};

private:
	const Queue<T>* queue;
	int index;
	ConstIterator(const Queue<T>* queue, int index) : queue(queue), index(index)
	{}
	friend class Queue<T>;

};

template<class T>
Queue<T>::Queue(int size)
{
	m_size = 0;
	m_maxQueueSize = 5;
	m_arr = nullptr;
}

template<class T>
Queue<T>::~Queue()
{
	delete[] m_arr;
}

template<class T>
Queue<T>::Queue(const Queue& q1)
{
	m_size = q1.m_size;
	m_maxQueueSize = q1.m_maxQueueSize;
	if (m_size == 0)
	{
		m_arr = nullptr;
	}
	else
	{
		m_arr = new T[m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_arr[i] = q1.m_arr[i];
		}
	}
}

template<class T>
void Queue<T>::pushBack(const T& object)
{
	/*T add = t;
	if (m_arr != nullptr)
	{
		T* temp = new T[m_size + 1];
		for (int i = 0; i < m_size; i++)
			temp[i] = m_arr[i];
		m_size++;
		delete[] m_arr;
		m_arr = temp;
		m_arr[m_size - 1] = add;
	}
	else
	{
		m_size++;
		m_arr = new T[m_size];
		m_arr[m_size - 1] = t;
	}*/
	if (m_arr != nullptr)
	{
		if (m_size >= m_maxQueueSize)
		{
			m_maxQueueSize += 5;
			T* newArray = new T[m_maxQueueSize];
			for (int i = 0; i < m_size; i++)
			{
				newArray[i] = m_arr[i];
			}
			m_size++;
			delete[] m_arr;
			m_arr = newArray;
			m_arr[m_size - 1] = object;
		}
		else
		{
			m_size++;
			m_arr[m_size - 1] = object;
		}
	}
	else
	{
		m_arr = new T[m_maxQueueSize];
		m_arr[m_size] = object;
		m_size++;
	}
}

template<class T>
T& Queue<T>::front()
{
	if (m_size == 0)
		throw EmptyQueue();
	return *m_arr;
}

template<class T>
const T& Queue<T>::front() const
{
	return m_arr[0];
}

template<class T>
void Queue<T>::popFront()
{
	if (m_size > 1)
	{
		/*m_size = m_size - 1;
		T* temp = new T[m_size];
		for (int i = 1; i <= m_size; i++)
		{
			temp[i - 1] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = temp;*/
		for (int i = 0; i < m_size - 1; i++)
		{
			m_arr[i] = m_arr[i + 1];
		}
		m_size--;
	}
	else
	{
		if (m_size == 1)
		{
			delete[] m_arr;
			m_arr = nullptr;
			m_size = 0;
		}
		else
		{
			throw EmptyQueue();
		}
	}
}

template<class T>
int Queue<T>::size()const
{
	return m_size;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& q1)
{
	m_size = q1.m_size;
	if (m_size == 0)
	{
		m_arr = nullptr;
	}
	else
	{
		delete[] m_arr;
		m_arr = new T[m_size];
		for (int i = 0; i < m_size; i++)
		{
			m_arr[i] = q1.m_arr[i];
		}
	}
	return *this;
}

template<class T, class Condition>
Queue<T> filter(const Queue<T>& q1, Condition c)
{
	Queue<T> temp = q1;
	Queue<T> result;
	while (temp.size() > 0)
	{
		if (c(temp.front()))
			result.pushBack(temp.front());
		temp.popFront();
	}
	return result;
}
template<class T, class Operation>
void transform(Queue<T>& queue, Operation op)
{
	Queue<T> temp;
	while (queue.size() > 0)
	{
		op(queue.front());
		temp.pushBack(queue.front());
		queue.popFront();
	}
	queue = temp;
}
// Iterator functions
template<class T>
T& Queue<T>::Iterator::operator*()
{
	return this->queue->m_arr[this->index];
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
	if (this->queue->end() == *this)
	{
		throw InvalidOperation();
	}
	this->index++;
	return *this;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
	Iterator temp = *this;
	++* this;
	return temp;
}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& it) const
{
	if (queue == it.queue)
		return index == it.index;
	return false;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& it) const
{
	return !(*this == it);
}

// ConstIterator functions
template<class T>
const T& Queue<T>::ConstIterator::operator*() const
{
	return this->queue->m_arr[this->index];
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
	if (this->queue->end() == *this)
	{
		throw InvalidOperation();
	}
	this->index++;
	return *this;
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
	ConstIterator temp = *this;
	++* this;
	return temp;
}

template<class T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator& it) const
{
	if (queue == it.queue)
		return index == it.index;
	return false;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& it) const
{
	return !(*this == it);
}
