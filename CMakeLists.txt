# CMake build project to build the engine for Hearts of Oak, including 
# the necessary external projects (OGRE3d, CEGUI, etc). 
# 
# Prerequisites:
# To build this project, CMAKE v.2.8.12+ is necessary. Moreover, GIT, MERCURIAL
# and SVN must be installed on the computer. See "INSTALL" in the root folder of
# the project.
# 
# License
# This work is free. You can redistribute it and/or modify it under the
# terms of the Do What The Fuck You Want To Public License, Version 2,
# as published by Sam Hocevar. See the file "LICENSE" in the root folder 
# of the project or visit http://www.wtfpl.net/about for more details.
#
# 
# Author 
# Danduk82, alias Andrea Borghi
#
# Creation date
# 19/01/2014



cmake_minimum_required(VERSION 2.8.12)

include(ExternalProject)

project(HOO)



# third party libraries versions needed
set(OGRE_SDK_VERSION v1-8)
set(CEGUI_SDK_VERSION v0-8)
set(OPENAL_VERSION_TAG openal-soft-1.15.1)

set(DEP_DIR dependencies)

if(NOT DEFINED BUILD_TARGET )
    set(BUILD_TARGET Debug)
endif(NOT DEFINED BUILD_TARGET)

if(${BUILD_TARGET} STREQUAL Debug)
    set(SUFF "_d")
    MESSAGE("DEBUG! SUFF = ${SUFF}")
endif(${BUILD_TARGET} STREQUAL Debug)

MESSAGE("BUILD_TARGET is ${BUILD_TARGET}")
MESSAGE(CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX})

SET(OGRE_HOME ${CMAKE_INSTALL_PREFIX})
SET(LIBOISD ${CMAKE_INSTALL_PREFIX}/lib/libOIS_d.so)
SET(LIBOGRED ${CMAKE_INSTALL_PREFIX}/lib/libOgreMain_d.so)
SET(LIBOIS ${CMAKE_INSTALL_PREFIX}/lib/libOIS.so)
SET(LIBOGRE ${CMAKE_INSTALL_PREFIX}/lib/libOgreMain.so)

SET(GML_H_PATH ${CMAKE_INSTALL_PREFIX}/include)

MESSAGE("LIBOIS = ${LIBOIS}")
MESSAGE("LIBOGRE = ${LIBOGRE}")

# External project : OPENAL (audio library)
ExternalProject_Add(openAL
GIT_REPOSITORY git://repo.or.cz/openal-soft.git
GIT_TAG ${OPENAL_VERSION_TAG}
PREFIX ${DEP_DIR}/openAL
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DBUILD_SHARED_LIBS:BOOL=TRUE)

## External project : BULLET PHYSICS (physics engine)
ExternalProject_Add(BULLET
SVN_REPOSITORY http://bullet.googlecode.com/svn/trunk/
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DBUILD_SHARED_LIBS:BOOL=TRUE;
-DINSTALL_EXTRA_LIBS:BOOL=TRUE;
-DUSE_CUSTOM_VECTOR_MATH:BOOL=TRUE
PREFIX ${DEP_DIR}/BULLET)

# External project : OGRE_DEPENDENCIES (needed for OGRE3D)
ExternalProject_Add(ogredeps
HG_REPOSITORY https://bitbucket.org/cabalistic/ogredeps
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DBUILD_SHARED_LIBS:BOOL=TRUE
PREFIX ${DEP_DIR}/ogreDeps)

# External project : OGRE3D (render engine)
ExternalProject_Add(OGRE3D
HG_REPOSITORY http://bitbucket.org/sinbad/ogre/
HG_TAG ${OGRE_SDK_VERSION}
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DBUILD_SHARED_LIBS:BOOL=TRUE
PREFIX ${DEP_DIR}/OGRE3D_SDK
DEPENDS ogredeps)

## External project : OGRE BULLET PLUGIN 
ExternalProject_Add(Ogre_Bullet
GIT_REPOSITORY https://bitbucket.org/alexeyknyshev/ogrebullet.git
PREFIX ${DEP_DIR}/Ogre_Bullet
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DBUILD_SHARED_LIBS:BOOL=TRUE;
-DBULLET_INCLUDE_DIR:PATH=${CMAKE_INSTALL_PREFIX}/include/bullet;
-DBULLET_INCLUDE_COLLISION_DIR:PATH=${CMAKE_INSTALL_PREFIX}/include/bullet/BulletCollision;
-DBULLET_INCLUDE_DYNAMICS_DIR:PATH=${CMAKE_INSTALL_PREFIX}/include/bullet/BulletDynamics;
-DBULLET_INCLUDE_CONVEXDECOMPOSITION_DIR:PATH=${CMAKE_INSTALL_PREFIX}/include/bullet/ConvexDecomposition;
-DBULLET_INCLUDE_SOFTBODY_DIR:PATH=${CMAKE_INSTALL_PREFIX}/include/bullet/BulletSoftBody;
-DBULLET_INCLUDE_LINEARMATH_DIR:PATH=${CMAKE_INSTALL_PREFIX}/include/bullet/LinearMath
DEPENDS OGRE3D BULLET)


# External project : OpenGL Math Library
ExternalProject_Add(GML
GIT_REPOSITORY https://github.com/g-truc/glm.git
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DGLM_TEST_ENABLE:BOOL=TRUE;
-DBUILD_SHARED_LIBS:BOOL=TRUE
BUILD_COMMAND /bin/true
PREFIX ${DEP_DIR}/GML)

#https://bitbucket.org/cegui/cegui
#https://danduk82_@bitbucket.org/danduk82_/cegui
#HG_TAG ${CEGUI_SDK_VERSION}

# External project : CEGUI (GUI-system)
ExternalProject_Add(CEGUI
HG_REPOSITORY https://danduk82_@bitbucket.org/danduk82_/cegui
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DBUILD_SHARED_LIBS:BOOL=TRUE;
-DCEGUI_BUILD_PYTHON_MODULES:BOOL=OFF;
-DCEGUI_BUILD_RENDERER_OGRE:BOOL=ON;
-DOIS_LIB_DBG:PATH=${LIBOISD};
-DOGRE_LIB_DBG:PATH=${LIBOGRED};
-DOIS_LIB:PATH=${LIBOIS};
-DOGRE_LIB:PATH=${LIBOGRE};
-DOGRE_H_PATH:PATH=${OGRE_HOME}/include/OGRE;
-DOIS_H_PATH:PATH=${OGRE_HOME}/include/OIS;
-DCEGUI_SAMPLES_ENABLED:BOOL=FALSE;
-DGML_H_PATH:PATH=${GML_H_PATH}
PREFIX ${DEP_DIR}/CEGUI
DEPENDS OGRE3D)

# official site: https://github.com/imperative/CommunityHydrax
# personal fork: https://github.com/danduk82/CommunityHydrax.git
# External project : OGRE HYDRAX PLUGIN (OGRE plugin for sea)
ExternalProject_Add(HYDRAX
GIT_REPOSITORY https://github.com/danduk82/CommunityHydrax.git
PREFIX ${DEP_DIR}/Ogre_hydrax
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DCMAKE_MODULE_PATH:PATH=${CMAKE_INSTALL_PREFIX}/lib/OGRE/cmake;
-DBUILD_SHARED_LIBS:BOOL=TRUE;
DEPENDS OGRE3D)

# External project : OGRE CAMERA CONTROL SYSTEM PLUGIN (plugin for easy camera handling)
ExternalProject_Add(CCS
SVN_REPOSITORY svn://svn.code.sf.net/p/ogre-ccs/code/trunk
PREFIX ${DEP_DIR}/Ogre_CCS
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DBUILD_SHARED_LIBS:BOOL=TRUE;
DEPENDS OGRE3D)

# External project : OGRE SKYX PLUGIN
ExternalProject_Add(SKYX
GIT_REPOSITORY https://github.com/th3flyboy/SkyX.git
PREFIX ${DEP_DIR}/Ogre_SkyX
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DCMAKE_MODULE_PATH:PATH=${CMAKE_INSTALL_PREFIX}/lib/OGRE/cmake;
-DBUILD_SHARED_LIBS:BOOL=TRUE;
DEPENDS OGRE3D)


#add_subdirectory(HOOengine)

