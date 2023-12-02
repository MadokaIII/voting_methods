#ifndef TEST_CODE_H
#define TEST_CODE_H

#include "matrix.h"
#include "miscellaneous.h"
#include "stringbuffer.h"

// General errors
#define SUCCESS 0
#define FAILURE 1
#define MEMORY_ALLOCATION_ERROR 2
#define NULL_POINTER_ERROR 3

// Matrix-specific errors
#define MATRIX_INIT_ERROR 30
#define MATRIX_ADD_ERROR 31
#define MATRIX_DELETE_ERROR 32
#define MATRIX_ACCESS_ERROR 33
#define MATRIX_DIMENSION_ERROR 34

// String buffer-specific errors
#define STRINGBUFFER_INIT_ERROR 40
#define STRINGBUFFER_OVERFLOW_ERROR 41
#define STRINGBUFFER_UNDERFLOW_ERROR 42
#define STRINGBUFFER_CONCAT_ERROR 43
#define STRINGBUFFER_COPY_ERROR 44

// Other errors based on your requirements
#define INVALID_ARGUMENT_ERROR 50
#define UNEXPECTED_BEHAVIOR_ERROR 51
#define TIMEOUT_ERROR 52
#define PERMISSION_DENIED_ERROR 53

#endif /* TEST_CODE_H */