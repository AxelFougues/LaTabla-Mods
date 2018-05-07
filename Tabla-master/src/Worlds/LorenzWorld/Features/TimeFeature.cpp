#include "../LorenzWorld.h"

#ifdef isUsingTime
float LorenzWorld::getTimeSinceStart(){
    return ci::app::getElapsedSeconds() - worldEnterTime;
}
#endif
