// -----------------------------------------------------------------------------
//  Filename:    Characters.cpp
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
//  02/04/2014

// HOO specific headers
#include "HOO_definitions.h"
#include "HOO_gameObjects.h"
#include "HOO_Character.h"

HOO::Character::Character(HOO::String name , Ogre::Entity * entity, Ogre::SceneNode * node){
	_name = name;
	_entity = entity;
	_node = node;
//	_mesh = _entity->getMesh();
	defineAnimations();
}

HOO::Character::~Character(){

}

void HOO::Character::defineAnimations(void){
	// if the mesh is define add the existing animations, else set to NULL
	if (_entity){
		Ogre::AnimationStateSet* set = _entity->getAllAnimationStates();
		Ogre::AnimationStateIterator iter = set->getAnimationStateIterator();
		while (iter.hasMoreElements()){
			std::cout<< iter.getNext()->getAnimationName()<<std::endl;
		}

		_idleAniState=NULL;
		_idleAnimation=NULL;
		_bottomAniState=NULL;
		_BottomAnimation=NULL;
		_topAniState=NULL;
		_TopAnimation=NULL;
		_fightAniState=NULL;
		_fightAnimation=NULL;
		_jumpAnimation=NULL;
		_jumpAnimation=NULL;
	}
	else{
		_idleAniState=NULL;
		_idleAnimation=NULL;
		_bottomAniState=NULL;
		_BottomAnimation=NULL;
		_topAniState=NULL;
		_TopAnimation=NULL;
		_fightAniState=NULL;
		_fightAnimation=NULL;
		_jumpAnimation=NULL;
		_jumpAnimation=NULL;
	}
}

void HOO::Character::addCheckPoint(std::vector<HOO::Vector3> checkPtVct){
	_checkpoints.insert(_checkpoints.end(),checkPtVct.begin(),checkPtVct.end());
}

void HOO::Character::addCheckPoint(HOO::Vector3 checkPt){
	_checkpoints.push_back(checkPt);
}

void HOO::Character::deleteCheckpoints(void){
	if (! _checkpoints.empty()){
		_checkpoints=std::vector<HOO::Vector3>();
	}
}

bool HOO::Character::isMoving(void){
	return _isMoving;
}
bool HOO::Character::isRunning(void){
	return _isRunning;
}

HOO::PlayerCharacter::PlayerCharacter(HOO::String name, Ogre::Entity * entity, Ogre::SceneNode * node) : HOO::Character::Character(name, entity, node){
	return;
}
HOO::PlayerCharacter::~PlayerCharacter(){}
