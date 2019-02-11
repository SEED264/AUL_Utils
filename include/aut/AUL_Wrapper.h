#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_

#include <string>
#include <vector>
#include <lua.hpp>
#include "aut/AUL_Enum.h"
#include "aut/AUL_Type.h"

using std::string;
using std::vector;

namespace aut {
    void getAULFunc(lua_State *L, const string &funcName);
    int getpixeldata(lua_State *L, Pixel_RGBA **out_data, int *out_w, int *out_h, vector<string> &option=vector<string>());
    int putpixeldata(lua_State *L, Pixel_RGBA *data);
}

void aut::getAULFunc(lua_State *L, const string &funcName) {
    lua_getglobal(L, "obj");
    lua_getfield(L, -1, funcName.c_str());
}

int aut::getpixeldata(lua_State *L, Pixel_RGBA **out_data, int *out_w, int *out_h, vector<string> &option=vector<string>()) {
    getAULFunc(L, "getpixeldata");
    int argnum = 0;
    for(size_t i = 0; i < option.size(); i++) {
        lua_pushstring(L, option[i].c_str());
        argnum++;
    }
    lua_call(L, argnum, 3);
    *out_h = lua_tointeger(L, -1);
    *out_w = lua_tointeger(L, -2);
    *out_data = (Pixel_RGBA*)lua_touserdata(L, -3);
    lua_pop(L, 3);
    if (*out_data == nullptr) return -1;
    return 0;
}

int aut::putpixeldata(lua_State *L, Pixel_RGBA *data) {
    getAULFunc(L, "putpixeldata");
    lua_pushlightuserdata(L, data);
    lua_call(L, 1, 0);
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_