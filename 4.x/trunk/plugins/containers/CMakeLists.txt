############################################################
# 
############################################################
PROJECT(plugin-containers)

# define header and source files for the library
set (HEADER_FILES
  bookutils.h
  )

set (SOURCE_FILES
	containers.cpp
  )

DEFINE_PLUGIN( containers )
ADD_PLUGIN( plugin-containers SHARED ${HEADER_FILES} ${SOURCE_FILES} )

