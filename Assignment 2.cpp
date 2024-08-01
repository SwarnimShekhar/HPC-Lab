#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

int is_integer(const char *str) {
    if (*str == '-' || *str == '+') str++;
    if (!*str) return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

void find_min_max(int *arr, int size, int *min, int *max) {
    *min = *max = *arr;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) < *min) {
            *min = *(arr + i);
        }
        if (*(arr + i) > *max) {
            *max = *(arr + i);
        }
    }
}

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

int main(int argc, char *argv[]) {
    // Q1: Declare an integer variable, assign it a value, and print its address using a pointer.
    printf("Q1:\n");
    {
        int var = 10;
        int *ptr = &var;
        printf("Value of var: %d\n", var);
        printf("Address of var: %p\n\n", (void*)ptr);
    }

    // Q2: Swap two integers using pointers.
    printf("Q2:\n");
    {
        int x = 10, y = 20;
        printf("Before swap: x = %d, y = %d\n", x, y);
        swap(&x, &y);
        printf("After swap: x = %d, y = %d\n\n", x, y);
    }

    // Q3: Declare an integer array, initialize it, and use a pointer to print each element.
    printf("Q3:\n");
    {
        int arr[] = {1, 2, 3, 4, 5};
        int *ptr = arr;
        for (int i = 0; i < 5; i++) {
            printf("Element %d: %d\n", i, *(ptr + i));
        }
        printf("\n");
    }

    // Q4: Compute the sum of elements in an integer array using a pointer.
    printf("Q4:\n");
    {
        int arr[] = {1, 2, 3, 4, 5};
        int *ptr = arr;
        int sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += *(ptr + i);
        }
        printf("Sum of elements: %d\n\n", sum);
    }

    // Q5: Reverse an array using pointers.
    printf("Q5:\n");
    {
        int arr[] = {1, 2, 3, 4, 5};
        int size = sizeof(arr) / sizeof(arr[0]);
        int *start = arr;
        int *end = arr + size - 1;
        while (start < end) {
            int temp = *start;
            *start = *end;
            *end = temp;
            start++;
            end--;
        }
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n\n");
    }

    // Q6: Find the largest and smallest elements in an array using pointers.
    printf("Q6:\n");
    {
        int arr[] = {3, 1, 4, 1, 5, 9};
        int size = sizeof(arr) / sizeof(arr[0]);
        int min, max;
        find_min_max(arr, size, &min, &max);
        printf("Min: %d, Max: %d\n\n", min, max);
    }

    // Q7: Use a function pointer to call a function that adds two integers.
    printf("Q7:\n");
    {
        int (*func_ptr)(int, int) = add;
        int result = func_ptr(3, 4);
        printf("Result of addition: %d\n\n", result);
    }

    // Q8: Menu-driven program using function pointers.
    printf("Q8:\n");
    {
        int choice, a, b;
        int (*func_ptr)(int, int);
        while (1) {
            printf("Menu:\n1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            if (choice == 5) break;
            printf("Enter two integers: ");
            scanf("%d%d", &a, &b);
            switch (choice) {
                case 1: func_ptr = add; break;
                case 2: func_ptr = subtract; break;
                case 3: func_ptr = multiply; break;
                case 4: func_ptr = divide; break;
                default: printf("Invalid choice\n"); continue;
            }
            printf("Result: %d\n\n", func_ptr(a, b));
        }
    }

    // Q9: Dynamically allocate memory for an array of integers, initialize it, and free the memory.
    printf("Q9:\n");
    {
        int n;
        printf("Enter the number of elements: ");
        scanf("%d", &n);
        int *arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        for (int i = 0; i < n; i++) {
            arr[i] = i + 1;
        }
        printf("Array elements: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        free(arr);
        printf("\n");
    }

    // Q10: Dynamically allocate memory for a string, take input from the user, and print the string.
    printf("Q10:\n");
    {
        int n;
        printf("Enter the length of the string: ");
        scanf("%d", &n);
        char *str = (char*)malloc((n + 1) * sizeof(char));
        if (str == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        printf("Enter the string: ");
        scanf("%s", str);
        printf("You entered: %s\n", str);
        free(str);
        printf("\n");
    }

    // Q11: Print the number of command-line arguments passed to the program.
    printf("Q11:\n");
    {
        printf("Number of command-line arguments: %d\n\n", argc);
    }

    // Q12: Print each command-line argument on a new line.
    printf("Q12:\n");
    {
        for (int i = 0; i < argc; i++) {
            printf("Argument %d: %s\n", i, argv[i]);
        }
        printf("\n");
    }

    // Q13: Reverse a single string from the command line.
    printf("Q13:\n");
    {
        if (argc != 2) {
            printf("Usage: %s <string>\n", argv[0]);
            return 1;
        }
        reverse(argv[1]);
        printf("Reversed string: %s\n\n", argv[1]);
    }

    // Q14: Concatenate multiple strings from the command line into a single string.
    printf("Q14:\n");
    {
        if (argc < 2) {
            printf("Usage: %s <strings>\n", argv[0]);
            return 1;
        }
        int total_length = 0;
        for (int i = 1; i < argc; i++) {
            total_length += strlen(argv[i]);
        }
        char *result = (char*)malloc((total_length + argc) * sizeof(char)); // +argc for spaces
        if (result == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        strcpy(result, argv[1]);
        for (int i = 2; i < argc; i++) {
            strcat(result, " ");
            strcat(result, argv[i]);
        }
        printf("Concatenated string: %s\n", result);
        free(result);
        printf("\n");
    }

    // Q15: Calculate the average of a list of integers from the command line.
    printf("Q15:\n");
    {
        if (argc < 2) {
            printf("Usage: %s <integers>\n", argv[0]);
            return 1;
        }
        int sum = 0;
        for (int i = 1; i < argc; i++) {
            sum += atoi(argv[i]);
        }
        double average = (double)sum / (argc - 1);
        printf("Average: %.2f\n\n", average);
    }

    // Q16: Check if the correct number of command-line arguments are provided and print an error message if not.
    printf("Q16:\n");
    {
        if (argc != 3) {
            printf("Usage: %s <arg1> <arg2>\n", argv[0]);
            return 1;
        }
        printf("Arguments are correct\n\n");
    }

    // Q17: Validate whether the command-line arguments are integers and print an error message for invalid inputs.
    printf("Q17:\n");
    {
        for (int i = 1; i < argc; i++) {
            if (!is_integer(argv[i])) {
                printf("Error: Argument %s is not an integer\n", argv[i]);
                return 1;
            }
        }
        printf("All arguments are valid integers\n\n");
    }

    // Q18: Print all the environment variables passed to the program.
    printf("Q18:\n");
    {
        extern char **environ;
        char **env = environ;
        while (*env) {
            printf("%s\n", *env);
            env++;
        }
        printf("\n");
    }

    // Q19: Print the value of a specific environment variable passed from the command line.
    printf("Q19:\n");
    {
        if (argc != 2) {
            printf("Usage: %s <env_variable>\n", argv[0]);
            return 1;
        }
        char *value = getenv(argv[1]);
        if (value) {
            printf("Value of %s: %s\n", argv[1], value);
        } else {
            printf("%s not found\n", argv[1]);
        }
        printf("\n");
    }

    // Q20: Execute a list of commands from the command line sequentially.
    printf("Q20:\n");
    {
        if (argc < 2) {
            printf("Usage: %s <commands>\n", argv[0]);
            return 1;
        }
        for (int i = 1; i < argc; i++) {
            int ret = system(argv[i]);
            if (ret == -1) {
                printf("Failed to execute command: %s\n", argv[i]);
            }
        }
        printf("\n");
    }

    return 0;
}

