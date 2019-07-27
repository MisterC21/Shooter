#include "perso.h"


void deplacementPerso(t_personnage *perso)/*Fonction à améliorer pour collision*/
{
    int x, y;

    x=perso->x+key[RIGHT]*perso->dx-key[LEFT]*perso->dx;
    y=perso->y+key[DOWN]*perso->dy-key[UP]*perso->dy;

    if(x>=0 && x+perso->anim->tx<=SCREENX && y>=0 && y+perso->anim->ty<=SCREENY){
        perso->x=x;
        perso->y=y;
    }
}

t_personnage *construct_t_personnage(int x, int y, int dx, int dy, int type, t_animation *animation)
{
    t_personnage *perso=NULL;
    perso=(t_personnage*)malloc(sizeof(t_personnage));
    perso->x=x;
    perso->y=y;
    perso->dx=dx;
    perso->dy=dy;
    perso->vie=3;
    perso->cadenceTir=0;
    perso->imageCourante=0;
    perso->type=type;
    perso->vulnerable=true;
    perso->anim=animation;

    return perso;

}

void destruct_perso(t_personnage **perso)
{
    free(*perso);
    *perso=NULL;
}
