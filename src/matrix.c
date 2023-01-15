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

#include "libre/matrix.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int libre_matrix_create(libre_matrix_t *matrix, int rows, int columns)
{
   if (!matrix)
      return -1;
   memset(matrix, 0, sizeof(*matrix));

   matrix->rows = rows;
   matrix->columns = columns;

   matrix->data = malloc(sizeof(LIBRE_MATRIX_TYPE) * rows * columns);
   if (!matrix->data)
      return -1;
   memset(matrix->data, 0, sizeof(LIBRE_MATRIX_TYPE) * rows * columns);

   return 0;
}

void libre_matrix_destroy(libre_matrix_t matrix)
{
   free(matrix.data);
   matrix.data = NULL;
}

void libre_matrix_print(libre_matrix_t matrix)
{
   for (int i = 0; i < matrix.rows; i++)
   {
      for (int j = 0; j < matrix.columns; j++)
         printf("%f\t", LIBRE_MATRIX_GET(matrix, i, j));
      printf("\n");
   }
}

libre_matrix_t libre_matrix_copy(libre_matrix_t matrix, int *result)
{
   libre_matrix_t copy = {0};

   if (libre_matrix_create(&copy, matrix.rows, matrix.columns))
   {
      if (result)
         *result = -1;
      return copy;
   }

   memcpy(copy.data, matrix.data, sizeof(LIBRE_MATRIX_TYPE) * copy.rows * copy.columns);

   if (result)
      *result = 0;
   return copy;
}

libre_matrix_t libre_matrix_add(libre_matrix_t a, libre_matrix_t b, libre_matrix_t *destination, int *result)
{
   libre_matrix_t sum = {0};

   if (a.rows != b.rows || a.columns != b.columns)
   {
      if (result)
         *result = -1;
      return sum;
   }

   if (destination)
   {
      if (destination->rows != a.rows || destination->columns != a.columns)
      {
         if (result)
            *result = -1;
         return sum;
      }
      sum = *destination;
   }
   else if (libre_matrix_create(&sum, a.rows, a.columns))
   {
      if (result)
         *result = -1;
      return sum;
   }

   for (int i = 0; i < a.rows; i++)
      for (int j = 0; j < a.columns; j++)
         LIBRE_MATRIX_SET(sum, i, j, LIBRE_MATRIX_GET(a, i, j) + LIBRE_MATRIX_GET(b, i, j));

   if (result)
      *result = 0;
   return sum;
}

void libre_matrix_scale(libre_matrix_t matrix, LIBRE_MATRIX_TYPE factor)
{
   for (int i = 0; i < matrix.rows; i++)
      for (int j = 0; j < matrix.columns; j++)
         LIBRE_MATRIX_SET(matrix, i, j, LIBRE_MATRIX_GET(matrix, i, j) * factor);
}

libre_matrix_t libre_matrix_multiply(libre_matrix_t a, libre_matrix_t b, libre_matrix_t *destination, int *result)
{
   libre_matrix_t product = {0};

   if (a.columns != b.rows)
   {
      if (result)
         *result = -1;
      return product;
   }

   if (destination)
   {
      if (destination->rows != a.rows || destination->columns != b.columns)
      {
         if (result)
            *result = -1;
         return product;
      }
      product = *destination;
   }
   else if (libre_matrix_create(&product, a.rows, b.columns))
   {
      if (result)
         *result = -1;
      return product;
   }

   for (int i = 0; i < product.rows; i++)
      for (int j = 0; j < product.columns; j++)
      {
         LIBRE_MATRIX_TYPE sum = 0;
         for (int k = 0; k < a.columns; k++)
            sum += LIBRE_MATRIX_GET(a, i, k) * LIBRE_MATRIX_GET(b, k, j);

         LIBRE_MATRIX_SET(product, i, j, sum);
      }

   if (result)
      *result = 0;
   return product;
}

libre_matrix_t libre_matrix_projection_ortho(LIBRE_MATRIX_TYPE l, LIBRE_MATRIX_TYPE r, LIBRE_MATRIX_TYPE t, LIBRE_MATRIX_TYPE b, LIBRE_MATRIX_TYPE n, LIBRE_MATRIX_TYPE f, int *result)
{
   libre_matrix_t projection = {0};
   if (libre_matrix_create(&projection, 4, 4))
   {
      if (result)
         *result = -1;
      return projection;
   }

   LIBRE_MATRIX_SET(projection, 0, 0, (LIBRE_MATRIX_TYPE)2.0 / (r - l));
   LIBRE_MATRIX_SET(projection, 1, 1, (LIBRE_MATRIX_TYPE)2.0 / (t - b));
   LIBRE_MATRIX_SET(projection, 2, 2, (LIBRE_MATRIX_TYPE)2.0 / (f - n));
   LIBRE_MATRIX_SET(projection, 3, 3, (LIBRE_MATRIX_TYPE)1.0);

   LIBRE_MATRIX_SET(projection, 0, 3, -(r + l) / (r - l));
   LIBRE_MATRIX_SET(projection, 1, 3, -(t + b) / (t - b));
   LIBRE_MATRIX_SET(projection, 2, 3, -(f + n) / (f - n));

   if (result)
      *result = 0;
   return projection;
}

libre_matrix_t libre_matrix_translation(LIBRE_MATRIX_TYPE x, LIBRE_MATRIX_TYPE y, LIBRE_MATRIX_TYPE z, int *result)
{
   libre_matrix_t translation = {0};
   if (libre_matrix_create(&translation, 4, 4))
   {
      if (result)
         *result = -1;
      return translation;
   }

   for (int i = 0; i < 4; i++)
      LIBRE_MATRIX_SET(translation, i, i, (LIBRE_MATRIX_TYPE)1.0);

   LIBRE_MATRIX_SET(translation, 0, 3, x);
   LIBRE_MATRIX_SET(translation, 1, 3, y);
   LIBRE_MATRIX_SET(translation, 2, 3, z);

   if (result)
      *result = 0;
   return translation;
}

libre_matrix_t libre_matrix_rotation(LIBRE_MATRIX_TYPE w, LIBRE_MATRIX_TYPE x, LIBRE_MATRIX_TYPE y, LIBRE_MATRIX_TYPE z, int *result)
{
   libre_matrix_t rotation = {0};
   if (libre_matrix_create(&rotation, 4, 4))
   {
      if (result)
         *result = -1;
      return rotation;
   }

   LIBRE_MATRIX_TYPE magnitude = 0;
   magnitude += w * w;
   magnitude += x * x;
   magnitude += y * y;
   magnitude += z * z;
   magnitude = (LIBRE_MATRIX_TYPE)sqrt(magnitude);

   w /= magnitude;
   x /= magnitude;
   y /= magnitude;
   z /= magnitude;

   LIBRE_MATRIX_SET(rotation, 0, 0, (LIBRE_MATRIX_TYPE)(1.0 - 2.0 * y * y - 2.0 * z * z));
   LIBRE_MATRIX_SET(rotation, 0, 1, (LIBRE_MATRIX_TYPE)(2.0 * x * y - 2.0 * z * w));
   LIBRE_MATRIX_SET(rotation, 0, 2, (LIBRE_MATRIX_TYPE)(2.0 * x * z + 2.0 * y * w));

   LIBRE_MATRIX_SET(rotation, 1, 0, (LIBRE_MATRIX_TYPE)(2.0 * x * y + 2.0 * z * w));
   LIBRE_MATRIX_SET(rotation, 1, 1, (LIBRE_MATRIX_TYPE)(1.0 - 2.0 * x * x + 2.0 * z * z));
   LIBRE_MATRIX_SET(rotation, 1, 2, (LIBRE_MATRIX_TYPE)(2.0 * y * z - 2.0 * x * w));

   LIBRE_MATRIX_SET(rotation, 2, 0, (LIBRE_MATRIX_TYPE)(2.0 * x * z - 2.0 * y * w));
   LIBRE_MATRIX_SET(rotation, 2, 1, (LIBRE_MATRIX_TYPE)(2.0 * y * z + 2.0 * x * w));
   LIBRE_MATRIX_SET(rotation, 2, 2, (LIBRE_MATRIX_TYPE)(1.0 - 2.0 * x * x - 2.0 * y * y));

   LIBRE_MATRIX_SET(rotation, 3, 3, (LIBRE_MATRIX_TYPE)1.0);

   if (result)
      *result = 0;
   return rotation;
}
