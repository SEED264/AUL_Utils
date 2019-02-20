#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_

#include <cstddef>
#include <string>
#include <vector>
#include <lua.hpp>
#include "aut/AUL_Enum.h"
#include "aut/AUL_Type.h"

using std::string;
using std::vector;

namespace aut {
    void getAULFunc(lua_State *L, const string &funcName);

    template<typename T>
    size_t pushValue(lua_State *L, T *v);
    size_t pushValue(lua_State *L, lua_Integer v);
    size_t pushValue(lua_State *L, const std::string &v);
    size_t pushValue(lua_State *L, lua_Number v);

    int getpixeldata(lua_State *L, Pixel_RGBA **out_data, Size_2D *out_size, const vector<string> &option = vector<string>());
    int getpixeldata(lua_State *L, Pixel_RGBA **out_data, uint *out_w, uint *out_h, const vector<string> &option = vector<string>());
    int putpixeldata(lua_State *L, Pixel_RGBA *data);
}

void aut::getAULFunc(lua_State *L, const string &funcName) {
    lua_getglobal(L, "obj");
    lua_getfield(L, -1, funcName.c_str());
}


template <typename T>
size_t aut::pushValue(lua_State *L, T *v) {
    lua_pushlightuserdata(L, v);
    return 1;
}

size_t aut::pushValue(lua_State *L, lua_Integer v) {
    lua_pushinteger(L, v);
    return 1;
}

size_t aut::pushValue(lua_State *L, const std::string &v) {
    lua_pushstring(L, v.c_str());
    return 1;
}

size_t aut::pushValue(lua_State *L, lua_Number v) {
    lua_pushnumber(L, v);
    return 1;
}


int aut::getpixeldata(lua_State *L, Pixel_RGBA **out_data, Size_2D *out_size, const vector<string> &option) {
    return getpixeldata(L, out_data, &out_size->w, &out_size->h, option);
}

int aut::getpixeldata(lua_State *L, Pixel_RGBA **out_data, uint *out_w, uint *out_h, const vector<string> &option)
{
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