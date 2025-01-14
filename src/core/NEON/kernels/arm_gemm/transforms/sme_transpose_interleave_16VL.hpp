/*
 * Copyright (c) 2022 Arm Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#pragma once

#ifdef __ARM_FEATURE_SVE


namespace {

void sme_transpose_interleave_16VL(uint32_t *out, const uint32_t *in, size_t width, size_t in_stride, size_t height)
{
    size_t out_stride = 16 * height * sme::get_vector_length<uint8_t>();

    __asm__ __volatile__(
      ".inst 0xd503477f  // SMSTART ZA\n"
      "ptrue p7.b\n"
      "1:"  // Main row loop: Head
      "mov x22, %x[in]\n"
      "add %x[in], x22, %x[in_stride]\n"
      "mov x21, %x[out]\n"
      "sub %x[height], %x[height], #0x1\n"
      "mov x20, %x[width]\n"
      "2:"  // Main row loop: Column loop
      "mov x19, x20\n"
      "whilelt p0.s, XZR, x19\n"
      "ld1w { z31.s }, p0/Z, [x22]\n"
      "decw x19\n"
      "whilelt p0.s, XZR, x19\n"
      "ld1w { z30.s }, p0/Z, [x22, #1, MUL VL]\n"
      "decw x19\n"
      "whilelt p0.s, XZR, x19\n"
      "ld1w { z29.s }, p0/Z, [x22, #2, MUL VL]\n"
      "decw x19\n"
      "whilelt p0.s, XZR, x19\n"
      "ld1w { z28.s }, p0/Z, [x22, #3, MUL VL]\n"
      "decw x19\n"
      "whilelt p0.s, XZR, x19\n"
      "ld1w { z27.s }, p0/Z, [x22, #4, MUL VL]\n"
      "decw x19\n"
      "whilelt p0.s, XZR, x19\n"
      "ld1w { z26.s }, p0/Z, [x22, #5, MUL VL]\n"
      "decw x19\n"
      "whilelt p0.s, XZR, x19\n"
      "ld1w { z25.s }, p0/Z, [x22, #6, MUL VL]\n"
      "decw x19\n"
      "whilelt p0.s, XZR, x19\n"
      "ld1w { z24.s }, p0/Z, [x22, #7, MUL VL]\n"
      "decw x19\n"
      "whilelt p0.s, XZR, x19\n"
      "decw x19\n"
      "whilelt p6.s, XZR, x19\n"
      "decw x19\n"
      "whilelt p5.s, XZR, x19\n"
      "decw x19\n"
      "whilelt p4.s, XZR, x19\n"
      "decw x19\n"
      "whilelt p3.s, XZR, x19\n"
      "decw x19\n"
      "whilelt p2.s, XZR, x19\n"
      "decw x19\n"
      "whilelt p1.s, XZR, x19\n"
      "decw x19\n"
      "addvl x22, x22, #16\n"
      "ld1w { z23.s }, p0/Z, [x22, #-8, MUL VL]\n"
      "whilelt p0.s, XZR, x19\n"
      "mov x19, x21\n"
      "ld1w { z22.s }, p6/Z, [x22, #-7, MUL VL]\n"
      "decw x20, ALL, MUL #16\n"
      "ld1w { z21.s }, p5/Z, [x22, #-6, MUL VL]\n"
      "cmp x20, #0x0\n"
      "ld1w { z20.s }, p4/Z, [x22, #-5, MUL VL]\n"
      "add x21, x21, %x[out_stride]\n"
      "ld1w { z19.s }, p3/Z, [x22, #-4, MUL VL]\n"
      "ld1w { z18.s }, p2/Z, [x22, #-3, MUL VL]\n"
      "ld1w { z17.s }, p1/Z, [x22, #-2, MUL VL]\n"
      "ld1w { z16.s }, p0/Z, [x22, #-1, MUL VL]\n"
      "st1w { z31.s }, p7, [x19]\n"
      "st1w { z30.s }, p7, [x19, #1, MUL VL]\n"
      "st1w { z29.s }, p7, [x19, #2, MUL VL]\n"
      "st1w { z28.s }, p7, [x19, #3, MUL VL]\n"
      "st1w { z27.s }, p7, [x19, #4, MUL VL]\n"
      "st1w { z26.s }, p7, [x19, #5, MUL VL]\n"
      "st1w { z25.s }, p7, [x19, #6, MUL VL]\n"
      "st1w { z24.s }, p7, [x19, #7, MUL VL]\n"
      "addvl x19, x19, #16\n"
      "st1w { z23.s }, p7, [x19, #-8, MUL VL]\n"
      "st1w { z22.s }, p7, [x19, #-7, MUL VL]\n"
      "st1w { z21.s }, p7, [x19, #-6, MUL VL]\n"
      "st1w { z20.s }, p7, [x19, #-5, MUL VL]\n"
      "st1w { z19.s }, p7, [x19, #-4, MUL VL]\n"
      "st1w { z18.s }, p7, [x19, #-3, MUL VL]\n"
      "st1w { z17.s }, p7, [x19, #-2, MUL VL]\n"
      "st1w { z16.s }, p7, [x19, #-1, MUL VL]\n"
      "bgt 2b\n"
      "3:"  // Main row loop: Column loop skip
      "cmp %x[height], #0x1\n"
      "addvl %x[out], %x[out], #16\n"
      "bge 1b\n"
      ".inst 0xd503467f  // SMSTOP\n"
      : [height] "+&r" (height), [in] "+&r" (in), [out] "+&r" (out)
      : [in_stride] "r" (in_stride), [out_stride] "r" (out_stride), [width] "r" (width)
      : "cc", "memory", "p0", "p1", "p2", "p3", "p4", "p5", "p6", "p7", "p8", "p9", "p10", "p11", "p12", "p13", "p14", "p15", "x19", "x20", "x21", "x22", "z0", "z1", "z2", "z3", "z4", "z5", "z6", "z7", "z8", "z9", "z10", "z11", "z12", "z13", "z14", "z15", "z16", "z17", "z18", "z19", "z20", "z21", "z22", "z23", "z24", "z25", "z26", "z27", "z28", "z29", "z30", "z31"
    );
}

} // anonymous namespace

template<>
void Transform<16, 1, true, VLType::SME>(
    float *out, const float *in, int stride, int x0, int xmax, int k0, int kmax)
{
    sme_transpose_interleave_16VL(
        reinterpret_cast<uint32_t *>(out),
        reinterpret_cast<const uint32_t *>(in + k0 * stride + x0),
        (xmax-x0) * sizeof(float) / 4,
        stride * sizeof(float),
        (kmax-k0)
    );
}

#endif // __ARM_FEATURE_SVE
