############################################################
# plugin-common
############################################################

# define header and source files for the library
set (HEADER_FILES
  )

set (SOURCE_FILES
	common.cpp
  )

DEFINE_PLUGIN( common )
ADD_PLUGIN( plugin-common SHARED ${HEADER_FILES} ${SOURCE_FILES} ) 

