#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

int main()
{
    std::string   input;
    std::ifstream fileStream;
    fileStream.open("input.txt");

    int total = 0;
    while (std::getline(fileStream, input))
    {
        std::vector<int> size;

        std::stringstream sstream(input);
        std::string       chunk;
        while (std::getline(sstream, chunk, 'x'))
        {
            size.push_back(std::stoi(chunk));
            std::cout << std::stoi(chunk) << std::endl;
        }

        std::sort(size.begin(), size.end());

        const int volume = size[0] * size[1] * size[2];

        const int partial = 2 * (size[0] + size[1]);

        total += volume + partial;
    }

    std::cout << total << std::endl;

    return 0;
}