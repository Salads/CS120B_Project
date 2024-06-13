#include "Queue.h"

template<typename T>
Queue<T>::Queue()
{
	m_data = new T[QUEUE_MAX_DATA];
}

template<typename T>
Queue<T>::~Queue()
{
	delete m_data;
}

template<typename T>
void Queue<T>::Enqueue(const T& newItem)
{
	
}

template<typename T>
T Queue<T>::Dequeue()
{

}

template<typename T>
void Queue<T>::Clear()
{

}

template<typename T>
bool Queue<T>::Empty()
{

}

template<typename T>
bool Queue<T>::Full()
{

}