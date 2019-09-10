#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char *name;
} person;

/**
 * Lab 23
 * For this lab you will be implementing a shallow copy function and a deep copy function
 * for the person struct defined above. You'll know you've implemented it correctly when you get
 * the following output:
 * 
 * SHALLOW COPY:
 * Person 1's age: 22, Person 2's age: 22, Person 1's name: Bob, Person 2's name: Bob
 * Person 1's age: 22, Person 2's age: 22, Person 1's name: Box, Person 2's name: Box
 * DEEP COPY:
 * Person 3's age: 22, Person 4's age: 22, Person 3's name: Sally, Person 4's name: Sally
 * Person 3's age: 22, Person 4's age: 22, Person 3's name: Salty, Person 4's name: Sally
 * 
 * To run your code, call make, and then run the compiled executable by calling ./copy
 **/



void shallow_copy_struct(person *src, person *dst) {
    //TODO: Copy the struct src is pointing to into dst using shallow copy logic
    *dst = *src;
}

void deep_copy_struct(person *src, person *dst) {
    //TODO: Copy the struct src is point to into dst using deep copy logic
    // Make sure a brand new char array for name is created and copied properly!
    // HINT: Make sure you think of where you make space for your array in memory!
    *dst = *src;
    
    dst -> name = malloc(10 * sizeof(char));
    for (int i = 0; i < 6; i++) {
        dst -> name[i] = src -> name[i];
    }
}

int main(void) {
    printf("SHALLOW COPY:\n");
    char p1_name[4] = "Bob";
    person p1 = {22, p1_name};
    person p2;
    shallow_copy_struct(&p1, &p2);

    printf("Person 1's age: %d, Person 2's age: %d, Person 1's name: %s, Person 2's name: %s\n",
            p1.age, p2.age, p1.name, p2.name);
    p1.name[2] = 'x';
    printf("Person 1's age: %d, Person 2's age: %d, Person 1's name: %s, Person 2's name: %s\n",
            p1.age, p2.age, p1.name, p2.name);

    printf("DEEP COPY:\n");
    char p3_name[6] = "Sally";
    person p3 = {22, p3_name};
    person p4;
    deep_copy_struct(&p3, &p4);

    printf("Person 3's age: %d, Person 4's age: %d, Person 3's name: %s, Person 4's name: %s\n",
            p3.age, p4.age, p3.name, p4.name);
    p3.name[3] = 't';
    printf("Person 3's age: %d, Person 4's age: %d, Person 3's name: %s, Person 4's name: %s\n",
            p3.age, p4.age, p3.name, p4.name);


}
