############################################################
# plugin-interface
############################################################

# define header source files for the library
SET (HEADER_FILES
  component.h
  fontcontainer.h
  plugin.h
  xrcconv.h
  )

SET (SOURCE_FILES
	xrcconv.cpp
  )

DEFINE_PLUGIN( "" ) # include basic plugin stuff
ADD_LIBRARY( plugin-interface STATIC ${HEADER_FILES} ${SOURCE_FILES}) 
ADD_DEPENDENCIES( plugin-interface  TiCPP)
TARGET_LINK_LIBRARIES( plugin-interface  ${wxWidgets_LIBRARIES})

