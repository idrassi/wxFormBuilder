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
/**
 * @file    defs.h
 * @author  Andrea Zanellato (zanellato.andrea@gmail.com)
 * @date    2011/09/07
 * @version 0.0.1
 */
#ifndef __WXFBLIB_DEFS_H__
#define __WXFBLIB_DEFS_H__

#if defined(WXMAKINGLIB_WXFBCORE)
  #define WXDLLIMPEXP_WXFBCORE
#elif defined(WXMAKINGDLL_WXFBCORE)
  #define WXDLLIMPEXP_WXFBCORE WXEXPORT
#elif defined(WXUSINGDLL_WXFBCORE)
  #define WXDLLIMPEXP_WXFBCORE WXIMPORT
#else // not making nor using DLL
  #define WXDLLIMPEXP_WXFBCORE
#endif

#define wxFB_XRC_DIR wxStandardPaths::Get().GetResourcesDir().BeforeLast('/') + wxFILE_SEP_PATH + wxT("wxformbuilder") + wxFILE_SEP_PATH + wxT("xrc")
#define wxFB_XRC_DEFAULTS wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("default.xrc")
#define wxFB_XRC_OBJ_INSP wxFB_XRC_DIR + wxFILE_SEP_PATH + wxT("objinsp.xrc")

#define AppData() ( ApplicationData::Get() )

#endif //__WXFBLIB_DEFS_H__
