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
include(HOO_dependencies)
# configure dependencies build
include(HOO_metDependencies)

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
    )

add_executable(${HOO_PROJECT} ${HDRS} ${SRCS} )

# HOO_PROJECT is dependent on all the dependencies
add_dependencies(${HOO_PROJECT} ${HOO_NEEDED_DEPENDENCIES})

# link engine and needed libraries
set(TARGET_LINK_LIBRARIES ${OGRE_LIBRARY} ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${CEGUI_LIBRARY} ${CEGUI_LIBRARIES} ${CEGUI_OGRE_LIBRARY})
target_link_libraries(${HOO_PROJECT} ${TARGET_LINK_LIBRARIES} )

# install directives
if(UNIX) 
	install(TARGETS ${HOO_PROJECT}
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
endif(UNIX)
 
