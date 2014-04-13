#include "HOO_app.h"

HOO::FrameListener::FrameListener(){
	_debugEntitiesVector=NULL;
	_node=NULL;
	_Cam=NULL;
	_viewport=NULL;
}

HOO::FrameListener::~FrameListener(){}
void HOO::FrameListener::StartFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::Viewport* viewport, Ogre::SceneNode* node,Ogre::Entity* ent, entityVector * entityDebugVector){
	_Cam = cam;
	_movementspeed = 50.0f;
	_viewport = viewport;
	_debugEntitiesVector=entityDebugVector;

	comp1 = false;
	comp2 = false;
	comp3 = false;

	down1 = false;
	down2 = false;
	down3 = false;

	downT=false;

	_polyMode=Ogre::PM_SOLID;

	_WalkingSpeed = 50.0f;
	_node = node;

	OIS::ParamList parameters;
	unsigned int windowHandle = 0;
	std::ostringstream windowHandleString;

	win->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleString << windowHandle;
	parameters.insert(std::make_pair("WINDOW", windowHandleString.str()));

	_InputManager = OIS::InputManager::createInputSystem(parameters);
	_Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject( OIS::OISKeyboard, false ));
	_Mouse = static_cast<OIS::Mouse*>(_InputManager->createInputObject( OIS::OISMouse, false ));

	_aniState = ent->getAnimationState("RunBase");
	_aniState->setLoop(false);

	_aniStateTop = ent->getAnimationState("RunTop");
	_aniStateTop->setLoop(false);

}

void HOO::FrameListener::StopFrameListener(){
	_InputManager->destroyInputObject(_Keyboard);
	std::cout << "shutdown OIS::Keyboard done"<<std::endl;
	_InputManager->destroyInputObject(_Mouse);
	std::cout << "shutdown OIS::Mouse done"<<std::endl;
	OIS::InputManager::destroyInputSystem(_InputManager);
	std::cout << "shutdown OIS successful"<<std::endl;
}

bool HOO::FrameListener::processUnbufferedKeyInput(const Ogre::FrameEvent& evt){return true;}
void HOO::FrameListener::processCamaraKeyInput(void){return;}

// Overriden
bool HOO::FrameListener::processUnbufferedMouseInput(const Ogre::FrameEvent& evt){return true;}
void HOO::FrameListener::moveCamera(){return;}


bool HOO::FrameListener::frameStarted(const Ogre::FrameEvent& evt){

	_Keyboard->capture();
	if(_Keyboard->isKeyDown(OIS::KC_ESCAPE)){
		return false;
	}

	Ogre::Vector3 translate(0,0,0);
	if(_Keyboard->isKeyDown(OIS::KC_W)){
		translate += Ogre::Vector3(0,0,-1);
	}
	if(_Keyboard->isKeyDown(OIS::KC_S)){
		translate += Ogre::Vector3(0,0,1);
	}
	if(_Keyboard->isKeyDown(OIS::KC_A)){
		translate += Ogre::Vector3(-1,0,0);
	}
	if(_Keyboard->isKeyDown(OIS::KC_D)){
		translate += Ogre::Vector3(1,0,0);
	}

	if(_Keyboard->isKeyDown(OIS::KC_1) && !down1){
		down1 = true;
		comp1 = !comp1;
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(_viewport, "Compositor2", comp1);
	}
	if(_Keyboard->isKeyDown(OIS::KC_2) && !down2){
		down2 = true;
		comp2 = !comp2;
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(_viewport, "Compositor3", comp2);
	}
	if(_Keyboard->isKeyDown(OIS::KC_3) && !down3){
		down3 = true;
		comp3 = !comp3;
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(_viewport, "Compositor7", comp3);
	}


	if(_Keyboard->isKeyDown(OIS::KC_T) && !downT){
		downT = true;
		if(_polyMode == Ogre::PM_SOLID){_polyMode=Ogre::PM_WIREFRAME;}
		else if (_polyMode == Ogre::PM_WIREFRAME){_polyMode=Ogre::PM_POINTS;}
		else if (_polyMode == Ogre::PM_POINTS){_polyMode=Ogre::PM_SOLID;}
		_Cam->setPolygonMode(_polyMode);
	}

	if(!_Keyboard->isKeyDown(OIS::KC_1)){down1 = false;	}
	if(!_Keyboard->isKeyDown(OIS::KC_2)){down2 = false;	}
	if(!_Keyboard->isKeyDown(OIS::KC_3)){down3 = false; }
	if(!_Keyboard->isKeyDown(OIS::KC_T)){downT = false;	}

	_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);

	_Mouse->capture();
	float rotX = _Mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
	float rotY = _Mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;


	_Cam->yaw(Ogre::Radian(rotX));
	_Cam->pitch(Ogre::Radian(rotY));

	Ogre::Vector3 SinbadTranslate(0,0,0);
	float _rotation = 0.0f;
	bool walked = false;

	if(_Keyboard->isKeyDown(OIS::KC_UP)){
		SinbadTranslate += Ogre::Vector3(0,0,-1);
		_rotation = 3.14f;
		walked = true;
	}
	if(_Keyboard->isKeyDown(OIS::KC_DOWN)){
		SinbadTranslate += Ogre::Vector3(0,0,1);
		_rotation = 0.0f;
		walked = true;
	}
	if(_Keyboard->isKeyDown(OIS::KC_LEFT)){
		SinbadTranslate += Ogre::Vector3(-1,0,0);
		_rotation = -1.57f;
		walked = true;
	}
	if(_Keyboard->isKeyDown(OIS::KC_RIGHT)){
		SinbadTranslate += Ogre::Vector3(1,0,0);
		_rotation = 1.57f;
		walked = true;
	}

	_node->translate(SinbadTranslate * evt.timeSinceLastFrame * _WalkingSpeed);
	_node->resetOrientation();
	_node->yaw(Ogre::Radian(_rotation));

	if(walked){
		_aniState->setEnabled(true);
		_aniStateTop->setEnabled(true);
		if(_aniState->hasEnded())
		{
			_aniState->setTimePosition(0.0f);
		}
		if(_aniStateTop->hasEnded())
		{
			_aniStateTop->setTimePosition(0.0f);
		}
	}
	else{
		_aniState->setTimePosition(0.0f);
		_aniState->setEnabled(false);
		_aniStateTop->setTimePosition(0.0f);
		_aniStateTop->setEnabled(false);
	}

	_aniState->addTime(evt.timeSinceLastFrame);
	_aniStateTop->addTime(evt.timeSinceLastFrame);


	// Right before the frame is rendered, call DebugDrawer to display all the entities
	// that are in debug mode
	for(int i_ent =0; i_ent!=_debugEntitiesVector->size(); ++i_ent){
		DebugDrawer::getSingleton().drawCuboid(_debugEntitiesVector->at(i_ent)->getWorldBoundingBox(true).getAllCorners(), Ogre::ColourValue::Red, true);
	}
	DebugDrawer::getSingleton().build();

	return true;
}

bool HOO::FrameListener::frameEnded(const Ogre::FrameEvent& evt){
	// After the frame is rendered, call DebugDrawer::clear()
	DebugDrawer::getSingleton().clear();

//	(void)evt;
	return true;
}
