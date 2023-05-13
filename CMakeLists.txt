cmake_minimum_required(VERSION 3.20)
project(GameEngineSkeleton)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})


set(CMAKE_CXX_STANDARD 20)


if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif()


include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES fmt/9.1.0 sfml/2.5.1 sol2/3.3.0
        GENERATORS CMakeDeps)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})



add_executable(${PROJECT_NAME} main.cpp src/Window/Window.cpp src/Window/Window.h src/Window/SFMLWindow.cpp src/Window/SFMLWindow.h src/Event.cpp src/Event.h src/Drawable/Drawable.cpp src/Drawable/Drawable.h src/Mesh.cpp src/Mesh.h src/Drawable/DrawableSprite.cpp src/Drawable/DrawableSprite.h src/Renderer/Renderer.cpp src/Renderer/Renderer.h src/Renderer/SFMLRenderer.cpp src/Renderer/SFMLRenderer.h src/Drawable/DrawableGridTerrain.cpp src/Drawable/DrawableGridTerrain.h src/GameObject.cpp src/GameObject.h src/ECS/Entity.cpp src/ECS/Entity.h src/ECS/System.cpp src/ECS/System.h Example/Pong/Pong.cpp src/Drawable/DrawableRectangle.cpp src/Drawable/DrawableRectangle.h src/ECS/SystemUpdatePositionFromVelocity.cpp src/ECS/SystemUpdatePositionFromVelocity.h)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wno-attributes)

find_package(fmt)
if(fmt_FOUND)
    MESSAGE(STATUS "FMT Found\n")
    include_directories(${fmt_INCLUDE_DIR})
    target_link_libraries (${PROJECT_NAME} ${fmt_LIBRARIES})
else()
    MESSAGE(FATAL_ERROR "FMT NOT FOUND")
endif()

find_package(sfml)
if(sfml_FOUND)
    MESSAGE(STATUS "SFML Found\n")
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries (${PROJECT_NAME} ${SFML_LIBRARIES})
else()
    MESSAGE(FATAL_ERROR "SFML NOT FOUND")
endif()


find_package(sol2)
if(sol2_FOUND)
    MESSAGE(STATUS "SOL2 Found\n")
    include_directories(${sol2_INCLUDE_DIR})
    target_link_libraries (${PROJECT_NAME} ${sol2_LIBRARIES})
else()
    MESSAGE(FATAL_ERROR "SOL2 NOT FOUND")
endif()


target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
