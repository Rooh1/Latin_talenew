#pragma once
#include "stdafx.h"

class Alerta {
public:
    static Alerta* GetInstance();

    void Init();
    void Draw();
    // Mantemos o parâmetro do PlayerName que você pediu
    void ShowAlert(const char* szItemName, const char* szMonsterName, const char* szPlayerName);

private:
    Alerta();

    UI::ImageBox_ptr pImage;
    UI::Text_ptr pText;

    bool bActive; // Variável 'global' do seu código antigo

    // Variáveis da animação original
    int iTimer;   // Variável 'i' do seu código antigo
    int iOffsetY; // Variável 'j' do seu código antigo

    char szAlertText[256];
};

#define ALERTATELA Alerta::GetInstance()