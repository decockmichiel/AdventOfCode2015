#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>

int main()
{
    std::string   input;
    std::ifstream fileStream;
    fileStream.open("input.txt");
    std::getline(fileStream, input);

    struct Location
    {
        int x = 0;
        int y = 0;
    };

    auto comparator = [](const Location& left, const Location& right)
    {
        if (left.x == right.x)
            return left.y < right.y;
        return left.x < right.x;
    };

    std::set<Location, decltype(comparator)> houses(comparator);

    Location current;
    for (const auto& direction : input)
    {
        if (direction == '>')
            current.x++;
        else if (direction == '<')
            current.x--;
        else if (direction == '^')
            current.y++;
        else if (direction == 'v')
            current.y--;

        houses.insert(current);
    }

    std::cout << houses.size() << std::endl;

    return 0;
}