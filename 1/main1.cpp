#include <fstream>
#include <iostream>

int main()
{
    std::string   input;
    std::ifstream fileStream;
    fileStream.open("input.txt");
    std::getline(fileStream, input);

    const auto ascend = std::count(input.cbegin(), input.cend(), '(');
    const auto descend = std::count(input.cbegin(), input.cend(), ')');
    std::cout << ascend - descend << std::endl;

    return 0;
}