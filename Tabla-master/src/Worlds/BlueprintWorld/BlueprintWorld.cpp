//
//  BlueprintWorld.cpp
//  Tabla
//
//  Created by Axel Fougues on 09/04/2018.
//
//
#include "BlueprintWorld.h"

#ifdef isVisible
static GameCartridgeSimple sCartridge(nameOfWorld, [](){
    return std::make_shared<BlueprintWorld>();
});
#endif




void BlueprintWorld::initialize(){ //Called at world creation
	
}

void BlueprintWorld::update(){ //Called each frame
    reconCubeInputs();
}

void BlueprintWorld::prepareToDraw(){ //Called before each draw call
    
}

void BlueprintWorld::draw( DrawType drawType ){//Called many times per frame
    for(Contour c : cubeInputs){
        drawWorldBounds(getMeanContourColor(c));
    }
}



#ifdef isUsingXml

    void BlueprintWorld::setParams( XmlTree xml ){
        //Get needed variables from xml file (assets/config/NameOfWorld.xml) Example:
        //getXml(xml,"ParentNode/ChildNode", variable);
        cout << "Blueprint Xml loading works." << endl;
    }
#endif

//INPUT

#ifdef isUsingKeyboard

    void BlueprintWorld::keyDown( KeyEvent event){
        cout << "Blueprint keyboard key down used." << endl;
        switch ( event.getCode() ){
            case KeyEvent::KEY_s:
                break ;
                
            case KeyEvent::KEY_b:
                break ;
        }
    }

    void BlueprintWorld::keyUp( KeyEvent event){
        cout << "Blueprint keyboard key up used." << endl;
        switch ( event.getCode() ){
            case KeyEvent::KEY_a:
                break ;
                
            case KeyEvent::KEY_b:
                break ;
        }
    }
#endif

#ifdef isUsingGamepad

    void BlueprintWorld::gamepadEvent( const GamepadManager::Event& ) {
        cout << "Blueprint gamepad used." << endl;
    }
#endif


#ifdef isUsingMouse
    /*Inherited:
     vec2 getMousePosInWorld();
        */


    void BlueprintWorld::mouseClick( vec2 event ){
        cout << "Blueprint mouse clicked." << endl;
    }


    void BlueprintWorld::drawMouseDebugInfo( vec2 position){
        
    }

	void BlueprintWorld::drawPointer(Color color, int size){
		gl::drawSolidCircle( getMousePosInWorld(), size);
	}
#endif










