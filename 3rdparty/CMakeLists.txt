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
