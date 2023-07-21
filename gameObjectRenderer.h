#pragma once
#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "gameObject.h"
#include <vector>
#include <string>


using namespace std;

class gameObjectRenderer
{
public:
	vector<gameObject*> objects;
	vector<gameObject*> toRender;
	vector<gameObject**> objectsTagged;

	void renderObjs();
	void renderObjsFromArray(gameObject** ar, int size);

	vector<gameObject**> findTagged(string tag);
	vector<gameObject**> checkCol(int x, int y);
	vector<gameObject**> checkCol(int x, int y, string tag);
};

