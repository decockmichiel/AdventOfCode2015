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

    Location santa;
    Location robot;

    for (auto it = input.cbegin(); it != input.cend(); ++it)
    {
        auto move = [](Location& location, const char& direction)
        {
            if (direction == '>')
                location.x++;
            else if (direction == '<')
                location.x--;
            else if (direction == '^')
                location.y++;
            else if (direction == 'v')
                location.y--;
        };

        move(santa, *it);
        houses.insert(santa);

        ++it;
        move(robot, *it);
        houses.insert(robot);
    }

    std::cout << houses.size() << std::endl;

    return 0;
}