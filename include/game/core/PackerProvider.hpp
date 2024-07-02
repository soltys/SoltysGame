#include <filesystem>

int tinfl_write_into_ofstream(const void *pBuf, int len, void *pUser);
void remove_packer_if_exists(const std::filesystem::path packer_path);
std::filesystem::path get_packer_path();
void extract_packer_from_executable(const std::filesystem::path packer_path);