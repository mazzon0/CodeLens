add_executable(CodeLens
    "main.cpp"
    "Editor/Editor.cpp"
    "UI/UI.cpp"
    "Platform/Windows/WinWindow.cpp"
    "Platform/Windows/WinPlatform.cpp")

target_include_directories(CodeLens PUBLIC
    "."
    "../ext/volk")
#target_link_libraries(CodeLens PUBLIC volk)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
# TODO
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# TODO
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(CodeLens PUBLIC LP_WINDOWS)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(CodeLens PUBLIC LP_APPLE)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(CodeLens PUBLIC LP_LINUX)
endif()