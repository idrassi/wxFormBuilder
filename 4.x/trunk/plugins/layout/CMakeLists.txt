############################################################
# plugin-layout
############################################################

# define header and source files for the library
set (HEADER_FILES
  )

set (SOURCE_FILES
	layout.cpp
  )

DEFINE_PLUGIN( layout  )
ADD_PLUGIN( plugin-layout SHARED ${HEADER_FILES} ${SOURCE_FILES} )

