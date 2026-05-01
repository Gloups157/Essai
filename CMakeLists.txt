cmake_minimum_required(VERSION 4.0)
project(Essai)

set(CMAKE_CXX_STANDARD 17)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Stb REQUIRED)

include_directories(Essai PRIVATE include)

add_executable(Essai src/main.cpp
        src/engine/renderer/Shader.cpp
        include/engine/renderer/Shader.h
        src/engine/renderer/Texture.cpp
        include/engine/renderer/Texture.h
        src/engine/core/Engine.cpp
        include/engine/core/Engine.h
        src/engine/core/Camera.cpp
        include/engine/core/Camera.h
        include/engine/window/AWindow.h
        include/engine/input/AInput.h
        src/engine/time/ATime.cpp
        include/engine/time/ATime.h
        include/engine/input/EKey.h
        include/engine/input/InputInfo.h
        include/engine/input/EInputState.h
        include/engine/input/EMouseButton.h
        src/engine/window/glfw/GLFWWindow.cpp
        include/engine/window/glfw/GLFWWindow.h
        include/engine/window/WindowSettings.h
        src/engine/input/glfw/GLFWInput.cpp
        include/engine/input/glfw/GLFWInput.h
        include/engine/core/EngineContext.h
        include/engine/window/EWindowBackend.h
        include/engine/window/WindowFactory.h
        include/engine/input/InputFactory.h
        include/engine/ecs/components/Meta.h
        include/engine/ecs/core/ComponentSparseSet.h
        include/engine/ecs/components/Transform.h
        include/engine/ecs/core/IComponentSparseSet.h
        include/engine/ecs/core/ILifeCycle.h
        include/engine/ecs/core/ECSTypes.h
        src/engine/ecs/core/SystemManager.cpp
        include/engine/ecs/core/SystemManager.h
        src/engine/ecs/core/EntityManager.cpp
        include/engine/ecs/core/EntityManager.h
        include/engine/ecs/core/ASystem.h
        src/engine/ecs/core/ASystem.cpp
        src/engine/ecs/core/World.cpp
        include/engine/ecs/core/World.h
        src/engine/ecs/core/Universe.cpp
        include/engine/ecs/core/Universe.h
        src/engine/ecs/core/Query.cpp
        include/engine/ecs/core/Query.h
        src/engine/ecs/systems/MovementSystem.cpp
        include/engine/ecs/systems/MovementSystem.h
        src/engine/renderer/ARenderer.cpp
        include/engine/renderer/ARenderer.h
        src/engine/renderer/opengl/OpenGLRenderer.cpp
        include/engine/renderer/opengl/OpenGLRenderer.h
        src/engine/time/glfw/GLFWTime.cpp
        include/engine/time/glfw/GLFWTime.h
        src/engine/time/TimeFactory.cpp
        include/engine/time/TimeFactory.h
        include/engine/renderer/opengl/OpenGLCore.h
        include/engine/renderer/ERendererBackend.h
        include/engine/renderer/RendererFactory.h
        src/engine/input/AInput.cpp
        include/engine/ecs/components/View.h
        src/application/core/Application.cpp
        include/application/core/Application.h
        src/application/core/ApplicationLayer.cpp
        include/application/core/ApplicationLayer.h
        "src/core/utilities/patterns/statemachine/StateMachine.cpp"
        "include/core/utilities/patterns/statemachine/StateMachine.h"
        "src/core/utilities/patterns/statemachine/ITransition.cpp"
        "include/core/utilities/patterns/statemachine/ITransition.h"
        "src/core/utilities/patterns/statemachine/StateNode.cpp"
        "include/core/utilities/patterns/statemachine/StateNode.h"
        "src/core/utilities/patterns/statemachine/IState.cpp"
        "include/core/utilities/patterns/statemachine/IState.h"
        include/core/utilities/containers/TypeVector.h
        src/engine/renderer/RendererSystem.cpp
        include/engine/renderer/RendererSystem.h
        include/engine/ecs/components/Renderer2D.h
        include/core/Types.h
        src/core/utilities/helpers/AActivable.cpp
        include/core/utilities/helpers/AActivable.h
        src/engine/renderer/opengl/OpenGLTextureLibrary.cpp
        include/engine/renderer/opengl/OpenGLTextureLibrary.h
)

target_link_libraries(Essai PRIVATE glad::glad PRIVATE glfw)
