// -----------------------------------------------------------------------------
//  Filename:    HOO_Character.h
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

#ifndef HOO_CHARACTER_H
#define HOO_CHARACTER_H

// HOO specific headers
#include "HOO_definitions.h"



namespace HOO{
	class Character{
	private:
		// character's unique identifier
		uint64 _uid;

		// status variables
		// if the character can by played by the user
		bool _isPlayable;
		// if it is selected
		bool _isSelected;
		// if it is visible (not the same as active)
		bool _isVisible;
		// if it is active, i.e. if the IA engine is taking care of him or not
		// usually far away characters are unactive, or sailors on boat out of sight
		// are also unactive (to save a lot of CPU)
		bool _isActive;
		// if the character is moving (see animations states)
		bool _isMoving;
		// if the character is running
		bool _isRunning;

		// state of the hands
		// right hand
		bool _asWeaponInRightHand;
		bool _asItemInRightHand;
		// left hand
		bool _asWeaponInLeftHand;
		bool _asItemInLeftHand;

		// direction it is facing
		Vector3 _lookingAt;
		// health: vector2 because of 0=health ; 1=armor
		Vector2 _health;

		// basic characteristics
		float _walkSpeed;
		float _runSpeed;
		float _jumpHeight;

		// character's name
		String _name;

		// the entity it corresponds
		Ogre::Entity * _entity;
		// the node it is associated
		Ogre::SceneNode * _node;
		// the mesh it corresponds
		Ogre::MeshPtr * _mesh;

		// animation states, this is very basic and will need deep improvements,
		// but it's a beggining...
		// animation for top of the body
		Ogre::Animation _TopAnimation;
		Ogre::AnimationState _topAniState;

		// animation for bottom of the body
		Ogre::Animation _BottomAnimation;
		Ogre::AnimationState _bottomAniState;

		// jump animation
		Ogre::Animation _jumpAnimation;
		Ogre::AnimationState _jumpAniState;

		// fight animation
		Ogre::Animation _fightAnimation;
		Ogre::AnimationState _fightAniState;

		// IDLE animation
		Ogre::Animation _idleAnimation;
		Ogre::AnimationState _idleAniState;

		// what the character has in his inventory
		Inventory _inventory;

		// "IA" section (veeeery basic for the moment)
		// list of coordinates where he should go (in order of execution)
		vector<Vector3> _checkpoints;

	public:
		Character();
		~Character();
		/**
		 * add checkpoints to the list of points to reach
		 */
		void addCheckPoint(Vector3);
		/**
		 * remove all checkpoints (clears the list)
		 */
		void deleteCheckpoints(void);
		bool isMoving(void);
		bool isRunning(void);

	};

	class PlayerCharacter : public Character{

	};
}

#endif
