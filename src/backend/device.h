#ifndef DEVICE_H
#define DEVICE_H

#include <cstddef>

bool initializeAudioOutput();
void streamAudioBuffer(const void* data, size_t length, int sampleRate, int channels);
void shutdownAudioOutput();

#endif
