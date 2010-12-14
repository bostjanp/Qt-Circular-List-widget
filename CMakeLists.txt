cmake_minimum_required(VERSION 2.6)

project (QCIRCULARLW)

option (TEST "Default test is off" OFF )
add_subdirectory (lib)

if (TEST)
	add_subdirectory (UnitTest)
else (TEST)
	add_subdirectory (demo)
endif (TEST)
