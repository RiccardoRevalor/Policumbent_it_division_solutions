# Questions

## Question 1

What is the time complexity of the following C program?

```c
#include <stdio.h>

#define MAXN 100

int main() {
    int n = 0, i = 0, j = 0;
    int mat[MAXN][MAXN];

    fscanf(stdin, "%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(stdin, "%d", &mat[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        mat[i][0] *= 2;
    }
}
```
Since both the inner and the outer loops run exactly n times, they determine the time complexity which is O(n^2).
The last loop, having a lower time complexity (linear), do not influence the overall time complexity of the program.

## Question 2

What is a memory leak? Explain how to correctly free memory after a dynamic
memory allocation in C

A memory leak is related to the HEAP management and it occurs when we don't free the dinamyc allocated memory when we no longer need it.
To prevent memory leaks, you should ensure that every allocation of dynamic memory has a corresponding free() call when the memory is no longer needed.

## Question 3

What is an abstract method in OOP? How is it used?

It's a method that is declared but not implemented in the class.
In fact, in OOP paradigm we use abstract classes and interfaces that may contain abstract methods. The idea is to then create child classes implementing the code.

For example, if I have an abstract class with the abstract method X, in the abstract class I can write (Java):

```Java
abstract class MyAbstractClass{
    abstract void myPrint();
}
```

Then I can declare another class, extending the abstract class and implementing the abstract method, like:

```Java
class myClass extends MyAbstractClass {

    @Override
    void myPrint() {
        System.out.println("Hello Policumbent.");
    }
}
```

## Question 4

How is `systemd` used in most Linux systems?

It's used as the default init system and service manager.

## Question 5

What is a `git rebase`?

It's a command related to git repositories, which can change the base of a branch from one commit to another one.
For example, if you use git rebase on a branch created by commit X, after the rebase it looks like the branch was created after commit Y, with X not equal to Y.