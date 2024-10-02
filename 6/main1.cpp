#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
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

struct Point
{
    int row = 0;
    int col = 0;
};

using Corners = std::array<Point, 2>;

enum class Operation
{
    on,
    off,
    toggle,
};

const size_t size = 1000;

using Lights = std::vector<std::vector<bool>>;

void updateLights(const Corners& corners, Operation operation, Lights& lights)
{
    const auto topLeft = corners[0];
    const auto bottomRight = corners[1];

    for (int row = topLeft.row; row <= bottomRight.row; ++row)
    {
        for (int col = topLeft.col; col <= bottomRight.col; ++col)
        {
            switch (operation)
            {
            case Operation::on:
                lights[row][col] = true;
                break;
            case Operation::off:
                lights[row][col] = false;
                break;
            case Operation::toggle:
                lights[row][col] = !lights[row][col];
                break;
            }
        }
    }
}

int main()
{
    std::vector<bool> row(size, false);
    Lights            lights(size, row);

    const auto lines = readFile("input.txt", {});

    for (const auto& line : lines)
    {
        const auto chuncks = splitLine(line, {' '});

        Corners   corners;
        int       corner = 0;
        Operation operation;
        for (const auto& chunk : chuncks)
        {
            if (chunk == "turn")
                continue;

            if (chunk == "through")
            {
                corner++;
                continue;
            }

            if (chunk == "on")
            {
                operation = Operation::on;
                continue;
            }

            if (chunk == "off")
            {
                operation = Operation::off;
                continue;
            }

            if (chunk == "toggle")
            {
                operation = Operation::toggle;
                continue;
            }

            const auto coords = splitLine(chunk, {','});
            corners[corner].row = std::stoi(coords.front());
            corners[corner].col = std::stoi(coords.back());
        }

        updateLights(corners, operation, lights);
    }

    int lightsOn = 0;
    for (int row = 0; row != size; ++row)
    {
        for (int col = 0; col != size; ++col)
        {
            if (lights[row][col])
                lightsOn++;
        }
    }

    std::cout << lightsOn << std::endl;

    return 0;
}