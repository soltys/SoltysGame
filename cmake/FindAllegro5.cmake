find_library(ALLEGRO_LIBRARY
    NAMES allegro    
)
find_file(ALLEGRO_SHARED_LIBRARY
    NAMES allegro-5.2.dll
    PATHS "$ENV{VCPKG_ROOT}/installed/$ENV{VCPKG_DEFAULT_TRIPLET}/bin"
)
find_path(ALLEGRO_INCLUDE_DIR
    NAMES allegro5
)