/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPVServerFileDialog.cxx
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
#include "vtkPVServerFileDialog.h"

#include "vtkPVApplication.h"
#include "vtkPVProcessModule.h"
#include "vtkKWLabel.h"
#include "vtkKWMenuButton.h"
#include "vtkKWPushButton.h"
#include "vtkKWEntry.h"
#include "vtkKWFrame.h"
#include "vtkKWListBox.h"
#include "vtkKWWindow.h"
#include "vtkKWImageLabel.h"
#include "vtkKWIcon.h"
#include "vtkKWMenu.h"
#include "vtkObjectFactory.h"
#include "vtkString.h"
#include "vtkDirectory.h"
#include "vtkIntArray.h"
#include "vtkStringList.h"
#include "vtkKWTkUtilities.h"
#include "vtkKWDirectoryUtilities.h"

//----------------------------------------------------------------------------
vtkStandardNewMacro( vtkPVServerFileDialog );
vtkCxxRevisionMacro(vtkPVServerFileDialog, "1.14");

int vtkPVServerFileDialogCommand(ClientData cd, Tcl_Interp *interp,
                           int argc, char *argv[]);





// Taken from source selection list  we need ne images.
/* 
 * This part was generated by ImageConvert from image:
 *    PVUpDirectoryButton.png (zlib, base64)
 */
#define image_PVUpDirectoryButton_width         16
#define image_PVUpDirectoryButton_height        16
#define image_PVUpDirectoryButton_pixel_size    3
#define image_PVUpDirectoryButton_buffer_length 108

static unsigned char image_PVUpDirectoryButton[] = 
  "eNq7cuHEFbIQAyogqPj/f5AaOIlHCwPRAK4e2WQ8JEQlmmPwaIerR1YMt5qg+ZiuJWg+RJ"
  "B27ocI4nIYVvPxkFjNJyb8SY1i2iEAqg6qMg==";


/* 
 * This part was generated by ImageConvert from image:
 *    PVFolder.png (zlib, base64)
 */
#define image_PVFolder_width         17
#define image_PVFolder_height        17
#define image_PVFolder_pixel_size    3
#define image_PVFolder_buffer_length 448

static unsigned char image_PVFolder[] = 
  "eNr7/59+4MxMk9MzjE9OMzw+Rf/+/fvfvn0jqB6Ze6hf68SJE3h0wdTPREL/93ap7mpX2t"
  "4iv7VJdnOj9IY6CaDV379/h2gBuuf/94n/v/ShIFSwrkasp6fn3r17EC7Q/f9ft/5/1nh0"
  "ki4aOtCrsadTZUerwpZGGaBdQAS0C6gF6N//D6qBCvD59lkjkFhcyA20C8gAKb6SD/bRTF"
  "zox9EEILkgjyMvLw8SPv/PpIN8BJQFegober8nHCg7L4ctNzcXqAXoYKAWsMNmgjyFDT3b"
  "7AeUnZPFAtECDE+glv096iAtD6qxojsrXYCyszKYIFqA4Q/UAgwWkJYr+VjR5QXWQNmZ6Y"
  "wQvwDDDR5fwPBfXSm8okxgaTEvMHyA/gW6H+geoPlA9T4+Ps3NzUAtwIQBTB5Adi4hAFQD"
  "VAkJdaAuoF3XCAFikisuAADhFaXg";

/* 
 * This part was generated by ImageConvert from image:
 *    PVDocument.png (zlib, base64)
 */
#define image_PVDocument_width         17
#define image_PVDocument_height        17
#define image_PVDocument_pixel_size    3
#define image_PVDocument_buffer_length 176

static unsigned char image_PVDocument[] = 
  "eNqd0sENgCAMBdAeu4+zdB9O7sBMcHYFxqgFYiS1FOJPA8b0pWBk/pPTTYzRJKVcsxJCRF"
  "/inKFPUWpJ6IkiznUQMaVkEoDI+ZBVlRB1tpGY5RDzLvLRVgQCQH/f9yWp/a217m3dmMLv"
  "FHkK4JPZDzAj6MYkyyiSNzIS2k7vvwHIB2gH";



// This constant must be adjusted to be the largest width of the icons
// to be used on the left size of a label.

#define image_icon_max_width         image_PVFolder_width






//----------------------------------------------------------------------------
vtkPVServerFileDialog::vtkPVServerFileDialog()
{
  this->CommandFunction = vtkPVServerFileDialogCommand;
  
  this->TopFrame = vtkKWWidget::New();
  this->MiddleFrame = vtkKWFrame::New();
  this->FileList = vtkKWWidget::New();
  this->BottomFrame = vtkKWWidget::New();

  this->DirectoryDisplay = vtkKWLabel::New();
  this->DirectoryMenuButton = vtkKWMenuButton::New();  

  this->DownDirectoryButton = vtkKWImageLabel::New();
  this->DownDirectoryIcon = vtkKWIcon::New();
  this->DownDirectoryIcon->SetImageData(image_PVUpDirectoryButton, 
                    image_PVUpDirectoryButton_width,
                    image_PVUpDirectoryButton_height,
                    image_PVUpDirectoryButton_pixel_size,
                    image_PVUpDirectoryButton_buffer_length);

  this->FileNameLabel = vtkKWLabel::New();
  this->FileNameEntry = vtkKWEntry::New();
  this->FileNameMenuButton = vtkKWMenuButton::New();

  this->ExtensionsLabel = vtkKWLabel::New();
  this->ExtensionsDisplayFrame = vtkKWWidget::New();
  this->ExtensionsDisplay = vtkKWLabel::New();
  this->ExtensionsMenuButton = vtkKWMenuButton::New();

  this->LoadSaveButton = vtkKWPushButton::New();
  this->CancelButton = vtkKWPushButton::New();

  this->MasterWindow = 0;

  this->SelectBoxId = NULL;
  this->SelectedDirectory = NULL;

  this->FileTypeStrings = vtkStringList::New();
  this->FileTypeDescriptions = vtkStringList::New();
  this->ExtensionStrings = vtkStringList::New();

  this->ScrollBar = vtkKWWidget::New();
}

//----------------------------------------------------------------------------
vtkPVServerFileDialog::~vtkPVServerFileDialog()
{
  this->TopFrame->Delete();
  this->TopFrame = NULL;
  this->MiddleFrame->Delete();
  this->MiddleFrame = NULL;
  this->FileList->Delete();
  this->FileList = NULL;
  this->BottomFrame->Delete();
  this->BottomFrame = NULL;

  this->DirectoryDisplay->Delete();
  this->DirectoryDisplay = NULL;
  this->DirectoryMenuButton->Delete();
  this->DirectoryMenuButton = NULL; 

  this->DownDirectoryButton->Delete();
  this->DownDirectoryButton = NULL;
  this->DownDirectoryIcon->Delete();
  this->DownDirectoryIcon = NULL;

  this->FileNameLabel->Delete();
  this->FileNameLabel = NULL;
  this->FileNameEntry->Delete();
  this->FileNameEntry = NULL;
  this->FileNameMenuButton->Delete();
  this->FileNameMenuButton = NULL;

  this->ExtensionsLabel->Delete();
  this->ExtensionsLabel = NULL;
  this->ExtensionsDisplayFrame->Delete();
  this->ExtensionsDisplayFrame = NULL;
  this->ExtensionsDisplay->Delete();
  this->ExtensionsDisplay = NULL;
  this->ExtensionsMenuButton->Delete();
  this->ExtensionsMenuButton = NULL;

  this->LoadSaveButton->Delete();
  this->LoadSaveButton = NULL;
  this->CancelButton->Delete();
  this->CancelButton = NULL;

  this->SetMasterWindow(0);
  
  this->SetSelectBoxId(NULL);

  this->FileTypeStrings->Delete();
  this->FileTypeStrings = NULL;

  this->FileTypeDescriptions->Delete();
  this->FileTypeDescriptions = NULL;

  this->ExtensionStrings->Delete();
  this->ExtensionStrings = NULL;

  if (this->ScrollBar)
    {
    this->ScrollBar->Delete();
    }
}

//----------------------------------------------------------------------------
void vtkPVServerFileDialog::SetMasterWindow(vtkKWWindow* win)
{
  if (this->MasterWindow != win) 
    { 
    if (this->MasterWindow) 
      { 
      this->MasterWindow->UnRegister(this); 
      }
    this->MasterWindow = win; 
    if (this->MasterWindow) 
      { 
      this->MasterWindow->Register(this); 
      if (this->Application)
        {
        this->Script("wm transient %s %s", this->GetWidgetName(), 
                     this->MasterWindow->GetWidgetName());
        }
      } 
    this->Modified(); 
    }   
}

//----------------------------------------------------------------------------
void vtkPVServerFileDialog::Create(vtkKWApplication *app, const char *args)
{
  const char *wname;
  
  // must set the application
  if (this->Application)
    {
    vtkErrorMacro("Server file dialog already created");
    return;
    }
  
  this->SetApplication(app);

  // create the top level
  wname = this->GetWidgetName();
  if (this->MasterWindow)
    {
    this->Script("toplevel %s -class %s", 
                 wname, 
                 this->MasterWindow->GetClassName());
    }
  else
    {
    this->Script("toplevel %s", wname);
    }

  if (this->SaveDialog)
    {
    this->SetTitle("ParaView Save File");
    }
  else
    {
    this->SetTitle("ParaView Load File");
    }
  this->Script("wm title %s \"%s\"", wname, this->Title);
  this->Script("wm iconname %s \"vtk\"", wname);
  if (this->MasterWindow)
    {
    this->Script("wm transient %s %s", wname, 
                 this->MasterWindow->GetWidgetName());
    }


  this->Script("wm protocol %s WM_DELETE_WINDOW {%s CancelCallback}",
               wname, this->GetTclName());
    
  this->TopFrame->SetParent(this);
  this->TopFrame->Create(app, "frame", "");
  this->Script("grid %s -column 0 -row 0 -padx 2m -sticky ew",
               this->TopFrame->GetWidgetName());

  this->MiddleFrame->SetParent(this);
  this->MiddleFrame->Create(app, " ");
  this->Script("grid %s -column 0 -row 1 -padx 2m -sticky ewns",
               this->MiddleFrame->GetWidgetName());

  this->FileList->SetParent(this->MiddleFrame); 
  this->FileList->Create(app, "canvas", "-background white -bd 2 -relief sunken"); 
  this->Script("pack %s -fill both -expand 1",
               this->FileList->GetWidgetName());

  this->Script("grid %s -row 0 -column 0 -sticky news", 
               this->FileList->GetWidgetName());
  this->Script("grid columnconfig %s 0 -weight 1", 
               this->MiddleFrame->GetWidgetName());
  this->Script("grid rowconfig %s 0 -weight 1", 
               this->MiddleFrame->GetWidgetName());

  // Scrollbar
  ostrstream command;
  this->ScrollBar->SetParent(this->MiddleFrame);
  command << "-command \"" <<  this->FileList->GetWidgetName()
          << " yview\"" << ends;
  char* commandStr = command.str();
  this->ScrollBar->Create(this->Application, "scrollbar", commandStr);
  delete[] commandStr;
  this->Script("%s configure -yscrollcommand \"%s set\"", 
               this->FileList->GetWidgetName(),
               this->ScrollBar->GetWidgetName());
  this->FileList->SetBind(this, "<Configure>", "Reconfigure");


  this->BottomFrame->SetParent(this);
  this->BottomFrame->Create(app, "frame", "");
  this->Script("grid %s -column 0 -row 2 -pady 1m  -padx 2m -sticky ew",
               this->BottomFrame->GetWidgetName());

  // Make the file list the only row which resizes.
  this->Script("grid rowconfigure %s 1 -weight 1 -minsize 250",
               this->GetWidgetName());
  // Resize all horizontally.
  this->Script("grid columnconfigure %s 0 -weight 1 -minsize 500",
               this->GetWidgetName());

  this->DirectoryDisplay->SetParent(this->TopFrame);
  this->DirectoryDisplay->Create(app, "-background white -bd 2 -relief sunken");
  this->Script("grid %s -row 0 -column 0 -pady 2m -sticky news",
               this->DirectoryDisplay->GetWidgetName());

  this->DownDirectoryButton->SetParent(this->TopFrame);
  this->DownDirectoryButton->Create(app, "");
  this->DownDirectoryButton->SetImageData(this->DownDirectoryIcon);
  this->DownDirectoryButton->SetBalloonHelpString("Up One Level");
  this->Script("bind %s <ButtonRelease-1> { %s DownDirectoryCallback}",
               this->DownDirectoryButton->GetWidgetName(),
               this->GetTclName());

  this->Script("grid %s -row 0 -column 1 -pady 2m -padx 5m -sticky news",
               this->DownDirectoryButton->GetWidgetName());
  this->Script("grid columnconfigure %s 0 -weight 1",
               this->TopFrame->GetWidgetName());


  this->FileNameLabel->SetParent(this->BottomFrame);
  this->FileNameLabel->SetLabel("File name:");
  this->FileNameLabel->Create(app, "");
  this->Script("grid %s -row 0 -column 0 -sticky w", 
               this->FileNameLabel->GetWidgetName());

  this->FileNameEntry->SetParent(this->BottomFrame);
  this->FileNameEntry->Create(app, "");
  this->Script("grid %s -row 0 -column 1 -sticky ew -padx 5m", 
               this->FileNameEntry->GetWidgetName());

  this->LoadSaveButton->SetParent(this->BottomFrame);
  this->LoadSaveButton->Create(app, "");
  this->LoadSaveButton->SetCommand(this, "LoadSaveCallback");

  if (this->SaveDialog)
    {
    this->LoadSaveButton->SetLabel("Save");
    }
  else
    {
    this->LoadSaveButton->SetLabel("Open");
    }
  this->Script("grid %s -row 0 -column 2 -sticky ew -ipadx 2m", 
               this->LoadSaveButton->GetWidgetName());


  this->ExtensionsLabel->SetParent(this->BottomFrame);
  if (this->SaveDialog)
    {
    this->ExtensionsLabel->SetLabel("Save as type:");
    }
  else
    {
    this->ExtensionsLabel->SetLabel("Load type:");
    }
  this->ExtensionsLabel->Create(app, "");
  this->Script("grid %s -row 1 -column 0 -sticky w", 
               this->ExtensionsLabel->GetWidgetName());

  this->ExtensionsDisplayFrame->SetParent(this->BottomFrame);
  this->ExtensionsDisplayFrame->Create(app, "frame", "-bd 2 -relief sunken");
  this->Script("grid %s -row 1 -column 1  -sticky ew -padx 5m", 
               this->ExtensionsDisplayFrame->GetWidgetName());
  this->ExtensionsDisplay->SetParent(this->ExtensionsDisplayFrame);
  this->ExtensionsDisplay->Create(app, "-background white");
  this->Script("pack %s -side left -expand 1 -fill both",
               this->ExtensionsDisplay->GetWidgetName());
  this->ExtensionsMenuButton->SetParent(this->ExtensionsDisplayFrame);
  this->ExtensionsMenuButton->GetMenu()->SetTearOff(0);
  this->ExtensionsMenuButton->Create(app, "");
  this->ExtensionsMenuButton->SetButtonText("");
  this->Script("pack %s -side left -expand 0", 
               this->ExtensionsMenuButton->GetWidgetName());

  this->CancelButton->SetParent(this->BottomFrame);
  this->CancelButton->Create(app, "-pady 0");
  this->CancelButton->SetCommand(this, "CancelCallback");
  this->CancelButton->SetLabel("Cancel");
  this->Script("grid %s -row 1 -column 2 -sticky ew -ipadx 2m", 
               this->CancelButton->GetWidgetName());

  this->Script("grid columnconfigure %s 1 -weight 1",
               this->BottomFrame->GetWidgetName());

  this->Script("wm withdraw %s", wname);


  // Icons
  ostrstream folder;
  folder << this->GetWidgetName() << ".folderimg" << ends;
  if (!vtkKWTkUtilities::UpdatePhoto(this->Application->GetMainInterp(),
                                     folder.str(), 
                                     image_PVFolder, 
                                     image_PVFolder_width, 
                                     image_PVFolder_height, 
                                     image_PVFolder_pixel_size,
                                     image_PVFolder_buffer_length,
                                     this->FileList->GetWidgetName()))
    {
    vtkWarningMacro(<< "Error creating photo (eye open)");
    }
  folder.rdbuf()->freeze(0);

  ostrstream document;
  document << this->GetWidgetName() << ".documentimg" << ends;
  if (!vtkKWTkUtilities::UpdatePhoto(this->Application->GetMainInterp(),
                                     document.str(), 
                                     image_PVDocument, 
                                     image_PVDocument_width, 
                                     image_PVDocument_height, 
                                     image_PVDocument_pixel_size,
                                     image_PVDocument_buffer_length,
                                     this->FileList->GetWidgetName()))
    {
    vtkWarningMacro(<< "Error creating photo (eye gray)");
    }
  document.rdbuf()->freeze(0);

}

//----------------------------------------------------------------------------
int vtkPVServerFileDialog::Invoke()
{   
  // Get rid of back slashes.
  this->ConvertLastPath();

  this->Application->SetDialogUp(1);
  this->UpdateExtensionsMenu();
  // Side effect of UpdateExtensionsMenu is to Update.
  //this->Update();

  this->Script("wm deiconify %s", this->GetWidgetName());
  this->Script("grab %s", this->GetWidgetName());

  this->Done = 0;
  while ( ! this->Done)
    {
    this->Script("after 100; update");
    }
  this->Application->SetDialogUp(0);
  return this->ReturnValue;
}


//----------------------------------------------------------------------------
void vtkPVServerFileDialog::ConvertLastPath()
{  
  int max = 1000; 
  char *p;

  if (this->LastPath == NULL)
    {
    return;
    }
  p = this->LastPath;
  while (*p != '\0' && max > 0)
    {
    if (*p == '\\')
      {
      *p = '/';
      }
    --max;
    ++p;
    }
}

//----------------------------------------------------------------------------
void vtkPVServerFileDialog::LoadSaveCallback()
{
  int last;
  const char* dir;
  dir = this->DirectoryDisplay->GetLabel();
  last = static_cast<int>(strlen(dir))-1;

  if (this->SelectedDirectory)
    {
    ostrstream newdir;
    if (last >= 0 && dir[last] == '/')
      { // special case for root. Avoid "//" in path.
      newdir << dir << this->SelectedDirectory << ends;
      }
    else
      {
      newdir << dir << "/" << this->SelectedDirectory << ends;
      }
    this->SetLastPath(newdir.str());
    this->ConvertLastPath();
    this->Update();
    newdir.rdbuf()->freeze(0);
    return;
    } 

  ostrstream fullpath;
  if (last >= 0 && dir[last] == '/')
    { // special case for root. Avoid "//" in path.
    fullpath << dir << this->FileNameEntry->GetValue() << ends;
    }
  else
    {
    fullpath << dir << "/" << this->FileNameEntry->GetValue() << ends;
    }
  this->SetFileName(fullpath.str());
  fullpath.rdbuf()->freeze(0);
   
  this->Done = 1;
  this->Script("grab release %s", this->GetWidgetName());
  this->Script("wm withdraw %s", this->GetWidgetName());
  this->ReturnValue = 1;
}

//----------------------------------------------------------------------------
void vtkPVServerFileDialog::CancelCallback()
{
  this->Done = 1;
  this->Script("grab release %s", this->GetWidgetName());
  this->Script("wm withdraw %s", this->GetWidgetName());
  this->ReturnValue = 0;
}

//----------------------------------------------------------------------------
void vtkPVServerFileDialog::DownDirectoryCallback()
{
  char *newdir;
  char *p;
  char *last;
  int count = 0;

  newdir = new char[strlen(this->LastPath) + 1];
  strcpy(newdir, this->LastPath);

  p = newdir;
  while (*p != '\0')
    {
    if (*p == '/')
      {
      last = p;
      count++;
      }
    ++p;
    }
  
  // Do not remove the last slash.
  if (count > 1)
    {
    *last = '\0';
    this->SetLastPath(newdir);
    }
  if (count == 1)
    {
    last[1] = '\0';
    this->SetLastPath(newdir);
    }
  // If count == 0;
  // already at top level.
  // what to do about switching disks?
  delete [] newdir;
  this->Update();
}

//----------------------------------------------------------------------------
void vtkPVServerFileDialog::ExtensionsMenuButtonCallback(int typeIdx)
{
  char *extensions;
  char *extensionsCopy;
  char *ptr;
  char *extensionStart;
  
  extensions = this->FileTypeStrings->GetString(typeIdx);

  // Make a copy of the extensions string 
  // so we can change characters while we parse.
  extensionsCopy = new char[strlen(extensions) + 1];
  strcpy(extensionsCopy, extensions);

  // Clear previous extensions.
  this->ExtensionStrings->RemoveAllItems();

  // Find the first extension after the parenthesis.
  ptr = extensionsCopy;
  while (*ptr != '(')
    {
    if (*ptr == '\0')
      {
      delete [] extensionsCopy;
      this->Update();
      return;
      }
    ++ptr;
    }
  // Pass the parenthesis.
  ++ptr;

  while (*ptr != ')' && *ptr != '\0')
    {
    // Since we formated the string, we know that extensions always start with "*."
    // But, lets be general and handle spaces.
    while (*ptr == ' ')
      {
      ++ptr;
      }
    if (ptr[0] != '*' && ptr[1] != '.')
      {
      vtkErrorMacro("All extensions should start with *.");
      delete [] extensionsCopy;
      this->Update();
      return;
      }
    ptr += 2;
  
    extensionStart = ptr;
    while (*ptr != ';' && *ptr != ')') 
      {
      if (*ptr == '\0')
        { // Handle unexpected end of string properly.
        delete [] extensionsCopy;
        this->Update();
        return;
        }
      ++ptr;
      }
    // Add end of string character to terminate extension.
    *ptr = '\0';
    ++ptr;
    // Add extension to the extension list.
    this->ExtensionStrings->AddString(extensionStart);
    }

  delete [] extensionsCopy;

  ostrstream label;
  label << this->FileTypeDescriptions->GetString(typeIdx) << " ";
  if (this->ExtensionStrings->GetNumberOfStrings() <= 1)
    {
    label << extensions;
    }
  label << ends;

  this->ExtensionsDisplay->SetLabel(label.str());
  label.rdbuf()->freeze(0);
  
  this->Update();
}


//----------------------------------------------------------------------------
void vtkPVServerFileDialog::UpdateExtensionsMenu()
{
  int extensionsFinished, extensionCount;
  int typesFinished;
  int typeIdx;
  char methodAndArgString[256];
  char* ptr1;
  char* fileTypeDescription;
  char* fileExtension;
  char* fileTypesCopy;

  if (this->FileTypes == NULL)
    {
    return;
    }
  this->FileTypeStrings->RemoveAllItems();

  // Make a copy of the file type so we can modify the string.
  fileTypesCopy = new char[strlen(this->FileTypes) + 1];
  strcpy(fileTypesCopy, this->FileTypes);
  this->ExtensionsMenuButton->GetMenu()->DeleteAllMenuItems();

  ptr1 = fileTypesCopy;

  char separator;
#ifdef _WIN32
  separator = ';';
#else
  separator = ' ';
#endif
  
  typesFinished = 0;
  typeIdx = 0;
  while ( ! typesFinished)
    {
    ostrstream label;
    ostrstream extensions;
    // Take off first and second Parenthesis for type.
    while (*ptr1 == ' ' || *ptr1 == '{')
      {
      ++ptr1;
      }
    fileTypeDescription = ptr1;
    // find end of file type description (paren).
    while ( ! typesFinished && *ptr1 != '}')
      {
      if (*ptr1 == '\0')
        { // No more types.
        typesFinished = 1;
        }
      else
        {
        ++ptr1;
        }
      }
    // Put a end of string character to terminate the fileTypeDescription.
    // It overwrites the parenthesis.
    *ptr1 = '\0';
    ++ptr1; // Skip the string termination we put in.
    // Put the file type in the new string/description/label.
    label << fileTypeDescription << " (";
    extensions << "(";

    // Pick out all of the extensions.
    extensionsFinished = 0;
    extensionCount = 0;
    while ( ! typesFinished && ! extensionsFinished)
      {
      // Find the start of the first extension.
      while ( ! extensionsFinished && 
             (*ptr1==' ' || *ptr1=='{' || *ptr1=='.' || *ptr1=='*'))
        {
        if (*ptr1 == '\0' || *ptr1 == '}' )
          {
          extensionsFinished = 1;
          }
        ++ptr1;
        }
      fileExtension = ptr1;
      // Now find the end of the extension
      while ( ! extensionsFinished && *ptr1!='}' && *ptr1!= separator )
        {
        if (*ptr1 == '\0')
          {
          extensionsFinished = 1;
          }
        ++ptr1;
        }
      if ( ! extensionsFinished)
        {
        if (*ptr1 == '}')
          { // last extension.
          extensionsFinished = 1;
          }
        // Record the extension
        *ptr1 = '\0';
        ++ptr1; // Skip the string termination we put in.
        if (extensionCount > 0)
          {
          if (extensionCount < 3)
            { // hack to get "..."
            label << ";";
            }
          if (extensionCount == 3)
            {
            label << "...";
            }
          extensions << ";";
          }
        if (fileExtension[0] == '\0')
          { // special case happens with "all files" "*.*".  
          // Will also happen with an empty list which I do not think is valid.
          if (extensionCount < 2)
            { // hack to get "..."
            label << "*.*";
            }
          extensions << "*.*";
          }
        else
          {
          if (extensionCount < 2)
            { // hack to get "..."
            label << "*." << fileExtension;
            }
           extensions << "*." << fileExtension;
          }
        ++extensionCount;
        }
      }
    // Pass the last bracket for type
    while ( ! typesFinished && *ptr1 != '}')
      {
      if ( *ptr1 == '\0')
        {
        vtkErrorMacro("Missing last type bracket.");
        typesFinished = 1;
        }
      ++ptr1;
      }
    ++ptr1;
    
    if ( ! typesFinished)
      {
      label << ")" << ends;
      extensions << ")" << ends;
      sprintf(methodAndArgString, "ExtensionsMenuButtonCallback %d", typeIdx);
      this->ExtensionsMenuButton->GetMenu()->AddCommand(label.str(), this,
                                                        methodAndArgString);
      this->FileTypeStrings->AddString(extensions.str());
      this->FileTypeDescriptions->AddString(fileTypeDescription);
      ++typeIdx;
      }
    label.rdbuf()->freeze(0);
    extensions.rdbuf()->freeze(0);
    }

  // Default file type is the first in the list.
  if (typeIdx > 0)
    {
    this->ExtensionsMenuButtonCallback(0);
    }

  if (fileTypesCopy)
    {
    delete [] fileTypesCopy;
    fileTypesCopy = NULL;
    }
}



//----------------------------------------------------------------------------
int vtkPVServerFileDialog::CheckExtension(const char* name)
{
  int num;
  int idx;
  const char *nameExt;
  const char* ptr;
  char *ext;

  if (name == NULL)
    {
    return 0;
    }

  num = this->ExtensionStrings->GetNumberOfStrings();
  if (num == 0)
    { // No extensions?  Pass all.
    return 1;
    }

  // Find the extension in the name.
  nameExt = NULL;
  ptr = name;
  while (*ptr != '\0')
    {
    if (*ptr == '.')
      {
      nameExt = ptr + 1;
      }
    ++ptr;
    }
  if (nameExt == NULL || *nameExt == '\0')
    {
    return 0;
    }

  for (idx = 0; idx < num; ++idx)
    {
    ext = this->ExtensionStrings->GetString(idx);
    if (strcmp(ext, "*") == 0)
      { // special case for All Files wild card.
      return 1;
      }
    if (strcmp(nameExt, ext) == 0)
      {
      return 1;
      }
    }

  return 0;
}

//----------------------------------------------------------------------------
vtkPVApplication* vtkPVServerFileDialog::GetPVApplication()
{
  return vtkPVApplication::SafeDownCast(this->Application);
}

//----------------------------------------------------------------------------
void vtkPVServerFileDialog::Update()
{
  vtkStringList* dirs = vtkStringList::New();
  vtkStringList* files = vtkStringList::New();
  const char* perm = "readable";
  if(this->SaveDialog)
    {
    perm = "writable";
    }
  
  // Make sure we have a directory.
  if(!this->LastPath)
    {    
    this->GetPVApplication()->GetProcessModule()->RootScript("pwd");
    char* result = this->GetPVApplication()->GetProcessModule()->NewRootResult();
    this->SetLastPath(result);
    this->ConvertLastPath();
    delete [] result;
    }

  // Read the list of subdirectories and files.
  if(!(this->GetPVApplication()->GetProcessModule()
       ->GetDirectoryListing(this->LastPath, dirs, files, perm)))
    {
    // Directory did not exist, use current directory instead.
    vtkErrorMacro("Cannot open directory: " << this->LastPath);
    this->GetPVApplication()->GetProcessModule()->RootScript("pwd");
    char* result = this->GetPVApplication()->GetProcessModule()->NewRootResult();
    this->SetLastPath(result);
    this->ConvertLastPath();
    delete [] result;
    
    // We will now succeed.
    this->GetPVApplication()->GetProcessModule()
      ->GetDirectoryListing(this->LastPath, dirs, files, perm);
    }
  
  this->Script("%s delete all", this->FileList->GetWidgetName());
  this->SetSelectBoxId(NULL);
  this->DirectoryDisplay->SetLabel(this->LastPath);
  
  // Construct the gui representation.
  int y = 10;
  int dirsLen = dirs->GetLength();
  int i;
  for(i=0; i < dirsLen; ++i)
    {
    y = this->Insert(dirs->GetString(i), y, 1);
    }
  int filesLen = files->GetLength();
  for(i=0; i < filesLen; ++i)
    {
    const char* name = files->GetString(i);
    if(this->CheckExtension(name))
      {
      y = this->Insert(name, y, 0);
      }
    }
  
  files->Delete();
  dirs->Delete();

  this->Reconfigure();
}


//----------------------------------------------------------------------------
int vtkPVServerFileDialog::Insert(const char* name, int y, int directory)
{
  int x=10;
  int yNext = y+17;
  static const char *font = "-adobe-helvetica-medium-r-normal-*-14-100-100-100-p-76-iso8859-1";
  char *result = 0;
  char *tmp;

  // Create an image on the left of the label.
  this->Script("%s create image %d %d", this->FileList->GetWidgetName(), 
               x + image_icon_max_width / 2, y);
  if (this->Application->GetMainInterp()->result)
    {
    char *tmp = 
      vtkString::Duplicate(this->Application->GetMainInterp()->result);
    if (directory)
      {
      this->Script("%s bind %s <ButtonPress-1> {%s SelectDirectory {%s} %s}",
                   this->FileList->GetWidgetName(), tmp,
                   this->GetTclName(), name, tmp);
      this->Script("%s bind %s <Double-ButtonPress-1> {%s SelectDirectory {%s} %s; %s LoadSaveCallback}",
                   this->FileList->GetWidgetName(), tmp,
                   this->GetTclName(), name, tmp, this->GetTclName());
      this->Script("%s itemconfigure %s -image %s.folderimg",
                   this->FileList->GetWidgetName(), tmp, 
                   this->GetWidgetName());
      }
    else
      {
      this->Script("%s bind %s <ButtonPress-1> {%s SelectFile {%s} %s}",
                   this->FileList->GetWidgetName(), tmp,
                   this->GetTclName(), name, tmp);
      this->Script("%s bind %s <Double-ButtonPress-1> {%s SelectFile {%s} %s; %s LoadSaveCallback}",
                   this->FileList->GetWidgetName(), tmp,
                   this->GetTclName(), name, tmp, this->GetTclName());
      this->Script("%s itemconfigure %s -image %s.documentimg",
                   this->FileList->GetWidgetName(), tmp, 
                   this->GetWidgetName());
      }
    delete [] tmp;
    }

  // Add some space between the icon and the label

  x += image_icon_max_width + 4;

  // Draw the name of the file.
  this->Script("%s create text %d %d -text {%s} -font %s -anchor w -tags x",
               this->FileList->GetWidgetName(), x, y, name, font);

  // Make the name hot for picking.
  result = this->Application->GetMainInterp()->result;
  tmp = new char[strlen(result)+1];
  strcpy(tmp,result);
  if (directory)
    {
    this->Script("%s bind %s <ButtonPress-1> {%s SelectDirectory {%s} %s}",
                 this->FileList->GetWidgetName(), tmp,
                 this->GetTclName(), name, tmp);
    this->Script("%s bind %s <Double-ButtonPress-1> {%s SelectDirectory {%s} %s; %s LoadSaveCallback}",
                 this->FileList->GetWidgetName(), tmp,
                 this->GetTclName(), name, tmp, this->GetTclName());
    }
  else
    {
    this->Script("%s bind %s <ButtonPress-1> {%s SelectFile {%s} %s}",
                 this->FileList->GetWidgetName(), tmp,
                 this->GetTclName(), name, tmp);
    this->Script("%s bind %s <Double-ButtonPress-1> {%s SelectFile {%s} %s; %s LoadSaveCallback}",
                 this->FileList->GetWidgetName(), tmp,
                 this->GetTclName(), name, tmp, this->GetTclName());
    }
          
  return yNext;
}

  
//----------------------------------------------------------------------------
void vtkPVServerFileDialog::SelectFile(const char* name, const char* id)
{
  int bbox[4];
  const char* result;

  if (this->SelectBoxId)
    {
    this->Script("%s delete %s", this->FileList->GetWidgetName(), this->SelectBoxId);
    this->SetSelectBoxId(NULL);
    }

  // Get the bounding box for the name. We need to highlight it.
  this->Script( "%s bbox %s",this->FileList->GetWidgetName(), id);
  result = this->Application->GetMainInterp()->result;
  sscanf(result, "%d %d %d %d", bbox, bbox+1, bbox+2, bbox+3);

  this->Script("%s create rectangle %d %d %d %d -fill yellow -outline {}",
               this->FileList->GetWidgetName(), 
               bbox[0], bbox[1], bbox[2], bbox[3]);
  this->SetSelectBoxId(this->Application->GetMainInterp()->result);
  this->Script( "%s lower %s",this->FileList->GetWidgetName(), this->SelectBoxId);

  this->FileNameEntry->SetValue(name);

  this->SetSelectedDirectory(NULL);
}

//----------------------------------------------------------------------------
void vtkPVServerFileDialog::SelectDirectory(const char* name, const char* id)
{
  int bbox[4];
  const char* result;

  if (this->SelectBoxId)
    {
    this->Script("%s delete %s", this->FileList->GetWidgetName(), this->SelectBoxId);
    this->SetSelectBoxId(NULL);
    }

  // Get the bounding box for the name. We need to highlight it.
  this->Script( "%s bbox %s",this->FileList->GetWidgetName(), id);
  result = this->Application->GetMainInterp()->result;
  sscanf(result, "%d %d %d %d", bbox, bbox+1, bbox+2, bbox+3);

  this->Script("%s create rectangle %d %d %d %d -fill yellow -outline {}",
               this->FileList->GetWidgetName(), 
               bbox[0], bbox[1], bbox[2], bbox[3]);
  this->SetSelectBoxId(this->Application->GetMainInterp()->result);
  this->Script( "%s lower %s",this->FileList->GetWidgetName(), this->SelectBoxId);

  this->FileNameEntry->SetValue("");
  this->SetSelectedDirectory(name);
}


//-----------------------------------------------------------------------------
void vtkPVServerFileDialog::Reconfigure()
{
  int bbox[4];
  this->CalculateBBox(this->FileList, "all", bbox);
  int height = atoi(this->Script("winfo height %s", 
                                 this->FileList->GetWidgetName()));
  if (height > 1 && (bbox[3] - bbox[1]) > height)
    {
    this->Script("grid %s -row 0 -column 1 -sticky news", 
                 this->ScrollBar->GetWidgetName());
    }
  else
    {
    this->Script("grid remove %s", this->ScrollBar->GetWidgetName());
    }
  // You don't want to stick the visible part right at the border of the
  // canvas, but let some space (2 pixels on top and left)
  this->Script("%s configure -scrollregion \"%d %d %d %d\"", 
               this->FileList->GetWidgetName(), 
               bbox[0] - 2, bbox[1] - 2, bbox[2], bbox[3]);
  //this->PostChildUpdate();
}

//-----------------------------------------------------------------------------
void vtkPVServerFileDialog::CalculateBBox(vtkKWWidget* canvas, 
                                          const char* name, 
                                          int bbox[4])
{
  const char *result;
  // Get the bounding box for the name. We may need to highlight it.
  result = this->Script("%s bbox %s", canvas->GetWidgetName(), name);
  if(sscanf(result, "%d %d %d %d", bbox, bbox+1, bbox+2, bbox+3) < 4)
    {
    // There are no objects in the canvas.  Create a fake bounding
    // box.
    bbox[0] = 0;
    bbox[1] = 0;
    bbox[2] = 1;
    bbox[3] = 1;
    }
}


//----------------------------------------------------------------------------
void vtkPVServerFileDialog::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);  
}
