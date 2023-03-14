//
// Created by seeeagull on 23-3-7.
//


#include <cstring>
#include "controller.h"

void Controller::ParseCmd(int argc, char *argv[]) {
    std::string suffix;
    int i = 1;
    while (i < argc) {
        switch (argv[i][1]) {
            case 'n':
                if (function_type_ != kNone) {
                    if (function_type_ == kFindAllWordChains) {
                        throw DuplicateParamException();
                    } else {
                        throw ParamsConflictException();
                    }
                }
                function_type_ = kFindAllWordChains;
                if (i + 1 == argc || argv[i + 1][0] == '-') {
                    throw NoInputFileException();
                }
                input_file_ = argv[i + 1];
                if (input_file_.length() <= 4) {
                    throw FileTypeErrorException();
                }
                suffix = input_file_.substr(input_file_.length() - 4);
                if (suffix != ".txt") {
                    throw FileTypeErrorException();
                }
                i += 2;
                if (i < argc && argv[i][0] != '-') {
                    throw MultipleFileException();
                }
                break;
            case 'w':
                if (function_type_ != kNone) {
                    if (function_type_ == kFindWordChainWithMostWords) {
                        throw DuplicateParamException();
                    } else {
                        throw ParamsConflictException();
                    }
                }
                function_type_ = kFindWordChainWithMostWords;
                if (i + 1 == argc || argv[i + 1][0] == '-') {
                    throw NoInputFileException();
                }
                input_file_ = argv[i + 1];
                if (input_file_.length() <= 4) {
                    throw FileTypeErrorException();
                }
                suffix = input_file_.substr(input_file_.length() - 4);
                if (suffix != ".txt") {
                    throw FileTypeErrorException();
                }
                i += 2;
                if (i < argc && argv[i][0] != '-') {
                    throw MultipleFileException();
                }
                break;
            case 'c':
                if (function_type_ != kNone) {
                    if (function_type_ == kFindWordChainWithMostLetters) {
                        throw DuplicateParamException();
                    } else {
                        throw ParamsConflictException();
                    }
                }
                function_type_ = kFindWordChainWithMostLetters;
                if (i + 1 == argc || argv[i + 1][0] == '-') {
                    throw NoInputFileException();
                }
                input_file_ = argv[i + 1];
                if (input_file_.length() <= 4) {
                    throw FileTypeErrorException();
                }
                suffix = input_file_.substr(input_file_.length() - 4);
                if (suffix != ".txt") {
                    throw FileTypeErrorException();
                }
                i += 2;
                if (i < argc && argv[i][0] != '-') {
                    throw MultipleFileException();
                }
                break;
            case 'h':
                if (i + 1 == argc || argv[i + 1][0] == '-') {
                    throw CharNotAssignException();
                }
                if (strlen(argv[i + 1]) > 1) {
                    throw IllegalCharException();
                }
                if (argv[i + 1][0] >='A' && argv[i + 1][0] <= 'Z') {
                    head = argv[i + 1][0] - 'A';
                } else if (argv[i + 1][0] >= 'a' && argv[i + 1][0] <= 'z') {
                    head = argv[i + 1][0] - 'a';
                } else  {
                    throw IllegalCharException();
                }
                i += 2;
                if (i < argc && argv[i][0] != '-') {
                    throw IllegalCharException();
                }
                break;
            case 't':
                if (i + 1 == argc || argv[i + 1][0] == '-') {
                    throw CharNotAssignException();
                }
                if (strlen(argv[i + 1]) > 1) {
                    throw IllegalCharException();
                }
                if (argv[i + 1][0] >='A' && argv[i + 1][0] <= 'Z') {
                    tail = argv[i + 1][0] - 'A';
                } else if (argv[i + 1][0] >= 'a' && argv[i + 1][0] <= 'z') {
                    tail = argv[i + 1][0] - 'a';
                } else  {
                    throw IllegalCharException();
                }
                i += 2;
                if (i < argc && argv[i][0] != '-') {
                    throw IllegalCharException();
                }
                break;
            case 'j':
                if (i + 1 == argc || argv[i + 1][0] == '-') {
                    throw CharNotAssignException();
                }
                if (strlen(argv[i + 1]) > 1) {
                    throw IllegalCharException();
                }
                if (argv[i + 1][0] >='A' && argv[i + 1][0] <= 'Z') {
                    banned_head_ = argv[i + 1][0] - 'A';
                } else if (argv[i + 1][0] >= 'a' && argv[i + 1][0] <= 'z') {
                    banned_head_ = argv[i + 1][0] - 'a';
                } else  {
                    throw IllegalCharException();
                }
                i += 2;
                if (i < argc && argv[i][0] != '-') {
                    throw IllegalCharException();
                }
                break;
            case 'r':
                allow_loop_ = true;
                ++i;
                if (i < argc && argv[i][0] != '-') {
                    throw IllegalParamException();
                }
                break;
            default:
                throw IllegalParamException();
        }
    }
    if (function_type_ == kNone) {
        throw NoFunctionalParamException();
    }
    if (function_type_ == kFindAllWordChains &&
        (head != 30 || tail != 30 || banned_head_ != 30 || allow_loop_)) {
        throw ParamsConflictException();
    }
}

int Controller::Cmd(int argc, char **argv, int *res, const char* file_name) {
    try {
        ParseCmd(argc, argv);
    } catch (NoInputFileException& e) {
        return kNoFilePath;
    } catch (MultipleFileException& e) {
        return kMultiFilePath;
    } catch (FileTypeErrorException& e) {
        return kFileTypeError;
    } catch (IllegalParamException& e) {
        return kIllegalParam;
    } catch (NoFunctionalParamException& e) {
        return kNoFunctionalParam;
    } catch (ParamsConflictException& e) {
        return kParamsConflict;
    } catch (DuplicateParamException& e) {
        return kDuplicateParam;
    } catch (CharNotAssignException& e) {
        return kCharNotAssign;
    } catch (IllegalCharException& e) {
        return kIllegalChar;
    }
    graph.SetHead(head);
    graph.SetTail(tail);
    graph.SetBannedHead(banned_head_);
    graph.SetFileIO(&file_io_);
    file_io_.SetInputFile(std::make_shared<std::string>(input_file_));
    std::string output_file(file_name);
    file_io_.SetOutputFile(std::make_shared<std::string>(output_file));
    std::vector<std::shared_ptr<std::string>> words{};
    try {
        file_io_.ReadFile(words);
    } catch (InputFileNotExists& e) {
        return kFileNotExists;
    }

    for(const auto& it : words) {
        graph.AddWord(it);
    }
    bool has_loop = graph.DetectLoop();
    if (has_loop && !allow_loop_) {
        return kUnexpectedLoop;
    }
    std::vector<std::shared_ptr<std::string>> wordlist{};
    switch (function_type_) {
        case kFindAllWordChains:
            *res = graph.FindAllWordChains(wordlist);
            break;
        case kFindWordChainWithMostWords:
            *res = graph.FindLongestChain(false, wordlist);
            break;
        case kFindWordChainWithMostLetters:
            *res = graph.FindLongestChain(true, wordlist);
            break;
        default:
            break;
    }
    return kNoError;
}

