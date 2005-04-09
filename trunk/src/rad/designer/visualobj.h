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
// Written by José Antonio Hurtado - joseantonio.hurtado@hispalinux.es
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __VISUAL_OBJS__
#define __VISUAL_OBJS__

#include "wx/wx.h"
#include "model/objectbase.h"
#include "rad/appobserver.h"

class VisualObject;
class VisualWindow;

typedef shared_ptr<VisualObject> PVisualObject;
typedef shared_ptr<VisualWindow> PVisualWindow;

/**
 * Objeto Visual.
 *
 * La vista preliminar (Designer), tiene un conjunto de objetos de esta clase.
 * Define una interfaz para abstraer los detalles de la creación o actualización
 * de cada componente visual.
 *
 * @todo Hay que evaluar la posibilidad de crear una clase del tipo
 *       VisualObjectPlugin, que pueda cargar una DLL para poder extender el
 *       conjunto de widgets.
 *       Los plugins podrían ser una pequeña interfaz en "C" (para facilitar
 *       la importación) para crear/actualizar/destruir el widget).
 */
class VisualObject
{
  
 private:
  PObjectBase m_object;
  
  VisualObject() {};
    
 public:
  /**
   * Método Fábrica.
   * Crea un objeto a partir del ObjectBase asociado.
   * Para crear los widgets es necesaria una referencia al padre (wxWindow*)
   */
  static PVisualObject CreateVisualObject(PObjectBase obj, wxWindow *wx_parent);

  VisualObject(PObjectBase obj);
  virtual ~VisualObject();
  
  PObjectBase GetObject() { return m_object; }
  
  /**
   * Añade el objeto visual (wxSizer* /wxWindow* /spacer) asociado,  al sizer que
   * se pasa como parámetro. Será redefinida según el objeto que sea.
   * obj -> Objeto de tipo T_SIZER_ITEM con las propiedades de layout
   */
  virtual void AddToSizer(wxSizer *sizer, PObjectBase sizeritem){};
  
  /**
   * Este método actualiza el objeto leyendo todas las propiedades, existen
   * objetos que no permiten cambiar las propiedades una vez construidos, en
   * este caso el método devolverá false, y se regenerará nuevamente la
   * vista del form.
   * @note en la práctica se ve que no tiene mucho sentido, ya que no supone
   *       mucho coste forzar la regeneración. Esta rutina está condenada a
   *       morir!!.
   */
//  virtual bool Update();
};  


class VisualSizer : public VisualObject
{
 private:
  wxSizer *m_sizer;
  
 public:
  VisualSizer(PObjectBase obj, wxWindow *parent);
  wxSizer *GetSizer() { return m_sizer; }
  void SetSizer(wxSizer *sizer) { m_sizer = sizer; }
  void AddToSizer(wxSizer *sizer, PObjectBase sizeritem);
};  

class VisualWindow : public VisualObject
{
 private:
  wxWindow *m_window;
  
 protected:
 public:
  VisualWindow(PObjectBase obj, wxWindow *parent);
  wxWindow *GetWindow() { return m_window; }
  void SetWindow(wxWindow *window) { m_window = window; }
  void AddToSizer(wxSizer *sizer, PObjectBase sizeritem);

  /**
   * Automáticamente carga la configuración wxWindow
   */
  void SetupWindow();
 
};

class VisualSpacer : public VisualObject
{
 private: 
 public:  
  VisualSpacer(PObjectBase obj, wxWindow *parent);
  void AddToSizer(wxSizer *sizer, PObjectBase sizeritem); 
};    

/**
 * VisualLayout es un objeto ficticio que representa al objeto T_SIZERITEM.
 *
 * Cuando se modifican las propiedades de layout de un objeto, el designer
 * captura el evento obteniendo el objeto asiciado. El método Update siempre
 * devuelve false, y por tanto se regenerará la vista por completo.
 */
class VisualLayout : public VisualObject
{
 public:
  VisualLayout(PObjectBase obj);

  // no hace nada, ya que es un objeto ficticio
  void AddToSizer(wxSizer *sizer, PObjectBase sizeritem) {}; 

  // fuerza la notificación de la aplicación ya que cambiará
  // la previsualización
  bool Update();
};

// Procesa los eventos asociados a un objeto
// En principio vamos a querer seleccionar el objeto
// al poner el foco
class VObjEvtHandler : public wxEvtHandler
{
 private:
   WPObjectBase m_object; 
   wxWindow *m_window;
   DataObservable *m_data;
   wxSizer *m_sizer;
//   wxPoint m_pos;

//   long m_mouseX, m_mouseY;
   VObjEvtHandler() {};

 protected:
  DECLARE_EVENT_TABLE()   
  
 public:
   VObjEvtHandler(wxWindow *win, wxSizer *sizer, PObjectBase obj, DataObservable *data);
   void OnLeftClick(wxMouseEvent &event);
//   void OnMouseMove(wxMouseEvent &event);
   void OnPaint(wxPaintEvent &event);
}; 


#ifdef __WXFB_EXPERIMENTAL__

class EditorHandler : public wxEvtHandler
{
 private:
  typedef enum { ST_IDLE, ST_MOVING } MouseState;
  static wxPoint s_pos;  
  static WPObjectBase s_object;
  static long s_mouseX, s_mouseY;
  static MouseState s_state;
  static wxWindow *s_editor;
  static wxPoint s_boundPos;
  static wxSize s_boundSize;
  DataObservable *m_data;
  
 protected:
  DECLARE_EVENT_TABLE()
 
 public: 
  EditorHandler(DataObservable *data);
  void SetWindow(wxWindow *win) {s_editor = win; }
  void SetObject(PObjectBase obj);
  void OnLeftClick(wxMouseEvent &event);
  void OnMouseMove(wxMouseEvent &event);
};

#endif // __WXFB_EXPERIMENTAL__

#endif //__VISUAL_OBJS__


