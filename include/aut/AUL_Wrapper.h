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

    bool getVariable(lua_State *L, const std::string &name, int max_Local_Hierarchy = UCHAR_MAX);
    bool getGlobalVariable(lua_State *L, const std::string &name);
    bool getLocalVariable(lua_State *L, const std::string &name, int max_Hierarchy = UCHAR_MAX);

    bool getfield_Boolean(lua_State *L, const std::string &name);
    lua_Integer getfield_Integer(lua_State *L, const std::string &name);
    lua_Number getfield_Number(lua_State *L, const std::string &name);
    const char* getfield_String(lua_State *L, const std::string &name);
    void* getfield_Userdata(lua_State *L, const std::string &name);

    bool gettable_Boolean(lua_State *L, int index, int tableIndex = -1);
    lua_Integer gettable_Integer(lua_State *L, int index, int tableIndex = -1);
    lua_Number gettable_Number(lua_State *L, int index, int tableIndex = -1);
    const char* gettable_String(lua_State *L, int index, int tableIndex = -1);
    void* gettable_Userdata(lua_State *L, int index, int tableIndex = -1);

    size_t pushValue(lua_State *L, void *v);
    size_t pushValue(lua_State *L, lua_Integer v);
    size_t pushValue(lua_State *L, const std::string &v);
    size_t pushValue(lua_State *L, lua_Number v);
    size_t pushBool(lua_State *L, bool v);

    size_t setArgs(lua_State *L);
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
    bool getoption_gui(lua_State *L);
    lua_Integer getoption_camera_mode(lua_State *L);
    Camera_Param getoption_camera_param(lua_State *L);
    bool getoption_multi_object(lua_State *L);
    template<typename T, typename... Parms>
    lua_Number getvalue(lua_State *L, T target, Parms... parms);
    template<typename... Parms>
    lua_Integer setanchor(lua_State *L, const std::string &name, lua_Integer num, Parms... parms);
    template<typename... Parms>
    void getpixeldata(lua_State *L, Pixel_RGBA **out_data, Size_2D *out_size, Parms... parms);
    template<typename... Parms>
    void getpixeldata(lua_State *L, Pixel_RGBA **out_data, uint *out_w, uint *out_h, Parms... parms);
    void putpixeldata(lua_State *L, Pixel_RGBA *data);
}

void aut::getAULFunc(lua_State *L, const std::string &funcName) {
    lua_getglobal(L, "obj");
    lua_getfield(L, -1, funcName.c_str());
}

bool aut::getVariable(lua_State *L, const std::string &name, int max_Local_Hierarchy = UCHAR_MAX) {
    if (getLocalVariable(L, name, max_Local_Hierarchy))
        return true;
    if (getGlobalVariable(L, name))
        return true;
    return false;
}

bool aut::getGlobalVariable(lua_State *L, const std::string &name) {
    int stackNum_before = lua_gettop(L);
    lua_getglobal(L, name.c_str());
    if (lua_gettop(L) == stackNum_before)return false;
    return true;
}

bool aut::getLocalVariable(lua_State *L, const std::string &name, int max_Hierarchy) {
    for(size_t hi = 1; hi <= max_Hierarchy; hi++) {
    lua_Debug lDebug;
        if (!lua_getstack(L, hi, &lDebug))break;
    size_t i = 1;
    while(true){
        const char *vn = lua_getlocal(L, &lDebug, i);
            if (vn == nullptr)break;
        if (vn == name) return true;
        lua_pop(L, 1);
        i++;
    }
    }
    return false;
}

bool aut::getfield_Boolean(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    bool ret = static_cast<bool>(lua_toboolean(L, -1));
    lua_pop(L, 1);
    return ret;
}

lua_Integer aut::getfield_Integer(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

lua_Number aut::getfield_Number(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}

const char* aut::getfield_String(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    const char *ret = lua_tostring(L, -1);
    lua_pop(L, 1);
    return ret;
}

void* aut::getfield_Userdata(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    void *ret = lua_touserdata(L, -1);
    lua_pop(L, 1);
    return ret;
}

bool aut::gettable_Boolean(lua_State *L, int index, int tableIndex) {
    pushValue(L, index);
    lua_gettable(L, tableIndex - 1);
    bool ret = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return ret;
}

lua_Integer aut::gettable_Integer(lua_State *L, int index, int tableIndex) {
    pushValue(L, index);
    lua_gettable(L, tableIndex - 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

lua_Number aut::gettable_Number(lua_State *L, int index, int tableIndex) {
    pushValue(L, index);
    lua_gettable(L, tableIndex - 1);
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}

const char* aut::gettable_String(lua_State *L, int index, int tableIndex) {
    pushValue(L, index);
    lua_gettable(L, tableIndex - 1);
    const char *ret = lua_tostring(L, -1);
    lua_pop(L, 1);
    return ret;
}

void* aut::gettable_Userdata(lua_State *L, int index, int tableIndex) {
    pushValue(L, index);
    lua_gettable(L, tableIndex - 1);
    void *ret = lua_touserdata(L, -1);
    lua_pop(L, 1);
    return ret;
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

size_t aut::setArgs(lua_State *L) {
    return 0;
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
    lua_pop(L, 1);
}

void aut::draw(lua_State *L, double ox, double oy, double oz, double zoom, double alpha, double rx, double ry, double rz) {
    getAULFunc(L, "draw");
    size_t pushedNum = setArgs(L, ox, oy, oz, zoom, alpha, rx, ry, rz);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}

void aut::drawpoly(lua_State *L, double x0, double y0, double z0, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3,
             double u0, double v0, double u1, double v1, double u2, double v2, double u3, double v3, double alpha) {
    getAULFunc(L, "drawpoly");
    size_t pushedNum = setArgs(L, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3, u0, v0, u1, v1, u2, v2, u3, v3, alpha);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}

template <typename... Parms>
void aut::load(lua_State *L, Parms... parms) {
    aut::getAULFunc(L, "load");
    size_t pushedNum = setArgs(L, parms...);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}

template <typename... Parms>
void aut::setfont(lua_State *L, const std::string &name, double size, Parms... parms) {
    aut::getAULFunc(L, "setfont");
    size_t pushedNum = setArgs(L, name, size, parms...);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}

template <typename... Parms>
lua_Integer aut::rand(lua_State *L, lua_Integer st_num, lua_Integer ed_num, Parms... parms) {
    getAULFunc(L, "rand");
    size_t pushedNum = setArgs(L, st_num, ed_num, parms...);
    lua_call(L, pushedNum, 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
    return ret;
}

template <typename... Parms>
void aut::setoption(lua_State *L, const std::string &name, Parms... parms) {
    getAULFunc(L, "setoption");
    size_t pushedNum = setArgs(L, name, parms...);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}

lua_Integer aut::getoption_track_mode(lua_State *L, lua_Integer value) {
    getAULFunc(L, "getoption");
    size_t pushedNum = setArgs(L, "track_mode", value);
    lua_call(L, pushedNum, 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
    return ret;
}

lua_Integer aut::getoption_section_num(lua_State *L) {
    getAULFunc(L, "getoption");
    size_t pushedNum = setArgs(L, "section_num");
    lua_call(L, pushedNum, 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
    return ret;
}

const char* aut::getoption_script_name(lua_State *L, lua_Integer value, bool skip) {
    getAULFunc(L, "getoption");
    size_t pushedNum = setArgs(L, "script_name", value);
    pushedNum += pushBool(L, skip);
    lua_call(L, pushedNum, 1);
    const char *ret = lua_tostring(L, -1);
    lua_pop(L, 2);
    return ret;
}

bool aut::getoption_gui(lua_State *L) {
    getAULFunc(L, "getoption");
    size_t pushedNum = setArgs(L, "gui");
    lua_call(L, pushedNum, 1);
    int ret = lua_toboolean(L, -1);
    lua_pop(L, 2);
    return static_cast<bool>(ret);
}

lua_Integer aut::getoption_camera_mode(lua_State *L) {
    getAULFunc(L, "getoption");
    size_t pushedNum = setArgs(L, "camera_mode");
    lua_call(L, pushedNum, 1);
    int ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
    return ret;
}

aut::Camera_Param aut::getoption_camera_param(lua_State *L) {
    getAULFunc(L, "getoption");
    size_t pushedNum = setArgs(L, "camera_param");
    lua_call(L, pushedNum, 1);
    Camera_Param cp;
    cp.x  = getfield_Number(L, "x");
    cp.y  = getfield_Number(L, "y");
    cp.z  = getfield_Number(L, "z");
    cp.tx = getfield_Number(L, "tx");
    cp.ty = getfield_Number(L, "ty");
    cp.tz = getfield_Number(L, "tz");
    cp.rz = getfield_Number(L, "rz");
    cp.ux = getfield_Number(L, "ux");
    cp.uy = getfield_Number(L, "uy");
    cp.uz = getfield_Number(L, "uz");
    cp.d  = getfield_Number(L, "d");
    lua_pop(L, 2);
    return cp;
}

bool aut::getoption_multi_object(lua_State *L) {
    getAULFunc(L, "getoption");
    size_t pushedNum = setArgs(L, "multi_object");
    lua_call(L, pushedNum, 1);
    int ret = lua_toboolean(L, -1);
    lua_pop(L, 2);
    return static_cast<bool>(ret);
}

template<typename T, typename... Parms>
lua_Number aut::getvalue(lua_State *L, T target, Parms... parms) {
    getAULFunc(L, "getvalue");
    size_t pushedNum = setArgs(L, target, parms...);
    lua_call(L, pushedNum, 1);
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 2);
    return ret;
}

template<typename... Parms>
lua_Integer aut::setanchor(lua_State *L, const std::string &name, lua_Integer num, Parms... parms) {
    getAULFunc(L, "setanchor");
    size_t pushedNum = setArgs(L, name, num, parms...);
    lua_call(L, pushedNum, 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
    return ret;
}

template<typename... Parms>
void aut::getpixeldata(lua_State *L, Pixel_RGBA **out_data, Size_2D *out_size, Parms... parms) {
    getpixeldata(L, out_data, &out_size->w, &out_size->h, parms...);
}

template<typename... Parms>
void aut::getpixeldata(lua_State *L, Pixel_RGBA **out_data, uint *out_w, uint *out_h, Parms... parms) {
    getAULFunc(L, "getpixeldata");
    int pushedNum = setArgs(L, parms...);
    lua_call(L, pushedNum, 3);
    *out_h = lua_tointeger(L, -1);
    *out_w = lua_tointeger(L, -2);
    *out_data = reinterpret_cast<Pixel_RGBA*>(lua_touserdata(L, -3));
    lua_pop(L, pushedNum + 4);
}

void aut::putpixeldata(lua_State *L, Pixel_RGBA *data) {
    getAULFunc(L, "putpixeldata");
    lua_pushlightuserdata(L, data);
    lua_call(L, 1, 0);
    lua_pop(L, 1);
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_