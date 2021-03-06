///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 Jos� Antonio Hurtado
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
// Written by Jos� Antonio Hurtado - joseantonio.hurtado@hispalinux.es
//
///////////////////////////////////////////////////////////////////////////////

#include "visualeditor.h"

#include "visualeditor.h"
#include "visualobj.h"
#include "utils/typeconv.h"
#include "utils/debug.h"


#ifdef __WX24__
  #define wxFULL_REPAINT_ON_RESIZE 0
#endif

#ifdef __WXGTK__
  #define VISUAL_EDITOR_BORDER wxRAISED_BORDER
#else
  #define VISUAL_EDITOR_BORDER (wxFULL_REPAINT_ON_RESIZE | wxDOUBLE_BORDER)
#endif


BEGIN_EVENT_TABLE(VisualEditor,wxPanel)
  EVT_SASH_DRAGGED(-1, VisualEditor::OnResizeBackPanel)
  EVT_PAINT(VisualEditor::OnPaintPanel)
END_EVENT_TABLE()

VisualEditor::VisualEditor(wxWindow *parent)
  : wxPanel(parent,-1,wxDefaultPosition,wxDefaultSize,wxSIMPLE_BORDER)
{

// Parece ser que han modificado el comportamiento en wxMSW 2.5.x ya que al
// poner un color de background, este es aplicado a los hijos tambi�n.  
// SetBackgroundColour(wxColour(150,150,150));
  
  m_back = new GridPanel(this,-1,wxPoint(10,10),wxSize(350,200),VISUAL_EDITOR_BORDER);
  m_back->SetAutoLayout(true);
  m_back->SetSashVisible(wxSASH_BOTTOM,true);
  m_back->SetSashBorder(wxSASH_BOTTOM,true);
  m_back->SetSashVisible(wxSASH_RIGHT,true);
  m_back->SetSashBorder(wxSASH_RIGHT,true);
//  m_back->PushEventHandler(new EditorHandler(GetData()));
}  

void VisualEditor::Setup()
{
  #ifdef __WXFB_EXPERIMENTAL__
  EditorHandler *handler = new EditorHandler(GetData());
  handler->SetWindow(m_back);
  m_back->PushEventHandler(handler);
  #endif //__WXFB_EXPERIMENTAL__
  
}

void VisualEditor::OnPaintPanel (wxPaintEvent &event)
{
  // es necesario esto para que se pinte el panel de oscuro
  // con wxGTK.
  wxPaintDC dc(this);
  dc.SetBackground(wxBrush(wxColour(150,150,150),wxSOLID));
  dc.Clear();
}

void VisualEditor::OnResizeBackPanel (wxSashEvent &event)
{
  wxRect rect(event.GetDragRect());
  Debug::Print("VisualEditor::OnResizeBackPanel [%d,%d,%d,%d]",rect.x,rect.y,rect.width, rect.height);
  m_back->SetSize(rect.width,rect.height);
  m_back->Layout();  
  
  PObjectBase form (GetData()->GetSelectedForm());
  
  if (form)
  {
    PProperty prop(form->GetProperty("size"));
    if (prop)
    {
      wxString value(TypeConv::PointToString(wxPoint(rect.width,rect.height)));
      GetData()->ModifyProperty(prop, value);
    }
  }
}  

/**
 * Crea la vista preliminar borrando la previa.
 */
void VisualEditor::Create()
{
  bool need_fit = false;
  
  Debug::Print("[VisualEditor::Update] Generating preview...");
  PObjectBase root = GetData()->GetSelectedForm();
  m_form = root;

  #ifdef __WX24__
    Freeze(); // Freeze no funciona como en wxWidgets 2.4!
  #endif 

  
  m_back->DestroyChildren();
  m_back->SetSizer(NULL);  /* ! */
  
  //m_map.erase(m_map.begin(),m_map.end());
  
  if (root)
  { 
    // lo primero que hacemos es establecer el tama�o
    PProperty psize(root->GetProperty("size"));
    if (psize)
    {
      wxSize wsize(TypeConv::StringToSize(_WXSTR(psize->GetValue())));
      if (wsize.GetHeight() > 0 && wsize.GetWidth() > 0)
        m_back->SetSize(wsize);
      else
      {
        need_fit = true;
      }
    }
    else
    {
      m_back->SetSize(350,200);
    }
    
    for (unsigned int i=0; i < root->GetChildCount(); i++)
    {
      PObjectBase child = root->GetChild(i);
      Generate(child,m_back,NULL,true); 
    }
    
    if (need_fit)
      m_back->Fit();
  }
  else
  {
    m_back->SetSize(10,10);
  }
  
  m_back->Layout();

  #ifdef __WX24__
    Thaw(); // Freeze no funciona como en wxWidgets 2.4!
  #endif   
}  


/**
 * ALGORITMO PARA GENERAR LA VISTA PRELIMINAR
 * @param obj ObjectBase a generar.
 * @param parent wxWindow padre, necesario para instanciar un widget.
 * @param sizer sizer m�s pr�ximo, para poder incluir el objeto creado.
 * @param is_widget indica si el objeto padre es un widget o no. Si vamos
 *                  a crear un sizer y resulta que el padre es un widget
 *                  hemos de establecer este como su sizer.
 */
PVisualObject VisualEditor::Generate(PObjectBase obj, wxWindow *parent,
  wxSizer *sizer, bool is_widget)
{
  PVisualObject vobj = VisualObject::CreateVisualObject(obj,parent);
  
  if (!vobj)
    return vobj;
 
  //m_map.insert(VisualObjectMap::value_type(obj,vobj));

  ObjectType type = obj->GetObjectType();

  switch (type)
  {
    case T_WIDGET:
    {
      {
        PVisualWindow winobj(shared_dynamic_cast<VisualWindow>(vobj));
        wxWindow *window = winobj->GetWindow();
        window->PushEventHandler(new VObjEvtHandler(window,obj,GetData()));
        #ifdef __WXFB_EXPERIMENTAL__
        window->PushEventHandler(new EditorHandler(GetData()));
        #endif //__WXFB_EXPERIMENTAL__
      }
      
      wxWindow *new_parent =
        shared_dynamic_cast<VisualWindow>(vobj)->GetWindow();

      // generamos los hijos pasando el widget creado como nuevo padre.
      for (unsigned int i=0; i<obj->GetChildCount() ; i++)
        Generate(obj->GetChild(i),new_parent,NULL,true);
    }
    break;

    case T_SPACER:
      // nada que hacer
      break;
      
    case T_SIZER:
    {
      wxSizer *new_sizer =
        shared_dynamic_cast<VisualSizer>(vobj)->GetSizer();
         
      // generamos los hijos pasando el sizer creado.
      for (unsigned int i=0; i<obj->GetChildCount() ; i++)
        Generate(obj->GetChild(i),parent,new_sizer,false);
      
      if (is_widget)
      {
        // Si el nodo padre es un widget, entonces hay que asociarle el
        // sizer.
        Debug::Print("SetSizer");
        parent->SetSizer(new_sizer);
        //new_sizer->SetSizeHints(parent);
        parent->SetAutoLayout(true);
        //parent->Fit();
        parent->Layout();
      }  
    }    
    break;
      
    case T_SIZERITEM:
    {
      // un sizeritem s�lo podr� tener 1 hijo
      PVisualObject vchild = Generate(obj->GetChild(0), parent,NULL,false);
      assert(sizer);
      vchild->AddToSizer(sizer,obj);
      break;
    }  
    default:
      assert(false);
      break;
  }
  return vobj;
}  

BEGIN_EVENT_TABLE(GridPanel, wxSashWindow)
  EVT_PAINT(GridPanel::OnPaint)
//  EVT_MOTION(GridPanel::OnMouseMove)	
END_EVENT_TABLE()


GridPanel::GridPanel(wxWindow *parent, int id, const wxPoint& pos,

  const wxSize &size, long style, const wxString &name)
  : wxSashWindow(parent,id,pos,size,style,name)
{
  SetGrid(10,10);
  
}
void GridPanel::SetGrid(int x, int y)
{
  m_x = x;
  m_y = y;
}  
void GridPanel::OnPaint(wxPaintEvent &event)
{
  wxPaintDC dc(this);
  wxSize size = GetSize();
  dc.SetPen(*wxBLACK_PEN);
  for (int i=0;i<size.GetWidth();i += m_x)
    for (int j=0;j<size.GetHeight();j += m_y)
      dc.DrawPoint(i-1,j-1);
}   
/*
void GridPanel::OnMouseMove(wxMouseEvent &event)
{
  wxLogMessage(_("Moving.."));
  event.Skip();
}*/

//////////////////////////////////////////////////////////////////////////////

void VisualEditor::ProjectLoaded()
{
  Create();
}

void VisualEditor::ProjectRefresh()
{
  Create();
}

void VisualEditor::ProjectSaved()
{
}

void VisualEditor::ObjectSelected(PObjectBase obj)
{
  // s�lo es necesario regenerar la vista si el objeto
  // seleccionado pertenece a otro form
  
  if (GetData()->GetSelectedForm() != m_form)
    Create();
}

void VisualEditor::ObjectCreated(PObjectBase obj)
{
  Create();
}

void VisualEditor::ObjectRemoved(PObjectBase obj)
{
  Create();  
}

void VisualEditor::PropertyModified(PProperty prop)
{
  Create();
}




