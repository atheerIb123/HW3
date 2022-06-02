#ifndef EX3_Queue_H
#define EX3_Queue_H

#include<iostream>

template<class T>
class Queue
{
public:
	Queue();
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
	T* m_data;
	int m_size;
	void expand();
	void scaleDown();
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

#endif //EX3_Queue_H

template<class T>
Queue<T>::Queue()
{
	m_size = 0;
	m_data = nullptr;
}

template<class T>
Queue<T>::~Queue()
{
	if (m_data != nullptr)
	{
		delete[] m_data;
	}
}

template<class T>
Queue<T>::Queue(const Queue& queue)
{
	m_size = queue.m_size;

	if (m_size == 0)
	{
		m_data = nullptr;
	}
	else
	{
		m_data = new T[m_size];

		for (int i = 0; i < m_size; i++)
		{
			m_data[i] = queue.m_data[i];
		}
	}
}

template<class T>
void Queue<T>::expand()
{
	T* newArray = new T[m_size + 1];

	for (int i = 0; i < m_size; i++)
	{
		newArray[i] = m_data[i];
	}

	m_size++;

	delete[] m_data;
	m_data = newArray;
}

template<class T>
void Queue<T>::pushBack(const T& object)
{
	T assign = object;

	if (m_data != nullptr)
	{
		expand();
		m_data[m_size - 1] = assign;
	}
	else
	{
		m_size++;
		m_data = new T[m_size];
		m_data[m_size - 1] = assign;
	}
}


template<class T>
T& Queue<T>::front()
{
	if (m_size == 0)
	{
		throw EmptyQueue();
	}

	return m_data[0];
}

template<class T>
const T& Queue<T>::front() const
{
	if (m_size == 0)
	{
		throw EmptyQueue();
	}

	return m_data[0];
}

template<class T>
void Queue<T>::scaleDown()
{
	T* tempData = new T[m_size - 1];

	for (int i = 0; i < m_size - 1; i++)
	{
		tempData[i] = m_data[i + 1];
	}

	delete[] m_data;
	m_data = tempData;
}

template<class T>
void Queue<T>::popFront()
{
	if (m_size == 0 || m_data == nullptr)
	{
		throw EmptyQueue();
	}
	else if (m_size > 1)
	{
		try
		{
			scaleDown();
			m_size--;
		}
		catch (const std::bad_alloc& err)
		{
			delete[] m_data;
			m_data = nullptr;
			m_size = 0;
			throw err;
		}
	}
	else
	{
		delete[] m_data;
		m_data = nullptr;
		m_size = 0;
	}
}

template<class T>
int Queue<T>::size() const
{
	return m_size;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
	if (this == &queue)
	{
		return *this;
	}

	m_size = queue.m_size;

	if (m_size == 0)
	{
		m_data = nullptr;
	}
	else
	{
		delete[] m_data;

		m_data = new T[m_size];

		for (int i = 0; i < m_size; i++)
		{
			m_data[i] = queue.m_data[i];
		}
	}

	return *this;
}


template<class T, class Condition>
Queue<T> filter(const Queue<T>& queue, Condition c)
{
	Queue<T> tempQueue = queue;
	Queue<T> filteredQueue;

	while (tempQueue.size() > 0)
	{
		if (c(tempQueue.front()))
			filteredQueue.pushBack(tempQueue.front());
		tempQueue.popFront();
	}

	return filteredQueue;
}

template<class T, class Alter>
void transform(Queue<T>& queue, Alter operation)
{
	Queue<T> tempQueue;

	while (queue.size() > 0)
	{
		operation(queue.front());
		tempQueue.pushBack(queue.front());
		queue.popFront();
	}

	queue = tempQueue;
}

template<class T>
T& Queue<T>::Iterator::operator*()
{
	return this->queue->m_data[this->index];
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

template<class T>
const T& Queue<T>::ConstIterator::operator*() const
{
	return this->queue->m_data[this->index];
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
