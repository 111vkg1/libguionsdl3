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
    virtual ~GOS_Element() {};
	virtual void Update(float x, float y, SDL_Event ev)
	{
	}
    virtual bool MouseOn(float x, float y)
    {
		return x >= Face.x && y >= Face.y && x <= Face.x + Face.h && y <= Face.y + Face.h;
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
};

#endif
