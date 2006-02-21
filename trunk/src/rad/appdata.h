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

#ifndef __APP_DATA__
#define __APP_DATA__

#include "rad/appobserver.h"
#include "model/database.h"
#include "rad/cmdproc.h"
#include <set>

class ApplicationData : public DataObservable
{
 private:

  string m_rootDir;       // directorio raíz (mismo que el ejecutable)
  bool m_modFlag;           // flag de proyecto modificado
  PObjectDatabase m_objDb;  // Base de datos de objetos
  PObjectBase m_project;    // Proyecto
  PObjectBase m_selObj;     // Objeto seleccionado

  PObjectBase m_clipboard;
  bool m_copyOnPaste; // flag que indica si hay que copiar el objeto al pegar

  // Procesador de comandos Undo/Redo
  CommandProcessor m_cmdProc;
  string m_projectFile;


  /**
   * Comprueba las referencias cruzadas de todos los nodos del árbol
   */
  void CheckProjectTree(PObjectBase obj);

  /**
   * Resuelve un posible conflicto de nombres.
   * @note el objeto a comprobar debe estar insertado en proyecto, por tanto
   *       no es válida para arboles "flotantes".
   */
  void ResolveNameConflict(PObjectBase obj);

  /**
   *
   */
  void ResolveSubtreeNameConflicts(PObjectBase obj, PObjectBase topObj = PObjectBase());

  /**
   * Rutina auxiliar de ResolveNameConflict
   */
  void BuildNameSet(PObjectBase obj, PObjectBase top, set<string> &name_set);

  /**
   * Calcula la posición donde deberá ser insertado el objeto.
   *
   * Dado un objeto "padre" y un objeto "seleccionado", esta rutina calcula la
   * posición de inserción de un objeto debajo de "parent" de forma que el objeto
   * quede a continuación del objeto "seleccionado".
   *
   * El algoritmo consiste ir subiendo en el arbol desde el objeto "selected"
   * hasta encontrar un objeto cuyo padre sea el mismo que "parent" en cuyo
   * caso se toma la posición siguiente a ese objeto.
   *
   * @param parent objeto "padre"
   * @param selected objeto "seleccionado".
   * @return posición de insercción (-1 si no se puede insertar).
   */
  int CalcPositionOfInsertion(PObjectBase selected,PObjectBase parent);


  /**
   * Elimina aquellos items que no contengan hijos.
   *
   * Esta rutina se utiliza cuando el árbol que se carga de un fichero
   * no está bien formado, o la importación no ha sido correcta.
   */
   void RemoveEmptyItems(PObjectBase obj);

   /**
    * Eliminar un objeto.
    */
   void DoRemoveObject(PObjectBase object, bool cutObject);

   void Execute(PCommand cmd);

 public:
  ApplicationData(const string &rootdir = ".");

  // Operaciones sobre los datos
  bool LoadProject(const wxString &filename);
  void SaveProject(const wxString &filename);
  void NewProject();
  void SelectObject(PObjectBase obj);
  void CreateObject(wxString name);
  void RemoveObject(PObjectBase obj);
  void CutObject(PObjectBase obj);
  void CopyObject(PObjectBase obj);
  void PasteObject(PObjectBase parent);
  void InsertObject(PObjectBase obj, PObjectBase parent);
  void MergeProject(PObjectBase project);
  void ModifyProperty(PProperty prop, wxString value);
  void GenerateCode();
  void MovePosition(PObjectBase, bool right, unsigned int num = 1);
  void Undo();
  void Redo();
  void ToggleExpandLayout(PObjectBase obj);
  void ToggleStretchLayout(PObjectBase obj);
  void ChangeAlignment (PObjectBase obj, int align, bool vertical);
  void ToggleBorderFlag(PObjectBase obj, int border);
  void CreateBoxSizerWithObject(PObjectBase obj);

  // Servicios para los observadores
  PObjectBase GetSelectedObject();
  PObjectBase GetProjectData();
  PObjectBase GetSelectedForm();
  bool CanUndo() { return m_cmdProc.CanUndo(); }
  bool CanRedo() { return m_cmdProc.CanRedo(); }
  bool GetLayoutSettings(PObjectBase obj, int *flag, int *option,int *border);
  bool CanPasteObject();
  bool CanCopyObject();
  bool IsModified();

  PObjectPackage GetPackage(unsigned int idx)
    { return m_objDb->GetPackage(idx);}

  unsigned int GetPackageCount()
    { return m_objDb->GetPackageCount(); }

  PObjectDatabase GetObjectDatabase()
    { return m_objDb; }


  // Servicios específicos, no definidos en DataObservable
  void        SetClipboardObject(PObjectBase obj) { m_clipboard = obj; }
  PObjectBase GetClipboardObject()                { return m_clipboard; }

  string GetProjectFileName() { return m_projectFile; }
};



#endif //__APP_DATA__
