/*=========================================================================

  Program:   ParaView
  Module:    vtkPVSourceList.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

Copyright (c) 2000-2001 Kitware Inc. 469 Clifton Corporate Parkway,
Clifton Park, NY, 12065, USA.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

 * Neither the name of Kitware nor the names of any contributors may be used
   to endorse or promote products derived from this software without specific 
   prior written permission.

 * Modified source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
// .NAME vtkPVSourceList
// .SECTION Description
// This is the UI for the Assembly browser / editor.

#ifndef __vtkPVSourceList_h
#define __vtkPVSourceList_h

#include "vtkPVSourcesNavigationWindow.h"

class vtkKWEntry;
class vtkPVSource;
class vtkPVSourceCollection;
class vtkKWMenu;

class VTK_EXPORT vtkPVSourceList : public vtkPVSourcesNavigationWindow
{
public:
  static vtkPVSourceList* New();
  vtkTypeRevisionMacro(vtkPVSourceList,vtkPVSourcesNavigationWindow);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Callback from the canvas buttons.
  void Pick(int assyIdx);
  void ToggleVisibility(int assyIdx, char* id, int button);
  void EditColor(int assyIdx);

  // Description:
  // This method is called before the object is deleted.
  virtual void PrepareForDelete();
 
protected:
  vtkPVSourceList();
  ~vtkPVSourceList();

  virtual void ChildUpdate(vtkPVSource*, int NoBind);
  virtual void PostChildUpdate();

  // Description:
  // Create a Tk widget
  virtual void ChildCreate();

  int UpdateSource(vtkPVSource *comp, int y, int in, int current, int noBind);
  void UpdateVisibility(vtkPVSource *comp, const char *id);

  // Description:
  // The assembly that is displayed in the editor.
  vtkGetObjectMacro(Sources, vtkPVSourceCollection);
  virtual void SetSources(vtkPVSourceCollection*);
  vtkPVSourceCollection *Sources;

  int StartY;
  int LastY;
  int CurrentY;

private:
  vtkPVSourceList(const vtkPVSourceList&); // Not implemented
  void operator=(const vtkPVSourceList&); // Not implemented
};

#endif


