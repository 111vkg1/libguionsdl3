#ifdef USETEXTURES
#ifndef GOS_TEXTURED
#define GOS_TEXTURED

enum class GOS_RenderType
{
	Centered,
	Stretched,
	Standart,
	Left,
	Right
};

struct GOS_TexturedBox : public GOS_StyledBox
{
	GOS_TexturedBox()
	{
		Name = "Textured box";
	}
	SDL_Texture* Texture;
	GOS_RenderType RenderType = GOS_RenderType::Centered;
	bool Active = false;

	virtual void Draw(SDL_Renderer* _r) override
	{
		if(!Visible) return;
		SDL_FRect BorderFrame = {Face.x, Face.y, Face.w+BorderSize, Face.h+BorderSize};
		SDL_SetRenderDrawColor(_r, Color.r, Color.g, Color.b, Color.a);
		SDL_RenderFillRect(_r, &BorderFrame);
		if(Texture == nullptr) return;
		switch(RenderType){
			case GOS_RenderType::Stretched:
			{	
				SDL_RenderTexture(_r, Texture, NULL, &Face);
				break;
			}
			case GOS_RenderType::Standart:
			{
				float TextureW, TextureH;
				SDL_GetTextureSize(Texture, &TextureW, &TextureH);
				SDL_FRect TextureFace = {Face.x, Face.y, TextureW, TextureH};	
				SDL_RenderTexture(_r, Texture, NULL, &TextureFace);
				break;
			}
			case GOS_RenderType::Centered:	
			{
				float TextureW, TextureH;
				SDL_GetTextureSize(Texture, &TextureW, &TextureH);
				SDL_FRect TextureFace = {Face.x, Face.y, Face.w, Face.h};	
				int DistX = Face.w - TextureW;
				TextureFace.x = Face.x + DistX/2;
				TextureFace.w = TextureW;
				int DistY = Face.h - TextureH;
				TextureFace.y = Face.y + DistY/2;
				TextureFace.h = TextureH;
				SDL_RenderTexture(_r, Texture, NULL, &TextureFace);
				break;
			}
			case GOS_RenderType::Right:
			{
				float TextureW, TextureH;
				SDL_GetTextureSize(Texture, &TextureW, &TextureH);
				SDL_FRect TextureFace = {Face.x, Face.y, Face.w, Face.h};	
				TextureFace.x = Face.x + Face.w - TextureW;
				TextureFace.w = TextureW;
				float DistY = Face.h - TextureH;
				TextureFace.y = Face.y + DistY/2;
				TextureFace.h = TextureH;
				SDL_RenderTexture(_r, Texture, NULL, &TextureFace);
				break;

			}
			case GOS_RenderType::Left:
			{
				float TextureW, TextureH;
				SDL_GetTextureSize(Texture, &TextureW, &TextureH);
				SDL_FRect TextureFace = {Face.x, Face.y, Face.w, Face.h};	
				TextureFace.x = Face.x;
				TextureFace.w = TextureW;
				float DistY = Face.h - TextureH;
				TextureFace.y = Face.y + DistY/2;
				TextureFace.h = TextureH;
				SDL_RenderTexture(_r, Texture, NULL, &TextureFace);
				break;
			}

		}	
	}
	virtual bool MouseOn(float x, float y)
	{
		Active = (x >= Face.x && x <= Face.x+Face.w) && (y >= Face.y && y <= Face.y+Face.h);
		return Active;
	}
};

struct GOS_TexturedButton : public GOS_TexturedBox 
{
    short BorderSize = 3;
    GOS_TexturedButton()
    {
        Name = "TexturedButton";
    };
    virtual std::string GetName() override
    {
        return Name;
    }
    virtual void Draw(SDL_Renderer* _r) override
    {
        if(!Visible)
			return;
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
		if(Texture == nullptr) return;
		switch(RenderType){
			case GOS_RenderType::Stretched: 
			{	
				SDL_RenderTexture(_r, Texture, NULL, &Face);
				break;
			}
			case GOS_RenderType::Standart:
			{
				float TextureW, TextureH;
				SDL_GetTextureSize(Texture, &TextureW, &TextureH);
				SDL_FRect TextureFace = {Face.x, Face.y, TextureW, TextureH};	
				SDL_RenderTexture(_r, Texture, NULL, &TextureFace);
				break;
			}
			case GOS_RenderType::Centered:	
			{
				float TextureW, TextureH;
				SDL_GetTextureSize(Texture, &TextureW, &TextureH);
				SDL_FRect TextureFace = {Face.x, Face.y, Face.w, Face.h};	
				float DistX = Face.w - TextureW;
				TextureFace.x = Face.x + DistX/2;
				TextureFace.w = TextureW;
				float DistY = Face.h - TextureH;
				TextureFace.y = Face.y + DistY/2;
				TextureFace.h = TextureH;
				SDL_RenderTexture(_r, Texture, NULL, &TextureFace);
				break;
			}
			case GOS_RenderType::Right:
			{
				float TextureW, TextureH;
				SDL_GetTextureSize(Texture, &TextureW, &TextureH);
				SDL_FRect TextureFace = {Face.x, Face.y, Face.w, Face.h};	
				TextureFace.x = Face.x + Face.w - TextureW;
				TextureFace.w = TextureW;
				float DistY = Face.h - TextureH;
				TextureFace.y = Face.y + DistY/2;
				TextureFace.h = TextureH;
				SDL_RenderTexture(_r, Texture, NULL, &TextureFace);
				break;
			}
			case GOS_RenderType::Left:
			{
				float TextureW, TextureH;
				SDL_GetTextureSize(Texture, &TextureW, &TextureH);
				SDL_FRect TextureFace = {Face.x, Face.y, Face.w, Face.h};	
				TextureFace.x = Face.x;
				TextureFace.w = TextureW;
				float DistY = Face.h - TextureH;
				TextureFace.y = Face.y + DistY/2;
				TextureFace.h = TextureH;
				SDL_RenderTexture(_r, Texture, NULL, &TextureFace);
				break;
			}
    	}
	}
};

#endif
#endif
