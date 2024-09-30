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

        const std::vector<int> area = {size[0] * size[1], size[0] * size[2], size[1] * size[2]};

        const int partial = 2 * std::accumulate(area.cbegin(), area.cend(), 0) +
                            *std::min_element(area.cbegin(), area.cend());

        total += partial;
    }

    std::cout << total << std::endl;

    return 0;
}