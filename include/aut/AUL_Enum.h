#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_ENUM_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_ENUM_H_

namespace aut {
    enum LuaVarStatus :int {
        kLuaVarNotFound = 0,
        kLuaVarLocal = 1,
        kLuaVarGlobal = 2
    };
}

#endif // _AUL_UTILS_INCLUDE_AUT_AUL_ENUM_H_