############################################################
# plugin-additional
############################################################

# define header and source files for the library
set (HEADER_FILES
  )

set (SOURCE_FILES
	additional.cpp
  )

DEFINE_PLUGIN( additional )
ADD_PLUGIN( plugin-additional SHARED ${HEADER_FILES} ${SOURCE_FILES} ) 

