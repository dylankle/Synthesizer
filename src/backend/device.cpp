#include "device.h"
#include <AudioToolbox/AudioToolbox.h>
#include <cstring>

using namespace std;

static AudioQueueRef audioQueue = nullptr;

void AQCallback(void *customData, AudioQueueRef queue, AudioQueueBufferRef buffer) {
    // required by CoreAudio so it doesnt break
}

bool initializeAudioOutput() {
    return true;
}

void streamAudioBuffer(const void* data, size_t length, int sampleRate, int channels) {
    AudioStreamBasicDescription format = {0};
    format.mSampleRate       = sampleRate;
    format.mFormatID         = kAudioFormatLinearPCM;
    format.mFormatFlags      = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
    format.mBitsPerChannel   = 16;
    format.mChannelsPerFrame = channels;
    format.mFramesPerPacket  = 1;
    format.mBytesPerFrame    = 2 * channels;
    format.mBytesPerPacket   = format.mBytesPerFrame;

    if (!audioQueue) {
        AudioQueueNewOutput(&format, AQCallback, nullptr, nullptr, nullptr, 0, &audioQueue);
    }

    AudioQueueBufferRef bufferRef;
    AudioQueueAllocateBuffer(audioQueue, length, &bufferRef);
    std::memcpy(bufferRef->mAudioData, data, length);
    bufferRef->mAudioDataByteSize = static_cast<UInt32>(length);

    AudioQueueEnqueueBuffer(audioQueue, bufferRef, 0, nullptr);
    AudioQueueStart(audioQueue, nullptr);
}

void shutdownAudioOutput() {
    if (audioQueue) {
        AudioQueueStop(audioQueue, true);
        AudioQueueDispose(audioQueue, true);
        audioQueue = nullptr;
    }
}
