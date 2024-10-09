#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
#include <regex>
#include <set>
#include <sstream>

using Strings = std::vector<std::string>;

Strings splitLine(const std::string& line, const std::vector<char>& delimiters)
{
    std::stringstream sstream(line);
    std::string       chunk;

    Strings chunks;

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

Strings readFile(const char* fileName, const std::vector<char>& delimiters)
{
    Strings lines;

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

std::string transform(const std::string& sequence)
{
    char   currentDigit = 0; // which is not a digit
    size_t count = 0;

    std::string output;

    auto flush = [&currentDigit, &count, &output]()
    {
        if (count != 0)
            output += std::to_string(count) + currentDigit;
    };

    for (const auto& digit : sequence)
    {
        if (digit != currentDigit)
        {
            flush();

            currentDigit = digit;
            count = 1;
        }
        else
            count++;
    }

    flush();

    return output;
}

int main()
{
    const size_t iterations = 50;
    std::string  sequence = "1113122113";

    for (size_t it = 0; it != iterations; ++it)
    {
        sequence = transform(sequence);
    }

    std::cout << sequence.size() << std::endl;

    return 0;
}
