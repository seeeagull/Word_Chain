//
// Created by seeeagull on 23-3-6.
//

#ifndef WORD_CHAIN_TYPES_H
#define WORD_CHAIN_TYPES_H

#include <exception>

enum FUNCTION_TYPE {
    kNone,
    kFindAllWordChains,
    kFindWordChainWithMostWords,
    kFindWordChainWithMostLetters
};

enum ERROR_CODE {
    kNoError,
    kNoFilePath,
    kMultiFilePath,
    kFileNotExists,
    kFileTypeError,
    kIllegalParam,
    kNoFunctionalParam,
    kParamsConflict,
    kDuplicateParam,
    kCharNotAssign,
    kIllegalChar,
    kUnexpectedLoop,
    kLengthOverflow,
    kIllegalInput
};



struct ParamsConflictException
        : public std::exception {
    const char * what () const noexcept override {
        return "Parameters conflict!";
    }
};

struct DuplicateParamException
        : public std::exception {
    const char * what () const noexcept override {
        return "Duplicate parameter exists!";
    }
};

struct NoFunctionalParamException
        : public std::exception {
    const char * what () const noexcept override {
        return "Must specify one functional parameter!";
    }
};

struct NoInputFileException
        : public std::exception {
    const char * what () const noexcept override {
        return "Must input a text file!";
    }
};

struct FileTypeErrorException
        : public std::exception {
    const char * what () const noexcept override {
        return "Should input a .txt file!";
    }
};

struct MultipleFileException
        : public std::exception {
    const char * what () const noexcept override {
        return "Can only input one .txt file!";
    }
};

struct InputFileNotExists
        : public std::exception {
    const char * what () const noexcept override {
        return "Cannot find text file!";
    }
};

struct IllegalParamException
        : public std::exception {
    const char * what () const noexcept override {
        return "Input contains illegal parameters!";
    }
};

struct CharNotAssignException
        : public std::exception {
    const char * what () const noexcept override {
        return "Should assign a char for additional parameters!";
    }
};

struct IllegalCharException
        : public std::exception {
    const char * what () const noexcept override {
        return "The assigned char for additional parameters is illegal!";
    }
};

#endif //WORD_CHAIN_TYPES_H
