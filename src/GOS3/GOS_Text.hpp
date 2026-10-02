#ifndef GOS_TEXT
#define GOS_TEXT

#ifndef FONTSIZE
#define FONTSIZE 15.0
#endif // FONTSIZE

#ifdef USETEXT
struct GOS_PointButton : public GOS_StyledButton
{
    GOS_PointButton()
    {
        Name = "PointButton";
    };
    virtual std::string GetName() override
    {
        return Name;
    }
    virtual bool MouseOn(float x, float y) override
    {
        return (x >= Face.x && y >= Face.y && x <= Face.x+Face.w && y <= Face.y+Face.h);
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
            if(Active){
                if(TextureCash.find("v") == TextureCash.end()){
                    SDL_Surface* _s = TTF_RenderText_Blended(Font, "v", FONTSIZE, TextColor);
                    TextureCash["v"] = SDL_CreateTextureFromSurface(_r, _s);
                    SDL_DestroySurface(_s);
                }
                SDL_RenderTexture(_r, TextureCash["v"], nullptr, &Face);
            }
            else{
                if(TextureCash.find("x") == TextureCash.end()){
                    SDL_Surface* _s = TTF_RenderText_Blended(Font, "x", FONTSIZE, TextColor);
                    TextureCash["x"] = SDL_CreateTextureFromSurface(_r, _s);
                    SDL_DestroySurface(_s);
                }
                SDL_RenderTexture(_r, TextureCash["x"], nullptr, &Face);
            }
        }
    }
};
struct GOS_TextBox : public GOS_Box
{
    // Simple textbox for text printing
    GOS_TextBox()
    {
        Name = "TextBox";
    };
    virtual void Draw(SDL_Renderer* _r) override
    {
        if(Visible){
            SDL_SetRenderDrawColor(_r, Color.r, Color.g, Color.b, Color.a);
            SDL_RenderFillRect(_r, &Face);
            if(TextureCash.find(Text) == TextureCash.end()){
                SDL_Surface* _s = TTF_RenderText_Blended_Wrapped(Font, Text.c_str(), Text.size(), TextColor, 0);
                TextureCash[Text] = SDL_CreateTextureFromSurface(_r, _s);
                SDL_DestroySurface(_s);
            }
            if(int(Text.size())*12 >= Face.w){
                SDL_RenderTexture(_r, TextureCash[Text], nullptr, &Face);
            }
            else{
                SDL_FRect _t = {Face.x + (Face.w - int(Text.size())*12)/2, Face.y, int(Text.size())*12, Face.h};
                SDL_RenderTexture(_r, TextureCash[Text], nullptr, &_t);
            }
        }
    }
};

struct GOS_TextInputBox : public GOS_Button
{
	char LastChar = ' ';
	int LastCharTick = -150;
    GOS_TextInputBox()
    {
        Name = "TextInputBox";
        Text = "Input";
    }
    virtual void Draw(SDL_Renderer* _r) override
    {
        if(!Visible) return;
        SDL_SetRenderDrawColor(_r, Color.r, Color.g, Color.b, Color.a);
        SDL_RenderFillRect(_r, &Face);
        if(Text == "") return;
		if(TextureCash.find(Text) == TextureCash.end()){
            SDL_Surface* _s = TTF_RenderText_Blended_Wrapped(Font, Text.c_str(), Text.size(), TextColor, 0);
            TextureCash[Text] = SDL_CreateTextureFromSurface(_r, _s);
            SDL_DestroySurface(_s);
        }
        if(int(Text.size())*12 >= Face.w){
            SDL_RenderTexture(_r, TextureCash[Text], nullptr, &Face);
        }
        else{
            SDL_FRect _t = {Face.x + (Face.w - int(Text.size())*12)/2, Face.y, int(Text.size())*12, Face.h};
            SDL_RenderTexture(_r, TextureCash[Text], nullptr, &_t);
        }
    }
};
#endif

#endif
