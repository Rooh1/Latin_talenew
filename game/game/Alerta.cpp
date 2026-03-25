#include "stdafx.h"
#include "Alerta.h"

#ifndef RESOLUTION_WIDTH
#define RESOLUTION_WIDTH DX::Graphic::GetWidthBackBuffer()
#define RESOLUTION_HEIGHT DX::Graphic::GetHeightBackBuffer()
#endif

Alerta* Alerta::GetInstance() {
    static Alerta instance;
    return &instance;
}

Alerta::Alerta() {
    bActive = false;
    iTimer = 0;
    iOffsetY = 0;
    memset(szAlertText, 0, sizeof(szAlertText));
}

void Alerta::Init() {
    // Cria a imagem (Banner) - 600x43 (Igual ao original)
    pImage = std::make_shared<UI::ImageBox>(Rectangle2D(0, 0, 600, 43));
    pImage->SetImage(UI::ImageLoader::LoadImage("game\\images\\Global\\Global.png"));

    // Cria o texto
    pText = std::make_shared<UI::Text>(Rectangle2D(0, 0, 600, 20));
    pText->SetFont("Arial", 16, 0, FALSE, TRUE, -1);
    pText->SetHorizontalAlign(EAlign::ALIGN_Center); // Centralizado
}

void Alerta::ShowAlert(const char* szItemName, const char* szMonsterName, const char* szPlayerName) {
    // Formatea el texto como solicitaste: "Nishimura ha soltado (Item)!"
    wsprintf(szAlertText, "%s ha soltado (%s)!", szPlayerName, szItemName);

    if (pText) {
        pText->SetText(szAlertText);
        pText->SetColor(D3DCOLOR_ARGB(255, 255, 215, 0)); // Cor Dourada
    }

    // Reseta as variáveis de animação (Igual ao início do Draw original)
    bActive = true; // 'global = true'
    iTimer = 0;     // 'i = 0'
    iOffsetY = 0;   // 'j = 0'
}

void Alerta::Draw() {
    // Se não estiver ativo, não faz nada
    if (!bActive) return;

    // --- LÓGICA ORIGINAL DO SEU ARQUIVO ---

    // Fase de Descida (Aparecer)
    if (iOffsetY < 45 && iTimer < 1800) {
        iOffsetY++; // j++
    }

    // Fase de Subida (Sumir) após o tempo
    if (iTimer >= 1800) {
        iOffsetY--; // j--
    }

    iTimer++; // i++

    // Verifica se acabou a animação
    if (iTimer > 2000) {
        bActive = false; // global = false
        iTimer = 0;
        iOffsetY = 0;
        return;
    }

    // --- RENDERIZAÇÃO ---

    // Posição X Centralizada: (LarguraTela / 2) - 300
    int iX = (RESOLUTION_WIDTH / 2) - 300;

    // Posição Y Original: j + 35
    int iY = iOffsetY + 35;

    // Desenha Imagem
    if (pImage) {
        pImage->SetPosition(iX, iY);
        pImage->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
    }

    // Desenha Texto (Centralizado na imagem)
    // O texto original ficava em j + 47 (12 pixels abaixo da imagem)
    if (pText) {
        pText->SetBox(Rectangle2D(iX, iY + 12, 600, 20));
        pText->Render(0, 0, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
    }
}
