######################################
# CMAKE settings / workarounds
######################################
cmake_minimum_required(VERSION 2.8) # 2.6 should be okay..but I didn't checked it
cmake_policy(VERSION 2.8)
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE) 

# by default use MONOLITH build only on windows
SET(MONOLITH_DEFAULT FALSE)

if(WIN32)
  SET(MONOLITH_DEFAULT TRUE)   
  set(CMAKE_USE_RELATIVE_PATHS true)
endif()

# Remove /STACK:10000000 set by CMake. This value for stack size
# is very high, limiting the number of threads we can spawn.
# Default value used by Windows is 1MB which is good enough.
STRING(REGEX REPLACE "/STACK:[0-9]+" "" CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
STRING(REGEX REPLACE "/STACK:[0-9]+" "" CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")

######################################
# options
######################################
OPTION(wxFB_MONOLITH_WXWIDGETS "use monolith wxwidget" ${MONOLITH_DEFAULT})
OPTION(wxFB_DEBUG   "enable formbuilder debug" FALSE)

######################################
# Set up the basic build environment
######################################
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "")
set(BUILD_SHARED_LIBS true)

# main project
PROJECT(wxFB_PRJ) 

# for our cmake scripts
set(CMAKE_MODULE_PATH 
  "${wxFB_PRJ_SOURCE_DIR}/cmake"
  )

# VS flags
if (MSVC)
  if (CMAKE_CL_64)
    # Visual Studio bails out on debug builds in 64bit mode unless this flag is set...
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /bigobj")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /bigobj")
  endif ()
endif ()

if (MINGW)
  add_definitions(-D_WIN32_WINNT=0x0500)
endif ()

# Specify build path
if (WIN32)
  # win32: build in output directory (and get rid of 'debug/release' sub dir)
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${wxFB_PRJ_SOURCE_DIR}/output")
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
else()
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
  SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/wxformbuilder")
endif()

IF (wxFB_DEBUG)
    SET(CMAKE_DEBUG_POSTFIX "d")
ENDIF()

######################################
# Dependencies
######################################
# wxWidget -> www.wxwidgets.org
INCLUDE(FindwxWidgets)
IF (wxFB_MONOLITH_WXWIDGETS)
  FIND_PACKAGE(wxWidgets COMPONENTS mono )
  IF(NOT wxWidgets_FOUND)
    MESSAGE(SEND_ERROR "wxWidgets Monolith not found!\nInstall/Compile wxWidgetSet.\nMake sure WXWIN environment variable is set.")
  ENDIF()
ELSE()

  FIND_PACKAGE(wxWidgets COMPONENTS base core aui adv html xml richtext xrc propgrid stc net)
  
  IF(NOT wxWidgets_FOUND)
    MESSAGE(SEND_ERROR "wxWidgets 2.9+ libs/dlls not found!\nInstall/Compile wxWidget.\nMake sure WXWIN environment variable is set.")
  ENDIF()
ENDIF()

# Boost -> www.boost.org
FIND_PACKAGE( Boost 1.31.0)
IF(NOT Boost_FOUND)
  MESSAGE(SEND_ERROR "Boost not found!\nSet BOOSTROOT environment var or set Boost directories manual.")
ENDIF()

# Doxygen -> http://www.stack.nl/~dimitri/doxygen/index.html
INCLUDE(FindDoxygen)

######################################
# Helper for PLUGINs
######################################

# PART1: define a plugin
macro(DEFINE_PLUGIN name)

  # create DLL flag (not for "plugin-base")
  IF (NOT name STREQUAL "")
    ADD_DEFINITIONS(-DBUILD_DLL)
  ENDIF()
  
  # use TICPP
  ADD_DEFINITIONS(-DTIXML_USE_TICPP)
  
  # debug
  IF (wxFB_DEBUG)
    ADD_DEFINITIONS(-D__WXFB_DEBUG__)
  ENDIF()
  
  # include wxWidget & SDK stuff
  INCLUDE( ${wxWidgets_USE_FILE} )
  INCLUDE_DIRECTORIES( 
      ${WXWINDOWS_INCLUDE_PATH} 
      "${wxFB_PRJ_SOURCE_DIR}/sdk/plugin_interface" 
      "${wxFB_PRJ_SOURCE_DIR}/sdk/tinyxml" 
      )
  
  SET(wxFB_PRJ_CUR_PLUGIN_NAME ${name})
endmacro()

# PART2: create the plugin
macro(ADD_PLUGIN)

  # create
  ADD_LIBRARY( ${ARGV} ) 
  ADD_DEPENDENCIES( ${ARGV0} plugin-interface TiCPP )
  TARGET_LINK_LIBRARIES( ${ARGV0} plugin-interface TiCPP )

  # set output name and dir
  if (WIN32)
    SET_TARGET_PROPERTIES( ${ARGV0} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${wxFB_PRJ_SOURCE_DIR}/output/plugins/${wxFB_PRJ_CUR_PLUGIN_NAME}"
      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${wxFB_PRJ_SOURCE_DIR}/output/plugins/${wxFB_PRJ_CUR_PLUGIN_NAME}"
      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${wxFB_PRJ_SOURCE_DIR}/output//plugins/${wxFB_PRJ_CUR_PLUGIN_NAME}"
    )  
  else()
    SET_TARGET_PROPERTIES( ${ARGV0} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY "${wxFB_PRJ_SOURCE_DIR}/output/lib/wxformbuilder"
      )
  endif()

  SET_TARGET_PROPERTIES( ${ARGV0} PROPERTIES
      PREFIX "lib"   # use "lib"-prefix on all plattforms
      RUNTIME_OUTPUT_NAME "${wxFB_PRJ_CUR_PLUGIN_NAME}"
      LIBRARY_OUTPUT_NAME "${wxFB_PRJ_CUR_PLUGIN_NAME}"
      ARCHIVE_OUTPUT_NAME "${wxFB_PRJ_CUR_PLUGIN_NAME}"
    )
  
  # INSTALL
  if(WIN32)    
    INSTALL(TARGETS ${ARGV0} DESTINATION "plugins/${wxFB_PRJ_CUR_PLUGIN_NAME}")
  else()
    INSTALL(TARGETS ${ARGV0} DESTINATION "lib/wxformbuilder")
    
    # with cmake2.8 we could use "OPTIONAL" instead of the "if"
    if(EXISTS "${wxFB_PRJ_SOURCE_DIR}/output/plugins/${wxFB_PRJ_CUR_PLUGIN_NAME}/icons")
      INSTALL(DIRECTORY "${wxFB_PRJ_SOURCE_DIR}/output/plugins/${wxFB_PRJ_CUR_PLUGIN_NAME}/icons"
              DESTINATION "share/wxformbuilder/plugins/${wxFB_PRJ_CUR_PLUGIN_NAME}"
              PATTERN ".svn" EXCLUDE)
    endif()
    
    if(EXISTS "${wxFB_PRJ_SOURCE_DIR}/output/plugins/${wxFB_PRJ_CUR_PLUGIN_NAME}/xml")
      INSTALL(DIRECTORY "${wxFB_PRJ_SOURCE_DIR}/output/plugins/${wxFB_PRJ_CUR_PLUGIN_NAME}/xml"
              DESTINATION "share/wxformbuilder/plugins/${wxFB_PRJ_CUR_PLUGIN_NAME}"
              PATTERN ".svn" EXCLUDE)
    endif()
  endif()
endmacro()

######################################
# Projects
######################################
add_subdirectory(sdk)
add_subdirectory(src)
add_subdirectory(plugins)

######################################
# Doxygen 
######################################
IF (DOXYGEN_FOUND)
  CONFIGURE_FILE( "${wxFB_PRJ_SOURCE_DIR}/cmake/Doxyfile.in" ${CMAKE_BINARY_DIR}/doxyfile)
	ADD_CUSTOM_TARGET(DOC COMMAND 
    ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${wxFB_PRJ_SOURCE_DIR}
    COMMENT "Building documentation" VERBATIM
  )
ENDIF() 

######################################
# some "make" helpers
######################################
#if (UNIX)
#    ADD_CUSTOM_TARGET(uninstall  "${CMAKE_COMMAND}" -E cmake_echo_color --switch=$(COLOR) --cyan "PLEASE USE: xargs rm < install_manifest.txt") 
#endif()
