#ifndef INC_173_PROJ4_PART1_H
#define INC_173_PROJ4_PART1_H

typedef struct CSG CSG;
typedef struct CSGList CSGList;
typedef struct SNAP SNAP;
typedef struct SNAPList SNAPList;
typedef struct CP CP;
typedef struct CPList CPList;
typedef struct CDH CDH;
typedef struct CDHList CDHList;
typedef struct CR CR;
typedef struct CRList CRList;

extern const int tableSize;
//SNAP (StudentId-Name-Address-Phone)
struct SNAP {
    int StudentId;
    char *Name;
    char *Address;
    char *Phone;
    SNAP *nextSNAP;
};
struct SNAPList {
    SNAP **lists;
};

void printSNAP(SNAPList *Hashtable);

SNAPList *new_SNAPList();

SNAP *newSNAP(int StudentId, char *Name, char *Address, char *Phone);

void insert_SNAP(SNAPList *hashTable, int StudentId, char *Name, char *Address, char *Phone);

void lookup_SNAP(SNAPList *hashTable, int StudentId, char *Name, char *Address, char *Phone);

void delete_SNAP(SNAPList *hashTable, int StudentId, char *Name, char *Address, char *Phone);


//CSG (Course-StudentId-Grade)
struct CSG {
    char *Course;
    int StudentId;
    char *Grade;
    CSG *nextCSG;
};
struct CSGList {
    CSG **lists;
};

void printCSG(CSGList *Hashtable);

CSGList *new_CSGList();

CSG *newCSG(int StudentId, char *Course, char *Grade);

void insert_CSG(CSGList *hashTable, char *Course, int StudentId, char *Grade);

void lookup_CSG(CSGList *hashTable, char *Course, int StudentId, char *Grade);

void delete_CSG(CSGList *hashTable, char *Course, int StudentId, char *Grade);


//CP(Course-Prerequisite)
struct CP {
    char *Course;
    char *Prerequisite;
    CP *nextCP;
};
struct CPList {
    CP **lists;
};

void printCP(CPList *Hashtable);

CPList *new_CPList();

CP *newCP(char *Course, char *Prerequisite);

void insert_CP(CPList *hashTable, char *Course, char *Prerequisite);

void lookup_CP(CPList *hashTable, char *Course, char *Prerequisite);

void delete_CP(CPList *hashTable, char *Course, char *Prerequisite);


//CDH (Course-Day-Hour)
struct CDH {
    char *Course;
    char *Day;
    char *Hour;
    CDH *nextCDH;
};
struct CDHList {
    CDH **lists;
};

void printCDH(CDHList *hashTable);

CDHList *new_CDHList();

CDH *newCDH(char *Course, char *Day, char *Hour);

void insert_CDH(CDHList *hashTable, char *Course, char *Day, char *Hour);

void lookup_CDH(CDHList *hashTable, char *Course, char *Day, char *Hour);

void delete_CDH(CDHList *hashTable, char *Course, char *Day, char *Hour);


//CR (Course-Room)
struct CR {
    char *Course;
    char *Room;
    CR *nextCR;
};
struct CRList {
    CR **lists;
};

void printCR(CRList *Hashtable);

CRList *new_CRList();

CR *newCR(char *Course, char *Room);

void insert_CR(CRList *hashTable, char *Course, char *Room);

void lookup_CR(CRList *hashTable, char *Course, char *Room);

void delete_CR(CRList *hashTable, char *Course, char *Room);
//printXX, new_XX, insert_XX, lookup_XX, & delete_XX


//Hashtable methods
int hashInt(int key);
int hashString(char *key);

//Free relations
void freeSNAP(SNAP *snap);

void freeCSG(CSG *csg);

void freeCP(CP *cp);

void freeCDH(CDH *cdh);

void freeCR(CR *cr);

//debug
void printCSG2(CSGList *Hashtable);
void printSNAP2(SNAPList *Hashtable);
void printCP2(CPList *Hashtable);
void printCDH2(CDHList *HashTable);
void printCR2(CRList *Hashtable);
#endif //INC_173_PROJ4_PART1_H
