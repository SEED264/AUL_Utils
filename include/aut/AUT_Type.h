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
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_TYPE_H_