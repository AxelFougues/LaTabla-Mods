#include "../LorenzWorld.h"

#ifdef isUsingOrientation
void LorenzWorld::setOrientationVec(string name, vec2 value){
    if ( name=="Up" ){
        mUpVec = value;
    }
    setAreUserSettingsDirty();
}
map<string,vec2> LorenzWorld::getOrientationVecs() const{
    map<string,vec2> m;
    m["Up"] = mUpVec;
    return m;
}
void LorenzWorld::initSettings(){
    mUpVec = mDefaultUpVec;
}

XmlTree LorenzWorld::getUserSettings() const{
    XmlTree xml("settings","");
    xml.push_back( XmlTree("UpVec", vecToString(mUpVec)) );
    return xml;
}

void LorenzWorld::setUserSettings( XmlTree settingsXml ){
    if ( settingsXml.hasChild("settings") ){
        XmlTree xml = settingsXml.getChild("settings");
        getXml(xml, "UpVec", mUpVec );
    }
}
#endif
