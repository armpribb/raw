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

if(UNIX)
    FetchContent_Declare(
        clip
        GIT_REPOSITORY https://github.com/dacap/clip.git
        GIT_TAG a65a9e543e9a270bb7c58789d15d027bbd8efb2a
    )

    set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
    set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")
    set(CLIP_X11_WITH_PNG OFF CACHE BOOL "Compile clip X11 with PNG")
    FetchContent_MakeAvailable(clip)
endif()
