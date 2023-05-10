#include <iostream>
#include <fstream>
#include <string>
#include <regex>

void replace_template_parameter(std::string &line, size_t &enable_if_start, std::ofstream &output)
{
    const std::string template_keyword = "template";
    size_t template_start = line.find(template_keyword);

    if (template_start == std::string::npos)
    {
        return; // early exit if "template" not found
    }

    std::cout << "DEBUG I\n";

    std::string line_copy = line;
    std::regex pattern_typename("typename\\s+([a-zA-Z0-9_]+),");
    std::smatch matches_typename;

    if (std::regex_search(line_copy, matches_typename, pattern_typename))
    {
        std::string result = "template <typename " + matches_typename[1].str() + ">";
        output << result << std::endl; // Output: template <typename T>
    }

    std::regex pattern_enable_if(R"(std::enable_if(?:_t)?<(.+?>))");
    std::smatch matches;

    while (std::regex_search(line, matches, pattern_enable_if))
    {
        output << "requires " << matches[1] << std::endl;
        line = matches.suffix();
    }
}

void replace_return_parameter(const std::string &line, const std::string &next_line, const size_t enable_if_start, std::ofstream &output)
{
    std::cout << "DEBUG II\n";

    const std::string open_bracket = "<";
    const std::string close_bracket = ">";

    const size_t v_start = line.find_first_of(open_bracket, enable_if_start) + 1;
    const size_t v_stop = line.find_first_of(close_bracket, v_start);

    const size_t typename_name_start = line.find(open_bracket, v_start) + 1;
    const size_t typename_name_end = line.find(close_bracket, v_start);

    const std::string typename_name = line.substr(typename_name_start, typename_name_end - typename_name_start);

    output << typename_name << " " << next_line << " requires(" << line.substr(v_start, v_stop - v_start + 1) << ")" << std::endl;
}

void replace_class_parameter(std::string &line, const size_t enable_if_start, std::ofstream &output)
{
    std::cout << "DEBUG III\n";

    const std::string open_bracket = "<";
    const std::string close_bracket = ">";

    const size_t v_start = line.find_first_of(open_bracket, enable_if_start) + 1;
    const size_t v_stop = line.find_first_of(close_bracket, v_start);

    const std::string requires_clause = "requires " + line.substr(v_start, v_stop - v_start + 1) + "\n";
    const std::string template_declaration = line.substr(0, enable_if_start - 11) + ">\n"; // 11 -> length of ", typename "  <--- make it more common

    output << requires_clause << template_declaration;
}

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
        size_t if_class = line.find("class");

        if (enable_if_start != std::string::npos)
        {
            if (const size_t template_start = line.find("template"); template_start != std::string::npos)
            {
                replace_template_parameter(line, enable_if_start, output);
            }
            else if (enable_if_start == 0 || if_return_par == 0)
            {
                std::string next_line;
                std::getline(input, next_line);
                replace_return_parameter(line, next_line, enable_if_start, output);
            }
            else if (if_class == 0)
            {
                replace_class_parameter(line, enable_if_start, output);
            }
            else if (0) // FUNCTION PARAMETER
            {
                std::cout << "DEBUG IV\n";
            }
            else
            {
                std::cout << "This example of enable_if substitution is not supported yet\n";
            }
        }
        else
        {
            output << line << "\n";
        }
    }

    std::cout << "Conversion successful.\n";
    return 0;
}
