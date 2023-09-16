```markdown
# File to Clipboard Copier

A simple and user-friendly command-line tool developed in C++ to copy the contents of a file to the clipboard in various formats including plain text, with line numbers, or as HTML. This tool is particularly designed for Linux systems and utilizes `xclip` for clipboard interactions.

## Installation

Before using this tool, ensure that `xclip` is installed on your system. You can install it using the following command:

```sh
sudo pacman -S xclip
```

To compile the program, navigate to the directory containing the source file (`copy_tool.cpp`) and use the following command:

```sh
g++ -o copy_tool copy_tool.cpp
```

## Usage

To use the program, run it using the following syntax:

```sh
./copy_tool <filename> [options]
```

### Options

- `--plain`: Copy the content in plain text format (default).
- `--line-numbers`: Copy the content with line numbers.
- `--html`: Copy the content in HTML format.
- `-h`, `--help`: Display the help manual with usage instructions.

### Examples

```sh
./copy_tool example.sh --plain
```
This command copies the content of `example.sh` in plain text format to the clipboard.

```sh
./copy_tool example.sh --line-numbers
```
This command copies the content of `example.sh` with line numbers to the clipboard.

```sh
./copy_tool example.sh --html
```
This command copies the content of `example.sh` in HTML format to the clipboard.

## Note

- The `--html` option currently wraps the content in basic HTML tags. Future versions may support syntax highlighting for code files.
- The tool uses `xclip` to interact with the clipboard. Ensure `xclip` is installed before using the tool.

## License

This project is open source and available under the [MIT License](LICENSE).

## Contributing

Contributions, issues, and feature requests are welcome! Feel free to check [issues page](https://github.com/your_repo/issues).
```
```

You can copy the content between the backticks and use it as your README.md file. Please replace `your_repo` with the actual repository name and update the license link as necessary.

