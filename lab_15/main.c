#include <stdio.h>

// This is a function pointer. You will learn about this later --- for
// now, don't worry about it. All you need to know is that points at
// your assembly code, which is at 0x8000
static int (*nice_asm)(void) = (int (*)(void))0x8000U;

int nice_c(void) {
    //
    // YOUR EXERCISE 2 CODE HERE
    //
    // Reminder the pseudocode is:
    //
    //     sum = 0
    //
    //     for i = 0 to 69 inclusive:
    //         sum += i
    //
    //     return sum
    
    int sum = 0;
    int i = 0;
    
    for (; i <= 69; i = i + 1)
        sum = sum + i;
    
    return sum;
}

int main(void) {
    //
    // YOUR EXERCISE 3 CODE HERE
    //
    // Hint: you need to call both nice_c() and nice_asm() and pass the
    //       results to printf() in the form specified in README.txt
    //

    int sumASM = nice_asm();
    int sumC = nice_c();
    
    printf("nice_asm() = %d = 0x%x \n", sumASM, sumASM);
    
    printf("nice_c() = %d = 0x%x", sumC, sumC);
    
    return 0;
}
