cmake_minimum_required(VERSION 2.6)

# set main package name
	set (PACKAGE QCircularLW)
	SET (TARGETNAME qcircularlw)

# set compiler to g++
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")
	message(STATUS  "CMAKE_CXX_COMPILER is ${CMAKE_CXX_COMPILER}")

	message (STATUS "*********************************************************")
	message (STATUS "preparing build scripts fot ${PACKAGE} libraries for QT4.")
	message (STATUS "*********************************************************")

	SET( CMAKE_CXX_FLAGS_DEBUG "${UNITTEST_FLAGS} -Wall -DDEBUG -ggdb" CACHE STRING
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

# this command finds Qt4 libraries and sets all required variables
# note that it's Qt4, not QT4 or qt4
#FIND_PACKAGE( Qt4 REQUIRED )
include(FindQt4)
if(QT_FOUND)

	include( ${QT_USE_FILE} )

	SET( ${PACKAGE}_SRCS ./qcircularlw.cpp ./qcircularlw.cpp )
	SET( ${PACKAGE}_HDRS ./qcircularlw.h )
	SET( ${PACKAGE}_MOC_HDRS ./qcircularlw.h )
	SET( QT_USE_QTXML TRUE )

	QT4_WRAP_CPP( ${PACKAGE}_MOC_SRCS ${${PACKAGE}_MOC_HDRS} )

	add_library (${TARGETNAME} SHARED ${${PACKAGE}_SRCS} ${${PACKAGE}_MOC_SRCS} )

else(QT_FOUND)
	message(FATAL_ERROR "qt not found")
endif(QT_FOUND)

