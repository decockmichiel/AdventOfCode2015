#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <optional>
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

enum class Operation
{
    NONE,
    AND,
    OR,
    NOT,
    LSHIFT,
    RSHIFT,
};

using Int = unsigned short;
using Wires = std::map<std::string, Int>;

Int processSignal(std::array<Int, 2> numbers, Operation operation)
{
    switch (operation)
    {
    case Operation::NONE:
        return numbers[0];
    case Operation::AND:
        return numbers[0] & numbers[1];
    case Operation::OR:
        return numbers[0] | numbers[1];
    case Operation::NOT:
        return ~numbers[0];
    case Operation::LSHIFT:
        return numbers[0] << numbers[1];
    case Operation::RSHIFT:
        return numbers[0] >> numbers[1];
    }

    return 0;
}

std::optional<Int> getNumber(const std::string& string)
{
    try
    {
        return static_cast<Int>(std::stoll(string));
    }
    catch (std::invalid_argument&)
    {
    }
    return {};
}

int main()
{
    auto lines =
        readFile("/Users/michieldecock/Software Development/Advent of Code/2015/7/input3.txt", {});
    Wires wires;

    while (!lines.empty())
    {
        for (int i = 0; i != lines.size(); ++i)
        {
            const auto& line = lines[i];
            const auto  chunks = splitLine(line, {' '});

            std::array<Int, 2> numbers;
            int                current = 0;
            Operation          operation = Operation::NONE;
            bool               activateOut = false;
            std::string        out;

            try
            {
                for (const auto& chunk : chunks)
                {
                    if (chunk == "AND")
                    {
                        operation = Operation::AND;
                        current++;
                        continue;
                    }

                    if (chunk == "OR")
                    {
                        operation = Operation::OR;
                        current++;
                        continue;
                    }

                    if (chunk == "NOT")
                    {
                        operation = Operation::NOT;
                        continue;
                    }

                    if (chunk == "LSHIFT")
                    {
                        operation = Operation::LSHIFT;
                        current++;
                        continue;
                    }

                    if (chunk == "RSHIFT")
                    {
                        operation = Operation::RSHIFT;
                        current++;
                        continue;
                    }

                    if (chunk == "->")
                    {
                        activateOut = true;
                        continue;
                    }

                    if (activateOut)
                    {
                        out = chunk;
                        break;
                    }

                    if (auto number = getNumber(chunk))
                    {
                        numbers[current] = *number;
                        continue;
                    }

                    numbers[current] = wires.at(chunk);
                }

                wires[out] = processSignal(numbers, operation);
                lines.erase(lines.cbegin() + i);
                break;
            }
            catch (std::out_of_range& e)
            {
                continue;
            }
        }
    }

    std::cout << wires["a"] << std::endl;

    return 0;
}