#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>

bool enoughVowels(const std::string& input)
{
    auto count = [input](const char& vowel)
    { return std::count(input.cbegin(), input.cend(), vowel); };

    return count('a') + count('e') + count('i') + count('o') + count('u') > 2;
}

bool twins(const std::string& input)
{
    for (int i = 0; i < input.size() - 1; ++i)
    {
        if (input[i] == input[i + 1])
            return true;
    }

    return false;
}

bool noForbiddenPattern(const std::string& input)
{
    auto contains = [input](const std::string& pattern)
    { return input.find(pattern) != std::string::npos; };

    return !contains("ab") && !contains("cd") && !contains("pq") && !contains("xy");
}

bool doubleTwins(const std::string& input)
{
    for (int i = 0; i < input.size() - 3; ++i)
    {
        if (input.find(input.substr(i, 2), i + 2) != std::string::npos)
            return true;
    }

    return false;
}

bool splitTwins(const std::string& input)
{
    for (int i = 0; i < input.size() - 2; ++i)
    {
        if (input[i] == input[i + 2])
            return true;
    }

    return false;
}

int main()
{
    std::string   input;
    std::ifstream fileStream;
    fileStream.open("input.txt");

    size_t nice = 0;
    while (std::getline(fileStream, input))
    {
        if (!doubleTwins(input))
            continue;

        if (!splitTwins(input))
            continue;

        nice++;
    }

    std::cout << nice << std::endl;

    return 0;
}