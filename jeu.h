#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include <math.h>
#include <time.h>

#define SCREENX 960
#define SCREENY 640
#define TX 32
#define TY 32
#define PAS 5


#define NBRENNEMI 10
#define NBRBALLE 5
#define NBRBALLEENNEMI 50

enum{UP, RIGHT, DOWN, LEFT, KEYMAX};
enum{TJOUEUR1,TJOUEUR2,TJOUEUR3,TENNEMI1,TENNEMI2,TENNEMI3,TENNEMI4};

typedef struct{
    char *nom;
    int tx, ty;
    int nbrImage;
    int cptImage;
    int dureeTour;
    bool mask;
    ALLEGRO_BITMAP **animation;

}t_animation;

typedef struct{
    int x, y;
    int dx, dy;
    int imageCourante;
    int vie;
    int cadenceTir;
    int type;
    int tpsInv;
    bool vulnerable;
    t_animation *anim;

}t_personnage;


typedef struct{
    float x, y;
    float xinit, yinit;
    float xfinal, yfinal;
    int tx, ty;
    int dx, dy;
    int type;
    bool sens;
    bool lethal;
    ALLEGRO_BITMAP *balle;

}t_balle;


void erreur(const char*txt);
ALLEGRO_DISPLAY *allegro_init(ALLEGRO_TIMER **timer, ALLEGRO_EVENT_QUEUE **queue, double tpsTimer);
bool collisionPerso(t_personnage *perso1, t_personnage *perso2);
t_balle *construct_t_balle(t_personnage perso, t_personnage cible,int dx, int dy, char *nom, bool sens);
ALLEGRO_BITMAP *recup_bitmap(ALLEGRO_BITMAP *bmp, int x, int y, int tx, int ty, int nbrColonne, int ex, int ey, int numImage);
void recupere_animation(t_animation *animation, int x, int y, int tx, int ty, int nbrColonne, int ex, int ey);
void deplacementBalle(t_balle *balle, int vit);
void collisionBalle(t_balle *balle, t_personnage *personnage, ALLEGRO_TIMER *timer);
void deplacementPerso(t_personnage *perso);
void destruct_perso(t_personnage **perso);
t_personnage *construct_t_personnage(int x, int y, int dx, int dy, int type, t_animation *animation);
void invinsibite_perso(t_personnage *perso, ALLEGRO_TIMER *timer, int dureeInv);

t_personnage  **allouer_tableau(int nbPerso);
t_personnage ***construct_t_personnage_pointeur(t_personnage **perso, int nbrPerso);
void destruct_t_balle(t_balle *balle);
