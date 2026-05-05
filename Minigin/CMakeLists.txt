set(ENGINE_NAME minigin)

set(MINIGIN_SOURCE_FILES
        Minigin/src/Audio/AudioQueue.cpp
        Minigin/src/Audio/ConcurrentAudioQueue.cpp
        Minigin/src/Audio/SdlSoundSystem.cpp
        Minigin/src/Component/ColliderComponent.cpp
        Minigin/src/Component/GameComponent.cpp
        Minigin/src/Component/TextComponent.cpp
        Minigin/src/Component/TextureComponent.cpp
        Minigin/src/Event/EventManager.cpp
        Minigin/src/Event/EventRingBuffer.cpp
        Minigin/src/Input/InputManager.cpp
        Minigin/src/Input/KeyboardInput.cpp
        Minigin/src/Render/Font.cpp
        Minigin/src/Render/GuiWindow.cpp
        Minigin/src/Render/Renderer.cpp
        Minigin/src/Render/ResourceManager.cpp
        Minigin/src/Render/Texture2D.cpp
        Minigin/src/GameObject.cpp
        Minigin/src/Minigin.cpp
        Minigin/src/PhysicsSystem.cpp
        Minigin/src/Scene.cpp
        Minigin/src/SceneManager.cpp
        Minigin/src/ServiceLocator.cpp
        Minigin/src/Time.cpp
        Minigin/src/Transform.cpp
)

# Platform specific source files
if (WIN32)
    set(MINIGIN_SOURCE_FILES ${MINIGIN_SOURCE_FILES} Minigin/src/Input/ControllerInputXInput.cpp)
else()
    set(MINIGIN_SOURCE_FILES ${MINIGIN_SOURCE_FILES} Minigin/src/Input/ControllerInputSdl.cpp)
endif()

add_library(${ENGINE_NAME}
        ${MINIGIN_SOURCE_FILES}
)

# Add both public includes and private ones (but dont directly include private so we still have to prefix it with "private/")
target_include_directories(${ENGINE_NAME} PUBLIC Minigin/include Minigin)
target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_20)

target_include_directories("${ENGINE_NAME}" PUBLIC
        ${glm_SOURCE_DIR}
        ${sdl3_SOURCE_DIR}/include
        ${sdl3_image_SOURCE_DIR}/include
        ${sdl3_ttf_SOURCE_DIR}/include
        ${imgui_SOURCE_DIR}
        ${implot_SOURCE_DIR}
        ${json_SOURCE_DIR}/include
        ${VLD_INCLUDE_DIR}
)

target_link_libraries("${ENGINE_NAME}" PUBLIC
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
        glm::glm
        imgui
        implot
        nlohmann_json::nlohmann_json
        ${VLD_LIBRARIES}
)

if(MSVC)
    # compile at warning level 4 + treat warnings as errors
    target_compile_options(${ENGINE_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${ENGINE_NAME} PRIVATE -Wall -Wextra -Werror)
endif()


