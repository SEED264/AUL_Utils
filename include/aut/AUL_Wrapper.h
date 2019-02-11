#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_

#include <lua.hpp>
#include "aut/AUL_Enum.h"
#include "aut/AUT_Type.h"

namespace aut {
    int getpixeldata(lua_State *L, Pixel_RGBA **out_data, int *out_w, int *out_h, getpixeldata_op option = 0);
}

int aut::getpixeldata(lua_State *L, Pixel_RGBA **out_data, int *out_w, int *out_h, getpixeldata_op option = 0) {
    lua_getglobal(L, "obj");
    lua_getfield(L, -1, "getpixeldata");
    lua_call(L, 0, 3);
    *out_h = lua_tointeger(L, -1);
    *out_w = lua_tointeger(L, -2);
    *out_data = (Pixel_RGBA*)lua_touserdata(L, -3);
    lua_pop(L, 3)
    if (*out_data == nullptr) return -1;
    return 0;
}
#endif // _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_