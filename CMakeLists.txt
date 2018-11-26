cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(Bob LANGUAGES CXX)

set(BOB_MAJOR_VERSION 0)
set(BOB_MINOR_VERSION 1)
set(BOB_PATCH_VERSION 0)
set(BOB_VERSION
  ${BOB_MAJOR_VERSION}.${BOB_MINOR_VERSION}.${BOB_PATCH_VERSION})

set(INSTALL_LIB_DIR lib CACHE PATH "Install directory for library code")
set(INSTALL_BIN_DIR CACHE PATH "Install directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Instal directory for header files")

if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/CMake/Bob)
endif()

set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL+PREFIX}/${${var}}")
  endif()
endforeach()

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}")

add_subdirectory(bob/core)
add_subdirectory(bob/neural)
add_subdirectory(bob/naive)

export(TARGETS BobCore BobNeural BobNaive FILE "${PROJECT_BINARY_DIR}/BobCoreTargets.cmake")

export(PACKAGE Bob)

file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
  "${INSTALL_INCLUDE_DIR}")

# Build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(BobConfig.cmake.in
  "${PROJECT_BINARY_DIR}/BobConfig.cmake" @ONLY)

# Install tree
set(CONF_INCLUDE_DIRS "\${BOB_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(BobConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/BobConfig.cmake" @ONLY)

# Install and Build trees
configure_file(BobCoreConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/BobCoreConfigVersion.cmake" @ONLY)

# Install the BobCoreConfig.cmake and BobCoreConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/BobCoreConfig.cmake"
  "${PROJECT_BINARY_DIR}/BobCoreConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)

install(EXPORT BobCoreTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)
