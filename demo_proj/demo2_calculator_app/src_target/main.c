/*
 * 文件: main.c
 * 路径: src_target/demo_projects/demo2_calculator_app/main.c
 * 对应MCCP文件: src_mbh/demo_projects/demo2_calculator_app/main_c.mbh, src_mpc/demo_projects/demo2_calculator_app/main_c.mpc
 *
 * 这个文件是MCCP演示项目demo2_calculator_app的主程序入口。
 * 它负责处理用户输入循环，调用计算逻辑，并显示结果。
 * 文件内容将由MCCP工具链根据.mbh和.mpc文件生成/完善。
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include "calculator.h"

void display_calculator_menu() {
    printf("Simple MCCP Calculator (C Implementation)\n");
    printf("Enter expression (e.g., 2 + 3 * 4 or 5 / 0) or type 'quit'/'exit'.\n");
}

void display_message(const char* message) {
    printf("%s", message);
}

int main() {
    char user_input_buffer[256]; 
    double calculation_result;
    int calculation_status; 
    int app_exit_flag = 0; 

    while (!app_exit_flag) {
        display_calculator_menu();
        display_message("> ");

        if (fgets(user_input_buffer, sizeof(user_input_buffer), stdin) != NULL) {
            user_input_buffer[strcspn(user_input_buffer, "\n")] = 0;

            if (strcmp(user_input_buffer, "quit") == 0 || strcmp(user_input_buffer, "exit") == 0) {
                app_exit_flag = 1; 
                continue; 
            }

            process_expression(user_input_buffer, &calculation_result, &calculation_status);

            if (calculation_status == ERROR_CODE_SUCCESS) { 
                printf("Result: %lf\n", calculation_result); 
            } else {
                if (calculation_status == ERROR_CODE_DIVISION_BY_ZERO) {
                    display_message(ERROR_MSG_DIVISION_BY_ZERO);
                    display_message("\n");
                } else if (calculation_status == ERROR_CODE_INVALID_INPUT) {
                    display_message(ERROR_MSG_INVALID_INPUT);
                    display_message("\n");
                } else {
                    display_message(ERROR_MSG_UNKNOWN_ERROR);
                    display_message("\n");
                }
            }
        } else {
            display_message("Error reading input.\n");
            app_exit_flag = 1; 
        }
    }

    display_message("Calculator exiting.\n");
    return EXIT_SUCCESS; 
}
