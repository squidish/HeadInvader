# CMakeList.txt : CMake project for HeadInvader, include source and define
# project specific logic here.
#

set(CMAKE_CXX_STANDARD 17)

# Add source to this project's executable.
add_executable (HeadInvader "main.cpp" "HeadInvaderGame.cpp"  "Head.cpp" "MusicManager.cpp" "MusicManager.h")

#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET HeadInvader PROPERTY CXX_STANDARD 20)
#endif()

#find package
#set(SFML_STATIC_LIBRARIES ON)
#set(SFML_DIR "C:/SFML-3.0.0/lib/cmake/SFML/")
set("C:/Program Files (x86)/SFML/lib/")
#find_package(SFML COMPONENTS Graphics System Window)

#find_package(SFML 3.0.0 EXACT REQUIRED COMPONENTS Graphics Window System REQUIRED)
find_package(SFML 3 COMPONENTS Audio Graphics Window System REQUIRED)

message(STATUS "SFML include directory: ${SFML_GRAPHICS_FOUND}")
message(STATUS "SFML libraries: ${FIND_SFML_PATHS}")
target_link_libraries(HeadInvader  SFML::Graphics  SFML::Audio SFML::Window SFML::System)
#target_link_libraries(HeadInvader  SFML::Graphics SFML::Window SFML::Audio)
# TODO: Add tests and install targets if needed.

