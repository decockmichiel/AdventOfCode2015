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

Strings getCities(const Strings& lines)
{
    Strings cities;

    for (const auto& line : lines)
    {
        const auto chunks = splitLine(line, {' '});

        for (const auto& chunk : chunks)
        {
            try
            {
                if (chunk == "to" || chunk == "=" || std::stoi(chunk))
                    continue;
            }
            catch (std::invalid_argument&)
            {
            }

            if (auto it = std::find(cities.cbegin(), cities.cend(), chunk); it != cities.cend())
                continue;

            cities.push_back(chunk);
        }
    }

    return cities;
}

using Distances = std::vector<std::vector<int>>;

void print(const Distances& distances)
{
    for (int row = 0; row != distances.size(); ++row)
    {
        for (int col = 0; col != distances.size(); ++col)
        {
            std::cout << distances[row][col] << "\t\t";
        }
        std::cout << std::endl;
    }
}

Distances readDistances(const Strings& lines)
{
    const auto cities = getCities(lines);

    Distances distances(cities.size(), std::vector<int>(cities.size(), 0));

    for (const auto& line : lines)
    {
        const auto chunks = splitLine(line, {' '});

        std::vector<int> locations;

        for (const auto& chunk : chunks)
        {
            if (chunk == "to" || chunk == "=")
                continue;

            try
            {
                const auto distance = std::stoi(chunk);
                distances[locations.front()][locations.back()] = distance;
                distances[locations.back()][locations.front()] = distance;
            }
            catch (std::invalid_argument&)
            {
            }

            locations.push_back(
                std::distance(cities.cbegin(), std::find(cities.cbegin(), cities.cend(), chunk)));
        }
    }

    return distances;
}

int getDistance(const Distances& distances, const std::vector<int>& cities)
{
    const auto numberOfCities = cities.size();

    int distance = 0;

    for (int city = 1; city != numberOfCities; ++city)
    {
        distance += distances[cities[city - 1]][cities[city]];
    }

    return distance;
}

int findLongestRoute(int                     maxDistance,
                     const std::vector<int>& visitedCities,
                     const Distances&        distances)
{
    const auto numberOfCities = distances.size();

    for (int city = 0; city != numberOfCities; ++city)
    {
        if (std::find(visitedCities.cbegin(), visitedCities.cend(), city) != visitedCities.cend())
            continue;

        std::vector<int> cities = visitedCities;
        cities.push_back(city);

        if (visitedCities.size() == numberOfCities - 1)
            maxDistance = std::max(maxDistance, getDistance(distances, cities));
        else

            maxDistance = std::max(maxDistance, findLongestRoute(maxDistance, cities, distances));
    }

    return maxDistance;
}

int main()
{
    const auto lines = readFile("input.txt", {});
    const auto distances = readDistances(lines);

    int maxDistance = findLongestRoute(0, {}, distances);

    // print(distances);
    std::cout << maxDistance << std::endl;

    return 0;
}
