# =============================================================================
# A simple CMake module for finding the SDL2 TTF library definitions.
#
# Note that currently this is a highly fragile module. Module does currently
# only support the finding of SDL2 TTF on Windows systems. It does also require
# the SDL2 TTF binaries (DLL) to be found and copied on the build directory.
# =============================================================================
# find the SDL2 TTF include directory.
find_path(SDL2_TTF_INCLUDE SDL_ttf.h
	HINTS
	$ENV{SDL2TTFDIR}
	PATH_SUFFIXES include
)

# find the 32bit version of the SDL2 TTF DLL library.
find_path(SDL2_TTF_BINARY_PATH SDL2_ttf.dll 
	HINTS
	$ENV{SDL2TTFDIR}
	PATH_SUFFIXES lib/x86
)

# find the 32bit version of the SDL2 TTF library.
find_library(SDL2_TTF_LIBRARY
	NAMES SDL2_ttf
	HINTS
	$ENV{SDL2TTFDIR}
	PATH_SUFFIXES lib/x86
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2_TTF
	REQUIRED_VARS SDL2_TTF_LIBRARY SDL2_TTF_INCLUDE SDL2_TTF_BINARY_PATH
)
