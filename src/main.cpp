#include <iostream>
#include "CLI/CliContext.h"
using namespace std;



int main(int argc, char *argv[]) {
    try {
        CliContext context(argc, argv);
        context.execute();
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}


