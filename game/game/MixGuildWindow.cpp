/*
*	STR MIX GUILD 2019
*	gabrielcarlos91@hotmail.com
*/
#include "stdafx.h"
#include "MixGuildWindow.h"

CMixGuildWindow::CMixGuildWindow()
{
}

CMixGuildWindow::~CMixGuildWindow()
{
}

void CMixGuildWindow::OnMouseMove(class CMouse* pcMouse)
{
	pWindow1->OnMouseMove(pcMouse, 0, 0, DX::Graphic::GetWidthBackBuffer(), DX::Graphic::GetHeightBackBuffer(), 0, 0);
}

BOOL CMixGuildWindow::OnMouseClick(class CMouse* pcMouse)
{
	if (pWindow1->OnMouseClick(pcMouse, 0, 0, DX::Graphic::GetWidthBackBuffer(), DX::Graphic::GetHeightBackBuffer(), 0, 0))
		return TRUE;
	return FALSE;
}

BOOL CMixGuildWindow::OnMouseScroll(class CMouse* pcMouse)
{
	UI::Window_ptr pWindowItem = pWindow1->GetElement<UI::Window>(WINDOWID_MixData);
	if (pWindow1->IsOpen() && pWindowItem)
	{
		if (pWindowItem->OnMouseScroll(pcMouse, pWindow1->GetX(), pWindow1->GetY(), DX::Graphic::GetWidthBackBuffer(), DX::Graphic::GetHeightBackBuffer(), 0, 0))
			return TRUE;
	}

	if (pWindow1->OnMouseScroll(pcMouse, 0, 0, DX::Graphic::GetWidthBackBuffer(), DX::Graphic::GetHeightBackBuffer(), 0, 0))
		return TRUE;
	return FALSE;
}

BOOL CMixGuildWindow::OnKeyPress(class CKeyboard* pcKeyboard)
{
	if (pWindow1->OnKeyPress(pcKeyboard))
		return TRUE;
	return FALSE;
}

BOOL CMixGuildWindow::OnKeyChar(class CKeyboard* pcKeyboard)
{
	if (pWindow1->OnKeyChar(pcKeyboard))
		return TRUE;
	return FALSE;
}

void CMixGuildWindow::BuildWindow1()
{
	pWindow1 = std::make_shared<UI::Window>(Rectangle2D(20, 20, 762, 553));
	pWindow1->SetImage(UI::ImageLoader::LoadImage("game\\images\\mixguide\\window.png"));

	pWindow1->SetPosition((RESOLUTION_WIDTH >> 1) - (pWindow1->GetWidth() >> 1), (RESOLUTION_HEIGHT >> 1) - (pWindow1->GetHeight() >> 1));

	// Window Item Data
	UI::Window_ptr pWindow2 = std::make_shared<UI::Window>(Rectangle2D(20, 20, 750, 443));
	pWindow2->SetID(WINDOWID_MixData);
	pWindow1->AddElement(pWindow2);

	// List Mix
	UI::List_ptr pListText = std::make_shared<UI::List>(Rectangle2D(20, 24, 270, 310));
	pListText->SetID(LISTID_About);
	pListText->MakeScrollBar(Rectangle2D(274, 4, 6, 300), "game\\images\\UI\\scroll\\barbg_v.png", "game\\images\\UI\\scroll\\icon_2.png");
	pWindow1->AddElement(pListText);

	// Close Button
	UI::Button_ptr pButtonClose = std::make_shared<UI::Button>(Rectangle2D(725, 25, 30, 28));
	pButtonClose->SetActiveImage(UI::ImageLoader::LoadActiveImage("game\\images\\mixguide\\closebtn.png", "game\\images\\mixguide\\closebtn_.png"));
	pButtonClose->SetEvent(UI::Event::Build(std::bind(&CMixGuildWindow::OnCloseButtonClick, this, std::placeholders::_1)));
	pWindow1->AddElement(pButtonClose);

	{
		UI::Text_ptr pItemMixGuide = std::make_shared<UI::Text>(Rectangle2D(335, 15, 240, 14));
		pItemMixGuide->SetText("Gu\355a de mezclas");
		pItemMixGuide->SetFont("Arial", 18, 0, FALSE, TRUE, D3DCOLOR_ARGB(150, 170, 150, 120));
		pWindow1->AddElement(pItemMixGuide);

		UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(20, 55, 240, 14));
		pItemMixName->SetText("Nombre de la mezcla");
		pItemMixName->SetFont("Arial", 16, 0, FALSE, TRUE, D3DCOLOR_ARGB(255, 210, 195, 180));
		pWindow1->AddElement(pItemMixName);

		UI::Text_ptr pItemSheltoms = std::make_shared<UI::Text>(Rectangle2D(228, 55, 240, 14));
		pItemSheltoms->SetText("Sheltoms");
		pItemSheltoms->SetFont("Arial", 16, 0, FALSE, TRUE, D3DCOLOR_ARGB(255, 210, 195, 180));
		pWindow1->AddElement(pItemSheltoms);

		UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(428, 55, 240, 14));
		pItemDesc->SetText("Descripci\363n");
		pItemDesc->SetFont("Arial", 16, 0, FALSE, TRUE, D3DCOLOR_ARGB(255, 210, 195, 180));
		pWindow1->AddElement(pItemDesc);

		// ComboBox
		UI::ComboBox_ptr pComboBox = std::make_shared<UI::ComboBox>(Rectangle2D(620, 55, 110, 26));
		pComboBox->SetDefaultText("Seleccionar");
		pComboBox->SetID(COMBOBOX_DESC);
		pComboBox->SetBackgroundImage(UI::ImageLoader::LoadActiveImage("game\\images\\UI\\combobox\\drop.png", "game\\images\\UI\\combobox\\dropon.png"));
		pComboBox->SetBackgroundSelectedImage(UI::ImageLoader::LoadImage("game\\images\\UI\\combobox\\drop_.png"));
		pComboBox->SetBackgroundActiveImage(UI::ImageLoader::LoadActiveImage("game\\images\\UI\\combobox\\dropbg.png", "game\\images\\UI\\combobox\\dropdown.png"));
		pComboBox->SetHoverColor(D3DCOLOR_ARGB(150, 170, 150, 120));
		//Options
		{
            pComboBox->AddOption(pComboBox->MakeOption("Armas", Rectangle2D(0, 0, 110, 16), FALSE, D3DCOLOR_ARGB(255, 210, 195, 180)));
            pComboBox->AddOption(pComboBox->MakeOption("Armaduras/Tunicas", Rectangle2D(0, 0, 110, 16), FALSE, D3DCOLOR_ARGB(255, 210, 195, 180)));
            pComboBox->AddOption(pComboBox->MakeOption("Escudos", Rectangle2D(0, 0, 110, 16), FALSE, D3DCOLOR_ARGB(255, 210, 195, 180)));
            pComboBox->AddOption(pComboBox->MakeOption("Orbes", Rectangle2D(0, 0, 110, 16), FALSE, D3DCOLOR_ARGB(255, 210, 195, 180)));
            pComboBox->AddOption(pComboBox->MakeOption("Brazaletes", Rectangle2D(0, 0, 110, 16), FALSE, D3DCOLOR_ARGB(255, 210, 195, 180)));
            pComboBox->AddOption(pComboBox->MakeOption("Guanteletes", Rectangle2D(0, 0, 110, 16), FALSE, D3DCOLOR_ARGB(255, 210, 195, 180)));
            pComboBox->AddOption(pComboBox->MakeOption("Botas", Rectangle2D(0, 0, 110, 16), FALSE, D3DCOLOR_ARGB(255, 210, 195, 180)));
            pComboBox->AddOption(pComboBox->MakeOption("Amuleto", Rectangle2D(0, 0, 110, 16), FALSE, D3DCOLOR_ARGB(255, 210, 195, 180)));
            pComboBox->AddOption(pComboBox->MakeOption("Anillo", Rectangle2D(0, 0, 110, 16), FALSE, D3DCOLOR_ARGB(255, 210, 195, 180)));
            pComboBox->AddOption(pComboBox->MakeOption("Sheltom", Rectangle2D(0, 0, 110, 16), FALSE, D3DCOLOR_ARGB(255, 210, 195, 180)));
		}
		pComboBox->SetChangeEvent(UI::Event::Build(std::bind(&CMixGuildWindow::OnChangeMixSelect, this, std::placeholders::_1)));
		pWindow1->AddElement(pComboBox);
	}

	pWindow1->Hide();
}

void CMixGuildWindow::OnResolutionChanged()
{
	pWindow1->SetPosition((RESOLUTION_WIDTH >> 1) - (pWindow1->GetWidth() >> 1), (RESOLUTION_HEIGHT >> 1) - (pWindow1->GetHeight() >> 1));
}

void CMixGuildWindow::OnMixLoad(int MixID)
{
    UI::Window_ptr pWindowItem = pWindow1->GetElement<UI::Window>(WINDOWID_MixData);

    if (pWindowItem)
    {
        pWindowItem->Clear(); // limpa datos 

        if (MixID == 1) // WEAPONS
        {
            int startX = 210;
            int horizontalSpacing = 45;

            { // MIX 1 - Mix Divino (2 Transparo, 3 Murky, 4 Devine)
                int mixStartY = 65;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Divino");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Transparo (itos106)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos106.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Murky (itos107)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Devine (itos108)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("ATQ m\355n(+7) ATQ m\341x(+8) AR(+35) Cr\355t(+2) MP(+10)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            { // MIX 2 - Mix Celesto (2 Murky, 3 Devine, 5 Celesto)
                int mixStartY = 65 + 32;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Celesto");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 5x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("5x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("ATQ m\355n(+8) ATQ m\341x(+9) AR(+40) Cr\355t(+3) MP(+15)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            { // MIX 3 - Mix Mirage (1 Murky, 2 Devine, 4 Celesto, 5 Mirage)
                int mixStartY = 65 + 64;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Espejismo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 5x Mirage (itos110)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("5x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("ATQ m\355n(+9) ATQ m\341x(+11) AR(+45) Cr\355t(+3) MP(+20)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            { // MIX 4 - Mix Inferna (2 Celesto, 4 Mirage, 6 Inferna)
                int mixStartY = 65 + 96;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Inferna");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 4x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("4x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 6x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("6x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("ATQ m\355n(+13) ATQ m\341x(+15) AR(+50) Cr\355t(+4) MP(+25)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            { // MIX 5 - Mix Enigma (1 Celesto, 2 Mirage, 3 Inferna, 6 Enigma)
                int mixStartY = 65 + 128;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Enigma");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 3x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("3x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 6x Enigma (itos112)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("6x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("ATQ m\355n(+15) ATQ m\341x(+19) AR(+55) Cr\355t(+4) MP(+30)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            { // MIX 6 - Mix Bellum (4 Enigma, 8 Bellum)
                int mixStartY = 65 + 160;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Bellum");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 4x Enigma (itos112)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("4x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 8x Bellum (itos113)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("8x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("ATQ m\355n(+17) ATQ m\341x(+21) AR(+55) Cr\355t(+4) MP(+30)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            { // MIX 7 - Mix Oredo (3 Bellum, 9 Oredo)
                int mixStartY = 65 + 192;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Oredo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 3x Bellum (itos113)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("3x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 9x Oredo (itos114)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("9x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos114.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("ATQ m\355n(+18) ATQ m\341x(+23) AR(+55) Cr\355t(+4) MP(+30)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }
        }

        else if (MixID == 2) // ARMADURAS E ROBES
        {
            int startX = 210;
            int horizontalSpacing = 45;

            // ====================================================================
            // MIX 1 - Mix Divino
            // ====================================================================
            {
                int mixStartY = 65;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Divino");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Transparo (itos106)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos106.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Murky (itos107)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Devine (itos108)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+80) Abs(+2.0) HP(+10)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 2 - Mix Celesto
            // ====================================================================
            {
                int mixStartY = 65 + 32;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Celesto");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 5x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("5x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+120) Abs(+3.0) HP(+15)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 3 - Mix Mirage
            // ====================================================================
            {
                int mixStartY = 65 + 64;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Espejismo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 5x Mirage (itos110)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("5x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+160) Abs(+4.0) HP(+20)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 4 - Mix Inferna
            // ====================================================================
            {
                int mixStartY = 65 + 96;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Inferna");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 4x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("4x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 6x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("6x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+200) Abs(+5.0) HP(+25)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 5 - Mix Enigma
            // ====================================================================
            {
                int mixStartY = 65 + 128;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Enigma");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 3x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("3x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 6x Enigma (itos112)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("6x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+240) Abs(+6.0) HP(+30)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 6 - Mix Bellum
            // ====================================================================
            {
                int mixStartY = 65 + 160;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Bellum");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 4x Enigma (itos112)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("4x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 8x Bellum (itos113)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("8x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+280) Abs(+7.0) HP(+35)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 7 - Mix Oredo
            // ====================================================================
            {
                int mixStartY = 65 + 192;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Oredo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 3x Bellum (itos113)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("3x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 9x Oredo (itos114)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("9x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos114.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+320) Abs(+8.0) HP(+40)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }
        }

        else if (MixID == 3) // ESCUDOS
        {
            int startX = 210;
            int horizontalSpacing = 45;

            // ====================================================================
            // MIX 1 - Mix Divino
            // ====================================================================
            {
                int mixStartY = 65;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Divino");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Transparo (itos106)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos106.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Murky (itos107)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Devine (itos108)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Abs(+1.5) Bloqueo(+2%) HP(+10)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 2 - Mix Celesto
            // ====================================================================
            {
                int mixStartY = 65 + 32;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Celesto");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 5x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("5x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Abs(+2.0) Bloqueo(+3%) HP(+20)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 3 - Mix Mirage
            // ====================================================================
            {
                int mixStartY = 65 + 64;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Espejismo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 5x Mirage (itos110)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("5x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Abs(+2.5) Bloqueo(+4%) HP(+30)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 4 - Mix Inferna
            // ====================================================================
            {
                int mixStartY = 65 + 96;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Inferna");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 4x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("4x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 6x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("6x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Abs(+3.0) Bloqueo(+5%) HP(+50)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 5 - Mix Enigma
            // ====================================================================
            {
                int mixStartY = 65 + 128;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Enigma");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 3x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("3x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 6x Enigma (itos112)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("6x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Abs(+3.5) Bloqueo(+6%) HP(+70)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 6 - Mix Bellum
            // ====================================================================
            {
                int mixStartY = 65 + 160;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Bellum");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 4x Enigma (itos112)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("4x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 8x Bellum (itos113)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("8x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Abs(+4.0) Bloqueo(+6%) HP(+90)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 7 - Mix Oredo
            // ====================================================================
            {
                int mixStartY = 65 + 192;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Oredo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 3x Bellum (itos113)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("3x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 9x Oredo (itos114)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("9x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos114.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Abs(+4.5) Bloqueo(+6%) HP(+110)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }
        }

        else if (MixID == 4) // ORBS
        {
            int startX = 210;
            int horizontalSpacing = 45;

            // ====================================================================
            // MIX 1 - Mix Divino
            // ====================================================================
            {
                int mixStartY = 65;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Divino");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Transparo (itos106)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos106.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Murky (itos107)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Devine (itos108)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+20) Abs(+1.4) HP(+15) SP(+45)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 2 - Mix Celesto
            // ====================================================================
            {
                int mixStartY = 65 + 32;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Celesto");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 5x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("5x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+55) Abs(+2.0) HP(+20) SP(+60)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 3 - Mix Mirage
            // ====================================================================
            {
                int mixStartY = 65 + 64;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Espejismo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 5x Mirage (itos110)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("5x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+90) Abs(+2.7) HP(+25) SP(+75)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 4 - Mix Inferna
            // ====================================================================
            {
                int mixStartY = 65 + 96;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Inferna");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 4x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("4x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 6x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("6x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+125) Abs(+3.5) HP(+30) SP(+90)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 5 - Mix Enigma
            // ====================================================================
            {
                int mixStartY = 65 + 128;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Enigma");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 3x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("3x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 6x Enigma (itos112)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("6x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+160) Abs(+4.3) HP(+35) SP(+105)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 6 - Mix Bellum
            // ====================================================================
            {
                int mixStartY = 65 + 160;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Bellum");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 4x Enigma (itos112)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("4x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 8x Bellum (itos113)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("8x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+195) Abs(+5.1) HP(+40) SP(+120)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 7 - Mix Oredo
            // ====================================================================
            {
                int mixStartY = 65 + 192;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Oredo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 3x Bellum (itos113)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("3x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 9x Oredo (itos114)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("9x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos114.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+230) Abs(+5.9) HP(+45) SP(+135)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }
        }

        else if (MixID == 5) // BRACELETS
        {
            int startX = 210;
            int horizontalSpacing = 45;

            // ====================================================================
            // MIX 1 - Mix Divino
            // ====================================================================
            {
                int mixStartY = 65;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Divino");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Transparo (itos106)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos106.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Murky (itos107)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Devine (itos108)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+15) AR(+30) HP(+5) MP(+10) SP(+15)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 2 - Mix Celesto
            // ====================================================================
            {
                int mixStartY = 65 + 32;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Celesto");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 5x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("5x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+25) AR(+40) HP(+10) MP(+15) SP(+20)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 3 - Mix Mirage
            // ====================================================================
            {
                int mixStartY = 65 + 64;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Espejismo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 5x Mirage (itos110)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("5x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+35) AR(+50) HP(+15) MP(+20) SP(+25)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 4 - Mix Inferna
            // ====================================================================
            {
                int mixStartY = 65 + 96;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Inferna");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 4x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("4x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 6x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("6x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+45) AR(+60) HP(+20) MP(+25) SP(+30)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 5 - Mix Enigma
            // ====================================================================
            {
                int mixStartY = 65 + 128;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Enigma");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 3x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("3x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 6x Enigma (itos112)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("6x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+55) AR(+70) HP(+25) MP(+30) SP(+35)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 6 - Mix Bellum
            // ====================================================================
            {
                int mixStartY = 65 + 160;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Bellum");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 4x Enigma (itos112)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("4x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 8x Bellum (itos113)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("8x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+65) AR(+80) HP(+30) MP(+35) SP(+40)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 7 - Mix Oredo
            // ====================================================================
            {
                int mixStartY = 65 + 192;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Oredo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 3x Bellum (itos113)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("3x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 9x Oredo (itos114)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("9x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos114.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+75) AR(+90) HP(+35) MP(+40) SP(+45)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }
        }

        else if (MixID == 6) // LUVAS/GAUNTLETS
        {
            int startX = 210;
            int horizontalSpacing = 45;

            // ====================================================================
            // MIX 1 - Mix Divino
            // ====================================================================
            {
                int mixStartY = 65;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Divino");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Transparo (itos106)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos106.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Murky (itos107)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Devine (itos108)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+10) Abs(+1.0) HP(+5) MP(+10) SP(+15)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 2 - Mix Celesto
            // ====================================================================
            {
                int mixStartY = 65 + 32;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Celesto");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 5x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("5x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+30) Abs(+2.0) HP(+10) MP(+15) SP(+20)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 3 - Mix Mirage
            // ====================================================================
            {
                int mixStartY = 65 + 64;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Espejismo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 5x Mirage (itos110)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("5x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+50) Abs(+3.0) HP(+15) MP(+20) SP(+25)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 4 - Mix Inferna
            // ====================================================================
            {
                int mixStartY = 65 + 96;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Inferna");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 4x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("4x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 6x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("6x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+70) Abs(+4.0) HP(+20) MP(+25) SP(+30)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 5 - Mix Enigma
            // ====================================================================
            {
                int mixStartY = 65 + 128;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Enigma");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 3x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("3x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 6x Enigma (itos112)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("6x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+90) Abs(+5.0) HP(+25) MP(+30) SP(+35)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 6 - Mix Bellum
            // ====================================================================
            {
                int mixStartY = 65 + 160;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Bellum");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 4x Enigma (itos112)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("4x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 8x Bellum (itos113)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("8x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+110) Abs(+6.0) HP(+30) MP(+35) SP(+40)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 7 - Mix Oredo
            // ====================================================================
            {
                int mixStartY = 65 + 192;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Oredo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 3x Bellum (itos113)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("3x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 9x Oredo (itos114)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("9x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos114.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Def(+130) Abs(+7.0) HP(+35) MP(+40) SP(+45)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }
        }

        else if (MixID == 7) // BOTAS
        {
            int startX = 210;
            int horizontalSpacing = 45;

            // ====================================================================
            // MIX 1 - Mix Divino
            // ====================================================================
            {
                int mixStartY = 65;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Divino");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Transparo (itos106)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos106.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Murky (itos107)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Devine (itos108)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Def(+10) Abs(+1.2) Mov.(+0.9) HP(+5) MP(+10) SP(+15)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 2 - Mix Celesto
            // ====================================================================
            {
                int mixStartY = 65 + 32;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Celesto");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 5x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("5x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Def(+15) Abs(+1.8) Mov.(+1.8) HP(+10) MP(+15) SP(+20)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 3 - Mix Mirage
            // ====================================================================
            {
                int mixStartY = 65 + 64;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Espejismo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 5x Mirage (itos110)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("5x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Def(+20) Abs(+2.4) Mov.(+2.7) HP(+15) MP(+20) SP(+25)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 4 - Mix Inferna
            // ====================================================================
            {
                int mixStartY = 65 + 96;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Inferna");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 4x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("4x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 6x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("6x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Def(+25) Abs(+3.0) Mov.(+3.6) HP(+20) MP(+25) SP(+30)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 5 - Mix Enigma
            // ====================================================================
            {
                int mixStartY = 65 + 128;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Enigma");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 3x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("3x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 6x Enigma (itos112)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("6x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Def(+30) Abs(+3.6) Mov.(+4.6) HP(+25) MP(+30) SP(+35)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 6 - Mix Bellum
            // ====================================================================
            {
                int mixStartY = 65 + 160;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Bellum");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 4x Enigma (itos112)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("4x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 8x Bellum (itos113)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("8x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Def(+35) Abs(+4.2) Mov.(+5.6) HP(+30) MP(+35) SP(+40)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 7 - Mix Oredo
            // ====================================================================
            {
                int mixStartY = 65 + 192;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Oredo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 3x Bellum (itos113)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("3x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 9x Oredo (itos114)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("9x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos114.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Def(+40) Abs(+4.8) Mov.(+6.6) HP(+35) MP(+40) SP(+45)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }
        }

        else if (MixID == 8) // AMULETOS
        {
            int startX = 210;
            int horizontalSpacing = 45;

            // ====================================================================
            // MIX 1 - Mix Divino
            // ====================================================================
            {
                int mixStartY = 65;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Divino");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Transparo (itos106)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos106.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Murky (itos107)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Devine (itos108)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+0.4) Reg. MP(+0.8) HP(+4) MP(+8) SP(+12)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 2 - Mix Celesto
            // ====================================================================
            {
                int mixStartY = 65 + 32;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Celesto");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 5x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("5x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+0.6) Reg. MP(+1.0) HP(+6) MP(+10) SP(+14)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 3 - Mix Mirage
            // ====================================================================
            {
                int mixStartY = 65 + 64;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Espejismo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 5x Mirage (itos110)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("5x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+1.2) Reg. MP(+1.6) HP(+12) MP(+16) SP(+20)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 4 - Mix Inferna
            // ====================================================================
            {
                int mixStartY = 65 + 96;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Inferna");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 4x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("4x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 6x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("6x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+1.5) Reg. MP(+2.0) HP(+18) MP(+20) SP(+25)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 5 - Mix Enigma
            // ====================================================================
            {
                int mixStartY = 65 + 128;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Enigma");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 3x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("3x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 6x Enigma (itos112)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("6x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+1.8) Reg. MP(+2.2) HP(+20) MP(+22) SP(+30)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 6 - Mix Bellum
            // ====================================================================
            {
                int mixStartY = 65 + 160;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Bellum");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 4x Enigma (itos112)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("4x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 8x Bellum (itos113)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("8x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+2.0) Reg. MP(+2.4) HP(+22) MP(+24) SP(+32)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 7 - Mix Oredo
            // ====================================================================
            {
                int mixStartY = 65 + 192;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Oredo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 3x Bellum (itos113)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("3x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 9x Oredo (itos114)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("9x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos114.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+2.2) Reg. MP(+2.6) HP(+24) MP(+26) SP(+40)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }


        }

        else if (MixID == 9) // ANÉIS
        {
            int startX = 210;
            int horizontalSpacing = 45;

            // ====================================================================
            // MIX 1 - Mix Divino
            // ====================================================================
            {
                int mixStartY = 65;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Divino");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Transparo (itos106)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos106.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Murky (itos107)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Devine (itos108)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Reg. HP(+0.4) HP(+2) MP(+6)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 2 - Mix Celesto
            // ====================================================================
            {
                int mixStartY = 65 + 32;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Celesto");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 3x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("3x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 5x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("5x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 320, 14));
                pItemDesc->SetText("Reg. HP(+0.8) HP(+6) MP(+10)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 3 - Mix Mirage
            // ====================================================================
            {
                int mixStartY = 65 + 64;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Espejismo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Murky (itos107)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos107.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Devine (itos108)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos108.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 4x Celesto (itos109)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("4x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 5x Mirage (itos110)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("5x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+1.2) HP(+12) MP(+16) Def(+10) Abs(+0.5)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 4 - Mix Inferna
            // ====================================================================
            {
                int mixStartY = 65 + 96;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Inferna");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 2x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("2x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 4x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("4x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 6x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("6x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                //DESC MIX CORRIGIDA
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+1.6) HP(+16) MP(+20) Def(+20) Abs(+0.8) AR(+15)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 5 - Mix Enigma
            // SQL: 1 Celesto, 2 Mirage, 3 Inferna, 6 Enigma
            // Atributos: Regen(+1.8) HP(+18) MP(+22) Abs(+25) Def(+1) AR(+20)
            // ====================================================================
            {
                int mixStartY = 65 + 128;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Enigma");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 1x Celesto (itos109)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos109.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 2x Mirage (itos110)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos110.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - 3x Inferna (itos111)
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mixStartY, 20, 14));
                pItemSheltom3->SetText("3x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mixStartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos111.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - 6x Enigma (itos112)
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mixStartY, 20, 14));
                pItemSheltom4->SetText("6x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mixStartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+1.8) HP(+18) MP(+22) Def(+25) Abs(+1.0) AR(+20)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 6 - Mix Bellum
            // SQL: 4 Enigma, 8 Bellum
            // Atributos: Regen(+2) HP(+20) MP(+24) Abs(+25) Def(+1) AR(+20)
            // ====================================================================
            {
                int mixStartY = 65 + 160;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Bellum");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 4x Enigma (itos112)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("4x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos112.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 8x Bellum (itos113)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("8x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+2.0) HP(+20) MP(+24) Def(+25) Abs(+1.0) AR(+20)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            // ====================================================================
            // MIX 7 - Mix Oredo
            // SQL: 3 Bellum, 9 Oredo
            // Atributos: Regen(+2.2) HP(+22) MP(+26) Abs(+25) Def(+1) AR(+20)
            // ====================================================================
            {
                int mixStartY = 65 + 192;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mixStartY, 240, 14));
                pItemMixName->SetText("Mezcla Oredo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // Sheltom 1 - 3x Bellum (itos113)
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mixStartY, 20, 14));
                pItemSheltom1->SetText("3x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mixStartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos113.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - 9x Oredo (itos114)
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mixStartY, 20, 14));
                pItemSheltom2->SetText("9x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mixStartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itos114.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                //DESC MIX
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mixStartY, 360, 14));
                pItemDesc->SetText("Reg. HP(+2.2) HP(+22) MP(+26) Def(+25) Abs(+1.0) AR(+20)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }
        }

        else if (MixID == 10) // SHELTOMS
        {
            { // MIX 1 - Con 6 sheltoms en horizontal
                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, 65, 240, 14));
                pItemMixName->SetText("Mezcla Cr\355tico Transparo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // QNT SHELTONS y IMAGENES para Mix 1 - DISPOSICIÓN HORIZONTAL
                int startY = 65;
                int startX = 210;
                int horizontalSpacing = 45;

                // Sheltom 1 - itfo103
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, startY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, startY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo103.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - itfo104
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, startY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, startY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo104.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - itfo105
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, startY, 20, 14));
                pItemSheltom3->SetText("1x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, startY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo105.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - itfo106
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, startY, 20, 14));
                pItemSheltom4->SetText("1x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, startY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo106.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, startY, 240, 14));
                pItemDesc->SetText("ATQ m\355n(+3) ATQ m\341x(+4) Cr\355t(+1)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            { // MIX 2 - Con 6 sheltoms en horizontal
                int mix2StartY = 65 + 40;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mix2StartY, 240, 14));
                pItemMixName->SetText("Mezcla Cr\355tico Transparo");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // QNT SHELTONS y IMAGENES para Mix 2
                int startX = 210;
                int horizontalSpacing = 45;

                // Sheltom 1 - itfo103
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mix2StartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mix2StartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo103.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - itfo104
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mix2StartY, 20, 14));
                pItemSheltom2->SetText("1x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mix2StartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo104.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - itfo105
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mix2StartY, 20, 14));
                pItemSheltom3->SetText("1x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mix2StartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo105.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - itfo106
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mix2StartY, 20, 14));
                pItemSheltom4->SetText("1x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mix2StartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo106.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mix2StartY, 240, 14));
                pItemDesc->SetText("ATQ m\355n(+3) ATQ m\341x(+4) Cr\355t(+1)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            { // MIX 3 - Con 4 sheltoms (itfo104, itfo105, itfo106, itfo107)
                int mix3StartY = 65 + 80;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mix3StartY, 240, 14));
                pItemMixName->SetText("Mezcla Especial 3");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // QNT SHELTONS y IMAGENES para Mix 3
                int startX = 210;
                int horizontalSpacing = 45;

                // Sheltom 1 - itfo104
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mix3StartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mix3StartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo104.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - itfo105
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mix3StartY, 20, 14));
                pItemSheltom2->SetText("2x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mix3StartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo105.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - itfo106
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mix3StartY, 20, 14));
                pItemSheltom3->SetText("1x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mix3StartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo106.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - itfo107
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mix3StartY, 20, 14));
                pItemSheltom4->SetText("1x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mix3StartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo107.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mix3StartY, 240, 14));
                pItemDesc->SetText("Defensa(+5) HP(+50)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            { // MIX 4 - Con 4 sheltoms (itfo104, itfo105, itfo106, itfo107)
                int mix4StartY = 65 + 120;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mix4StartY, 240, 14));
                pItemMixName->SetText("Mezcla Especial 4");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // QNT SHELTONS y IMAGENES para Mix 4
                int startX = 210;
                int horizontalSpacing = 45;

                // Sheltom 1 - itfo104
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mix4StartY, 20, 14));
                pItemSheltom1->SetText("3x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mix4StartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo104.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - itfo105
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mix4StartY, 20, 14));
                pItemSheltom2->SetText("1x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mix4StartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo105.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - itfo106
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mix4StartY, 20, 14));
                pItemSheltom3->SetText("2x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mix4StartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo106.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - itfo107
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mix4StartY, 20, 14));
                pItemSheltom4->SetText("1x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mix4StartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo107.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mix4StartY, 240, 14));
                pItemDesc->SetText("Velocidad(+2) Evasi\363n(+3)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }

            { // MIX 5 - Con 4 sheltoms (itfo104, itfo105, itfo106, itfo107)
                int mix5StartY = 65 + 160;

                // NAME MIX
                UI::Text_ptr pItemMixName = std::make_shared<UI::Text>(Rectangle2D(0, mix5StartY, 240, 14));
                pItemMixName->SetText("Mezcla Especial 5");
                pItemMixName->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemMixName);

                // QNT SHELTONS y IMAGENES para Mix 5
                int startX = 210;
                int horizontalSpacing = 45;

                // Sheltom 1 - itfo104
                UI::Text_ptr pItemSheltom1 = std::make_shared<UI::Text>(Rectangle2D(startX, mix5StartY, 20, 14));
                pItemSheltom1->SetText("1x");
                pItemSheltom1->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom1);

                UI::ImageBox_ptr pItemImageBox1 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + 15, mix5StartY, 22, 22));
                pItemImageBox1->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo104.bmp"));
                pWindowItem->AddElement(pItemImageBox1);

                // Sheltom 2 - itfo105
                UI::Text_ptr pItemSheltom2 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing, mix5StartY, 20, 14));
                pItemSheltom2->SetText("1x");
                pItemSheltom2->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom2);

                UI::ImageBox_ptr pItemImageBox2 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing + 15, mix5StartY, 22, 22));
                pItemImageBox2->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo105.bmp"));
                pWindowItem->AddElement(pItemImageBox2);

                // Sheltom 3 - itfo106
                UI::Text_ptr pItemSheltom3 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 2, mix5StartY, 20, 14));
                pItemSheltom3->SetText("1x");
                pItemSheltom3->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom3);

                UI::ImageBox_ptr pItemImageBox3 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 2 + 15, mix5StartY, 22, 22));
                pItemImageBox3->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo106.bmp"));
                pWindowItem->AddElement(pItemImageBox3);

                // Sheltom 4 - itfo107
                UI::Text_ptr pItemSheltom4 = std::make_shared<UI::Text>(Rectangle2D(startX + horizontalSpacing * 3, mix5StartY, 20, 14));
                pItemSheltom4->SetText("4x");
                pItemSheltom4->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemSheltom4);

                UI::ImageBox_ptr pItemImageBox4 = std::make_shared<UI::ImageBox>(Rectangle2D(startX + horizontalSpacing * 3 + 15, mix5StartY, 22, 22));
                pItemImageBox4->SetImage(UI::ImageLoader::LoadImage("image\\Sinimage\\Items\\Accessory\\itfo107.bmp"));
                pWindowItem->AddElement(pItemImageBox4);

                //DESC MIX
                UI::Text_ptr pItemDesc = std::make_shared<UI::Text>(Rectangle2D(410, mix5StartY, 240, 14));
                pItemDesc->SetText("Da\361o Cr\355tico(+5%)");
                pItemDesc->SetFont("Arial", 16, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 236, 236, 236));
                pWindowItem->AddElement(pItemDesc);
            }
        }

        else
            pWindowItem->Clear();
    }

}

void CMixGuildWindow::OnChangeMixSelect(UIEventArgs e)
{
	UI::Window_ptr pWindowItem = pWindow1->GetElement<UI::Window>(WINDOWID_MixData);

	if (pWindowItem)
	{
		UI::ComboBox_ptr pComboBox = pWindow1->GetElement<UI::ComboBox>(COMBOBOX_DESC);//dados combobox

		if (pComboBox)
		{

			iSelectedMix = pComboBox->GetSelectedID(); // pega id do combobox selecionado

			switch (iSelectedMix)
			{
			default:
				break;
			case 1:
				OnMixLoad(iSelectedMix);
				break;
			case 2:
				OnMixLoad(iSelectedMix);
				break;
			case 3:
				OnMixLoad(iSelectedMix);
				break;
			case 4:
				OnMixLoad(iSelectedMix);
				break;
			case 5:
				OnMixLoad(iSelectedMix);
				break;
			case 6:
				OnMixLoad(iSelectedMix);
				break;
			case 7:
				OnMixLoad(iSelectedMix);
				break;
			case 8:
				OnMixLoad(iSelectedMix);
				break;
			case 9:
				OnMixLoad(iSelectedMix);
				break;
			case 10:
				OnMixLoad(iSelectedMix);
				break;
			}


		}
	}
}

void CMixGuildWindow::Open(int iNPC)
{
	if (!pWindow1->IsOpen())
	{		
		pWindow1->Show();

		MOUSEHANDLER->BlockMouse();
	}
}

void CMixGuildWindow::Close()
{
	if (pWindow1->IsOpen())
	{
		pWindow1->Hide();
		MOUSEHANDLER->UnblockMouse();
	}
	iSelectedMix = 0;
	/*if (pWindow2->IsOpen())
		OnReadMoreButtonClick(UIEventArgs{});*/

	HIDERIGHTNPCBOX;
}

void CMixGuildWindow::Init()
{
	BuildWindow1();
}

void CMixGuildWindow::Render()
{
	pWindow1->Render(0, 0, DX::Graphic::GetWidthBackBuffer(), DX::Graphic::GetHeightBackBuffer(), 0, 0);
}
