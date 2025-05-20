# CMakeList.txt : CMake project for HeadInvader, include source and define
# project specific logic here.
#

set(CMAKE_CXX_STANDARD 17)

# Add source to this project's executable.
add_executable (HeadInvader "main.cpp" "HeadInvaderGame.cpp"  "StandardHead.cpp" "HeadBase.h" "MusicManager.cpp" "MusicManager.h" "Bullet.h")

#find package
set("C:/Program Files (x86)/SFML/lib/")
find_package(SFML 3 COMPONENTS Audio Graphics Window System REQUIRED)

message(STATUS "SFML include directory: ${SFML_GRAPHICS_FOUND}")
message(STATUS "SFML libraries: ${FIND_SFML_PATHS}")
target_link_libraries(HeadInvader  SFML::Graphics  SFML::Audio SFML::Window SFML::System)

# TODO: Add tests and install targets if needed.
file(COPY ${CMAKE_SOURCE_DIR}/HeadInvader/Heads DESTINATION ${CMAKE_BINARY_DIR}/HeadInvader/)
file(COPY ${CMAKE_SOURCE_DIR}/HeadInvader/Sounds DESTINATION ${CMAKE_BINARY_DIR}/HeadInvader/)
file(COPY ${CMAKE_SOURCE_DIR}/HeadInvader/arialceb.ttf DESTINATION ${CMAKE_BINARY_DIR}/HeadInvader/)


