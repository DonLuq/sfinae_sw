#include <iostream>
#include <fstream>
#include <string>

void replace_template_parameter(std::string &line, size_t &enable_if_start, std::ofstream &output)
{
    size_t template_start = line.find("template");
    std::cout << "DEBUG I\n";
    size_t v_start = line.find_first_of("<", enable_if_start) + 1; // 1 -> "<"
    size_t v_stop = line.find_first_of(">", v_start);
    output << line.substr(0, enable_if_start - 11) + ">"; // 11 -> length of ", typename "  <--- make it more common
    output << "\nrequires " << line.substr(v_start, v_stop - v_start + 1)
           << "\n";
};

void replace_return_parameter(std::string &line, std::string &next_line, size_t &enable_if_start, std::ofstream &output)
{
    std::cout << "DEBUG II\n";
    // std::string old_line = line;
    size_t v_start = line.find_first_of("<", enable_if_start) + 1; // 1 -> "<"
    size_t v_stop = line.find_first_of(">", v_start);

    size_t typename_name_s = line.find("<", v_start) + 1;
    size_t typename_name_e = line.find(">", v_start);

    output << line.substr(typename_name_s, typename_name_e - typename_name_s) + " " + next_line + " requires(" + line.substr(v_start, v_stop - v_start + 1) + ")" << std::endl;
};

void replace_class_parameter(std::string &line, size_t &enable_if_start, std::ofstream &output)
{
    std::cout << "DEBUG III\n";
    size_t v_start = line.find_first_of("<", enable_if_start) + 1; // 1 -> "<"
    size_t v_stop = line.find_first_of(">", v_start);

    output << "requires " + line.substr(v_start, v_stop - v_start + 1) << std::endl;
    output << line.substr(0, enable_if_start - 11) + ">" << std::endl; // temp solution to rewrite to not use constants
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Failed to open input file: " << argv[1] << "\n";
        return 1;
    }

    std::ofstream output(argv[2]);
    if (!output.is_open())
    {
        std::cerr << "Failed to open output file: " << argv[2] << "\n";
        return 1;
    }

    std::string line;
    while (std::getline(input, line)) // main loop over a file
    {
        size_t enable_if_start = line.find("std::enable_if");
        size_t if_return_par = line.substr(0, enable_if_start + 1).find("typename");
        size_t if_class = line.find("class"); // dodac helper remove whitespaces
        if (enable_if_start != std::string::npos)
        {
            size_t template_start = line.find("template");
            if (template_start != std::string::npos)
            {
                replace_template_parameter(line, enable_if_start, output);
            }
            else if (enable_if_start == 0 || if_return_par == 0)
            {
                std::string next_line;
                std::getline(input, next_line);
                replace_return_parameter(line, next_line, enable_if_start, output);
            }
            else if (if_class == 0) // CLASS PARAMETER
            {
                replace_class_parameter(line, enable_if_start, output);
            }
            else if (0) // FUNCTION PARAMETER
            {
                std::cout << "DEBUG IV\n";
            }
            else
            {
                std::cout << "This example of enable_if substitution is not supported yet";
            }
        }
        else
        {
            // implamented two other options where eneable_if could be used
            output << line << "\n";
        }
    }

    std::cout << "Conversion successful.\n";
    return 0;
}
