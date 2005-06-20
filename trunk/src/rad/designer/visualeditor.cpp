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
// A�adir IsShown() al hacer Freeze y Thaw en Create
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#include "visualeditor.h"

#include "visualeditor.h"
#include "visualobj.h"
#include "utils/typeconv.h"
#include "utils/debug.h"
#include "menubar.h"
#include "wx/statline.h"
#include "rad/designer/resizablepanel.h"

#ifdef __WX24__
  #define wxFULL_REPAINT_ON_RESIZE 0
#endif

#ifdef __WXGTK__
  #define VISUAL_EDITOR_BORDER wxRAISED_BORDER
#else
  #define VISUAL_EDITOR_BORDER (wxFULL_REPAINT_ON_RESIZE | wxDOUBLE_BORDER)
#endif

BEGIN_EVENT_TABLE(VisualEditor,wxPanel)
  //EVT_SASH_DRAGGED(-1, VisualEditor::OnResizeBackPanel)
  //EVT_COMMAND(-1, wxEVT_PANEL_RESIZED, VisualEditor::OnResizeBackPanel)
  EVT_PANEL_RESIZED(-1, VisualEditor::OnResizeBackPanel)
  EVT_PAINT(VisualEditor::OnPaintPanel)
END_EVENT_TABLE()

VisualEditor::VisualEditor(wxWindow *parent)
  : wxPanel(parent,-1,wxDefaultPosition,wxDefaultSize,wxSUNKEN_BORDER)
{

// Parece ser que han modificado el comportamiento en wxMSW 2.5.x ya que al
// poner un color de background, este es aplicado a los hijos tambi�n.  
// SetBackgroundColour(wxColour(150,150,150));
  
  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
  
  m_back = new GridPanel(this,-1,wxPoint(10,10),wxSize(350,200),VISUAL_EDITOR_BORDER);
  m_back->SetAutoLayout(true);
  /*m_back->SetSashVisible(wxSASH_BOTTOM,true);
  m_back->SetSashBorder(wxSASH_BOTTOM,true);
  m_back->SetSashVisible(wxSASH_RIGHT,true);
  m_back->SetSashBorder(wxSASH_RIGHT,true);*/
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
  //dc.SetBackground(wxBrush(wxColour(150,150,150),wxSOLID));
  dc.SetBackground(wxBrush(wxColour(192,192,192),wxSOLID));
  dc.Clear();
}

void VisualEditor::OnResizeBackPanel (wxCommandEvent &event) //(wxSashEvent &event)
{
  /*wxRect rect(event.GetDragRect());
  Debug::Print("VisualEditor::OnResizeBackPanel [%d,%d,%d,%d]",rect.x,rect.y,rect.width, rect.height);
  m_back->SetSize(rect.width,rect.height);
  m_back->Layout();*/  
  
  PObjectBase form (GetData()->GetSelectedForm());
  
  if (form)
  {
    PProperty prop(form->GetProperty("size"));
    if (prop)
    {
      wxString value(TypeConv::PointToString(wxPoint(m_back->GetSize().x, m_back->GetSize().y)));
      GetData()->ModifyProperty(prop, value);
    }
  }
  
  //event.Skip();
}  

/**
 * Crea la vista preliminar borrando la previa.
 */
void VisualEditor::Create()
{
  bool need_fit = false;
  PObjectBase menubar;
  wxWindow *statusbar = NULL;
  
  Debug::Print("[VisualEditor::Update] Generating preview...");
  PObjectBase root = GetData()->GetSelectedForm();
  m_form = root;

  if (IsShown()) Freeze();

  m_back->SetSelectedItem(NULL);
  m_back->SetSelectedSizer(NULL);
  m_back->SetSelectedObject(PObjectBase());
  
  m_back->DestroyChildren();
  m_back->SetSizer(NULL);  /* ! */
  
  m_map.erase(m_map.begin(),m_map.end());
  
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
        need_fit = true;
    }
    else
    {
      m_back->SetSize(350,200);
    }
    
    if (root->GetClassName() == "Frame")
      m_back->SetOwnBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));
    else
      m_back->SetOwnBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    
    for (unsigned int i=0; i < root->GetChildCount(); i++)
    {
      PObjectBase child = root->GetChild(i);
      if (child->GetObjectTypeName() == "menubar")
        menubar = child;
      else
        Generate(child,m_back,NULL,PVisualObject()); 
      
      if (child->GetClassName() == "wxStatusBar")
      {
        VisualObjectMap::iterator it = m_map.find(child);
        statusbar = shared_dynamic_cast<VisualWindow>(it->second)->GetWindow();
      }
    }
    
    if (need_fit)
      m_back->Fit();
    
    m_back->Layout();
      
    if (menubar || statusbar) m_back->SetFrameWidgets(menubar, statusbar);
    
  }
  else
  {
    m_back->SetSize(10,10);
    m_back->SetOwnBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
  }

  if (IsShown()) Thaw();
}  


/**
 * ALGORITMO PARA GENERAR LA VISTA PRELIMINAR
 *
 * @param obj ObjectBase a generar.
 * @param parent wxWindow padre, necesario para instanciar un widget.
 * @param sizer sizer m�s pr�ximo, para poder incluir el objeto creado.
 * @param is_widget indica si el objeto padre es un widget o no. Si vamos
 *                  a crear un sizer y resulta que el padre es un widget
 *                  hemos de establecer este como su sizer.
 */
PVisualObject VisualEditor::Generate(PObjectBase obj, wxWindow *wxparent,
  wxSizer *sizer, PVisualObject vparent)//ObjectType parentType)
{
  // en primer lugar creamos la instancia del objeto-wx que nos ocupa
  PVisualObject vobj(VisualObject::CreateVisualObject(obj,wxparent));
    
  if (!vobj)
    return vobj; // no se debe dar nunca
 
  IComponent *comp = obj->GetObjectInfo()->GetComponent();  
  assert(comp);
  
  // registramos el objeto para poder obtener la referencia a VisualObject a
  // partir de un ObjectBase
  m_map.insert(VisualObjectMap::value_type(obj,vobj));
  
  VisualObjectAdapter obj_view(vobj); // Adaptador IObjectView para obj
  
  // Si el objeto es un widget, le a�adimos el menejador de eventos para
  // poder seleccionarlo desde el designer y que se dibujen los recuadros...
  // FIXME: eliminar dependencias con ObjectType
  //        (quiz� con una funci�n en el plugin: bool IsContainer()
  //if (obj_view.Window() &&
  //    (obj->GetObjectTypeName() == "widget" || obj->GetObjectTypeName() == "container")
  //    || obj->GetObjectTypeName() == "statusbar")
  if (obj_view.Window())// && !comp->KeepEvtHandler())
  {
    obj_view.Window()->PushEventHandler(
      new VObjEvtHandler(obj_view.Window(),obj,GetData()));
  }

  // nuevo padre para las ventanas que se encuentren por debajo
  wxWindow *new_wxparent = (obj_view.Window() ? obj_view.Window() : wxparent);

  // Generamos recursivamente todos los hijos conservando la refenrencia 
  // del primero, ya que ser� pasado como par�metros en la funci�n del
  // plugin OnCreated.

  PVisualObject first_child;

  if (obj->GetChildCount()>0)
    first_child = Generate(obj->GetChild(0),new_wxparent,NULL,vobj);
    
  for (unsigned int i=1; i<obj->GetChildCount() ; i++)
    Generate(obj->GetChild(i),new_wxparent,NULL,vobj);


  // Procesamos el evento OnCreated
  VisualObjectAdapter parent_view(vparent);
  VisualObjectAdapter first_child_view(first_child);
  
  comp->OnCreated(&obj_view,new_wxparent,&parent_view, &first_child_view);
  
  // Por �ltimo, debemos asignar el sizer al widget, en los siguientes casos:
  // 1. El objeto creado sea un sizer y el objeto padre sea una ventana.
  // 2. No objeto padre (wxparent == m_back).
  
  if ((obj_view.Sizer() && parent_view.Window()) || (!vparent && obj_view.Sizer()))
  {
    wxparent->SetSizer(obj_view.Sizer());
    wxparent->SetAutoLayout(true);
    wxparent->Layout();
  }
    
  return vobj;
}  

BEGIN_EVENT_TABLE(GridPanel, ResizablePanel) //wxSashWindow)
  EVT_PAINT(GridPanel::OnPaint)
//  EVT_MOTION(GridPanel::OnMouseMove)	
END_EVENT_TABLE()

IMPLEMENT_CLASS(GridPanel, ResizablePanel) //wxSashWindow)

GridPanel::GridPanel(wxWindow *parent, int id, const wxPoint& pos,

  const wxSize &size, long style, const wxString &name)
  : ResizablePanel(parent, pos, size, style) //wxSashWindow(parent,id,pos,size,style,name)
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
    PObjectBase sizerParent = object->FindNearAncestor("sizer");
    if (sizerParent && sizerParent->GetParent())
        DrawRectangle(dc, point, size, sizerParent);
  }
  if (m_selItem)
  {
    wxPoint point;
    bool shown;

    // Tenemos un problema (de momento) con los wxClassInfo's de los
    // componentes que no forman parte de wxWidgets, debido a que el componente
    // se compila por separado en una librer�a compartida/dll 
    // y parece ser que la informaci�n de tipo de wxWidgets se configura
    // est�ticamente.
    // Por tanto, no vamos a usar la informaci�n de tipos de wxWidgets.

    if (m_selItem->IsKindOf(CLASSINFO(wxWindow)))
    {
        point = ((wxWindow*)m_selItem)->GetPosition();
        size = ((wxWindow*)m_selItem)->GetSize();
        shown = ((wxWindow*)m_selItem)->IsShown();
    }
    else if (m_selItem->IsKindOf(CLASSINFO(wxSizer)))
    {
        point = ((wxSizer*)m_selItem)->GetPosition();
        size = ((wxSizer*)m_selItem)->GetSize();
        shown = true;
    }
    else
    {
        Debug::Print("Unknown class: %s", m_selItem->GetClassInfo()->GetClassName());
        return;
    }
    
    if (shown)
    {
      wxPen redPen(*wxRED, 1, wxSOLID);
      dc.SetPen(redPen);
      dc.SetBrush(*wxTRANSPARENT_BRUSH);
      DrawRectangle(dc, point, size, object);
    }
  }
}

wxMenu* GridPanel::GetMenuFromObject(PObjectBase menu)
{
  int lastMenuId = wxID_HIGHEST + 1;
  wxMenu *menuWidget = new wxMenu();
  for (unsigned int j = 0; j < menu->GetChildCount(); j++)
  {
    PObjectBase menuItem = menu->GetChild(j);
    if (menuItem->GetObjectTypeName() == "submenu")
      menuWidget->Append(wxID_HIGHEST + 1, menuItem->GetPropertyAsString(_T("label")), GetMenuFromObject(menuItem));
    else if (menuItem->GetClassName() == "separator")
      menuWidget->AppendSeparator();
    else
    {
      wxString label = menuItem->GetPropertyAsString(_T("label"));
      wxString shortcut = menuItem->GetPropertyAsString(_T("shortcut"));
      if (!shortcut.IsEmpty())
        label += '\t' + shortcut;
        
      wxMenuItem *item = new wxMenuItem(menuWidget, lastMenuId++, 
          label, menuItem->GetPropertyAsString(_T("help")), 
          menuItem->GetPropertyAsInteger(_T("kind")));
          
      if (!menuItem->GetProperty("bitmap")->IsDefaultValue())
        item->SetBitmap(menuItem->GetPropertyAsBitmap("bitmap"));
        
      menuWidget->Append(item);
        
      if (item->GetKind() == wxITEM_CHECK && menuItem->GetPropertyAsInteger("checked"))
        item->Check(true);
        
      item->Enable(menuItem->GetPropertyAsInteger("enabled"));
    }
  }
  return menuWidget; 
}

void GridPanel::SetFrameWidgets(PObjectBase menubar, wxWindow *statusbar)
{
  Menubar *mbWidget = NULL;
  
  if (menubar)
  {
    mbWidget = new Menubar(this, -1);
    for (unsigned int i = 0; i < menubar->GetChildCount(); i++)
    {
      PObjectBase menu = menubar->GetChild(i);
      wxMenu *menuWidget = GetMenuFromObject(menu);
      mbWidget->AppendMenu(menu->GetPropertyAsString(_T("label")), menuWidget);
    }
  }
  
  wxSizer *mainSizer = GetSizer();
  
  SetSizer(NULL, false);
  
  wxSizer *dummySizer = new wxBoxSizer(wxVERTICAL);
  if (mbWidget)
  {
    dummySizer->Add(mbWidget, 0, wxEXPAND | wxTOP | wxBOTTOM, 0);
    dummySizer->Add(new wxStaticLine(this, -1), 0, wxEXPAND | wxALL, 0);
  }
  
  if (mainSizer)
    dummySizer->Add(mainSizer, 1, wxEXPAND | wxALL, 0);
  else
    dummySizer->AddStretchSpacer(1);
    
  if (statusbar) dummySizer->Add(statusbar, 0, wxEXPAND | wxALL, 0);
  
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
  // s�lo es necesario regenerar la vista si el objeto
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
    objAuxCt = obj->FindNearAncestor("container");  
    objAuxNb = obj->FindNearAncestor("notebook");
    
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
    string typeName = obj->GetObjectTypeName();
    if ( typeName == "widget" || typeName == "container" ||
         typeName == "notebook" || typeName == "statusbar")
      item = shared_dynamic_cast<VisualWindow>(visualObj)->GetWindow();
      
    else if (typeName == "sizer")
      item = shared_dynamic_cast<VisualSizer>(visualObj)->GetSizer();
    
    objAux = obj->FindNearAncestor("sizer");
    objAuxCt = obj->FindNearAncestor("container");
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




