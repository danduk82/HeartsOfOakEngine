#include "HOO_app.h"

HOO::ResourceListener::ResourceListener(){
	num = 0;
	endnum = 0;
}

HOO::ResourceListener::~ResourceListener(){
}

void HOO::ResourceListener::resourceGroupScriptingStarted (const Ogre::String &groupName, size_t scriptCount){
	endnum += scriptCount;
}

void HOO::ResourceListener::scriptParseStarted (const Ogre::String &scriptName, bool &skiphisScript){

}


void HOO::ResourceListener::scriptParseEnded (const Ogre::String &scriptName, bool skipped){
	num++;
	std::cout << num <<"/" << endnum << std::endl;
}

void HOO::ResourceListener::resourceGroupScriptingEnded (const Ogre::String &groupName){
}

void HOO::ResourceListener::resourceGroupLoadStarted (const Ogre::String &groupName, size_t resourceCount){
	std::cout << "!!!!" << resourceCount << std::endl;
}

void HOO::ResourceListener::resourceLoadStarted (const Ogre::ResourcePtr &resource){
}

void HOO::ResourceListener::resourceLoadEnded (void){
}

void HOO::ResourceListener::worldGeometryStageStarted (const Ogre::String &description){
}

void HOO::ResourceListener::worldGeometryStageEnded (void){
}

void HOO::ResourceListener::resourceGroupLoadEnded (const Ogre::String &groupName){
}
