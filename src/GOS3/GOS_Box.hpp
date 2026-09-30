#ifndef GOS_BOX
#define GOS_BOX

struct GOS_Box : public GOS_Element
{
	GOS_Box()
	{
		Name = "Box";
	};
	virtual std::string GetName() override
	{
		return Name;
	}		
};

struct GOS_StyledBox : public GOS_Box
{
	short BorderSize = 3;
	GOS_StyledBox()
	{
		Name = "StyledBox";
	};
	virtual void Draw(SDL_Renderer* _r) override
	{
		if(!Visible)
			return;
		SDL_SetRenderDrawColor(_r, (Color.r-50*(Color.r>=50)), (Color.g-50*(Color.r>=50)), (Color.b-50*(Color.b>=50)), Color.a);
		SDL_Rect BorderFace = {Face.x, Face.y, Face.w+BorderSize, Face.h+BorderSize};
		SDL_RenderFillRect(_r, &BorderFace);
		SDL_SetRenderDrawColor(_r, Color.r, Color.g, Color.b, Color.a);
		SDL_RenderFillRect(_r, &Face);
	}
};

#endif
