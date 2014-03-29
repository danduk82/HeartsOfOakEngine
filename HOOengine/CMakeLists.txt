#-----------------------------------------------------------------------------
# Filename:    CMakeLists.txt
#-----------------------------------------------------------------------------
#
# This source file is part of the
#                        _                __     ___      _    
#   /\  /\___  __ _ _ __| |_ ___    ___  / _|   /___\__ _| | __
#  / /_/ / _ \/ _` | '__| __/ __|  / _ \| |_   //  // _` | |/ /
# / __  /  __/ (_| | |  | |_\__ \ | (_) |  _| / \_// (_| |   < 
# \/ /_/ \___|\__,_|_|   \__|___/  \___/|_|   \___/ \__,_|_|\_\
#                                                              
#    __            _                                           
#   /__\ __   __ _(_)_ __   ___                                
#  /_\| '_ \ / _` | | '_ \ / _ \                               
# //__| | | | (_| | | | | |  __/                               
# \__/|_| |_|\__, |_|_| |_|\___|                               
#            |___/                                             
# 
#-----------------------------------------------------------------------------
# Purpose: build the engine for:
# "Hearts of Oak, Conquest of the seas" (see www.piratesahoy.net)
# 
# Prerequisites:
# To build this project, CMAKE v.2.8.12+ is necessary. Moreover, GIT, MERCURIAL
# and SVN must be installed on the computer. See "README.rst" in the root folder of
# the project.
# 
# Author: Andrea Borghi, alias Danduk82
# Creation Date: 11.12.2013
# License: This engine is provided under the terms of the WTFPL (www.wtfpl.net)


# we NEED cmake V>=2.8.12. This is required for the external projects 
cmake_minimum_required(VERSION 2.8.12)

# name of the executable/project
set(HOO_PROJECT engine)
project(${HOO_PROJECT})

# third party libraries versions
set(OGRE_SDK_VERSION v1-8)
set(CEGUI_SDK_VERSION v0-8)
set(OPENAL_VERSION_TAG openal-soft-1.15.1)

# directories
set(DEP_DIR dependencies)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# select build target. Default will be "Debug" until alpha release version
if(NOT DEFINED BUILD_TARGET )
    set(BUILD_TARGET Debug)
endif(NOT DEFINED BUILD_TARGET)

if(${BUILD_TARGET} STREQUAL Debug)
    set(SUFF "_d")
    MESSAGE("DEBUG! SUFF = ${SUFF}")
endif(${BUILD_TARGET} STREQUAL Debug)

MESSAGE(STATUS "BUILD_TARGET is ${BUILD_TARGET}")
MESSAGE(STATUS CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX})

# these are fundamental
SET(OGRE_HOME ${CMAKE_INSTALL_PREFIX})
SET(LIBOISD ${CMAKE_INSTALL_PREFIX}/lib/libOIS_d.so)
SET(LIBOGRED ${CMAKE_INSTALL_PREFIX}/lib/libOgreMain_d.so)
SET(LIBOIS ${CMAKE_INSTALL_PREFIX}/lib/libOIS.so)
SET(LIBOGRE ${CMAKE_INSTALL_PREFIX}/lib/libOgreMain.so)

# GLM not used for instance, but anyway...
SET(GLM_H_PATH ${CMAKE_INSTALL_PREFIX}/include)

MESSAGE("LIBOIS = ${LIBOIS}")
MESSAGE("LIBOGRE = ${LIBOGRE}")

include(ExternalProject)
# download and compile all the dependencies
#include(HOO_dependencies)
# configure dependencies build
#include(HOO_metDependencies)


include(ExternalProject)
# External project : OGRE_DEPENDENCIES (needed for OGRE)
ExternalProject_Add(ogredeps
HG_REPOSITORY https://bitbucket.org/cabalistic/ogredeps
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DBUILD_SHARED_LIBS:BOOL=TRUE
PREFIX ${DEP_DIR}/ogreDeps)

### External project : OIS PHYSICS (physics engine)
#ExternalProject_Add(OIS
#SVN_REPOSITORY  svn://svn.code.sf.net/p/wgois/code/
#CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
#-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
#-DBUILD_SHARED_LIBS:BOOL=TRUE;
#PREFIX ${DEP_DIR}/OIS)


# External project : OGRE (render engine)
ExternalProject_Add(OGRE
HG_REPOSITORY http://bitbucket.org/sinbad/ogre/
HG_TAG ${OGRE_SDK_VERSION}
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DBUILD_SHARED_LIBS:BOOL=TRUE
PREFIX ${DEP_DIR}/OGRE_SDK
DEPENDS ogredeps)


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
DEPENDS OGRE BULLET)

# new version of CEGUI needs the new version of GLM
# External project : OpenGL Math Library
#ExternalProject_Add(
#    glm
#    PREFIX ${CMAKE_BINARY_DIR}/glm
#    GIT_REPOSITORY https://github.com/g-truc/glm.git
#    CONFIGURE_COMMAND ""
#    BUILD_COMMAND ""
#    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
#                    <SOURCE_DIR>/glm ${CMAKE_BINARY_DIR}/installed/glm
#    LOG_DOWNLOAD ON
#    LOG_INSTALL ON
#    )
    
#https://bitbucket.org/cegui/cegui
#https://danduk82_@bitbucket.org/danduk82_/cegui
#HG_TAG ${CEGUI_SDK_VERSION}
#-DGLM_H_PATH:PATH=${GLM_H_PATH}

# External project : CEGUI (GUI-system)
ExternalProject_Add(CEGUI
HG_REPOSITORY https://bitbucket.org/cegui/cegui
HG_TAG ${CEGUI_SDK_VERSION}
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
PREFIX ${DEP_DIR}/CEGUI
DEPENDS OGRE)

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
DEPENDS OGRE)

## External project : OGRE DEBUG MATERIAL
#ExternalProject_Add(Ogre_debug_material
#HG_REPOSITORY https://danduk82_@bitbucket.org/danduk82_/ogre-debug-drawing-utility
#PREFIX ${DEP_DIR}/Ogre_debug_material
#CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
#-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
#-DCMAKE_MODULE_PATH:PATH=${CMAKE_INSTALL_PREFIX}/lib/OGRE/cmake;
#-DBUILD_SHARED_LIBS:BOOL=TRUE;
#DEPENDS OGRE)

# External project : OGRE CAMERA CONTROL SYSTEM PLUGIN (plugin for easy camera handling)
ExternalProject_Add(CCS
SVN_REPOSITORY svn://svn.code.sf.net/p/ogre-ccs/code/trunk
PREFIX ${DEP_DIR}/Ogre_CCS
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DBUILD_SHARED_LIBS:BOOL=TRUE;
DEPENDS OGRE)

# "original" GIT_REPOSITORY https://github.com/th3flyboy/SkyX.git
# using my own fork to be sure it exists
# External project : OGRE SKYX PLUGIN
ExternalProject_Add(SKYX
GIT_REPOSITORY https://github.com/danduk82/SkyX.git
PREFIX ${DEP_DIR}/Ogre_SkyX
CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX};
-DCMAKE_BUILD_TYPE:STRING=${BUILD_TARGET};
-DOGRE_HOME:PATH=${OGRE_HOME};
-DSKYX_DEPENDENCIES_DIR:PATH=${OGRE_HOME};
-DSKYX_BUILD_SAMPLES:BOOL=FALSE;
-DSKYX_INSTALL_SAMPLES:BOOL=FALSE;
-DCMAKE_MODULE_PATH:PATH=${CMAKE_INSTALL_PREFIX}/lib/OGRE/cmake;
-DBUILD_SHARED_LIBS:BOOL=TRUE;
DEPENDS OGRE)


find_package(OGRE )
if(NOT ${OGRE_FOUND})
    #rerun cmake in initial build
    #will update cmakecache/project files on first build
    #so you may have to reload project after first build
    add_custom_target(RescanOgre ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS OGRE)
else(NOT ${OGRE_FOUND})
    #Rescan becomes a dummy target after first build
    #this prevents cmake from rebuilding cache/projects on subsequent builds
    if (${OGRE_Terrain_FOUND})
    # pretty sure the following include is unneeded
      # include_directories(${OGRE_Terrain_INCLUDE_DIRS})
    # append OgreTerrain to the end of the OGRE_LIBRARIES variable
      set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${OGRE_Terrain_LIBRARIES})  
      message(STATUS "Found OGRE_Terrain: ${OGRE_Terrain_LIBRARIES}")
#    else (${OGRE_Terrain_FOUND})
#      message(SEND_ERROR "OgreTerrain Library not found.")
    endif(${OGRE_Terrain_FOUND})
    add_custom_target(RescanOgre)
endif(NOT ${OGRE_FOUND})

find_package(OIS)
if(NOT ${OIS_FOUND})
	add_custom_target(RescanOIS ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS OIS)
else(NOT ${OIS_FOUND})
    add_custom_target(RescanOIS)
endif(NOT ${OIS_FOUND})
 
find_package(CEGUI)
if(NOT ${CEGUI_FOUND})
	add_custom_target(RescanCEGUI ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS CEGUI)
else(NOT ${CEGUI_FOUND})
    add_custom_target(RescanCEGUI)
endif(NOT ${CEGUI_FOUND})

find_package(CCS)
if(NOT ${CCS_FOUND})
	add_custom_target(RescanCCS ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS CCS)
else(NOT ${CCS_FOUND})
    add_custom_target(RescanCCS)
endif(NOT ${CCS_FOUND})

find_package(openAL)
if(NOT ${openAL_FOUND})
	add_custom_target(RescanopenAL ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS CEGUI)
else(NOT ${openAL_FOUND})
    add_custom_target(RescanopenAL)
endif(NOT ${openAL_FOUND})


# Find Boost
# for boost we do not perform a download as for the others. This needs to be installed
# on the machine if we want to use it, but it is not an imperative dependency.
if (NOT ${OGRE_BUILD_PLATFORM_IPHONE})
	if (WIN32 OR APPLE)
		set(Boost_USE_STATIC_LIBS TRUE)
	else (WIN32 OR APPLE)
		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif (WIN32 OR APPLE)
	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
	endif (MINGW)
	set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
	# Components that need linking (NB does not include header-only components like bind)
	set(OGRE_BOOST_COMPONENTS thread date_time)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	if (NOT ${Boost_FOUND})
		# Try again with the other type of libs
		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	endif(NOT ${Boost_FOUND})
	find_package(Boost QUIET)
	# Set up referencing of Boost
	include_directories(${Boost_INCLUDE_DIR})
	add_definitions(-DBOOST_ALL_NO_LIB)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif(NOT ${OGRE_BUILD_PLATFORM_IPHONE})

# NEEDED dependencies that MUST be built before HOO_PROJECT
SET(HOO_NEEDED_DEPENDENCIES RescanOgre RescanOIS RescanCEGUI RescanCCS)


# headers and source files for the engine itself
set(HDRS
	"./include/HOO_app.h"
    "./include/OIS_2_CEGUI.h"
)
 
set(SRCS
	./src/HOO_app.cpp
	./src/MouseControl.cpp
	./src/TerrainStuff.cpp
	./src/OIS_2_CEGUI.cpp
	./src/engine.cpp
)
 
# include directories for the engine
include_directories(${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
    ${CEGUI_INCLUDE_DIR}/../
    ${CCS_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_INSTALL_PREFIX}/include"
    )




message(STATUS OGRE_INCLUDE_DIRS ${OGRE_INCLUDE_DIRS})
message(STATUS OGRE_SAMPLES_INCLUDEPATH	${OGRE_SAMPLES_INCLUDEPATH})
message(STATUS CEGUI_INCLUDE_DIR    ${CEGUI_INCLUDE_DIR})
message(STATUS CCS_INCLUDE_DIRS    ${CCS_INCLUDE_DIRS})
    
message(STATUS "OIS_INCLUDE_DIRS = ${OIS_INCLUDE_DIRS}")

add_executable(${HOO_PROJECT} ${HDRS} ${SRCS} )

# HOO_PROJECT is dependent on all the dependencies
#add_dependencies(${HOO_PROJECT} ${HOO_NEEDED_DEPENDENCIES})
#add_dependencies(${HOO_PROJECT} OGRE CEGUI CCS )

# link engine and needed libraries
set(TARGET_LINK_LIBRARIES ${OGRE_LIBRARY} ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${CEGUI_LIBRARY} ${CEGUI_LIBRARIES} ${CEGUI_OGRE_LIBRARY})
target_link_libraries(${HOO_PROJECT} ${TARGET_LINK_LIBRARIES} )

# install directives
install(TARGETS ${HOO_PROJECT}
	RUNTIME DESTINATION bin
	CONFIGURATIONS All)


#if(UNIX) 
#	install(TARGETS ${HOO_PROJECT}
#		RUNTIME DESTINATION bin
#		CONFIGURATIONS All)
#	
#	install(FILES ${CMAKE_SOURCE_DIR}/plugins.cfg
#	    ${CMAKE_SOURCE_DIR}/plugins_d.cfg
#        ${CMAKE_SOURCE_DIR}/resources.cfg
#        ${CMAKE_SOURCE_DIR}/resources_d.cfg
#        DESTINATION bin
#        CONFIGURATIONS Release RelWithDebInfo Debug)
#endif(UNIX)
 
