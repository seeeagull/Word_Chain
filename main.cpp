#include "compute/controller.h"

int main(int argc, char **argv) {
    auto controller = new Controller();
    int ret;
    controller->Cmd(argc, argv, &ret);
    return 0;
}
