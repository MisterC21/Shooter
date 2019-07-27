#include "niveauUn.h"


void NIVEAUUN(int tps,t_personnage **ennemi,t_animation animPerso)
{
    switch(tps)
    {
        case 70:
            ennemi[0]=construct_t_personnage(SCREENX/2-96,-32,5,5,TENNEMI1,&animPerso);
            ennemi[1]=construct_t_personnage(SCREENX/2+96,-32,5,5,TENNEMI1,&animPerso);
            break;
        case 100:
            ennemi[2]=construct_t_personnage(0,-32,5,5,TENNEMI2,&animPerso);
            break;
      }
}

