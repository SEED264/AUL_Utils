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

#include <cmath>
#include <limits>
#include <string>
#include <vector>
#include <Windows.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <lua.hpp>
#include "aut/AUL_Enum.h"
#include "aut/AUL_Type.h"

namespace aut {
    static const double pi = 3.14159265358979323846;
    inline double ToRadian(double deg) {
        return deg * pi / 180;
    }
    inline double ToDegree(double rad) {
        return rad * 180 / pi;
    }
    // Luaの変数を取得する関数
    // ローカル->グローバルの順に探し、LuaVarStatusで探索の結果を返す
    // 見つかった場合は、変数はスタックトップに積まれる
    LuaVarStatus GetVariable(lua_State *L, const std::string &name, size_t max_local_hierarchy = UCHAR_MAX);
    // グローバル変数を取得する関数
    // 変数が見つかった場合はtrue、見つからなかった(取得した中身がnilであった)場合はfalseを返す
    // 見つかった場合は、変数はスタックトップに積まれる
    bool GetGlobalVariable(lua_State *L, const std::string &name);
    // ローカル変数を取得する関数
    // 変数が見つかった場合はtrue、見つからなかった場合はfalseを返す
    // 見つかった場合は、変数はスタックトップに積まれる
    bool GetLocalVariable(lua_State *L, const std::string &name, size_t max_hierarchy = UCHAR_MAX);

    // スタックの指定の位置に積まれたテーブルからnameを指定してbool値を取得する関数
    bool GetFieldBoolean(lua_State *L, const std::string &name, int table_index = -1);
    // スタックの指定の位置に積まれたテーブルからnameを指定して整数を取得する関数
    lua_Integer GetFieldInteger(lua_State *L, const std::string &name, int table_index = -1);
    // スタックの指定の位置に積まれたテーブルからnameを指定して浮動小数点数を取得する関数
    lua_Number GetFieldNumber(lua_State *L, const std::string &name, int table_index = -1);
    // スタックの指定の位置に積まれたテーブルからnameを指定して文字列を取得する関数
    const char* GetFieldString(lua_State *L, const std::string &name, int table_index = -1);
    // スタックの指定の位置に積まれたテーブルからnameを指定してユーザーデータのポインタを取得する関数
    void* GetFieldUserdata(lua_State *L, const std::string &name, int table_index = -1);

    // スタックの指定の位置に積まれたテーブルからindexを指定してbool値を取得する関数
    bool GetTableBoolean(lua_State *L, int index, int table_index = -1);
    // スタックの指定の位置に積まれたテーブルからindexを指定して整数を取得する関数
    lua_Integer GetTableInteger(lua_State *L, int index, int table_index = -1);
    // スタックの指定の位置に積まれたテーブルからindexを指定して浮動小数点数を取得する関数
    lua_Number GetTableNumber(lua_State *L, int index, int table_index = -1);
    // スタックの指定の位置に積まれたテーブルからindexを指定して文字列を取得する関数
    const char* GetTableString(lua_State *L, int index, int table_index = -1);
    // スタックの指定の位置に積まれたテーブルからindexを指定してユーザーデータのポインタを取得する関数
    void* GetTableUserdata(lua_State *L, int index, int table_index = -1);

    // スタックトップにvecの配列の内容をbool値としてコピーしたテーブルを作成する関数
    template<typename T>
    void PushArrayBoolean(lua_State *L, std::vector<T> &vec);
    // スタックトップにvecの配列の内容を整数としてコピーしたテーブルを作成する関数
    template<typename T>
    void PushArrayInteger(lua_State *L, std::vector<T> &vec);
    // スタックトップにvecの配列の内容を浮動小数点数としてコピーしたテーブルを作成する関数
    template<typename T>
    void PushArrayNumber(lua_State *L, std::vector<T> &vec);
    // スタックトップにvecの配列の内容を文字列としてコピーしたテーブルを作成する関数
    void PushArrayString(lua_State *L, std::vector<std::string> &vec);
    // スタックトップにvecの配列の内容を文字列としてコピーしたテーブルを作成する関数
    void PushArrayString(lua_State *L, std::vector<const char*> &vec);

    // スタックトップにユーザーデータのポインタを積む関数
    size_t PushValue(lua_State *L, void *v);
    // スタックトップに整数を積む関数
    size_t PushValue(lua_State *L, lua_Integer v);
    // スタックトップに整数を積む関数
    size_t PushValue(lua_State *L, char v);
    // スタックトップに整数を積む関数
    size_t PushValue(lua_State *L, short v);
    // スタックトップに整数を積む関数
    size_t PushValue(lua_State *L, long v);
    // スタックトップに整数を積む関数
    size_t PushValue(lua_State *L, unsigned char v);
    // スタックトップに整数を積む関数
    size_t PushValue(lua_State *L, unsigned short v);
    // スタックトップに整数を積む関数
    size_t PushValue(lua_State *L, unsigned int v);
    // スタックトップに整数を積む関数
    size_t PushValue(lua_State *L, unsigned long v);
    // スタックトップに文字列を積む関数
    size_t PushValue(lua_State *L, const std::string &v);
    // スタックトップに文字列を積む関数
    size_t PushValue(lua_State *L, const char *v);
    // スタックトップに浮動小数点数を積む関数
    size_t PushValue(lua_State *L, lua_Number v);
    // スタックトップにbool値を積む関数
    size_t pushBool(lua_State *L, bool v);

    // スタックトップに引数を積む関数
    // 実際に積んだ引数の数を返す
    size_t SetArgs(lua_State *L);
    // スタックトップに引数を積む関数
    // 実際に積んだ引数の数を返す
    template <typename T>
    size_t SetArgs(lua_State *L, T value);
    // スタックトップに引数を積む関数
    // 実際に積んだ引数の数を返す
    template <typename T, typename... Parms>
    size_t SetArgs(lua_State *L, T value, Parms... parms);

    // 指定したテーブルの内容をbool値としてvectorにコピーする関数
    std::vector<bool> ToArrayBoolean(lua_State *L, int table_index = -1);
    // 指定したテーブルの内容を整数としてvectorにコピーする関数
    std::vector<lua_Integer> ToArrayInteger(lua_State *L, int table_index = -1);
    // 指定したテーブルの内容を浮動小数点数としてvectorにコピーする関数
    std::vector<lua_Number> ToArrayNumber(lua_State *L, int table_index = -1);
    // 指定したテーブルの内容を文字列としてvectorにコピーする関数
    std::vector<std::string> ToArrayString(lua_State *L, int table_index = -1);

    // 指定した名前のテーブルの内容をbool値としてvectorにコピーする関数
    std::vector<bool> ToArrayBoolean(lua_State *L, const std::string &name);
    // 指定した名前のテーブルの内容を整数としてvectorにコピーする関数
    std::vector<lua_Integer> ToArrayInteger(lua_State *L, const std::string &name);
    // 指定した名前のテーブルの内容を浮動小数点数としてvectorにコピーする関数
    std::vector<lua_Number> ToArrayNumber(lua_State *L, const std::string &name);
    // 指定した名前のテーブルの内容を文字列としてvectorにコピーする関数
    std::vector<std::string> ToArrayString(lua_State *L, const std::string &name);

    // 指定した名前のテーブルの内容をdvec2としてvectorにコピーする関数
    std::vector<glm::dvec2> TableToVec2(lua_State *L, const std::string &table_name, int max_num = INT_MAX);
    // 指定した名前のテーブルの内容をdvec3としてvectorにコピーする関数
    std::vector<glm::dvec3> TableToVec3(lua_State *L, const std::string &table_name, int max_num = INT_MAX);

    // 引数の値を文字列として結合する関数
    template <typename T>
    std::string CombineAsString(T value);
    // 引数の値を文字列として結合する関数
    std::string CombineAsString(const char *value);
    // 引数の値を文字列として結合する関数
    std::string CombineAsString(std::string &value);
    // 引数の値を文字列として結合する関数
    template <typename T, typename... Parms>
    std::string CombineAsString(T value, Parms... parms);

    // 受け取った引数をデバッグ出力する関数
    template <typename... T>
    void DebugPrint(T... values);
}

inline aut::LuaVarStatus aut::GetVariable(lua_State *L, const std::string &name, size_t max_local_hierarchy) {
    if (GetLocalVariable(L, name, max_local_hierarchy))
        return kAutLuaVarLocal;
    if (GetGlobalVariable(L, name))
        return kAutLuaVarGlobal;
    return kAutLuaVarNotFound;
}

inline bool aut::GetGlobalVariable(lua_State *L, const std::string &name) {
    lua_getglobal(L, name.c_str());
    if (lua_isnil(L, -1)) {
        lua_pop(L, 1);
        return false;
    }
    return true;
}

inline bool aut::GetLocalVariable(lua_State *L, const std::string &name, size_t max_hierarchy) {
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

inline bool aut::GetFieldBoolean(lua_State *L, const std::string &name, int table_index) {
    lua_getfield(L, table_index, name.c_str());
    bool ret = static_cast<bool>(lua_toboolean(L, -1));
    lua_pop(L, 1);
    return ret;
}

inline lua_Integer aut::GetFieldInteger(lua_State *L, const std::string &name, int table_index) {
    lua_getfield(L, table_index, name.c_str());
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

inline lua_Number aut::GetFieldNumber(lua_State *L, const std::string &name, int table_index) {
    lua_getfield(L, table_index, name.c_str());
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}

inline const char* aut::GetFieldString(lua_State *L, const std::string &name, int table_index) {
    lua_getfield(L, table_index, name.c_str());
    const char *ret = lua_tostring(L, -1);
    lua_pop(L, 1);
    return ret;
}

inline void* aut::GetFieldUserdata(lua_State *L, const std::string &name, int table_index) {
    lua_getfield(L, table_index, name.c_str());
    void *ret = lua_touserdata(L, -1);
    lua_pop(L, 1);
    return ret;
}

inline bool aut::GetTableBoolean(lua_State *L, int index, int table_index) {
    PushValue(L, static_cast<lua_Integer>(index));
    lua_gettable(L, table_index - 1);
    bool ret = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return ret;
}

inline lua_Integer aut::GetTableInteger(lua_State *L, int index, int table_index) {
    PushValue(L, static_cast<lua_Integer>(index));
    lua_gettable(L, table_index - 1);
    lua_Integer ret = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return ret;
}

inline lua_Number aut::GetTableNumber(lua_State *L, int index, int table_index) {
    PushValue(L, static_cast<lua_Integer>(index));
    lua_gettable(L, table_index - 1);
    lua_Number ret = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return ret;
}

inline const char* aut::GetTableString(lua_State *L, int index, int table_index) {
    PushValue(L, static_cast<lua_Integer>(index));
    lua_gettable(L, table_index - 1);
    const char *ret = lua_tostring(L, -1);
    lua_pop(L, 1);
    return ret;
}

inline void* aut::GetTableUserdata(lua_State *L, int index, int table_index) {
    PushValue(L, static_cast<lua_Integer>(index));
    lua_gettable(L, table_index - 1);
    void *ret = lua_touserdata(L, -1);
    lua_pop(L, 1);
    return ret;
}

template<typename T>
inline void aut::PushArrayBoolean(lua_State *L, std::vector<T> &vec) {
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
inline void aut::PushArrayInteger(lua_State *L, std::vector<T> &vec) {
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
inline void aut::PushArrayNumber(lua_State *L, std::vector<T> &vec) {
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

inline void aut::PushArrayString(lua_State *L, std::vector<std::string> &vec) {
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

inline void aut::PushArrayString(lua_State *L, std::vector<const char*> &vec) {
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

inline size_t aut::PushValue(lua_State *L, void *v) {
    lua_pushlightuserdata(L, v);
    return 1;
}

inline size_t aut::PushValue(lua_State *L, lua_Integer v) {
    lua_pushinteger(L, v);
    return 1;
}

inline size_t aut::PushValue(lua_State *L, char v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

inline size_t aut::PushValue(lua_State *L, short v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

inline size_t aut::PushValue(lua_State *L, long v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

inline size_t aut::PushValue(lua_State *L, unsigned char v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

inline size_t aut::PushValue(lua_State *L, unsigned short v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

inline size_t aut::PushValue(lua_State *L, unsigned int v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

inline size_t aut::PushValue(lua_State *L, unsigned long v) {
    lua_pushinteger(L, static_cast<lua_Integer>(v));
    return 1;
}

inline size_t aut::PushValue(lua_State *L, const std::string &v) {
    lua_pushstring(L, v.c_str());
    return 1;
}

inline size_t aut::PushValue(lua_State *L, const char *v) {
    lua_pushstring(L, v);
    return 1;
}

inline size_t aut::PushValue(lua_State *L, lua_Number v) {
    lua_pushnumber(L, v);
    return 1;
}

inline size_t aut::pushBool(lua_State *L, bool v) {
    lua_pushboolean(L, v);
    return 1;
}

inline size_t aut::SetArgs(lua_State *L) {
    return 0;
}

template <typename T>
inline size_t aut::SetArgs(lua_State *L, T value) {
    return aut::PushValue(L, value);
}

template <typename T, typename... Parms>
inline size_t aut::SetArgs(lua_State *L, T value, Parms... parms) {
    size_t pushed_num = aut::PushValue(L, value);
    return SetArgs(L, parms...) + pushed_num;
}

inline std::vector<bool> aut::ToArrayBoolean(lua_State *L, int table_index) {
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

inline std::vector<lua_Integer> aut::ToArrayInteger(lua_State *L, int table_index) {
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

inline std::vector<lua_Number> aut::ToArrayNumber(lua_State *L, int table_index) {
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

inline std::vector<std::string> aut::ToArrayString(lua_State *L, int table_index) {
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

inline std::vector<bool> aut::ToArrayBoolean(lua_State *L, const std::string &name) {
    auto v_status = GetVariable(L, name);
    if (v_status != kAutLuaVarNotFound) {
        std::vector<bool> out_vec = ToArrayBoolean(L);
        lua_pop(L, 1);
        return out_vec;
    }
    return std::vector<bool>();
}

inline std::vector<lua_Integer> aut::ToArrayInteger(lua_State *L, const std::string &name) {
    auto v_status = GetVariable(L, name);
    if (v_status != kAutLuaVarNotFound) {
        std::vector<lua_Integer> out_vec = ToArrayInteger(L);
        lua_pop(L, 1);
        return out_vec;
    }
    return std::vector<lua_Integer>();
}

inline std::vector<lua_Number> aut::ToArrayNumber(lua_State *L, const std::string &name) {
    auto v_status = GetVariable(L, name);
    if (v_status != kAutLuaVarNotFound) {
        std::vector<lua_Number> out_vec = ToArrayNumber(L);
        lua_pop(L, 1);
        return out_vec;
    }
    return std::vector<lua_Number>();
}

inline std::vector<std::string> aut::ToArrayString(lua_State *L, const std::string &name) {
    auto v_status = GetVariable(L, name);
    if (v_status != kAutLuaVarNotFound) {
        std::vector<std::string> out_vec = ToArrayString(L);
        lua_pop(L, 1);
        return out_vec;
    }
    return std::vector<std::string>();
}

inline std::vector<glm::dvec2> aut::TableToVec2(lua_State *L, const std::string &table_name, int max_num) {
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

inline std::vector<glm::dvec3> aut::TableToVec3(lua_State *L, const std::string &table_name, int max_num) {
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
inline std::string aut::CombineAsString(T value) {
    return std::to_string(value);
}

inline std::string aut::CombineAsString(const char *value) {
    return std::string(value);
}

inline std::string aut::CombineAsString(std::string &value) {
    return value;
}

template <typename T, typename... Parms>
inline std::string aut::CombineAsString(T value, Parms... parms) {
    return CombineAsString(value) + CombineAsString(parms...);
}

template <typename... T>
inline void aut::DebugPrint(T... values) {
    std::string str = CombineAsString(values...);
    OutputDebugString(str.c_str());
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_
