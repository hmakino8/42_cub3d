typedef struct	s_ray
{
	double		posx; //position x du joueur
	double		posy; //position y du joueur
	double		dirx; //vecteur de direction (commence à -1 pour N, 1 pour S, 0 sinon)
	double		diry; //vecteur de direction (commence à -1 pour W, 1 pour E, 0 sinon)
	double		planx; //vecteur du plan (commence à 0.66 pour E, -0.66 pour W, 0 sinon)
	double		plany; //vecteur du plan (commence à 0.66 pour N, -0.66 pour S, 0 sinon)
	double		raydirx; //calcul de direction x du rayon
	double		raydiry; //calcul de direction y du rayon
	double		camerax; //point x sur la plan camera : Gauche ecran = -1, milieu = 0, droite = 1
	int		mapx; // coordonée x du carré dans lequel est pos
	int		mapy; // coordonnée y du carré dans lequel est pos
	double		sidedistx; //distance que le rayon parcours jusqu'au premier point d'intersection vertical (=un coté x)
	double		sidedisty; //distance que le rayon parcours jusqu'au premier point d'intersection horizontal (= un coté y)
	double		deltadistx; //distance que rayon parcours entre chaque point d'intersection vertical
	double		deltadisty; //distance que le rayon parcours entre chaque point d'intersection horizontal
	int		stepx; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int		stepy; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
	int		hit; // 1 si un mur a ete touche, 0 sinon
	int		side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	double		perpwalldist; // distance du joueur au mur
	int		lineheight; //hauteur de la ligne a dessiner
	int		drawstart; //position de debut ou il faut dessiner
	int		drawend; //position de fin ou il faut dessiner
	int		x; //permet de parcourir tous les rayons
}					t_ray;


/*

sidex = 64 - (player.pxl_x % 64)
sidey = 64 - (player.pxl_y % 64)


sidex = 10 - (1 % 10) = 9
sidey = 10 - (2 % 10) = 8

if (3 < 24)
if ( |sidex / deltax| < |sidey / deltay|)
{
	x de susumu
	ray.x = player.pxl_x + sidex;
	ray.y = player.pxl_y + sidex * deltay / BPP;

	sidex = BPP;
	sidey -= sidex * deltay / BPP;
}
else
{
	y de susumu
	ray.x = player.pxl_x + sidey * deltax / BPP;
	ray.y = player.pxl_y + sidey;

	sidex -= sidey * deltax / BPP;
	sidey = BPP;
}

start : (1, 2)
end : (130, 43)

deltax : (130 - 1) / (43 - 2) = 129 / 41
	= 3

deltay : (43 - 2) / (130 - 1) = 41 / 129
	= 1/3


*/
