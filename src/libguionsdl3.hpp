#ifndef LIBGUIONSDL3
#define LIBGUIONSDL3

#include<SDL3/SDL.h>
#include<vector>
#include<map>
#include<string>
#include<random>
#include<memory>
#include<stdexcept>

class IdAlreadyExistsException : public std::exception
{
	private:
		std::string message;

	public:
		explicit IdAlreadyExistsException(int id)
			: message("Id " + std::to_string(id) + " already exists!") {}

		const char* what() const noexcept override
		{
			return message.c_str();
		}
};

#ifdef USETEXT

#include<SDL3_ttf/SDL_ttf.h>
extern TTF_Font *Font;
std::map<std::string, SDL_Texture*> TextureCash;
SDL_Color TextColor = {0,0,0,255};

#endif

#include<GOS3/GOS_Color.hpp>
#include<GOS3/GOS_Element.hpp>
#include<GOS3/GOS_Box.hpp>
#include<GOS3/GOS_Button.hpp>

#ifdef USETEXT

#include<SDL3_image/SDL_image.h>
#include<GOS3/GOS_Text.hpp>

#endif // USETEXT

#ifdef USETEXTURES
#include<GOS3/GOS_Textured.hpp>
#endif

#include<GOS3/GOS_Menu.hpp>

struct GOS_GUI
{
    bool Visible = 1;
    SDL_Rect RFace = {0,0,0,0};
    std::vector<std::unique_ptr<GOS_Element>> Childs;
	int RepeatTicks = 250;

    GOS_GUI() = default;

    ~GOS_GUI() = default;
    void AddElement(GOS_Element* element)
    {
		element->Id = Childs.size();
        Childs.push_back(std::unique_ptr<GOS_Element>(element));
    }
	void AddElementWithId(GOS_Element* element, int newId = -1)
	{
		std::unique_ptr<GOS_Element> ptr(element);
		if(newId > -1)
			ptr->Id = newId;
		if(this->GetElementById(ptr->Id) == nullptr){
			Childs.push_back(std::move(ptr));
		}
		else{
			throw IdAlreadyExistsException(ptr->Id);
		}
	}
    void Draw(SDL_Renderer* _r)
    {
        if(!Visible)
            return;
        for(auto& child : Childs) {
            if(child && child->Visible) {
                child->Draw(_r);
            }
        }
    }
    GOS_Element* GetSelected()
    {
        for(auto it = Childs.rbegin(); it != Childs.rend(); ++it) {
            auto& child = *it;
            if(child) {
                if(child->Active){
                    return child.get();
                }
            }
        }
        return nullptr;
    }
    void EraseElementByName(std::string name)
    {
        for(size_t it = 0; it < Childs.size(); it++) {
            if(Childs[it] && Childs[it]->GetName() == name) {
                Childs.erase(Childs.begin() + it);
            }
        }
    }
    void EraseElementById(int id)
    {
        for(size_t it = 0; it < Childs.size(); it++) {
            if(Childs[it] && Childs[it]->Id == id) {
                Childs.erase(Childs.begin() + it);
            }
        }
    }
    void Update(float x, float y, SDL_Event ev)
    {
        for(auto& child : Childs) {
            if(child) {
                child->Update(x, y, ev);
            }
        }
		#ifdef USETEXT
		if(ev.type == SDL_EVENT_KEY_DOWN && ev.key.key == SDLK_BACKSPACE) {
        	for(auto& child : Childs) {
            	if(child) {
                	auto* inputBox = dynamic_cast<GOS_TextInputBox*>(child.get());
                	if(inputBox && !inputBox->Text.empty()) {
                		int now = SDL_GetTicks();
       		     		if(now - inputBox->LastCharTick >= RepeatTicks) {
                			inputBox->Text.pop_back();
                			inputBox->LastCharTick = now;
            	    		inputBox->LastChar = '\b';
            			}			
					}
            	}
        	}
    	}
		if(ev.type == SDL_EVENT_TEXT_INPUT) {
			for(auto& child : Childs) {
				GOS_TextInputBox* inputBox = dynamic_cast<GOS_TextInputBox*>(child.get());
            	if(inputBox && inputBox->Name == "TextInputBox") {
            		int now = SDL_GetTicks();
            		if(inputBox->LastChar != ev.text.text[0]) {
                		inputBox->Text += ev.text.text;
                		inputBox->LastChar = ev.text.text[0];
                		inputBox->LastCharTick = now;
            		} 
            		else if(now - inputBox->LastCharTick >= RepeatTicks) {
                		inputBox->Text += ev.text.text;
                		inputBox->LastCharTick = now;
            		}			
        		}
			}
		}
		#endif
    }
    GOS_Element* GetElementAt(float x, float y)
    {
        for(auto& child : Childs) {
            if(child && child->Visible && child->MouseOn(x, y)) {
                return child.get();
            }
        }
        return nullptr;
    }
    GOS_Element* GetElementByName(std::string Name)
    {
        for(auto& child : Childs) {
            if(child && child->Visible && child->Name == Name) {
                return child.get();
            }
        }
        return nullptr;
    }
    GOS_Element* GetElementById(int id)
    {
        for(auto& child : Childs) {
            if(child && child->Id == id) {
                return child.get();
            }
        }
        return nullptr;
    }
};

#endif // LIBGUIONSDL3
