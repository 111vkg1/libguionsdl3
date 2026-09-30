#ifndef GOS_COLOR
#define GOS_COLOR

struct GOS_Color
{
    int r, g, b, a;
    void SetAllTo(int n)
    	{
	this->r = n;
	this->g = n;
	this->b = n;	
    }
    void SetRandom()
    {
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, 256);
	this->r = dist(rng);
	this->g = dist(rng);
	this->b = dist(rng);
    }
    std::string GetHex()
    {
	char buffer[10];
	std::snprintf(buffer, sizeof(buffer), "#%02X%02X%02X%02X", this->r, this->g, this->b, this->a);
	return std::string(buffer);
    }
    GOS_Color(int r, int g, int b, int a)
    {
		this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
    };
};

#endif
