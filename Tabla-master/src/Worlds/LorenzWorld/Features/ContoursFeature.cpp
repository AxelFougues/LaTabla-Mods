#include "../LorenzWorld.h"

#ifdef isUsingContours


PolyLine2 LorenzWorld::getContainerContour(vec2 point){
    const Contour* in = mContours.findLeafContourContainingPoint(point ,mContourFilter) ;
    if (in){
        return in->mPolyLine;
    }
    return getWorldBoundsPoly();
}

void LorenzWorld::drawAllContours(Color color){
    ContourVector& contours = getContours();
    gl::color(color);
    for(Contour c : contours){
        if(c.mPolyLine.size()<CONTOUR_THRESHOLD)
            gl::draw(c.mPolyLine);
    }
}
void LorenzWorld::drawWorldBounds(Color color){
    gl::color(color);
    gl::draw(getWorldBoundsPoly());
}
void LorenzWorld::drawContainerContour(vec2 point, Color color){
    gl::color(color);
    gl::draw(getContainerContour(point));
}

void LorenzWorld::reconCubeInputs(){
    cubeInputs.clear();
    for(Contour c : mContours){
        if(c.mIsLeaf && c.mPolyLine.getPoints().size()==4 && c.mArea < MAX_AREA_THRESHOLD){
            cubeInputs.push_back(c);
        }
    }
}

void LorenzWorld::drawCubeInputs(Color color){
    gl::color(color);
    for(Contour c : cubeInputs){
        if(c.mPolyLine.size()<CONTOUR_THRESHOLD)
            gl::draw(c.mPolyLine);
            //gl::drawSolidRect(Rectf(c.mPolyLine.getPoints()));
    }
}
#endif
