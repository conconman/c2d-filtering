#include <iostream>
#include "system.h"
#include <string>

int main() {
    // Build System object.
    System sys1{"sys1", 2};
    sys1.get_info();

    std::cout << "Program finished." << std::endl;
}