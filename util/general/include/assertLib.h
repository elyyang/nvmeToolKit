/********************************************************************************************
*  _  ___   ____  __    _____         _ _  ___ _   
* | \| \ \ / /  \/  |__|_   _|__  ___| | |/ (_) |_ 
* | .` |\ V /| |\/| / -_)| |/ _ \/ _ \ | ' <| |  _|
* |_|\_| \_/ |_|  |_\___||_|\___/\___/_|_|\_\_|\__|
*                                                              
* MIT License
* 
* Copyright (c) 2026 Eric L. Yang
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
* 
* https://github.com/elyyang
* elyyang@gmail.com
*
*********************************************************************************************/

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// user defined assert options

#ifndef ENABLE_NVME_DBG_ASSERT
#define ENABLE_NVME_DBG_ASSERT              (1)
#endif

#ifndef NVME_DBG_ASSERT_NOTIFICATION_OPTION
#define NVME_DBG_ASSERT_NOTIFICATION_OPTION (1)
#endif

#ifndef NVME_DBG_ASSERT_ACTION_OPTION
#define NVME_DBG_ASSERT_ACTION_OPTION       (2)
#endif

#if ENABLE_NVME_DBG_ASSERT

#define NVME_DBG_ASSERT(condition, message)                              _assert_condition((!(condition)), message)
#define NVME_DBG_ASSERT_IF_TRUE(condition, message)                      _assert_condition((condition), message)
#define NVME_DBG_ASSERT_IF_EQUAL(actual, expected, message)              _assert_condition((actual==expected), message)
#define NVME_DBG_ASSERT_IF_NOT_EQUAL(actual, expected, message)          _assert_condition((actual!=expected), message)
#define NVME_DBG_ASSERT_IF_GREATER_THAN(actual, threshold, message)      _assert_condition((actual>threshold), message)
#define NVME_DBG_ASSERT_IF_LESSER_THAN(actual, threshold, message)       _assert_condition((actual<threshold), message)
#define NVME_DBG_ASSERT_IF_GREATER_OR_EQUAL(actual, threshold, message)  _assert_condition((actual>=threshold), message)
#define NVME_DBG_ASSERT_IF_LESSER_OR_EQUAL(actual, threshold, message)   _assert_condition((actual<=threshold), message)

// assert condition
#define _assert_condition(condition, message) \
do{                                           \
    if (condition)                            \
    {                                         \
        _assert_notification(message)         \
        _assert_action                        \
    }                                         \
}while(0);

/*
options for assert notification
1. printf message
2. uart message 
default no message 
*/

// assert notification
#define _assert_msg_format                  ("[NVM DBG ASSERT] [%s:%s:(%.3d)]: (%s) \n")

#if (NVME_DBG_ASSERT_NOTIFICATION_OPTION==1)
#define _assert_notification(message)       printf(_assert_msg_format, __FILE__, __FUNCTION__, __LINE__, message);
#elif (NVME_DBG_ASSERT_NOTIFICATION_OPTION==2)
#define _assert_notification(message)       char argString[256]; sprintf(argString, _assert_msg_format, __FILE__, __FUNCTION__, __LINE__, message); printf("%s", argString);
#else
#define _assert_notification(message)
#endif

/*
option for assert action 
1. hang (while 1)
2. exit program (with stdlib) 
default no action
*/

// assert action
#if(NVME_DBG_ASSERT_ACTION_OPTION==1)
#define _assert_action                      while(1);
#elif(NVME_DBG_ASSERT_ACTION_OPTION==2)
#define _assert_action                      _Exit(1);
#else
#define _assert_action                      
#endif

#else   //ENABLE_NVME_DBG_ASSERT

#define NVME_DBG_ASSERT(condition, message)                              
#define NVME_DBG_ASSERT_IF_TRUE(condition, message)                      
#define NVME_DBG_ASSERT_IF_EQUAL(actual, expected, message)              
#define NVME_DBG_ASSERT_IF_NOT_EQUAL(actual, expected, message)          
#define NVME_DBG_ASSERT_IF_GREATER_THAN(actual, threshold, message)      
#define NVME_DBG_ASSERT_IF_LESSER_THAN(actual, threshold, message)       
#define NVME_DBG_ASSERT_IF_GREATER_OR_EQUAL(actual, threshold, message)  
#define NVME_DBG_ASSERT_IF_LESSER_OR_EQUAL(actual, threshold, message)   

#endif  //ENABLE_NVME_DBG_ASSERT