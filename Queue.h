#ifndef EX3_Queue_H
#define EX3_Queue_H

#define DEFAULT_SIZE 5

template<class T>
class Queue
{
public:
	Queue();
	Queue(const Queue&);
	Queue& operator=(const Queue&);
	~Queue();

	void pushBack(T value);
	T& front() const;
	void popFront();
	int size() const;

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
	int m_rearIndex; //also represents the size of the array
	int m_maxQueueSize;
	void expand();
};

template<class T>
class Queue<T>::Iterator {
public:
	T& operator*();
	Iterator& operator++();
	Iterator operator++(int);
	bool operator==(const Iterator& it);
	bool operator!=(const Iterator& it);
	class InvalidOperation {};
	Iterator(const Iterator&) = default;
	Iterator& operator=(const Iterator&) = default;

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
int Queue<T>::size() const
{
	int queueSize = m_rearIndex + 1;
	return queueSize;
}

template<class T>
Queue<T>::Queue()
{
	this->m_arr = new T[DEFAULT_SIZE];
	this->m_rearIndex = -1; //Starting Index of an empty queue --> (this field is sort of a pointer to the last index of the queue)
	this->m_maxQueueSize = DEFAULT_SIZE;
}

template<class T>
Queue<T>::Queue(const Queue<T>& queue) : m_arr(new T[queue.m_maxQueueSize])
{
	this->m_rearIndex = queue.m_rearIndex;
	this->m_maxQueueSize = queue.m_maxQueueSize;

	for (int i = 0; i < (this->m_rearIndex + 1); i++)
	{
		this->m_arr[i] = queue.m_arr[i];
	}
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
	if (this == &queue)
	{
		return *this;
	}

	delete[] this->m_arr;
	this->m_arr = new T[queue.m_maxQueueSize];
	this->m_maxQueueSize = queue.m_maxQueueSize;
	this->m_rearIndex = queue.m_rearIndex;

	for (int i = 0; i <= this->m_rearIndex; i++)
	{
		this->m_arr[i] = queue.m_arr[i];
	}

	return *this;
}

template<class T>
Queue<T>::~Queue()
{
	delete[] this->m_arr;
}

template<class T>
void Queue<T>::expand()
{
	int newSize = (this->m_rearIndex + 1) + DEFAULT_SIZE; //reallocating new memory 
	T* newData = new T[newSize];

	for (int i = 0; i < this->m_rearIndex + 1; ++i) {
		newData[i] = this->m_arr[i];
	}

	delete[] this->m_arr;

	this->m_arr = new T[newSize];

	for (int i = 0; i < newSize; i++)
	{
		this->m_arr[i] = newData[i];
	}
	delete[] newData;
	this->m_maxQueueSize = newSize;
}

template<class T>
void Queue<T>::pushBack(T value)
{
	this->m_rearIndex++;
	if (this->m_rearIndex >= this->m_maxQueueSize)
	{
		expand();
	}
	this->m_arr[this->m_rearIndex] = value;
}

template<class T>
T& Queue<T>::front() const
{
	if (this->m_rearIndex == -1)
	{
		throw EmptyQueue();
	}

	return this->m_arr[0];
}

template<class T>
void Queue<T>::popFront()
{
	int queueSize = this->m_rearIndex + 1;

	if (queueSize <= 0)
	{
		throw EmptyQueue();
	}

	T* newData = new T[queueSize];

	for (int i = 1; i < queueSize; ++i) {
		newData[i - 1] = this->m_arr[i];
	}

	this->m_rearIndex--;
	this->m_arr = newData;
	delete[] newData;
}

template<class T, class Condition>
Queue<T> filter(const Queue<T>& queueToFilter, Condition c)
{
	Queue<T> tempQueue = queueToFilter;
	Queue<T> filteredQueue;

	for (int i = 0; i < queueToFilter.size(); i++)
	{
		if (c(tempQueue.front()))
		{
			filteredQueue.pushBack(tempQueue.front());
		}
		tempQueue.popFront();
	}

	return filteredQueue;
}

template<class T, class Alter>
void transform(Queue<T>& queueToTransform, Alter a)
{
	Queue<T> transformedQueue;
	for (int i = 0; i < queueToTransform.size(); i++)
	{
		a(queueToTransform.front());
		transformedQueue.pushBack(queueToTransform.front());
		queueToTransform.popFront();
	}
	queueToTransform = transformedQueue;
}

template<class T>
T& Queue<T>::Iterator::operator*()
{
	return this->queue->m_arr[this->index];
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
	if (queue->end() == *this)
	{
		throw InvalidOperation();
	}

	++index;
	return *this;
}

template<class T>
bool Queue<T>::Iterator::operator==(const Iterator& it)
{
	if (this->queue == it.queue)
	{
		return this->index == it.index;
	}

	return false;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
	Iterator result = *this;
	++* this;
	return result;
}


template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& it)
{
	bool ans = !(*this == it);
	return ans;
}



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

	++index;
	return *this;
}

template<class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
	ConstIterator result = *this;
	++* this;
	return result;
}

template<class T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator& it) const
{
	if (queue == it.queue)
	{
		return index == it.index;
	}

	return false;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& it) const
{
	bool ans = !(*this == it);
	return ans;
}
