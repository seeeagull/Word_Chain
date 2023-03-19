#include "compute/controller.h"

int main(int argc, char **argv) {
    auto controller = new Controller();
    int ret;
    int code = controller->Cmd(argc, argv, &ret);
//    std::cout << "return code: " << code << std::endl;
    return 0;
}
