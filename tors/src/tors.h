#ifndef TORS_H
#define TORS_H

/*
 * MIT License
 * 
 * Copyright (c) 2023 Jshuk-7
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include <stdint.h>
#include <ctype.h>

#ifndef TORS_MALLOC
#include <stdlib.h>
#define TORS_MALLOC malloc
#endif

#ifndef TORS_REALLOC
#include <stdlib.h>
#define TORS_REALLOC realloc
#endif

#ifndef TORS_FREE
#include <stdlib.h>
#define TORS_FREE free
#endif

#ifndef TORS_ASSERT
#include <assert.h>
#define TORS_ASSERT assert
#endif

#define DYN_STRING_IMPLEMENTATION
#include "dyn_string.h"

#define DYN_ARRAY_IMPLEMENTATION
#include "dyn_array.h"

typedef enum
{
    TT_WORD,
    TT_PUNCTUATION,
    TT_ARITHMETIC,
} TokenType;

typedef struct
{
    TokenType type;
    size_t ascii_sum;
} Token;

/// @brief Converts the input to a stream of tokens. To free the result use darray_destroy.
/// @param input the input string
/// @return a dynamic array of tokens
DArray* tors_tokenize_string(const DString* input);

#endif

#ifdef TORS_IMPLEMENTATION

static void add_token(DArray* tokens, const Token* token) {
    darray_push_back(tokens, sizeof(Token), token);
}

DArray* tors_tokenize_string(const DString* input)
{
    TORS_ASSERT(input->data);
    DArray* tokens = darray_create(sizeof(Token));
    size_t start = 0;
    size_t cursor = 0;

    while (cursor < input->size) {
        char c = dstring_get_char(input, cursor);
        start = cursor;

        if (isalpha(c)) {
            while (isalpha(c)) {
                c = dstring_get_char(input, ++cursor);
            }
            size_t count = cursor - start;
            DString lexeme = dstring_substring(input, start, count);
            size_t sum = 0;
            for (size_t i = 0; i < lexeme.size; i++) {
                sum += (size_t)(uint32_t)dstring_get_char(&lexeme, i);
            }
            Token token = { .type = TT_WORD, .ascii_sum = sum };
            add_token(tokens, &token);
        }

        if (isspace(c)) {
            cursor++;
        }

        if (c == '!') {
            size_t sum = (size_t)(uint32_t)c;
            Token token = { .type = TT_PUNCTUATION, .ascii_sum = sum };
            add_token(tokens, &token);
            cursor++;
        }
    }

    return tokens;
}

#endif