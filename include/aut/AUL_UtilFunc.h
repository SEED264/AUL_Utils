#ifndef _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_
#define _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_

#define _USE_MATH_DEFINES

#include <cmath>
#include "aut/AUL_Type.h"

namespace aut {
    inline double toRadian(double deg) {
        return deg * M_PI / 180;
    }
    inline double toDegree(double rad) {
        return rad * 180 / M_PI;
    }
}


#endif // _AUL_UTILS_INCLUDE_AUT_AUL_UTILFUNC_H_