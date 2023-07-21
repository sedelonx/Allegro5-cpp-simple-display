#include <iostream>
#include <stdint.h>
#include <string>
#include <allegro5/allegro.h>
#include<allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "gameObject.h"
#include "gameObjectRenderer.h"
#include <vector>
#include <ctime>
#include <list>
#include <allegro5/utf8.h>
#include <Windows.h>
#include <fstream>
#include <filesystem>






gameObject cosas[850];
gameObject *particles[850];


using namespace std;
bool running = true;
bool redraw = true;
int mouseX;
int mouseY;



//Variables for school project, will be commented out later.
//positive is going lower, so it's in reverse
//DFEFAULT OF FRAMESTOSPAWN IS 180
ALLEGRO_BITMAP* fishimg;
vector<ALLEGRO_BITMAP*> pIMGS;
int spawned = 0;
int framesToSpawn = 130;
int currentFrameCounter;
int particleYspeed = 5;
vector<string> dialogs {"", "En el vasto océano azul, hogar de innumerables maravillas, un enemigo invisible se cierne en las profundidades: los microplásticos.", "Estas diminutas partículas de destrucción flotan sin cesar, como fantasmas tóxicos,", "arrastrando consigo un legado de contaminación y tristeza.", "Una vez nacidos como productos de nuestra insensata dependencia del plástico,", "estos pequeños demonios se desprenden de sus formas originales, descomponiéndose en pedazos cada vez más pequeños.", "Y así, con cada fragmento, crece su poder destructivo, arrojado al mar como un cruel desprecio por el delicado equilibrio natural.", "Los microplásticos se infiltran en las vidas de las criaturas marinas inocentes, engañándolas con su apariencia disfrazada.", "Los peces, con sus ojos curiosos, confunden estos fragmentos con alimento esencial, y sin saberlo, se tragan un veneno que corroe sus entrañas.", "Las tortugas, majestuosas guardianas de los océanos, quedan atrapadas en una red de plástico, su movimiento obstaculizado por una trampa mortal.", "Y las aves marinas, cuyos vuelos solían ser un símbolo de libertad, caen víctimas de su propia gula, llenando sus estómagos con pequeñas partículas que les roban la vida.", "La contaminación silenciosa se propaga, afectando a todos los niveles del ecosistema marino.", "Desde los organismos más pequeños hasta los más grandes, ningún ser vivo escapa a la sombra tóxica que proyectan los microplásticos.", "La biodiversidad se desvanece lentamente, mientras los corales, esos arrecifes vibrantes y coloridos que albergaban tanta vida, se desvanecen en un mar de plástico, privados de la vitalidad que los sustentaba.", "Y ¿qué somos nosotros, los responsables de este caos?", "Somos los testigos de un crimen ecológico, los perpetuadores de una tragedia que amenaza la supervivencia de nuestro propio hogar.", "No podemos cerrar los ojos ante el sufrimiento causado por nuestras acciones irresponsables.", "Cada bolsa de plástico que flota sin control, cada envase descartable que maltrata las olas, nos implica en esta catástrofe en curso.", "Pero aún hay esperanza.", "Aún podemos desafiar a los microplásticos y restaurar el esplendor perdido de nuestros océanos.", "A través de la educación y la conciencia, podemos cambiar nuestra forma de consumir y exigir alternativas sostenibles.", "Podemos trabajar juntos para reducir la producción de plástico, reciclar con diligencia y limpiar nuestras playas de esta plaga dañina.", "El océano nos necesita, y es nuestra responsabilidad protegerlo.", "Es hora de que abracemos la valentía y el amor por la naturaleza que arde en nuestro interior.", "Juntos, podemos liberar a los océanos de la prisión de los microplásticos y permitir que vuelvan a ser un refugio de vida, belleza y armonía.", "Es tiempo de actuar, antes de que el último suspiro de los mares llegue"};
vector<ALLEGRO_USTR*> tt;
ALLEGRO_USTR *toDrawUST;
int toChangeText = 240;
int textInded = 0;
bool fishMoving = false;
string toDraw;
bool toPhy;
bool toRender;
gameObject fish;


bool spawn = true;

vector<int> positions;


//vector<gameObject*> particles(625);

//Declaration of short functions
void credits();
void checkMouseState(ALLEGRO_MOUSE_STATE& state, gameObjectRenderer& rend);
void particlePhysics();
void spawnParticle(ALLEGRO_BITMAP* *img, gameObjectRenderer* ren);
void particleTimer();
void textStory();
void fishPhysics();
ALLEGRO_BITMAP* *getImgs();





int main() {

	
	
	
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);


	//initialize addons

	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();

	credits();

	//tt = { al_ustr_new("ds") , al_ustr_new("re loco jaja ááááá") };
	//toDrawUST = al_ustr_new("aáñ");
	srand(time(0));
	gameObjectRenderer renderer;
	;
	//positions.begin();
	for (int i = 0; i < 25; i++) {
		positions.push_back(0);
	}

	//ANTI-CRASH OBJECTS - WHEN FINDING OBJECTS WITH TAGS, THERE MUST BE AT LEAST BE ONE OBJECT WITH THAT TAG OR
	//THE PROGRAMM CRASHES
	//FOR CHECKING OBJECTS COLLISIONS; THEY MUST BE IN THE gameObjectRenderer VARIABLE objects ATTRIBUTE. 
	//OBJECTS THAT ARE NOT IN THE objects ATTRIBUTE WILL NOT BE CHECKED FOR COLLISIONS.

	
	
	

	

	//Declare basic variables to display
	ALLEGRO_BITMAP* img = al_load_bitmap("resources/images/save_icon.png");
	ALLEGRO_BITMAP* img_ = al_load_bitmap("resources/images/save_icon.png");
	ALLEGRO_BITMAP* bg = al_load_bitmap("resources/images/bg.png");
	pIMGS.push_back(al_load_bitmap("resources/images/part0.png"));
	pIMGS.push_back(al_load_bitmap("resources/images/part1.png"));
	pIMGS.push_back(al_load_bitmap("resources/images/part2.png"));
	pIMGS.push_back(al_load_bitmap("resources/images/part3.png"));
	ALLEGRO_FONT* text = al_load_font("resources/fonts/Arial.ttf", 24, 0);
	ALLEGRO_FONT* consolaText = al_load_font("resources/fonts/CONSOLA.ttf", 24, 0);
	ALLEGRO_MONITOR_INFO info;
	
	//renderer.toRender.push_back(&go);
	//renderer.objects.push_back(&go);


	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_set_new_display_flags(ALLEGRO_NOFRAME);

	al_get_monitor_info(0, &info);

	//CREATE DISPLAY WITH MONITOR RESOLUTION
	// //FULL SCREEN
	//ALLEGRO_DISPLAY* disp = al_create_display((info.x2 - info.x1 + 1), (info.y2-info.y1+1));
	ALLEGRO_DISPLAY* disp = al_create_display((500), (500));
	
	
	//al_set_window_position(disp, (info.x2 - info.x1 + 1)/2, (info.y2 - info.y1 + 1)/2);
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_mouse_event_source());
	
	
	al_start_timer(timer);
	ALLEGRO_EVENT event;
	ALLEGRO_MOUSE_STATE mouseState;
	ALLEGRO_KEYBOARD_STATE keyboardState;


	//school project of microplastics test run shit down below
	///
	//gameObject p("patata");

	fishimg = al_load_bitmap("resources/images/fish.png");
	//ALLEGRO_BITMAP* ppp = al_load_bitmap("resources/images/p1.png");
	fish.assignImg(&fishimg);
	fish.initialize();
	fish.moveTo(1000, 0);
	renderer.toRender.push_back(&fish);
	
	//p.assignImg(&ppp);
	//p.initialize();
	//p.moveTo(200, 200);
	//particles.push_back(&p);
	//renderer.toRender.push_back(&p);
	///
	//GAME LOOP
	
	

	while (running) {

		al_wait_for_event(queue, &event);
		

		

		if (event.type == ALLEGRO_EVENT_TIMER) redraw = true;
		else if ((event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)) {
			break;
		}
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			mouseX = event.mouse.x;
			mouseY = event.mouse.y;
		}
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				running = false;
				break;
		
			}
		}

		
		al_get_mouse_state(&mouseState);
		//MOUSE INPUT STUFF
		//checkMouseState(mouseState, renderer);
		if (redraw && al_is_event_queue_empty(queue)) {
			al_clear_to_color(ALLEGRO_COLOR(al_map_rgb(0,0,0)));

			//al_draw_bitmap(*(&bg), 0, 0, 0);
			textStory();
			particleTimer();
			if (spawn == true) { 
				spawnParticle((getImgs()), &renderer);
				//gameObject m = particlesOBJ[0];
				
				
				//(*particles[0]).moveTo(2, 43);
				
			}
			

			particlePhysics();
			fishPhysics();
			
			

			//for (int i = 0; i < particlesOBJ.size(); i++) {
			//	printf((particlesOBJ[i].name + " \n").c_str());
			//}
			
			
			
			
			al_draw_multiline_text(consolaText, al_map_rgb(255, 255, 255), 250, 100, 450, 30, ALLEGRO_ALIGN_CENTRE, toDraw.c_str());
			renderer.renderObjsFromArray(particles, spawned);
			renderer.renderObjs();
			//al_draw_tinted_bitmap(pIMGS[2], al_map_rgba(0, 0, 0, 0.7), 200, 200, 0);
			al_flip_display();
			
			redraw = false;
		};
	}
	
	

	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;

}


void debugInfo(ALLEGRO_FONT* &text, gameObject &go) {
	al_draw_text(text, al_map_rgb(255, 255, 255), 0, 0, 0, to_string(mouseX).c_str());
	al_draw_text(text, al_map_rgb(255, 255, 255), 0, 20, 0, to_string(go.getX() + go.witdh / 2).c_str());
	al_draw_text(text, al_map_rgb(255, 255, 255), 0, 40, 0, to_string(mouseY).c_str());
	al_draw_text(text, al_map_rgb(255, 255, 255), 0, 60, 0, to_string(go.getY() + go.height / 2).c_str());
	al_draw_text(text, al_map_rgb(255, 255, 255), 0, 80, 0, to_string(go.getY()).c_str());
}


void checkMouseState(ALLEGRO_MOUSE_STATE &state, gameObjectRenderer &rend) {
	gameObjectRenderer *r = &rend;
	
	if (state.buttons & 1) {
		vector<gameObject**> clicked;
		
		clicked = (r->checkCol(mouseX, mouseY));
		
		for (int i = 0; i < clicked.size(); i++) {
			//gameObject ***g = &clicked[i];
			//(***g).getX
			// 
			// get gameobject atributes with its pointer to not duplicate it
			//((**(clicked[i])).name);

			//printf(((**(clicked[i])).name).c_str());
			(**(clicked[i])).moveTo(mouseX, mouseY);
		}

		//printf(to_string(clicked.size()).c_str());
	}
	else if (state.buttons & 2) {
		try {
			vector<gameObject**> clicked;

			clicked = (r->checkCol(mouseX, mouseY, "cosa"));

			for (int i = 0; i < clicked.size(); i++) {
				//gameObject ***g = &clicked[i];
				//(***g).getX
				// 
				// get gameobject atributes with its pointer to not duplicate it
				//((**(clicked[i])).name);

				//printf(((**(clicked[i])).name).c_str());
				(**(clicked[i])).moveTo(mouseX, mouseY);
			}

			//printf(to_string(clicked.size()).c_str());
		}
		catch (...) { printf("NO OBJECT OF SPECIFIED TAG FOUND"); }
	}
};


//kind of a rigid body but only for a school project, will be commented after
void particlePhysics() {

	for (int i = 0; i < spawned; i++) {

		

		//printf((**toMove).name.c_str());
		//printf("\n");
		
		int actualy = ((*particles[i]).getY() + ((*particles[i]).height / 2));
		
		//(*particles[i]).moveTo(((*particles[i]).getX() + (*particles[i]).witdh/2), actualy + particleYspeed);
		for (int j = 0; j < spawned; j++) {



			//printf((**toMove).name.c_str());
			//printf("\n");

			if (((*particles[j]).collidesWith((*particles[i]).getX() + (*particles[i]).witdh/2, (*particles[i]).getY() + (*particles[i]).height/2))) {
				if (&(*particles[j]) != &(*particles[i])) {
					(*particles[i]).rigidBody = false;
				}
			}
			
				//+ ((*particles[i]).height / 2));

			

		}
		if ((*particles[i]).getY() + (*particles[i]).height / 2 >= 500){
			(*particles[i]).rigidBody = false;
		}
		if ((*particles[i]).rigidBody)(*particles[i]).moveTo(((*particles[i]).getX() + (*particles[i]).witdh / 2), actualy + particleYspeed);
	}

}

void spawnParticle(ALLEGRO_BITMAP* *img, gameObjectRenderer *ren) {
	spawn = false;
	//particlesOBJ.push_back(gameObject("PARTI "+to_string(particlesOBJ.size())));
	bool posible = false;
	int rx = 1 + (rand() % 25);
	while (positions.at(rx-1) != 0) {
		//printf("repeated thing");
		rx = 1 + (rand() % 25);
		while (!posible) {
			for (int l = 0; l < 25; l++) {
				if (positions.at(l) == 0) {
					posible = true;
					break;
				}
				
			}

			if (posible)break;

			for (int m = 0; m < 25; m++) {
					positions.at(m) = 0;
			}
				
		}
	}
	positions.at(rx - 1) = 1;
	cosas[spawned] = gameObject("PARTI " + to_string(spawned));

	cosas[spawned].assignImg(img);
	cosas[spawned].initialize();

	//*ren).objects.push_back(&(particlesOBJ.back()));
	particles[spawned] = ((&(cosas[spawned])));

	cosas[spawned].moveTo((rx-1) * 20+10, -20);

	//string a = (*particles.back()).name;
	//int b = (*particles.back()).witdh;

	//printf((to_string(b)).c_str());


	framesToSpawn -= 1;
	if (framesToSpawn <= 3)framesToSpawn = 3;
	currentFrameCounter = 0;
	spawned++;


	//printf((to_string(spawned) + ("mhm\n")).c_str());

	
}

void particleTimer() {
	currentFrameCounter++;
	if (currentFrameCounter >= framesToSpawn) {
		
		spawn = true;
		currentFrameCounter = 0;
	}
}

void textStory() {
	toChangeText--;
	if (toChangeText <= 0 && textInded+1 < dialogs.size()) {
		
			//printf(to_string(dialogs.size()).c_str());
			if (toDraw == ("")) {
				textInded++;
				toDraw = dialogs[textInded];
				//toDrawUST = tt.at(textInded);
				toChangeText = 360;
			}
			else {
				toDraw = ("");
				toChangeText = 30;
			}
	}
}

void fishPhysics() {

	if (spawned == 840) {
		//spawned = 0;
		framesToSpawn = 130;
		textInded = 0;
		toDraw = dialogs[0];
		toChangeText = 240;
		fishMoving = true;
		fish.moveTo(1150, 300);

	}
	if (fishMoving) {
		fish.moveTo(fish.getX() + fish.witdh  / 2 -20, 380);
		if (fish.getX() + fish.witdh / 2 == 250) {
			spawned = 0;
		}
		if (fish.getX() + fish.witdh / 2 == -1050) {
			fishMoving = false;
		}
	}
}

void credits() {
	
	cout << "Profundidades" << endl;
	cout << "Programador: Gabriel Lautaro Antequera" << endl;
	cout << "Escritoras: Antonela María Girardi - Mía Panuccio" << endl;
	cout << "Diseñadora gráfica: Victoria Abril Alcoba" << endl;
}

ALLEGRO_BITMAP* *getImgs() {
	int r = (rand() % 4);
	//cout << to_string(r).c_str() << endl;
	return &pIMGS[r];
}