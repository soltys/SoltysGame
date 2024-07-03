#include <args/args.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

int main(int argc, char **argv)
{
    args::ArgumentParser parser("This program merges multiple JSON pack.json into one");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<std::string> output_file(parser, "output", "Output file where merged json should be", {'o'}, args::Options::Required);
    args::PositionalList<std::string> files(parser, "files", "JSON files to be merged", args::Options::Required);

    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (const args::Help &)
    {
        std::cout << parser;
        return 0;
    }
    catch (const args::ParseError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return EXIT_FAILURE;
    }
    catch (args::ValidationError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return EXIT_FAILURE;
    }

    auto file_list = args::get(files);
    auto output_path = args::get(output_file);

    if (std::filesystem::exists(output_path))
    {
        std::filesystem::remove(output_path);
    }

    return 0;
}