/*
BSD 2-Clause License

Copyright (c) 2023, Caleb Heydon
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <libre/matrix.h>

#include <stddef.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    libre_matrix_t a;
    libre_matrix_create(&a, 2, 3);

    libre_matrix_t b;
    libre_matrix_create(&b, 3, 2);

    a.data[0] = 1.0f;
    a.data[1] = 2.0f;
    a.data[2] = 3.0f;
    a.data[3] = 4.0f;
    a.data[4] = 5.0f;
    a.data[5] = 6.0f;

    b.data[0] = 7.0f;
    b.data[1] = 8.0f;
    b.data[2] = 9.0f;
    b.data[3] = 10.0f;
    b.data[4] = 11.0f;
    b.data[5] = 12.0f;

    int result;
    libre_matrix_t product = libre_matrix_multiply(a, b, NULL, &result);

    if (result)
    {
        printf("error\n");
        return -1;
    }

    libre_matrix_print(product);

    libre_matrix_destroy(product);
    libre_matrix_destroy(b);
    libre_matrix_destroy(a);
    return 0;
}
