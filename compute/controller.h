//
// Created by seeeagull on 23-3-7.
//

#ifndef WORD_CHAIN_CONTROLLER_H
#define WORD_CHAIN_CONTROLLER_H

#include "./file_io.h"
#include "./graph.h"

class Controller {
public:
    void ParseCmd(int argc, char *argv[]);
    void Cmd(int argc, char *argv[]);

private:
    FUNCTION_TYPE function_type_ = kNone;
    bool allow_loop_ = false;
    std::string input_file_;
    char head = 30;
    char tail = 30;
    char banned_head_ = 30;
    FileIo file_io_{};
    Graph graph{};
};

#endif //WORD_CHAIN_CONTROLLER_H
