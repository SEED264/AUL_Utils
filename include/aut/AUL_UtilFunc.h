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
    inline double toRadian(double deg) {
        return deg * M_PI / 180;
    }
    inline double toDegree(double rad) {
        return rad * 180 / M_PI;
    }
    LuaVarStatus getVariable(lua_State *L, const std::string &name, size_t max_Local_Hierarchy = UCHAR_MAX);
    bool getGlobalVariable(lua_State *L, const std::string &name);
    bool getLocalVariable(lua_State *L, const std::string &name, size_t max_Hierarchy = UCHAR_MAX);

    bool getField_Boolean(lua_State *L, const std::string &name);
    lua_Integer getField_Integer(lua_State *L, const std::string &name);
    lua_Number getField_Number(lua_State *L, const std::string &name);
    const char* getField_String(lua_State *L, const std::string &name);
    void* getField_Userdata(lua_State *L, const std::string &name);

    bool gettable_Boolean(lua_State *L, int index, int tableIndex = -1);
    lua_Integer gettable_Integer(lua_State *L, int index, int tableIndex = -1);
    lua_Number gettable_Number(lua_State *L, int index, int tableIndex = -1);
    const char* gettable_String(lua_State *L, int index, int tableIndex = -1);
    void* gettable_Userdata(lua_State *L, int index, int tableIndex = -1);

    template<typename T>
    void pushArray_Boolean(lua_State *L, std::vector<T> vec);
    template<typename T>
    void pushArray_Integer(lua_State *L, std::vector<T> vec);
    template<typename T>
    void pushArray_Number(lua_State *L, std::vector<T> vec);
    void pushArray_String(lua_State *L, std::vector<std::string> vec);
    void pushArray_String(lua_State *L, std::vector<const char*> vec);

    size_t pushValue(lua_State *L, void *v);
    size_t pushValue(lua_State *L, lua_Integer v);
    size_t pushValue(lua_State *L, const std::string &v);
    size_t pushValue(lua_State *L, const char *v);
    size_t pushValue(lua_State *L, lua_Number v);
    size_t pushBool(lua_State *L, bool v);

    size_t setArgs(lua_State *L);
    template <typename T>
    size_t setArgs(lua_State *L, T value);
    template <typename T, typename... Parms>
    size_t setArgs(lua_State *L, T value, Parms... parms);

    std::vector<bool> toArray_Boolean(lua_State *L, int tableIndex = -1);
    std::vector<lua_Integer> toArray_Integer(lua_State *L, int tableIndex = -1);
    std::vector<lua_Number> toArray_Number(lua_State *L, int tableIndex = -1);
    std::vector<std::string> toArray_String(lua_State *L, int tableIndex = -1);

    std::vector<bool> toArray_Boolean(lua_State *L, const std::string &name);
    std::vector<lua_Integer> toArray_Integer(lua_State *L, const std::string &name);
    std::vector<lua_Number> toArray_Number(lua_State *L, const std::string &name);
    std::vector<std::string> toArray_String(lua_State *L, const std::string &name);

    std::vector<glm::dvec2> tableToVec2(lua_State *L, const std::string &tableName, int maxNum = INT_MAX);
    std::vector<glm::dvec3> tableToVec3(lua_State *L, const std::string &tableName, int maxNum = INT_MAX);

    template <typename T>
    std::string combineAsString(T value);
    std::string combineAsString(const char *value);
    std::string combineAsString(std::string &value);
    template <typename T, typename... Parms>
    std::string combineAsString(T value, Parms... parms);

    template <typename... T>
    void debug_print(T... values);
}

aut::LuaVarStatus aut::getVariable(lua_State *L, const std::string &name, size_t max_Local_Hierarchy) {
    if (getLocalVariable(L, name, max_Local_Hierarchy))
        return kLuaVarLocal;
    if (getGlobalVariable(L, name))
        return kLuaVarGlobal;
    return kLuaVarNotFound;
}

bool aut::getGlobalVariable(lua_State *L, const std::string &name) {
    lua_getglobal(L, name.c_str());
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        return false;
    }
    return true;
}

bool aut::getLocalVariable(lua_State *L, const std::string &name, size_t max_Hierarchy) {
    for(size_t hi = 1; hi <= max_Hierarchy; hi++) {
        lua_Debug lDebug;
        if (!lua_getstack(L, hi, &lDebug))break;
        size_t i = 1;
        while(true) {
            const char *vn = lua_getlocal(L, &lDebug, i);
            if (vn == nullptr)break;
            if (vn == name)return true;
            lua_pop(L, 1);
            i++;
        }
    }
    return false;
}

bool aut::getField_Boolean(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    bool ret = static_cast<bool>(lua_toboolean(L, -1));
    lua_pop(L, 1);
    return ret;
}

lua_Integer aut::getField_Integer(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

lua_Number aut::getField_Number(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}

const char* aut::getField_String(lua_State *L, const std::string &name) {
    lua_getfield(L, -1, name.c_str());
    const char *ret = lua_tostring(L, -1);
    lua_pop(L, 1);
    return ret;
}

void* aut::getField_Userdata(lua_State *L, const std::string &name) {
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

template<typename T>
void aut::pushArray_Boolean(lua_State *L, std::vector<T> vec) {
    size_t v_size = vec.size();
    if (v_size != 0) {
        lua_createtable(L, v_size, 0);
        for(size_t i = 0; i < v_size; i++) {
            pushValue(L, static_cast<lua_Integer>(i + 1));
            pushBool(L, static_cast<bool>(vec[i]));
            lua_settable(L, -3);
        }
    }
}

template<typename T>
void aut::pushArray_Integer(lua_State *L, std::vector<T> vec) {
    size_t v_size = vec.size();
    if (v_size != 0) {
        lua_createtable(L, v_size, 0);
        for(size_t i = 0; i < v_size; i++) {
            pushValue(L, static_cast<lua_Integer>(i + 1));
            pushValue(L, static_cast<lua_Integer>(vec[i]));
            lua_settable(L, -3);
        }
    }
}

template<typename T>
void aut::pushArray_Number(lua_State *L, std::vector<T> vec) {
    size_t v_size = vec.size();
    if (v_size != 0) {
        lua_createtable(L, v_size, 0);
        for(size_t i = 0; i < v_size; i++) {
            pushValue(L, static_cast<lua_Integer>(i + 1));
            pushValue(L, static_cast<lua_Number>(vec[i]));
            lua_settable(L, -3);
        }
    }
}

void aut::pushArray_String(lua_State *L, std::vector<std::string> vec) {
    size_t v_size = vec.size();
    if (v_size != 0) {
        lua_createtable(L, v_size, 0);
        for(size_t i = 0; i < v_size; i++) {
            pushValue(L, static_cast<lua_Integer>(i + 1));
            pushValue(L, vec[i]);
            lua_settable(L, -3);
        }
    }
}

void aut::pushArray_String(lua_State *L, std::vector<const char*> vec) {
    size_t v_size = vec.size();
    if (v_size != 0) {
        lua_createtable(L, v_size, 0);
        for(size_t i = 0; i < v_size; i++) {
            pushValue(L, static_cast<lua_Integer>(i + 1));
            pushValue(L, vec[i]);
            lua_settable(L, -3);
        }
    }
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

size_t aut::pushValue(lua_State *L, const char *v) {
    lua_pushstring(L, v);
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

std::vector<bool> aut::toArray_Boolean(lua_State *L, int tableIndex) {
    std::vector<bool> outVec;
    if (lua_istable(L, tableIndex)) {
        size_t tLen = lua_objlen(L, tableIndex);
        outVec.resize(tLen);
        for(size_t i = 0; i < outVec.size(); i++) {
            outVec[i] = gettable_Boolean(L, i+1, tableIndex);
        }
    }
    return outVec;
}

std::vector<lua_Integer> aut::toArray_Integer(lua_State *L, int tableIndex) {
    std::vector<lua_Integer> outVec;
    if (lua_istable(L, tableIndex)) {
        size_t tLen = lua_objlen(L, tableIndex);
        outVec.resize(tLen);
        for(size_t i = 0; i < outVec.size(); i++) {
            outVec[i] = gettable_Integer(L, i+1, tableIndex);
        }
    }
    return outVec;
}

std::vector<lua_Number> aut::toArray_Number(lua_State *L, int tableIndex) {
    std::vector<lua_Number> outVec;
    if (lua_istable(L, tableIndex)) {
        size_t tLen = lua_objlen(L, tableIndex);
        outVec.resize(tLen);
        for(size_t i = 0; i < outVec.size(); i++) {
            outVec[i] = gettable_Number(L, i+1, tableIndex);
        }
    }
    return outVec;
}

std::vector<std::string> aut::toArray_String(lua_State *L, int tableIndex) {
    std::vector<std::string> outVec;
    if (lua_istable(L, tableIndex)) {
        size_t tLen = lua_objlen(L, tableIndex);
        outVec.resize(tLen);
        for(size_t i = 0; i < outVec.size(); i++) {
            outVec[i] = std::string(gettable_String(L, i+1, tableIndex));
        }
    }
    return outVec;
}

std::vector<bool> aut::toArray_Boolean(lua_State *L, const std::string &name) {
    auto vStatus = getVariable(L, name);
    if (vStatus != kLuaVarNotFound) {
        std::vector<bool> outVec = toArray_Boolean(L);
        lua_pop(L, 1);
        return outVec;
    }
    return std::vector<bool>();
}

std::vector<lua_Integer> aut::toArray_Integer(lua_State *L, const std::string &name) {
    auto vStatus = getVariable(L, name);
    if (vStatus != kLuaVarNotFound) {
        std::vector<lua_Integer> outVec = toArray_Integer(L);
        lua_pop(L, 1);
        return outVec;
    }
    return std::vector<lua_Integer>();
}

std::vector<lua_Number> aut::toArray_Number(lua_State *L, const std::string &name) {
    auto vStatus = getVariable(L, name);
    if (vStatus != kLuaVarNotFound) {
        std::vector<lua_Number> outVec = toArray_Number(L);
        lua_pop(L, 1);
        return outVec;
    }
    return std::vector<lua_Number>();
}

std::vector<std::string> aut::toArray_String(lua_State *L, const std::string &name) {
    auto vStatus = getVariable(L, name);
    if (vStatus != kLuaVarNotFound) {
        std::vector<std::string> outVec = toArray_String(L);
        lua_pop(L, 1);
        return outVec;
    }
    return std::vector<std::string>();
}

std::vector<glm::dvec2> aut::tableToVec2(lua_State *L, const std::string &tableName, int maxNum) {
    std::vector<glm::dvec2> outVec;
    auto vStatus = getVariable(L, tableName);
    if (vStatus != kLuaVarNotFound) {
        size_t tLen = lua_objlen(L, -1);
        outVec.resize(static_cast<size_t>(std::ceil(static_cast<double>(tLen) / 2)));
        for (size_t i = 0; i < outVec.size(); i++) {
            glm::dvec2 v;
            for(size_t j = 0; j < 2; j++) {
                size_t index = 2 * i + j + 1;
                if (index > tLen)break;
                v[j] = gettable_Number(L, index);
            }
            outVec[i] = v;
        }
    }
    lua_pop(L, 1);
    return outVec;
}

std::vector<glm::dvec3> aut::tableToVec3(lua_State *L, const std::string &tableName, int maxNum) {
    std::vector<glm::dvec3> outVec;
    auto vStatus = getVariable(L, tableName);
    if (vStatus != kLuaVarNotFound) {
        size_t tLen = lua_objlen(L, -1);
        outVec.resize(static_cast<size_t>(std::ceil(static_cast<double>(tLen) / 3)));
        for (size_t i = 0; i < outVec.size(); i++) {
            glm::dvec3 v;
            for(size_t j = 0; j < 3; j++) {
                size_t index = 3 * i + j + 1;
                if (index > tLen)break;
                v[j] = gettable_Number(L, index);
            }
            outVec[i] = v;
        }
    }
    lua_pop(L, 1);
    return outVec;
}

template <typename T>
std::string aut::combineAsString(T value) {
    return std::to_string(value);
}

std::string aut::combineAsString(std::string &value) {
    return value;
}

std::string aut::combineAsString(const char *value) {
    return std::string(value);
}

template <typename T, typename... Parms>
std::string aut::combineAsString(T value, Parms... parms) {
    return combineAsString(value) + combineAsString(parms...);
}

template <typename... T>
void aut::debug_print(T... values) {
    std::string str = combineAsString(values...);
    OutputDebugString(str.c_str());
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_
