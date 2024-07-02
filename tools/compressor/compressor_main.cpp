#include <miniz/miniz.hpp>
#include <args/args.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

std::string read_file_into_string(const std::string &file_name)
{
    std::ifstream ifs;

    ifs.open(file_name, std::ios::in | std::ios::binary);
    if (!ifs.is_open())
    {
        std::cerr << "Failed to open a file";
        throw std::invalid_argument("could not open the file: " + file_name);
    }
    ifs.unsetf(std::ios::skipws);

    // get its size:
    ifs.seekg(0, std::ios::end);
    const std::streampos input_size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    auto buffer = std::string();
    buffer.reserve(input_size);
    std::copy(std::istream_iterator<char>(ifs), std::istream_iterator<char>(), std::back_inserter(buffer));
    ifs.close();

    return buffer;
}

int main(int argc, char **argv)
{
    args::ArgumentParser parser("This program compresses file given as input");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::Positional<std::string> input_file(parser, "input", "input file to be compressed");
    args::Positional<std::string> output_file(parser, "output", "output file where output should be");
    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (const args::Help &)
    {
        std::cout << parser;
        return 0;
    }
    catch (const args::ParseError &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return EXIT_FAILURE;
    }

    if (!input_file)
    {
        std::cerr << "no input file specified" << std::endl;
        std::cerr << parser;
        return EXIT_FAILURE;
    }
    if (!output_file)
    {
        std::cerr << "no output file specified" << std::endl;
        std::cerr << parser;
        return EXIT_FAILURE;
    }
    auto input_path = args::get(input_file);
    auto output_path = args::get(output_file);

    if (std::filesystem::exists(output_path))
    {
        std::filesystem::remove(output_path);
    }

    auto input_data = read_file_into_string(input_path);
    auto compress_length = compressBound(input_data.size());
    std::vector<unsigned char> compress_data;
    compress_data.reserve(compress_length);
    auto compress_status = compress(compress_data.data(), &compress_length, (const unsigned char *)input_data.data(), input_data.size());
    if (compress_status != Z_OK)
    {
        std::cerr << "compress() failed" << std::endl;
        return EXIT_FAILURE;
    }
    std::fstream ofs;
    ofs.open(output_path, std::ios::out | std::ios::binary);
    ofs.write((const char *)compress_data.data(), compress_length);
    ofs.close();

    return 0;
}