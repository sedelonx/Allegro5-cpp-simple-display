#include "gameObjectRenderer.h"
#include "gameObject.h"
#include <string>
#include <vector>

void gameObjectRenderer::renderObjs() {
	for (int i = 0; i < toRender.size(); i++)
	{
		//print name of object rendering
		//printf(("size is " + to_string(toRender.size()) + "\n" ).c_str());
		// print position of Y rendering
		//printf(("rendering at " + to_string(toRender[i]->getY())).c_str());
		gameObject* gO = &*toRender[i];
		//printf(((*gO).name + "\n").c_str());
		ALLEGRO_BITMAP*** aa = (*gO).getImg();
		al_draw_bitmap(**aa, (*gO).getX(), (*gO).getY(), 0);
	}
}
void gameObjectRenderer::renderObjsFromArray(gameObject **ar, int size) {
	for (int i = 0; i < size; i++)
	{
		//print name of object rendering
		//printf(("size is " + to_string(toRender.size()) + "\n").c_str());
		// print position of Y rendering
		//printf(("rendering at " + to_string(toRender[i]->getY())).c_str());
		//gameObject* gO = &*toRender[i];
		//printf(((*gO).name + "\n").c_str());
		ALLEGRO_BITMAP*** aa = (*ar[i]).getImg();
		al_draw_bitmap(**aa, (*ar[i]).getX(), (*ar[i]).getY(), 0);
	}
}

vector<gameObject**> gameObjectRenderer::findTagged(string tag) {
	vector <gameObject**> found;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->tag == tag) {
			found.push_back(&objects[i]);
		}
	}
	if (found[0] != NULL) return found;
	
	
	vector<gameObject**> a;
	a.begin();
	return a;
	
}

vector<gameObject**> gameObjectRenderer::checkCol(int x, int y) {
	vector<gameObject**> found;
	for (int i = 0; i < objects.size(); i++) {
		
		if (objects[i]->collidesWith(x, y)) found.push_back(&objects[i]);
	}
	return found;
}

vector<gameObject**> gameObjectRenderer::checkCol(int x, int y, string tag) {
	
	vector<gameObject**> found;
	found = (findTagged(tag));
	objectsTagged = found;
	found.clear();
	for (int i = 0; i < objectsTagged.size(); i++) {
		if((*objectsTagged[i])->collidesWith(x, y)){ found.push_back(objectsTagged[i]); }
		
	}
	return found;
}