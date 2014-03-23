# - Find OgreBullet
# Find the native OgreBullet includes and library
#
#   OgreBullet_FOUND       - True if OgreBullet found.
#   OgreBullet_INCLUDE_DIR - where to find includes
#   OgreBullet_LIBRARIES   - List of libraries when using OgreBullet.
#

if(OgreBullet_INCLUDE_DIR)
    # Already in cache, be silent
    set(OgreBullet_FIND_QUIETLY TRUE)
endif(OgreBullet_INCLUDE_DIR)

find_path(OgreBullet_INCLUDE_DIR "Dynamics/OgreBulletDynamicsRigidBody.h"
          PATH_SUFFIXES "OgreBullet")

find_library(OgreBullet_COL_LIB "OgreBulletCol")
find_library(OgreBullet_DYN_LIB "OgreBulletDyn")

set(OgreBullet_INCLUDE_DIRS "${OGREBULLET_INCLUDE_DIR}/Collisions" "${OGREBULLET_INCLUDE_DIR}/Dynamics")
set(OgreBullet_LIBRARIES OgreBulletDyn OgreBulletCol)

# handle the QUIETLY and REQUIRED arguments and set OGREBULLET_FOUND to TRUE if
# all listed variables are TRUE
include("FindPackageHandleStandardArgs")
find_package_handle_standard_args("OgreBullet" DEFAULT_MSG OgreBullet_INCLUDE_DIR OgreBullet_LIBRARIES)

mark_as_advanced(OgreBullet_INCLUDE_DIR OgreBullet_COL_LIB OgreBullet_DYN_LIB)

