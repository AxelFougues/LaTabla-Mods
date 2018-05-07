#include "../LorenzWorld.h"

#ifdef isUsingShapes

Shape* LorenzWorld::newDefaultShape(vec2 loc){
    Square *shape = new Square(loc);
    shape->mAccel = Rand::randVec2() * shape->mScale/2.f;
    shape->mHistory.set_capacity(mRibbonMaxLenght);
    shapes.push_back( shape ) ;
    return shapes.back();
}

Shape* LorenzWorld::addShape(Shape* shape){
    shapes.push_back( shape ) ;
    return shapes.back();
};

int LorenzWorld::getShapeIndex( const Shape* s ) const{
    int i = s - shapes[0];
    if (i<0 || i>=shapes.size()) i=-1;
    return i;
}

void LorenzWorld::removeShape(int index){
    shapes.erase( shapes.begin() + index );
}

void LorenzWorld::drawShapes() const{
    for(Shape* s : shapes){
        s->drawShape();
    }
}
void LorenzWorld::drawRibbons( DrawType ) const{
    
}

void LorenzWorld::accumulateShapeHistory(){
    if ( ci::app::getElapsedFrames() % mRibbonSampleRate==0 ){
        for( auto &b : shapes ){
            if ( b->mHistory.max_size() > 0 ){
                if ( b->mHistory.full() && !b->mHistory.empty() ) b->mHistory.pop_front();
                b->mHistory.push_back( b->mLoc );
            }
        }
    }
}
#endif
