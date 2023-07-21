#include "gameObject.h"

void gameObject::initialize() {
	if (img != NULL) {
		height = al_get_bitmap_width(*img);
		witdh = al_get_bitmap_height(*img);
	}
}

void gameObject::assignImg(ALLEGRO_BITMAP* *img_)
{
	img = *&img_;
}

void gameObject::moveTo(int x, int y) {
	posX = x;
	posY = y;
	
	
}

int gameObject::getX() {
	int a = posX - witdh/2;
	return a;
}

int gameObject::getY() {
	int a = posY - height/2;
	return a;
}

//Rectangular collision check only
bool gameObject::collidesWith(int x, int y) {
	{
		//Checks Horizontal collision
		if (x > getX() - witdh / 2 && x < getX() + witdh) {
			//Checks vertical collision
			if (y > getY() - height / 2 && y < getY() + height) {
				//it is colliding! return true
				
				return true;
			}
		}
		//it's not colliding, return false
		return false;
	}
}

ALLEGRO_BITMAP* **gameObject::getImg() {
	return &img;
}
