/*
 * 文件: calculator.c
 * 路径: src_target/demo_projects/demo2_calculator_app/calculator.c
 * 对应MCCP文件: src_mbh/demo_projects/demo2_calculator_app/calculator_c.mbh, src_mpc/demo_projects/demo2_calculator_app/calculator_c.mpc
 *
 * 这个文件实现了MCCP演示项目demo2_calculator_app的核心计算逻辑。
 * 文件内容将由MCCP工具链根据.mbh和.mpc文件生成/完善。
 */

#include "calculator.h"
#include <stdio.h> // For sscanf, printf (debugging)
#include <string.h> // For string manipulation
#include <ctype.h> // For isspace



static double CURRENT_CALCULATOR_VALUE = 0.0; // Initialize state
static char LAST_OPERATOR_USED = '\0'; // Initialize state ('\0' indicates no previous operator)








const char* ERROR_MSG_DIVISION_BY_ZERO = "Error: Division by zero."; // Actual definition
const char* ERROR_MSG_INVALID_INPUT = "Error: Invalid input format."; // Actual definition
const char* ERROR_MSG_UNKNOWN_ERROR = "Error: An unknown error occurred."; // Actual definition




/**
 * @brief Attempts to parse the input string into operands and operator.
 * @param InputString The string to parse.
 * @param Operand1 Pointer to store the first operand.
 * @param Operator Pointer to store the operator character.
 * @param Operand2 Pointer to store the second operand.
 * @param IsContinuous Pointer to a flag indicating if it's a continuous calculation.
 * @return An error code (ERROR_CODE_SUCCESS or ERROR_CODE_INVALID_INPUT).
 *
 * Pseudo-code corresponds to PARSE_EXPRESSION in calculator_c.mpc.
 * This is a simplified implementation placeholder.
 */
int parse_expression(const char* InputString, double* Operand1, char* Operator, double* Operand2, int* IsContinuous) {

    while (*InputString && isspace((unsigned char)*InputString)) {
        InputString++;
    }



    if (*InputString == '+' || *InputString == '-' || *InputString == '*' || *InputString == '/') {
        char temp_op = *InputString;
        InputString++; // Move past operator
        while (*InputString && isspace((unsigned char)*InputString)) { // Skip spaces after operator
             InputString++;
        }
        if (sscanf(InputString, "%lf", Operand1) == 1) { // Read the number into Operand1
            *IsContinuous = 1;
            *Operator = temp_op;
            *Operand2 = 0.0; // Second operand not used in continuous parsing here
            return ERROR_CODE_SUCCESS; // Successfully parsed continuous format
        } else {

            return ERROR_CODE_INVALID_INPUT;
        }
    }


    char temp_op_char = '\0';
    int items_read = sscanf(InputString, "%lf %c %lf", Operand1, &temp_op_char, Operand2);

    if (items_read == 3) {

        *IsContinuous = 0;
        *Operator = temp_op_char;
        if (*Operator != '+' && *Operator != '-' && *Operator != '*' && *Operator != '/') {
            return ERROR_CODE_INVALID_INPUT; 
        }
        return ERROR_CODE_SUCCESS; 
    } else if (items_read == 1) {
        *IsContinuous = 0; 
        *Operator = '\0'; 
        *Operand2 = 0.0;
        return ERROR_CODE_SUCCESS; 
    }
    return ERROR_CODE_INVALID_INPUT;
}


/**
 * @brief Performs the specified arithmetic operation.
 */
int perform_operation(double Operand1, char Operator, double Operand2, double* Result) {
    switch (Operator) {
        case '+':
            *Result = Operand1 + Operand2;
            return ERROR_CODE_SUCCESS;
        case '-':
            *Result = Operand1 - Operand2;
            return ERROR_CODE_SUCCESS;
        case '*':
            *Result = Operand1 * Operand2;
            return ERROR_CODE_SUCCESS;
        case '/':
            if (Operand2 == 0.0) {
                *Result = 0.0; 
                return ERROR_CODE_DIVISION_BY_ZERO;
            }
            *Result = Operand1 / Operand2;
            return ERROR_CODE_SUCCESS;
        default:
            *Result = 0.0;
            return ERROR_CODE_INVALID_INPUT; 
    }
}

void process_expression(const char* InputString, double* ResultRef, int* StatusRef) {
    double op1_parsed, op2_parsed;
    char op_char_parsed = '\0';
    int is_continuous_parsed = 0;
    int parse_status;

    parse_status = parse_expression(InputString, &op1_parsed, &op_char_parsed, &op2_parsed, &is_continuous_parsed);

    if (parse_status != ERROR_CODE_SUCCESS) {
        *StatusRef = parse_status; 
        *ResultRef = CURRENT_CALCULATOR_VALUE; 
        return; 
    }

    if (parse_status == ERROR_CODE_SUCCESS && !is_continuous_parsed && op_char_parsed == '\0') {
        CURRENT_CALCULATOR_VALUE = op1_parsed; 
        *ResultRef = CURRENT_CALCULATOR_VALUE;
        *StatusRef = ERROR_CODE_SUCCESS;
        LAST_OPERATOR_USED = '\0'; 
        return;
    }

    double final_op1, final_op2;
    char final_operator;

    if (is_continuous_parsed) {
        final_op1 = CURRENT_CALCULATOR_VALUE; 
        final_operator = op_char_parsed; 
        final_op2 = op1_parsed; 
        LAST_OPERATOR_USED = final_operator; 
    } else { 
        final_op1 = op1_parsed; 
        final_operator = op_char_parsed; 
        final_op2 = op2_parsed; 
        LAST_OPERATOR_USED = final_operator; 
    }

    int calculation_status;
    double calculation_result;

    calculation_status = perform_operation(final_op1, final_operator, final_op2, &calculation_result);

    *StatusRef = calculation_status; 
    *ResultRef = calculation_result; 

    if (calculation_status == ERROR_CODE_SUCCESS) {
        CURRENT_CALCULATOR_VALUE = calculation_result;
    }
}
