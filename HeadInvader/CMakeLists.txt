# CMakeList.txt : CMake project for HeadInvader, include source and define
# project specific logic here.
#

set(CMAKE_CXX_STANDARD 17)

# Add source to this project's executable.
add_executable (HeadInvader "main.cpp" "HeadInvaderGame.cpp"  "Head.cpp")

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET HeadInvader PROPERTY CXX_STANDARD 20)
#endif()

#find package
set(SFML_DIR "C:/SFML-3.0.0/lib/cmake/SFML/")
#find_package(SFML COMPONENTS Graphics System Window)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 3.0.0 EXACT REQUIRED COMPONENTS Graphics System Window REQUIRED)


message(STATUS "SFML include directory: ${SFML_GRAPHICS_FOUND}")
message(STATUS "SFML libraries: ${FIND_SFML_PATHS}")
target_link_libraries(HeadInvader SFML::System SFML::Graphics SFML::Window )

# TODO: Add tests and install targets if needed.
