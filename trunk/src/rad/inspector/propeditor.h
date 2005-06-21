///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 José Antonio Hurtado
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// Written by
//   José Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __PROP_EDITOR__
#define __PROP_EDITOR__

#include "rad/appobserver.h"
#include "model/objectbase.h"
#include "wx/wx.h"
#include "utils/typeconv.h"

////////////////////////////////////////////////////////////////////////////
// Errores detectados:  [ ] No corregidos     [X] Corregidos
//
//
// [ ] En wxPointEditor, Acceso no válido cuando el cursor está en la
//     coordenada "Y" y en ese momento se hace click en otro objeto.
// [ ] Cuando se modifica una propiedad y se pencha en otro objeto sin haber
//     cambiado el foco, no se notifica el evento.
////////////////////////////////////////////////////////////////////////////

/**
 * Editor de propiedad del Inspector de Objetos.
 *
 * Un editor no será más que un control gráfico que nos permitirá modificar
 * el valor de una propiedad.
 *
 * Aunque un editor no es una vista (ApplicationView) debe tener una referencia
 * al objeto de ApplicationDocument para poder modificar el valor.
 */
class PropertyEditor
{
 private:
  PProperty m_property;
  DataObservable *m_data;
   
 public:
  /**
   * Método Fábrica.
   */  
  static wxWindow* CreatePropertyEditor(DataObservable *data, PProperty prop,
                                        wxWindow *parent);  
    
  PropertyEditor(DataObservable *data, PProperty property)
  {
    assert(property);
    m_property = property;
    m_data = data;
  };
  virtual ~PropertyEditor() {};

  PProperty GetProperty() { return m_property; };
  DataObservable* GetData() {return m_data; };
  
  /**
   * Actualiza el control con el valor de la propiedad
   */
  virtual void RetrieveValue() = 0;  
  
  /**
   * Modifica el valor de la propiedad con el del editor, si el valor
   * no es válido no hace nada.
   */
  virtual void UpdateValue() = 0;

  
//  void UpdateValue();
};

class PointEditor : public PropertyEditor, public wxTextCtrl
{
 public:
   PointEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id);
   ~PointEditor();
   
   void RetrieveValue();   
   void UpdateValue();
};  

/**
 * Control para la edición de la propiedad "OPTION"
 */
class OptionEditor : public PropertyEditor, public wxComboBox
{
 protected:
   void ParseValue(const wxString &val);   
   
  public:
    OptionEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id);
    ~OptionEditor();
    void RetrieveValue();   
    void UpdateValue();
};

/**
 * Control para la edición de la propiedad "BITLIST"
 */
class BitlistEditor : public PropertyEditor, public wxListBox
{
 protected:
   void ParseValue(const wxString &val);   
   void ShowValue();

   // no se produce el event OnKillEvent bajo wxGTK
   DECLARE_EVENT_TABLE()
   
 public:
   BitlistEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id);
   ~BitlistEditor();
   
   void RetrieveValue();   
   void UpdateValue();

   void OnSelectItem(wxCommandEvent &event);
};

class TextEditor : public PropertyEditor, public wxTextCtrl
{
 public:
   TextEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id);
   ~TextEditor();
   
   void RetrieveValue();   
   void UpdateValue();
};

class BoolEditor : public PropertyEditor, public wxCheckBox
{
 public:
  BoolEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id);
  ~BoolEditor();

  
  void RetrieveValue();   
  void UpdateValue();
};    

class IntlistEditor : public PropertyEditor, public wxTextCtrl
{
 private:
   IntList m_list;
     
 public:
   IntlistEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id);
   ~IntlistEditor();
   
   void RetrieveValue();   
   void UpdateValue();
};

class FontEditor : public PropertyEditor, public wxPanel
{
 private: 
  wxTextCtrl *m_text;
  wxButton *m_button;
  DECLARE_EVENT_TABLE()
  
 public:
  FontEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id);
  ~FontEditor();
  
  void OnChooseFont(wxCommandEvent &event);
   
  void RetrieveValue();   
  void UpdateValue();
};

class ColourEditor : public PropertyEditor, public wxPanel
{
 private: 
  wxTextCtrl *m_text;

  wxButton *m_button;
  DECLARE_EVENT_TABLE()
  
 public:
  ColourEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id);
  ~ColourEditor();
  
  void OnChooseColour(wxCommandEvent &event);
   
  void RetrieveValue();   
  void UpdateValue();
};

class PathEditor : public PropertyEditor, public wxPanel
{
 private:
  wxTextCtrl *m_text;
  wxButton *m_button;
  DECLARE_EVENT_TABLE()

 public:
  PathEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id);
  ~PathEditor();
  
  void OnSelectPath(wxCommandEvent &event);
   
  void RetrieveValue();   
  void UpdateValue();
};

class BitmapEditor : public PropertyEditor, public wxPanel
{
 private:
  wxTextCtrl *m_text;
  wxButton *m_button;
  DECLARE_EVENT_TABLE()

 public:
  BitmapEditor(DataObservable *data, PProperty prop, wxWindow *parent, int id);
  ~BitmapEditor();
  
  void OnSelectBitmap(wxCommandEvent &event);
   
  void RetrieveValue();   
  void UpdateValue();
};

/**
 * Manejador de eventos para un editor.
 *
 * Simplifica las cosas, ya que así no tenemos que definir una tabla de eventos
 * por cada tipo de editor, basta con push'ear una instancia de este manejador
 * y listo.
 *
 * Para aquellos editores que sean agregados de varios widgets, vamos
 * a definir un wxEvtHandler especial, con el cual configuraremos dichos
 * controles y así no tener que derivar cada control en una clase nueva.
 */
class UpdateEventHandler : public wxEvtHandler
{
 private:
  PropertyEditor *m_propEditor;
  DECLARE_EVENT_TABLE()
       
 public:

  UpdateEventHandler(PropertyEditor *pe) { m_propEditor = pe; }  
  void OnKillFocus(wxFocusEvent &event);
};  

#endif //__PROP_EDITOR__

