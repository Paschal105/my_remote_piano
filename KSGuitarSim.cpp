// Copyright 2022 paschal ojatabu
#include <math.h>
#include <limits.h>
#include <map>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "CircularBuffer.h"
#include "StringSound.h"

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100
#define MAX_K  37


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

int main() {
    std::map<std::string, int> keys;
    keys.insert(std::make_pair("q", 0));
    keys.insert(std::make_pair("2", 1));
    keys.insert(std::make_pair("w", 2));
    keys.insert(std::make_pair("e", 3));
    keys.insert(std::make_pair("4", 4));
    keys.insert(std::make_pair("r", 5));
    keys.insert(std::make_pair("5", 6));
    keys.insert(std::make_pair("t", 7));
    keys.insert(std::make_pair("y", 8));
    keys.insert(std::make_pair("7", 9));
    keys.insert(std::make_pair("u", 10));
    keys.insert(std::make_pair("8", 11));
    keys.insert(std::make_pair("i", 12));
    keys.insert(std::make_pair("9", 13));
    keys.insert(std::make_pair("0", 14));
    keys.insert(std::make_pair("p", 15));
    keys.insert(std::make_pair("-", 16));
    keys.insert(std::make_pair("[", 17));
    keys.insert(std::make_pair("=", 18));
    keys.insert(std::make_pair("z", 19));
    keys.insert(std::make_pair("x", 20));
    keys.insert(std::make_pair("d", 21));
    keys.insert(std::make_pair("c", 22));
    keys.insert(std::make_pair("f", 23));
    keys.insert(std::make_pair("v", 24));
    keys.insert(std::make_pair("g", 25));
    keys.insert(std::make_pair("b", 26));
    keys.insert(std::make_pair("n", 27));
    keys.insert(std::make_pair("j", 28));
    keys.insert(std::make_pair("m", 29));
    keys.insert(std::make_pair("k", 30));
    keys.insert(std::make_pair(",", 31));
    keys.insert(std::make_pair(".", 32));
    keys.insert(std::make_pair(";", 33));
    keys.insert(std::make_pair("/", 34));
    keys.insert(std::make_pair("'", 35));
    keys.insert(std::make_pair(" ", 36));

    sf::RenderWindow window(sf::VideoMode(300, 200),
    "SFML Plucked String Sound Lite");
    sf::Event event;
    double freq;
    std::vector<sf::Int16> samp;
    // lambda
    auto calFreq = [](int num) { return 440 * pow(2, ((num - 24.0) / 12.0)); };
    std::vector<std::vector<int16_t >> samples;
    std::vector<sf::Sound> sounds;
    std::vector<sf::SoundBuffer> sBuffer;
    for (int i = 0; i < MAX_K; i++) {
        freq = calFreq(i);
        StringSound gs(freq);
        samp = makeSamples(gs);
        samples.push_back(samp);
    }
    for (int i = 0; i < MAX_K; i++) {
        sf::SoundBuffer buf;
        if (!buf.loadFromSamples(&samples.at(i).front(),
        samples.at(i).size(), 2, SAMPLES_PER_SEC))
        throw std::runtime_error(
            "sf::SoundBuffer: failed to load from samples.");
        sBuffer.push_back(buf);
    }
    for (int i = 0; i < MAX_K; i++) {
        sf::Sound s;
        s.setBuffer(sBuffer[i]);
        sounds.push_back(s);
    }
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                std::string nameKey;
                int keyNum;
                nameKey = event.text.unicode;
                keyNum = keys[nameKey];
               // std::cout<<keyNum<< std::endl;
                sounds[keyNum].play();
            } else {
            }
            window.clear();
            window.display();
        }
    }
    return 0;
}
