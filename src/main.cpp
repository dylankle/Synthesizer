#include "backend/audio.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    Audio engine;

    if (!engine.loadSound("../assets/sounds/sample.wav", 0)) {
        cerr << "Failed to load sound.\n";
        return 1;
    }

    cout << "Playing sound...\n";
    engine.playSound(0);

    this_thread::sleep_for(chrono::seconds(3));
    return 0;
}
