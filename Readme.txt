CSC173 project2
Junfei Liu
jliu137@u.rochester.edu

I collaborate with Dingcheng Wang (dwang63@u.rochester.edu)

Our code can be compiled by
gcc -g -o run -std=c99 -Wall -Werror main.c Part1.h Part1.c Part2.h Part2.c Part3.h Part3.c

and you can run it by
./run.exe

Our code can perfectly execute all required functions in the command line, including
1. creating the database,
2. perform five required insert, delete, and lookup operations in part1,
3. perform two required queries with REPL,
4. perform four required relational algebra operations.

We have not done any extra credits.

Things you might want to know:
In part1, we originally planned to use a simple hash function which is to simply
add up the value of char and mod by table size, like
int hashString(char *key) {
    int temp = 0;
    for (int i = 0; i < strlen(key); i++) {
        temp = (temp + (int) key[i]);
    }
    return temp % tableSize;
}
but we found that the hash of "CSC171" is surprisingly the same as "CSC252", so
I made it more complex with reference to djb2 hash function by
temp = (temp * 33 ^ (int) key[i]) % tableSize;
so that their hash value won't be the same.

Because part2 requires the database before deletion or insertion, we load data again
at the beginning of part2.