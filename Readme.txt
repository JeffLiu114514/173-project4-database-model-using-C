
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