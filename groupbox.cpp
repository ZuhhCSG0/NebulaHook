#include "sdk.h"
#include "controls.h"
#include "Render.h"
#include "Menu.h"
MGroupbox::MGroupbox(MBaseElement* parent, std::string caption, int x_offset, int y_offset, float x_blocks, int y_blocks, bool inside)
{
	this->caption = caption;
	this->parent = parent;
	this->position = parent->position;

	parent->AddChildControl(this);
	this->inside = inside;



	this->x_offset = x_offset;
	this->x_blocks = x_blocks;
	this->y_blocks = y_blocks;
	this->y_offset = y_offset;
}

void MGroupbox::Draw()
{
	int alpha = m_pMenu->alpha;
	if (inside)
	{
		this->position = this->parent->position;
		this->position.x += 10;
		this->position.y += 10;

		this->size.x = parent->size.x - 20;

		for (int i = 0; i < this->parent->Children.size(); i++)
			if (this->parent->Children.at(i) != (MBaseElement*)this)
			{
				this->position.y += this->parent->Children.at(i)->size.y + 10; //boxes are 15 px big, that means 5 difference is natural
			}
			else
				break;

		int buffersize = 0;
		for (int i = 0; i < this->Children.size(); i++)
			buffersize += this->Children.at(i)->size.y;

		this->size.y = 30 + 5 * this->Children.size() + buffersize;

		g_pRender->BorderBoxOutlinedText(this->position.x + 1, this->position.y + 1, this->size.x - 2, this->size.y - 2, 1, D3DCOLOR_RGBA(10, 10, 10, 255), D3DCOLOR_ARGB(alpha, 10, 10, 10), (char*)this->caption.c_str(), g_pRender->Fonts.menu_control);
		g_pRender->BorderBoxOutlinedText2(this->position.x, this->position.y, this->size.x, this->size.y, 1, D3DCOLOR_RGBA(10, 10, 10, 255), D3DCOLOR_RGBA(55, 55, 55, 255), (char*)this->caption.c_str(), g_pRender->Fonts.menu_control);
		//font size
		//	g_pRender->Text((char*)this->caption.c_str(), position.x + size.x/2, position.y - g_pRender->menu_control_size / 2, centered, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));
	}
	else
	{

		this->position = this->parent->position;
		this->position.x = m_pMenu->MainWindow->position.x + 25; //not +10 because
		this->position.y += m_pMenu->MainWindow->dragYoffset + 50;

		int y_minus = this->y_blocks == 2 ? 20 : 30;

		this->size.x = (m_pMenu->MainWindow->size.x - 40) / 3 * x_blocks - 15; //left, right and middle shit offsets
		this->size.y = (m_pMenu->MainWindow->size.y - y_minus - m_pMenu->MainWindow->dragYoffset) / 2 * y_blocks - 30;

		int x = this->position.x + (10 + (m_pMenu->MainWindow->size.x - 40) / 3) * (this->x_offset - 1);
		int y = this->position.y + ((m_pMenu->MainWindow->size.y - y_minus - m_pMenu->MainWindow->dragYoffset) / 2) * (this->y_offset - 1) - 10;

		g_pRender->BorderedBox(x, y, this->size.x, this->size.y, D3DCOLOR_ARGB(alpha, 55, 55, 55));
		g_pRender->BorderedBox(x + 1, y + 1, this->size.x - 2, this->size.y - 2, BLACK(alpha));

		int name_x = this->position.x + (10 + (m_pMenu->MainWindow->size.x - 40) / 3) * (this->x_offset - 1) + this->size.x / 2 - 15;
		int name_y = this->position.y + ((m_pMenu->MainWindow->size.y - y_minus - m_pMenu->MainWindow->dragYoffset) / 2) * (this->y_offset - 1) - 10;
		name_y -= g_pRender->menu_control_size / 2; //font size
		g_pRender->Text((char*)this->caption.c_str(), name_x, name_y, centered, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));

		this->position.x += (10 + (m_pMenu->MainWindow->size.x - 40) / 3) * (this->x_offset - 1);
		this->position.y += ((m_pMenu->MainWindow->size.y - y_minus - m_pMenu->MainWindow->dragYoffset) / 2) * (this->y_offset - 1) - 10;
	}





	//bc of things like dropboxes
	for (int i = Children.size() - 1; i >= 0; i--)
		Children[i]->Draw();

}


MGroupbox2::MGroupbox2(MBaseElement* parent, std::string caption, int x_offset, int y_offset, float x_blocks, int y_blocks, bool inside, int sizeX, int sizeY, int positionX, int positionY)
{
	this->caption = caption;
	this->parent = parent;
	this->position = parent->position;

	parent->AddChildControl(this);
	this->inside = inside;



	this->x_offset = x_offset;
	this->x_blocks = x_blocks;
	this->y_blocks = y_blocks;
	this->y_offset = y_offset;
	this->sizex = sizeX;
	this->sizey = sizeY;
	this->positonx = positionX;
	this->positony = positionY;
}


void MGroupbox2::Draw()
{
	int alpha = m_pMenu->alpha;
	if (inside)
	{
		this->position = this->parent->position;
		this->position.x += 10;
		this->position.y += 10;

		this->size.x = parent->size.x - 20;

		for (int i = 0; i < this->parent->Children.size(); i++)
			if (this->parent->Children.at(i) != (MBaseElement*)this)
			{
				this->position.y += this->parent->Children.at(i)->size.y + 10; //boxes are 15 px big, that means 5 difference is natural
			}
			else
				break;

		int buffersize = 0;
		for (int i = 0; i < this->Children.size(); i++)
			buffersize += this->Children.at(i)->size.y;
		this->size.y = 15 + 5 * this->Children.size() + buffersize;



		//	g_pRender->BorderedBox(position.x, position.y, size.x, size.y, D3DCOLOR_ARGB(alpha, 55, 55, 55));
		//		g_pRender->BorderedBox(position.x + 1, position.y + 1, size.x - 2, size.y - 2, BLACK(alpha));
		//font size
		//	g_pRender->Text((char*)this->caption.c_str(), position.x + size.x / 2, position.y - g_pRender->menu_control_size / 2, centered, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));
	}
	else
	{

		this->position = m_pMenu->MainWindow->position;
		this->position.x = m_pMenu->MainWindow->position.x + positonx + 25; //not +10 because
		this->position.y += m_pMenu->MainWindow->dragYoffset + positony + 50;

		int y_minus = this->y_blocks == 2 ? 20 : 30;

		this->size.x = this->sizex; //left, right and middle shit offsets
		this->size.y = this->sizey;

		int x = this->position.x;
		int y = this->position.y;


		//	g_pRender->BorderedBox(x, y, this->size.x, this->size.y, D3DCOLOR_ARGB(alpha, 55, 55, 55));
		//	g_pRender->BorderedBox(x + 1, y + 1, this->size.x - 2, this->size.y - 2, BLACK(alpha));

		int name_x = this->position.x + this->size.x / 2;
		int name_y = this->position.y;
		name_y -= g_pRender->menu_control_size / 2; //font size


													//g_pRender->BorderedBox(position.x, position.y, size.x, size.y, D3DCOLOR_ARGB(alpha, 55, 55, 55));
		g_pRender->BorderBoxOutlinedText(this->position.x, y, this->size.x, this->size.y, 1, D3DCOLOR_RGBA(10, 10, 10, 255), D3DCOLOR_RGBA(55, 55, 55, 255), (char*)this->caption.c_str(), g_pRender->Fonts.menu_control);
		g_pRender->BorderBoxOutlinedText2(this->position.x + 1, y + 1, this->size.x - 2, this->size.y - 2, 1, D3DCOLOR_RGBA(10, 10, 10, 255), D3DCOLOR_ARGB(alpha, 10, 10, 10), (char*)this->caption.c_str(), g_pRender->Fonts.menu_control);

		//g_pRender->BorderBoxOutlinedText2(x + 0.5, y + 0.5, this->size.x - 1, this->size.y - 1, 1, D3DCOLOR_RGBA(10, 10, 10, 255), D3DCOLOR_RGBA(0, 0, 0, 255), (char*)this->caption.c_str(), g_pRender->Fonts.menu_control);

		//	g_pRender->Text((char*)this->caption.c_str(), name_x, name_y, centered, g_pRender->Fonts.menu_control, true, WHITE(alpha), BLACK(alpha));

		//	this->position.x += (10 + (m_pMenu->MainWindow->size.x - 40) / 3) * (this->x_offset - 1);
		//	this->position.y += ((m_pMenu->MainWindow->size.y - y_minus - m_pMenu->MainWindow->dragYoffset) / 2) * (this->y_offset - 1) - 35;
	}





	//bc of things like dropboxes
	for (int i = Children.size() - 1; i >= 0; i--)
		Children[i]->Draw();

}
