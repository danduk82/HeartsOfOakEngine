# - Find SkyX
# Find the native SkyX includes and library
#
#   SKYX_FOUND       - True if SkyX found.
#   SKYX_INCLUDE_DIR - where to find includes
#   SKYX_LIBRARIES   - List of libraries when using SkyX.
#

if(SKYX_INCLUDE_DIR)
    # Already in cache, be silent
    set(SKYX_FIND_QUIETLY TRUE)
endif(SKYX_INCLUDE_DIR)

find_path(SKYX_INCLUDE_DIR "SkyX.h"
          PATH_SUFFIXES "SkyX")

find_library(SKYX_LIB "SkyX")

set(SKYX_INCLUDE_DIRS "${SKYX_INCLUDE_DIR}" "${SKYX_INCLUDE_DIR}/VClouds")
set(SKYX_LIBRARIES SkyX) 

# handle the QUIETLY and REQUIRED arguments and set SkyX_FOUND to TRUE if
# all listed variables are TRUE
include("FindPackageHandleStandardArgs")
find_package_handle_standard_args("SKYX" DEFAULT_MSG SkyX_INCLUDE_DIR SKYX_LIBRARIES)

mark_as_advanced(SKYX_INCLUDE_DIR SKYX_LIB)

