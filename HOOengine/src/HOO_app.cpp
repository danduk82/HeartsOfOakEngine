#include "HOO_app.h"


HOO::FrameListener::FrameListener(){}
HOO::FrameListener::~FrameListener(){}

void HOO::FrameListener::StartFrameListener(Ogre::RenderWindow* win,Ogre::Camera* cam,Ogre::Viewport* viewport,Ogre::SceneNode* node,Ogre::Entity* ent){
	_Cam = cam;
	_movementspeed = 50.0f;
	_viewport = viewport;

	comp1 = false;
	comp2 = false;
	comp3 = false;

	down1 = false;
	down2 = false;
	down3 = false;

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

bool HOO::FrameListener::frameStarted(const Ogre::FrameEvent& evt){
	_Keyboard->capture();
	if(_Keyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		return false;
	}

	Ogre::Vector3 translate(0,0,0);
	if(_Keyboard->isKeyDown(OIS::KC_W))
	{
		translate += Ogre::Vector3(0,0,-1);
	}
	if(_Keyboard->isKeyDown(OIS::KC_S))
	{
		translate += Ogre::Vector3(0,0,1);
	}
	if(_Keyboard->isKeyDown(OIS::KC_A))
	{
		translate += Ogre::Vector3(-1,0,0);
	}
	if(_Keyboard->isKeyDown(OIS::KC_D))
	{
		translate += Ogre::Vector3(1,0,0);
	}

	if(_Keyboard->isKeyDown(OIS::KC_1) && !down1)
	{
		down1 = true;
		comp1 = !comp1;
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(_viewport, "Compositor2", comp1);
	}
	if(_Keyboard->isKeyDown(OIS::KC_2) && !down2)
	{
		down2 = true;
		comp2 = !comp2;
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(_viewport, "Compositor3", comp2);
	}
	if(_Keyboard->isKeyDown(OIS::KC_3) && !down3)
	{
		down3 = true;
		comp3 = !comp3;
		Ogre::CompositorManager::getSingleton().setCompositorEnabled(_viewport, "Compositor7", comp3);
	}

	if(!_Keyboard->isKeyDown(OIS::KC_1))
	{
		down1 = false;
	}
	if(!_Keyboard->isKeyDown(OIS::KC_2))
	{
		down2 = false;
	}
	if(!_Keyboard->isKeyDown(OIS::KC_3))
	{
		down3 = false;
	}



	_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);

	_Mouse->capture();
	float rotX = _Mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
	float rotY = _Mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;


	_Cam->yaw(Ogre::Radian(rotX));
	_Cam->pitch(Ogre::Radian(rotY));


	Ogre::Vector3 SinbadTranslate(0,0,0);
	float _rotation = 0.0f;
	bool walked = false;

	if(_Keyboard->isKeyDown(OIS::KC_UP))
	{
		SinbadTranslate += Ogre::Vector3(0,0,-1);
		_rotation = 3.14f;
		walked = true;
	}
	if(_Keyboard->isKeyDown(OIS::KC_DOWN))
	{
		SinbadTranslate += Ogre::Vector3(0,0,1);
		_rotation = 0.0f;
		walked = true;
	}
	if(_Keyboard->isKeyDown(OIS::KC_LEFT))
	{
		SinbadTranslate += Ogre::Vector3(-1,0,0);
		_rotation = -1.57f;
		walked = true;
	}
	if(_Keyboard->isKeyDown(OIS::KC_RIGHT))
	{
		SinbadTranslate += Ogre::Vector3(1,0,0);
		_rotation = 1.57f;
		walked = true;
	}

	_node->translate(SinbadTranslate * evt.timeSinceLastFrame * _WalkingSpeed);
	_node->resetOrientation();
	_node->yaw(Ogre::Radian(_rotation));

	if(walked)
	{
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
	else
	{
		_aniState->setTimePosition(0.0f);
		_aniState->setEnabled(false);
		_aniStateTop->setTimePosition(0.0f);
		_aniStateTop->setEnabled(false);
	}

	_aniState->addTime(evt.timeSinceLastFrame);
	_aniStateTop->addTime(evt.timeSinceLastFrame);


	return true;
}

HOO::ResourceListener::ResourceListener(){
	num = 0;
	endnum = 0;

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

HOO::Application::Application(){
	_sceneManager = NULL;
	_listener = NULL;
	_keepRunning = true;
	mResourcesCfg = Ogre::StringUtil::BLANK;
	mPluginsCfg = Ogre::StringUtil::BLANK;
}

HOO::Application::~Application(){}

int HOO::Application::shutDown(){
	/*
	 * Shutdown the application, first destroy the frame listener and OIS and then destroy the Ogre::root object.
	 */
	if(_listener)
	{
		_listener->StopFrameListener();
		delete _listener;
	}
	if(_root)
	{
		_root->removeFrameListener(_listener);
		_root->destroyAllRenderQueueInvocationSequences();
		_root->destroySceneManager(_sceneManager);
		delete _root;
	}
	return 0;
}

void HOO::Application::loadResources(){
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();
	Ogre::String sectionName, typeName, dataname;
	while (sectionIter.hasMoreElements())
	{
		sectionName = sectionIter.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			dataname = i->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				dataname, typeName, sectionName);

		}
	}

	HOO::ResourceListener* listener = new HOO::ResourceListener();
	Ogre::ResourceGroupManager::getSingleton().addResourceGroupListener(listener);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void HOO::Application::createCamera(void)
    {
        // Create the camera
		_camera = _sceneManager->createCamera("PlayerCam");

        // Position it at 500 in Z direction
        //mCamera->setPosition(Vector3(0,0,500));
        // Look back along -Z
        //mCamera->lookAt(Vector3(0,0,-300));
		_camera->setNearClipDistance(5);
    }

int HOO::Application::startup(){
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif

	_root = new Ogre::Root(mPluginsCfg);

	if(!_root->showConfigDialog())
	{
		return -1;
	}

	Ogre::RenderWindow* window = _root->initialise(true,"PiratesAhoy! Hearts Of Oak, Conquest of the Seas");

	_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);

	Ogre::Camera* camera = _sceneManager->createCamera("Camera");
	camera->setPosition(Ogre::Vector3(0,0,50));
	camera->lookAt(Ogre::Vector3(0,0,0));
	camera->setNearClipDistance(5);


	Ogre::Viewport* viewport = window->addViewport(camera);
	viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
	camera->setAspectRatio(Ogre::Real(viewport->getActualWidth())/ Ogre::Real(viewport->getActualHeight()));


	loadResources();
	createScene();

	_listener = new HOO::FrameListener();
	_listener->StartFrameListener(window,camera,viewport,_SinbadNode,_SinbadEnt);

	_root->addFrameListener(_listener);

	Ogre::CompositorManager::getSingleton().addCompositor(viewport, "Compositor2");
	Ogre::CompositorManager::getSingleton().addCompositor(viewport, "Compositor3");
	Ogre::CompositorManager::getSingleton().addCompositor(viewport, "Compositor7");

	return 0;
}

void HOO::Application::createScene(){
	_SinbadEnt = _sceneManager->createEntity("Sinbad.mesh");
	_SinbadNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	_SinbadNode->attachObject(_SinbadEnt);

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
	Ogre::MeshManager::getSingleton().createPlane("plane",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		1500,1500,200,200,true,1,5,5,Ogre::Vector3::UNIT_Z);

	Ogre::Entity* ground = _sceneManager->createEntity("LightPlaneEntity", "plane");
	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ground);
	ground->setMaterialName("Examples/BeachStones");

	Ogre::Light* light = _sceneManager->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1,-1,0));

	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

}

void HOO::Application::renderOneFrame(){
	Ogre::WindowEventUtilities::messagePump();
	_keepRunning = _root->renderOneFrame();
}

bool HOO::Application::keepRunning(){
	return _keepRunning;
}

bool HOO::Application::go(){
	/*
	 * The main game loop.
	 */
	startup();
	while(keepRunning()){
		renderOneFrame();
	}
	shutDown();
	return 0;
}
