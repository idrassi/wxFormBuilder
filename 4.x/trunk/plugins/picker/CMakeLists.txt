############################################################
# plugin-picker
############################################################

# define header and source files for the library
set (HEADER_FILES
  )

set (SOURCE_FILES
	picker.cpp
  )

DEFINE_PLUGIN( picker  )
ADD_PLUGIN( plugin-picker SHARED ${HEADER_FILES} ${SOURCE_FILES} )

