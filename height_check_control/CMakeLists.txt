ADD_EXECUTABLE( height_check_control main.cpp )

IF( CANVAS )
  TARGET_LINK_LIBRARIES( height_check_control ${CANVAS} )
ENDIF( CANVAS )

IF( Boost_FOUND )
  INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )
  TARGET_LINK_LIBRARIES( height_check_control ${Boost_LIBRARIES} )
ENDIF( Boost_FOUND )

FIND_LIBRARY( CGAL CGAL )
IF( CGAL )
  TARGET_LINK_LIBRARIES( height_check_control ${CGAL} )
ENDIF( CGAL )

INSTALL( TARGETS height_check_control DESTINATION bin )
