#-----------------------------------------------------------------------------
# Filename:    HOO_metDependencies.cmake
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
# Purpose: find dependencies for the engine. The way this file works is quite
# hackish: in the first build, the dependencies are not yet met, because they have 
# to be dowloaded. So the effective dependencies for the project are not met
# during the configuration phase, but become it at build time.
# 
# Author: Andrea Borghi, alias Danduk82
# Creation Date: 11.12.2013
# License: This engine is provided under the terms of the WTFPL (www.wtfpl.net)


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
    else (${OGRE_Terrain_FOUND})
      message(SEND_ERROR "OgreTerrain Library not found.")
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
	add_custom_target(RescanCCS ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS CEGUI)
else(NOT ${CCS_FOUND})
    add_custom_target(RescanCCS)
endif(NOT ${CCS_FOUND})

#find_package(openAL)
#if(NOT ${openAL_FOUND})
#	add_custom_target(RescanopenAL ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS CEGUI)
#else(NOT ${openAL_FOUND})
#    add_custom_target(RescanopenAL)
#endif(NOT ${openAL_FOUND})


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

