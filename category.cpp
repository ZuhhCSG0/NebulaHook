#include "sdk.h"
#include "controls.h"
#include "Render.h"
#include "Menu.h"
MCategory* MCategory::CurrentCategory = nullptr;
MCategory::MCategory(std::string name, MWindow* parent, byte* texture,UINT size, int res_x, int res_y)
{
	this->name = name;
	this->parent = parent;
	this->position = parent->position;
	this->res_x = res_x;
	this->res_y = res_y;
	this->texture_size = size;
	this->tex_array = texture;
	printf("%i", size);

	
	parent->AddChildControl(this);
}





void MCategory::Draw()
{
	MWindow* Parent = (MWindow*)this->parent; //We could use m_pMenu->MainWindow-> instead, why tf tho
	int width = (Parent->size.x - 20) / Parent->Children.size();

	//if(!this->texture)
	//	D3DXCreateTextureFromFileInMemoryEx(g_pRender->device, this->tex_array, this->texture_size, res_x, res_y, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &this->texture);

	
		this->position = parent->position;
	
		this->position.x += 10;


	int height = m_pMenu->MainWindow->dragYoffset + 1;
	int index = -1;

	
		for (int i = 0; i < Parent->Children.size(); i++)
			if (Parent->Children.at(i) == (MBaseElement*)this)
			{
				position.x += width * i;
				index = i;
			}
	

	if (Parent->Clicked(Vector(this->position.x, this->position.y + 25), Vector(width, height, 0)))
	{
		if (MCategory::CurrentCategory != nullptr)
			MCategory::CurrentCategory->active = false;

		this->active = true;
		MCategory::CurrentCategory = this;
	}
	int alpha = m_pMenu->alpha;
	if (this->active)
	{
		g_pRender->FilledBox(this->position.x + width / 8, this->position.y + height + 25, width - width / 4.1, 1, D3DCOLOR_ARGB(alpha, 255, 0, 0));
		/*if(index != 0)
		g_pRender->Line(this->position.x, this->position.y, this->position.x, this->position.y + height, D3DCOLOR_ARGB(alpha, 41, 42, 45));
		if(index != this->parent->Children.size())
		g_pRender->Line(this->position.x + width, this->position.y, this->position.x + width, this->position.y + height, D3DCOLOR_ARGB(alpha, 41, 42, 45));*/

		for (int i = Children.size() - 1; i >= 0; i--)
			Children[i]->Draw();
	}
	else
	{
	//	g_pRender->FilledBox(this->position.x, this->position.y + 25, width, height, D3DCOLOR_ARGB(alpha, 18, 18, 18));
		g_pRender->FilledBox(this->position.x + width / 6, this->position.y + height + 25, width - width / 3.1, 1, D3DCOLOR_ARGB(alpha, 50, 50, 50));
		//g_pRender->Line(this->position.x, this->position.y + height, this->position.x + width, this->position.y + height,  D3DCOLOR_ARGB(alpha, 41, 42, 45));
	}

	g_pRender->Text((char*)this->name.c_str(), this->position.x + width / 2, this->position.y + 33, text_alignment::centered, g_pRender->Fonts.menu_control, false, active ? D3DCOLOR_RGBA(255, 0, 0,alpha) : D3DCOLOR_RGBA(155, 155, 155, alpha), D3DCOLOR_RGBA(255, 255, 255, 255));

//	g_pRender->Sprite(this->texture, this->position.x + width/2 - 32/*size/2 of the sprites*/, this->position.y, this->res_x, this->res_y, width/ this->res_x , m_pMenu->MainWindow->dragYoffset/this->res_y,  0, WHITE(alpha));
	
	this->position.x -= 10;
}