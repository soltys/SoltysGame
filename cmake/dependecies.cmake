
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)

FetchContent_Declare(embed_resource
    GIT_REPOSITORY https://github.com/soltys/embed_resource.git
    GIT_TAG 0.2.2
)    

FetchContent_Declare(packer
    GIT_REPOSITORY https://github.com/soltys/packer.git
    GIT_TAG b7cebce9743634e5e6088b119f5ec462a780d1da
)

set(SQLITECPP_RUN_CPPLINT OFF CACHE BOOL "" FORCE)
set(SQLITECPP_RUN_CPPCHECK OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG        3.3.1
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(SFML SQLiteCpp embed_resource packer)