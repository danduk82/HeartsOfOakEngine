// -----------------------------------------------------------------------------
//  Filename:    HOO.h
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

#ifndef __customApplication_h_

#define _DEBUG

#define __customApplication_h_

//#include <OgreCamera.h>
//#include <OgreEntity.h>
//#include <OgreLogManager.h>
//#include <OgreRoot.h>
//#include <OgreViewport.h>
//#include <OgreSceneManager.h>
//#include <OgreRenderWindow.h>
//#include <OgreConfigFile.h>
//
//#include <OISEvents.h>
//#include <OISInputManager.h>
//#include <OISKeyboard.h>
//#include <OISMouse.h>


#include "Ogre.h"
#include "OIS.h"
namespace HOO{
	class FrameListener : public Ogre::FrameListener
	{
	private:

		OIS::InputManager* _InputManager;
		OIS::Keyboard* _Keyboard;
		OIS::Mouse* _Mouse;
		Ogre::Camera* _Cam;
		Ogre::Viewport* _viewport;
		float _movementspeed;

		bool comp1,comp2,comp3;
		bool down1,down2,down3;

		float _WalkingSpeed;
		Ogre::SceneNode* _node;

		Ogre::AnimationState* _aniState;
		Ogre::AnimationState* _aniStateTop;
	public:

		FrameListener(void);
		~FrameListener(void);

		void StartFrameListener(Ogre::RenderWindow* win,Ogre::Camera* cam,Ogre::Viewport* viewport,Ogre::SceneNode* node,Ogre::Entity* ent);
		void StopFrameListener(void);

		bool frameStarted(const Ogre::FrameEvent& evt);

	};

	class ResourceListener : public Ogre::ResourceGroupListener
	{
	private:

		int num;
		int endnum;
	public:

		ResourceListener(void);
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

		Ogre::Camera* _camera

		Ogre::SceneNode* _SinbadNode;
		Ogre::Entity* _SinbadEnt;

		FrameListener* _listener;

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
		bool keepRunning(void);

		bool go(void);
	};
}


#endif // #ifndef __customApplication_h_
