#include<iostream>
#define USETEXT
#define USETEXTURES
#include<libguionsdl3.hpp>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

TTF_Font *Font;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
	Font = TTF_OpenFont("../resources/Schiffbauer-Regular.otf", 20);
    if(!Font) return 1;
	window = SDL_CreateWindow("test", 500, 500, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
   	if(!window || !renderer){
		std::cout << SDL_GetError();
		return 1;
	}	
	SDL_ShowWindow(window);
	SDL_StartTextInput(window);    
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	GOS_GUI gui;
    GOS_StyledBox *box = new GOS_StyledBox();
    box->Face = {0, 0, 100, 600};
    box->Color = GOS_Color(255, 125, 255, 255);
    
    GOS_StyledButton *button = new GOS_StyledButton();
    button->Face = {0, 50, 50, 50};
    button->Color = GOS_Color(100, 255, 255, 150);
    GOS_TextBox *text = new GOS_TextBox();
    text->Face = {0, 150, 100, 50};
    text->Color = GOS_Color(220, 220, 220, 255);
	text->Text = "Hello";
	
	SDL_Surface* surf = IMG_Load("../resources/test2.png");
	GOS_TexturedBox *texture = new GOS_TexturedBox();
	texture->Face = {0, 250, 100, 50};
	texture->Color.SetAllTo(50);
	texture->Color.r = 255;
	texture->Color.a = 255;
	texture->BorderSize = 0;
	texture->Texture = SDL_CreateTextureFromSurface(renderer, surf);
	texture->RenderType = GOS_RenderType::Left;
	SDL_DestroySurface(surf);
	GOS_TexturedButton *tb = new GOS_TexturedButton();
	tb->Face = {0, 350, 100, 50};
	tb->Color.SetAllTo(255);
	tb->Color.r = 0;
	tb->BorderSize = 5;
	tb->Texture = texture->Texture;
	tb->RenderType = GOS_RenderType::Centered;

	GOS_TextInputBox *ti = new GOS_TextInputBox();
	ti->Face = {0, 450, 100, 50};
	ti->Color.SetAllTo(46);
	ti->Color.b = 255;
	ti->Text = "";
	GOS_OpenMenu *om = new GOS_OpenMenu();
	om->Face = {150, 50, 100, 50};
	om->OpenedFace = {150, 50, 100, 150};
	om->Color.SetAllTo(150);
	GOS_RadioButton *rb1 = new GOS_RadioButton();
	GOS_RadioButton *rb2 = new GOS_RadioButton();
	GOS_RadioButton *rb3 = new GOS_RadioButton();
	rb1->Face = {175, 175, 10, 10};
	rb2->Face = {195, 175, 10, 10};
	rb3->Face = {215, 175, 10, 10};
	rb1->Color.SetRandom();
	rb2->Color.SetRandom();
	rb3->Color.SetRandom();
	rb1->ActiveColor.SetRandom();
	rb2->ActiveColor.SetRandom();
	rb3->ActiveColor.SetRandom();

	GOS_Box *om_bx= new GOS_Box();
	om_bx->Face = {150, 100, 100, 50};
	om_bx->Color.SetAllTo(45);
	om_bx->Visible = false;
	om->AddElement(om_bx);
	om->AddElement(rb1);
	om->AddElement(rb2);
	om->AddElement(rb3);

	GOS_ScrollingMenu *sm = new GOS_ScrollingMenu();
	sm->Face = {250, 50, 125, 75};
	sm->Color.SetAllTo(75);
	GOS_Box *sm_bx = new GOS_Box();
	sm_bx->Face = {250, 50, 100, 50};
	sm_bx->Color.SetAllTo(35);
	sm_bx->Color.g = 255;
	sm->AddElement(sm_bx);
	GOS_Box *sm_bx1 = new GOS_Box();
	sm_bx1->Face = {250, 100, 100, 50};
	sm_bx1->Color.SetAllTo(50);
	sm_bx1->Color.b = 255;
	sm->AddElement(sm_bx1);
	GOS_Box *sm_bx2 = new GOS_Box();
	sm_bx2->Face = {250, 150, 100, 50};
	sm_bx2->Color.SetAllTo(100);
	sm_bx2->Color.r = 255;
	sm->AddElement(sm_bx2);
	
	gui.AddElement(box);
    gui.AddElement(button);
    gui.AddElement(text);
    gui.AddElement(texture);
	gui.AddElement(tb);
	gui.AddElement(ti);
	gui.AddElement(om);
	gui.AddElement(sm);
	bool run = true;
    while(run) 
    {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	
        SDL_RenderClear(renderer);
		while(SDL_PollEvent(&event)){
	    	if(event.button.button == SDL_BUTTON_RIGHT){
	       		run = false; 
   	    	}
			if(event.button.button == SDL_BUTTON_LEFT) {
				gui.EraseElementById(3);
			}
			float mx, my;
    		SDL_GetMouseState(&mx, &my);
			gui.Update(mx, my, event);
		}
		SDL_PumpEvents();
		gui.Draw(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
    } 
    SDL_Quit();
    return 0;
}
