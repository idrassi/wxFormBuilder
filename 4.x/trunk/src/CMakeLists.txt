############################################################
# Main Application
############################################################

# Source files
set (CODEGEN_FILES
	codegen/codegen.h
	codegen/codewriter.h
	codegen/cppcg.h
	codegen/pythoncg.h
	codegen/xrccg.h
	codegen/codegen.cpp
	codegen/codewriter.cpp
	codegen/cppcg.cpp
	codegen/pythoncg.cpp
	codegen/xrccg.cpp
  )

set (MODEL_FILES
	model/database.h
	model/objectbase.h
	model/types.h
	model/xrcfilter.h
	model/database.cpp
	model/objectbase.cpp
	model/types.cpp
	model/xrcfilter.cpp
  )

set (RAD_FILES_CODEED
	rad/codeeditor/codeeditor.h
	rad/codeeditor/codeeditor.cpp
  )

set (RAD_FILES_PANELS
	rad/genericpanel.h
	rad/genericpanel.cpp
	rad/cpppanel/cpppanel.h
	rad/cpppanel/cpppanel.cpp
	rad/pythonpanel/pythonpanel.h
	rad/xrcpanel/xrcpanel.h
	rad/pythonpanel/pythonpanel.cpp
	rad/xrcpanel/xrcpanel.cpp
	rad/xrcpreview/xrcpreview.h
	rad/xrcpreview/xrcpreview.cpp
  )

set (RAD_FILES_DESIGNER
	rad/designer/innerframe.h
	rad/designer/menubar.h
	rad/designer/visualeditor.h
	rad/designer/visualobj.h
	rad/designer/window_buttons.h
	rad/designer/innerframe.cpp
	rad/designer/menubar.cpp
	rad/designer/visualeditor.cpp
	rad/designer/visualobj.cpp
  )

set (RAD_FILES_GENCLASS
	rad/geninheritclass/geninhertclass.h
	rad/geninheritclass/geninhertclass_gui.h
	rad/geninheritclass/geninhertclass.cpp
	rad/geninheritclass/geninhertclass_gui.cpp
  )
  
set (RAD_FILES
	rad/dataobject/dataobject.h
	rad/inspector/objinspect.h
	rad/objecttree/objecttree.h
	rad/about.h
	rad/appdata.h
	rad/bitmaps.h
	rad/cmdproc.h
	rad/customkeys.h
	rad/mainframe.h
	rad/menueditor.h
	rad/title.h
	rad/wxfbevent.h
	rad/wxfbmanager.h
	rad/wxfbpalette.h
	rad/dataobject/dataobject.cpp
	rad/inspector/objinspect.cpp
	rad/objecttree/objecttree.cpp
	rad/about.cpp
	rad/appdata.cpp
	rad/bitmaps.cpp
	rad/cmdproc.cpp
	rad/customkeys.cpp
	rad/mainframe.cpp
	rad/menueditor.cpp
	rad/title.cpp
	rad/wxfbevent.cpp
	rad/wxfbmanager.cpp
	rad/wxfbpalette.cpp
	rad/maingui.h
	rad/splashscreen.h
	rad/maingui.cpp
	rad/splashscreen.cpp
  )

set (UTIL_FILES
	dbg_stack_trace/stack.hpp
    md5/md5.hh
    md5/md5.cc
	utils/annoyingdialog.h
	utils/annoyingdialog.cpp
	utils/debug.h
	utils/debug.cpp
	utils/encodingutils.h
	utils/encodingutils.cpp
	utils/stringutils.h
	utils/stringutils.cpp
	utils/typeconv.h
	utils/typeconv.cpp
	utils/wxfbdefs.h
	utils/wxfbexception.h
	utils/wxfbipc.h
	utils/wxfbipc.cpp
	utils/wxlogstring.h
  )



# Plattform depending
set (SOURCE_FILES "")
IF( WIN32 )
  SET(SOURCE_FILES ${SOURCE_FILES} 
                   wxFormBuilder.rc)
ENDIF( WIN32 )

# Groups (VS only)
SOURCE_GROUP(CodeGen FILES ${CODEGEN_FILES})
SOURCE_GROUP(Model FILES ${MODEL_FILES})
SOURCE_GROUP(Util FILES ${UTIL_FILES})
SOURCE_GROUP(RAD FILES ${RAD_FILES})
SOURCE_GROUP(RAD\\CodeEditor FILES ${RAD_FILES_CODEED})
SOURCE_GROUP(RAD\\CodePanels FILES ${RAD_FILES_PANELS})
SOURCE_GROUP(RAD\\designer FILES ${RAD_FILES_DESIGNER})
SOURCE_GROUP(RAD\\GenClass FILES ${RAD_FILES_GENCLASS})
SOURCE_GROUP("" FILES ${SOURCE_FILES})

# wxwidget
IF (MSVC_VERSION GREATER 1300)
  ADD_DEFINITIONS (/D _CRT_SECURE_NO_WARNINGS)
ENDIF()
INCLUDE( ${wxWidgets_USE_FILE} )

# use TiCPP
ADD_DEFINITIONS(-DTIXML_USE_TICPP)

# debug
IF (wxFB_DEBUG)
  ADD_DEFINITIONS(-D__WXFB_DEBUG__)
ENDIF()
 
INCLUDE_DIRECTORIES(
  "."
  "../sdk/plugin_interface"
  "../sdk/tinyxml"
  ${WXWINDOWS_INCLUDE_PATH} 
  ${Boost_INCLUDE_DIRS}
  )

# MAIN FILE
ADD_EXECUTABLE(wxFormBuilder WIN32
    ${CODEGEN_FILES} 
    ${MODEL_FILES} 
    ${RAD_FILES} 
    ${RAD_FILES_CODEED}
    ${RAD_FILES_PANELS}
    ${RAD_FILES_DESIGNER}
    ${RAD_FILES_GENCLASS}
    ${UTIL_FILES} 
    ${HEADER_FILES} ${SOURCE_FILES} ) 

# linker
IF( WIN32 )
  # manifest is included through wxWidget resources
  SET_TARGET_PROPERTIES(wxFormBuilder PROPERTIES LINK_FLAGS " /MANIFEST:NO")
  
  if (MSVC_VERSION GREATER 1599)
    message(WARNING "(CMake bug): in VS2010 you have to disable 'Generate Manifest' in wxFormBuilder project linker options.")
  ENDIF()
ENDIF( WIN32 )

ADD_DEPENDENCIES( wxFormBuilder TiCPP)
TARGET_LINK_LIBRARIES(wxFormBuilder ${wxWidgets_LIBRARIES} TiCPP)

# use lower case target name(for linux)
SET_TARGET_PROPERTIES( wxFormBuilder PROPERTIES RUNTIME_OUTPUT_NAME "wxformbuilder" )

# create symlinks for debugging on linux
if (UNIX)
    ADD_CUSTOM_COMMAND(TARGET wxFormBuilder POST_BUILD
                    COMMAND "${CMAKE_COMMAND}" -E  make_directory "${CMAKE_BINARY_DIR}/share"
                    COMMAND "${CMAKE_COMMAND}" -E create_symlink "${wxFB_PRJ_SOURCE_DIR}/output/" "${CMAKE_BINARY_DIR}/share/wxformbuilder"
                    COMMENT "Creating debug symlinks"
                                                 )
endif()

INSTALL(TARGETS wxFormBuilder DESTINATION bin)
INSTALL(DIRECTORY "${wxFB_PRJ_SOURCE_DIR}/output/xml"
        DESTINATION "share/wxformbuilder"
        PATTERN ".svn" EXCLUDE)
INSTALL(DIRECTORY "${wxFB_PRJ_SOURCE_DIR}/output/resources"
        DESTINATION "share/wxformbuilder"
        PATTERN ".svn" EXCLUDE)

