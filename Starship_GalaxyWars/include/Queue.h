#pragma once

#include <stdint.h>

#define QUEUE_MAX_DATA 32

// Ima leave this here, i think what i'll do for audio
// is just pass a pointer to an array of data
// This makes it so that we can only play one array at a time,
// but thats all i need.
template<typename T>
class Queue
{
public:
	Queue();
	~Queue();
	void Enqueue(const T& newItem);
	T 	 Dequeue();
	void Clear();
	bool Empty();
	bool Full();
private:
	T* 	 	m_data[QUEUE_MAX_DATA];
	uint8_t m_numElements;
};
