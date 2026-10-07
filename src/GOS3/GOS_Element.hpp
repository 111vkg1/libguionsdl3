#ifndef GOS_ELEMENT
#define GOS_ELEMENT

struct GOS_Element
{
    bool Visible = true;
    std::string Name = "Element";
    std::string Text = "None";
    int Id = 0;
    bool Active = false;
    GOS_Color Color = {255, 255, 255, 255};
    SDL_FRect Face = {0,0,0,0};
	GOS_Element *Parent = nullptr;
	std::vector<std::unique_ptr<GOS_Element>> Childs;
    virtual ~GOS_Element() {};
	virtual void Update(float x, float y, SDL_Event ev)
	{
	}
    virtual bool MouseOn(float x, float y)
    {
		return x >= Face.x && y >= Face.y && x <= Face.x + Face.w && y <= Face.y + Face.h;
    }
    virtual void Draw(SDL_Renderer* _r)
    {
		SDL_SetRenderDrawColor(_r, Color.r, Color.g, Color.b, Color.a);
		SDL_RenderFillRect(_r, &Face);
    }
    virtual void SetColor(GOS_Color* _c)
    {
		Color = *_c;
    }
    virtual void SetFace(SDL_FRect* _f)
    {
		Face = *_f;
    }
    virtual std::string GetName()
    {
		return Name;
    }
	virtual bool StoresId(int id)
	{
		for(auto& child : this->Childs) {
			if(child && child->Id == id){
				return true;
			}
		}
		return false;
	}
	virtual bool StoresName(std::string name)
	{
		for(auto& child : this->Childs) {
			if(child && child->GetName() == name) {
				return true;
			}
		}
		return false;
	}
	// Erasers
	virtual void EraseById(int id)
	{
		if(!StoresId(id)) return;
		for(auto child = this->Childs.begin(); child != this->Childs.end(); ++child) {
			if((*child) && (*child)->Id == id) {
				this->Childs.erase(child);
				return;
			}
		}

	}
	virtual void EraseByName(std::string name)
	{
		if(!StoresName(name)) return;
		for(auto child = this->Childs.begin(); child != this->Childs.end(); ++child) {
			if((*child) && (*child)->GetName() == name) {
				this->Childs.erase(child);
				return;
			}
		}
	}
	// Getters
	virtual GOS_Element* GetById(int id)
	{
		if(!StoresId(id)) return nullptr;
		for(auto& child : this->Childs) {
			if(child && child->Id == id) {
				return child.get();
			}
		}
		return nullptr;
	}
	virtual GOS_Element* GetByName(std::string name)
	{
		if(!StoresName(name)) return nullptr;
		for(auto& child : this->Childs) {
			if(child && child->GetName() == name) {
				return child.get();
			}
		}
		return nullptr;
	}
};

#endif
