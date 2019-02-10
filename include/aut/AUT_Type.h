#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_TYPE_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_TYPE_H_

// unsigned longの代わりのメモリ上の配置が同じになる構造体
// メモリの配置順の都合上、内部の変数の順番はBGRAでなくてはならない
struct Pixel_RGBA {
	unsigned char b = 0;
	unsigned char g = 0;
	unsigned char r = 0;
	unsigned char a = 0;
};

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_TYPE_H_