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

struct CSG {
    char *Course;
    int StudentId;
    char *Grade;
    CSG *nextCSG;
};
struct CSGList {
    CSG **lists;
};

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

struct CP {
    char *Course;
    char *Prerequisite;
    CP *nextCP;
};
struct CPList {
    CP **lists;
};

struct CDH {
    char *Course;
    char *Day;
    char *Hour;
    CDH *nextCDH;
};
struct CDHList {
    CDH **lists;
};

struct CR {
    char *Course;
    char *Room;
    CR *nextCR;
};
struct CRList {
    CR **lists;
};
//printXX, new_XX, insert_XX, lookup_XX, & delete_XX
//CSG (Course-StudentId-Grade)
void printCSG(CSGList *Hashtable);

CSGList *new_CSGList();

CSG *newCSG(char *Course, int StudentId, char *Grade);

void insert_CSG(CSGList *HashTable, char *Course, int StudentId, char *Grade);

void lookup_CSG(CSGList *HashTable, char *Course, int StudentId, char *Grade);

void delete_CSG(CSGList *HashTable, char *Course, int StudentId, char *Grade);


//SNAP (StudentId-Name-Address-Phone)
void printSNAP(SNAPList *Hashtable);

SNAPList *new_SNAPList();

SNAP *newSNAP(int StudentId, char *Name, char *Address, char *Phone);

void insert_SNAP(SNAPList *HashTable, int StudentId, char *Name, char *Address, char *Phone);

void lookup_SNAP(SNAPList *HashTable, int StudentId, char *Name, char *Address, char *Phone);

void delete_SNAP(SNAPList *HashTable, int StudentId, char *Name, char *Address, char *Phone);


//CP(Course-Prerequisite)
void printCP(CPList *Hashtable);

CPList *new_CPList();

CP *newCP(char *Course, char *Prerequisite);

void insert_CP(CPList *HashTable, char *Course, char *Prerequisite);

void lookup_CP(CPList *HashTable, char *Course, char *Prerequisite);

void delete_CP(CPList *HashTable, char *Course, char *Prerequisite);


//CDH (Course-Day-Hour)
void printCDH(CDHList *HashTable);

CDHList *new_CDHList();

CDH *newCDH(char *Course, char *Day, char *Hour);

void insert_CDH(CDHList *HashTable, char *Course, char *Day, char *Hour);

void lookup_CDH(CDHList *HashTable, char *Course, char *Day, char *Hour);

void delete_CDH(CDHList *HashTable, char *Course, char *Day, char *Hour);


//CR (Course-Room)
void printCR(CRList *Hashtable);

CRList *new_CRList();

CR *newCR(char *Course, char *Room);

void insert_CR(CRList *HashTable, char *Course, char *Room);

void lookup_CR(CRList *HashTable, char *Course, char *Room);

void delete_CR(CRList *HashTable, char *Course, char *Room);

//Hashtable methods
int hashInt(int key);
int hashString(char *key);

//Free these relations
void freeCSG(CSG *Cf);

void freeSNAP(SNAP *Sf);

void freeCP(CP *CPi);

void freeCDH(CDH *CDHi);

void freeCR(CR *CRi);

#endif //INC_173_PROJ4_PART1_H