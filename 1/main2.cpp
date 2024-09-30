#include <fstream>
#include <iostream>

int main()
{
    std::string   input;
    std::ifstream fileStream;
    fileStream.open("input.txt");
    std::getline(fileStream, input);

    int floor = 0;
    for (auto it = input.cbegin(); it != input.cend(); ++it)
    {
        if (*it == '(')
            floor++;
        else if (*it == ')')
            floor--;

        if (floor != -1)
            continue;

        std::cout << std::distance(input.cbegin(), it) + 1 << std::endl;
        break;
    }

    return 0;
}