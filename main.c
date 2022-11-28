#include "Part1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    CSGList *CSGHash = new_CSGList();
    insert_CSG(CSGHash, "CSC171", 12345, "A");
    insert_CSG(CSGHash, "CSC171", 67890, "B");
    insert_CSG(CSGHash, "MATH150", 12345, "A");
    insert_CSG(CSGHash, "DSCC201", 12345, "C");
    insert_CSG(CSGHash, "DSCC201", 11111, "B+");
    insert_CSG(CSGHash, "CSC172", 98789, "A-");
    insert_CSG(CSGHash, "MATH150", 67890, "C+");
    insert_CSG(CSGHash, "CSC173", 12321, "B+");
    insert_CSG(CSGHash, "CSC173", 98789, "A");
    insert_CSG(CSGHash, "DSCC201", 98789, "C");

    SNAPList *SNAPHash = new_SNAPList();
    insert_SNAP(SNAPHash, 11111, "M. Subban", "1 Exchange Blvd", "555-1212");
    insert_SNAP(SNAPHash, 12345, "R. Zmolek", "2700 B-H Townline Rd", "555-1111");
    insert_SNAP(SNAPHash, 67890, "P. Tischke", "1 Exchange Blvd", "555-1234");
    insert_SNAP(SNAPHash, 12321, "P. F. Cedarqvist", "80 Lyndon Rd", "555-2222");
    insert_SNAP(SNAPHash, 98789, "M. Subban", "123 Ling Rd", "555-3333");

    CPList *CPHash = new_CPList();
    insert_CP(CPHash, "CSC172", "CSC171");
    insert_CP(CPHash, "CSC172", "MATH150");
    insert_CP(CPHash, "CSC173", "CSC172");
    insert_CP(CPHash, "CSC252", "CSC172");
    insert_CP(CPHash, "CSC254", "CSC252");
    insert_CP(CPHash, "DSCC201", "CSC171");
    insert_CP(CPHash, "DSCC202", "DSCC201");
    insert_CP(CPHash, "DSCC265", "CSC262");
    insert_CP(CPHash, "DSCC265", "CSC171");

    CDHList *CDHHash = new_CDHList();
    insert_CDH(CDHHash, "CSC171", "T", "1400");
    insert_CDH(CDHHash, "CSC171", "R", "1400");
    insert_CDH(CDHHash, "CSC172", "T", "1525");
    insert_CDH(CDHHash, "CSC172", "R", "1640");
    insert_CDH(CDHHash, "CSC173", "T", "1400");
    insert_CDH(CDHHash, "CSC173", "R", "1400");
    insert_CDH(CDHHash, "CSC252", "T", "1230");
    insert_CDH(CDHHash, "CSC252", "R", "1230");
    insert_CDH(CDHHash, "DSCC201", "M", "900");
    insert_CDH(CDHHash, "DSCC201", "W", "900");
    insert_CDH(CDHHash, "DSCC202", "M", "1650");
    insert_CDH(CDHHash, "DSCC202", "W", "1650");
    insert_CDH(CDHHash, "DSCC265", "M", "1400");
    insert_CDH(CDHHash, "DSCC265", "W", "1400");

    CRList *CRHash = new_CRList();
    insert_CR(CRHash, "CSC171", "Hutchison Hall 141");
    insert_CR(CRHash, "CSC172", "Hutchison Hall 141");
    insert_CR(CRHash, "CSC173", "Wegmans 1400");
    insert_CR(CRHash, "CSC252", "Wegmans 1400");
    insert_CR(CRHash, "CSC254", "Wegmans 1400");
    insert_CR(CRHash, "DSCC201", "Bausch & Lomb 109");
    insert_CR(CRHash, "DSCC202", "Dewey 2162");
    insert_CR(CRHash, "DSCC265", "Wegmans 1400");
    insert_CR(CRHash, "MATH150", "Harkness 115");
}
