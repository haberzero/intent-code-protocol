/*
 * 文件: calculator.h
 * 路径: src_target/demo_projects/demo2_calculator_app/calculator.h
 * 对应MCCP文件: src_mbh/demo_projects/demo2_calculator_app/calculator_h.mbh, src_mpc/demo_projects/demo2_calculator_app/calculator_h.mpc
 *
 * 这个头文件为MCCP演示项目demo2_calculator_app的计算逻辑模块定义了公共接口。
 * 文件内容将由MCCP工具链根据.mbh和.mpc文件生成/完善。
 */

#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 


#define ERROR_CODE_SUCCESS          0 
#define ERROR_CODE_DIVISION_BY_ZERO 1 
#define ERROR_CODE_INVALID_INPUT    2 
#define ERROR_CODE_UNKNOWN_ERROR   99 


extern const char* ERROR_MSG_DIVISION_BY_ZERO;
extern const char* ERROR_MSG_INVALID_INPUT;
extern const char* ERROR_MSG_UNKNOWN_ERROR;


void process_expression(const char* InputString, double* ResultRef, int* StatusRef);

#endif // CALCULATOR_H_INCLUDED
