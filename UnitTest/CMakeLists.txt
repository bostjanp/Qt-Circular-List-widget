cmake_minimum_required(VERSION 2.8)

SET (PACKAGE UTEST-QCIRCULARLW)
SET (TARGETNAME utQCircularLW.x)

ADD_DEFINITIONS( -g -fno-inline -Wall -Wextra ${QT_DEFINITIONS})

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

message (STATUS "***************************************************************")
message (STATUS "preparing build scripts for ${PACKAGE}  - Unit test.")
message (STATUS "***************************************************************")

SET( CMAKE_CXX_FLAGS_DEBUG "${UNITTEST_FLAGS} -Wall -DDEBUG -ggdb" CACHE STRING
	"Flags used by the CXX compiler during debug builds."
	FORCE )
message (STATUS "no build type defined. Default build type: Debug")
SET(CMAKE_BUILD_TYPE Debug)

include(FindQt4)
if(QT_FOUND)

	set ( QT_USE_QTTEST 1 )

	# tells to include UseQt4.cmake
	set (CMAKE_MODULE_PATH ${CMAKE_ROOT}/Modules )
	include (${QT_USE_FILE})
	include_directories( ${QT_INCLUDE_DIR} )
	include_directories( ${QT_INCLUDE_DIR}/QtTest )
	include_directories (${PROJECT_SOURCE_DIR}/lib )

	set ( ${PACKAGE}_SRCS ut_qcircularlw.cpp )
	set ( ${PACKAGE}_HDRS ut_qcircularlw.h )
	set ( ${PACKAGE}_MOC_HDRS ut_qcircularlw.h )
	#	SET( QT_USE_QTXML TRUE )

	QT4_WRAP_CPP( ${PACKAGE}_MOC_SRCS ${${PACKAGE}_MOC_HDRS} )

	link_directories ( ${PROJECT_BINARY_DIR}/lib )
	
	add_executable (${TARGETNAME}  ${${PACKAGE}_SRCS} ${${PACKAGE}_MOC_SRCS} )
	target_link_libraries( ${TARGETNAME} ${QT_QTTEST_LIBRARY} ${QT_LIBRARIES} qcircularlw )

else(QT_FOUND)
	message(FATAL_ERROR "qt not found")
endif(QT_FOUND)
  
