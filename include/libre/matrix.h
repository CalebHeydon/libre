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

#pragma once

#define LIBRE_MATRIX_TYPE float

typedef struct libre_matrix
{
   int rows, columns;
   LIBRE_MATRIX_TYPE *data;
} libre_matrix_t;

#define LIBRE_MATRIX_GET(matrix, i, j) ((matrix).data[i * (matrix).columns + j])
#define LIBRE_MATRIX_SET(matrix, i, j, x) ((matrix).data[i * (matrix).columns + j] = x)

int libre_matrix_create(libre_matrix_t *matrix, int rows, int columns);
void libre_matrix_destroy(libre_matrix_t matrix);
void libre_matrix_print(libre_matrix_t matrix);
libre_matrix_t libre_matrix_copy(libre_matrix_t matrix, int *result);

libre_matrix_t libre_matrix_add(libre_matrix_t a, libre_matrix_t b, libre_matrix_t *destination, int *result);
void libre_matrix_scale(libre_matrix_t matrix, LIBRE_MATRIX_TYPE factor);
libre_matrix_t libre_matrix_multiply(libre_matrix_t a, libre_matrix_t b, libre_matrix_t *destination, int *result);

libre_matrix_t libre_matrix_projection_ortho(LIBRE_MATRIX_TYPE l, LIBRE_MATRIX_TYPE r, LIBRE_MATRIX_TYPE t, LIBRE_MATRIX_TYPE b, LIBRE_MATRIX_TYPE n, LIBRE_MATRIX_TYPE f, int *result);
libre_matrix_t libre_matrix_translation(LIBRE_MATRIX_TYPE x, LIBRE_MATRIX_TYPE y, LIBRE_MATRIX_TYPE z, int *result);
libre_matrix_t libre_matrix_rotation(LIBRE_MATRIX_TYPE w, LIBRE_MATRIX_TYPE x, LIBRE_MATRIX_TYPE y, LIBRE_MATRIX_TYPE z, int *result);
