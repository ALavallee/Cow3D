#ifndef EVOCLIENT_TRACK_H
#define EVOCLIENT_TRACK_H

#include <vector>
#include <iostream>
#include "Frame.h"

enum class Interpolation {
    Constant = 0,
    Linear = 1,
    Cubic = 2,
};

template<class T>
struct Track {

    static constexpr float LoopReplayFrameTime = 0.15f;

    Interpolation interpolation;
    std::vector<Frame<T>> frames;

    float adjustTimeForLoop(float time, bool looping) {
        if (looping && frames.size() > 1) {
            Frame<T> *last_frame = &frames[frames.size() - 1];
            if (time > last_frame->time) {
                time = fmodf(time, last_frame->time + LoopReplayFrameTime);
            }
        }
        return time;
    }

    int getFrame(float time) {
        if (frames.size() > 1) {
            float last_time = frames[frames.size() - 1].time;
            if (time > last_time) {
                return (int) frames.size() - 1;
            }

            for (int i = 0; i < frames.size() - 1; ++i) {
                float begin = frames[i].time;
                float end = frames[i + 1].time;
                if (time >= begin && time < end) {
                    return i;
                }
            }
        } else if (frames.size() == 1) {
            return 0;
        }

        return -1;
    }

    T sample(float time, bool loop, T defaultValue) {
        time = adjustTimeForLoop(time, loop);
        int frameIndex = getFrame(time);
        if (frameIndex >= 0) {
            Frame<T> *frame = &frames[frameIndex];
            Frame<T> *nextFrame;
            float frameDelta;
            if (frameIndex + 1 < frames.size() || !loop) {
                nextFrame = &frames[frameIndex + 1];
                frameDelta = nextFrame->time - frame->time;
            } else {
                nextFrame = &frames[0];
                frameDelta = (frame->time + LoopReplayFrameTime) - frame->time;
            }
            
            if (frameDelta > 0.f) { // avoid division by zero
                switch (interpolation) {

                    case Interpolation::Cubic:
                    case Interpolation::Linear: {
                        float t = (time - frame->time) / frameDelta;
                        return frame->v.lerp(nextFrame->v, t);
                    }

                    case Interpolation::Constant:
                        return frame->v;
                }
            }
        }

        return defaultValue;
    }
};

#endif //EVOCLIENT_TRACK_H
