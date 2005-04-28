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
// Sustituir "proportion" por "option"
//           "fg_colour" por "fg"
//           "bg_colour" por "bg"
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#include "visualobj.h"
#include "visualeditor.h"

#include "utils/typeconv.h"
#include "utils/debug.h"
#include "rad/genericpanel.h"

using namespace TypeConv;

PVisualObject VisualObject::CreateVisualObject
  (PObjectBase obj, wxWindow *wx_parent)
{
  PVisualObject vobj;
  
  PObjectInfo obj_info = obj->GetObjectInfo();
  ObjectType type = obj->GetObjectType();

  switch (type)
  {
    case T_CONTAINER:
    case T_WIDGET:
      vobj = PVisualObject(new VisualWindow(obj,wx_parent));
      break;
    case T_SIZER:
    {
      vobj = PVisualObject(new VisualSizer(obj,wx_parent));
      break;
    }
    case T_SIZERITEM:
      vobj = PVisualObject(new VisualLayout(obj));
      break;
      
    case T_SPACER:
      vobj = PVisualObject(new VisualSpacer(obj));
      break;

    default:
      break;
  }

  return vobj;
}   

VisualObject::VisualObject(PObjectBase obj) : m_object(obj)
{
}  

VisualObject::~VisualObject()
{
}
  
///////////////////////////////////////////////////////////////////////////////
VisualSizer::VisualSizer(PObjectBase obj,wxWindow *parent)
  : VisualObject(obj)
{
  ComponentBase *comp = obj->GetObjectInfo()->GetComponent();  
  if (comp)
    SetSizer((wxSizer *)(comp->Create(obj.get(),parent)));

  else
    // para que no pete ponemos un sizer por defecto, aunque deberá mostrar algun
    // mensaje de advertencia
    SetSizer(new wxBoxSizer(wxVERTICAL));
}  
void VisualSizer::AddToSizer(wxSizer *sizer, PObjectBase obj)
{
  wxSizer *sizer_obj = GetSizer();
  sizer->Add(sizer_obj,
    obj->GetProperty("option")->GetValueAsInteger(),
    obj->GetProperty("flag")->GetValueAsInteger(),
    obj->GetProperty("border")->GetValueAsInteger());
    
  Debug::Print("Add sizer to sizer");
}

///////////////////////////////////////////////////////////////////////////////

VisualWindow::VisualWindow(PObjectBase obj, wxWindow *parent)
  : VisualObject(obj)
{
  //m_window = NULL;
  // Ahora los widgets se crean a partir de los componentes externos
  
  ComponentBase *comp = obj->GetObjectInfo()->GetComponent();
  
  if (comp)
    SetWindow((wxWindow *)(comp->Create(obj.get(),parent)));

  else
    SetWindow(new GenericWindow(parent));
 
  SetupWindow();
}
  
void VisualWindow::AddToSizer(wxSizer *sizer, PObjectBase obj)
{
  wxWindow *window_obj = GetWindow();
  sizer->Add(window_obj,
    obj->GetProperty("option")->GetValueAsInteger(),
    obj->GetProperty("flag")->GetValueAsInteger(),
    obj->GetProperty("border")->GetValueAsInteger());
    
  Debug::Print("Add window to sizer");
}


void VisualWindow::SetupWindow()
{
  PObjectBase obj = GetObject();
  
  // todas las propiedades del objeto wxWindow se aplicaran en este
  // procedimiento
  PProperty ppos   = obj->GetProperty("pos");
  PProperty psize  = obj->GetProperty("size");
  PProperty pfont  = obj->GetProperty("font");
  PProperty pfg_colour  = obj->GetProperty("fg");
  PProperty pbg_colour  = obj->GetProperty("bg");
    
  wxPoint pos;
  wxSize size;
  wxFont font;
  wxColour fg_colour;
  wxColour bg_colour;
  
  if (ppos)
    pos = StringToPoint(_WXSTR(ppos->GetValue()));

  if (psize)
    size = StringToSize(_WXSTR(psize->GetValue()));

  if (pfont)
    font = StringToFont(_WXSTR(pfont->GetValue()));
    
  if (pfg_colour)
    fg_colour = StringToColour(_WXSTR(pfg_colour->GetValue()));

  if (pbg_colour)
    bg_colour = StringToColour(_WXSTR(pbg_colour->GetValue()));


  if (GetWindow())
  {
    GetWindow()->SetSize(pos.x,pos.y,size.GetWidth(), size.GetHeight());

    if (pfont->GetValue() != "")
      GetWindow()->SetFont(font);
    
    if (pfg_colour->GetValue() != "")
      GetWindow()->SetForegroundColour(fg_colour);

    if (pbg_colour->GetValue() != "")
      GetWindow()->SetBackgroundColour(bg_colour);
  }
}

///////////////////////////////////////////////////////////////////////////////
VisualSpacer::VisualSpacer(PObjectBase obj)
  : VisualObject(obj)
{
  PProperty propHeight = obj->GetProperty("height");
  PProperty propWidth = obj->GetProperty("width");
  
  m_height = (propHeight ? propHeight->GetValueAsInteger() : 0);
  m_width = (propWidth ? propWidth->GetValueAsInteger() : 0);
}  

void VisualSpacer::AddToSizer(wxSizer *sizer, PObjectBase obj)
{
  sizer->Add(m_width, m_height,
    obj->GetProperty("option")->GetValueAsInteger(),
    obj->GetProperty("flag")->GetValueAsInteger(),
    obj->GetProperty("border")->GetValueAsInteger());
    
  Debug::Print("Add spacer to sizer");
}

///////////////////////////////////////////////////////////////////////////////
VisualLayout::VisualLayout (PObjectBase obj)
  : VisualObject(obj)
{
}

///////////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(VObjEvtHandler,wxEvtHandler)
//  EVT_SET_FOCUS(VObjEvtHandler::OnSetFocus)
  EVT_LEFT_DOWN(VObjEvtHandler::OnLeftClick)
//  EVT_MOTION(VObjEvtHandler::OnMouseMove)	
  EVT_PAINT(VObjEvtHandler::OnPaint)
END_EVENT_TABLE()

VObjEvtHandler::VObjEvtHandler(wxWindow *win, PObjectBase obj, DataObservable *data)
{
  m_window = win;
  m_object = obj;
  m_data = data;
};

void VObjEvtHandler::OnLeftClick(wxMouseEvent &event)
{
/*  m_mouseX = event.GetX();
  m_mouseY = event.GetY();
  m_pos.x = m_pos.y = 0;*/
  
  PObjectBase obj = m_object.lock();

  if (obj)
    m_data->SelectObject(obj);
  else
    wxLogMessage(wxT("Hay algun problema en VObjEvtHandler"));
    
  //event.Skip();
}  

/*void VObjEvtHandler::OnMouseMove(wxMouseEvent &event)
{
  wxLogMessage(_("Moving.."));
}*/
/*
void VObjEvtHandler::OnMouseMove(wxMouseEvent &event)
{
  long delta_x, delta_y;
  
  delta_x = event.GetX() - m_mouseX;
  delta_y = event.GetY() - m_mouseY;


  wxLogMessage(wxString::Format(wxT("Dragging %ld,%ld"),delta_x,delta_y));
  
  
  if (event.Dragging())
  {
    

    // movemos el widget

    
    m_pos.x += delta_x;
    m_pos.y += delta_y;
  }
  else
  {
    PObjectBase obj = m_object.lock();
    if (obj)
    {
      PProperty prop = obj->GetProperty("pos");
      if (prop)
      {
        wxPoint current_pos = prop->GetValueAsPoint();
        current_pos.x += m_pos.x;
        current_pos.y += m_pos.y;
        
        m_data->ModifyProperty(prop,TypeConv::PointToString(current_pos));
      }
      
    }
  }  
  
  m_mouseX = event.GetX();
  m_mouseY = event.GetY();
}  */


void VObjEvtHandler::OnPaint(wxPaintEvent &event)
{
  //PWidgetObject wo = shared_dynamic_cast<WidgetObject>(m_object.lock());
  PObjectBase wo = shared_dynamic_cast<ObjectBase>(m_object.lock());
  if (wo->IsContainer())
  {
    wxWindow *aux = m_window;
    while (!aux->IsKindOf(CLASSINFO(GridPanel))) aux = aux->GetParent();
    GridPanel *gp = (GridPanel*) aux;
    if (gp->GetActivePanel() == m_window)
    {
      wxPaintDC dc(m_window);
      gp->HighlightSelection(dc);
    }
  }
  event.Skip();  
}


///////////////////////////////////////////////////////////////////////////////
// ESTO ES CÓDIGO "SUCIO", LO HE MANTENIDO PARA DAR IDEAS DE PROGRAMACIÓN
// A ALGUIEN QUE QUIERA IMPLEMENTAR LA POSIBILIDAD DE EDITAR WIDGETS
// DESDE EL DESIGNER.
// ESTO ES EXPIRIMENTAL!!!.
// 
///////////////////////////////////////////////////////////////////////////////
#ifdef __WXFB_EXPERIMENTAL__

BEGIN_EVENT_TABLE(EditorHandler,wxEvtHandler)
  EVT_MOTION(EditorHandler::OnMouseMove)	
  EVT_LEFT_DOWN(EditorHandler::OnLeftClick)
END_EVENT_TABLE()


wxPoint EditorHandler::s_pos = wxPoint();
WPObjectBase EditorHandler::s_object = PObjectBase();
long EditorHandler::s_mouseX = 0;
long EditorHandler::s_mouseY = 0;
EditorHandler::MouseState EditorHandler::s_state = ST_IDLE;
wxWindow *EditorHandler::s_editor = NULL;  
wxPoint EditorHandler::s_boundPos;
wxSize EditorHandler::s_boundSize;

EditorHandler::EditorHandler(DataObservable *data)
{
  m_data = data;
}

void EditorHandler::OnLeftClick(wxMouseEvent &event)
{
/*  s_mouseX = event.GetX();
  s_mouseY = event.GetY();
  s_pos.x = s_pos.y = 0;
  s_state = ST_IDLE;*/
  event.Skip();
}

void EditorHandler::SetObject(PObjectBase obj)
{
  s_object = obj;
}

void EditorHandler::OnMouseMove(wxMouseEvent &event)
{
//  wxLogMessage(_("[EditorHandler] Moving.."));
  long delta_x, delta_y;
  
  if (event.Dragging())
  {
    if (s_state == ST_IDLE)
    {
      s_state = ST_MOVING;
      s_mouseX = event.GetX();
      s_mouseY = event.GetY();
      s_pos.x = s_pos.y = 0;
      delta_x = 0;
      delta_y = 0;
      
      PObjectBase obj = m_data->GetSelectedObject();
      if (obj && obj->GetObjectType()==T_WIDGET)
      {
        PProperty ppos = obj->GetProperty("pos");
        PProperty psize = obj->GetProperty("size");
        if (ppos && psize)
        {
          s_boundPos = ppos->GetValueAsPoint();
          s_boundSize = psize->GetValueAsSize();
          if (s_boundSize.GetHeight() <= 0 || s_boundSize.GetWidth() <= 0)
            s_boundSize = wxSize(20,20);
        }
      }
    }
    else
    {
      // borramos el dibujo previo
      if (s_editor)
      {
        long temp_x, temp_y;
        temp_x = ((s_boundPos.x+5)/10)*10;
        temp_y = ((s_boundPos.y+5)/10)*10;        
        
        wxClientDC dc(s_editor);
        wxPen pen(*wxBLACK,1,wxDOT);
        dc.SetPen(pen);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.SetLogicalFunction(wxINVERT);
        //dc.DrawLine(event.GetX()-10,event.GetY(),event.GetX()+10,event.GetY());
        dc.DrawRectangle(temp_x, temp_y ,s_boundSize.GetWidth(),s_boundSize.GetHeight());
      }
      
      delta_x = event.GetX() - s_mouseX;
      delta_y = event.GetY() - s_mouseY;
      s_boundPos.x += delta_x;
      s_boundPos.y += delta_y;
    }
      

    // movemos el widget
    s_pos.x += delta_x;
    s_pos.y += delta_y;

    // dibujamos     
    if (s_editor)
    {
        long temp_x, temp_y;
        temp_x = ((s_boundPos.x+5)/10)*10;
        temp_y = ((s_boundPos.y+5)/10)*10;        
        
        wxClientDC dc(s_editor);
        wxPen pen(*wxBLACK,1,wxDOT);
        dc.SetPen(pen);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);
        dc.SetLogicalFunction(wxINVERT);
        //dc.DrawLine(event.GetX()-10,event.GetY(),event.GetX()+10,event.GetY());
        dc.DrawRectangle(temp_x, temp_y ,s_boundSize.GetWidth(),s_boundSize.GetHeight());
     
    }
    
  }
  else if (s_state == ST_MOVING)
  {
    s_state = ST_IDLE;
    PObjectBase obj = m_data->GetSelectedObject();
    if (obj && obj->GetObjectType()==T_WIDGET)
    {
      PProperty prop = obj->GetProperty("pos");
      if (prop)
      {
        wxPoint current_pos = prop->GetValueAsPoint();
        
        // ajustamos a la rejilla
        s_pos.x = ((s_pos.x+5)/10)*10;
        s_pos.y = ((s_pos.y+5)/10)*10;
        
/*        current_pos.x += s_pos.x;
        current_pos.y += s_pos.y;*/
        current_pos.x = ((s_boundPos.x+5)/10)*10;
        current_pos.y = ((s_boundPos.y+5)/10)*10; 

        m_data->ModifyProperty(prop,TypeConv::PointToString(current_pos));
      }
      
    }
  }

  
  s_mouseX = event.GetX();
  s_mouseY = event.GetY();
  event.Skip();  
}

#endif // __WXFB_EXPERIMENTAL__
