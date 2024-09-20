
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0-rc.1
    GIT_SHALLOW 1
)

FetchContent_Declare(packer
    GIT_REPOSITORY https://github.com/soltys/packer.git
    GIT_TAG 3bc5606a29ad4c944b730452e74ee91685e7a267
    GIT_SHALLOW 1
)

set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG        3.3.1
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(SFML SQLiteCpp packer)