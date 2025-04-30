#include "audio.h"
#include "device.h"
#include <fstream>

using namespace std;

Audio::Audio() {
    initializeAudioOutput();
}

Audio::~Audio() {
    shutdownAudioOutput();
}

bool Audio::loadSound(const string& path, int slot) {
    ifstream file(path, ios::binary);
    if (!file) return false;

    char header[44];
    file.read(header, 44);

    vector<uint8_t> data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    slots[slot].buffer = move(data);
    slots[slot].sampleRate = 44100;
    slots[slot].channels = 2;

    return true;
}

void Audio::playSound(int slot) {
    if (slots[slot].buffer.empty())
        return;

    streamAudioBuffer(slots[slot].buffer.data(), slots[slot].buffer.size(),
                      slots[slot].sampleRate, slots[slot].channels);
}
