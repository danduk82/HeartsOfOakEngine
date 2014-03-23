#-------------------------------------------------------------------
# This file is part of the CMake build system for CCS (Camera Control system for Ogre)
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# - Try to find CCS
# Once done, this will define
#
#  CCS_FOUND - system has CCS
#  CCS_INCLUDE_DIRS - the CCS include directories 
#  CCS_LIBRARIES - link these to use CCS

include(FindPkgMacros)
findpkg_begin(CCS)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(CCS_HOME)
getenv_path(OGRE_SDK)
getenv_path(OGRE_HOME)
getenv_path(OGRE_SOURCE)

# construct search paths
set(CCS_PREFIX_PATH 
    ${CCS_HOME} 
    ${ENV_CCS_HOME} 
    ${OGRE_SOURCE}
    ${OGRE_SDK} 
    ${ENV_OGRE_SDK}
    ${OGRE_HOME} 
    ${ENV_OGRE_HOME})
    
create_search_paths(CCS)
# redo search if prefix path changed
clear_if_changed(CCS_PREFIX_PATH
  CCS_LIBRARY_FWK
  CCS_LIBRARY_REL
  CCS_LIBRARY_DBG
  CCS_INCLUDE_DIR
)

set(CCS_LIBRARY_NAMES CCS)
get_debug_names(CCS_LIBRARY_NAMES)

use_pkgconfig(CCS_PKGC CCS)

# For CCS, prefer static library over framework (important when referencing CCS source build)
set(CMAKE_FIND_FRAMEWORK "LAST")

findpkg_framework(CCS)
if (CCS_HOME)
  # CCS uses the 'includes' path for its headers in the source release, not 'include'
  set(CCS_INC_SEARCH_PATH ${CCS_INC_SEARCH_PATH} ${CCS_HOME}/includes)
endif()
if (APPLE AND CCS_HOME)
  # CCS source build on Mac stores libs in a different location
  # Also this is for static build
  set(CCS_LIB_SEARCH_PATH ${CCS_LIB_SEARCH_PATH} ${CCS_HOME}/Mac/XCode-2.2/build)
endif()

message("CCS_HOME = ${CCS_HOME}")
message("CCS_LIB_SEARCH_PATH = ${CCS_LIB_SEARCH_PATH}")
message("CCS_INC_SEARCH_PATH = ${CCS_INC_SEARCH_PATH}")
message("CCS_PKGC_INCLUDE_DIRS = ${CCS_PKGC_INCLUDE_DIRS}")


find_path(CCS_INCLUDE_DIR NAMES CCSCameraControlSystem.h HINTS ${CCS_INC_SEARCH_PATH} ${CCS_PKGC_INCLUDE_DIRS} PATH_SUFFIXES CCS)
find_library(CCS_LIBRARY_REL NAMES ${CCS_LIBRARY_NAMES} HINTS ${CCS_LIB_SEARCH_PATH} ${CCS_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "" release relwithdebinfo minsizerel)
find_library(CCS_LIBRARY_DBG NAMES ${CCS_LIBRARY_NAMES_DBG} HINTS ${CCS_LIB_SEARCH_PATH} ${CCS_PKGC_LIBRARY_DIRS} PATH_SUFFIXES "" debug)
make_library_set(CCS_LIBRARY)

findpkg_finish(CCS)

# Reset framework finding
set(CMAKE_FIND_FRAMEWORK "FIRST")
