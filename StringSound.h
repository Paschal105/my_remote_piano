// Copyright 2022 Paschal Ojatabu
#ifndef StringSound_h  // NOLINT
#define StringSound_h  // NOLINT
#include <vector>
#include <iostream>
#include <memory>
#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "CircularBuffer.h"

class StringSound {
 public:
  explicit StringSound(double frequency);
  explicit StringSound(std::vector<sf::Int16> init);
  StringSound (const StringSound &obj) = delete;  // no copy const
  ~StringSound();
  void pluck();
  void tic();
  size_t sizes() {
     return _cb->size();
     }
  size_t capacitys() {
     return _cb->capacity();
  }
  sf::Int16 sample();
  int time();

 private:
  std::unique_ptr<CircularBuffer> _cb;
  int _time;
};

#endif   // NOLINT
