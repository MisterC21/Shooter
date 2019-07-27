#include "jeu.h"


int key[KEYMAX]={0,0,0,0};


void erreur(const char*txt)
{
    al_show_native_message_box(NULL,"ERREUR",txt,NULL,NULL,0);
    exit(EXIT_FAILURE);
}

ALLEGRO_DISPLAY *allegro_init(ALLEGRO_TIMER **timer, ALLEGRO_EVENT_QUEUE **queue, double tpsTimer)
{
    if(!al_init()){
        erreur("al_init()");
    }

    if(!al_install_keyboard()){
        erreur("al_install_keyboard");
    }

    if(!al_init_image_addon()){
        erreur("al_init_image_addon");
    }

    ALLEGRO_DISPLAY *display=NULL;
    display=al_create_display(SCREENX,SCREENY);

    *timer=al_create_timer(tpsTimer);
    *queue=al_create_event_queue();

    al_register_event_source(*queue, al_get_display_event_source(display));
    al_register_event_source(*queue, al_get_keyboard_event_source());
    al_register_event_source(*queue, al_get_timer_event_source(*timer));

    return(display);

}

bool collisionPerso(t_personnage *perso1, t_personnage *perso2)
{
    if(sqrt(pow(perso1->x+perso1->anim->tx/2-(perso2->x+perso2->anim->tx/2),2)+pow(perso1->y+perso1->anim->ty/2-(perso2->y+perso2->anim->ty/2),2))<=(perso1->anim->ty/2+perso2->anim->ty/2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

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
    perso->tpsInv=0;
    perso->vulnerable=true;
    perso->anim=animation;

    return perso;

}


void invinsibite_perso(t_personnage *perso, ALLEGRO_TIMER *timer, int dureeInv)
{

    int tps=al_get_timer_count(timer);

    if (perso->vulnerable==false && abs(tps-perso->tpsInv)>dureeInv)
    {
        perso->vulnerable=true;
        perso->tpsInv=tps;
    }
}

void destruct_perso(t_personnage **perso)
{
    free(*perso);
    *perso=NULL;
}

void collisionBalle(t_balle *balle, t_personnage *personnage, ALLEGRO_TIMER *timer)
{
    if (balle->x<=(personnage->x+personnage->anim->tx) && balle->x>=personnage->x && balle->y<=(personnage->y+personnage->anim->ty) && balle->y>=personnage->y && balle->lethal==true){
        balle->lethal=false;

            if((personnage->type==TJOUEUR1 || personnage->type==TJOUEUR2 ||personnage->type==TJOUEUR3) &&  personnage->vulnerable==true)
            {
                personnage->vie--;
                personnage->vulnerable=false;
                personnage->tpsInv=al_get_timer_count(timer);
            }

            else if(personnage->type==TENNEMI1 || personnage->type==TENNEMI2 ||personnage->type==TENNEMI3 || personnage->type==TENNEMI4)
            {
                personnage->vie--;
            }
    }

}

void deplacementBalle(t_balle *balle, int vit)
{
    if(balle->type==TJOUEUR1 || balle->type==TENNEMI1)
    {
        balle->y+=vit;
    }
    if(balle->type==TENNEMI2)
    {
        balle->y+=vit;
        balle->x-=vit;
    }

    if(balle->type==TENNEMI4)
    {
        balle->y+=vit;
        balle->x+=vit;
    }

    if(balle->type==TENNEMI3)
    {

        balle->x+=(balle->xfinal-balle->xinit)/(abs(balle->yfinal-balle->yinit)+abs(balle->xfinal-balle->xinit))*vit;
        balle->y+=(balle->yfinal-balle->yinit)/(abs(balle->yfinal-balle->yinit)+abs(balle->xfinal-balle->xinit))*vit;
    }

    if(balle->type==TJOUEUR2)
    {
        balle->y+=vit;
        float y=balle->yinit-balle->y;
        balle->x=balle->xinit+pow(-1,balle->sens)*pow(y/20,2);

    }

}

ALLEGRO_BITMAP *recup_bitmap(ALLEGRO_BITMAP *bmp, int x, int y, int tx, int ty, int nbrColonne, int ex, int ey, int numImage)
{
    ALLEGRO_BITMAP *image=al_create_bitmap(tx, ty);
    if(!image){
        erreur("create_bitmap");
    }

    int ix=x+numImage%nbrColonne*(ex+tx);
    int iy=y+numImage/nbrColonne*(ey+ty);

    al_set_target_bitmap(image);
    al_draw_bitmap(bmp,ix,iy,0);

    al_destroy_bitmap(bmp);

    return (image);
}


t_balle *construct_t_balle(t_personnage perso, t_personnage cible, int dx, int dy, char *nom, bool sens)
{
    t_balle *balle=(t_balle*)malloc(sizeof(t_balle));
    balle->x=perso.x+perso.anim->tx/2;
    balle->xinit=perso.x+perso.anim->tx/2;
    balle->tx=4;
    balle->ty=4;
    balle->dx=dx;
    balle->dy=dy;
    balle->type=perso.type;
    balle->sens=sens;
    balle->lethal=true;
    balle->balle=al_load_bitmap(nom);

    if(perso.type==TJOUEUR1 || perso.type==TJOUEUR2 || perso.type==TJOUEUR3)
    {
        balle->y=perso.y;
        balle->yinit=perso.y;
        balle->xfinal=0;
        balle->yfinal=0;
    }

    if(perso.type==TENNEMI1 || perso.type==TENNEMI2 || perso.type==TENNEMI3 || perso.type==TENNEMI4)
    {
        balle->y=perso.y+perso.anim->ty;
        balle->yinit=perso.y+perso.anim->ty;
        balle->xfinal=cible.x+cible.anim->tx;
        balle->yfinal=cible.y+cible.anim->ty;
    }

    if(!balle->balle){
        erreur("load_balle");
    }

    return balle;
}


void recupere_animation(t_animation *animation, int x, int y, int tx, int ty, int nbrColonne, int ex, int ey)
{
    ALLEGRO_BITMAP *bmp=al_load_bitmap(animation->nom);
    if(!bmp){
        erreur("load_bitmap_animation");
    }

    animation->animation=(ALLEGRO_BITMAP**)malloc(sizeof(ALLEGRO_BITMAP*)*animation->nbrImage);

    for(int i=0;i<animation->nbrImage;i++){
        animation->animation[i]=recup_bitmap(bmp,x,y,tx,ty,nbrColonne,ex,ey,i);

        if(animation->mask){
            al_set_target_bitmap(animation->animation[i]);
            al_convert_mask_to_alpha(animation->animation[i], al_get_pixel(animation->animation[i],0,0));
        }
    }
}


/*********************************************************************************************************/
t_personnage  **allouer_tableau(int nbPerso) {
  t_personnage **perso=(t_personnage**)malloc ( sizeof(t_personnage)*nbPerso);

  for(int i=0;i<nbPerso;i++)
  {
      perso[i]=NULL;
  }
  return perso;
}


void destruct_t_balle(t_balle *balle)
{
    if (balle->lethal==false || balle->x>SCREENX || balle->x<0 || balle->y>SCREENY || balle->y<0){
        free(balle);
        balle=NULL;
    }
}
