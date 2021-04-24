/**
 * @file AUL_Wrapper.h
 * @author SEED264
 * @brief Wrappers for Lua functions in AviUtl
 */

/*
 * This file is part of AUL_Utils.
 *
 * The MIT License
 *
 * Copyright (c) 2019, 2021 SEED264
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

#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_

#include <cstddef>
#include <limits>
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <lua.hpp>
#include "./AUL_Enum.h"
#include "./AUL_Type.h"
#include "./AUL_UtilFunc.h"

namespace aut {
    /**
     * Stack functions in obj space on the top of the stack
     * 
     * @param[in] func_name The name of the function that want to get
     */
    void GetAULFunc(lua_State *L, const std::string &func_name);

    /**
     * Call obj.effect
     * 
     * @param[in] params Similar to obj.effect
     */
    template <typename... Params>
    void effect(lua_State *L, Params... params);
    /**
     * Call obj.draw
     * 
     * @param[in] ox Relative coord X
     * @param[in] oy Relative coord Y
     * @param[in] oz Relative coord Z
     * @param[in] zoom Enlargement rate (1.0 = 1x)
     * @param[in] alpha Opacity (0.0 = transparent / 1.0 = opaque)
     * @param[in] rx X-axis rotation angle (one rotation at 360.0)
     * @param[in] ry Y-axis rotation angle (one rotation at 360.0)
     * @param[in] rz Z-axis rotation angle (one rotation at 360.0)
     */
    void draw(lua_State *L, double ox = 0, double oy = 0, double oz = 0,
              double zoom = 1, double alpha = 1,
              double rx = 0, double ry = 0, double rz = 0);
    /**
     * Call obj.draw
     * 
     * @param[in] pos Relative coord
     * @param[in] zoom Enlargement rate (1.0 = 1x)
     * @param[in] alpha Opacity (0.0 = transparent / 1.0 = opaque)
     * @param[in] rot Rotation angle (one rotation at 360.0)
     */
    void draw(lua_State *L, glm::dvec3 pos = glm::dvec3(0),
              double zoom = 1, double alpha = 1, glm::dvec3 rot = glm::dvec3(0));
    /**
     * Call obj.drawpoly
     * 
     * @param[in] x0,y0,z0 Coordinates of vertices 0 of the rectangle
     * @param[in] x1,y1,z1 Coordinates of vertices 1 of the rectangle
     * @param[in] x2,y2,z2 Coordinates of vertices 2 of the rectangle
     * @param[in] x3,y3,z3 Coordinates of vertices 3 of the rectangle
     * @param[in] u0,v0 Image coordinates of the object corresponding to vertex 0
     * @param[in] u1,v1 Image coordinates of the object corresponding to vertex 1
     * @param[in] u2,v2 Image coordinates of the object corresponding to vertex 2
     * @param[in] u3,v3 Image coordinates of the object corresponding to vertex 3
     * @param[in] alpha Opacity (0.0 = transparent / 1.0 = opaque)
     */
    void drawpoly(lua_State *L,
                  double x0, double y0, double z0,
                  double x1, double y1, double z1,
                  double x2, double y2, double z2,
                  double x3, double y3, double z3,
                  double u0 = 0, double v0 = 0,
                  double u1 = USHRT_MAX, double v1 = 0,
                  double u2 = USHRT_MAX, double v2 = USHRT_MAX,
                  double u3 = 0, double v3 = USHRT_MAX,
                  double alpha = 1);
    /**
     * Call obj.drawpoly
     * 
     * @param[in] p0 Coordinates of vertices 0 of the rectangle
     * @param[in] p1 Coordinates of vertices 1 of the rectangle
     * @param[in] p2 Coordinates of vertices 2 of the rectangle
     * @param[in] p3 Coordinates of vertices 3 of the rectangle
     * @param[in] uv0 Image coordinates of the object corresponding to vertex 0
     * @param[in] uv1 Image coordinates of the object corresponding to vertex 1
     * @param[in] uv2 Image coordinates of the object corresponding to vertex 2
     * @param[in] uv3 Image coordinates of the object corresponding to vertex 3
     * @param[in] alpha Opacity (0.0 = transparent / 1.0 = opaque)
     */
    void drawpoly(lua_State *L,
                  glm::dvec3 p0, glm::dvec3 p1, glm::dvec3 p2, glm::dvec3 p3,
                  glm::dvec2 uv0 = glm::dvec2(0, 0),
                  glm::dvec2 uv1 = glm::dvec2(USHRT_MAX, 0),
                  glm::dvec2 uv2 = glm::dvec2(USHRT_MAX, USHRT_MAX),
                  glm::dvec2 uv3 = glm::dvec2(0, USHRT_MAX),
                  double alpha = 1);
    /**
     * Call obj.load
     * 
     * @param params Similar to obj.load
     */
    template <typename... Params>
    void load(lua_State *L, Params... params);
    /**
     * Call obj.setfont
     * @param[in] name Font name
     * @param[in] size Font size
     * @param[in] params Similar to obj.setfont
     */
    template <typename... Params>
    void setfont(lua_State *L, const std::string &name, double size, Params... params);
    /**
     * Call obj.rand
     * 
     * @param[in] st_num Minimum random number
     * @param[in] ed_num Maximum random number
     * @param[in] params Similar to obj.rand
     * 
     * @return lua_Integer Generated random number (integer)
     */
    template <typename... Params>
    lua_Integer rand(lua_State *L, lua_Integer st_num, lua_Integer ed_num, Params... params);
    /**
     * Call obj.setoption
     * 
     * @param[in] name Option name
     * @param[in] params Similar to obj.setoption
     */
    template <typename... Params>
    void setoption(lua_State *L, const std::string &name, Params... params);
    /**
     * Call obj.getoption("track_mode", ...)
     * 
     * @param[in] value Track bar number
     * 
     * @return lua_Integer Track bar movement mode
     */
    lua_Integer getoption_track_mode(lua_State *L, lua_Integer value);
    /**
     * Call obj.getoption("section_num")
     * 
     * @return lua_Integer Number of object intervals
     */
    lua_Integer getoption_section_num(lua_State *L);
    /**
     * Call obj.getoption("script_name"...)
     * 
     * @param[in] value Relative positions above and below the filter effect
     *                  (0 is self / minus is up / plus is down)
     * @param[in] skip Skip disabled filter effects (true = do / false <default> = not)
     * 
     * @return const char* Script name
     */
    const char* getoption_script_name(lua_State *L, lua_Integer value = 0, bool skip = false);
    /**
     * Call obj.getoption("gui")
     * 
     * @return bool GUI display status
     */
    bool getoption_gui(lua_State *L);
    /** 
     * Call obj.getoption("camera_mode")
     * 
     * @return lua_Integer Camera control status
     */
    lua_Integer getoption_camera_mode(lua_State *L);
    /**
     * Call obj.getoption("camera_param")
     * 
     * @return CameraParam Camera parameters
     */
    CameraParam getoption_camera_param(lua_State *L);
    /**
     * Call obj.getoption("multi_object")
     * 
     * @return bool true = valid / false = invalid
     */
    bool getoption_multi_object(lua_State *L);
    /**
     * Call obj.getvalue
     * 
     * @param[in] target Setting type
     * @param[in] params Similar to obj.getvalue
     * 
     * @return lua_Number Current object's setting value
     */
    template<typename T, typename... Params>
    lua_Number getvalue(lua_State *L, T target, Params... params);
    /**
     * Call obj.setanchor
     * 
     * @param[in] name Specifies the variable name that stores the coordinates
     *                 specified by --dialog.
     *                 * Specify the variable name as a character string
     * @param[in] num Specifies the number of anchor points.
     *                You can specify up to 16 anchors in total.
     * @param[in] params Similar to obj.setanchor
     * 
     * @return lua_Integer Number of anchor points acquired
     */
    template<typename... Params>
    lua_Integer setanchor(lua_State *L, const std::string &name, lua_Integer num,
                          Params... params);
    /**
     * Call obj.getaudio
     * 
     * @param[in] buf_name Specifies the table that receives the data.
     *                     If specified "nil", returns the contents of the table of
     *                     third return values
     * @param[in] file Audio file name (If you specify "audiobuffer",
     *                 you can get the audio data being edited)
     * @param[in] type Type of acquired data
     * @param[in] size Number of data to be acquired (may be less than the specified value)
     * @param[out] out_data_num Number of acquired data (null can be specified)
     * @param[out] out_sampling_rate Sampling rate (null can be specified)
     * 
     * @return std::vector<lua_Integer> Recieved data array
     */
    std::vector<lua_Integer> getaudio(lua_State *L, const std::string &buf_name,
                                      const std::string &file, const std::string &type,
                                      lua_Integer size, lua_Integer *out_data_num = nullptr,
                                      lua_Integer *out_sampling_rate = nullptr);
    /**
     * Call obj.filter
     * 
     * @param[in] name Filter name
     * @param[in] params Similar to obj.filter
     */
    template<typename... Params>
    void filter(lua_State *L, const std::string &name, Params... params);
    /**
     * Call obj.copybuffer
     * 
     * @param[in] dst Destination buffer
     * @param[in] src Source buffer
     * 
     * @return bool true = success / false = failure
     */
    bool copybuffer(lua_State *L, const std::string &dst, const std::string &src);
    /**
     * Call obj.getpixel(x,y, "col")
     * 
     * @param[in] x,y Coords of pixels to get
     * 
     * @return PixelCol Acquired pixel data
     */
    PixelCol getpixel_col(lua_State *L, lua_Integer x, lua_Integer y);
    /**
     * Call obj.getpixel(x,y, "rgb")
     * 
     * @param[in] x,y Coords of pixels to get
     * 
     * @return PixelRGBA Acquired pixel data
     */
    PixelRGBA getpixel_rgb(lua_State *L, lua_Integer x, lua_Integer y);
    /**
     * Call obj.getpixel(x,y, "yc")
     * 
     * @param[in] x,y Coords of pixels to get
     * 
     * @return PixelYC Acquired pixel data
     */
    PixelYC getpixel_yc(lua_State *L, lua_Integer x, lua_Integer y);
    /**
     * Call obj.getpixel()
     * 
     * @return Size2D Number of horizontal and vertical pixels
     */
    Size2D getpixel_size(lua_State *L);
    /**
     * Call obj.putpixel
     * 
     * @param[in] x,y Coords of pixels to put
     * @param[in] pix Pixel data to put
     */
    void putpixel(lua_State *L, lua_Integer x, lua_Integer y, PixelCol pix);
    /**
     * Call obj.putpixel
     * 
     * @param[in] x,y Coords of pixels to put
     * @param[in] pix Pixel data to put
     */
    void putpixel(lua_State *L, lua_Integer x, lua_Integer y, PixelRGBA pix);
    /**
     * Call obj.putpixel
     * 
     * @param[in] x,y Coords of pixels to put
     * @param[in] pix Pixel data to put
     */
    void putpixel(lua_State *L, lua_Integer x, lua_Integer y, PixelYC pix);
    /**
     * obj.copypixel
     * 
     * @param[in] dst_x,dst_y Coords of copy destination
     * @param[in] src_x,src_y Coords of copy source
     */
    void copypixel(lua_State *L, lua_Integer dst_x, lua_Integer dst_y,
                   lua_Integer src_x, lua_Integer src_y);
    /**
     * Call obj.pixeloption
     * 
     * @param[in] name Option name
     * @param[in] value Option value
     */
    void pixeloption(lua_State *L, const std::string &name, const std::string &value);
    /**
     * Call obj.pixeloption
     * 
     * @param[in] name Option name
     * @param[in] value Option value
     */
    void pixeloption(lua_State *L, const std::string &name, lua_Integer value);
    /**
     * Call obj.getpixeldata
     * 
     * @param[out] out_data Acquired image data
     * @param[out] out_size Acquired image size
     * @param[in] params Similar to obj.getpixeldata
     */
    template<typename... Params>
    void getpixeldata(lua_State *L, PixelRGBA **out_data, Size2D *out_size, Params... params);
    /**
     * Call obj.getpixeldata
     * 
     * @param[out] out_data Acquired image data
     * @param[out] out_w Acquired image width
     * @param[out] out_h Acquired image height
     * @param[in] params Similar to obj.getpixeldata
     */
    template<typename... Params>
    void getpixeldata(lua_State *L, PixelRGBA **out_data, uint *out_w, uint *out_h, Params... params);
    /**
     * Call obj.putpixeldata
     * 
     * @param[in] data Pixel datas to put
     */
    void putpixeldata(lua_State *L, PixelRGBA *data);
    /**
     * Call obj.getinfo("script_path")
     * 
     * @return std::string Script path
     */
    std::string getinfo_script_path(lua_State *L);
    /**
     * Callobj.getinfo("saving")
     * 
     * @return bool Is saving
     */
    bool getinfo_saving(lua_State *L);
    /**
     * Call obj.getinfo("image_max")
     * 
     * @return Size2D Max image size
     */
    Size2D getinfo_image_max(lua_State *L);
    /**
     * Call obj.interpolation
     * 
     * @param[in] time Time within 0 ~ 1
     * @param[in] x0 X coord of point 0
     * @param[in] x1 X coord of point 1
     * @param[in] x2 X coord of point 2
     * @param[in] x3 X coord of point 3
     */
    lua_Number interpolation(lua_State *L, lua_Number time,
                             lua_Number x0, lua_Number x1,
                             lua_Number x2, lua_Number x3);
    /**
     * Call obj.interpolation
     * 
     * @param[in] time Time within 0 ~ 1
     * @param[in] x0,y0 X, Y coord of point 0
     * @param[in] x1,y1 X, Y coord of point 1
     * @param[in] x2,y2 X, Y coord of point 2
     * @param[in] x3,y3 X, Y coord of point 3
     */
    glm::dvec2 interpolation(lua_State *L, lua_Number time,
                             lua_Number x0, lua_Number y0,
                             lua_Number x1, lua_Number y1,
                             lua_Number x2, lua_Number y2,
                             lua_Number x3, lua_Number y3);
    /**
     * Call obj.interpolation
     * 
     * @param[in] time Time within 0 ~ 1
     * @param[in] x0,y0,z0 X, Y, Z coord of point 0
     * @param[in] x1,y1,z1 X, Y, Z coord of point 1
     * @param[in] x2,y2,z2 X, Y, Z coord of point 2
     * @param[in] x3,y3,z3 X, Y, Z coord of point 3
     */
    glm::dvec3 interpolation(lua_State *L, lua_Number time,
                             lua_Number x0, lua_Number y0, lua_Number z0,
                             lua_Number x1, lua_Number y1, lua_Number z1,
                             lua_Number x2, lua_Number y2, lua_Number z2,
                             lua_Number x3, lua_Number y3, lua_Number z3);
    /**
     * Call obj.interpolation
     * 
     * @param[in] time Time within 0 ~ 1
     * @param[in] p0 Coord of point 0
     * @param[in] p1 Coord of point 1
     * @param[in] p2 Coord of point 2
     * @param[in] p3 Coord of point 3
     */
    glm::dvec2 interpolation(lua_State *L, lua_Number time,
                             const glm::dvec2 &p0, const glm::dvec2 &p1,
                             const glm::dvec2 &p2, const glm::dvec2 &p3);
    /**
     * Call obj.interpolation
     * 
     * @param[in] time Time within 0 ~ 1
     * @param[in] p0 Coord of point 0
     * @param[in] p1 Coord of point 1
     * @param[in] p2 Coord of point 2
     * @param[in] p3 Coord of point 3
     */
    glm::dvec3 interpolation(lua_State *L, lua_Number time,
                             const glm::dvec3 &p0, const glm::dvec3 &p1,
                             const glm::dvec3 &p2, const glm::dvec3 &p3);
}

inline void aut::GetAULFunc(lua_State *L, const std::string &func_name) {
    lua_getglobal(L, "obj");
    lua_getfield(L, -1, func_name.c_str());
}

template <typename... Params>
inline void aut::effect(lua_State *L, Params... params) {
    aut::GetAULFunc(L, "effect");
    size_t pushed_num = SetArgs(L, params...);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

inline void aut::draw(lua_State *L, double ox, double oy, double oz,
                      double zoom, double alpha,
                      double rx, double ry, double rz) {
    GetAULFunc(L, "draw");
    size_t pushed_num = SetArgs(L, ox, oy, oz, zoom, alpha, rx, ry, rz);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

inline void aut::draw(lua_State *L, glm::dvec3 pos,
                      double zoom, double alpha, glm::dvec3 rot) {
    GetAULFunc(L, "draw");
    size_t pushed_num = SetArgs(L, pos.x, pos.y, pos.z, zoom, alpha, rot.x, rot.y, rot.z);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

inline void aut::drawpoly(lua_State *L,
                          double x0, double y0, double z0,
                          double x1, double y1, double z1,
                          double x2, double y2, double z2,
                          double x3, double y3, double z3,
                          double u0, double v0, double u1, double v1,
                          double u2, double v2, double u3, double v3,
                          double alpha) {
    GetAULFunc(L, "drawpoly");
    size_t pushed_num = SetArgs(L, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3,
                                u0, v0, u1, v1, u2, v2, u3, v3, alpha);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

inline void aut::drawpoly(lua_State *L,
                          glm::dvec3 p0, glm::dvec3 p1,
                          glm::dvec3 p2, glm::dvec3 p3,
                          glm::dvec2 uv0, glm::dvec2 uv1,
                          glm::dvec2 uv2, glm::dvec2 uv3, double alpha) {
    drawpoly(L, p0.x, p0.y, p0.z, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z,
             uv0.x, uv0.y, uv1.x, uv1.y, uv2.x, uv2.y, uv3.x, uv3.y, alpha);
}

template <typename... Params>
inline void aut::load(lua_State *L, Params... params) {
    aut::GetAULFunc(L, "load");
    size_t pushed_num = SetArgs(L, params...);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

template <typename... Params>
inline void aut::setfont(lua_State *L, const std::string &name, double size,
                         Params... params) {
    aut::GetAULFunc(L, "setfont");
    size_t pushed_num = SetArgs(L, name, size, params...);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

template <typename... Params>
inline lua_Integer aut::rand(lua_State *L, lua_Integer st_num, lua_Integer ed_num,
                             Params... params) {
    GetAULFunc(L, "rand");
    size_t pushed_num = SetArgs(L, st_num, ed_num, params...);
    lua_call(L, pushed_num, 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
    return ret;
}

template <typename... Params>
inline void aut::setoption(lua_State *L, const std::string &name, Params... params) {
    GetAULFunc(L, "setoption");
    size_t pushed_num = SetArgs(L, name, params...);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

inline lua_Integer aut::getoption_track_mode(lua_State *L, lua_Integer value) {
    GetAULFunc(L, "getoption");
    size_t pushed_num = SetArgs(L, "track_mode", value);
    lua_call(L, pushed_num, 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
    return ret;
}

inline lua_Integer aut::getoption_section_num(lua_State *L) {
    GetAULFunc(L, "getoption");
    size_t pushed_num = SetArgs(L, "section_num");
    lua_call(L, pushed_num, 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
    return ret;
}

inline const char* aut::getoption_script_name(lua_State *L, lua_Integer value,
                                              bool skip) {
    GetAULFunc(L, "getoption");
    size_t pushed_num = SetArgs(L, "script_name", value);
    pushed_num += pushBool(L, skip);
    lua_call(L, pushed_num, 1);
    const char *ret = lua_tostring(L, -1);
    lua_pop(L, 2);
    return ret;
}

inline bool aut::getoption_gui(lua_State *L) {
    GetAULFunc(L, "getoption");
    size_t pushed_num = SetArgs(L, "gui");
    lua_call(L, pushed_num, 1);
    int ret = lua_toboolean(L, -1);
    lua_pop(L, 2);
    return static_cast<bool>(ret);
}

inline lua_Integer aut::getoption_camera_mode(lua_State *L) {
    GetAULFunc(L, "getoption");
    size_t pushed_num = SetArgs(L, "camera_mode");
    lua_call(L, pushed_num, 1);
    int ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
    return ret;
}

inline aut::CameraParam aut::getoption_camera_param(lua_State *L) {
    GetAULFunc(L, "getoption");
    size_t pushed_num = SetArgs(L, "camera_param");
    lua_call(L, pushed_num, 1);
    CameraParam cp;
    cp.x  = GetFieldNumber(L, "x");
    cp.y  = GetFieldNumber(L, "y");
    cp.z  = GetFieldNumber(L, "z");
    cp.tx = GetFieldNumber(L, "tx");
    cp.ty = GetFieldNumber(L, "ty");
    cp.tz = GetFieldNumber(L, "tz");
    cp.rz = GetFieldNumber(L, "rz");
    cp.ux = GetFieldNumber(L, "ux");
    cp.uy = GetFieldNumber(L, "uy");
    cp.uz = GetFieldNumber(L, "uz");
    cp.d  = GetFieldNumber(L, "d");
    lua_pop(L, 2);
    return cp;
}

inline bool aut::getoption_multi_object(lua_State *L) {
    GetAULFunc(L, "getoption");
    size_t pushed_num = SetArgs(L, "multi_object");
    lua_call(L, pushed_num, 1);
    int ret = lua_toboolean(L, -1);
    lua_pop(L, 2);
    return static_cast<bool>(ret);
}

template<typename T, typename... Params>
inline lua_Number aut::getvalue(lua_State *L, T target, Params... params) {
    GetAULFunc(L, "getvalue");
    size_t pushed_num = SetArgs(L, target, params...);
    lua_call(L, pushed_num, 1);
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 2);
    return ret;
}

template<typename... Params>
inline lua_Integer aut::setanchor(lua_State *L, const std::string &name,
                                  lua_Integer num, Params... params) {
    GetAULFunc(L, "setanchor");
    size_t pushed_num = SetArgs(L, name, num, params...);
    lua_call(L, pushed_num, 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 2);
    return ret;
}

inline std::vector<lua_Integer> aut::getaudio(lua_State *L, const std::string &buf_name,
                                              const std::string &file, const std::string &type,
                                              lua_Integer size, lua_Integer *out_data_num,
                                              lua_Integer *out_sampling_rate) {
    GetAULFunc(L, "getaudio");

    bool return_buffer = false;
    int returnNum = 2;
    if (buf_name == "nil" || !GetVariable(L, buf_name)) {
        return_buffer = true;
    } else if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        return_buffer = true;
    }
    if (return_buffer) {
        lua_pushnil(L);
        returnNum++;
    }
    size_t pushed_num = SetArgs(L, file, type, size) + 1;
    lua_call(L, pushed_num, returnNum);

    size_t bufSize = lua_tointeger(L, -returnNum);
    if (out_data_num != nullptr)
        *out_data_num = bufSize;
    if (out_sampling_rate != nullptr)
        *out_sampling_rate = lua_tointeger(L, -returnNum + 1);

    if (!return_buffer)
        GetVariable(L, buf_name);
    std::vector<lua_Integer> buf(bufSize);
    for (size_t i = 0; i < bufSize; i++) {
        buf[i] = GetTableInteger(L, i + 1);
    }

    lua_pop(L, 4);
    return buf;
}

template<typename... Params>
inline void aut::filter(lua_State *L, const std::string &name, Params... params) {
    GetAULFunc(L, "filter");
    size_t pushed_num = SetArgs(L, name, params...);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

inline bool aut::copybuffer(lua_State *L, const std::string &dst,
                            const std::string &src) {
    GetAULFunc(L, "copybuffer");
    size_t pushed_num = SetArgs(L, dst, src);
    lua_call(L, pushed_num, 1);
    bool ret = static_cast<bool>(lua_toboolean(L, -1));
    lua_pop(L, 2);
    return ret;
}

inline aut::PixelCol aut::getpixel_col(lua_State *L, lua_Integer x, lua_Integer y) {
    GetAULFunc(L, "getpixel");
    size_t pushed_num = SetArgs(L, x, y, "col");
    lua_call(L, pushed_num, 2);
    PixelCol ret;
    ret.col = static_cast<unsigned long>(lua_tointeger(L, -2));
    ret.a = static_cast<float>(lua_tonumber(L, -1));
    lua_pop(L, 3);
    return ret;
}

inline aut::PixelRGBA aut::getpixel_rgb(lua_State *L, lua_Integer x, lua_Integer y) {
    GetAULFunc(L, "getpixel");
    size_t pushed_num = SetArgs(L, x, y, "rgb");
    lua_call(L, pushed_num, 4);
    PixelRGBA ret;
    ret.r = static_cast<byte>(lua_tointeger(L, -4));
    ret.g = static_cast<byte>(lua_tointeger(L, -3));
    ret.b = static_cast<byte>(lua_tointeger(L, -2));
    ret.a = static_cast<byte>(lua_tointeger(L, -1));
    lua_pop(L, 5);
    return ret;
}

inline aut::PixelYC aut::getpixel_yc(lua_State *L, lua_Integer x, lua_Integer y) {
    GetAULFunc(L, "getpixel");
    size_t pushed_num = SetArgs(L, x, y, "yc");
    lua_call(L, pushed_num, 4);
    PixelYC ret;
    ret.y  = static_cast<short>(lua_tointeger(L, -4));
    ret.cb = static_cast<short>(lua_tointeger(L, -3));
    ret.cr = static_cast<short>(lua_tointeger(L, -2));
    ret.a  = static_cast<unsigned short>(lua_tointeger(L, -1));
    lua_pop(L, 5);
    return ret;
}

inline aut::Size2D aut::getpixel_size(lua_State *L) {
    GetAULFunc(L, "getpixel");
    lua_call(L, 0, 2);
    Size2D ret;
    ret.w = static_cast<unsigned int>(lua_tointeger(L, -2));
    ret.h = static_cast<unsigned int>(lua_tointeger(L, -1));
    lua_pop(L, 3);
    return ret;
}

inline void aut::putpixel(lua_State *L, lua_Integer x, lua_Integer y, PixelCol pix) {
    GetAULFunc(L, "putpixel");
    size_t pushed_num = SetArgs(L, x, y, static_cast<lua_Integer>(pix.col), pix.a);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}
inline void aut::putpixel(lua_State *L, lua_Integer x, lua_Integer y, PixelRGBA pix) {
    GetAULFunc(L, "putpixel");
    size_t pushed_num = SetArgs(L, x, y, pix.r, pix.g, pix.b, pix.a);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}
inline void aut::putpixel(lua_State *L, lua_Integer x, lua_Integer y, PixelYC pix) {
    GetAULFunc(L, "putpixel");
    size_t pushed_num = SetArgs(L, x, y, pix.y, pix.cb, pix.cr, pix.a);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

inline void aut::copypixel(lua_State *L, lua_Integer dst_x, lua_Integer dst_y,
                           lua_Integer src_x, lua_Integer src_y) {
    GetAULFunc(L, "copypixel");
    size_t pushed_num = SetArgs(L, dst_x, dst_y, src_x, src_y);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

inline void aut::pixeloption(lua_State *L, const std::string &name,
                             const std::string &value) {
    GetAULFunc(L, "pixeloption");
    size_t pushed_num = SetArgs(L, name, value);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

inline void aut::pixeloption(lua_State *L, const std::string &name, lua_Integer value) {
    GetAULFunc(L, "pixeloption");
    size_t pushed_num = SetArgs(L, name, value);
    lua_call(L, pushed_num, 0);
    lua_pop(L, 1);
}

template<typename... Params>
inline void aut::getpixeldata(lua_State *L, PixelRGBA **out_data, Size2D *out_size,
                              Params... params) {
    getpixeldata(L, out_data, &out_size->w, &out_size->h, params...);
}

template<typename... Params>
inline void aut::getpixeldata(lua_State *L, PixelRGBA **out_data,
                              uint *out_w, uint *out_h, Params... params) {
    GetAULFunc(L, "getpixeldata");
    int pushed_num = SetArgs(L, params...);
    lua_call(L, pushed_num, 3);
    *out_h = lua_tointeger(L, -1);
    *out_w = lua_tointeger(L, -2);
    *out_data = reinterpret_cast<PixelRGBA*>(lua_touserdata(L, -3));
    lua_pop(L, 4);
}

inline void aut::putpixeldata(lua_State *L, PixelRGBA *data) {
    GetAULFunc(L, "putpixeldata");
    lua_pushlightuserdata(L, data);
    lua_call(L, 1, 0);
    lua_pop(L, 1);
}

inline std::string aut::getinfo_script_path(lua_State *L) {
    GetAULFunc(L, "getinfo");
    size_t pushed_num = SetArgs(L, "script_path");
    lua_call(L, pushed_num, 1);
    std::string ret(lua_tostring(L, -1));
    lua_pop(L, 2);
    return ret;
}

inline bool aut::getinfo_saving(lua_State *L) {
    GetAULFunc(L, "getinfo");
    size_t pushed_num = SetArgs(L, "saving");
    lua_call(L, pushed_num, 1);
    bool ret = static_cast<bool>(lua_toboolean(L, -1));
    lua_pop(L, 2);
    return ret;
}

inline aut::Size2D aut::getinfo_image_max(lua_State *L) {
    GetAULFunc(L, "getinfo");
    size_t pushed_num = SetArgs(L, "image_max");
    lua_call(L, pushed_num, 2);
    Size2D ret;
    ret.w = static_cast<unsigned int>(lua_tointeger(L, -2));
    ret.h = static_cast<unsigned int>(lua_tointeger(L, -1));
    lua_pop(L, 3);
    return ret;
}

inline lua_Number aut::interpolation(lua_State *L, lua_Number time,
                                     lua_Number x0, lua_Number x1,
                                     lua_Number x2, lua_Number x3) {
    GetAULFunc(L, "interpolation");
    size_t pushed_num = SetArgs(L, time, x0, x1, x2, x3);
    lua_call(L, pushed_num, 1);
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 2);
    return ret;
}

inline glm::dvec2 aut::interpolation(lua_State *L, lua_Number time,
                                     lua_Number x0, lua_Number y0,
                                     lua_Number x1, lua_Number y1,
                                     lua_Number x2, lua_Number y2,
                                     lua_Number x3, lua_Number y3) {
    GetAULFunc(L, "interpolation");
    size_t pushed_num = SetArgs(L, time, x0, y0, x1, y1, x2, y2, x3, y3);
    lua_call(L, pushed_num, 2);
    glm::dvec2 ret;
    ret.x = lua_tonumber(L, -2);
    ret.y = lua_tonumber(L, -1);
    lua_pop(L, 3);
    return ret;
}

inline glm::dvec3 aut::interpolation(lua_State *L, lua_Number time,
                                     lua_Number x0, lua_Number y0, lua_Number z0,
                                     lua_Number x1, lua_Number y1, lua_Number z1,
                                     lua_Number x2, lua_Number y2, lua_Number z2,
                                     lua_Number x3, lua_Number y3, lua_Number z3) {
    GetAULFunc(L, "interpolation");
    size_t pushed_num = SetArgs(L, time, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3);
    lua_call(L, pushed_num, 3);
    glm::dvec3 ret;
    ret.x = lua_tonumber(L, -3);
    ret.y = lua_tonumber(L, -2);
    ret.z = lua_tonumber(L, -1);
    lua_pop(L, 4);
    return ret;
}

inline glm::dvec2 aut::interpolation(lua_State *L, lua_Number time,
                                     const glm::dvec2 &p0, const glm::dvec2 &p1,
                                     const glm::dvec2 &p2, const glm::dvec2 &p3) {
    return interpolation(L, time, p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
}

inline glm::dvec3 aut::interpolation(lua_State *L, lua_Number time,
                                     const glm::dvec3 &p0, const glm::dvec3 &p1,
                                     const glm::dvec3 &p2, const glm::dvec3 &p3) {
    return interpolation(L, time, p0.x, p0.y, p0.z, p1.x, p1.y, p1.z,
                         p2.x, p2.y, p2.z, p3.x, p3.y, p3.z);
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_WRAPPER_H_
