cmake_minimum_required(VERSION 2.8)

SET( BIN final )
SET( SOURCE_ROOT .)
project( ${BIN} )

FIND_PACKAGE(Boost REQUIRED COMPONENTS system thread regex)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

SET( CMAKE_CXX_FLAGS "-std=c++11 -lboost_system -pthread" ) 
aux_source_directory( ${SOURCE_ROOT} SOURCES )
add_executable( ${BIN} ${SOURCES} )
TARGET_LINK_LIBRARIES(${BIN} ${USED_LIBS})
