#define TORS_IMPLEMENTATION
#include "tors.h"

#include <stdio.h>

int main(void) {
	DString input = dstring_create("This is the beginning!");
	DArray* tokens = tors_tokenize_string(&input);

	for (size_t i = 0; i < tokens->buf_size; i++) {
		Token token = DARRAY_ELEMENT(tokens, Token, i);
		printf("%zu: %zu\n", i, token.ascii_sum);
	}

	dstring_destroy(&input);
	darray_destroy(tokens);
	return 0;
}