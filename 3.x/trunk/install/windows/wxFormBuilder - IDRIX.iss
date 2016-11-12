;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
; File:        wxFormBuilder.iss
; Author:      Ryan Pusztai & Ryan Mulder
; Date:        02/07/2006
; Copyright:   (c) 2007 Ryan Pusztai <rpusztai@gmail.com>
;              (c) 2007 Ryan Mulder <rjmyst3@gmail.com>
; License:     wxWindows license
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



[Setup]
AppName=wxFormBuilder (IDRIX Build)
AppVerName=wxFormBuilder 3.5.2-4RC2 (IDRIX Build)
AppPublisher=IDRIX
AppPublisherURL=https://www.idrix.fr
AppSupportURL=http://wxformbuilder.org
AppUpdatesURL=http://wxformbuilder.org
DefaultDirName={pf}\wxFormBuilder (IDRIX Build)
DisableDirPage=false
DefaultGroupName=wxFormBuilder (IDRIX Build)
DisableProgramGroupPage=false
OutputBaseFilename=wxFormBuilder_v3.5.2-4RC2_IDRIX

Compression=lzma/ultra
SolidCompression=true
InternalCompressLevel=ultra
OutputDir=.
ShowLanguageDialog=yes
AppVersion="3.5.2-4RC2"
AppendDefaultGroupName=false
AllowNoIcons=true
WizardImageFile=compiler:WizModernImage-IS.bmp
WizardSmallImageFile=compiler:WizModernSmallImage-IS.bmp
SetupIconFile=support\wxFormBuilder.ico
UninstallDisplayIcon={app}\wxFormBuilder.exe
ChangesAssociations=true
VersionInfoVersion=3.5.2.4
VersionInfoDescription=wxFormBuilder (IDRIX Build)
InfoAfterFile=..\..\output\Changelog.txt
LicenseFile=..\..\output\license.txt
MinVersion=0,5.0
;signtool81 = "C:\Program Files (x86)\Windows Kits\8.1\bin\x86\signtool" $p
SignTool=signtool81 sign /v /a /n IDRIX /i Thawte /ac C:\Dev\Thawt_CodeSigning_CA.crt /fd sha1 /t http://timestamp.verisign.com/scripts/timestamp.dll $f
SignTool=signtool81 sign /v /a /n "IDRIX SARL" /i GlobalSign /ac C:\Dev\GlobalSign_SHA256_EV_CodeSigning_CA.cer /as /fd sha256 /tr http://timestamp.globalsign.com/?signature=sha2 /td SHA256 $f
SignedUninstaller=True

[Messages]
BeveledLabel=wxFormBuilder v3.5.2-4RC2 (IDRIX BUILD)

[Tasks]
Name: desktopicon; Description: {cm:CreateDesktopIcon}; GroupDescription: {cm:AdditionalIcons}; Flags: unchecked

[Files]
Source: ..\..\output\*; DestDir: {app}; Flags: ignoreversion recursesubdirs createallsubdirs; Excludes: .svn\*, .git\*, *.bat, *.cer, *.pdb, *.exp, *.lib, *d.exe, *d.dll, wxmsw30ud_*, wxmsw30umd_*, Thumbs.db, *.a


[Icons]
Name: {group}\wxFormBuilder (IDRIX Build); Filename: {app}\wxFormBuilder.exe
Name: {group}\{cm:UninstallProgram,wxFormBuilder (IDRIX Build)}; Filename: {uninstallexe}
Name: {userdesktop}\wxFormBuilder (IDRIX Build); Filename: {app}\wxFormBuilder.exe; Tasks: desktopicon

[Run]
Filename: {app}\wxFormBuilder.exe; Description: {cm:LaunchProgram,wxFormBuilder (IDRIX Build)}; Flags: nowait postinstall skipifsilent

[Registry]
Root: HKLM; Subkey: SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\wxFormBuilder.exe; ValueType: string; ValueData: {app}\wxFormBuilder.exe; Flags: uninsdeletekey
Root: HKCR; SubKey: .fbp; ValueType: string; ValueData: wxFormBuilder_IDRIX.Project; Flags: uninsdeletekey
Root: HKCR; SubKey: wxFormBuilder_IDRIX.Project\DefaultIcon; ValueType: string; ValueName: ; ValueData: {app}\wxFormBuilder.exe; Flags: uninsdeletekey
Root: HKCR; SubKey: wxFormBuilder_IDRIX.Project; ValueType: string; ValueData: wxFormBuilder (IDRIX Build) Project File; Flags: uninsdeletekey
Root: HKCR; SubKey: wxFormBuilder_IDRIX.Project\Shell\Open\Command; ValueType: string; ValueData: """{app}\wxFormBuilder.exe"" ""%1"""; Flags: uninsdeletevalue







