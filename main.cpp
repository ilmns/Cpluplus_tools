#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
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


void copy_to_clipboard(const std::string& content, const std::string& format) {
    // Prepare a temporary file to hold the content
    std::ofstream temp_file("temp_copy_file.txt");
    if (!temp_file.is_open()) {
        std::cerr << "Could not create a temporary file!" << std::endl;
        exit(1);
    }

    // Write the content to the temporary file
    temp_file << content;
    temp_file.close();

    // Use xclip to copy the content to clipboard
    int result = system(("xclip -selection clipboard -t " + format + " -i temp_copy_file.txt").c_str());

    // Remove the temporary file
    system("rm temp_copy_file.txt");

    if (result == 0) {
        std::cout << "The content of the file has been copied to the clipboard." << std::endl;
    } else {
        std::cerr << "An error occurred while copying to the clipboard." << std::endl;
    }
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

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    std::string formatted_content;
    std::string mime_type = "text/plain";

    if (format_flag == "--plain") {
        formatted_content = get_plain_text(content);
    } else if (format_flag == "--line-numbers") {
        formatted_content = get_text_with_line_numbers(content);
    } else if (format_flag == "--html") {
        formatted_content = get_html_formatted_text(content);
        mime_type = "text/html";
    } else {
        std::cerr << "Unknown format flag: " << format_flag << std::endl;
        return 1;
    }

    copy_to_clipboard(formatted_content, mime_type);

    return 0;
}
