#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_

#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>
#include <limits>
#include <string>
#include <vector>
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

    std::vector<lua_Integer> tableToArray_Integer(lua_State *L, const std::string &name);

    std::vector<glm::dvec2> tableToVec2(lua_State *L, const std::string &tableName, int maxNum = INT_MAX);
    std::vector<glm::dvec3> tableToVec3(lua_State *L, const std::string &tableName, int maxNum = INT_MAX);
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

std::vector<lua_Integer> aut::tableToArray_Integer(lua_State *L, const std::string &name) {
    std::vector<lua_Integer> outVec;
    auto vStatus = getVariable(L, name);
    if (vStatus != kLuaVarNotFound) {
        size_t tLen = lua_objlen(L, -1);
        outVec.resize(tLen);
        for(size_t i = 0; i < outVec.size(); i++) {
            outVec[i] = gettable_Integer(L, i+1);
        }
    }
    lua_pop(L, 1);
    return outVec;
}

std::vector<glm::dvec2> aut::tableToVec2(lua_State *L, const std::string &tableName, int maxNum) {
    std::vector<glm::dvec2> outVec;
    auto vStatus = getVariable(L, tableName);
    if (vStatus != kLuaVarNotFound) {
        size_t tLen = lua_objlen(L, -1);
        outVec.resize(std::ceil(static_cast<double>(tLen) / 2));
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
        outVec.resize(std::ceil(static_cast<double>(tLen) / 3));
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

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_
