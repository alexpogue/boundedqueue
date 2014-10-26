// Copyright [2014] Alex Pogue
#ifndef BOUNDED_QUEUE_H
#define BOUNDED_QUEUE_H

#include <stdexcept>
#include <algorithm>
#include "BoundedQueue.h"

BoundedQueue::BoundedQueue(int size)
    : capacity(size),
      front(0),
      numElements(0) {
    data = new int[capacity];
}

BoundedQueue::~BoundedQueue() {
    delete[] data;
}

BoundedQueue::BoundedQueue(const BoundedQueue& source)
    : capacity(source.capacity),
      front(source.front),
      numElements(source.numElements) {
    data = new int[capacity];
    if (!data) {
        throw new std::exception;
    }
    std::copy(source.data, source.data + source.capacity, data);
}

BoundedQueue& BoundedQueue::operator=(const BoundedQueue& rhs) {
    delete[] data;
    data = new int[rhs.capacity];
    std::copy(rhs.data, rhs.data + rhs.capacity, data);

    return *this;
}

void BoundedQueue::reinit() {
    numElements = 0;
    front = 0;
}

int BoundedQueue::getCapacity() {
    return capacity;
}

int BoundedQueue::getSize() {
    return numElements;
}
void BoundedQueue::enqueue(int element) {
    if (numElements >= capacity) {
        throw std::runtime_error("cannot enqueue a full BoundedQueue");
    }

    int back = front + numElements;
    if (back >= capacity) {
        back -= capacity;
    }

    ++numElements;
    data[back] = element;
}

int BoundedQueue::dequeue() {
    if (numElements == 0) {
        throw std::runtime_error("cannot dequeue an empty BoundedQueue");
    }
    int elem = data[front];
    ++front;
    if (front >= capacity) {
        front -= capacity;
    }
    --numElements;
    return elem;
}

#endif
