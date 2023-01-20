#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define NAVEGACAO 0
#define BATALHA 1
#define MENU 2
#define INSTRUCOES 3
#define TAM_HEROI 30
#define TAM_OBJ 50
#define PASSO 30
#define MAX_DIST 50
#define FUGIR 0
#define ATACAR 1
#define ESPECIAL 2
#define EASY 1
#define MEDIO 2
#define HARD 3
#define BOSS 4
#define AMIGA 5
#define MAXEASY 9
#define MAXMEDIO 5
#define MAXHARD 3
#define MAXBOSS 1
#define MAXAMIGAS 3
#define MAXTAM 30


const float FPS = 15;  

const int SCREEN_W = 960;
const int SCREEN_H = 540;

int CEU_H;
int X_OPT, Y_OPT;
int deslocx;

ALLEGRO_FONT *FONTE;
ALLEGRO_FONT *FONTEINFO;

int random(int n) {
	return rand()%n;
}

int randInt(int min, int max) {
	return min + random(max - min + 1);
}

typedef struct Heroi

{
	ALLEGRO_BITMAP *imagem;
	int x, y;
	ALLEGRO_COLOR cor;
	int vida;
	
	//BATALHA
	
	int acao;
	int executar;
	int x_old;
	int y_old;
	int pontuacao;
	int atacando;
	int travatecla;
	int numespecial;
	int ativacheat;
	int revelainimigos;
		
} Heroi;

typedef struct ataqueHeroi

{
	int x, y, r;
	ALLEGRO_COLOR cor;
	int dano;	
	
} ataqueHeroi;

typedef struct ataqueEspecial

{
	int x, y, r;
	ALLEGRO_COLOR cor;
	int dano;	
	
} ataqueEspecial;

typedef struct ataqueCheat

{
	int x, y, r;
	ALLEGRO_COLOR cor;
	int dano;
	
} ataqueCheat;

typedef struct Amiga

{
	int x, y;
	int bonus;
	
} Amiga;

typedef struct MonstroEasy

{
	int x,y;
	int vida;
	int pontos;

} MonstroEasy;

typedef struct ataqueEasy

{
	int x, y, r;
	ALLEGRO_COLOR cor;
	int dano;	
	
} ataqueEasy;

typedef struct MonstroMedio

{
	int x,y;
	int vida;
	int pontos;
	
} MonstroMedio;

typedef struct ataqueMedio

{
	int x, y, r;
	ALLEGRO_COLOR cor;
	int dano;	
	
} ataqueMedio;

typedef struct MonstroHard

{
	int x,y;
	int vida;
	int pontos;

} MonstroHard;

typedef struct ataqueHard

{
	int x, y, r;
	ALLEGRO_COLOR cor;
	int dano;	
	
} ataqueHard;

typedef struct MonstroBoss

{
	int x,y;
	int vida;
	int pontos;
	
} MonstroBoss;

typedef struct ataqueBoss

{
	int x, y, r;
	ALLEGRO_COLOR cor;
	int dano;
	
} ataqueBoss;

typedef struct Opcao

{
	int x,y,r;
	ALLEGRO_COLOR cor;
	int telamenu, inst;
	
} Opcao;

void initHeroi(Heroi *h)

{
	h->imagem = al_load_bitmap("pactras.png");
	h->x = 0;
	h->y = SCREEN_H - TAM_HEROI;
	h->cor = al_map_rgb(225,32,65);
	h->vida = 100;
	h->acao = 5;
	h->executar = 0;
	h->x_old = h->x;
	h->y_old = h->y;
	h->pontuacao = 0;
	h->atacando = 0;
	h->travatecla = 0;
	h->numespecial = 5;
	h->ativacheat = 0;
	h->revelainimigos = 0;
}

void initataqueHeroi(ataqueHeroi *atqhero)

{
	atqhero->x = 700;
	atqhero->y = SCREEN_H / 2;
	atqhero->r = 15;
	atqhero->cor = al_map_rgb(255,255,0);
	atqhero->dano = 15;	
}

void initataqueEspecial(ataqueEspecial *atqesp)

{
	atqesp->x = 700;
	atqesp->y = SCREEN_H / 2;
	atqesp->cor = al_map_rgb(255,255,0);
	srand(time(NULL));
	atqesp->dano = randInt(25,30);
	atqesp->r = atqesp->dano;
}

void initataqueCheat(ataqueCheat *atqcheat)

{
	atqcheat->x = 700;
	atqcheat->y = SCREEN_H / 2;
	atqcheat->cor = al_map_rgb(255,255,255);
	atqcheat->dano = 200;
	atqcheat->r = 20;
}

void initAmiga(Amiga *amiga)

{
	//srand(time(NULL));
	amiga->x = randInt(TAM_HEROI + MAX_DIST, SCREEN_W - TAM_OBJ + 20);
	amiga->y = randInt(5, SCREEN_H - 10);
	amiga->bonus = randInt(15,25);
	
}
	

void initMonstroEasy(MonstroEasy *m)

{
	m->x = randInt(TAM_HEROI + MAX_DIST,500);
	m->y = randInt(5,SCREEN_H - 10);
	m->vida = 30;
	m->pontos = 30;
}

void initataqueEasy(ataqueEasy *atqe)
{
	
	atqe->x = 250;
	atqe->y = Y_OPT - 250/2;
	srand(time(NULL));
	atqe->dano = randInt(2,5);
	atqe->r = atqe->dano;
	atqe->cor = al_map_rgb(204,255,255);
}

void initMonstroMedio(MonstroMedio *m)

{
	m->x = randInt(400,700);
	m->y = randInt(5,SCREEN_H - 10);
	m->vida = 45;
	m->pontos = 45;
}

void initataqueMedio(ataqueMedio *atqm)

{
	atqm->x = 250;
	atqm->y = Y_OPT - 250/2;
	srand(time(NULL));
	atqm->dano = randInt(5,8);
	atqm->r = atqm->dano;
	atqm->cor = al_map_rgb(51,255,51);	
}

void initMonstroHard(MonstroHard *m)

{
	m->x = randInt(600,800);
	m->y = randInt(5,SCREEN_H - 10);
	m->vida = 75;
	m->pontos = 75;
}

void initataqueHard(ataqueHard *atqh)

{
	atqh->x = 250;
	atqh->y = Y_OPT - 250/2;
	srand(time(NULL));
	atqh->dano = randInt(8,12);
	atqh->r = atqh->dano;
	atqh->cor = al_map_rgb(255,255,51);

}

void initMonstroBoss(MonstroBoss *m)

{
	m->x = randInt(750,SCREEN_W - TAM_OBJ + 10);
	m->y = randInt(5,SCREEN_H - 10);
	m->vida = 120;
	m->pontos = 120;
}

void initataqueBoss(ataqueBoss *atqb)

{
	atqb->x = 250;
	atqb->y = Y_OPT - 250/2;
	srand(time(NULL));
	atqb->dano = randInt(12,20);
	atqb->r = atqb->dano;
	atqb->cor = al_map_rgb(255,0,0);
	
}

void initOpcao(Opcao *o)

{
	o->x = X_OPT + 150;
	o->y = Y_OPT + 30;
	o->r = 10;
	o->cor = al_map_rgb(255,255,255);
}

void initMenu(Opcao *o)

{
	o->x = SCREEN_W / 2 + 110;
	o->y = SCREEN_H / 2 + 35;
	o->r = 10;
	o->cor = al_map_rgb(255,255,255);
	o->telamenu = 1;
	o->inst = 0;
}

void initGlobais()

{
	CEU_H = (2 * SCREEN_H) / 3;
	X_OPT = (3 * SCREEN_W) / 4;
	Y_OPT = (3 * SCREEN_H) / 4;
	deslocx = 12;
	
	int TAM_FONTE = 32;
	
	//carrega o arquivo arial.ttf da fonte Arial e define que sera usado o tamanho 32 (segundo parametro)
    FONTE = al_load_font("arial.ttf", TAM_FONTE, 1);   
	if(FONTE == NULL) {
		fprintf(stderr, "font file does not exist or cannot be accessed!\n");
	}
	
	FONTEINFO = al_load_font("arial.ttf", 16, 1); 
}

//============================== NAVEGACAO ==================//


void desenhaHeroiNaveg(Heroi h, ALLEGRO_BITMAP *imagem)

{
	al_draw_bitmap(imagem,h.x, h.y,0);
	
}

void desenhaCenarioNaveg(Heroi h) 

{ 
	char pont[MAXTAM];
	sprintf(pont, "Pontuacao: %d", h.pontuacao);
	char vida[MAXTAM];
	sprintf(vida, "HP: %d", h.vida);
	char esp[MAXTAM];
	sprintf(esp, "Especiais: %d", h.numespecial);
	
	al_clear_to_color(al_map_rgb(32,32,32));
	al_draw_text(FONTEINFO, al_map_rgb(128, 200, 30), 10, 10, 0, pont);
	al_draw_text(FONTEINFO, al_map_rgb(255, 0, 0), 150, 10, 0, vida);
	al_draw_text(FONTEINFO, al_map_rgb(255, 255, 0), 240, 10, 0, esp);
}

void processaTeclaNaveg(Heroi *h, int tecla)

{
	
	h->x_old = h->x;
	h->y_old = h->y;
	
	switch(tecla) {
		
		case ALLEGRO_KEY_UP: 
		if(h->y - PASSO >= 0)h->y -= PASSO;
		break;
		
		case ALLEGRO_KEY_DOWN:
		if(h->y + TAM_HEROI + PASSO <= SCREEN_H)h->y += PASSO;
		break;
		
		case ALLEGRO_KEY_LEFT:
		if(h->x - PASSO >= 0)h->x -= PASSO;
		break;
		
		case ALLEGRO_KEY_RIGHT:
		if(h->x + TAM_HEROI + PASSO <= SCREEN_W)h->x += PASSO;
		break;
		
		case ALLEGRO_KEY_W: 
		if(h->y - PASSO >= 0)h->y -= PASSO;
		break;
		
		case ALLEGRO_KEY_S:
		if(h->y + TAM_HEROI + PASSO <= SCREEN_H)h->y += PASSO;
		break;
		
		case ALLEGRO_KEY_A:
		if(h->x - PASSO >= 0)h->x -= PASSO;
		break;
		
		case ALLEGRO_KEY_D:
		if(h->x + TAM_HEROI + PASSO <= SCREEN_W)h->x += PASSO;
		break;
		
		case ALLEGRO_KEY_E:
		printf("\n\n%d", h->numespecial);
		break;
		
		case ALLEGRO_KEY_R:
		if(h->revelainimigos == 0)
			h->revelainimigos = 1;
		else if(h->revelainimigos = 1)
			h->revelainimigos = 0;
	}
		
}

int chegouObjetivo(Heroi h)

{
	if(h.x > SCREEN_W - TAM_OBJ && h.y + TAM_HEROI <= TAM_OBJ)
		return 1;
	
	return 0;
	
}
	

//============================ BATALHA ==================//

void desenhaCenarioAmiga(Heroi *h, Amiga *a)

{
	al_clear_to_color(al_map_rgb(32,32,32));
	al_draw_filled_rectangle(0,0,SCREEN_W, CEU_H,al_map_rgb(0,0,0));

	char vidaheroi[MAXTAM];
	sprintf(vidaheroi, "HP: %d", h->vida);
	al_draw_text(FONTE, al_map_rgb(255, 0, 0), X_OPT + 10, 100, 0, vidaheroi);
	
	char text[MAXTAM];
	char bonus[MAXTAM];
	sprintf(text, "Voce encontrou uma amiga!");
	sprintf(bonus, "+%d HP", a->bonus);
	al_draw_text(FONTE, al_map_rgb(0, 255, 0), (SCREEN_W / 2) - 250, 100, 0, text);
	al_draw_text(FONTE, al_map_rgb(255, 0, 0), (SCREEN_W / 2) - 150, 150, 0, bonus);

} 

void desenhaCenarioBatalha(Heroi h)

{	
	char vidaheroi[MAXTAM];
	sprintf(vidaheroi, "HP: %d", h.vida);
	
	al_clear_to_color(al_map_rgb(32,32,32));
	al_draw_filled_rectangle(0,0,SCREEN_W, CEU_H,al_map_rgb(0,0,0));
	al_draw_filled_rectangle(X_OPT, Y_OPT, SCREEN_W, SCREEN_H, al_map_rgb(20,16,77));
	al_draw_text(FONTE, al_map_rgb(255, 255, 255), X_OPT + 8, Y_OPT + 8, 0, "Ataque");
	al_draw_text(FONTE, al_map_rgb(255, 255, 255), X_OPT + 8, Y_OPT + 90, 0, "Fuga");
	al_draw_text(FONTE, al_map_rgb(255, 0, 0), X_OPT + 10, 100, 0, vidaheroi);
	
	if(h.numespecial > 0)
		al_draw_text(FONTE, al_map_rgb(255, 255, 255), X_OPT + 8, Y_OPT + 48, 0, "Especial");
	
	else if(h.numespecial == 0)
		al_draw_text(FONTE, al_map_rgb(160, 160, 160), X_OPT + 8, Y_OPT + 48, 0, "Especial");
}

int chancesFuga(Heroi *h)

{
	int chances;
	
	if(h->vida > 60)
		chances = randInt(1,99);
	
	else if(h->vida <= 60 && h->vida > 30)
		chances = randInt(1,66);
	
	else if(h->vida <= 30)
		chances = randInt(1,33);
	
	return chances;
	
}


int processaTeclaBatalha(Heroi *h, int tecla, Opcao *o)

{
    if(h->travatecla == 0) {

	switch(tecla) {
		
		case ALLEGRO_KEY_UP: 
		if(o->y > 460)
           o->y -= 40;			
		break;
		
		case ALLEGRO_KEY_DOWN:
		if(o->y < SCREEN_H - 40)
           o->y += 40;	
		break;
		
		case ALLEGRO_KEY_W: 
		if(o->y > 460)
           o->y -= 40;			
		break;
		
		case ALLEGRO_KEY_S:
		if(o->y < SCREEN_H - 40)
           o->y += 40;	
		break;
		
		case ALLEGRO_KEY_I:
		if(h->ativacheat == 0)
			h->ativacheat = 1;
		else if(h->ativacheat == 1)
			h->ativacheat = 0;
		break;
			
		
		case ALLEGRO_KEY_ENTER:
		h->travatecla = 1;
		h->executar = 1;
		if(o->y == Y_OPT + 110)
			h->acao = FUGIR;
		else if(o->y == Y_OPT + 30)
			h->acao = ATACAR;
		else if(o->y == Y_OPT + 70)
			h->acao = ESPECIAL;
		break;
	}
	
	}
	
}
	
int processaAcaoHeroi(Heroi *h)

    {
		
		int chances = chancesFuga(h);
		
		if(h->executar)
		{
			h->executar = 0;
			
			if(h->acao == FUGIR)
			{
				if(chances > 20) {
				h->travatecla = 0;
				h->x = h->x_old;
				h->y = h->y_old;
				return NAVEGACAO;
				}
				
				else {
					h->travatecla = 1;
					printf("\nFuga falhou!");
				}
			}
			
			else if(h->acao == ATACAR)
			{
				h->atacando = 1;
				printf("Ataque");
			}
			
			else if(h->acao == ESPECIAL)
			{
				if(h->numespecial > 0)
				{
					h->numespecial--;
					h->atacando = 1;
				}
				
				else
				printf("Especial");
			    h->travatecla = 0;
			}
		}
		
		return BATALHA;

	}

void desenhaOpcao(Opcao o)

{
	al_draw_filled_circle(o.x, o.y, o.r, o.cor);
}

float dist(int x1, int y1, int x2, int y2)

{
	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

int detectouMonstroEasy(Heroi h, MonstroEasy ME)

{
	if(dist(h.x, h.y, ME.x,ME.y) <= MAX_DIST)
		return 1;
	return 0;
}

int detectouMonstroMedio(Heroi h, MonstroMedio MM)

{
	if(dist(h.x, h.y, MM.x,MM.y) <= MAX_DIST)
		return 1;
	return 0;
}

int detectouMonstroHard(Heroi h, MonstroHard MH)

{
	if(dist(h.x, h.y, MH.x,MH.y) <= MAX_DIST)
		return 1;
	return 0;
}

int detectouMonstroBoss(Heroi h, MonstroBoss MB)

{
	if(dist(h.x, h.y, MB.x,MB.y) <= MAX_DIST)
		return 1;
	return 0;
}

int detectouAmiga(Heroi h, Amiga a)

{
	if(dist(h.x, h.y, a.x,a.y) <= MAX_DIST)
		return 1;
	return 0;
}

//============================== MENU E FIM DE JOGO =======================//
int processaTeclaMenu(int tecla, Opcao *o)

{
	switch(tecla) {
		
		case ALLEGRO_KEY_UP: 
        o->y = SCREEN_H / 2 + 35;		
		break;
		
		case ALLEGRO_KEY_DOWN:
		o->y = SCREEN_H / 2 + 120;
		break;
		
		case ALLEGRO_KEY_W: 
		o->y = SCREEN_H / 2 + 35;		
		break;
		
		case ALLEGRO_KEY_S:
		o->y = SCREEN_H / 2 + 120;
		break;
		
		case ALLEGRO_KEY_ENTER:
		if(o->y == SCREEN_H / 2 + 35) {
			o->telamenu = 0;
			o->inst = 0;
		}
		else if(o->y == SCREEN_H / 2 + 120) {
			o->inst = 1;
			o->telamenu = 0;
		}
		break;
	}
	
	
}

int processaTeclaInst(int tecla, Opcao *o)

{
	switch(tecla) {
		case ALLEGRO_KEY_ENTER:
		o->telamenu = 1;
		o->inst = 0;
		break;
	}
}


void desenhaCenarioFinal()

{
	al_clear_to_color(al_map_rgb(32,32,32));	
}

int heroiMorreu(Heroi h)
{
	if(h.vida <= 0)
		return 1;
	
	return 0;
	
}

void desenhaCenarioDerrota()

{
	al_clear_to_color(al_map_rgb(0,0,0));	
	char derrota[MAXTAM];
    sprintf(derrota, "Voce perdeu...");
	al_draw_text(FONTE, al_map_rgb(255, 0, 0), SCREEN_W / 2 - 150, SCREEN_H / 2 - 100, 0, derrota);
}
	
int main(int argc, char **argv){
	
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
   
	//----------------------- rotinas de inicializacao ---------------------------------------
    
	//inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	
    //inicializa o módulo de primitivas do Allegro
    if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }	
	
	//inicializa o modulo que permite carregar imagens no jogo
	if(!al_init_image_addon()){
		fprintf(stderr, "failed to initialize image module!\n");
		return -1;
	}
   
	//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}
 
	//cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	//inicializa o modulo allegro que carrega as fontes
	al_init_font_addon();

	//inicializa o modulo allegro que entende arquivos tff de fontes
	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}
	
 	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}
   
	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	 	
	//inicia o temporizador
	al_start_timer(timer);
	
	//imagens +- por aqui	
	ALLEGRO_BITMAP *imgmenu = NULL;
	imgmenu = al_load_bitmap("menu.png");
	
	ALLEGRO_BITMAP *imginst = NULL;
	imginst = al_load_bitmap("inst.png");
	
	ALLEGRO_BITMAP *objetivo = NULL;
	objetivo = al_load_bitmap("objetivo.png");

	ALLEGRO_BITMAP *posicao = NULL;
	posicao = al_load_bitmap("pactras.png");
	
	ALLEGRO_BITMAP *pacbatalha = NULL;
	pacbatalha = al_load_bitmap("pacbatalha.png");
	
	ALLEGRO_BITMAP *imgamiga = NULL;
	imgamiga = al_load_bitmap("amiga.png");
	
	ALLEGRO_BITMAP *imgeasy = NULL;
	imgeasy = al_load_bitmap("inimigoeasy.png");

	ALLEGRO_BITMAP *imgmedio = NULL;
	imgmedio = al_load_bitmap("inimigomedio.png");
	
	ALLEGRO_BITMAP *imghard = NULL;
	imghard = al_load_bitmap("inimigohard.png");
	
	ALLEGRO_BITMAP *imgboss = NULL;
	imgboss = al_load_bitmap("inimigoboss.png");
	
	int playing = 1;
	int modo_jogo = MENU;
	
	
	initGlobais();
	 
	Heroi heroi;
	ataqueHeroi atqhero;
	ataqueEspecial atqesp;
	ataqueCheat atqcheat;
	initataqueHeroi(&atqhero);
	initataqueEspecial(&atqesp);
	initataqueCheat(&atqcheat);
	
	Amiga amiga[MAXAMIGAS];
	
	MonstroEasy ME[MAXEASY];
	ataqueEasy atqe;
	initataqueEasy(&atqe);
	
	MonstroMedio MM[MAXMEDIO];
	ataqueMedio atqm;
	initataqueMedio(&atqm);
	
	MonstroHard MH[MAXHARD];
	ataqueHard atqh;
	initataqueHard(&atqh);
	
	MonstroBoss MB[MAXBOSS];
	ataqueBoss atqb;
	initataqueBoss(&atqb);
	
	Opcao o;
	initHeroi(&heroi);
	initOpcao(&o);
	
	Opcao menu;
	initMenu(&menu);
	
	int qualinimigo = 0;
	
	int easy = 0, medio = 0, hard = 0, boss = 0, amg = 0;
	
	int i = 0;
	
	for(i = 0; i < MAXAMIGAS; i++)
		initAmiga(&amiga[i]);
	
	for(i = 0; i < MAXEASY; i++) 
		initMonstroEasy(&ME[i]);
	
	for(i = 0; i < MAXMEDIO; i++)
		initMonstroMedio(&MM[i]);
	
	for(i = 0; i < MAXHARD; i++)
		initMonstroHard(&MH[i]);
	
	for(i = 0; i < MAXBOSS; i++)
		initMonstroBoss(&MB[i]);
	
	while(playing) {
		ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);

		//se o tipo de evento for um evento do temporizador, ou seja, se o tempo passou de t para t+1
		if(ev.type == ALLEGRO_EVENT_TIMER) {
			
			if(modo_jogo == MENU)
				
				{					
	                al_draw_bitmap(imgmenu, 0, 0,0);
					al_draw_filled_circle(menu.x,menu.y,menu.r,menu.cor);
					
					if(menu.telamenu == 0 && menu.inst == 0)
						modo_jogo = NAVEGACAO;
					
					else if(menu.inst == 1)
						modo_jogo = INSTRUCOES;
		
				}
				
			else if(modo_jogo == INSTRUCOES)
			    {
	                al_draw_bitmap(imginst, 0, 0,0);
					al_draw_filled_circle(670,495,menu.r, menu.cor);
				  
				    if(menu.telamenu == 1)
						modo_jogo = MENU;
				
			    }

			else if(modo_jogo == NAVEGACAO)
				
				{
					int j = 0;
					
					desenhaCenarioNaveg(heroi);
					al_draw_bitmap(objetivo, SCREEN_W - TAM_OBJ, 0,0);
					
					if(heroi.revelainimigos == 1) {
					for(j = 0; j < MAXAMIGAS; j++)
					al_draw_filled_circle(amiga[j].x, amiga[j].y, 5, al_map_rgb(255,153,255));
									
					for(j = 0; j < MAXEASY; j++)
					al_draw_filled_circle(ME[j].x, ME[j].y, 5, al_map_rgb(0,0,255));
				
				    for(j = 0; j < MAXMEDIO; j++)
					al_draw_filled_circle(MM[j].x, MM[j].y, 5, al_map_rgb(0,255,0));
				
				    for(j = 0; j < MAXHARD; j++)
					al_draw_filled_circle(MH[j].x, MH[j].y, 5, al_map_rgb(255,255,0));
				
				    for(j = 0; j < MAXBOSS; j++)
					al_draw_filled_circle(MB[j].x, MB[j].y, 5, al_map_rgb(255,0,0));
					}
				
					if(heroi.y > heroi.y_old)
						posicao = al_load_bitmap("pacfrente.png");
					
					else if(heroi.y < heroi.y_old)
						posicao = al_load_bitmap("pactras.png");
					
					else if(heroi.x < heroi.x_old)
						posicao = al_load_bitmap("pacesq.png");
						
					else if(heroi.x > heroi.x_old)
						posicao = al_load_bitmap("pacdir.png");
					
					desenhaHeroiNaveg(heroi, posicao);
					
					int a = 0, b = 0, c = 0, d = 0, e = 0;
					
					for(a = 0; a < MAXEASY; a++) {
					if(detectouMonstroEasy(heroi, ME[a])) {					
						easy = a;
						qualinimigo = EASY;
                        modo_jogo = BATALHA;						
					}
					}
					
					for(b = 0; b < MAXMEDIO; b++) {
					if(detectouMonstroMedio(heroi, MM[b])) {
						medio = b;
						qualinimigo = MEDIO;	
                        modo_jogo = BATALHA;						
					}
					}
					
					for(c = 0; c < MAXHARD; c++) {
					if(detectouMonstroHard(heroi, MH[c])) {
						hard = c;
						qualinimigo = HARD;
						modo_jogo = BATALHA;
					}
					}
					
					for(d = 0; d < MAXBOSS; d++) {
					if(detectouMonstroBoss(heroi, MB[d])) {
						boss = d;
						qualinimigo = BOSS;
						modo_jogo = BATALHA;
					}
					}
					
					for(e = 0; e < MAXAMIGAS; e++) {
					if(detectouAmiga(heroi, amiga[e])) {
						amg = e;
						qualinimigo = AMIGA;
						modo_jogo = BATALHA;
					}
					}
					
					if(chegouObjetivo(heroi)) {
						
						int sim = 0;
						int recorde;
						FILE *verificarecorde;
						verificarecorde = fopen("recordepontuacao.txt", "r");
						fscanf(verificarecorde, "%d", &recorde);
						fclose(verificarecorde);
						
						if(heroi.pontuacao > recorde) {
							
						    FILE *newrecord;
							newrecord = fopen("recordepontuacao.txt", "w");
							fprintf(newrecord, "%d", heroi.pontuacao);
							fclose(newrecord);
							sim = 1;
						}
						
						desenhaCenarioFinal();
						
	                    char parabens[MAXTAM];
	                    char pontfinal[MAXTAM];
						char novorecorde[MAXTAM];
						
	                    sprintf(parabens, "Voce venceu!");
	                    sprintf(pontfinal, "Pontuacao Final: %d", heroi.pontuacao);
						sprintf(novorecorde, "Novo recorde de pontuacao!");
						
	                    al_draw_text(FONTE, al_map_rgb(0, 255, 0), SCREEN_W / 2 - 150, SCREEN_H / 2 - 100, 0, parabens);
	                    al_draw_text(FONTE, al_map_rgb(0, 0, 255), SCREEN_W / 2 - 150, SCREEN_H / 2, 0, pontfinal);
						if(sim == 1)
							al_draw_text(FONTE, al_map_rgb(255, 0, 0), SCREEN_W / 2 - 150, SCREEN_H / 2 + 100, 0, novorecorde);
						playing = 0;
					}
				}
				
				else
				{
			
					if(qualinimigo != AMIGA)
					{
						desenhaCenarioBatalha(heroi);
					    desenhaOpcao(o);
					    modo_jogo = processaAcaoHeroi(&heroi);	
					}
					
					al_draw_bitmap(pacbatalha, X_OPT - 20, Y_OPT - 250,0);
					
					if(qualinimigo == AMIGA) {
						
					desenhaCenarioAmiga(&heroi, &amiga[amg]);
					al_draw_bitmap(pacbatalha, X_OPT - 20, Y_OPT - 250,0);
					al_draw_bitmap(imgamiga, 50, Y_OPT - 270,0);
                    al_flip_display();
					al_rest(3);
					heroi.vida += amiga[amg].bonus;
					heroi.numespecial++;
					amiga[amg].x = -250;
					modo_jogo = NAVEGACAO;
					}
								
					else if(qualinimigo == EASY) {	
	
					char vidainimigo[MAXTAM];
	                sprintf(vidainimigo, "HP: %d", ME[easy].vida);
                    al_draw_text(FONTE, al_map_rgb(255, 0, 0), 100, 100, 0, vidainimigo);
					al_draw_bitmap(imgeasy, 50, Y_OPT - 250,0);
			
					    if(heroi.acao == ATACAR && heroi.atacando == 1 && heroi.ativacheat == 0)
						{
							if(atqhero.x > 200) {
								al_draw_filled_circle(atqhero.x,atqhero.y,atqhero.r, atqhero.cor);
							    atqhero.x -= deslocx;		
							}
							
							else if(atqhero.x - deslocx <= 200)
							{
								
								ME[easy].vida -= atqhero.dano;
								initataqueHeroi(&atqhero);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}				
						}
						
						else if(heroi.acao == ESPECIAL && heroi.atacando == 1 && heroi.ativacheat == 0)
						{
							if(atqesp.x > 200) {
								al_draw_filled_circle(atqesp.x,atqesp.y,atqesp.r, atqesp.cor);
							    atqesp.x -= deslocx;		
							}
							
							else if(atqesp.x - deslocx <= 200)
							{
								
								ME[easy].vida -= atqesp.dano;
								initataqueEspecial(&atqesp);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}
						}
						
						else if(heroi.atacando == 1 && heroi.ativacheat == 1)
						{
							if(atqcheat.x > 200) {
								al_draw_filled_circle(atqcheat.x,atqcheat.y,atqcheat.r, atqcheat.cor);
							    atqcheat.x -= deslocx;
							}
							else if(atqcheat.x - deslocx <= 200)
							{
								
								ME[easy].vida -= atqcheat.dano;
								initataqueCheat(&atqcheat);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}
							
						}
					                
						else if(heroi.travatecla == 1 && ME[easy].vida > 0) {
	                        
	                        if(atqe.x < 800) {
								
							al_draw_filled_circle(atqe.x,atqe.y,atqe.r, atqe.cor);
							atqe.x += deslocx;
							}
							
							else if(atqe.x + deslocx >= 800)
							{
								heroi.vida -= atqe.dano;
								initataqueEasy(&atqe);
								heroi.travatecla = 0;		
							}
						
							
						}
						
						else if(ME[easy].vida <= 0)
					{
						qualinimigo = 0;
						modo_jogo = NAVEGACAO;
						ME[easy].x = -200;
						heroi.travatecla = 0;
						heroi.pontuacao += ME[easy].pontos;
					}
						
					}
					
					
					
					else if(qualinimigo == MEDIO) {

					char vidainimigo[MAXTAM];
	                sprintf(vidainimigo, "HP: %d", MM[medio].vida);
                    al_draw_text(FONTE, al_map_rgb(255, 0, 0), 100, 100, 0, vidainimigo);
					al_draw_bitmap(imgmedio, 50, Y_OPT - 250,0);
						
					 if(heroi.acao == ATACAR && heroi.atacando == 1 && heroi.ativacheat == 0)
						{
							if(atqhero.x > 200) {
								al_draw_filled_circle(atqhero.x,atqhero.y,atqhero.r, atqhero.cor);
							    atqhero.x -= deslocx;		
							}
							
							else if(atqhero.x - deslocx <= 200)
							{
								
								MM[medio].vida -= atqhero.dano;
								initataqueHeroi(&atqhero);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}
				
						}
						
						else if(heroi.acao == ESPECIAL && heroi.atacando == 1 && heroi.ativacheat == 0)
						{
							if(atqesp.x > 200) {
								al_draw_filled_circle(atqesp.x,atqesp.y,atqesp.r, atqesp.cor);
							    atqesp.x -= deslocx;		
							}
							
							else if(atqesp.x - deslocx <= 200)
							{
								
								MM[medio].vida -= atqesp.dano;
								initataqueEspecial(&atqesp);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}
						}
						
						else if(heroi.atacando == 1 && heroi.ativacheat == 1)
						{
							if(atqcheat.x > 200) {
								al_draw_filled_circle(atqcheat.x,atqcheat.y,atqcheat.r, atqcheat.cor);
							    atqcheat.x -= deslocx;
							}
							else if(atqcheat.x - deslocx <= 200)
							{
								
								MM[medio].vida -= atqcheat.dano;
								initataqueCheat(&atqcheat);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}
							
						}
					                
						else if(heroi.travatecla == 1 && MM[medio].vida > 0) {
	                        
	                        if(atqm.x < 800) {							
							al_draw_filled_circle(atqm.x,atqm.y,atqm.r, atqm.cor);
							atqm.x += deslocx;
							}
							
							else if(atqm.x + deslocx >= 800)
							{
								heroi.vida -= atqm.dano;
								initataqueMedio(&atqm);
								heroi.travatecla = 0;	
							}
						
							
						}	
						
						else if(MM[medio].vida <= 0)
					{
						modo_jogo = NAVEGACAO;
						MM[medio].x = -200;
						heroi.travatecla = 0;
						heroi.pontuacao += MM[medio].pontos;
					}
									
					}
			
					else if(qualinimigo == HARD) {
						
					char vidainimigo[MAXTAM];
	                sprintf(vidainimigo, "HP: %d", MH[hard].vida);
                    al_draw_text(FONTE, al_map_rgb(255, 0, 0), 100, 100, 0, vidainimigo);
					al_draw_bitmap(imghard, 50, Y_OPT - 250,0);
					
					if(heroi.acao == ATACAR && heroi.atacando == 1 && heroi.ativacheat == 0)
						{
							if(atqhero.x > 200) {
								al_draw_filled_circle(atqhero.x,atqhero.y,atqhero.r, atqhero.cor);
							    atqhero.x -= deslocx;		
							}
							
							else if(atqhero.x - deslocx <= 200)
							{			
								MH[hard].vida -= atqhero.dano;
								initataqueHeroi(&atqhero);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}				
						}
						
						else if(heroi.acao == ESPECIAL && heroi.atacando == 1 && heroi.ativacheat == 0)
						{
							if(atqesp.x > 200) {
								al_draw_filled_circle(atqesp.x,atqesp.y,atqesp.r, atqesp.cor);
							    atqesp.x -= deslocx;		
							}
							
							else if(atqesp.x - deslocx <= 200)
							{		
								MH[hard].vida -= atqesp.dano;
								initataqueEspecial(&atqesp);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}
						}
						
						else if(heroi.atacando == 1 && heroi.ativacheat == 1)
						{
							if(atqcheat.x > 200) {
								al_draw_filled_circle(atqcheat.x,atqcheat.y,atqcheat.r, atqcheat.cor);
							    atqcheat.x -= deslocx;
							}
							else if(atqcheat.x - deslocx <= 200)
							{
								
								MH[hard].vida -= atqcheat.dano;
								initataqueCheat(&atqcheat);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}
							
						}
					                
						else if(heroi.travatecla == 1 && MH[hard].vida > 0) {
	                        
	                        if(atqh.x < 800) {
								
							al_draw_filled_circle(atqh.x,atqh.y,atqh.r, atqh.cor);
							atqh.x += deslocx;
							}
							
							else if(atqh.x + deslocx >= 800)
							{
								heroi.vida -= atqh.dano;
								initataqueHard(&atqh);
								heroi.travatecla = 0;		
							}
						
							
						}
						
					else if(MH[hard].vida <= 0)
					{
						modo_jogo = NAVEGACAO;
						MH[hard].x = -200;
						heroi.travatecla = 0;
						heroi.pontuacao += MH[hard].pontos;							
					}	
					}					
					
					else if(qualinimigo == BOSS) {

					char vidainimigo[MAXTAM];
	                sprintf(vidainimigo, "HP: %d", MB[boss].vida);
                    al_draw_text(FONTE, al_map_rgb(255, 0, 0), 100, 100, 0, vidainimigo);
					al_draw_bitmap(imgboss, 50, Y_OPT - 250,0);
					
					if(heroi.acao == ATACAR && heroi.atacando == 1 && heroi.ativacheat == 0)
						{
							if(atqhero.x > 200) {
								al_draw_filled_circle(atqhero.x,atqhero.y,atqhero.r, atqhero.cor);
							    atqhero.x -= deslocx;		
							}
							
							else if(atqhero.x - deslocx <= 200)
							{
								
								MB[boss].vida -= atqhero.dano;
								initataqueHeroi(&atqhero);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}						
						}
						
						else if(heroi.acao == ESPECIAL && heroi.atacando == 1 && heroi.ativacheat == 0)
						{
							if(atqesp.x > 200) {
								al_draw_filled_circle(atqesp.x,atqesp.y,atqesp.r, atqesp.cor);
							    atqesp.x -= deslocx;		
							}
							
							else if(atqesp.x - deslocx <= 200)
							{		
								MB[boss].vida -= atqesp.dano;
								initataqueEspecial(&atqesp);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}
						}
						
						else if(heroi.atacando == 1 && heroi.ativacheat == 1)
						{
							if(atqcheat.x > 200) {
								al_draw_filled_circle(atqcheat.x,atqcheat.y,atqcheat.r, atqcheat.cor);
							    atqcheat.x -= deslocx;
							}
							else if(atqcheat.x - deslocx <= 200)
							{
								
								MB[boss].vida -= atqcheat.dano;
								initataqueCheat(&atqcheat);
								heroi.atacando = 0;
								heroi.travatecla = 1;
							}
							
						}
					                
						else if(heroi.travatecla == 1 && MB[boss].vida > 0) {
	                        
	                        if(atqb.x < 800) {
								
							al_draw_filled_circle(atqb.x,atqb.y,atqb.r, atqb.cor);
							atqb.x += deslocx;
							}
							
							else if(atqb.x + deslocx >= 800)
							{
								heroi.vida -= atqb.dano;
								initataqueBoss(&atqb);
								heroi.travatecla = 0;		
							}
						
							
						}
						
					    else if(MB[boss].vida <= 0) {
					
						modo_jogo = NAVEGACAO;
						MB[boss].x = -200;
						heroi.travatecla = 0;
						heroi.pontuacao += MB[boss].pontos;					
					}	
						
					}
						 		
					if(heroiMorreu(heroi)) {		 
				     desenhaCenarioDerrota();
				     playing = 0;
					 }
					 
				}

			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
			
			
			
		}
		//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
		
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			
			if(modo_jogo == MENU)
				processaTeclaMenu(ev.keyboard.keycode, &menu);
					
				
				
			else if(modo_jogo == INSTRUCOES)
				processaTeclaInst(ev.keyboard.keycode, &menu);
			
			else if(modo_jogo == NAVEGACAO)
				processaTeclaNaveg(&heroi, ev.keyboard.keycode); 				
				
			else			
				processaTeclaBatalha(&heroi, ev.keyboard.keycode, &o);
				

			//imprime qual tecla foi
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		}
		

	} //fim do while
     
	//procedimentos de fim de jogo (fecha a tela, limpa a memoria, etc)
	
    al_rest(3);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
   
 
	return 0;
}