// Scintilla source code edit control
// PlatWX.cxx - implementation of platform facilities on wxWidgets
// Copyright 1998-1999 by Neil Hodgson <neilh@scintilla.org>
//                        Robin Dunn <robin@aldunn.com>
// The License.txt file describes the conditions under which this software may be distributed.

#ifndef PLATWX_H
#define PLATWX_H

#ifdef SCI_NAMESPACE
namespace Scintilla
{
#endif
wxRect wxRectFromPRectangle(PRectangle prc);
PRectangle PRectangleFromwxRect(wxRect rc);
wxColour wxColourFromCA(const ColourAllocated& ca);
#ifdef SCI_NAMESPACE
}
#endif
#endif
