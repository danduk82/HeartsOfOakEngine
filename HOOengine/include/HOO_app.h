// -----------------------------------------------------------------------------
//  Filename:    HOO_app.h
// -----------------------------------------------------------------------------
//  This source file is part of the
//                         _                __     ___      _    
//    /\  /\___  __ _ _ __| |_ ___    ___  / _|   /___\__ _| | __
//   / /_/ / _ \/ _` | '__| __/ __|  / _ \| |_   //  // _` | |/ /
//  / __  /  __/ (_| | |  | |_\__ \ | (_) |  _| / \_// (_| |   < 
//  \/ /_/ \___|\__,_|_|   \__|___/  \___/|_|   \___/ \__,_|_|\_\
//                                                               
//     __            _                                           
//    /__\ __   __ _(_)_ __   ___                                
//   /_\| '_ \ / _` | | '_ \ / _ \                               
//  //__| | | | (_| | | | | |  __/                               
//  \__/|_| |_|\__, |_|_| |_|\___|                               
//             |___/                                             
//  
// -----------------------------------------------------------------------------
//  
//  License
//  This work is free. You can redistribute it and/or modify it under the
//  terms of the "Do What The Fuck You Want To Public License", Version 2,
//  as published by Sam Hocevar. See the file "LICENSE" in the root folder 
//  of the project or visit http://www.wtfpl.net/about for more details.
// 
//  
//  Author 
//  Danduk82, alias Andrea Borghi
// 
//  Creation date
//  19/01/2014

#ifndef __HOO_APP_h_


#define __HOO_APP_h_


// HOO specific headers
#include "HOO_definitions.h"
#include "HOO_gameObjects.h"

#ifdef _DEBUG
	#include "ExampleApplication.h"
	class samy : public ExampleApplication{
	private:
			Ogre::SceneNode* _PlayerNode;
			Ogre::Entity* _PlayerEnt;
	public:
			void createScene(void);
	};
#endif

namespace HOO{

	/** Create an Entity (instance of a discrete mesh). Usint Ogre::SceneManager::createEntity(const Ogre::String&, const Ogre::String&)
	 * This function allocates the mesh provided in parameters. But if the given mesh should not be found, than it
	 * assign a stupid pink box, and log the inicidend to the Ogre log pipe instead of crashing the engine. Useful for debug reasons.
		@param
			SceneManager A pointer to the scenemanager.
		@param
			entityName the name that the entity (a string)
		@param
			meshName The name of the Mesh it is to be based on (e.g. 'Sinbad.mesh'). The
			mesh will be loaded if it is not already.
	*/
	int allocateEntityToNode(Ogre::SceneManager *& SceneManager,  Ogre::SceneNode *& node, Ogre::Entity*& Ent ,  const Ogre::String& entityName, const Ogre::String& meshName, HOO::entityVector * debugEntityVector);

	class FrameListener : public Ogre::FrameListener
	{
	private:

		OIS::InputManager* _InputManager;
		OIS::Keyboard* _Keyboard;
		OIS::Mouse* _Mouse;
		Ogre::Camera* _Cam;
		Ogre::Viewport* _viewport;
		float _movementspeed;

		entityVector * _debugEntitiesVector;

		bool comp1,comp2,comp3;
		bool down1,down2,down3, downT;
		Ogre::PolygonMode _polyMode;

		float _WalkingSpeed;
		Ogre::SceneNode* _node;

		Ogre::AnimationState* _aniState;
		Ogre::AnimationState* _aniStateTop;
	public:

		FrameListener(void);
		~FrameListener(void);

		/** StartFrameListener is in fact the "real" constructor.
		 *  This is preferable, so we are sure of the order in which constructors
		 *  and destructors are called.
		 */
		void StartFrameListener(Ogre::RenderWindow* win,Ogre::Camera* cam,Ogre::Viewport* viewport,Ogre::SceneNode* node,Ogre::Entity* ent, entityVector * entityDebugVector);

		/** StopFrameListener is in fact the "real" destructor.
		 *  This is preferable, so we are sure of the order in which constructors
		 *  and destructors are called.
		 */
		void StopFrameListener(void);

		bool frameStarted(const Ogre::FrameEvent& evt);
		// Overriden
		bool frameEnded(const Ogre::FrameEvent& evt);
		bool processUnbufferedKeyInput(const Ogre::FrameEvent& evt);
		void processCamaraKeyInput(void);
		// Overriden
		bool processUnbufferedMouseInput(const Ogre::FrameEvent& evt);
		void moveCamera();

	};

	class ResourceListener : public Ogre::ResourceGroupListener
	{
	private:

		int num;
		int endnum;

	public:

		ResourceListener(void);
		~ResourceListener(void);
		void resourceGroupScriptingStarted (const Ogre::String &groupName, size_t scriptCount);
		void scriptParseStarted (const Ogre::String &scriptName, bool &skiphisScript);
		void scriptParseEnded (const Ogre::String &scriptName, bool skipped);
		void resourceGroupScriptingEnded (const Ogre::String &groupName);
		void resourceGroupLoadStarted (const Ogre::String &groupName, size_t resourceCount);
		void resourceLoadStarted (const Ogre::ResourcePtr &resource);
		void resourceLoadEnded (void);
		void worldGeometryStageStarted (const Ogre::String &description);
		void worldGeometryStageEnded (void);
		void resourceGroupLoadEnded (const Ogre::String &groupName);
	};

	class Application
	{
	private:
		Ogre::SceneManager* _sceneManager;
		Ogre::Root* _root;
		Ogre::RenderWindow* _window;

		Ogre::Camera* _camera;
		Ogre::Viewport* _viewport;


		Ogre::SceneNode* _PlayerNode;
		Ogre::Entity* _PlayerEnt;

		FrameListener* _listener;

		entityVector * _debugDrawEntitiesVector;

		bool _keepRunning;

		Ogre::String mResourcesCfg;
		Ogre::String mPluginsCfg;

	public:
		Application(void);
		~Application(void);

		void loadResources(void);
		int startup(void);
		int shutDown(void);
		void createCamera(void);
		void createScene(void);
		void renderOneFrame(void);
		void computePhysics(void);
		void computeIA(void);
		void outputSound(void);
		bool keepRunning(void);

		bool go(void);
	};
}


#endif // #ifndef __HOO_APP_h_
