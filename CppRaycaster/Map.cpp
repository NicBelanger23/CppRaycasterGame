#include "doorManager.h"
#include "Map.h"
#include "D2entity.h"
#include "LevelProgresser.h"
#include "./statemachine/soldier.h"

 int** Map::Level;

 vector2 Map::LevelSize = vector2(20, 20);
 vector2 Map::PlayerStartPosition = vector2(1.5f, 1.5f);
 float Map::PlayerStartRotation = 0.0f;
 int Map::numPatrolls = 0;
 vector2* Map::patrollrout = new vector2[0];

 // Function to create and populate the 2D array
 static void initializeLevel() {
     // Step 1: Allocate memory for rows
     Map::Level = new int* [Map::LevelSize.X];
     for (int i = 0; i < Map::LevelSize.X; ++i) {
         // Step 2: Allocate memory for each column in each row
         Map::Level[i] = new int[Map::LevelSize.Y];
     }
 }

 void Map::unloadLevel() {
     delete[] patrollrout;
     numPatrolls = 0;

     for (auto it = GameManager::entityMap.begin(); it != GameManager::entityMap.end(); ++it) {
         D2entity* entity = *it; // Dereference the iterator to get the entity pointer
         if (entity) { // Check if the pointer is not null
             delete entity;
         }
     }
     GameManager::remainingEntities = 0;
 }

 void Map::loadLevelOne() 
 {
     //setup map
     Map::PlayerStartPosition = vector2(10.5, 1.5);
     Map::PlayerStartRotation = 90.0f;
     Map::LevelSize = vector2(20, 20);
     
     //setup level progressor
     LevelProgresser::destination = vector2(6.5, 16.5);
     LevelProgresser::DM = doorManager(vector2(6, 14), 5, 1.5f);

     int loadedMap[20][20] = {
     {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9},
     {1,0,0,0,0,1,0,3,0,0,0,1,0,0,1,0,0,0,0,0},
     {2,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0,0,0},
     {3,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0},
     {4,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0},
     {5,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,0,0,0},
     {6,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0},
     {7,0,1,0,1,1,0,0,1,0,0,1,0,1,1,1,0,0,0,0},
     {8,1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0},
     {9,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
     {0,1,0,0,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
     {1,0,1,0,0,1,1,1,2,2,2,2,1,1,0,1,0,0,0,0},
     {2,0,1,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0},
     {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
     {4,0,1,1,1,1,3,1,1,1,1,1,1,2,2,1,0,0,0,0},
     {5,1,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
     {6,0,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
     {7,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
     {8,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
     {9,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}
     };
     //apply level grid
     {
         initializeLevel();
         // Populate with a pattern (optional)
         for (int i = 0; i < Map::LevelSize.X; ++i) {
             for (int j = 0; j < Map::LevelSize.Y; ++j) {
                 if (i == 0 || i == (Map::LevelSize.X - 1) || j == 0 || j == (Map::LevelSize.Y - 1)) {
                     Map::Level[i][j] = 1;
                 }
                 else {
                     Map::Level[i][j] = loadedMap[i][j];
                 }



             }
         }
     }
     //setup patrolls
     {
         delete[] patrollrout;
         numPatrolls = 4;
         patrollrout = new vector2[4];
     }
     //spawn entities
     {
         int vsize = 10;
         vector2 vecs[10] = {
             vector2(6.5f, 4.5f),
             vector2(7.3f, 3.5f),
             vector2(2.5f, 6.5f),
             vector2(4.5f, 9.0f),
             vector2(2.0f, 13.5f),
             vector2(13.0f, 13.5f),
             vector2(8.0f, 13.5f),
             vector2(14.5f, 8.5f),
             vector2(12.5f, 6.5f),
             vector2(14.5f, 11.0f)
            };



         for (int i = 0; i < vsize; i++) {
             D2entity* d = new D2entity(i, vecs[i]);
             stateMachine* m = new soldier(d);
             m->Construct();
             d->myMachine = m;
             GameManager::remainingEntities++;
         }
     }




 }

 void Map::loadLevelTwo(vector2 offset)
 {
     unloadLevel();
     Map::LevelSize = vector2(20, 20);
     Player::localPlayer.position = vector2(10.5, 3.5) + offset;

     //setup level progressor
     LevelProgresser::destination = vector2(4.5, 5.5);
     LevelProgresser::DM = doorManager(vector2(3, 7), 1, 2.0f);

     int loadedMap[20][20] = {
     {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9},
     {1,0,0,0,0,1,1,1,1,1,3,1,0,0,1,0,0,0,0,0},
     {2,0,0,0,0,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0},
     {3,0,0,0,0,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0},
     {4,0,1,1,1,1,2,1,0,0,0,1,0,0,1,0,0,0,0,0},
     {5,1,1,0,0,0,1,1,0,1,1,1,1,1,1,0,0,0,0,0},
     {6,0,1,0,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0},
     {7,0,1,3,1,1,1,0,0,1,0,1,0,1,1,1,0,0,0,0},
     {8,1,0,0,0,1,1,0,1,1,1,1,0,0,0,1,0,0,0,0},
     {9,0,1,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
     {0,1,0,0,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
     {1,0,1,0,0,1,1,1,2,2,2,2,1,1,0,1,0,0,0,0},
     {2,0,1,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0},
     {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
     {4,0,1,1,1,1,0,1,0,1,0,1,1,2,2,1,0,0,0,0},
     {5,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
     {6,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
     {7,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
     {8,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
     {9,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}
     };
     //apply level grid
     {
         initializeLevel();
         // Populate with loaded map
         for (int i = 0; i < Map::LevelSize.X; ++i) {
             for (int j = 0; j < Map::LevelSize.Y; ++j) {
                 if (i == 0 || i == (Map::LevelSize.X - 1) || j == 0 || j == (Map::LevelSize.Y - 1)) {
                     Map::Level[i][j] = 1;
                 }
                 else {
                     Map::Level[i][j] = loadedMap[i][j];
                 }
             }
         }
     }
     //setup patrolls
     {
         numPatrolls = 4;
         patrollrout = new vector2[4];
     }
     //spawn entities
     {
         int vsize = 10;
         vector2 vecs[10] = {
             vector2(5.5f, 1.0f),
             vector2(5.5f, 1.0f),
             vector2(12.5f, 6.5f),
             vector2(13.5f, 8.5f),
             vector2(14.5f, 11.5f),
             vector2(14.5f, 13.2f),
             vector2(11.0f, 13.7f),
             vector2(10.0f, 13.5f),
             vector2(9.0f, 12.5f),
             vector2(3.5f, 10.5f),
         };



         for (int i = 0; i < vsize; i++) {
             D2entity* d = new D2entity(i, vecs[i]);
             stateMachine* m = new soldier(d);
             m->Construct();
             d->myMachine = m;
         }
     }




 }

 void Map::loadLevelThree(vector2 offset)
 {
     unloadLevel();
     Player::localPlayer.position = vector2(2.5, 2.5) + offset;
     Map::LevelSize = vector2(20, 20);
     int loadedMap[20][20] = {
     {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
     {2,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
     {3,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0},
     {4,3,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0},
     {5,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0},
     {6,0,1,1,1,1,1,0,1,0,0,1,0,0,0,1,0,0,1,0},
     {7,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0},
     {8,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
     {9,0,1,0,1,1,1,1,1,0,0,1,0,0,0,1,0,0,1,0},
     {0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
     {1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
     {2,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0},
     {3,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
     {4,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0},
     {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
     };
     //apply level grid
     {
         initializeLevel();
         // Populate with loaded map
         for (int i = 0; i < Map::LevelSize.X; ++i) {
             for (int j = 0; j < Map::LevelSize.Y; ++j) {
                 if (i == 0 || i == (Map::LevelSize.X - 1) || j == 0 || j == (Map::LevelSize.Y - 1)) {
                     Map::Level[i][j] = 1;
                 }
                 else {
                     Map::Level[i][j] = loadedMap[i][j];
                 }
             }
         }
     }
     //setup patrolls
     {
         numPatrolls = 4;
         patrollrout = new vector2[4];
     }
     //spawn entities
     {
         int vsize = 4;
         vector2 vecs[4] = {
             vector2(16.6f, 6.0f),
             vector2(16.6f, 7.0f),
             vector2(10.0f, 6.0f),
             vector2(10.0f, 7.0f)
         };



         for (int i = 0; i < vsize; i++) {
             D2entity* d = new D2entity(i, vecs[i]);
             stateMachine* m = new soldier(d);
             m->Construct();
             d->myMachine = m;
         }
     }




 }