#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

std::pair<bool, std::string> reverseFileLines(const std::string& input_filepath, const std::string& output_filepath) {
    // Attempt to open input file
    std::ifstream input_file(input_filepath);
    if (!input_file.is_open()) {
        return {false, "Failed to open input file"};
    }

    // Read and process lines
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input_file, line)) {
        lines.push_back(line);
    }
    input_file.close();
    std::reverse(lines.begin(), lines.end());

    // Attempt to open output file
    std::ofstream output_file(output_filepath);
    if (!output_file.is_open()) {
        return {false, "Failed to open output file"};
    }

    // Write reversed lines
    for (const auto& l : lines) {
        output_file << l << '\n';  // Preserves original line endings
    }
    output_file.close();

    return {true, ""};  // Indicate success
}

int main() {
    auto result = reverseFileLines("input.txt", "output.txt");
    if (!result.first) {
        std::cerr << result.second << std::endl;
    } else {
        std::cout << "File lines reversed successfully." << std::endl;
    }
    return 0;
}



