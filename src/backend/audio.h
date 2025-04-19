#ifndef AUDIO_H
#define AUDIO_H

#include <vector>

using namespace std;

class Audio {
public:
    Audio();
    ~Audio();

    bool loadSound(const string& path, int slot);
    void playSound(int slot);

private:
    struct SoundSlot {
        vector<uint8_t> buffer;
        int sampleRate;
        int channels;
    };

    SoundSlot slots[10];
};

#endif
