#include "compute/controller.h"

int main(int argc, char **argv) {
    auto controller = new Controller();
    int ret;
    int code = controller->Cmd(argc, argv, &ret);
    switch (code) {
        case kNoFilePath:
            std::cout << "No File Path" << std::endl;
            break;
        case kMultiFilePath:
            std::cout << "Multiple File Path" << std::endl;
            break;
        case kFileNotExists:
            std::cout << "File Not Exists" << std::endl;
            break;
        case kFileTypeError:
            std::cout << "File Type Error" << std::endl;
            break;
        case kIllegalParam:
            std::cout << "Illegal Parameter" << std::endl;
            break;
        case kNoFunctionalParam:
            std::cout << "No Functional Parameter" << std::endl;
            break;
        case kParamsConflict:
            std::cout << "Parameters Conflict" << std::endl;
            break;
        case kDuplicateParam:
            std::cout << "Duplicate Parameter" << std::endl;
            break;
        case kCharNotAssign:
            std::cout << "Char Not Assign" << std::endl;
            break;
        case kIllegalChar:
            std::cout << "Illegal Char" << std::endl;
            break;
        case kUnexpectedLoop:
            std::cout << "Unexpected Loop" << std::endl;
            break;
        case kLengthOverflow:
            std::cout << "Length Overflow" << std::endl;
            break;
    }
//    std::cout << "return code: " << code << std::endl;
    return 0;
}
