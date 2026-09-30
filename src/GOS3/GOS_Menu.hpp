#ifndef GOS_MENU
#define GOS_MENU

#define SCROLL_STEP 5

struct GOS_Menu : public GOS_Element
{
	bool Active = false;
	std::vector<std::unique_ptr<GOS_Element>> Childs;
	virtual void Draw(SDL_Renderer* _r) override
	{
		if(!Visible) return;
		SDL_SetRenderDrawColor(_r, Color.r, Color.g, Color.b, Color.a);
		SDL_RenderFillRect(_r, &Face);
	
		for(auto& child : this->Childs){
			child->Draw(_r);
		}
	}

	virtual void Update(int x, int y, SDL_Event ev) override
	{
		for(auto& child : this->Childs){
			if(child){
				child->Update(x, y, ev);
			}
		}
		this->Active = (x >= Face.x && y >= Face.y && x <= Face.x+Face.w && y < Face.y+Face.h);
	}

	virtual void AddElement(GOS_Element* element)
	{
		if(!element) return;
		this->Childs.push_back(std::unique_ptr<GOS_Element>(element));
	}

	virtual int GetActiveId()
	{
		for(auto& child : this->Childs){
			if(child->Active){
				return child->Id;
			}
		}
		return -1;
	}
};

struct GOS_ScrollingMenu : public GOS_Menu
{
	GOS_ScrollingMenu()
	{
		this->Name = "ScrollingMenu";
	};
	virtual void Update(int x, int y, SDL_Event ev) override
	{
		for(auto& child : this->Childs){
			if(child){
				child->Update(x, y, ev);
			}
		}
		this->Active = (x >= Face.x && y >= Face.y && x <= Face.x+Face.w && y < Face.y+Face.h);
		if(ev.type == SDL_MOUSEWHEEL && this->Active){
			if(ev.wheel.y < 0 && !Childs.empty() && Childs.back()->Face.y+Childs.back()->Face.h <= Face.y+Face.h) return;
			if(ev.wheel.y > 0 && !Childs.empty() && Childs.front()->Face.y >= Face.y) return;
			for(auto& child : this->Childs){
				if(!child) return;
				child->Face.y += ev.wheel.y * SCROLL_STEP;
			}
		}
	}
	virtual void Draw(SDL_Renderer* _r) override
	{
		if(!Visible) return;
		SDL_SetRenderDrawColor(_r, Color.r, Color.g, Color.b, Color.a);
		SDL_RenderFillRect(_r, &Face);
	
		for(auto& child : this->Childs){
			if(child->Face.y < this->Face.y && child->Face.y+child->Face.h > this->Face.y){
				SDL_Rect drawable = {child->Face.x, 
					this->Face.y,
					child->Face.w,
					(child->Face.y+child->Face.h) - this->Face.y};
				SDL_SetRenderDrawColor(_r, child->Color.r, child->Color.g, child->Color.b, child->Color.a);
				SDL_RenderFillRect(_r, &drawable);
			} else if(child->Face.y+child->Face.h > this->Face.y+this->Face.h && child->Face.y < this->Face.y+this->Face.h){
				SDL_Rect drawable = {child->Face.x, 
					child->Face.y,
					child->Face.w,
					(this->Face.h) - (child->Face.y - this->Face.y)};
				SDL_SetRenderDrawColor(_r, child->Color.r, child->Color.g, child->Color.b, child->Color.a);
				SDL_RenderFillRect(_r, &drawable);
			} else if(child->Face.y >= this->Face.y && child->Face.y+child->Face.h <= this->Face.y+this->Face.h) {
				child->Draw(_r);
			} else {
				continue;
			}
		}
		//Scrollbar
		if(Childs.empty()) return;
		int content_top = Childs.front()->Face.y;
    	int content_bottom = Childs.back()->Face.y + Childs.back()->Face.h;
   		int content_height = content_bottom - content_top;
    
    	SDL_Rect scrl_bar_bg = {
        	this->Face.x + (this->Face.w - 5),
        	this->Face.y,
        	5,
        	this->Face.h
    	};
    	SDL_SetRenderDrawColor(_r, this->Color.r+30, this->Color.g+30, this->Color.b+30, this->Color.a);
    	SDL_RenderFillRect(_r, &scrl_bar_bg);
    
    	if (content_height > Face.h) {
        	int scrolled = Face.y - content_top;
        	float progress = (float)scrolled / (content_height - Face.h);
        	int thumb_h = (int)((float)Face.h / content_height * Face.h);
        	if (thumb_h < 20) thumb_h = 20;
        	if (thumb_h > Face.h) thumb_h = Face.h;
        	int thumb_y = Face.y + (int)(progress * (Face.h - thumb_h));
        	SDL_Rect scrl_bar = {
            	this->Face.x + (this->Face.w - 5),
            	thumb_y,
            	5,
            	thumb_h
        	};
        	SDL_SetRenderDrawColor(_r, this->Color.r-30, this->Color.g-30, this->Color.b-30, this->Color.a);
        	SDL_RenderFillRect(_r, &scrl_bar);		
		}
	}
};

struct GOS_OpenMenu : public GOS_Menu
{
	SDL_Rect OpenedFace = this->Face;
	bool IsOpened = false;
	GOS_OpenMenu()
	{
		this->Name = "OpenMenu";
	};
	virtual void Update(int x, int y, SDL_Event ev) override
	{
		for(auto& child : this->Childs){
			if(child){
				child->Update(x, y, ev);
			}
		}
		this->Active = (x >= Face.x && y >= Face.y && x <= Face.x+Face.w && y <= Face.y+Face.h);
		if(ev.type == SDL_MOUSEBUTTONUP && this->Active && ev.button.button == SDL_BUTTON_LEFT){
			this->IsOpened = !this->IsOpened;
		}	
	}
	virtual int GetActiveId()
	{
		for(auto& child : this->Childs){
			if(child->Active){
				return child->Id;
			}
		}
		if(this->Active){
			return this->Id;
		}
		return -1;
	}
	virtual void Open()
	{
		this->IsOpened = true;
	}
	
	virtual void Close()
	{
		this->IsOpened = false;
	}
	virtual void Draw(SDL_Renderer* _r) override
	{
		if(!Visible) return;
		SDL_SetRenderDrawColor(_r, Color.r, Color.g, Color.b, Color.a);
		SDL_RenderFillRect(_r, &Face);
		if(IsOpened){
			SDL_RenderFillRect(_r, &OpenedFace);
			for(auto& child : this->Childs){
				if(child){
					child->Draw(_r);
				}
			}
		}
	}
};

#endif
