#include "compute/controller.h"

int main(int argc, char **argv) {
    auto controller = new Controller();
    controller->Cmd(argc, argv);
    return 0;
}
