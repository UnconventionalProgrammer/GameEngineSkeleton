cmake_minimum_required(VERSION 3.5)
project(GameEngineSkeleton)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})


set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

set(sfml_DIR ${CMAKE_BINARY_DIR}/_deps/sfml-build/)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML"
        GIT_TAG        "3.0.1"
)
FetchContent_MakeAvailable(sfml)


FetchContent_Declare(
        sol2
        GIT_REPOSITORY "https://github.com/ThePhD/sol2"
        GIT_TAG        "v3.5.0"
)

FetchContent_MakeAvailable(sol2)



add_executable(${PROJECT_NAME} main.cpp src/Window/Window.cpp src/Window/Window.h src/Window/SFMLWindow.cpp src/Window/SFMLWindow.h src/Event.cpp src/Event.h src/Drawable/Drawable.cpp src/Drawable/Drawable.h src/Mesh.cpp src/Mesh.h src/Drawable/DrawableSprite.cpp src/Drawable/DrawableSprite.h src/Renderer/Renderer.cpp src/Renderer/Renderer.h src/Renderer/SFMLRenderer.cpp src/Renderer/SFMLRenderer.h src/Drawable/DrawableGridTerrain.cpp src/Drawable/DrawableGridTerrain.h src/GameObject.cpp src/GameObject.h src/ECS/Entity.cpp src/ECS/Entity.h src/ECS/System.cpp src/ECS/System.h Example/Pong/Pong.cpp src/Drawable/DrawableRectangle.cpp src/Drawable/DrawableRectangle.h src/ECS/SystemUpdatePositionFromVelocity.cpp src/ECS/SystemUpdatePositionFromVelocity.h)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wno-attributes)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sol2::sol2)
