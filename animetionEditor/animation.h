#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>

#include "frame.h"

// This class stores frames.
class Animation{
public:
    Animation();
    ~Animation();

    std::vector<Frame> frames;
};

#endif // ANIMATION_H
