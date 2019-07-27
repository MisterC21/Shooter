#include "jeu.h"


bool cadenceTir(t_personnage *perso, t_personnage *ennemi, ALLEGRO_TIMER *timer);
void deplacementEnnemi(t_personnage *perso);
void collisionEnnemi(t_personnage *perso, t_personnage ennemi, ALLEGRO_TIMER *timer);
