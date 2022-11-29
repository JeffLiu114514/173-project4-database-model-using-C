#ifndef INC_173_PROJ4_PART3_H
#define INC_173_PROJ4_PART3_H
#include "Part1.h"
typedef struct CRDH CRDH;
typedef struct CRDHList CRDHList;

struct CRDH {
    char *Course;
    char *Room;
    char *Day;
    char *Hour;
    CRDH *nextCRDH;
};

struct CRDHList {
    CRDH **lists;
};

//selection operation on CSG
CSGList *selection_CSG(CSGList *CSGHash, int id);

//projection operation on CSG
void projection_CSG(CSGList *CSGHash, char *type);

//joined relation CRDH
void printCRDH(CRDHList *table);

CRDHList *newCRDHList();

CRDH *newCRDH(char *Course, char *Room, char *Day, char *Hour);

CRDHList *joinCRDH(CRList *CRHash, CDHList *CDHHash);

void projection_CRDH(CRDHList *CRDHHash, char *type1, char *type2);

CRDHList *selection_CRDH(CRDHList *CRDHHash, char *Room);

void allOperation(CRList *CRHash, CDHList *CDHHash, char *Room, char *type1, char *type2);

void freeCRDH(CRDH *crdh);

#endif //INC_173_PROJ4_PART3_H
