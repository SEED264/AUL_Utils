#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_

#include <cstddef>
#include <limits>
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <lua.hpp>
#include "aut/AUL_Enum.h"
#include "aut/AUL_Type.h"
#include "aut/AUL_UtilFunc.h"

namespace aut {
    void getAULFunc(lua_State *L, const std::string &funcName);

    template <typename... Parms>
    void effect(lua_State *L, Parms... parms);
    void draw(lua_State *L, double ox = 0, double oy = 0, double oz = 0, double zoom = 1, double alpha = 1, double rx = 0, double ry = 0, double rz = 0);
    void drawpoly(lua_State *L, double x0, double y0, double z0, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3,
                  double u0 = 0, double v0 = 0, double u1 = USHRT_MAX, double v1 = 0, double u2 = USHRT_MAX, double v2 = USHRT_MAX, double u3 = 0, double v3 = USHRT_MAX, double alpha = 1);
    void drawpoly(lua_State *L, glm::dvec3 p0, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3,
                  glm::dvec2 uv0 = glm::dvec2(0, 0), glm::dvec2 uv1 = glm::dvec2(USHRT_MAX, 0), glm::dvec2 uv2 = glm::dvec2(USHRT_MAX, USHRT_MAX), glm::dvec2 uv3 = glm::dvec2(0, USHRT_MAX), double alpha = 1);
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
    std::vector<lua_Integer> getaudio(lua_State *L, const std::string &bufName, const std::string &file, const std::string &type, lua_Integer size, lua_Integer *out_dataNum = nullptr, lua_Integer *out_samplingRate = nullptr);
    template<typename... Parms>
    void filter(lua_State *L, const std::string &name, Parms... parms);
    bool copybuffer(lua_State *L, const std::string &dst, const std::string &src);
    Pixel_Col getpixel_col(lua_State *L, lua_Integer x, lua_Integer y);
    Pixel_RGBA getpixel_rgb(lua_State *L, lua_Integer x, lua_Integer y);
    Pixel_YC getpixel_yc(lua_State *L, lua_Integer x, lua_Integer y);
    Size_2D getpixel_size(lua_State *L);
    void putpixel(lua_State *L, lua_Integer x, lua_Integer y, Pixel_Col pix);
    void putpixel(lua_State *L, lua_Integer x, lua_Integer y, Pixel_RGBA pix);
    void putpixel(lua_State *L, lua_Integer x, lua_Integer y, Pixel_YC pix);
    void copypixel(lua_State *L, lua_Integer dst_x, lua_Integer dst_y, lua_Integer src_x, lua_Integer src_y);
    void pixeloption(lua_State *L, const std::string &name, const std::string &value);
    void pixeloption(lua_State *L, const std::string &name, lua_Integer value);
    template<typename... Parms>
    void getpixeldata(lua_State *L, Pixel_RGBA **out_data, Size_2D *out_size, Parms... parms);
    template<typename... Parms>
    void getpixeldata(lua_State *L, Pixel_RGBA **out_data, uint *out_w, uint *out_h, Parms... parms);
    void putpixeldata(lua_State *L, Pixel_RGBA *data);
    std::string getinfo_script_path(lua_State *L);
    bool getinfo_saving(lua_State *L);
    Size_2D getinfo_image_max(lua_State *L);
    lua_Number interpolation(lua_State *L, lua_Number time, lua_Number x0, lua_Number x1, lua_Number x2, lua_Number x3);
    glm::dvec2 interpolation(lua_State *L, lua_Number time, lua_Number x0, lua_Number y0, lua_Number x1, lua_Number y1, lua_Number x2, lua_Number y2, lua_Number x3, lua_Number y3);
    glm::dvec3 interpolation(lua_State *L, lua_Number time, lua_Number x0, lua_Number y0, lua_Number z0, lua_Number x1, lua_Number y1, lua_Number z1,
                            lua_Number x2, lua_Number y2, lua_Number z2, lua_Number x3, lua_Number y3, lua_Number z3);
    glm::dvec2 interpolation(lua_State *L, lua_Number time, const glm::dvec2 &p0, const glm::dvec2 &p1, const glm::dvec2 &p2, const glm::dvec2 &p3);
    glm::dvec3 interpolation(lua_State *L, lua_Number time, const glm::dvec3 &p0, const glm::dvec3 &p1, const glm::dvec3 &p2, const glm::dvec3 &p3);
}

void aut::getAULFunc(lua_State *L, const std::string &funcName) {
    lua_getglobal(L, "obj");
    lua_getfield(L, -1, funcName.c_str());
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

void aut::drawpoly(lua_State *L, glm::dvec3 p0, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3,
                   glm::dvec2 uv0 = glm::dvec2(0, 0), glm::dvec2 uv1 = glm::dvec2(USHRT_MAX, 0), glm::dvec2 uv2 = glm::dvec2(USHRT_MAX, USHRT_MAX), glm::dvec2 uv3 = glm::dvec2(0, USHRT_MAX), double alpha = 1) {
    drawpoly(L, p0.x, p0.y, p0.z, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p2.y, p3.z,
             uv0.x, uv0.y, uv1.x, uv1.y, uv2.x, uv2.y, uv3.x, uv3.y, alpha);
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

std::vector<lua_Integer> aut::getaudio(lua_State *L, const std::string &bufName, const std::string &file, const std::string &type, lua_Integer size, lua_Integer *out_dataNum, lua_Integer *out_samplingRate) {
    getAULFunc(L, "getaudio");

    bool return_buffer = false;
    int returnNum = 2;
    if (bufName == "nil" || !getVariable(L, bufName)) {
        return_buffer = true;
    } else if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return_buffer = true;
    }
    if (return_buffer) {
        lua_pushnil(L);
        returnNum++;
    }
    size_t pushedNum = setArgs(L, file, type, size) + 1;
    lua_call(L, pushedNum, returnNum);

    size_t bufSize = lua_tointeger(L, -returnNum);
    if (out_dataNum != nullptr)
        *out_dataNum = bufSize;
    if (out_samplingRate != nullptr)
        *out_samplingRate = lua_tointeger(L, -returnNum + 1);

    if (!return_buffer)
        getVariable(L, bufName);
    std::vector<lua_Integer> buf(bufSize);
    for (size_t i = 0; i < bufSize; i++) {
        buf[i] = gettable_Integer(L, i + 1);
    }

    lua_pop(L, 4);
    return buf;
}

template<typename... Parms>
void aut::filter(lua_State *L, const std::string &name, Parms... parms) {
    getAULFunc(L, "filter");
    size_t pushedNum = setArgs(L, name, parms...);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}

bool aut::copybuffer(lua_State *L, const std::string &dst, const std::string &src) {
    getAULFunc(L, "copybuffer");
    size_t pushedNum = setArgs(L, dst, src);
    lua_call(L, pushedNum, 1);
    bool ret = static_cast<bool>(lua_toboolean(L, -1));
    lua_pop(L, 2);
    return ret;
}

aut::Pixel_Col aut::getpixel_col(lua_State *L, lua_Integer x, lua_Integer y) {
    getAULFunc(L, "getpixel");
    size_t pushedNum = setArgs(L, x, y, "col");
    lua_call(L, pushedNum, 2);
    Pixel_Col ret;
    ret.col = static_cast<unsigned long>(lua_tointeger(L, -2));
    ret.a = static_cast<float>(lua_tonumber(L, -1));
    lua_pop(L, 3);
    return ret;
}

aut::Pixel_RGBA aut::getpixel_rgb(lua_State *L, lua_Integer x, lua_Integer y) {
    getAULFunc(L, "getpixel");
    size_t pushedNum = setArgs(L, x, y, "rgb");
    lua_call(L, pushedNum, 4);
    Pixel_RGBA ret;
    ret.r = static_cast<byte>(lua_tointeger(L, -4));
    ret.g = static_cast<byte>(lua_tointeger(L, -3));
    ret.b = static_cast<byte>(lua_tointeger(L, -2));
    ret.a = static_cast<byte>(lua_tointeger(L, -1));
    lua_pop(L, 5);
    return ret;
}

aut::Pixel_YC aut::getpixel_yc(lua_State *L, lua_Integer x, lua_Integer y) {
    getAULFunc(L, "getpixel");
    size_t pushedNum = setArgs(L, x, y, "yc");
    lua_call(L, pushedNum, 4);
    Pixel_YC ret;
    ret.y  = static_cast<short>(lua_tointeger(L, -4));
    ret.cb = static_cast<short>(lua_tointeger(L, -3));
    ret.cr = static_cast<short>(lua_tointeger(L, -2));
    ret.a  = static_cast<unsigned short>(lua_tointeger(L, -1));
    lua_pop(L, 5);
    return ret;
}

aut::Size_2D aut::getpixel_size(lua_State *L) {
    getAULFunc(L, "getpixel");
    lua_call(L, 0, 2);
    Size_2D ret;
    ret.w = static_cast<unsigned int>(lua_tointeger(L, -2));
    ret.h = static_cast<unsigned int>(lua_tointeger(L, -1));
    lua_pop(L, 3);
    return ret;
}

void aut::putpixel(lua_State *L, lua_Integer x, lua_Integer y, Pixel_Col pix) {
    getAULFunc(L, "putpixel");
    size_t pushedNum = setArgs(L, x, y, static_cast<lua_Integer>(pix.col), pix.a);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}
void aut::putpixel(lua_State *L, lua_Integer x, lua_Integer y, Pixel_RGBA pix) {
    getAULFunc(L, "putpixel");
    size_t pushedNum = setArgs(L, x, y, pix.r, pix.g, pix.b, pix.a);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}
void aut::putpixel(lua_State *L, lua_Integer x, lua_Integer y, Pixel_YC pix) {
    getAULFunc(L, "putpixel");
    size_t pushedNum = setArgs(L, x, y, pix.y, pix.cb, pix.cr, pix.a);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}

void aut::copypixel(lua_State *L, lua_Integer dst_x, lua_Integer dst_y, lua_Integer src_x, lua_Integer src_y) {
    getAULFunc(L, "copypixel");
    size_t pushedNum = setArgs(L, dst_x, dst_y, src_x, src_y);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}

void aut::pixeloption(lua_State *L, const std::string &name, const std::string &value) {
    getAULFunc(L, "pixeloption");
    size_t pushedNum = setArgs(L, name, value);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
}

void aut::pixeloption(lua_State *L, const std::string &name, lua_Integer value) {
    getAULFunc(L, "pixeloption");
    size_t pushedNum = setArgs(L, name, value);
    lua_call(L, pushedNum, 0);
    lua_pop(L, 1);
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
    lua_pop(L, 4);
}

void aut::putpixeldata(lua_State *L, Pixel_RGBA *data) {
    getAULFunc(L, "putpixeldata");
    lua_pushlightuserdata(L, data);
    lua_call(L, 1, 0);
    lua_pop(L, 1);
}

std::string aut::getinfo_script_path(lua_State *L) {
    getAULFunc(L, "getinfo");
    size_t pushedNum = setArgs(L, "script_path");
    lua_call(L, pushedNum, 1);
    std::string ret(lua_tostring(L, -1));
    lua_pop(L, 2);
    return ret;
}

bool aut::getinfo_saving(lua_State *L) {
    getAULFunc(L, "getinfo");
    size_t pushedNum = setArgs(L, "saving");
    lua_call(L, pushedNum, 1);
    bool ret = static_cast<bool>(lua_toboolean(L, -1));
    lua_pop(L, 2);
    return ret;
}

aut::Size_2D aut::getinfo_image_max(lua_State *L) {
    getAULFunc(L, "getinfo");
    size_t pushedNum = setArgs(L, "image_max");
    lua_call(L, pushedNum, 2);
    Size_2D ret;
    ret.w = static_cast<unsigned int>(lua_tointeger(L, -2));
    ret.h = static_cast<unsigned int>(lua_tointeger(L, -1));
    lua_pop(L, 3);
    return ret;
}

lua_Number aut::interpolation(lua_State *L, lua_Number time, lua_Number x0, lua_Number x1, lua_Number x2, lua_Number x3) {
    getAULFunc(L, "interpolation");
    size_t pushedNum = setArgs(L, time, x0, x1, x2, x3);
    lua_call(L, pushedNum, 1);
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 2);
    return ret;
}

glm::dvec2 aut::interpolation(lua_State *L, lua_Number time, lua_Number x0, lua_Number y0, lua_Number x1, lua_Number y1, lua_Number x2, lua_Number y2, lua_Number x3, lua_Number y3) {
    getAULFunc(L, "interpolation");
    size_t pushedNum = setArgs(L, time, x0, y0, x1, y1, x2, y2, x3, y3);
    lua_call(L, pushedNum, 2);
    glm::dvec2 ret;
    ret.x = lua_tonumber(L, -2);
    ret.y = lua_tonumber(L, -1);
    lua_pop(L, 3);
    return ret;
}

glm::dvec3 aut::interpolation(lua_State *L, lua_Number time, lua_Number x0, lua_Number y0, lua_Number z0, lua_Number x1, lua_Number y1, lua_Number z1,
                              lua_Number x2, lua_Number y2, lua_Number z2, lua_Number x3, lua_Number y3, lua_Number z3) {
    getAULFunc(L, "interpolation");
    size_t pushedNum = setArgs(L, time, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3);
    lua_call(L, pushedNum, 3);
    glm::dvec3 ret;
    ret.x = lua_tonumber(L, -3);
    ret.y = lua_tonumber(L, -2);
    ret.z = lua_tonumber(L, -1);
    lua_pop(L, 4);
    return ret;
}

glm::dvec2 aut::interpolation(lua_State *L, lua_Number time, const glm::dvec2 &p0, const glm::dvec2 &p1, const glm::dvec2 &p2, const glm::dvec2 &p3) {
    return interpolation(L, time, p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

glm::dvec3 aut::interpolation(lua_State *L, lua_Number time, const glm::dvec3 &p0, const glm::dvec3 &p1, const glm::dvec3 &p2, const glm::dvec3 &p3) {
    return interpolation(L, time, p0.x, p0.y, p0.z, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_
