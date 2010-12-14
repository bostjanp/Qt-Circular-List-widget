cmake_minimum_required(VERSION 2.6)

	SET (PACKAGE Demo-QCircularLW)
	set (TARGETNAME qcircularlw.x)

# set compiler to g++
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")
	message(STATUS  "CMAKE_CXX_COMPILER is ${CMAKE_CXX_COMPILER}")

	message (STATUS "***************************************************************")
	message (STATUS "preparing build scripts fot ${PACKAGE}.")
	message (STATUS "***************************************************************")

	SET( CMAKE_CXX_FLAGS_DEBUG "${UNITTEST_FLAGS} -Wall -DDEBUG" CACHE STRING
		"Flags used by the CXX compiler during debug builds."
		FORCE )
	SET( CMAKE_CXX_FLAGS_RELEASE "-Wall" CACHE STRING
		"Flags used by the CXX compiler during release builds."
		FORCE )

	if (NOT CMAKE_BUILD_TYPE)
		message (STATUS "no build type defined. Default build type: Debug")
		SET(CMAKE_BUILD_TYPE Debug)
	else(NOT CMAKE_BUILD_TYPE)
		message (STATUS "build type: ${CMAKE_BUILD_TYPE}")
	endif(NOT CMAKE_BUILD_TYPE)

include(FindQt4)
if(QT_FOUND)

	include_directories ( ${PROJECT_SOURCE_DIR}/lib )
	message ( STATUS "Package ${PACKAGE}" )
	SET( ${PACKAGE}_SRCS ./main.cpp )
  
# by default only QtCore and QtGui modules are enabled
# other modules must be enabled like this:
#	SET( QT_USE_QTXML TRUE )

# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
	include( ${QT_USE_FILE} )

	link_directories ( ${PROJECT_BINARY_DIR}/lib )
	add_executable(${TARGETNAME} ${${PACKAGE}_SRCS} ${${PACKAGE}_MOC_SRCS} )
	target_link_libraries ( ${TARGETNAME} ${QT_LIBRARIES} qcircularlw )


else(QT_FOUND)
	message(FATAL_ERROR "qt not found")
endif(QT_FOUND)

