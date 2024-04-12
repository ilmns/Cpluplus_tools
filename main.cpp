#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

void display_help() {
    std::cout << "Usage: copy_tool <filename> [options]\n\n"
              << "Options:\n"
              << "  --plain          Copy the content in plain text format (default).\n"
              << "  --line-numbers   Copy the content with line numbers.\n"
              << "  --html           Copy the content in HTML format.\n"
              << "  -h, --help       Display this help manual.\n\n"
              << "Examples:\n"
              << "  copy_tool example.sh --plain        Copy the content of example.sh in plain text format.\n"
              << "  copy_tool example.sh --line-numbers Copy the content of example.sh with line numbers.\n"
              << "  copy_tool example.sh --html         Copy the content of example.sh in HTML format.\n\n"
              << "Note:\n"
              << "  The --html option currently wraps the content in basic HTML tags. In future versions, it might support syntax highlighting for code files.\n"
              << "  The tool uses xclip to interact with the clipboard. Make sure xclip is installed before using the tool.\n";
}

void copy_to_clipboard(const std::string& content) {
    // Use xclip to copy the content to clipboard
    FILE* pipe = popen("xclip -selection clipboard -in", "w");
    if (!pipe) {
        std::cerr << "Error: Unable to open pipe to xclip." << std::endl;
        return;
    }
    fwrite(content.c_str(), sizeof(char), content.size(), pipe);
    pclose(pipe);
    std::cout << "The content of the file has been copied to the clipboard." << std::endl;
}

std::string get_plain_text(const std::string& content) {
    return content;
}

std::string get_text_with_line_numbers(const std::string& content) {
    std::istringstream stream(content);
    std::ostringstream result;
    std::string line;
    int line_number = 1;

    while (std::getline(stream, line)) {
        result << std::setw(4) << std::setfill(' ') << line_number << "  " << line << '\n';
        line_number++;
    }

    return result.str();
}

std::string get_html_formatted_text(const std::string& content) {
    // For now, just wrap content in basic HTML tags.
    // In a real application, you would integrate a library to handle syntax highlighting for code files.
    return "<html><body><pre>" + content + "</pre></body></html>";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Insufficient arguments. Use -h or --help to display the help manual." << std::endl;
        return 1;
    }

    if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
        display_help();
        return 0;
    }

    std::string format_flag = "--plain";
    if (argc == 3) {
        format_flag = argv[2];
        if (format_flag == "-h" || format_flag == "--help") {
            display_help();
            return 0;
        }
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    std::string formatted_content;
    if (format_flag == "--plain") {
        formatted_content = get_plain_text(content);
    } else if (format_flag == "--line-numbers") {
        formatted_content = get_text_with_line_numbers(content);
    } else if (format_flag == "--html") {
        formatted_content = get_html_formatted_text(content);
    } else {
        std::cerr << "Unknown format flag: " << format_flag << std::endl;
        return 1;
    }

    copy_to_clipboard(formatted_content);

    return 0;
}
