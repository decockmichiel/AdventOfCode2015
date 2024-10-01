#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <memory>

#include "hashlibpp.h"

int main()
{
    const std::string input = "yzbqklnj";

    auto hashWrapper = std::make_unique<md5wrapper>();

    for (size_t i = 0; i != 1e6; ++i) {
        const auto hash = hashWrapper->getHashFromString(input + std::to_string(i));
        if (hash.substr(0, 5) != "00000")
            continue;

        std::cout << i << std::endl;
        break;
    }

    return 0;
}