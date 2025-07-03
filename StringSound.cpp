// Copyright 2022 Paschal Ojatabu

#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "CircularBuffer.h"
#include "StringSound.h"


StringSound::StringSound(double frequency) {
 if (frequency < 1) {
        throw std::invalid_argument(
            "Error: frequency is invalid: less than 1");
    }

    int soundNum = ceil(44100/frequency);
    _cb = std::make_unique<CircularBuffer>(soundNum);

    for (int i = 0; i < soundNum; i++) {
        _cb->enqueue(0);
    }
    _time = 0;
}
StringSound::StringSound(std::vector<sf::Int16> init) {
    if (init.size() == 0) {
        throw std::invalid_argument(
            "Error: there is not items in the list");
    }
    _cb = std::make_unique<CircularBuffer>(init.size());
    for (auto &num : init) {
        _cb->enqueue(num);
    }
}
StringSound::~StringSound() {
    _cb.release();
}
void StringSound::pluck() {
    _cb->clearBuffer();
    for (size_t i = 0; i < _cb->capacity(); i++) {
       // int16_t randomN = rand() % (-32768 + 32767) + 32768;
       int16_t randomN = rand() % (32768 + 32767) - 32768; // NOLINT
        _cb->enqueue(randomN);
    }
    if (!_cb->isFull()) {
        throw std::runtime_error(
            "error: buffers is not full Bro!!");
    }
    _time++;
}
void StringSound::tic() {
    int16_t sample = ceil(0.996  * (_cb->dequeue() + _cb->peek()) * 0.5);
    _cb->enqueue(sample);
    _time++;
}
sf::Int16 StringSound::sample() {
    return _cb->peek();
}
int StringSound::time() {
    return _time;
}
