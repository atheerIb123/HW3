#pragma once
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
	typedef struct Node
	{
		Node* next;
		T data;
	}Node;
	int m_size;
	Node* m_head;
	Node* m_tail;
	void freeMemory();
	//static const int EXPANTION_SIZE = 10;
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
	Node* current;
	Iterator(Queue<T>* queue, int index) : queue(queue), index(index)
	{
		current = queue->m_head;
	}
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
	Node* current;
	ConstIterator(const Queue<T>* queue, int index) : queue(queue), index(index)
	{
		current = queue->m_head;
	}
	friend class Queue<T>;

};

#endif //EX3_Queue_H

template<class T>
Queue<T>::Queue()
{
	m_tail = nullptr;
	m_head = nullptr;
	m_size = 0;
}
template<class T>
void Queue<T>::pushBack(const T& object)
{
	/*if (m_head == nullptr)
	{
		m_head = new Node();
		m_head->data = object;
		m_head->next = nullptr;
		m_tail = m_head;
	}
	else
	{
		try {
			Node* newNode = new Node();
			newNode->data = object;
			m_tail->next = newNode;
			m_tail->next->next = nullptr;
			m_tail = m_tail->next;
		}
		catch (std::bad_alloc& e)
		{
			throw e;
		}
	}
	m_size++;*/
	Node* temp = new Node;
	temp->data = object;
	temp->next = nullptr;

	if (m_tail == nullptr)
	{
		m_tail = temp;
		m_head = temp;
	}
	else
	{
		m_tail->next = temp;
		m_tail = temp;

	}
	m_size++;
}
template<class T>
void Queue<T>::popFront()
{
	/*if (m_size == 0)
	{
		throw EmptyQueue();
	}
	else if (m_size == 1)
	{
		if (m_head != nullptr)
		{
			delete(m_tail);
		}
		
		m_head = nullptr;
		m_tail = nullptr;
	}
	else
	{
		Node* toDelete = m_head;
		m_head = m_head->next;
		
		if (m_head == nullptr)
		{
			m_tail = nullptr;
		}

		delete(toDelete);
	}
	m_size--;*/
	if (m_head != nullptr)
	{
		Node* toDelete = m_head;
		m_head = m_head->next;
		delete toDelete;
		if (m_head == nullptr)
		{
			m_tail = nullptr;
		}
		m_size--;
	}
	else
	{
		throw EmptyQueue();
	}
}

template<class T>
int Queue<T>::size() const
{
	return m_size;
}

template<class T>
T& Queue<T>::front()
{
	if (m_head == nullptr)
	{
		throw EmptyQueue();
	}

	return m_head->data;
}

template<class T>
const T& Queue<T>::front() const
{
	if (m_head == nullptr)
	{
		throw EmptyQueue();
	}

	return m_head->data;
}

template<class T>
void Queue<T>::freeMemory()
{
	if(m_head != nullptr)
	{ 
		//int qSize = queue.size();
		for (int i = 0; i < m_size; i++)
		{
			popFront();
		}
	}	
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
	if (&queue == this)
	{
		return *this;
	}

	try
	{
		Queue temp(queue);
		freeMemory();
		m_head = temp.m_head;
		m_tail = temp.m_tail;
		temp.m_head = nullptr;
		temp.m_tail = nullptr;
		temp.m_size = 0;
		return *this;
	}
	catch (const std::bad_alloc& err)
	{
		throw err;
	}

	//return *this;
}
template<class T>
Queue<T>::Queue(const Queue& queue)
{
	//if (queue.m_head != nullptr)
	//{
	//	Node* temp = queue.m_head;
	//	int QueueSize = queue.size();

	//	Node* newQueueNode = new Node();
	//	newQueueNode->next = nullptr;
	//	newQueueNode->data = temp->data;

	//	Node* head = newQueueNode;

	//	for (int i = 0; i < QueueSize; i++)
	//	{
	//		try {
	//			//pushBack(temp->data);
	//			temp = temp->next;

	//			Node* newNode = new Node();
	//			newNode->data = temp->data;
	//			newNode->next = nullptr;
	//			newQueueNode->next = newNode;
	//			newQueueNode = newQueueNode->next;
	//		}
	//		catch (std::bad_alloc& e)
	//		{
	//			std::cout << e.what() << std::endl;
	//			throw e;
	//		}

	//	}

	//	m_head = head;
	//}
	//m_size = queue.m_size;

	if (queue.m_head != nullptr)
	{
		for (ConstIterator it = queue.begin(); it != queue.end() ; it++)
		{
			try
			{
				pushBack(*it);
				//current = current->next;
			}
			catch (const std::bad_alloc& err)
			{
				freeMemory();
				throw err;
			}
		}
		m_size = queue.m_size;
	}
}

template<class T>
Queue<T>::~Queue()
{
	freeMemory();
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
	return current->data;
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
	if (this->queue->end() == *this)
	{
		throw InvalidOperation();
	}

	current = current->next;
	index++;
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
	return current->data;
}

template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
	if (this->queue->end() == *this)
	{
		throw InvalidOperation();
	}

	current = current->next;
	index++;

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
