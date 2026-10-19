#ifndef GOS_METER
#define GOS_METER

struct GOS_MeterHorizontal : public GOS_Element
{
	GOS_MeterHorizontal()
	{
		this->Name = "MeterHorizontal";
		this->Dragable = false;
		GOS_Box *holder = new GOS_Box();
		holder->Face = {0, 0, 10, 10};
		holder->Parent = this;
		this->Childs.push_back(std::unique_ptr<GOS_Element>(holder));
		this->Childs.front()->Dragable = true;
	};
	virtual void SetHolderColor(GOS_Color* _c)
	{
		this->Childs.front()->Color = *_c;
	}
	virtual void SetFace(SDL_FRect* _R)
	{
		this->Face = *_R;
		this->Childs.front()->Face = {
			_R->x - this->Face.w/2,
			_R->y,
			10,
			10
		};
	}
	virtual void SetHolderSize(float w, float h)
	{
		this->Childs.front()->Face.w = w;
		this->Childs.front()->Face.h = h;
	}
	virtual void Update(float x, float y, SDL_Event ev) override
	{
		this->Childs.front()->Update(x, y, ev);
		if(this->Childs.front()->Face.x+this->Childs.front()->Face.w/2 < this->Face.x) this->Childs.front()->Face.x = this->Face.x-this->Childs.front()->Face.w/2;
		if(this->Childs.front()->Face.y != this->Face.y) this->Childs.front()->Face.y = this->Face.y-this->Face.h/2;
		if(this->Childs.front()->Face.x+this->Childs.front()->Face.w/2 > this->Face.x+this->Face.w) this->Childs.front()->Face.x = this->Face.x+this->Face.w-this->Childs.front()->Face.w/2;
	}
	virtual void Draw(SDL_Renderer *_r) override
	{
		SDL_SetRenderDrawColor(_r, this->Color.r, this->Color.g, this->Color.b, this->Color.a);
		SDL_RenderFillRect(_r, &Face);
		this->Childs.front()->Draw(_r);
	}
	virtual float GetValue() override
	{	
		return (this->Childs.front()->Face.x - this->Face.x + this->Childs.front()->Face.w/2) / (this->Face.w);
	}
};	

struct GOS_MeterVertical : public GOS_MeterHorizontal
{
	GOS_MeterVertical()
	{
		this->Name = "MeterVertical";
		this->Dragable = false;
		GOS_Box *holder = new GOS_Box();
		holder->Face = {0, 0, 10, 10};
		holder->Parent = this;
		this->Childs.push_back(std::unique_ptr<GOS_Element>(holder));
		this->Childs.front()->Dragable = true;
	};
	virtual void Update(float x, float y, SDL_Event ev) override
	{
		this->Childs.front()->Update(x, y, ev);
		if(this->Childs.front()->Face.y+this->Childs.front()->Face.h/2 < this->Face.y) this->Childs.front()->Face.y = this->Face.y-this->Childs.front()->Face.h/2;
		if(this->Childs.front()->Face.x != this->Face.x) this->Childs.front()->Face.x = this->Face.x-this->Face.w/2;
		if(this->Childs.front()->Face.y+this->Childs.front()->Face.h/2 > this->Face.y+this->Face.h) this->Childs.front()->Face.y = this->Face.y+this->Face.h-this->Childs.front()->Face.h/2;
	}
	virtual float GetValue() override
	{	
		return (this->Childs.front()->Face.y - this->Face.y + this->Childs.front()->Face.h/2) / (this->Face.h);
	}
};

#endif //GOS_METER
