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

#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_

#define _USE_MATH_DEFINES
#define NOMINMAX

#include <math.h>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <debugapi.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <lua.hpp>
#include "aut/AUL_Type.h"

namespace aut {
    inline double ToRadian(double deg) {
        return deg * M_PI / 180;
    }
    inline double ToDegree(double rad) {
        return rad * 180 / M_PI;
    }
    LuaVarStatus GetVariable(lua_State *L, const std::string &name, size_t max_local_hierarchy = UCHAR_MAX);
    bool GetGlobalVariable(lua_State *L, const std::string &name);
    bool GetLocalVariable(lua_State *L, const std::string &name, size_t max_hierarchy = UCHAR_MAX);

    bool GetFieldBoolean(lua_State *L, const std::string &name);
    lua_Integer GetFieldInteger(lua_State *L, const std::string &name);
    lua_Number GetFieldNumber(lua_State *L, const std::string &name);
    const char* GetFieldString(lua_State *L, const std::string &name);
    void* GetFieldUserdata(lua_State *L, const std::string &name);

    bool GetTableBoolean(lua_State *L, int index, int table_index = -1);
    lua_Integer GetTableInteger(lua_State *L, int index, int table_index = -1);
    lua_Number GetTableNumber(lua_State *L, int index, int table_index = -1);
    const char* GetTableString(lua_State *L, int index, int table_index = -1);
    void* GetTableUserdata(lua_State *L, int index, int table_index = -1);

    template<typename T>
    void PushArrayBoolean(lua_State *L, std::vector<T> vec);
    template<typename T>
    void PushArrayInteger(lua_State *L, std::vector<T> vec);
    template<typename T>
    void PushArrayNumber(lua_State *L, std::vector<T> vec);
    void PushArrayString(lua_State *L, std::vector<std::string> vec);
    void PushArrayString(lua_State *L, std::vector<const char*> vec);

    size_t PushValue(lua_State *L, void *v);
    size_t PushValue(lua_State *L, lua_Integer v);
    size_t PushValue(lua_State *L, unsigned char v);
    size_t PushValue(lua_State *L, unsigned short v);
    size_t PushValue(lua_State *L, unsigned int v);
    size_t PushValue(lua_State *L, unsigned long v);
    size_t PushValue(lua_State *L, const std::string &v);
    size_t PushValue(lua_State *L, const char *v);
    size_t PushValue(lua_State *L, lua_Number v);
    size_t pushBool(lua_State *L, bool v);

    size_t SetArgs(lua_State *L);
    template <typename T>
    size_t SetArgs(lua_State *L, T value);
    template <typename T, typename... Parms>
    size_t SetArgs(lua_State *L, T value, Parms... parms);

    std::vector<bool> ToArrayBoolean(lua_State *L, int table_index = -1);
    std::vector<lua_Integer> ToArrayInteger(lua_State *L, int table_index = -1);
    std::vector<lua_Number> ToArrayNumber(lua_State *L, int table_index = -1);
    std::vector<std::string> ToArrayString(lua_State *L, int table_index = -1);

    std::vector<bool> ToArrayBoolean(lua_State *L, const std::string &name);
    std::vector<lua_Integer> ToArrayInteger(lua_State *L, const std::string &name);
    std::vector<lua_Number> ToArrayNumber(lua_State *L, const std::string &name);
    std::vector<std::string> ToArrayString(lua_State *L, const std::string &name);

    std::vector<glm::dvec2> TableToVec2(lua_State *L, const std::string &table_name, int max_num = INT_MAX);
    std::vector<glm::dvec3> TableToVec3(lua_State *L, const std::string &table_name, int max_num = INT_MAX);

    template <typename T>
    std::string CombineAsString(T value);
    std::string CombineAsString(const char *value);
    std::string CombineAsString(std::string &value);
    template <typename T, typename... Parms>
    std::string CombineAsString(T value, Parms... parms);

    template <typename... T>
    void DebugPrint(T... values);
}

aut::LuaVarStatus aut::GetVariable(lua_State *L, const std::string &name, size_t max_local_hierarchy) {
    if (GetLocalVariable(L, name, max_local_hierarchy))
        return kAutLuaVarLocal;
    if (GetGlobalVariable(L, name))
        return kAutLuaVarGlobal;
    return kAutLuaVarNotFound;
}

bool aut::GetGlobalVariable(lua_State *L, const std::string &name) {
    lua_getglobal(L, name.c_str());
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        return false;
    }
    return true;
}

bool aut::GetLocalVariable(lua_State *L, const std::string &name, size_t max_hierarchy) {
    for(size_t hi = 1; hi <= max_hierarchy; hi++) {
        lua_Debug l_debug;
        if (!lua_getstack(L, hi, &l_debug))break;
        size_t i = 1;
        while(true) {
            const char *vn = lua_getlocal(L, &l_debug, i);
            if (vn == nullptr)break;
            if (vn == name)return true;
            lua_pop(L, 1);
            i++;
        }
    }
    return false;
}

bool aut::GetFieldBoolean(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    bool ret = static_cast<bool>(lua_toboolean(L, -1));
    lua_pop(L, 1);
    return ret;
}

lua_Integer aut::GetFieldInteger(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

lua_Number aut::GetFieldNumber(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}

const char* aut::GetFieldString(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    const char *ret = lua_tostring(L, -1);
    lua_pop(L, 1);
    return ret;
}

void* aut::GetFieldUserdata(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    void *ret = lua_touserdata(L, -1);
    lua_pop(L, 1);
    return ret;
}

bool aut::GetTableBoolean(lua_State *L, int index, int table_index) {
    PushValue(L, index);
    lua_gettable(L, table_index - 1);
    bool ret = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return ret;
}

lua_Integer aut::GetTableInteger(lua_State *L, int index, int table_index) {
    PushValue(L, index);
    lua_gettable(L, table_index - 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

lua_Number aut::GetTableNumber(lua_State *L, int index, int table_index) {
    PushValue(L, index);
    lua_gettable(L, table_index - 1);
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}

const char* aut::GetTableString(lua_State *L, int index, int table_index) {
    PushValue(L, index);
    lua_gettable(L, table_index - 1);
    const char *ret = lua_tostring(L, -1);
    lua_pop(L, 1);
    return ret;
}

void* aut::GetTableUserdata(lua_State *L, int index, int table_index) {
    PushValue(L, index);
    lua_gettable(L, table_index - 1);
    void *ret = lua_touserdata(L, -1);
    lua_pop(L, 1);
    return ret;
}

template<typename T>
void aut::PushArrayBoolean(lua_State *L, std::vector<T> vec) {
    size_t v_size = vec.size();
    if (v_size != 0) {
        lua_createtable(L, v_size, 0);
        for(size_t i = 0; i < v_size; i++) {
            PushValue(L, static_cast<lua_Integer>(i + 1));
            pushBool(L, static_cast<bool>(vec[i]));
            lua_settable(L, -3);
        }
    }
}

template<typename T>
void aut::PushArrayInteger(lua_State *L, std::vector<T> vec) {
    size_t v_size = vec.size();
    if (v_size != 0) {
        lua_createtable(L, v_size, 0);
        for(size_t i = 0; i < v_size; i++) {
            PushValue(L, static_cast<lua_Integer>(i + 1));
            PushValue(L, static_cast<lua_Integer>(vec[i]));
            lua_settable(L, -3);
        }
    }
}

template<typename T>
void aut::PushArrayNumber(lua_State *L, std::vector<T> vec) {
    size_t v_size = vec.size();
    if (v_size != 0) {
        lua_createtable(L, v_size, 0);
        for(size_t i = 0; i < v_size; i++) {
            PushValue(L, static_cast<lua_Integer>(i + 1));
            PushValue(L, static_cast<lua_Number>(vec[i]));
            lua_settable(L, -3);
        }
    }
}

void aut::PushArrayString(lua_State *L, std::vector<std::string> vec) {
    size_t v_size = vec.size();
    if (v_size != 0) {
        lua_createtable(L, v_size, 0);
        for(size_t i = 0; i < v_size; i++) {
            PushValue(L, static_cast<lua_Integer>(i + 1));
            PushValue(L, vec[i]);
            lua_settable(L, -3);
        }
    }
}

void aut::PushArrayString(lua_State *L, std::vector<const char*> vec) {
    size_t v_size = vec.size();
    if (v_size != 0) {
        lua_createtable(L, v_size, 0);
        for(size_t i = 0; i < v_size; i++) {
            PushValue(L, static_cast<lua_Integer>(i + 1));
            PushValue(L, vec[i]);
            lua_settable(L, -3);
        }
    }
}

size_t aut::PushValue(lua_State *L, void *v) {
    lua_pushlightuserdata(L, v);
    return 1;
}

size_t aut::PushValue(lua_State *L, lua_Integer v) {
    lua_pushinteger(L, v);
    return 1;
}

size_t aut::PushValue(lua_State *L, unsigned char v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

size_t aut::PushValue(lua_State *L, unsigned short v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

size_t aut::PushValue(lua_State *L, unsigned int v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

size_t aut::PushValue(lua_State *L, unsigned long v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

size_t aut::PushValue(lua_State *L, const std::string &v) {
    lua_pushstring(L, v.c_str());
    return 1;
}

size_t aut::PushValue(lua_State *L, const char *v) {
    lua_pushstring(L, v);
    return 1;
}

size_t aut::PushValue(lua_State *L, lua_Number v) {
    lua_pushnumber(L, v);
    return 1;
}

size_t aut::pushBool(lua_State *L, bool v) {
    lua_pushboolean(L, v);
    return 1;
}

size_t aut::SetArgs(lua_State *L) {
    return 0;
}

template <typename T>
size_t aut::SetArgs(lua_State *L, T value) {
    return aut::PushValue(L, value);
}

template <typename T, typename... Parms>
size_t aut::SetArgs(lua_State *L, T value, Parms... parms) {
    size_t pushed_num = aut::PushValue(L, value);
    return SetArgs(L, parms...) + pushed_num;
}

std::vector<bool> aut::ToArrayBoolean(lua_State *L, int table_index) {
    std::vector<bool> out_vec;
    if (lua_istable(L, table_index)) {
        size_t tLen = lua_objlen(L, table_index);
        out_vec.resize(tLen);
        for(size_t i = 0; i < out_vec.size(); i++) {
            out_vec[i] = GetTableBoolean(L, i+1, table_index);
        }
    }
    return out_vec;
}

std::vector<lua_Integer> aut::ToArrayInteger(lua_State *L, int table_index) {
    std::vector<lua_Integer> out_vec;
    if (lua_istable(L, table_index)) {
        size_t tLen = lua_objlen(L, table_index);
        out_vec.resize(tLen);
        for(size_t i = 0; i < out_vec.size(); i++) {
            out_vec[i] = GetTableInteger(L, i+1, table_index);
        }
    }
    return out_vec;
}

std::vector<lua_Number> aut::ToArrayNumber(lua_State *L, int table_index) {
    std::vector<lua_Number> out_vec;
    if (lua_istable(L, table_index)) {
        size_t tLen = lua_objlen(L, table_index);
        out_vec.resize(tLen);
        for(size_t i = 0; i < out_vec.size(); i++) {
            out_vec[i] = GetTableNumber(L, i+1, table_index);
        }
    }
    return out_vec;
}

std::vector<std::string> aut::ToArrayString(lua_State *L, int table_index) {
    std::vector<std::string> out_vec;
    if (lua_istable(L, table_index)) {
        size_t tLen = lua_objlen(L, table_index);
        out_vec.resize(tLen);
        for(size_t i = 0; i < out_vec.size(); i++) {
            out_vec[i] = std::string(GetTableString(L, i+1, table_index));
        }
    }
    return out_vec;
}

std::vector<bool> aut::ToArrayBoolean(lua_State *L, const std::string &name) {
    auto v_status = GetVariable(L, name);
    if (v_status != kAutLuaVarNotFound) {
        std::vector<bool> out_vec = ToArrayBoolean(L);
        lua_pop(L, 1);
        return out_vec;
    }
    return std::vector<bool>();
}

std::vector<lua_Integer> aut::ToArrayInteger(lua_State *L, const std::string &name) {
    auto v_status = GetVariable(L, name);
    if (v_status != kAutLuaVarNotFound) {
        std::vector<lua_Integer> out_vec = ToArrayInteger(L);
        lua_pop(L, 1);
        return out_vec;
    }
    return std::vector<lua_Integer>();
}

std::vector<lua_Number> aut::ToArrayNumber(lua_State *L, const std::string &name) {
    auto v_status = GetVariable(L, name);
    if (v_status != kAutLuaVarNotFound) {
        std::vector<lua_Number> out_vec = ToArrayNumber(L);
        lua_pop(L, 1);
        return out_vec;
    }
    return std::vector<lua_Number>();
}

std::vector<std::string> aut::ToArrayString(lua_State *L, const std::string &name) {
    auto v_status = GetVariable(L, name);
    if (v_status != kAutLuaVarNotFound) {
        std::vector<std::string> out_vec = ToArrayString(L);
        lua_pop(L, 1);
        return out_vec;
    }
    return std::vector<std::string>();
}

std::vector<glm::dvec2> aut::TableToVec2(lua_State *L, const std::string &table_name, int max_num) {
    std::vector<glm::dvec2> out_vec;
    auto v_status = GetVariable(L, table_name);
    if (v_status != kAutLuaVarNotFound) {
        size_t t_len = lua_objlen(L, -1);
        out_vec.resize(static_cast<size_t>(std::ceil(static_cast<double>(t_len) / 2)));
        for (size_t i = 0; i < out_vec.size(); i++) {
            glm::dvec2 v;
            for(size_t j = 0; j < 2; j++) {
                size_t index = 2 * i + j + 1;
                if (index > t_len)break;
                v[j] = GetTableNumber(L, index);
            }
            out_vec[i] = v;
        }
    }
    lua_pop(L, 1);
    return out_vec;
}

std::vector<glm::dvec3> aut::TableToVec3(lua_State *L, const std::string &table_name, int max_num) {
    std::vector<glm::dvec3> out_vec;
    auto v_status = GetVariable(L, table_name);
    if (v_status != kAutLuaVarNotFound) {
        size_t t_len = lua_objlen(L, -1);
        out_vec.resize(static_cast<size_t>(std::ceil(static_cast<double>(t_len) / 3)));
        for (size_t i = 0; i < out_vec.size(); i++) {
            glm::dvec3 v;
            for(size_t j = 0; j < 3; j++) {
                size_t index = 3 * i + j + 1;
                if (index > t_len)break;
                v[j] = GetTableNumber(L, index);
            }
            out_vec[i] = v;
        }
    }
    lua_pop(L, 1);
    return out_vec;
}

template <typename T>
std::string aut::CombineAsString(T value) {
    return std::to_string(value);
}

std::string aut::CombineAsString(const char *value) {
    return std::string(value);
}

std::string aut::CombineAsString(std::string &value) {
    return value;
}

template <typename T, typename... Parms>
std::string aut::CombineAsString(T value, Parms... parms) {
    return CombineAsString(value) + CombineAsString(parms...);
}

template <typename... T>
void aut::DebugPrint(T... values) {
    std::string str = CombineAsString(values...);
    OutputDebugString(str.c_str());
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_
