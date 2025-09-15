# ICP: Target Code (Python) for Calculator

def add_numbers(num1, num2):
    """Adds two numbers."""
    return num1 + num2

def subtract_numbers(num1, num2):
    """Subtracts the second number from the first."""
    return num1 - num2

def multiply_numbers(num1, num2):
    """Multiplies two numbers."""
    return num1 * num2

def divide_numbers(num1, num2):
    """Divides the first number by the second, handling division by zero."""
    if num2 == 0:
        return "Error: Division by zero" # Simplified error handling for example
    else:
        return num1 / num2

# Example usage (optional, for testing)
# if __name__ == "__main__":
#     print(f"5 + 3 = {add_numbers(5, 3)}")
#     print(f"10 - 4 = {subtract_numbers(10, 4)}")
#     print(f"6 * 7 = {multiply_numbers(6, 7)}")
#     print(f"10 / 2 = {divide_numbers(10, 2)}")
#     print(f"10 / 0 = {divide_numbers(10, 0)}")
