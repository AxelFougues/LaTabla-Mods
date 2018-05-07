//
//  LorenzSystem.cpp
//  Tabla
//
//  Created by afougu01 on 20/04/2018.
//

#include "LorenzSystem.hpp"

vec3 LorenzSystem::getNextValues(){
    return system();
}

void LorenzSystem::restart(){
    buffer.clear();
    horizontalCoord = vec3(1,0,0);
    verticalCoord = vec3(0,-1,0);
    verticalSign = 0;
    horizontalSign = 0;
    iteration = 0;
}

float LorenzSystem::clamp(float x){
    if(x == NAN) return 0;
    if(x>100000) return 1000000;
    if(x<-1000000) return -1000000;
    return x;
}

float LorenzSystem::strechTo(vec2 in, vec2 out, float value){
    float scale = (out.y - out.x) / (in.y - in.x);
    return value * scale;
}

vec3 LorenzSystem::system(){
    float xt = x + t * a * (y - x);
    float yt = y + t * (x * (b - z) - y);
    float zt = z + t * (x * y - c * z);
    x = clamp(xt);
    y = clamp(yt);
    z = clamp(zt);
    buffer.push_back(cinder::vec3(x,y,z));
    if(buffer.size() >= bufferSize)
        buffer.pop_front();
    return buffer.back();
}


void LorenzSystem::updateParameters(float h, float v, vec2 center){
    //restart();
    if(horizontalCoord.x != 0) setA(h);
    if(verticalCoord.x != 0) setA(v);
    if(horizontalCoord.y != 0) setB(h);
    if(verticalCoord.y != 0) setB(v);
    if(horizontalCoord.z != 0) setC(h);
    if(verticalCoord.z != 0) setC(v);
    cout << " A: " << a << " B: "  << b << " C: " << c << endl;
}

void LorenzSystem::drawLorenz(vec2 ul, vec2 lr, ColorA color){
    float u = 0, d = 0, l = 0, r = 0;
    for(vec3 v : buffer){
        vec2 pos = vec2((
                         v.x * horizontalCoord.x +
                         v.y * horizontalCoord.y +
                         v.z * horizontalCoord.z), (
                         v.x * verticalCoord.x +
                         v.y * verticalCoord.y +
                         v.z * verticalCoord.z));
        if(pos.x>r)r = pos.x;
        if(pos.x<l)l = pos.x;
        if(pos.y>d)d = pos.y;
        if(pos.y<u)u = pos.y;
    }
    float scale = 0.8;
    
    if((u < ul.y || d > lr.y || l < ul.x || r > lr.x) && buffer.size() >= 50){
        scale = (lr.y - ul.y) / (d - u) * 0.8;
        vec2 frameCenter = vec2( lr.x -((lr.x - ul.x)/2), lr.y-((lr.y - ul.y)/2));
        vec2 centerOfFigure = vec2(r-((r-l)/2), d-((d-u)/2));
        center = vec2(frameCenter.x - centerOfFigure.x * scale, frameCenter.y - centerOfFigure.y * scale);
        /*gl::color(1, 0, 0);
        gl::drawSolidCircle(frameCenter, 2);
        gl::color(1, 1, 0);
        gl::drawSolidCircle(centerOfFigure, 3);
        gl::color(0.5, 1, 0.5);
        gl::drawSolidCircle(center, 3);*/
    }
    
    gl::color(color);
    vec3 old = vec3(0,0,0);
    for(vec3 v : buffer){
        vec3 pos = vec3(
                        center.x + (
                                    v.x * horizontalCoord.x +
                                    v.y * horizontalCoord.y +
                                    v.z * horizontalCoord.z) * scale,
                        center.y + (
                                    v.x * verticalCoord.x +
                                    v.y * verticalCoord.y +
                                    v.z * verticalCoord.z) * scale, scale
                        /*(
                                    abs(1-abs(v.x)) * verticalCoord.x +
                                    abs(1-abs(v.y)) * verticalCoord.y +
                                    abs(1-abs(v.z)) * verticalCoord.z) * scale*/
                        );
        drawLines(old, pos);
        //drawDots(pos);
        old = pos;
        //gl::drawString(" A: " + to_string((int)a) + " B: " + to_string((int)b) + " C: " + to_string((int)c), vec2(ul.x,ul.y + 10), ColorA(0.6, 0.2, 0.6), Font("Arial", 8));
        //cout << " up " << u << " d " << d << " le " << l << " ri " << r << endl;
    }
}

void LorenzSystem::drawLines(vec3 old, vec3 pos){
    if(old.x == 0 && old.y == 0 && old.z == 0)
        gl::drawSolidCircle(vec2(pos.x, pos.y), 0.3 + pos.z/10);
    else
        gl::drawLine(vec2(pos.x, pos.y), vec2(old.x, old.y));
}

void LorenzSystem::drawDots(vec3 pos){
        gl::drawSolidCircle(vec2(pos.x, pos.y), 0.3 + pos.z/10);
}



//DEPRECATED
void LorenzSystem::drawLorenz(vec2 center, float scale, ColorA color){
    gl::color(color);
    for(vec3 v : buffer){
        vec2 pos = vec2(
                        center.x + (
                         v.x * horizontalCoord.x +
                         v.y * horizontalCoord.y +
                         v.z * horizontalCoord.z) * scale,
                        center.y + (
                         v.x * verticalCoord.x +
                         v.y * verticalCoord.y +
                         v.z * verticalCoord.z) * scale
                        );
        gl::drawSolidCircle(pos, 0.3 + scale/10);
    }
}
//#############





void LorenzSystem::pivotTop(){
    pivotVertical();
    checkVerticalSign();
    verticalSign--;
}

void LorenzSystem::pivotBottom(){
    pivotVertical();
    checkVerticalSign();
    verticalSign++;
}

void LorenzSystem::pivotLeft(){
    pivotHorizontal();
    checkHorizontalSign();
    horizontalSign++;
}

void LorenzSystem::pivotRight(){
    pivotHorizontal();
    checkHorizontalSign();
    horizontalSign--;
}

void LorenzSystem::pivotVertical(){
    if(horizontalCoord.x != 0){
        int t = verticalCoord.z;
        verticalCoord.z = verticalCoord.y;
        verticalCoord.y = t;
    }
    if(horizontalCoord.y != 0){
        int t = verticalCoord.x;
        verticalCoord.z = verticalCoord.x;
        verticalCoord.x = t;
    }
    if(horizontalCoord.z != 0){
        int t = verticalCoord.y;
        verticalCoord.y = verticalCoord.x;
        verticalCoord.x = t;
    }
}

void LorenzSystem::checkVerticalSign(){
    if(verticalSign <=0 ){
        verticalCoord.x = abs(verticalCoord.x)*-1;
        verticalCoord.y = abs(verticalCoord.y)*-1;
        verticalCoord.z = abs(verticalCoord.z)*-1;
    }else{
        verticalCoord.x = abs(verticalCoord.x);
        verticalCoord.y = abs(verticalCoord.y);
        verticalCoord.z = abs(verticalCoord.z);
    }
}

void LorenzSystem::pivotHorizontal(){
    if(verticalCoord.x != 0){
        int t = horizontalCoord.z;
        horizontalCoord.z = horizontalCoord.y;
        horizontalCoord.y = t;
    }
    if(verticalCoord.y != 0){
        int t = horizontalCoord.z;
        horizontalCoord.z = horizontalCoord.x;
        horizontalCoord.x = t;
    }
    if(verticalCoord.z != 0){
        int t = horizontalCoord.y;
        horizontalCoord.y = horizontalCoord.x;
        horizontalCoord.x = t;
    }
}

void LorenzSystem::checkHorizontalSign(){
    if(horizontalSign <=0 ){
        horizontalCoord.x = abs(horizontalCoord.x)*-1;
        horizontalCoord.y = abs(horizontalCoord.y)*-1;
        horizontalCoord.z = abs(horizontalCoord.z)*-1;
    }else{
        horizontalCoord.x = abs(horizontalCoord.x);
        horizontalCoord.y = abs(horizontalCoord.y);
        horizontalCoord.z = abs(horizontalCoord.z);
    }
}

