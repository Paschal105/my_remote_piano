// Copyright 2022 Paschal Ojatabu
#include <ostream>
#include <stdint.h>  // NOLINT
#include <deque>
#ifndef CircularBuffer_h  // NOLINT
#define CircularBuffer_h  // NOLINT


class CircularBuffer{
 public:
CircularBuffer();
CircularBuffer(size_t capacity);  // create an empty ring buffer, with given max
                                  // capacity
size_t capacity();
size_t size();              // return number of items currently in the buffer
bool isEmpty();             // is the buffer empty (size equals zero)?
bool isFull();              // is the buffer full (size equals capacity)?
void enqueue(int16_t x);    // add item x to the end
int16_t dequeue();          // delete and return item from the front
int16_t peek();
void clearBuffer();           // return (but do not delete) item from the front
void deleteParticular(int num);
void pop();
 private:
size_t storage;
std::deque<int16_t>buffers;
};

#endif  // NOLINT
