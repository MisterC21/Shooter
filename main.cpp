#include "niveauUn.h"

/*Sans macro tes ennemis se crééent mais dès que tu tires ca plante bouffon. En vrai ca serait bien de developper un éditeur de niveau BITCH*/

extern int key[KEYMAX];
t_balle balle[NBRBALLE]={NULL};
t_balle *balleEnnemi[NBRBALLEENNEMI]={NULL};
t_personnage *ennemi[NBRENNEMI]={NULL};


int main()
{
    ALLEGRO_DISPLAY *display=NULL;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_TIMER *tirCadence;
    ALLEGRO_BITMAP *fond;
    bool fin=false;
    bool dessine=false;
    bool tirEn=false;
    int i=0, j=0, sens=0;
    int tps=0;

    display=allegro_init(&timer,&queue, 0.1);

    fond=al_load_bitmap("fondTest.bmp");

    t_animation animPerso={"persoTest.bmp",TX,TY,1,0,4,false};
    recupere_animation(&animPerso,0,0,TX,TY,1,0,0);
    t_personnage *perso=construct_t_personnage(SCREENX/2,SCREENY/2,10,10,TJOUEUR2,&animPerso);


    /*for(int i=0;i<NBRENNEMI;i++)
        {
            ennemi[i]=construct_t_personnage(SCREENX/2,32,5,5,TENNEMI4,&animPerso);
        }*/

    int yf=al_get_bitmap_height(fond)-SCREENY;

    al_set_target_backbuffer(display);

    al_start_timer(timer);

    while(!fin){

        ALLEGRO_EVENT event={0};
        al_wait_for_event(queue, &event);
        tps=al_get_timer_count(timer);


        if(event.type==ALLEGRO_EVENT_DISPLAY_CLOSE){
            fin=true;
        }

        if(event.type==ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    key[UP]=true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[LEFT]=true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[DOWN]=true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[RIGHT]=true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    balle[i]=construct_t_balle(*perso,*perso,0,0,"balle.bmp",sens);
                    i=(i+1)%NBRBALLE;
                    sens=(sens+1)%2;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    fin=true;
                    break;
            }
            dessine=true;
        }

        if(event.type==ALLEGRO_EVENT_KEY_UP){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    key[UP]=false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[LEFT]=false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[DOWN]=false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[RIGHT]=false;
                    break;
            }
        }


NIVEAUUN(tps,ennemi,animPerso);

        if(event.type==ALLEGRO_EVENT_TIMER){


            deplacementPerso(perso);
            for(int j=0;j<=NBRBALLE;j++){
                if (balle[j]!=NULL){
                    for(int i=0;i<NBRENNEMI;i++){
                        deplacementBalle(balle[j], -2);
                        if(ennemi[i]!=NULL){
                            collisionBalle(balle[j], ennemi[i], timer);
                        /*std::cout<<balle[0]->y<<"\n";*/
                            }
                        }
                    }
                }

                for(int i=0;i<NBRENNEMI;i++){
                    if(ennemi[i]!=NULL){
                        deplacementEnnemi(ennemi[i]);
                        collisionEnnemi(perso,*ennemi[i],timer);

                        tirEn=cadenceTir(perso,ennemi[i],timer);
                        if(tirEn)
                        {
                            balleEnnemi[j]=construct_t_balle(*ennemi[i],*perso,0,0,"balle.bmp",true);
                            j=(j+1)%NBRBALLEENNEMI;
                            }

                        if(ennemi[i]->vie<=0 && ennemi[i]!=NULL || ennemi[i]->y>SCREENY){
                            destruct_perso(&ennemi[i]);
                            }std::cout<<"PUTEUH"<<"\n";
                        }
                    }

                    for(int k=0;k<=NBRBALLEENNEMI;k++){
                                if(balleEnnemi[k]!=NULL)
                                {
                                    collisionBalle(balleEnnemi[k], perso, timer);
                                    deplacementBalle(balleEnnemi[k],7);
                                }
                        }
                        invinsibite_perso(perso,timer,50);
                            if(perso->vie<=0 && perso!=NULL)
                                        {
                                            destruct_perso(&perso);
                                            fin=true;
                                            break;
                                        }

                        yf=(yf-PAS);

        }


        if(dessine=true && al_event_queue_is_empty(queue)){
            if(yf<0)
            {
                yf=al_get_bitmap_height(fond)-SCREENY;
            }
            al_draw_bitmap_region(fond,0,yf,SCREENX,SCREENY,0,0,0);
            for(int i=0;i<NBRENNEMI;i++){
            if (ennemi[i]!=NULL){std::cout<<ennemi[i]<<"\n";

                al_draw_bitmap(ennemi[i]->anim->animation[ennemi[i]->imageCourante], ennemi[i]->x,ennemi[i]->y,0);

            }
            }


            if (perso!=NULL)
                {
                    al_draw_bitmap(perso->anim->animation[perso->imageCourante], perso->x,perso->y,0);
                }

            for (int j=0;j<=10;j++){
                if (balle[j]!=NULL && balle[j]->lethal==true){
                    al_draw_bitmap(balle[j]->balle, balle[j]->x,balle[j]->y,0);
                }
            }

            for (int j=0;j<NBRBALLEENNEMI;j++){
                if (balleEnnemi[j]!=NULL && balleEnnemi[j]->lethal==true){
                    al_draw_bitmap(balleEnnemi[j]->balle, balleEnnemi[j]->x,balleEnnemi[j]->y,0);
                    }
            }

            al_flip_display();
        }
    }

    for (int j=0;j<=NBRBALLE;j++){
          free(balle[j]);
                    }
    for (int j=0;j<=NBRBALLEENNEMI;j++){
          free(balleEnnemi[j]);
                    }
    al_destroy_event_queue(queue);
    for(int i=0;i<NBRENNEMI;i++){
        if(ennemi[i]!=NULL)
            {
             destruct_perso(&ennemi[i]);
            }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);


    if (perso==NULL)
    {
        erreur("Echec Bitch");
    }

     else
     {
         destruct_perso(&perso);
     }

    return(0);

}
