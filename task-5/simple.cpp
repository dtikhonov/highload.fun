#include <iostream>

int main() {
    uint64_t count = 0;
    while (std::cin) {
        uint8_t v = 0;
        std::cin >> v;
        if (v == 127)
            ++count;
    }

    std::cout << count << std::endl;
    return 0;
}
