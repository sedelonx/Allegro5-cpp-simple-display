#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdint.h>
#include <string>

using namespace std;


class gameObject
{
public:
	gameObject() {
		name = "gameObjet";
		id = 0;
	}
	gameObject(string n) {
		name = n;
	}
	gameObject(string n, int i) {
		name = n;
		id = i;
	}
	string name;
	string tag;
	int id;
private:
	int posX = 0;
	int posY = 0;
	int posZ = 0;

	

	bool isCol = false;
	bool isActive;
	ALLEGRO_BITMAP* *img;

	
public:	
	int height = 0;
	int witdh = 0;
	void initialize();
	void assignImg(ALLEGRO_BITMAP* *img_);
	void moveTo(int x, int y);

	int getX();
	int getY();
	ALLEGRO_BITMAP* **getImg();

	//Check collision for RECTANGULAR OBJECTS ONLY
	bool rigidBody = true;
	bool collidesWith(int x, int y);

};

