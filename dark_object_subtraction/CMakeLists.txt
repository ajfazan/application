ADD_EXECUTABLE( dark_object_subtraction main.cpp )

# SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

IF( Boost_FOUND )
  INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )
  TARGET_LINK_LIBRARIES( dark_object_subtraction ${Boost_LIBRARIES} )
ENDIF( Boost_FOUND )

IF( CANVAS )
  TARGET_LINK_LIBRARIES( dark_object_subtraction ${CANVAS} )
ENDIF( CANVAS )

INSTALL( TARGETS dark_object_subtraction DESTINATION bin )
