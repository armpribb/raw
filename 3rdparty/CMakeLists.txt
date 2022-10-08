include(FetchContent)

FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG c74846a891b3cc3bfa992d588b1295f528d43039 # v3.0.0
)

FetchContent_Declare(
    nowide
    GIT_REPOSITORY https://github.com/boostorg/nowide.git
    GIT_TAG 02f40f0b5f5686627fcddae93ff88ca399db4766 # standalone
)

FetchContent_MakeAvailable(cxxopts nowide)

custom_target_sanitize_options(nowide)
custom_target_debug_options(nowide)

if(LIN OR MAC)
    FetchContent_Declare(
        clip
        GIT_REPOSITORY https://github.com/dacap/clip.git
        GIT_TAG 2ada8b17b39bf41a669248a2be5c6e4be4c27f14 # v1.5
    )

    set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
    set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")
    set(CLIP_X11_WITH_PNG OFF CACHE BOOL "Compile clip X11 with PNG")
    FetchContent_MakeAvailable(clip)

    custom_target_sanitize_options(clip)
    custom_target_debug_options(clip)
endif()

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 58d77fa8070e8cec2dc1ed015d66b454c8d78850 # v1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

custom_target_sanitize_options(gtest_main)
custom_target_debug_options(gtest_main)

