cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0048 NEW)
project(labParadigm VERSION 0.0.1 LANGUAGES CXX)

# Here is the cmake magic
#https://crascit.com/2015/07/25/cmake-gtest/

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

include(GoogleTest)

SET(CES12_SRC "src" CACHE FILEPATH "Directory with student sources")

include_directories( ${CES12_SRC} include lib )

FILE(GLOB libLabSrc lib/*.cpp)
add_library(LabParadigma ${libLabSrc} )

FILE(GLOB LabSources ${CES12_SRC}/*.cpp)
add_executable(labTrocotests test/testTroco.cpp ${LabSources} )
add_executable(labSSPtests test/testSSP.cpp ${LabSources} )

ADD_LIBRARY(libParadigmaSolution STATIC IMPORTED)
SET_TARGET_PROPERTIES(libParadigmaSolution PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libsolParadigm.a )
#SET_TARGET_PROPERTIES(libParadigmaSolution PROPERTIES IMPORTED_LOCATION /home/luiz/lgm/src/ces12/libParadigm/build/libsolParadigm.a )

ADD_LIBRARY(libsolSSPDisPis STATIC IMPORTED)
SET_TARGET_PROPERTIES(libsolSSPDisPis PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libsolSSPDisPis.a )
#SET_TARGET_PROPERTIES(libsolSSPDisPis PROPERTIES IMPORTED_LOCATION /home/luiz/lgm/src/ces12/libParadigm/build/libsolSSPDisPis.a)


#link_directories(lib)
target_link_libraries(labTrocotests gtest gtest_main LabParadigma libParadigmaSolution libsolSSPDisPis)
target_link_libraries(labSSPtests gtest gtest_main LabParadigma libParadigmaSolution libsolSSPDisPis)
 
gtest_discover_tests(labTrocotests)
gtest_discover_tests(labSSPtests)




