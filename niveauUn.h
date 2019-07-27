#include "ennemi.h"

#define NIVEAU(timer,ennemi,animPerso)\
{\
     int tps=0;\
    tps=al_get_timer_count(timer);\
    switch(tps)\
    {\
        case 70:\
            ennemi[0]=construct_t_personnage(SCREENX/2-96,-32,5,5,TENNEMI1,&animPerso);\
            ennemi[1]=construct_t_personnage(SCREENX/2+96,-32,5,5,TENNEMI1,&animPerso);\
            break;\
        case 100:\
            ennemi[2]=construct_t_personnage(0,-32,5,5,TENNEMI2,&animPerso);\
            break;\
        case 105:\
            ennemi[3]=construct_t_personnage(0,-32,5,5,TENNEMI2,&animPerso);\
            break;\
         case 110:\
            ennemi[4]=construct_t_personnage(0,-32,5,5,TENNEMI2,&animPerso);\
            break;\
        case 115:\
            ennemi[5]=construct_t_personnage(SCREENX,-32,5,5,TENNEMI4,&animPerso);\
            break;\
        case 120:\
            ennemi[6]=construct_t_personnage(SCREENX,-32,5,5,TENNEMI4,&animPerso);\
            break;\
         case 125:\
            ennemi[7]=construct_t_personnage(SCREENX,-32,5,5,TENNEMI4,&animPerso);\
            break;\
         case 160:\
            ennemi[8]=construct_t_personnage((SCREENX+TX)/2,-32,5,5,TENNEMI3,&animPerso);\
            break;\
\
    }\
}\

void NIVEAUUN(int tps,t_personnage **ennemi,t_animation animPerso);
