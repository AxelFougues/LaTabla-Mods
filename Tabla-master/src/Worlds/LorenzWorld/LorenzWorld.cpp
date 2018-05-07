//
//  LorenzWorld.cpp
//  Tabla
//
//  Created by Axel Fougues on 09/04/2018.
//
//
#include "LorenzWorld.h"


#ifdef isVisible
static GameCartridgeSimple sCartridge(nameOfWorld, [](){
    return std::make_shared<LorenzWorld>();
});
#endif




void LorenzWorld::initialize(){ //Called at world creation
}

void LorenzWorld::update(){ //Called each frame
    switch(state){
        case construct:
            oGestures.clear();
            vGestures.clear();
            cubeInputs.clear();
            state = wait;
            break;
            
        case wait:
            computeFieldLayout();
            
            //GESTURE MANAGER
            oGestureRecon();
            wGestureRecon();
            if(wDetected){
                lSystem.restart();
            }
            
            if(oDetected){
                vec2 c = oGestures.front().mCenter;
                int top = c.y - upperRight.y;
                int bottom = lowerLeft.y - c.y;
                int left = c.x - upperLeft.x;
                int right = lowerRight.x - c.x;
                if(top < bottom && top < left && top < right) lSystem.pivotTop();
                else if(bottom < top && bottom < left && bottom < right) lSystem.pivotBottom();
                else if(left < right) lSystem.pivotLeft();
                else lSystem.pivotRight();
                //state = timed;
            }
            
            //TOKEN MANAGER
            reconCubeInputs();
            if(cubeInputs.size() >= 2){
                vec2 tempV = vec2(0,0), tempH = vec2(0,0);
                for(Contour c : cubeInputs){
                    if(c.mCenter.x>tempV.x)
                        tempV = c.mCenter;
                    if(c.mCenter.y>tempH.y)
                        tempH = c.mCenter;
                }
                if(abs((int)tempH.x - (int)horizontalToken.x) >= 2){
                    horizontalToken = tempH;
                    lSystem.updateParameters(horizontalToken.x, verticalToken.y, mCenter);
                }
                    
                if(abs((int)tempV.y - (int)verticalToken.y) >= 2){
                    verticalToken = tempV;
                    lSystem.updateParameters(horizontalToken.x, verticalToken.y, mCenter);
                }
            }
            
            lSystem.getNextValues();
            break;
            
        case timed:
            timer--;
            if(timer<=0){
                timer = 100;
                state = construct;
            }
            
            lSystem.getNextValues();
            break;
    }
}

void LorenzWorld::prepareToDraw(){ //Called before each draw call
    
}

void LorenzWorld::draw( DrawType drawType ){//Called many times per frame
    if(!(lowerRight.x<=0))
        lSystem.drawLorenz(upperLeft, lowerRight, ColorA(0,1,0));
    //lSystem.drawLorenz(centerPoint, 0.8, ColorA(1.0,0,1.0));
    drawOGestures(ColorA(1,1,0), false);
    drawWGestures(ColorA(1,0,0), false);
    drawWorldBounds(ColorA(1,0,0));
    drawCubeInputs(ColorA(1,0,0));
    gl::color(0.6, 0.2, 0.6);
    gl::drawLine(vec2(lowerLeft.x, lowerLeft.y - 2), vec2(lowerRight.x, lowerRight.y - 2));
    gl::drawLine(vec2(lowerRight.x - 2, lowerRight.y), vec2(upperRight.x - 2, upperRight.y));
    //gl::drawStringCentered(to_string((int)horizontalToken.x), horizontalToken, ColorA(0.6, 0.2, 0.6), Font("Arial", 10));
    //gl::drawStringCentered(to_string((int)verticalToken.y), verticalToken, ColorA(0.6, 0.2, 0.6), Font("Arial", 10));
}



#ifdef isUsingXml

    void LorenzWorld::setParams( XmlTree xml ){
        //Get needed variables from xml file (assets/config/NameOfWorld.xml) Example:
        //getXml(xml,"ParentNode/ChildNode", variable);
        cout << "Lorenz Xml loading works." << endl;
    }
#endif

//INPUT

#ifdef isUsingKeyboard

    void LorenzWorld::keyDown( KeyEvent event){
        cout << "Lorenz keyboard key down used." << endl;
        switch ( event.getCode() ){
            case KeyEvent::KEY_s:
                break ;
                
            case KeyEvent::KEY_b:
                break ;
        }
    }

    void LorenzWorld::keyUp( KeyEvent event){
        cout << "Lorenz keyboard key up used." << endl;
        switch ( event.getCode() ){
            case KeyEvent::KEY_a:
                break ;
                
            case KeyEvent::KEY_b:
                break ;
        }
    }
#endif

#ifdef isUsingGamepad

    void LorenzWorld::gamepadEvent( const GamepadManager::Event& ) {
        cout << "Lorenz gamepad used." << endl;
    }
#endif


#ifdef isUsingMouse
    /*Inherited:
     vec2 getMousePosInWorld();
        */


    void LorenzWorld::mouseClick( vec2 event ){
        cout << "Lorenz mouse clicked." << endl;
    }


    void LorenzWorld::drawMouseDebugInfo( vec2 position){
        
    }

	void LorenzWorld::drawPointer(Color color, int size){
		gl::drawSolidCircle( getMousePosInWorld(), size);
	}
#endif










