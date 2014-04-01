#include "HOO_app.h"


Ogre::Entity * HOO::allocateEntityToNode(Ogre::SceneManager * SceneManager, const Ogre::String& entityName, const Ogre::String& meshName, entityVector * entityVector ){
	Ogre::Entity * Ent;
	try{
		Ent = SceneManager->createEntity( entityName, meshName );
	} catch( Ogre::Exception & e ){
		Ent = SceneManager->createEntity( entityName, "ogrehead.mesh");
		entityVector->push_back(Ent);
		Ogre::String message = "WARNING ! Failed to load the following mesh : ";
		message += meshName;
		Ogre::LogManager::getSingletonPtr()->logMessage( message);
	}
	return Ent;
}

HOO::Application::Application(){
	_sceneManager = NULL;
	_listener = NULL;
	_keepRunning = true;
	mResourcesCfg = Ogre::StringUtil::BLANK;
	mPluginsCfg = Ogre::StringUtil::BLANK;
	_debugDrawEntitiesVector=NULL;
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
		// destroy debug facilities
		delete DebugDrawer::getSingletonPtr();
		delete _debugDrawEntitiesVector;

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

	// debug drawing facilites
	new DebugDrawer(_sceneManager, 0.5f);

	_debugDrawEntitiesVector=new entityVector;

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
	_listener->StartFrameListener(window,camera,viewport,_PlayerNode,_PlayerEnt, _debugDrawEntitiesVector);

	_root->addFrameListener(_listener);

	Ogre::CompositorManager::getSingleton().addCompositor(viewport, "Compositor2");
	Ogre::CompositorManager::getSingleton().addCompositor(viewport, "Compositor3");
	Ogre::CompositorManager::getSingleton().addCompositor(viewport, "Compositor7");

	return 0;
}

void HOO::Application::createScene(){
	_PlayerEnt = _sceneManager->createEntity("Sinbad.mesh");
	_PlayerNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	_PlayerNode->attachObject(_PlayerEnt);


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

	// Create a skydome
	_sceneManager->setSkyDome(true, "Examples/CloudySky", 30, 5);

	Ogre::SceneNode* barrelNode = _sceneManager->getRootSceneNode()->createChildSceneNode("barrelSceneNode");

	Ogre::Entity *barrel = allocateEntityToNode(_sceneManager, "barrel", "barrel.mesh" ,_debugDrawEntitiesVector);
	barrel->setCastShadows(true);
	barrelNode->attachObject( barrel );
	barrelNode->setPosition(Ogre::Vector3(50,0,50));

	Ogre::SceneNode* barrel2Node = _sceneManager->getRootSceneNode()->createChildSceneNode("barrel2SceneNode");
	Ogre::Entity *barrel2 = allocateEntityToNode(_sceneManager, "barrel2", "barrel.mesh" ,_debugDrawEntitiesVector);
	barrel2->setCastShadows(true);
	barrel2Node->attachObject( barrel2 );
	barrel2Node->setPosition(Ogre::Vector3(-50,0,-50));

#ifdef _DEBUG
	_sceneManager->showBoundingBoxes(true);
#endif
}

void HOO::Application::renderOneFrame(){
	Ogre::WindowEventUtilities::messagePump();
	_keepRunning = _root->renderOneFrame();
}

bool HOO::Application::keepRunning(){
	return _keepRunning;
}

void HOO::Application::computePhysics(){
	return;
}

void HOO::Application::computeIA(){
	return;
}

void HOO::Application::outputSound(){
	return;
}

/**
 * go(): This is in fact the main game loop.
 * For the moment it computes physics and output sounds on each frame
 * but this could be optimized further. It also computes IA on each frame...
 */
bool HOO::Application::go(){
	startup();
	while(keepRunning()){
		renderOneFrame();
		computePhysics();
		computeIA();
		outputSound();
	}
	shutDown();
	return 0;
}

