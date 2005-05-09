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
// Añadir IsShown() al hacer Freeze y Thaw en Create
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#include "visualeditor.h"

#include "visualeditor.h"
#include "visualobj.h"
#include "utils/typeconv.h"
#include "utils/debug.h"
#include "menubar.h"
#include "wx/statline.h"

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
  : wxPanel(parent,-1,wxDefaultPosition,wxDefaultSize,wxSUNKEN_BORDER)
{

// Parece ser que han modificado el comportamiento en wxMSW 2.5.x ya que al
// poner un color de background, este es aplicado a los hijos también.  
// SetBackgroundColour(wxColour(150,150,150));
  
  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
  
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
  PObjectBase menubar;
  
  Debug::Print("[VisualEditor::Update] Generating preview...");
  PObjectBase root = GetData()->GetSelectedForm();
  m_form = root;

  //#ifdef __WX24__
    if (IsShown()) Freeze(); // Freeze no funciona como en wxWidgets 2.4!
  //#endif 

  m_back->SetSelectedItem(NULL);
  m_back->SetSelectedSizer(NULL);
  m_back->SetSelectedObject(PObjectBase());
  
  m_back->DestroyChildren();
  m_back->SetSizer(NULL);  /* ! */
  
  m_map.erase(m_map.begin(),m_map.end());
  
  if (root)
  { 
    // lo primero que hacemos es establecer el tamaño
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
      if (child->GetObjectType() == T_MENUBAR)
        menubar = child;
      else
        Generate(child,m_back,NULL,T_CONTAINER); 
    }
    
    if (need_fit)
      m_back->Fit();
  }
  else
  {
    m_back->SetSize(10,10);
  }
  
  /*wxSizer *mainSizer = m_back->GetSizer();
  
  if (mainSizer)
  {
      Menubar *dummy = new Menubar(m_back, -1);
      
      wxMenu *menu = new wxMenu;
      menu->Append(wxNewId(), _T("Nuevo"));
      menu->Append(wxNewId(), _T("Abrir"));
      menu->Append(wxNewId(), _T("Guardar"));
      menu->Append(wxNewId(), _T("Salir"));
      dummy->AppendMenu(_T("File"), menu);
      
      menu = new wxMenu;
      menu->Append(wxNewId(), _T("Copiar"));
      menu->Append(wxNewId(), _T("Pegar"));
      menu->Append(wxNewId(), _T("Cortar"));
      menu->Append(wxNewId(), _T("Eliminar"));
      dummy->AppendMenu(_T("Edit"), menu);
      dummy->Fit();
      
      wxSizer *dummySizer = new wxBoxSizer(wxVERTICAL);
      dummySizer->Add(dummy, 0, wxEXPAND | wxTOP | wxBOTTOM, 3);
      dummySizer->Add(new wxStaticLine(m_back, -1), 0, wxEXPAND | wxALL, 0);
      dummySizer->Add(mainSizer, 1, wxEXPAND | wxALL, 0);
      m_back->SetSizer(dummySizer, false);
      
      m_back->Layout();
  }*/
  if (menubar) m_back->SetMenubar(menubar);

  //#ifdef __WX24__
    if (IsShown()) Thaw(); // Freeze no funciona como en wxWidgets 2.4!
  //#endif   
}  


/**
 * ALGORITMO PARA GENERAR LA VISTA PRELIMINAR
 * @param obj ObjectBase a generar.
 * @param parent wxWindow padre, necesario para instanciar un widget.
 * @param sizer sizer más próximo, para poder incluir el objeto creado.
 * @param is_widget indica si el objeto padre es un widget o no. Si vamos
 *                  a crear un sizer y resulta que el padre es un widget
 *                  hemos de establecer este como su sizer.
 */
PVisualObject VisualEditor::Generate(PObjectBase obj, wxWindow *parent,
  wxSizer *sizer, ObjectType parentType)
{
  PVisualObject vobj = VisualObject::CreateVisualObject(obj,parent);
  
  if (!vobj)
    return vobj;
 
  m_map.insert(VisualObjectMap::value_type(obj,vobj));

  ObjectType type = obj->GetObjectType();

  switch (type)
  {
    case T_NOTEBOOK:
    case T_CONTAINER:
    case T_WIDGET:
    {
      {
        PVisualWindow winobj(shared_dynamic_cast<VisualWindow>(vobj));
        wxWindow *window = winobj->GetWindow();
        
        if (type != T_NOTEBOOK)
          window->PushEventHandler(new VObjEvtHandler(window,obj,GetData()));
        #ifdef __WXFB_EXPERIMENTAL__
        window->PushEventHandler(new EditorHandler(GetData()));
        #endif //__WXFB_EXPERIMENTAL__
      }
      
      wxWindow *new_parent =
        shared_dynamic_cast<VisualWindow>(vobj)->GetWindow();

      // generamos los hijos pasando el widget creado como nuevo padre.
      for (unsigned int i=0; i<obj->GetChildCount() ; i++)
        Generate(obj->GetChild(i),new_parent,NULL,type);
        
    }
    break;


    case T_NOTEBOOK_PAGE:
    {
      if (obj->GetChildCount() > 0)
      {
        PVisualObject vchild = Generate(obj->GetChild(0), parent,sizer,type);
        wxWindow *page =
          shared_dynamic_cast<VisualWindow>(vchild)->GetWindow();
  
        // parent se supone wxNotebook
        assert(parent->IsKindOf(CLASSINFO(wxNotebook)));
        assert(page);
       
        ((wxNotebook *)parent)->AddPage(page,obj->GetPropertyAsString(_T("label")));
      }
    }  
    break;


    case T_SIZER:
    {
      wxSizer *new_sizer =
        shared_dynamic_cast<VisualSizer>(vobj)->GetSizer();
           
      // generamos los hijos pasando el sizer creado.
      for (unsigned int i=0; i<obj->GetChildCount() ; i++)
        Generate(obj->GetChild(i),parent,new_sizer,type);
      
      if (parentType == T_WIDGET || parentType == T_CONTAINER)
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
      // un sizeritem sólo podrá tener 1 hijo
      PVisualObject vchild = Generate(obj->GetChild(0), parent,sizer,type);
      assert(sizer);
      vchild->AddToSizer(sizer,obj);
    }  
    break;
    
    case T_SPACER:
      
      assert(sizer);
      vobj->AddToSizer(sizer,obj);
      break;
      
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

IMPLEMENT_CLASS(GridPanel, wxSashWindow)

GridPanel::GridPanel(wxWindow *parent, int id, const wxPoint& pos,

  const wxSize &size, long style, const wxString &name)
  : wxSashWindow(parent,id,pos,size,style,name)
{
  SetGrid(10,10);
  m_selSizer = NULL;
  m_selItem = NULL;
  m_actPanel = NULL;
  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
}

void GridPanel::SetGrid(int x, int y)
{
  m_x = x;
  m_y = y;
}

void GridPanel::DrawRectangle(wxDC& dc, const wxPoint& point, const wxSize& size, PObjectBase object)
{
  int border = object->GetParent()->GetPropertyAsInteger(_T("border"));
  if (border == 0) border = 1;
  int flag = object->GetParent()->GetPropertyAsInteger(_T("flag"));
  int topBorder = (flag & wxTOP) == 0 ? 1 : border;
  int bottomBorder = (flag & wxBOTTOM) == 0 ? 1 : border;
  int rightBorder = (flag & wxRIGHT) == 0 ? 1 : border;
  int leftBorder = (flag & wxLEFT) == 0 ? 1 : border;
  dc.DrawRectangle(point.x - leftBorder + 1, point.y - topBorder + 1, 
                    size.x + leftBorder + rightBorder - 2, 
                    size.y + topBorder + bottomBorder - 2);
  dc.DrawRectangle(point.x - leftBorder, point.y - topBorder, 
                    size.x + leftBorder + rightBorder, 
                    size.y + topBorder + bottomBorder);    
}  

void GridPanel::HighlightSelection(wxDC& dc)
{
  wxSize size;
  PObjectBase object = m_selObj.lock();
 
  if (m_selSizer)
  {
    wxPoint point = m_selSizer->GetPosition();
    size = m_selSizer->GetSize();
    wxPen bluePen(*wxBLUE, 1, wxSOLID);
    dc.SetPen(bluePen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    PObjectBase sizerParent = object->FindNearAncestor(T_SIZER);
    if (sizerParent && sizerParent->GetParent())
        DrawRectangle(dc, point, size, sizerParent);
  }
  if (m_selItem)
  {
    wxPoint point;

    // Tenemos un problema (de momento) con los wxClassInfo's de los
    // componentes que no forman parte de wxWidgets, debido a que el componente
    // se compila por separado en una librería compartida/dll 
    // y parece ser que la información de tipo de wxWidgets se configura
    // estáticamente.
    // Por tanto, no vamos a usar la información de tipos de wxWidgets.

    if (m_selItem->IsKindOf(CLASSINFO(wxWindow)))
    //if (object->GetObjectType() == T_WIDGET || object->GetObjectType() == T_CONTAINER)
    {
        point = ((wxWindow*)m_selItem)->GetPosition();
        size = ((wxWindow*)m_selItem)->GetSize();
    }
    else if (m_selItem->IsKindOf(CLASSINFO(wxSizer)))
    //else if (object->GetObjectType() == T_SIZER)
    {
        point = ((wxSizer*)m_selItem)->GetPosition();
        size = ((wxSizer*)m_selItem)->GetSize();
    }
    else
    {
        Debug::Print("Unknown class: %s", m_selItem->GetClassInfo()->GetClassName());
        return;
    }
        
    wxPen redPen(*wxRED, 1, wxSOLID);
    dc.SetPen(redPen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    DrawRectangle(dc, point, size, object);
  }
}

void GridPanel::SetMenubar(PObjectBase menubar)
{
  /* Falta soporte para submenús y separadores, pero es un comienzo */
  assert(menubar->GetObjectType() == T_MENUBAR);
  Menubar *mbWidget = new Menubar(this, -1);
  for (int i = 0; i < menubar->GetChildCount(); i++)
  {
    PObjectBase menu = menubar->GetChild(i);
    wxMenu *menuWidget = new wxMenu();
    for (int j = 0; j < menu->GetChildCount(); j++)
    {
      PObjectBase menuItem = menu->GetChild(j);
      wxString label = menuItem->GetPropertyAsString(_T("label"));
      label.Replace(_T("\\t"), _T("\t"));
      wxMenuItem *item = new wxMenuItem(menuWidget, 5000, label, menuItem->GetPropertyAsString(_T("help")));
      if (!menuItem->GetProperty("bitmap")->IsDefaultValue())
        item->SetBitmap(menuItem->GetPropertyAsBitmap("bitmap"));
      menuWidget->Append(item);
    }
    mbWidget->AppendMenu(menu->GetPropertyAsString(_T("label")), menuWidget);
  }
  wxSizer *mainSizer = GetSizer();
  wxSizer *dummySizer = new wxBoxSizer(wxVERTICAL);
  dummySizer->Add(mbWidget, 0, wxEXPAND | wxTOP | wxBOTTOM, 3);
  dummySizer->Add(new wxStaticLine(this, -1), 0, wxEXPAND | wxALL, 0);
  if (mainSizer) dummySizer->Add(mainSizer, 1, wxEXPAND | wxALL, 0);
  SetSizer(dummySizer, false);
  Layout();
}

void GridPanel::OnPaint(wxPaintEvent &event)
{
  wxPaintDC dc(this);
  wxSize size = GetSize();
  dc.SetPen(*wxBLACK_PEN);
  for (int i=0;i<size.GetWidth();i += m_x)
    for (int j=0;j<size.GetHeight();j += m_y)
      dc.DrawPoint(i-1,j-1);
      
  if (m_actPanel != this) return;
  HighlightSelection(dc);
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
  // sólo es necesario regenerar la vista si el objeto
  // seleccionado pertenece a otro form

  if (GetData()->GetSelectedForm() != m_form)
    Create();
    
  PVisualObject visualObj;
  PObjectBase objAuxCt, objAuxNb, objAux;
  VisualObjectMap::iterator it = m_map.find(obj);
  
  if (it != m_map.end())
  {
    wxWindow *selPanel = NULL;
    visualObj = it->second;
    //objAux = obj->FindNearAncestor(T_WIDGET);
    objAuxCt = obj->FindNearAncestor(T_CONTAINER);  
    objAuxNb = obj->FindNearAncestor(T_NOTEBOOK);
    
    if (!objAuxCt)
      objAux = objAuxNb;
    else if (!objAuxNb)
      objAux = objAuxCt;
    else
      objAux = objAuxNb->Deep() > objAuxCt->Deep() ? objAuxNb : objAuxCt;
    
    if (objAux)  // Un padre de tipo T_WIDGET es siempre un contenedor
    {
      it = m_map.find(objAux);
      selPanel = shared_dynamic_cast<VisualWindow>(it->second)->GetWindow();
    }
    else
      selPanel = m_back;
        
    wxObject *item = NULL;
    wxSizer *sizer = NULL;
    if (obj->GetObjectType() == T_WIDGET || obj->GetObjectType() == T_CONTAINER || obj->GetObjectType() == T_NOTEBOOK)
      item = shared_dynamic_cast<VisualWindow>(visualObj)->GetWindow();
    else if (obj->GetObjectType() == T_SIZER)
      item = shared_dynamic_cast<VisualSizer>(visualObj)->GetSizer();
    
    objAux = obj->FindNearAncestor(T_SIZER);
    objAuxCt = obj->FindNearAncestor(T_CONTAINER);
    if (objAux && (!objAuxCt || objAux->Deep() > objAuxCt->Deep()))
    {
      it = m_map.find(objAux);
      sizer = shared_dynamic_cast<VisualSizer>(it->second)->GetSizer(); 
    }
    
    m_back->SetSelectedSizer(sizer);
    m_back->SetSelectedItem(item);
    m_back->SetSelectedObject(obj);
    m_back->SetSelectedPanel(selPanel);
    m_back->Refresh();
  }
  else
  {
    m_back->SetSelectedSizer(NULL);
    m_back->SetSelectedItem(NULL);
    m_back->SetSelectedObject(PObjectBase());
    m_back->SetSelectedPanel(NULL);
    m_back->Refresh();
  }
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
  PObjectBase aux = m_back->GetSelectedObject();
  Create();
  ObjectSelected(aux);
}




