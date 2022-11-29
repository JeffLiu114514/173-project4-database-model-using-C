CSC173 project2
Junfei Liu
jliu137@u.rochester.edu

I collaborate with Dingcheng Wang (dwang63@u.rochester.edu)

Our code can be compiled by
gcc -g -o run -std=c99 -Wall -Werror main.c Part1.h Part1.c Part2.h Part2.c Part3.h Part3.c

and you can run it by
./run.exe




In part1, we originally planned to use a simple hash function which is to simple
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

Note that when you are testing part2 requirement2 i.e. “Where is Name at Hour on Day?”
by entering "R. Zmolek", "M", "900", it yields no result because Zmolek's DSCC201 was
deleted in part1 by delete(<"DSCC201", *, *>, Course-Day-Hour). We thought it was a bug
and spent lots of time debugging. Please refer to the database after deletion and
insertion operation from part1 when testing part2.