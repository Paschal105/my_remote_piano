// Copyright 2022 Paschal Ojatabu
/**
 * Name : paschal Ojatabu 
 * subject : Comp iv 
 * hours: 7 hours 
 * intructor: Dr Daly 
 * IDe : vscode 
 * system: windows 
 * 
*/
#include <vector>
#include <memory>
#include <ostream>
#include <iostream>
#include <algorithm>
#include "CircularBuffer.h"
#include "StringSound.h"
#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100

std::vector<sf::Int16> makeSamples(StringSound& gs) {  // NOLINT
    std::vector<sf::Int16> samples;

    gs.pluck();
    int duration = 8;  // seconds
    int i;
    for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs.tic();
        samples.push_back(gs.sample());
    }

    return samples;
}

int main(int argc, char* argv[]) {
    CircularBuffer B(5);
    // CircularBuffer E;
    B.enqueue(1);
    B.enqueue(2);
    B.enqueue(3);
    std::cout << B.size() << " " << B.capacity() << std::endl;
    std::cout << B.dequeue() << " " << B.size()
    << " " << B.capacity() << std::endl;
    B.enqueue(21);
    B.enqueue(13);
    if (B.isFull()) {
        std::cout << B.peek() << std::endl;
        std::cout << "It is full" << std::endl;
    } else {
        std::cout << B.peek() << std::endl;
        std::cout << "Not full" << std::endl;
    }
    double freq;
    freq = CONCERT_A;
    StringSound gs1(freq);
    gs1.pluck();
    gs1.pluck();
    std::vector<sf::Int16> samples;
    samples.push_back(gs1.sample());
    samples.push_back(gs1.sample());
    std::cout << gs1.sizes() << std::endl;
    std::cout << gs1.capacitys() << std::endl;
    std::cout << samples.size() << std::endl;
    return 0;
}
