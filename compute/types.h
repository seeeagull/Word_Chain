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



struct ConflictFunctionalParamsException
        : public std::exception {
    const char * what () const noexcept override {
        return "Cannot specify more than one functional parameters!";
    }
};

struct ConflictAdditionalParamsException
        : public std::exception {
    const char * what () const noexcept override {
        return "Cannot add any additional parameters with functional parameter '-n'!";
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

struct CannotFindInputFile
        : public std::exception {
    const char * what () const noexcept override {
        return "Cannot find text file!";
    }
};


#endif //WORD_CHAIN_TYPES_H
