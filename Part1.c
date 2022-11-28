#include "Part1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tableSize = 50;

void printSNAP(SNAPList *Hashtable) {

}

SNAPList* new_SNAPList() {
    SNAPList* hashTable = (SNAPList*) malloc(sizeof(SNAPList));
    hashTable->lists = (SNAP **) malloc(sizeof(SNAP*) * tableSize);
    for (int i = 0; i < tableSize; i++) {
        hashTable->lists[i] = NULL;
    }
    return hashTable;
}

SNAP *newSNAP(int StudentId, char *Name, char *Address, char *Phone) {
    SNAP* SNAPnew = (SNAP*)malloc(sizeof(SNAP));
    SNAPnew->Address = (char*)malloc(strlen(Address) + 1);
    SNAPnew->Name = (char*)malloc(strlen(Name) + 1);
    SNAPnew->Phone = (char*)malloc(strlen(Phone) + 1);

    strcpy(SNAPnew->Address, Address);
    strcpy(SNAPnew->Name, Name);
    strcpy(SNAPnew->Phone, Phone);

    SNAPnew->StudentId = StudentId;
    SNAPnew->nextSNAP = NULL;
    return SNAPnew;
}

void insert_SNAP(SNAPList *HashTable, int StudentId, char *Name, char *Address, char *Phone) {

}

void lookup_SNAP(SNAPList *HashTable, int StudentId, char *Name, char *Address, char *Phone) {

}

void delete_SNAP(SNAPList *HashTable, int StudentId, char *Name, char *Address, char *Phone) {

}