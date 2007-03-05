/////////////////////////////////////////////////////////////////////////////
// Name:        awx/button.h
// Purpose:
// Author:      Joachim Buermann
// Id:          $Id: button.h,v 1.3 2004/08/30 10:20:19 jb Exp $
// Copyright:   (c) 2003,2004 Joachim Buermann
// Licence:     wxWindows
/////////////////////////////////////////////////////////////////////////////

#ifndef __WX_MULTI_BUTTON__
#define __WX_MULTI_BUTTON__

#include <wx/dcmemory.h>
#include <wx/wx.h>

class wxBitmap;

class awxButton:public wxWindow {

DECLARE_DYNAMIC_CLASS (awxButton)

public:
    awxButton(wxWindow * parent, wxWindowID id,
		    const wxPoint & pos,
		    const wxSize & size,
		    char **upXPM, char **overXPM, char **downXPM, char **disXPM);
    awxButton() {};
    virtual ~ awxButton();

    virtual void Disable();
    virtual void Enable();
    virtual bool Enable(bool enable) {
	   if(enable) Enable();
	   else Disable();
	   return true;
    };
    virtual bool IsPressed() {return m_state == State_ButtonDown;};
    bool IsEnabled() {return m_enabled;};
    virtual void OnPaint(wxPaintEvent &event);
    virtual void OnEraseBackground(wxEraseEvent &event);
    virtual void OnMouseEvent(wxMouseEvent& event);
    virtual void OnSizeEvent(wxSizeEvent& event);
    virtual bool Press();
    virtual bool Release();
    virtual void SetText(const wxChar* text);
protected:
    enum ButtonState {
	   State_ButtonUp,
	   State_ButtonOver,
	   State_ButtonDown,
	   State_ButtonDis,
	   State_ButtonNew
    };

    enum BorderType {
	   Border_Sunken,
	   Border_Flat,
	   Border_High
    };

    int m_width;
    int m_height;
    int m_dx;
    int m_dy;

    bool m_enabled;

    ButtonState m_state;
    ButtonState m_laststate;
    wxBitmap* m_bitmap;

    wxString m_text;
    wxFont *m_font;
    wxIcon *m_icons[4];
    
    bool m_painted;
    bool m_theme;

    void DrawBorder(wxDC& dc, BorderType border);
    virtual void DrawOnBitmap();
    void Redraw();
public:
    void EnableTheme(bool enable) {
	   m_theme = enable;
    };
    DECLARE_EVENT_TABLE()
};

class awxCheckButton : public awxButton
{
protected:
    bool m_snapin;
public:
    awxCheckButton(wxWindow * parent, wxWindowID id,
			    const wxPoint & pos,
			    const wxSize & size,
			    char **upXPM,char **overXPM,char **downXPM,char **disXPM) :
	   awxButton(parent,id,pos,size,
			   upXPM,overXPM,downXPM,disXPM) {
	   m_snapin = false;
    };
    virtual void OnMouseEvent(wxMouseEvent& event);
    virtual bool Press();
    virtual bool Release();
    DECLARE_EVENT_TABLE()
};

class awxRadioButtonBox;

class awxRadioButton : public awxCheckButton
{
protected:
    awxRadioButtonBox* m_box;
public:
    awxRadioButton(wxWindow * parent, wxWindowID id,
			    const wxPoint & pos,
			    const wxSize & size,
			    char **upXPM,char **overXPM,char **downXPM,char **disXPM,
			    awxRadioButtonBox* selectBox = NULL);
    virtual void OnMouseEvent(wxMouseEvent& event);
    DECLARE_EVENT_TABLE()
};

class awxSeparator : public awxButton
{
 private:
    void DrawOnBitmap();
 public:
    awxSeparator(wxWindow * parent, wxWindowID id = -1,
			  const wxPoint & pos = wxDefaultPosition,
			  const wxSize & size = wxSize(8,32)) :
	   awxButton(parent,id,pos,size,
			   NULL,NULL,NULL,NULL) {};
    void OnEraseBackground(wxEraseEvent& event) {
	   DrawOnBitmap();
    };
public:
    DECLARE_EVENT_TABLE()
};

class awxRadioButtonBox : public wxWindow
{
protected:
    WX_DEFINE_ARRAY(awxRadioButton*,awxButtonArray);
    awxButtonArray m_array;
public:
    awxRadioButtonBox(wxWindow* parent,wxWindowID id) :
	   wxWindow(parent,id)
	   {Show(false);};
    void Add(awxRadioButton* button) {
	   m_array.Add(button);
    };
    void ReleaseAll() {
	   for(unsigned int i=0;i<m_array.GetCount();i++) {
		  m_array[i]->Release();
	   }
    };
    void SetValue(wxWindowID id) {
	   awxRadioButton* button = NULL;
	   for(unsigned int i=0;i<m_array.GetCount();i++) {
		  if(m_array[i]->GetId() == id) {
			 button = m_array[i];
			 break;
		  }
	   }
	   if(button) {
		  ReleaseAll();
		  button->Press();
	   }
    };
};

#endif
