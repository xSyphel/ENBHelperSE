cmake_minimum_required(VERSION 3.28)

# ---- Vcpkg ----
# This minimal project call helps ensure the toolchain is configured before anything else.
project(enbhelperse-build NONE)

if (DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
else ()
    message(WARNING "Environment variable VCPKG_ROOT is not set. Continuing without vcpkg.")
endif ()

# ---- Project ----

project(
    ENBHelperSE
    VERSION 3.0.1
    LANGUAGES CXX
)

# ---- Options ----

option(COPY_BUILD "Copy the build output to the Skyrim directory." OFF)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please create a separate build directory.")
endif()

# ---- Globals ----

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

# ---- Dependencies ----

find_package(CommonLibSSE CONFIG REQUIRED)

# ---- Create DLL ----

add_commonlibsse_plugin(
    ${PROJECT_NAME}
    SOURCES
        src/main.cpp
        src/functions.cpp
        src/functions.h
        src/PCH.h
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        src
)

target_precompile_headers(
    ${PROJECT_NAME}
    PRIVATE
        src/PCH.h
)

# ---- Compiler and Linker Settings ----

if (MSVC)
    # General flags for all builds
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
            /MP           # Build with Multiple Processes
            /W4           # Warning level 4
            /WX           # Treat warnings as errors
            /permissive-  # Standards conformance
            /utf-8        # Set Source and Executable character sets to UTF-8
            /sdl          # Enable Additional Security Checks
    )

    # Conformance flags
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
            /Zc:__cplusplus
            /Zc:char8_t
            /Zc:preprocessor
            /Zc:noexceptTypes
            /Zc:rvalueCast
            /Zc:strictStrings
    )

    # Release-specific flags
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
            "$<$<CONFIG:RELEASE>:/Ob3;/JMC-;/Zc:inline>"
    )

    # Linker flags
    target_link_options(
        ${PROJECT_NAME}
        PRIVATE
            /WX # Treat Linker Warnings as Errors
            "$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
            "$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF>"
    )
endif ()

# ---- Post build ----

if (COPY_BUILD)
    if (DEFINED ENV{Skyrim64Path})
        add_custom_command(
            TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "$ENV{Skyrim64Path}/Data/SKSE/Plugins/"
        )
    else ()
        message(WARNING "Environment variable Skyrim64Path is not defined. Skipping post-build copy command.")
    endif ()
endif ()
