/*
*	STR MIX GUILD 2019
*	gabrielcarlos91@hotmail.com
*/
#pragma once
class CMixGuildWindow
{
protected:

	UI::Window_ptr											pWindow1 = NULL;

	enum
	{
		WINDOWID_MixData,

		LISTID_Main,
		LISTID_About,
		
		COMBOBOX_DESC,
	};
	int														iSelectedMix = 0;
private:

	void													BuildWindow1();

	void													OnChangeMixSelect(UIEventArgs e);
	void													OnCloseButtonClick(UIEventArgs e) { this->Close(); };
public:
	CMixGuildWindow();
	virtual ~CMixGuildWindow();


	void													OnMouseMove(class CMouse* pcMouse);
	BOOL													OnMouseClick(class CMouse* pcMouse);
	BOOL													OnMouseScroll(class CMouse* pcMouse);

	BOOL													OnKeyPress(class CKeyboard* pcKeyboard);
	BOOL													OnKeyChar(class CKeyboard* pcKeyboard);

	void													OnResolutionChanged();
	void													OnMixLoad(int MixID);
	void													Open(int iNPC);
	void													Close();

	void													Init();

	void													Render();
};

