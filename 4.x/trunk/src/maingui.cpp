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

#include "maingui.h"
#include "splashscreen.h"
//#include <wx/splash.h>
#include "rad/mainframe.h"
#include "rad/appdata.h"

#include "model/objectbase.h"

#include "utils/debug.h"
#include "utils/typeconv.h"
#include "utils/wxfbexception.h"

#include <memory>

#include <wx/aui/auibook.h>
#include <wx/clipbrd.h>
#include <wx/config.h>
#include <wx/cmdline.h>
#include <wx/filename.h>
#include <wx/image.h>
#include <wx/msgout.h>
#include <wx/stdpaths.h>
#include <wx/sysopt.h>
#include <wx/xrc/xmlres.h>

// Abnormal Termination Handling
#if wxUSE_ON_FATAL_EXCEPTION && wxUSE_STACKWALKER
	#include <wx/stackwalk.h>
	#include <wx/utils.h>
#elif defined(_WIN32) && defined(__MINGW32__)
	#include "dbg_stack_trace/stack.hpp"
	#include <excpt.h>
	#include <sstream>

	EXCEPTION_DISPOSITION StructuredExceptionHandler(	struct _EXCEPTION_RECORD *ExceptionRecord,
																void * EstablisherFrame,
																struct _CONTEXT *ContextRecord,
																void * DispatcherContext );
#endif

void LogStack();

static const wxCmdLineEntryDesc s_cmdLineDesc[] =
{
	{ wxCMD_LINE_SWITCH, "g", "generate", "Generate code from passed file." },
	{ wxCMD_LINE_OPTION, "l", "language", "Override the code_generation property from the passed file and generate the passed languages. Separate multiple languages with commas." },
	{ wxCMD_LINE_SWITCH, "h", "help", "Show this help message.", wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_HELP },
	{ wxCMD_LINE_PARAM, NULL, NULL, "File to open.", wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
	{ wxCMD_LINE_NONE }
};

IMPLEMENT_APP( wxFormBuilderApp )

int wxFormBuilderApp::OnRun()
{
	// Abnormal Termination Handling
#if wxUSE_ON_FATAL_EXCEPTION && wxUSE_STACKWALKER
		::wxHandleFatalExceptions( true );
#elif defined(_WIN32) && defined(__MINGW32__)
		// Structured Exception handlers are stored in a linked list at FS:[0]
		// THIS MUST BE A LOCAL VARIABLE - windows won't use an object outside of the thread's stack frame
		EXCEPTION_REGISTRATION ex;
		ex.handler = StructuredExceptionHandler;
		asm volatile ( "movl %%fs:0, %0" : "=r" ( ex.prev ) );
		asm volatile ( "movl %0, %%fs:0" : : "r" ( &ex ) );
#endif

	// Using a space so the initial 'w' will not be capitalized in wxLogGUI dialogs
	wxApp::SetAppName(" wxFormBuilder");

	// Creating the wxConfig manually so there will be no space
	// The old config (if any) is returned, delete it
	// TODO: make a new wxFormBuilder.layout config file to differ from older versions
	//       and put it in a wxFormBuilder folder to let add different config files (future use)
	//       using wxFileConfig (Windows version will use Documents & Settings instead of registry
	delete wxConfigBase::Set( new wxConfig("wxFormBuilder") );

	// Get the data directory
	wxStandardPathsBase& stdPaths = wxStandardPaths::Get();
	wxString dataDir = stdPaths.GetDataDir();
	dataDir.Replace( GetAppName().c_str(), "wxformbuilder" );

	// Log to stderr while working on the command line
	delete wxLog::SetActiveTarget( new wxLogStderr );

	// Message output to the same as the log target
	delete wxMessageOutput::Set( new wxMessageOutputLog );

    // Load locales
    SelectLanguage( wxLANGUAGE_DEFAULT );

	// Parse command line
	wxCmdLineParser parser( s_cmdLineDesc, argc, argv );
	if ( 0 != parser.Parse() )
	{
		return 1;
	}

	// Get project to load
	wxString projectToLoad = wxEmptyString;
	if ( parser.GetParamCount() > 0 )
	{
		projectToLoad = parser.GetParam();
	}

	bool justGenerate = false;
	wxString language;
	bool hasLanguage = parser.Found( "l", &language );
	if ( parser.Found("g") )
	{
		if ( projectToLoad.empty() )
		{
			wxLogError( _("You must pass a path to a project file. Nothing to generate.") );
			return 2;
		}

		if ( hasLanguage )
		{
			if ( language.empty() )
			{
				wxLogError( _("Empty language option. Nothing generated.") );
				return 3;
			}
			language.Replace( ",", "|", true );
		}

		// generate code
		justGenerate = true;
	}
	else
	{
		delete wxLog::SetActiveTarget( new wxLogGui );
	}

	// Create singleton AppData - wait to initialize until sure that this is not the second
	// instance of a project file.
	AppDataCreate( dataDir );

	// Make passed project name absolute
	try
	{
		if ( !projectToLoad.empty() )
		{
			wxFileName projectPath( projectToLoad );
			if ( !projectPath.IsOk() )
			{
				THROW_WXFBEX( _("This path is invalid: ") << projectToLoad );
			}

			if ( !projectPath.IsAbsolute() )
			{
				if ( !projectPath.MakeAbsolute() )
				{
					THROW_WXFBEX( _("Could not make path absolute: ") << projectToLoad );
				}
			}
			projectToLoad = projectPath.GetFullPath();
		}
	}
	catch ( wxFBException& ex )
	{
		wxLogError( ex.what() );
	}

	// If the project is already loaded in another instance, switch to that instance and quit
	if ( !projectToLoad.empty() && !justGenerate )
	{
		if ( ::wxFileExists( projectToLoad ) )
		{
			if ( !AppData()->VerifySingleInstance( projectToLoad ) )
			{
				return 4;
			}
		}
	}

	// Init handlers
	wxInitAllImageHandlers();
	wxXmlResource::Get()->InitAllHandlers();

	// Init AppData
	try
	{
		AppDataInit();
	}
	catch( wxFBException& ex )
	{
		wxLogError( _("Error loading application: %s\nwxFormBuilder cannot continue."),	ex.what() );
		wxLog::FlushActive();
		return 5;
	}

	wxSystemOptions::SetOption( "msw.remap", 0 );
	wxSystemOptions::SetOption( "msw.staticbox.optimized-paint", 0 );

	m_frame = NULL;

// 	TODO: Check new Code::Blocks splashscreen code ( if any ), this seems to not appear ( at least in wxGTK )
#ifndef __WXFB_DEBUG__
	wxBitmap bitmap;
//	wxSplashScreen* splash;
	std::auto_ptr< cbSplashScreen > splash;
	if ( !justGenerate )
	{
		if ( bitmap.LoadFile( dataDir + wxFILE_SEP_PATH + "resources" + wxFILE_SEP_PATH + "splash.png", wxBITMAP_TYPE_PNG ) )
		{
			splash = std::auto_ptr< cbSplashScreen >( new cbSplashScreen( bitmap, -1, 0, wxNewId() ) );
/*			splash = new wxSplashScreen(bitmap,
										wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT,
										3000, NULL, -1, wxDefaultPosition, wxDefaultSize,
										wxNO_BORDER | wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP); */
		}
	}
#endif

	wxYield();

	// Read size and position from config file
	wxConfigBase *config = wxConfigBase::Get();
	config->SetPath("/mainframe");
	int x, y, w, h;
	// x = y = w = h = -1;
	config->Read( "PosX", &x );
	config->Read( "PosY", &y );
	config->Read( "SizeW", &w );
	config->Read( "SizeH", &h );

	config->SetPath("/");

	m_frame = new MainFrame( NULL, wxID_ANY, 0, wxPoint( x, y ), wxSize( w, h ) );
	if ( !justGenerate )
	{
		m_frame->Show( TRUE );
		SetTopWindow( m_frame );

		#ifndef __WXFB_DEBUG__
		// turn off the splash screen
		delete splash.release();
		#endif

		#ifdef __WXFB_DEBUG__
			wxLogWindow* log = dynamic_cast< wxLogWindow* >( AppData()->GetDebugLogTarget() );
			if ( log )
			{
				m_frame->AddChild( log->GetFrame() );
			}
		#endif //__WXFB_DEBUG__
	}
	// This is not necessary for wxFB to work. However, Windows sets the Current Working Directory
	// to the directory from which a .fbp file was opened, if opened from Windows Explorer.
	// This puts an unneccessary lock on the directory.
	// This changes the CWD to the already locked app directory as a workaround
	#ifdef __WXMSW__
	::wxSetWorkingDirectory( dataDir );
	#endif

	if ( !projectToLoad.empty() )
	{
		if ( AppData()->LoadProject( projectToLoad, !justGenerate ) )
		{
			if ( justGenerate )
			{
				if ( hasLanguage )
				{
					PObjectBase project = AppData()->GetProjectData();
					PProperty codeGen = project->GetProperty("code_generation");
					if ( codeGen )
					{
						codeGen->SetValue( language );
					}
				}
				AppData()->GenerateCode( false );
				return 0;
			}
			else
			{
				m_frame->InsertRecentProject( projectToLoad );
				return wxApp::OnRun();
			}
		}
		else
		{
			wxLogError( _("Unable to load project: %s"), projectToLoad.c_str() );
		}
	}
	if ( justGenerate )
	{
		return 6;
	}

	AppData()->NewProject();

#ifdef __WXMAC__
    // document to open on startup
    if(!m_mac_file_name.IsEmpty())
    {
        if ( AppData()->LoadProject( m_mac_file_name ) )
            m_frame->InsertRecentProject( m_mac_file_name );
    }
#endif

	return wxApp::OnRun();
}

bool wxFormBuilderApp::OnInit()
{
	// Initialization is done in OnRun, so MinGW SEH works for all code (it needs a local variable, OnInit is called before OnRun)
	return true;
}

int wxFormBuilderApp::OnExit()
{
	MacroDictionary::Destroy();
	AppDataDestroy();

	if( !wxTheClipboard->IsOpened() )
	{
        if ( !wxTheClipboard->Open() )
        {
            return wxApp::OnExit();
        }
	}
    // Allow clipboard data to persist after close
    wxTheClipboard->Flush();
    wxTheClipboard->Close();

	return wxApp::OnExit();
}

void wxFormBuilderApp::SelectLanguage( int lang )
{
    if ( !m_locale.Init(lang) )
    {
        wxLogError( _("This language is not supported by the system.") );
        return;
    } 

    wxLocale::AddCatalogLookupPathPrefix("../locale");
    m_locale.AddCatalog("wxformbuilder");
}

wxFormBuilderApp::~wxFormBuilderApp()
{
}

#ifdef __WXMAC__
void wxFormBuilderApp::MacOpenFile(const wxString &fileName)
{
    if(m_frame == NULL) m_mac_file_name = fileName;
    else
    {
        if(!m_frame->SaveWarning()) return;

        if ( AppData()->LoadProject( fileName ) )
            m_frame->InsertRecentProject( fileName );
    }
}
#endif

#if wxUSE_ON_FATAL_EXCEPTION && wxUSE_STACKWALKER
	class StackLogger : public wxStackWalker
	{
	protected:
		void OnStackFrame( const wxStackFrame& frame )
		{
			// Build param string
			wxString params;
			size_t paramCount = frame.GetParamCount();
			if ( paramCount > 0 )
			{
				params << "( ";

				for ( size_t i = 0; i < paramCount; ++i )
				{
					wxString type, name, value;
					if ( frame.GetParam( i, &type, &name, &value) )
					{
						params << type << " " << name << " = " << value << ", ";
					}
				}
				params << ")";
			}

			wxString source;
			if ( frame.HasSourceLocation() )
			{
				source.Printf( "%s@%i", frame.GetFileName().c_str(), frame.GetLine() );
			}

			wxLogError( "%03i %i %s %s %s %s",
						frame.GetLevel(),
						frame.GetAddress(),
						frame.GetModule().c_str(),
						frame.GetName().c_str(),
						params.c_str(),
						source.c_str() );
		}
	};

	void wxFormBuilderApp::OnFatalException()
	{
		LogStack();
	}
#elif defined(_WIN32) && defined(__MINGW32__)
	static _CONTEXT* context = 0;
	EXCEPTION_DISPOSITION StructuredExceptionHandler(	struct _EXCEPTION_RECORD *ExceptionRecord,
																void * EstablisherFrame,
																struct _CONTEXT *ContextRecord,
																void * DispatcherContext )
	{
		context = ContextRecord;
		LogStack();
		return ExceptionContinueSearch;
	}

	class StackLogger
	{
	public:
		void WalkFromException()
		{
			try
			{
				std::stringstream output;
				dbg::stack s( 0, context );
				dbg::stack::const_iterator frame;
				for ( frame = s.begin(); frame != s.end(); ++frame )
				{
					output << *frame;
					wxLogError( wxString( output.str().c_str(), *wxConvCurrent ) );
					output.str( "" );
				}
			}
			catch ( std::exception& ex )
			{
				wxLogError( wxString( ex.what(), *wxConvCurrent ) );
			}
		}
	};
#endif

#if (wxUSE_ON_FATAL_EXCEPTION && wxUSE_STACKWALKER) || (defined(_WIN32) && defined(__MINGW32__))
class LoggingStackWalker : public StackLogger
{
public:
    LoggingStackWalker()
    :
    StackLogger()
    {
        wxLog::Suspend();
    }

    ~LoggingStackWalker()
    {
        wxLogError( _("A Fatal Error Occurred. Click Details for a backtrace.") );
        wxLog::Resume();
        wxLog* logger = wxLog::GetActiveTarget();
        if ( 0 != logger )
        {
            logger->Flush();
        }
        exit(1);
    }
};

void LogStack()
{
    LoggingStackWalker walker;
    walker.WalkFromException();
}
#endif
