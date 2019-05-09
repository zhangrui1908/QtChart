//
//  cppToOc.hpp
//  RealTimeFilter
//
//  Created by Yeah on 2019/3/27.
//  Copyright © 2019 Yeah. All rights reserved.
//

#ifndef cppToOc_h
#define cppToOc_h
#define LENGTH 2500

#include <stdio.h>
#include "export.h"

static int inDataCount;
static int waveFilteringBuffer[LENGTH];

//#ifdef __cplusplus
//extern "C" {
//#endif

EXPORT_API void resetFiltrtBuffer();

EXPORT_API int* filter(int* in_data, int* out_data, int length);

//#ifdef __cplusplus
//}
//#endif /* end of __cplusplus */

#endif /* cppToOc_hpp */
