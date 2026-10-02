#ifndef GOS_BUTTON
#define GOS_BUTTON

struct GOS_Button : public GOS_Element
{
    GOS_Button()
    {
        Name = "Button";
    };
    virtual std::string GetName() override
    {
        return Name;
    }
    virtual void Draw(SDL_Renderer* _r) override
    {
        if(Visible){
            if(Active)
                SDL_SetRenderDrawColor(_r, (Color.r-50*(Color.r>=50)), (Color.g-50*(Color.g>=50)), (Color.b-50*(Color.b>=50)), Color.a);
            else
                SDL_SetRenderDrawColor(_r, Color.r, Color.g, Color.b, Color.a);

            SDL_RenderFillRect(_r, &Face);
        }
    }
	virtual void Update(float x, float y, SDL_Event ev) override
	{
        Active = (x >= Face.x && y >= Face.y && x <= Face.x+Face.w && y <= Face.y+Face.h);
	}
    virtual bool MouseOn(float x, float y) override
    {
        return Active;
    }
};

struct GOS_StyledButton : public GOS_Button
{
    // GOS_StyledButton is GOS_Button with border
    short BorderSize = 3;
    GOS_StyledButton()
    {
        Name = "StyledButton";
    };
    virtual std::string GetName() override
    {
        return Name;
    }
    virtual void Draw(SDL_Renderer* _r) override
    {
        if(Visible){
            SDL_SetRenderDrawColor(_r, (Color.r-50*(Color.r>=50)), (Color.g-50*(Color.g>=50)), (Color.b-50*(Color.b>=50)), Color.a);
            SDL_FRect BorderFace = {Face.x, Face.y, Face.w+BorderSize, Face.h+BorderSize};
            SDL_RenderFillRect(_r, &BorderFace);
            if(Active){
                SDL_SetRenderDrawColor(_r, (Color.r-50*(Color.r>=50)), (Color.g-50*(Color.g>=50)), (Color.b-50*(Color.b>=50)), Color.a);
            }
            else{
                SDL_SetRenderDrawColor(_r, Color.r, Color.g, Color.b, Color.a);
            }

            SDL_RenderFillRect(_r, &Face);
	    #ifdef USETEXT
            if(TextureCash.find(Text) == TextureCash.end()){
                SDL_Surface* _s = TTF_RenderText_Blended(Font, Text.c_str(), Text.size(), TextColor);
                TextureCash[Text] = SDL_CreateTextureFromSurface(_r, _s);
                SDL_DestroySurface(_s);
            }
            if(float(Text.size())*12 >= Face.w){
                SDL_RenderTexture(_r, TextureCash[Text], nullptr, &Face);
            }
            else{
                SDL_FRect _t = {Face.x + (Face.w - float(Text.size())*12)/2, Face.y, float(Text.size())*12, Face.h};
                SDL_RenderTexture(_r, TextureCash[Text], nullptr, &_t);
            }
	    #endif
        }
    }
};

#endif
