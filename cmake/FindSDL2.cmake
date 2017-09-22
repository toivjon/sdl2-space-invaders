# =============================================================================
# A simple CMake module for finding the SDL2 library definitions.
#
# Note that currently this is a highly fragile module. Module does currently
# only support the finding of SDL2 on Windows systems. It does also require
# the SDL2 binary (DLL) to be found and copied on the build directory.
# =============================================================================
# find the SDL2 include directory.
find_path(SDL2_INCLUDE SDL.h
	HINTS
	$ENV{SDL2DIR}
	PATH_SUFFIXES include
)

# find the 32bit version of the SDL2 DLL library.
find_path(SDL2_BINARY_PATH SDL2.dll
	HINTS
	$ENV{SDL2DIR}
	PATH_SUFFIXES lib/x86
)

# find the 32bit version of the SDL2 library.
find_library(SDL2_LIBRARY
	NAMES SDL2
	HINTS
	$ENV{SDL2DIR}
	PATH_SUFFIXES lib/x86
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2
	REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE SDL2_BINARY_PATH
)
