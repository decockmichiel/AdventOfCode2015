#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <regex>
#include <set>
#include <sstream>

std::vector<std::string> splitLine(const std::string& line, const std::vector<char>& delimiters)
{
    std::stringstream sstream(line);
    std::string       chunk;

    std::vector<std::string> chunks;

    while (std::getline(sstream, chunk, delimiters.front()))
    {
        if (chunk.empty())
            continue;

        if (delimiters.size() <= 1)
        {
            chunks.push_back(chunk);
            continue;
        }

        const std::vector<char> otherDelimiters(delimiters.cbegin() + 1, delimiters.cend());

        const auto subChunks = splitLine(chunk, otherDelimiters);
        chunks.insert(chunks.end(), subChunks.cbegin(), subChunks.cend());
    }

    return chunks;
}

std::vector<std::string> readFile(const char* fileName, const std::vector<char>& delimiters)
{
    std::vector<std::string> lines;

    std::fstream fstream;
    fstream.open(fileName);

    std::string line;
    while (std::getline(fstream, line))
    {
        if (line.empty())
            continue;

        if (delimiters.empty())
        {
            lines.push_back(line);
            continue;
        }

        const auto chunks = splitLine(line, delimiters);
        lines.insert(lines.end(), chunks.begin(), chunks.end());
    }

    return lines;
}

int main()
{
    const auto lines = readFile("input.txt", {});

    size_t codeCount = 0;
    size_t memoryCount = 0;

    for (const auto& line : lines)
    {
        codeCount += line.size();

        const std::regex regex("\\\\{2}|\\\\\\\"|\\\\x[0-9a-fA-F]{2}");
        memoryCount += std::regex_replace(line, regex, "#").size() - 2;
    }

    std::cout << codeCount - memoryCount << std::endl;

    return 0;
}