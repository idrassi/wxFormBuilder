############################################################
# plugin-edit
############################################################

# define header and source files for the library
set (HEADER_FILES
  )

set (SOURCE_FILES
	edit.cpp
  )

DEFINE_PLUGIN( edit  )
ADD_PLUGIN( plugin-edit SHARED ${HEADER_FILES} ${SOURCE_FILES} )

