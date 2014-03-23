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
# Author: Andrea Borghi, alias Danduk82
# Creation Date: 11.12.2013
# License: This engine is provided under the terms of the WTFPL (www.wtfpl.net)

cmake_minimum_required(VERSION 2.8.12)

# third party libraries versions needed
set(HOO_PROJECT engine)
project(${HOO_PROJECT})

set(OGRE_SDK_VERSION v1-8)
set(CEGUI_SDK_VERSION v0-8)
set(OPENAL_VERSION_TAG openal-soft-1.15.1)

# directories
set(DEP_DIR dependencies)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")


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

SET(GLM_H_PATH ${CMAKE_INSTALL_PREFIX}/include)

MESSAGE("LIBOIS = ${LIBOIS}")
MESSAGE("LIBOGRE = ${LIBOGRE}")


include(ExternalProject)
include(HOO_dependencies)
include(HOO_metDependencies)




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
 
include_directories(${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
    ${CEGUI_INCLUDE_DIR}/../
    ${CCS_INCLUDE_DIRS}
    )


add_executable(${HOO_PROJECT} ${HDRS} ${SRCS} )
add_dependencies(${HOO_PROJECT} RescanOgre RescanOIS RescanCEGUI RescanCCS )

if(${OGRE_FOUND})
    target_link_libraries(${HOO_PROJECT} ${OGRE_LIBRARY})
endif()


set(TARGET_LINK_LIBRARIES ${OGRE_LIBRARIES} ${OIS_LIBRARIES} ${CEGUI_LIBRARY} ${CEGUI_LIBRARIES} ${CEGUI_OGRE_LIBRARY})

target_link_libraries(${HOO_PROJECT} ${OGRE_LIBRARY} )

if(UNIX)
 
	install(TARGETS ${HOO_PROJECT}
		RUNTIME DESTINATION bin
		CONFIGURATIONS All)
 
endif(UNIX)
 
