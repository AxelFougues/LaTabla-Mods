#include "../LorenzWorld.h"

#ifdef isUsingWidgets
class Widget{
public:
    Widget(vec2 ul, vec2 lr){
        upperLeft = ul;
        lowerRight = lr;
        setCenter();
    }
    bool triggered = false;
    vec2 trigger;
    vec2 upperLeft;
    vec2 lowerRight;
    vec2 center;
    
    void setCenter(){center = vec2(lowerRight.x - upperLeft.x / 2, lowerRight.y - upperLeft.y / 2);}
    void drawWidget(ColorA color){gl::color(color);gl::drawSolidRect(Rectf(upperLeft.x, upperLeft.y, lowerRight.x, lowerRight.y));};
    //void drawWidgetContour(ColorA color){gl::color(color);gl::draw(Rectf(upperLeft.x, upperLeft.y, lowerRight.x, lowerRight.y));};
};
#endif
