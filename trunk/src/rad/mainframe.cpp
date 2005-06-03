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
// Añadido código de creación del panel XRC (línea 173)
// Juan Antonio Ortega (jortegalalmolda@gmail.com)

#include "mainframe.h"
#include "wx/splitter.h"
#include "wx/config.h"
#include "utils/debug.h"
#include "rad/title.h"
#include "rad/bitmaps.h"
#include "icons/wxwin16x16.xpm"
#include "icons/system.xpm"
#include "model/xrcfilter.h"
#include "rad/about.h"

#define ID_ABOUT 100
#define ID_QUIT  101 
#define ID_SAVE_PRJ  102
#define ID_OPEN_PRJ  103
#define ID_NEW_PRJ  104
#define ID_GENERATE_CODE 105
#define ID_IMPORT_XRC 106
#define ID_UNDO 107
#define ID_REDO 108


BEGIN_EVENT_TABLE(MainFrame,wxFrame)
  EVT_MENU(ID_NEW_PRJ,MainFrame::OnNewProject)
  EVT_MENU(ID_SAVE_PRJ,MainFrame::OnSaveProject)
  EVT_MENU(ID_OPEN_PRJ,MainFrame::OnOpenProject)
  EVT_MENU(ID_ABOUT,MainFrame::OnAbout)
  EVT_MENU(ID_QUIT,MainFrame::OnExit)
  EVT_MENU(ID_IMPORT_XRC,MainFrame::OnImportXrc)
  EVT_MENU(ID_GENERATE_CODE,MainFrame::OnGenerateCode)
  EVT_MENU(ID_UNDO,MainFrame::OnUndo)
  EVT_MENU(ID_REDO,MainFrame::OnRedo)
  EVT_CLOSE(MainFrame::OnClose)
END_EVENT_TABLE()

MainFrame::MainFrame(DataObservable *data,wxWindow *parent, int id)
  : wxFrame(parent,id,wxT("wxFormBuilder v.0.1"),wxDefaultPosition,wxSize(1000,800))
{
  wxString date(wxT(__DATE__));
  wxString time(wxT(__TIME__));
  SetTitle(wxT("wxFormBuilder (Build on ") + date +wxT(" - ")+ time + wxT(")"));
  
  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
  
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_OPEN_PRJ, _T("&Open...\tF2"), _T("Load a project"));
  menuFile->Append(10,          _T("&Save"), _T("Save current project"));
  menuFile->Append(ID_SAVE_PRJ, _T("Save &As...\tF3"), _T("Save the project"));
  menuFile->AppendSeparator();
  menuFile->Append(ID_IMPORT_XRC, _T("&Import XRC..."), _T("Save current project"));
  menuFile->AppendSeparator();
  menuFile->Append(ID_QUIT, _T("E&xit\tAlt-X"), _T("Quit this program"));

  wxMenu *menuEdit = new wxMenu;
  menuEdit->Append(ID_UNDO, _T("&Undo \tCTRL+Z"), _T("Undo"));
  menuEdit->Append(ID_REDO, _T("&Redo \tCTRL+Y"), _T("Redo"));
  
  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(ID_ABOUT, _T("&About...\tF1"), _T("Show about dialog"));
  

  // now append the freshly created menu to the menu bar...
  wxMenuBar *menuBar = new wxMenuBar();
  menuBar->Append(menuFile, _T("&File"));
  menuBar->Append(menuEdit, _T("&Edit"));
  menuBar->Append(menuHelp, _T("&Help"));

  // ... and attach this menu bar to the frame
  SetMenuBar(menuBar);

  /*
  #ifdef __WXFB_DEBUG__
  m_log = new wxLogWindow(NULL,wxT("Logging"));
  m_old_log = wxLog::SetActiveTarget(m_log);
  #endif //__WXFB_DEBUG__
  */
  
  wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);
  

  
  ///////////////

  wxSplitterWindow *v_splitter = new wxSplitterWindow(this,-1,wxDefaultPosition,wxDefaultSize, wxSP_3DSASH | wxSP_LIVE_UPDATE);
  wxPanel *left = new wxPanel(v_splitter,-1);//,wxDefaultPosition, wxDefaultSize,wxSIMPLE_BORDER);
  wxBoxSizer *left_sizer = new wxBoxSizer(wxVERTICAL);
    
  wxPanel *right = new wxPanel(v_splitter,-1);
  v_splitter->SplitVertically(left,right,300);

  wxSplitterWindow *h_splitter = new wxSplitterWindow(left,-1,wxDefaultPosition,wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE);//wxSP_BORDER);

  wxPanel *tree_panel = new wxPanel(h_splitter,-1);
  Title *tree_title = new Title(tree_panel,wxT("Object Tree"));

  m_objTree = new ObjectTree(tree_panel,-1);
  data->AddDataObserver(m_objTree);
  m_objTree->SetData(data);
  m_objTree->Create();
  
  wxBoxSizer *tree_sizer = new wxBoxSizer(wxVERTICAL);
  tree_sizer->Add(tree_title,0,wxEXPAND,0);
  tree_sizer->Add(m_objTree,1,wxEXPAND,0);
  
  tree_panel->SetSizer(tree_sizer);
  tree_panel->SetAutoLayout(true);


  wxPanel *obj_inspPanel = new wxPanel(h_splitter,-1);
  wxBoxSizer *obj_insp_sizer = new wxBoxSizer(wxVERTICAL);

  Title *obj_insp_title = new Title(obj_inspPanel,wxT("Object Properties"));
    
  m_objInsp = new ObjectInspector(obj_inspPanel,-1);
  data->AddDataObserver(m_objInsp);

  obj_insp_sizer->Add(obj_insp_title,0,wxEXPAND,0);

  obj_insp_sizer->Add(m_objInsp,1,wxEXPAND,0);

  h_splitter->SplitHorizontally(tree_panel,obj_inspPanel,400);
  obj_inspPanel->SetSizer(obj_insp_sizer);
  obj_inspPanel->SetAutoLayout(true);
  
  left_sizer->Add(h_splitter,1,wxEXPAND,0);

  left->SetSizer(left_sizer);
  left->SetAutoLayout(true);
  //////////////
  wxBoxSizer *right_sizer = new wxBoxSizer(wxVERTICAL);
  
  // la paleta de componentes, no es un observador propiamente dicho, ya
  // que no responde ante los eventos de la aplicación
  m_palette = new wxFbPalette(right,-1);
  m_palette->SetData(data);
  m_palette->Create();
  
  m_notebook = new wxNotebook(right, -1, wxDefaultPosition, wxDefaultSize, wxNB_NOPAGETHEME);

/*  wxPanel *panel = new wxPanel(notebook,-1);
  panel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DSHADOW)	);
  wxPanel *desig = new wxPanel(panel,-1,wxPoint(0,0),wxSize(100,100),wxDOUBLE_BORDER);*/
  
  //m_design = new DesignPanel(doc,m_notebook);
  m_visualEdit = new VisualEditor(m_notebook);
  data->AddDataObserver(m_visualEdit);
//  m_design = new wxPanel(m_notebook);
  m_notebook->AddPage( m_visualEdit, wxT("Designer") );

// provisional
//  m_h = new CodeEditorPanel(doc,m_notebook,FILE_H);
//  m_h = new wxPanel(m_notebook);

  m_cpp = new CppPanel(m_notebook,-1);
  data->AddDataObserver(m_cpp);
  m_notebook->AddPage( m_cpp, wxT("C++") );

//Juan
  m_xrc = new XrcPanel(m_notebook,-1);
  data->AddDataObserver(m_xrc);
  m_notebook->AddPage(m_xrc, wxT("XRC"));
//End
  
//  m_cpp = new CodeEditorPanel(doc,m_notebook,FILE_CPP);
//  m_cpp = new wxPanel(m_notebook);
//  m_notebook->AddPage( m_cpp, wxT("cpp") );

/*  wxStaticText *text = new wxStaticText(right,-1,wxT("EDITOR"),wxDefaultPosition,wxDefaultSize,wxSIMPLE_BORDER);
  text->SetBackgroundColour(wxColour(100,100,100));
  text->SetForegroundColour(*wxWHITE);
  text->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxBOLD, 0, wxT("")));*/
  Title *ed_title = new Title(right,wxT("Editor"));
  
  right_sizer->Add(m_palette,0,wxEXPAND,0);
  right_sizer->Add(ed_title,0,wxEXPAND,0);
//  right_sizer->Add(new wxNotebookSizer( m_notebook ),1,wxEXPAND|wxTOP,5);
  right_sizer->Add(m_notebook,1,wxEXPAND|wxTOP,5);
  right->SetSizer(right_sizer);

//  top_sizer->Add(sizer,0,wxEXPAND,0);
  top_sizer->Add(v_splitter,1,wxEXPAND,0);

  CreateStatusBar();
  wxToolBar* toolbar = CreateToolBar();
  toolbar->SetToolBitmapSize(wxSize(22, 22));
  toolbar->AddTool(ID_NEW_PRJ,wxT("New Project"),AppBitmaps::GetBitmap(wxT("new")));
  toolbar->AddTool(ID_OPEN_PRJ,wxT("Open Project"),AppBitmaps::GetBitmap(wxT("open")));
  toolbar->AddTool(ID_SAVE_PRJ,wxT("Save Project"),AppBitmaps::GetBitmap(wxT("save")));
  toolbar->AddSeparator();
  toolbar->AddTool(ID_GENERATE_CODE,wxT("Generate Code"),system_xpm);

  toolbar->Realize();

  SetSizer(top_sizer);
  top_sizer->SetSizeHints(this);
  SetAutoLayout(true);
  Layout();
  Fit();

  //SetSize(wxSize(1000,800));
  RestorePosition(_T("mainframe"));
  //Centre();
  Refresh();


  // añadimos el manejador de las teclas rápidas de la aplicación
  // realmente este es el sitio donde hacerlo ?????
  m_objTree->AddCustomKeysHandler(new CustomKeysEvtHandler(data));


  data->AddDataObserver(this);
};  


MainFrame::~MainFrame()
{/*
  #ifdef __WXFB_DEBUG__
  wxLog::SetActiveTarget(m_old_log);
  m_log->GetFrame()->Destroy();
  #endif //__WXFB_DEBUG__
  */

  // Eliminamos los observadores, ya que si quedara algún evento por procesar
  // se produciría un error de acceso no válido debido a que los observadores
  // ya estarían destruidos
  m_objTree->GetData()->RemoveDataObserver(m_objTree);
  m_objInsp->GetData()->RemoveDataObserver(m_objInsp);
  m_visualEdit->GetData()->RemoveDataObserver(m_visualEdit);
} 

void MainFrame::RestorePosition(const wxString &name)
{
    bool maximized;
    int x, y, w, h;
    wxConfigBase *config = wxConfigBase::Get();
    
    config->SetPath(name);
    if (config->Read(_T("IsMaximized"), &maximized))
    {
        Maximize(maximized);
    	x = y = w = h = -1;
        config->Read(_T("PosX"), &x);
        config->Read(_T("PosY"), &y);
        config->Read(_T("SizeW"), &w);
        config->Read(_T("SizeH"), &h);
        SetSize(x, y, w, h);
        bool iconized = false;
        config->Read(_T("IsIconized"), &iconized);
        if (iconized) Iconize(iconized);
    }
    config->SetPath(_T(".."));
}

void MainFrame::SavePosition(const wxString &name)
{
    wxConfigBase *config = wxConfigBase::Get();
    bool isIconized = IsIconized();
    bool isMaximized = IsMaximized();
    
    config->SetPath(name);
    if (!isMaximized)
    {
        config->Write(_T("PosX"), isIconized ? -1 : GetPosition().x);
        config->Write(_T("PosY"), isIconized ? -1 : GetPosition().y);
        config->Write(_T("SizeW"), isIconized ? -1 : GetSize().GetWidth());
        config->Write(_T("SizeH"), isIconized ? -1 : GetSize().GetHeight());
    }    
    config->Write(_T("IsMaximized"), isMaximized);
    config->Write(_T("IsIconized"), isIconized);
    config->SetPath(_T(".."));
} 

void MainFrame::OnSaveProject(wxCommandEvent &event)
{
//  GetData()->SaveProject(wxT("hola.xml"));
  wxFileDialog *dialog = new wxFileDialog(this,wxT("Open Project"),wxT("projects/example"),
    wxT("example.xml"),wxT("*.xml"),wxSAVE);

  if (dialog->ShowModal() == wxID_OK)
  {
    GetData()->SaveProject(dialog->GetPath());
  };
  
  dialog->Destroy();
}  

void MainFrame::OnOpenProject(wxCommandEvent &event)
{
  //GetData()->LoadProject(wxT("hola.xml"));
  wxFileDialog *dialog = new wxFileDialog(this,wxT("Open Project"),wxT("projects/example"),
    wxT("example.xml"),wxT("*.xml"),wxOPEN | wxHIDE_READONLY);

  if (dialog->ShowModal() == wxID_OK)
  {
    GetData()->LoadProject(dialog->GetPath());
  };
  
  dialog->Destroy();
}  

void MainFrame::OnImportXrc(wxCommandEvent &event)
{
  wxFileDialog *dialog = new wxFileDialog(this,wxT("Import XRC file"),wxT("projects/example"),
  wxT("example.xrc"),wxT("*.xrc"),wxOPEN | wxHIDE_READONLY);

  if (dialog->ShowModal() == wxID_OK)
  {
    TiXmlDocument doc(_STDSTR(dialog->GetPath()));
    if (doc.LoadFile())
    {
      XrcFilter xrc;
      xrc.SetObjectDatabase(GetData()->GetObjectDatabase());
      PObjectBase project = xrc.GetProject(&doc);
      if (project)
      {
        GetData()->MergeProject(project);
      }
      else
        wxLogMessage(wxT("Error al importar XRC"));
    }
    else
      wxLogMessage(wxT("Error al cargar archivo XRC"));
  }
  
  dialog->Destroy();
}


void MainFrame::OnNewProject(wxCommandEvent &event)
{
  GetData()->NewProject();
}  

void MainFrame::OnGenerateCode(wxCommandEvent &event)
{
  GetData()->GenerateCode();
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
  AboutDialog *dlg = new AboutDialog(this);
  dlg->ShowModal();
  dlg->Destroy();
  
  /*
  wxMessageBox(
    wxT("wxFormBuilder v.0.1\n"
        "wxFormBuilder is a visual dialog editor with\n"
        "code generation for wxWidgets Framework\n"
        "(C) 2005 - José Antonio Hurtado"),
    wxT("About of wxFormBuilder..."),wxOK);*/
}

void MainFrame::OnExit(wxCommandEvent &event)
{
  Close();
}

void MainFrame::OnClose(wxCloseEvent &event)
{
    SavePosition(_T("mainframe"));
    event.Skip();
}

void MainFrame::ProjectLoaded()
{
  GetStatusBar()->SetStatusText(wxT("Project Loaded!"));
  UpdateMenuBar();
}
void MainFrame::ProjectSaved()
{
  GetStatusBar()->SetStatusText(wxT("Project Saved!"));
  UpdateMenuBar();
}
void MainFrame::ObjectSelected(PObjectBase obj)
{
  wxString name;
  PProperty prop(obj->GetProperty("name"));
  
  if (prop)
    name = prop->GetValueAsString();
  else

    name = wxT("\"Unknown\"");
  
  GetStatusBar()->SetStatusText(wxT("Object ") + name + wxT(" Selected!"));
}

void MainFrame::ObjectCreated(PObjectBase obj)
{
  GetStatusBar()->SetStatusText(wxT("Object Created!"));
  UpdateMenuBar();
}

void MainFrame::ObjectRemoved(PObjectBase obj)
{
  GetStatusBar()->SetStatusText(wxT("Object Removed!"));
  UpdateMenuBar();
}

void MainFrame::PropertyModified(PProperty prop)
{
  GetStatusBar()->SetStatusText(wxT("Property Modified!"));
  UpdateMenuBar();
}

void MainFrame::CodeGeneration()
{
  GetStatusBar()->SetStatusText(wxT("Code Generated!"));
}

void MainFrame::OnUndo(wxCommandEvent &event)
{
  GetData()->Undo();
}
void MainFrame::OnRedo(wxCommandEvent &event)
{
  GetData()->Redo();
}

void MainFrame::UpdateMenuBar()
{
  wxMenu *menuEdit = GetMenuBar()->GetMenu(GetMenuBar()->FindMenu(_("Edit")));
  
  menuEdit->Enable(ID_REDO,GetData()->CanRedo());
  menuEdit->Enable(ID_UNDO,GetData()->CanUndo());
}

void MainFrame::ProjectRefresh()
{
  UpdateMenuBar();
}