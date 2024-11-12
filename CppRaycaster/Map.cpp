#include "Map.h"
#include "D2entity.h"
#include "./statemachine/soldier.h"
 int Map::Level1[10][10] =
    { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
      { 1, 1, 0, 0, 1, 0, 0, 1, 1, 1 },
      { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
      { 1, 0, 0, 2, 0, 0, 0, 0, 0, 1 },
      { 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
      { 1, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
      { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
      { 1, 2, 2, 0, 0, 0, 0, 1, 0, 1 },
      { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
      { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};

 int Map::Level1Size[2] = { 10, 10 };
 int Map::numPatrolls = 0;
 vector2* Map::patrollrout = new vector2[0];
 void Map::loadLevelOne() 
 {
     delete[] patrollrout;
     numPatrolls = 4;
     patrollrout = new vector2[4];
     patrollrout[0] = vector2(4.5f, 5.8f);
     patrollrout[1] = vector2(4.5f, 2.2f);
     patrollrout[2] = vector2(2.1f, 2.2f);
     patrollrout[3] = vector2(2.2f, 5.8f);


     D2entity* d = new D2entity(1, vector2(4.8f, 4.5f));
     stateMachine* m = new soldier(d);
     m->Construct();
     d->myMachine = m;

     d = new D2entity(2, vector2(4.8f, 2.5f));
     m = new soldier(d);
     m->Construct();
     d->myMachine = m;

 }