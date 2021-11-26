//
// Created by iensen on 8/19/16.
//

#ifndef PLOG_PLOG_H
#define PLOG_PLOG_H

typedef struct plog_ast_statement {
    //TODO
    union {
    };
}plog_ast_statement_t;

enum Format { json = 0, text = 1};

enum plog_warning {
    plog_warning_file_included       = 0, //!< same file included multiple times
    plog_warning_other = 1
};
//! Corresponding type to ::plog_warning.
typedef int plog_warning_t;

//! Enumeration of error codes.
//!
//! @note Errors can only be recovered from if explicitly mentioned; most
//! functions do not provide strong exception guarantees.  This means that in
//! case of errors associated objects cannot be used further.  If such an
//! object has a free function, this function can and should still be called.
enum plog_error {
    plog_error_runtime   = 1, //!< wrong usage of the clingo API or invalid input
    plog_error_sort_definition  = 2, //!< wrong usage of the clingo API or invalid input
};

//! Corresponding type to ::plog_error.
typedef int plog_error_t;

enum class SolvingMode {
    // compute query using algorithm for dynamically causally ordered programs
    query_dco,
    // compute query using naive algorithm (translation to clingo)
    query_naive,
    // compute possible worlds and probabilities
    possible_worlds

};
#endif //PLOG_PLOG_H
