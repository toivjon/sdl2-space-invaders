# =============================================================================
# A simple CMake module for finding the SDL2 Image library definitions.
#
# Note that currently this is a highly fragile module. Module does currently
# only support the finding of SDL2 Image on Windows systems. It also requires
# the SDL2 Image binaries (DLL) to be found and copied on the build directory.
# =============================================================================
# find the SDL2 Image include directory.
find_path(SDL2_IMAGE_INCLUDE SDL_image.h
	HINTS
	$ENV{SDL2IMAGEDIR}
	PATH_SUFFIXES include
)

# find the 32bit version of the SDL2 Image DLL library.
find_path(SDL2_IMAGE_BINARY_PATH SDL2_image.dll 
	HINTS
	$ENV{SDL2IMAGEDIR}
	PATH_SUFFIXES lib/x86
)

# find the 32bit version of the SDL2 Image library.
find_library(SDL2_IMAGE_LIBRARY
	NAMES SDL2_image
	HINTS
	$ENV{SDL2IMAGEDIR}
	PATH_SUFFIXES lib/x86
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2_IMAGE
	REQUIRED_VARS SDL2_IMAGE_LIBRARY SDL2_IMAGE_INCLUDE SDL2_IMAGE_BINARY_PATH
)
