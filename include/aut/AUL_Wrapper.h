#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_

#include <cstddef>
#include <limits>
#include <string>
#include <vector>
#include <lua.hpp>
#include "aut/AUL_Enum.h"
#include "aut/AUL_Type.h"

namespace aut {
    void getAULFunc(lua_State *L, const std::string &funcName);

    size_t pushValue(lua_State *L, void *v);
    size_t pushValue(lua_State *L, lua_Integer v);
    size_t pushValue(lua_State *L, const std::string &v);
    size_t pushValue(lua_State *L, lua_Number v);
    size_t pushBool(lua_State *L, bool v);

    template <typename T>
    size_t setArgs(lua_State *L, T value);
    template <typename T, typename... Parms>
    size_t setArgs(lua_State *L, T value, Parms... parms);

    template <typename... Parms>
    void effect(lua_State *L, Parms... parms);
    void draw(lua_State *L, double ox = 0, double oy = 0, double oz = 0, double zoom = 1, double alpha = 1, double rx = 0, double ry = 0, double rz = 0);
    void drawpoly(lua_State *L, double x0, double y0, double z0, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3,
                 double u0 = 0, double v0 = 0, double u1 = USHRT_MAX, double v1 = 0, double u2 = USHRT_MAX, double v2 = USHRT_MAX, double u3 = 0, double v3 = USHRT_MAX, double alpha = 1);
    template <typename... Parms>
    void load(lua_State *L, Parms... parms);
    template <typename... Parms>
    void setfont(lua_State *L, const std::string &name, double size, Parms... parms);
    template <typename... Parms>
    lua_Integer rand(lua_State *L, lua_Integer st_num, lua_Integer ed_num, Parms... parms);
    template <typename... Parms>
    void setoption(lua_State *L, const std::string &name, Parms... parms);
    lua_Integer getoption_track_mode(lua_State *L, lua_Integer value);
    lua_Integer getoption_section_num(lua_State *L);
    const char* getoption_script_name(lua_State *L, lua_Integer value = 0, bool skip = false);
    void getpixeldata(lua_State *L, Pixel_RGBA **out_data, Size_2D *out_size, const std::vector<std::string> &option = std::vector<std::string>());
    void getpixeldata(lua_State *L, Pixel_RGBA **out_data, uint *out_w, uint *out_h, const std::vector<std::string> &option = std::vector<std::string>());
    void putpixeldata(lua_State *L, Pixel_RGBA *data);
}

void aut::getAULFunc(lua_State *L, const std::string &funcName) {
    lua_getglobal(L, "obj");
    lua_getfield(L, -1, funcName.c_str());
}

size_t aut::pushValue(lua_State *L, void *v) {
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

size_t aut::pushBool(lua_State *L, bool v) {
    lua_pushboolean(L, v);
    return 1;
}

template <typename T>
size_t aut::setArgs(lua_State *L, T value) {
    return aut::pushValue(L, value);
}

template <typename T, typename... Parms>
size_t aut::setArgs(lua_State *L, T value, Parms... parms) {
    size_t pushedNum = aut::pushValue(L, value);
    return setArgs(L, parms...) + pushedNum;
}

template <typename... Parms>
void aut::effect(lua_State *L, Parms... parms) {
    aut::getAULFunc(L, "effect");
    size_t pushedNum = setArgs(L, parms...);
    lua_call(L, pushedNum, 0);
}

void aut::draw(lua_State *L, double ox, double oy, double oz, double zoom, double alpha, double rx, double ry, double rz) {
    getAULFunc(L, "draw");
    size_t pushedNum = setArgs(L, ox, oy, oz, zoom, alpha, rx, ry, rz);
    lua_call(L, pushedNum, 0);
}

void aut::drawpoly(lua_State *L, double x0, double y0, double z0, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3,
             double u0, double v0, double u1, double v1, double u2, double v2, double u3, double v3, double alpha) {
    getAULFunc(L, "drawpoly");
    size_t pushedNum = setArgs(L, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3, u0, v0, u1, v1, u2, v2, u3, v3, alpha);
    lua_call(L, pushedNum, 0);
}

template <typename... Parms>
void aut::load(lua_State *L, Parms... parms) {
    aut::getAULFunc(L, "load");
    size_t pushedNum = setArgs(L, parms...);
    lua_call(L, pushedNum, 0);
}

template <typename... Parms>
void aut::setfont(lua_State *L, const std::string &name, double size, Parms... parms) {
    aut::getAULFunc(L, "setfont");
    size_t pushedNum = setArgs(L, name, size, parms...);
    lua_call(L, pushedNum, 0);
}

template <typename... Parms>
lua_Integer aut::rand(lua_State *L, lua_Integer st_num, lua_Integer ed_num, Parms... parms) {
    getAULFunc(L, "rand");
    size_t pushedNum = setArgs(L, st_num, ed_num, parms...);
    lua_call(L, pushedNum, 1);
    return lua_tointeger(L, -1);
}

template <typename... Parms>
void aut::setoption(lua_State *L, const std::string &name, Parms... parms) {
    getAULFunc(L, "setoption");
    size_t pushedNum = setArgs(L, name, parms...);
    lua_call(L, pushedNum, 0);
}

lua_Integer aut::getoption_track_mode(lua_State *L, lua_Integer value) {
    getAULFunc(L, "getoption");
    size_t pushedNum = setArgs(L, "track_mode", value);
    lua_call(L, pushedNum, 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

lua_Integer aut::getoption_section_num(lua_State *L) {
    getAULFunc(L, "getoption");
    size_t pushedNum = setArgs(L, "section_num");
    lua_call(L, pushedNum, 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

const char* aut::getoption_script_name(lua_State *L, lua_Integer value, bool skip) {
    getAULFunc(L, "getoption");
    size_t pushedNum = setArgs(L, "script_name", value);
    pushedNum += pushBool(L, skip);
    lua_call(L, pushedNum, 1);
    const char *ret = lua_tostring(L, -1);
    lua_pop(L, 1);
    return ret;
}

void aut::getpixeldata(lua_State *L, Pixel_RGBA **out_data, Size_2D *out_size, const std::vector<std::string> &option) {
  getpixeldata(L, out_data, &out_size->w, &out_size->h, option);
}

void aut::getpixeldata(lua_State *L, Pixel_RGBA **out_data, uint *out_w, uint *out_h, const std::vector<std::string> &option) {
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
}

void aut::putpixeldata(lua_State *L, Pixel_RGBA *data) {
    getAULFunc(L, "putpixeldata");
    lua_pushlightuserdata(L, data);
    lua_call(L, 1, 0);
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_