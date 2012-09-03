#include "animation.h"

Animation::Animation(){
}

Animation::~Animation(){
    for(std::vector<Frame*>::iterator frameIt = frames.begin(); frameIt != frames.end();){
        delete *frameIt;
        frameIt = frames.erase(frameIt);
    }
}

void Animation::addFrame(Frame *frame){
    frames.push_back(frame);
}
