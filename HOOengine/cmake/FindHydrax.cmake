# - Find Hydrax
# Find the native Hydrax includes and library
#
#   HYDRAX_FOUND       - True if Hydrax found.
#   HYDRAX_INCLUDE_DIR - where to find includes
#   HYDRAX_LIBRARIES   - List of libraries when using Hydrax.
#

if(HYDRAX_INCLUDE_DIR)
    # Already in cache, be silent
    set(HYDRAX_FIND_QUIETLY TRUE)
endif(HYDRAX_INCLUDE_DIR)

find_path(HYDRAX_INCLUDE_DIR "Hydrax.h"
          PATH_SUFFIXES "Hydrax")

find_library(HYDRAX_LIB "Hydrax")

set(HYDRAX_INCLUDE_DIRS "${HYDRAX_INCLUDE_DIR}" "${HYDRAX_INCLUDE_DIR}/Modules" "${HYDRAX_INCLUDE_DIR}/Noise")
set(HYDRAX_LIBRARIES Hydrax) 

# handle the QUIETLY and REQUIRED arguments and set Hydrax_FOUND to TRUE if
# all listed variables are TRUE
include("FindPackageHandleStandardArgs")
find_package_handle_standard_args("HYDRAX" DEFAULT_MSG Hydrax_INCLUDE_DIR HYDRAX_LIBRARIES)

mark_as_advanced(HYDRAX_INCLUDE_DIR HYDRAX_LIB)

