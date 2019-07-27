#include "ennemi.h"


void deplacementEnnemi(t_personnage *perso)
{
    if (perso->type==TENNEMI1)
    {
        perso->y+=perso->dy;
    }

    if (perso->type==TENNEMI2)
    {
        perso->y+=perso->dy;
        perso->x+=perso->dx;
    }

     if (perso->type==TENNEMI3)
    {
        perso->y+=PAS;
    }

    if (perso->type==TENNEMI4)
    {
        perso->y+=perso->dy;
        perso->x-=perso->dx;
    }

}


bool cadenceTir(t_personnage *perso, t_personnage *ennemi, ALLEGRO_TIMER *timer)
{
    int timeValue=0;
    timeValue=al_get_timer_count(timer);
    /*std::cout<<perso->y<<"\n";*/

    if (ennemi->type==TENNEMI1 && perso->y>ennemi->y+2*ennemi->anim->ty && (perso->x>=ennemi->x-ennemi->anim->tx && perso->x<=ennemi->x+ennemi->anim->tx) && abs(timeValue-ennemi->cadenceTir)>=10)
        {
            ennemi->cadenceTir=timeValue;
            return true;
        }
    else if (ennemi->type==TENNEMI2 && (perso->y<=5*perso->anim->ty-perso->x+ennemi->y+ennemi->x && perso->y>=-5*perso->anim->ty-perso->x+ennemi->y+ennemi->x) && abs(timeValue-ennemi->cadenceTir)>=5)
        {
            ennemi->cadenceTir=timeValue;
            return true;
        }
    else if (ennemi->type==TENNEMI4 && (perso->y<=5*perso->anim->ty+perso->x+ennemi->y-ennemi->x && perso->y>=-5*perso->anim->ty+perso->x+ennemi->y-ennemi->x) && abs(timeValue-ennemi->cadenceTir)>=5)
        {
            ennemi->cadenceTir=timeValue;
            return true;
        }

    else if (ennemi->type==TENNEMI3 && ennemi->y<SCREENY && abs(timeValue-ennemi->cadenceTir)>=5)
        {
            ennemi->cadenceTir=timeValue;
            return true;
        }

    else
    {
        return false;
    }
}

void collisionEnnemi(t_personnage *perso, t_personnage ennemi, ALLEGRO_TIMER *timer)
{
    if(perso->vulnerable==true && collisionPerso(perso,&ennemi))
    {
        perso->vulnerable=false;
        perso->vie--;
        perso->tpsInv=al_get_timer_count(timer);
    }
}

