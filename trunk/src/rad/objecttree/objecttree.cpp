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

#include "objecttree.h"
#include "icons/ot_sizer.xpm"
#include "icons/ot_widget.xpm"
#include "icons/ot_form.xpm"
#include "icons/ot_spacer.xpm"
#include "icons/ot_project.xpm"
#include "icons/ot_notebook.xpm"
#include "icons/ot_menubar.xpm"
#include "icons/ot_menu.xpm"
#include "icons/ot_menuitem.xpm"
#include "utils/debug.h"
#include <wx/imaglist.h>


BEGIN_EVENT_TABLE(ObjectTree,ObjectTreeGUI)
  EVT_TREE_SEL_CHANGED(-1, ObjectTree::OnSelChanged)
  EVT_TREE_ITEM_RIGHT_CLICK(-1, ObjectTree::OnRightClick)	
END_EVENT_TABLE()

ObjectTree::ObjectTree(wxWindow *parent, int id)
  : ObjectTreeGUI(parent,id)
{
  wxImageList *img_list = new wxImageList(16,16);
  img_list->Add(wxBitmap(ot_project_xpm));
  img_list->Add(wxBitmap(ot_form_xpm));
  img_list->Add(wxBitmap(ot_sizer_xpm));
  img_list->Add(wxBitmap(ot_widget_xpm));
  img_list->Add(wxBitmap(ot_spacer_xpm));
  img_list->Add(wxBitmap(ot_notebook_xpm));
  img_list->Add(wxBitmap(ot_menubar_xpm));
  img_list->Add(wxBitmap(ot_menu_xpm));
  img_list->Add(wxBitmap(ot_menuitem_xpm));
  
  m_tcObjects->AssignImageList(img_list);
}

void ObjectTree::Create()
{
  m_tcObjects->Freeze();

  // borramos toda la información previa
  m_tcObjects->DeleteAllItems();
  m_map.erase(m_map.begin(),m_map.end());
  
  PObjectBase project = GetData()->GetProjectData();

//  wxTreeItemId root = m_tcObjects->AddRoot(wxT("Project"));
//  ObjectBase *class_obj = GetDocument()->GetSelectedWindow();
//  AddChildren(class_obj, root);
  if (project)
  {
    wxTreeItemId dummy;
    AddChildren(project, dummy, true );
  }  
  
  m_tcObjects->Thaw();
}  

void ObjectTree::OnSelChanged(wxTreeEvent &event)
{
  wxTreeItemId id = event.GetItem();
  if (!id.IsOk()) return;
  wxTreeItemData *item_data = m_tcObjects->GetItemData(id);

  if (item_data)
  {
    PObjectBase obj(((ObjectTreeItemData *)item_data)->GetObject());
    assert(obj);
    GetData()->SelectObject(obj);
  }
}

void ObjectTree::OnRightClick(wxTreeEvent &event)
{
  wxTreeItemId id = event.GetItem();
  wxTreeItemData *item_data = m_tcObjects->GetItemData(id);
  if (item_data)
  {  
    PObjectBase obj(((ObjectTreeItemData *)item_data)->GetObject());
    assert(obj);
    wxMenu * menu = new ItemPopupMenu(GetData(),obj);
    wxPoint pos = event.GetPoint();
    PopupMenu(menu,pos.x, pos.y);
  }
}

void ObjectTree::ProjectLoaded()
{
  Create();
}

void ObjectTree::ProjectRefresh()
{
  Create();
}
  
void ObjectTree::ProjectSaved()
{
}
 
void ObjectTree::ObjectSelected(PObjectBase obj)
{
  // buscamos el item asociado al objeto lo marcamos
  // como seleccionado
  ObjectItemMap::iterator it = m_map.find(obj);
  if (it != m_map.end() && m_tcObjects->GetSelection() != it->second)
  {
    m_tcObjects->SelectItem(it->second);
  }
    
  
}

void ObjectTree::ObjectCreated(PObjectBase obj)
{
  // seguro que se puede optimizar
  Create();
}

void ObjectTree::ObjectRemoved(PObjectBase obj)
{
  // seguro que se puede optimizar
  Create();
}

void ObjectTree::PropertyModified(PProperty prop)
{
  if (prop->GetName() == "name")
  {
    ObjectItemMap::iterator it = m_map.find(prop->GetObject());
    if (it != m_map.end())
    {
      UpdateItem(it->second,it->first);
    }
  };
}

void ObjectTree::AddChildren(PObjectBase obj, wxTreeItemId &parent, bool is_root)
{
  // los sizeritems son objetos "ficticios", y no se deben mostrar en el árbol
  //if (obj->GetObjectTypeName() == "sizeritem" ||
  //    obj->GetObjectTypeName() == "notebookpage")
  
  if (obj->GetObjectInfo()->GetObjectType()->IsItem())
    AddChildren(obj->GetChild(0),parent);
  else
  {
    wxTreeItemId new_parent;

    ObjectTreeItemData *item_data = new ObjectTreeItemData(obj);
    
    if (is_root)
      new_parent = m_tcObjects->AddRoot(wxT(""),-1,-1,item_data);
    else
      new_parent = m_tcObjects->AppendItem(parent,wxT(""),-1,-1,item_data);

    m_tcObjects->Expand(parent);      
    
    // registramos el objeto
    m_map.insert(ObjectItemMap::value_type(obj,new_parent));
    
    // configuramos su imagen
    int image_idx = GetImageIndex(obj->GetObjectTypeName());
    
    m_tcObjects->SetItemImage(new_parent,image_idx);
    m_tcObjects->SetItemSelectedImage(new_parent,image_idx);
    
    // y su contenido
    UpdateItem(new_parent,obj);
    

    // y de forma recursiva generamos el resto de hijos    
    unsigned int count = obj->GetChildCount();
    unsigned int i;
    for (i = 0; i < count ; i++)
    {
      PObjectBase child = obj->GetChild(i);
      AddChildren(child, new_parent);
    }
  }  
}

int ObjectTree::GetImageIndex (string type)
{
  // TO-DO: eliminar dependencias con el tipo usando el icono
  // definido para el componente en el fichero XML (el de la paleta)
  
  int image = 0;
  if (type == "project")
    image = 0;
  else if (type == "form")
    image = 1;
  else if (type == "sizer")
    image = 2;
  else if (type == "container" || type == "widget")
    image = 3;
  else if (type == "spacer")
    image = 4;
  else if (type == "notebook")
    image = 5;
  else if (type == "menubar")
    image = 6;
  else if (type == "menu")
    image = 7;
  else if (type == "menuitem")
    image = 8;
  
  return image;
}

void ObjectTree::UpdateItem(wxTreeItemId id, PObjectBase obj)
{
  // mostramos el nombre 
  wxString class_name(obj->GetClassName().c_str(),wxConvUTF8);
  PProperty prop = obj->GetProperty("name");
  wxString obj_name;
  if (prop)
    obj_name = wxString(prop->GetValue().c_str(),wxConvUTF8);
  
  wxString text = obj_name + wxT(" : ") + class_name;
  
  // actualizamos el item
  m_tcObjects->SetItemText(id,text);
}

///////////////////////////////////////////////////////////////////////////////

ObjectTreeItemData::ObjectTreeItemData(PObjectBase obj) : m_object(obj)
{}

///////////////////////////////////////////////////////////////////////////////

#define MENU_MOVE_UP    100
#define MENU_MOVE_DOWN  101
#define MENU_CUT        102
#define MENU_PASTE      103

BEGIN_EVENT_TABLE(ItemPopupMenu,wxMenu)
  EVT_MENU(-1, ItemPopupMenu::OnMenuEvent)
END_EVENT_TABLE()

ItemPopupMenu::ItemPopupMenu(DataObservable *data, PObjectBase obj)
  : wxMenu(), m_data(data), m_object(obj)
{
  Append(MENU_CUT,       wxT("Cut"));
  Append(MENU_PASTE,     wxT("Paste"));
  AppendSeparator();
  Append(MENU_MOVE_UP,   wxT("Move Up"));
  Append(MENU_MOVE_DOWN, wxT("Move Down"));

}

void ItemPopupMenu::OnMenuEvent (wxCommandEvent & event)
{
  int id = event.GetId();

  switch (id)
  {
    case MENU_CUT:
      m_data->CutObject(m_object);
      break;
    case MENU_PASTE:
      m_data->PasteObject(m_object);
      break;
    case MENU_MOVE_UP:
      m_data->MovePosition(m_object,false);
      break;
    case MENU_MOVE_DOWN:
      m_data->MovePosition(m_object,true);
      break;
    default:
      break;
  }
}

