#-----------------------------------------------------------------------------
# Filename:    CMakeLists.txt
#-----------------------------------------------------------------------------
# Purpose: build the dependencies and the engine for:
# "Hearts of Oak, Conquest of the seas" (see www.piratesahoy.net)
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
# 
# CMake project to build the engine for Hearts of Oak, including 
# the necessary external projects (OGRE, CEGUI, etc). 
# 
# Prerequisites:
# To build this project, CMAKE v.2.8.12+ is necessary. Moreover, GIT, MERCURIAL
# and SVN must be installed on the computer. See "README.rst" in the root folder of
# the project.
# 
# License
# This work is free. You can redistribute it and/or modify it under the
# terms of the "Do What The Fuck You Want To Public License", Version 2,
# as published by Sam Hocevar. See the file "LICENSE" in the root folder 
# of the project or visit http://www.wtfpl.net/about for more details.
#
# 
# Author 
# Danduk82, alias Andrea Borghi
#
# Creation date
# 19/01/2014


# we NEED cmake V>=2.8.12. This is required for the external projects 
cmake_minimum_required(VERSION 2.8.12)

# by the way, only include the engine itself for the moment
add_subdirectory(HOOengine)

# in the future, here we could include also resource files, documentation, etc

