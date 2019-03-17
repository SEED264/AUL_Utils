/*
 * This file is part of AUL_Utils.
 *
 * The MIT License
 *
 * Copyright (c) 2019 SEED264
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

#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_TYPE_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_TYPE_H_

namespace aut{
    using byte = unsigned char;
    using uint = unsigned int;
    using ulong = unsigned long;

    // unsigned longの代わりのメモリ上の配置が同じになる構造体
    // メモリの配置順の都合上、内部の変数の順番はBGRAでなくてはならない
    struct Pixel_RGBA {
        byte b;
        byte g;
        byte r;
        byte a;
        Pixel_RGBA(byte ar, byte ag, byte ab, byte aa):r(ar), g(ag), b(ab), a(aa) {}
        Pixel_RGBA() {
            Pixel_RGBA(0, 0, 0, 0);
        }
    };

    // 画像のサイズ等に使う構造体
    struct Size_2D{
        unsigned int w, h;
        Size_2D(unsigned int aw, unsigned int ah):w(aw), h(ah) {}
        Size_2D() {
            Size_2D(0, 0);
        }
    };

    // カメラのパラメータ用の構造体
    struct Camera_Param {
        double  x,  y,  z;
        double tx, ty, tz;
        double rz;
        double ux, uy, uz;
        double d;
    };

    // getpixel, putpixel等で使うcol用の構造体
    struct Pixel_Col {
        unsigned long col;
        float a;
        Pixel_Col(unsigned long acol, float aa):col(acol), a(aa) {}
        Pixel_Col() {
            Pixel_Col(0, 0);
        }
    };

    // getpixel, putpixel等で使うYCbCr用の構造体
    struct Pixel_YC {
        short y;
        short cb, cr;
        unsigned short a;
        Pixel_YC(short ay, short acb, short acr, unsigned short aa)
            :y(ay), cb(acb), cr(acr), a(aa) {}
        Pixel_YC() {
            Pixel_YC(0, 0, 0, 0);
        }
    };
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_TYPE_H_