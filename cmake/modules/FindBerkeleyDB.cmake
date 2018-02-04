# - Try to find BerkeleyDB library
# Once done this will define
#
# BERKELEY_DB_FOUND - system has BerkeleyDB headers and libraries
# BERKELEY_DB_INCLUDE_DIR - BerkeleyDB header directories
# BERKELEY_DB_LIBRARY_DIR - BerkeleyDB library directories
# BERKELEY_DB_LIBRARIES - BerkeleyDB libraries to link with
#
# Helper variables:
#
# BerkeleyDB_PREFIX - directory that contains `include' directory with BerkeleyDB headers and `lib' directory with BerkeleyDB libraries.
# BerkeleyDB_INCLUDE_DIRS - directories to search BerkeleyDB headers in.
# BerkeleyDB_LIBRARY_DIRS - directory to search BerkeleyDB libraries in.

INCLUDE(FindPackageHandleStandardArgs)

IF(NOT BERKELEY_DB_FOUND OR NOT BERKELEY_DB_INCLUDE_DIR OR NOT BERKELEY_DB_LIBRARY_DIR OR NOT BERKELEY_DB_LIBRARIES)

  IF(DEFINED BerkeleyDB_PREFIX AND NOT DEFINED BerkeleyDB_INCLUDE_DIRS)
    SET(BerkeleyDB_INCLUDE_DIRS "${BerkeleyDB_PREFIX}/include")
  ENDIF()

  IF(DEFINED BerkeleyDB_PREFIX AND NOT DEFINED BerkeleyDB_LIBRARY_DIRS)
    SET(BerkeleyDB_LIBRARY_DIRS "${BerkeleyDB_PREFIX}/lib")
  ENDIF()

  FIND_FILE(_BerkeleyDB_Header NAMES db.h PATHS ${BerkeleyDB_INCLUDE_DIRS})
  GET_FILENAME_COMPONENT(BERKELEY_DB_INCLUDE_DIR ${_BerkeleyDB_Header} PATH)

  FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/CMakeTmp/berkeleydb_version.cc"
    "#include <cstdio>
#include <db.h>
int main() { printf(\"%d%d\",  DB_VERSION_MAJOR,  DB_VERSION_MINOR); }")

  TRY_RUN(_BerkeleyDB_Version_Run_Result _BerkeleyDB_Version_Compile_Result
    "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/CMakeTmp"
    "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/CMakeTmp/berkeleydb_version.cc"
    CMAKE_FLAGS
    "-DINCLUDE_DIRECTORIES:STRING=${BERKELEY_DB_INCLUDE_DIR}"
    COMPILE_OUTPUT_VARIABLE _BerkeleyDB_Version_Compile_Output
    RUN_OUTPUT_VARIABLE _BerkeleyDB_Version)

  FIND_LIBRARY(_BerkeleyDB_Library NAMES db${_BerkeleyDB_Version} libdb${_BerkeleyDB_Version} PATHS ${BerkeleyDB_LIBRARY_DIRS})
  GET_FILENAME_COMPONENT(BERKELEY_DB_LIBRARY_DIR ${_BerkeleyDB_Library} PATH)
  GET_FILENAME_COMPONENT(BERKELEY_DB_LIBRARIES ${_BerkeleyDB_Library} NAME)

  IF(BERKELEY_DB_INCLUDE_DIR AND BERKELEY_DB_LIBRARY_DIR AND BERKELEY_DB_LIBRARIES)
    SET(BERKELEY_DB_FOUND TRUE CACHE BOOL "BerkeleyDB has been found")
    SET(BERKELEY_DB_INCLUDE_DIR ${BERKELEY_DB_INCLUDE_DIR} CACHE PATH "Directory with BerkeleyDB headers")
    SET(BERKELEY_DB_LIBRARY_DIR ${BERKELEY_DB_LIBRARY_DIR} CACHE PATH "Directory with BerkeleyDB libraries")
    SET(BERKELEY_DB_LIBRARIES ${BERKELEY_DB_LIBRARIES} CACHE PATH "BerkeleyDB libraries")
  ENDIF()

  FIND_PACKAGE_HANDLE_STANDARD_ARGS(BerkeleyDB DEFAULT_MSG BERKELEY_DB_FOUND BERKELEY_DB_INCLUDE_DIR BERKELEY_DB_LIBRARY_DIR BERKELEY_DB_LIBRARIES)

ENDIF()
