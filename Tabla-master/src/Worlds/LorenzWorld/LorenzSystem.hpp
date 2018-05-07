//
//  LorenzSystem.hpp
//  Tabla
//
//  Created by afougu01 on 20/04/2018.
//

#ifndef LorenzSystem_hpp
#define LorenzSystem_hpp

#include <stdio.h>

using namespace std;
using namespace cinder;

class LorenzSystem{
    
public:
    
    const float MAX_VALUES = 1000000;
    const float MIN_VALUES = -1000000;
    const float t = 0.01;
    
    float x = 0.1;
    float y = 0.1;
    float z = 0;
    float a = 10.0;
    float b = 28.0;
    float c = 8.0 / 3.0;

    vec3 horizontalCoord = vec3(1,0,0);
    vec3 verticalCoord = vec3(0,-1,0);
    int verticalSign = 0, horizontalSign = 0;
    list<vec3> buffer;
    int bufferSize;
    int iteration;
    vec2 center = vec2(50,30);
    
    LorenzSystem(int bs = 500, int it = 0){
        iteration = it;
        bufferSize = bs;
    };
    void restart();
    vec3 getNextValues();
    
    void setX(float d){x = d;}
    void setY(float d){y = d;}
    void setZ(float d){z = d;}
    void setA(float d){a = d;}
    void setB(float d){b = d;}
    void setC(float d){c = d;}
    
    void updateParameters(float h, float v, vec2 center);
    
    void pivotTop();
    void pivotBottom();
    void pivotLeft();
    void pivotRight();
    
    
    list<vec3> getBuffer(){return buffer;}
    void drawLorenz(vec2 center, float scale, ColorA color);
    void drawLorenz(vec2 ul, vec2 lr, ColorA color);
    
private:
    vec3 system();
    void pivotVertical();
    void pivotHorizontal();
    void checkVerticalSign();
    void checkHorizontalSign();
    float clamp(float x);
    void drawLines(vec3 old, vec3 pos);
    void drawDots(vec3 pos);
    float strechTo(vec2 in, vec2 out, float value);
};




#endif /* LorenzSystem_hpp */
