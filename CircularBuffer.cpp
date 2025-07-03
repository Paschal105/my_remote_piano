// Copyright 2022 Paschal Ojatabu
#include <vector>
#include <memory>
#include <ostream>
#include "CircularBuffer.h"  // NOLINT
#include <deque>  // NOLINT

CircularBuffer::CircularBuffer() {}

CircularBuffer::CircularBuffer(size_t capacity) {
    if (capacity < 1) {
        throw std::invalid_argument(
            "CircularBuffer constructor: capacity must be greater than zero.");
    }
    storage = capacity;
}  // create an empty ring buffer, with given max capacity
size_t CircularBuffer::capacity() {
    return storage;
}
size_t CircularBuffer::size() {
    size_t length = buffers.size();
    return length;
}  // return number of items currently in the buffer
bool CircularBuffer::isEmpty() {
    bool truth;
    if (buffers.empty()) {
        truth = true;
    } else {
        truth = false;
    }
    return truth;
}  // is the buffer empty (size equals zero)?
bool CircularBuffer::isFull() {
    bool truth = false;
    if (buffers.size() == storage) {
        truth = true;
    }
    return truth;
}  // is the buffer full (size equals capacity)?
void CircularBuffer::enqueue(int16_t x) {
    if (buffers.size() == storage) {
        throw std::runtime_error(
            "enqueue: can't enqueue to a full ring.");
    }
    buffers.push_back(x);
}  // add item x to the end
int16_t CircularBuffer::dequeue() {
    if (buffers.size() == 0) {
        throw std::runtime_error(
            "error: buffers is empty, when you try to dequeue");
    }
    int16_t items;
    items = buffers.front();
    buffers.pop_front();
    return items;
}   // delete and return item from the front
int16_t CircularBuffer::peek() {
    if (buffers.size() == 0) {
        throw std::runtime_error(
            "error: buffers is empty, when you try to peek");
    }
    return buffers.at(0);
}
void CircularBuffer::pop() {
    buffers.pop_front();
}

void CircularBuffer::clearBuffer() {
    if (!buffers.empty()) {
         buffers.clear();
        std::deque<int16_t>b;
        buffers = b;
    }
}
void CircularBuffer::deleteParticular(int num) {
    buffers.erase(buffers.begin()+num);
}
