// -----------------------------------------------------------------------------
//  Filename:    HOO_definitions.h
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

#ifndef HOO_DEFINITIONS_H
#define HOO_DEFINITIONS_H

// we are in debug mode, this is set specifically
#define _DEBUG


// include some stl useful utilities
#include <map>
#include <vector>
#include <iostream>

// base includes for the whole application
#include "Ogre.h"
#include "OIS.h"
#include "CEGUI/CEGUI.h"

// Camera Control System
#include "CCSCameraControlSystem.h"
#include "CCSBasicCameraModes.h"
#include "CCSFreeCameraMode.h"
#include "CCSOrbitalCameraMode.h"

// Debug drawing functions
#include "DebugDrawer.h"

// Debug 3D text
#include "MovableText.h"


namespace HOO{
// TYPE DEFINITIONS
typedef std::vector<Ogre::Entity*> entityVector;

// integer type definitions. For the moment we use it as a wrapper to
// Ogre types, which are already platform-specific. It is useful to use our
// custom defined types, so if in the future we need to implement our own ones,
// we do not need to change the whole source code, only here.
typedef Ogre::int64 int64;
typedef Ogre::int32 int32;
typedef Ogre::int16 int16;
typedef Ogre::int8 int8;

typedef Ogre::uint64 uint64;
typedef Ogre::uint32 uint32;
typedef Ogre::uint16 uint16;
typedef Ogre::uint8 uint8;

typedef Ogre::String String;

typedef Ogre::Vector2 Vector2;
typedef Ogre::Vector3 Vector3;
typedef Ogre::Vector4 Vector4;

}

#endif
