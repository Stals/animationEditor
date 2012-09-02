#include "animation.h"

Animation::Animation(){
}

Animation::~Animation(){
}

void Animation::addFrame(Frame frame){
    frames.push_back(frame);
}
