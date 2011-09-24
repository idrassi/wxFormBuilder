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
#include "main.h"

#include <manager.h>

#include <wx/config.h>
#include <wx/cmdline.h>
#include <wx/stdpaths.h>

#ifdef __WXMSW__
    #include <wx/sysopt.h>
#endif

// Abnormal Termination Handling
#if wxUSE_ON_FATAL_EXCEPTION && wxUSE_STACKWALKER
    #include <wx/stackwalk.h>
    #include <wx/utils.h>
#elif defined(_WIN32) && defined(__MINGW32__)
    #include "debug/stack_trace/stack.hpp"
    #include <sstream>
    #include <excpt.h>

    EXCEPTION_DISPOSITION StructuredExceptionHandler( struct _EXCEPTION_RECORD *ExceptionRecord,
                                                      void  * EstablisherFrame,
                                                      struct _CONTEXT *ContextRecord,
                                                      void  * DispatcherContext );
#endif
void LogStack();

static const wxCmdLineEntryDesc s_cmdLineDesc[] =
{
#if wxVERSION_NUMBER < 2900
    { wxCMD_LINE_SWITCH, wxT("g"), wxT("generate"), wxString(_("Generate code from passed file.") ) },
    { wxCMD_LINE_OPTION, wxT("l"), wxT("language"), wxString(_("Override the code_generation property from the passed file and generate the passed languages. Separate multiple languages with commas.") ) },
    { wxCMD_LINE_SWITCH, wxT("h"), wxT("help"),     wxString(_("Show this help message.") ), wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_HELP  },
    { wxCMD_LINE_PARAM, NULL, NULL,                 wxString(_("File to open.") ),           wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
    { wxCMD_LINE_NONE }
#else
    { wxCMD_LINE_SWITCH, "g", "generate", wxString(_("Generate code from passed file.") ) },
    { wxCMD_LINE_OPTION, "l", "language", wxString(_("Override the code_generation property from the passed file and generate the passed languages. Separate multiple languages with commas.") ) },
    { wxCMD_LINE_SWITCH, "h", "help",     wxString(_("Show this help message.") ), wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_HELP  },
    { wxCMD_LINE_PARAM, NULL, NULL,       wxString(_("File to open.") ),           wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
    { wxCMD_LINE_NONE }
#endif
};

IMPLEMENT_APP( wxFormBuilder )

int wxFormBuilder::OnRun()
{
    // Abnormal Termination Handling
    #if wxUSE_ON_FATAL_EXCEPTION && wxUSE_STACKWALKER
        ::wxHandleFatalExceptions( true );
    #elif defined(_WIN32) && defined(__MINGW32__)
        // Structured Exception handlers are stored in a linked list at FS:[0]
        // THIS MUST BE A LOCAL VARIABLE - windows won't use an object outside of the thread's stack frame
        EXCEPTION_REGISTRATION ex;
        ex.handler = StructuredExceptionHandler;
        asm volatile ("movl %%fs:0, %0" : "=r" (ex.prev));
        asm volatile ("movl %0, %%fs:0" : : "r" (&ex));
    #endif

    // Using a space so the initial 'w' will not be capitalized in wxLogGUI dialogs
//    wxApp::SetAppName( wxT( " wxFormBuilder" ) );

    // Get the data directory
    wxStandardPathsBase& stdPaths = wxStandardPaths::Get();
    wxString dataDir = stdPaths.GetDataDir();
    dataDir.Replace( GetAppName().c_str(), wxT("wxformbuilder") );

    // Log to stderr while working on the command line
    delete wxLog::SetActiveTarget( new wxLogStderr );

    // Message output to the same as the log target
    delete wxMessageOutput::Set( new wxMessageOutputLog );

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
    bool hasLanguage = parser.Found( wxT("l"), &language );
    if ( parser.Found( wxT("g") ) )
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
                wxLogError(_("Empty language option. Nothing generated.") );
                return 3;
            }
            language.Replace( wxT(","), wxT("|"), true );
        }

        // generate code
        justGenerate = true;
    }
    else
    {
        delete wxLog::SetActiveTarget( new wxLogGui );
    }

    // Create singleton AppData - wait to initialize until sure that this is not the second
    /* instance of a project file.
    AppDataCreate( dataDir );

    // Make passed project name absolute
    try
    {
        if ( !projectToLoad.empty() )
        {
            wxFileName projectPath( projectToLoad );
            if ( !projectPath.IsOk() )
            {
                THROW_WXFBEX( wxT("This path is invalid: ") << projectToLoad );
            }

            if ( !projectPath.IsAbsolute() )
            {
                if ( !projectPath.MakeAbsolute() )
                {
                    THROW_WXFBEX( wxT("Could not make path absolute: ") << projectToLoad );
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
*/
#ifdef __WXMSW__
    wxSystemOptions::SetOption( wxT( "msw.remap" ), 0 );
    wxSystemOptions::SetOption( wxT( "msw.staticbox.optimized-paint" ), 0 );
#endif

    m_frame = NULL;

    wxYield();

    m_frame = wxFBResource::Get()->GetMainFrame( NULL, true );

    if ( !m_frame )
    {
        wxLogError(_("Error while loading the main frame.") ); return 1;
    }

    // Setup frame icons
    wxFileName imgFileName = wxFileName( wxFB_LOGO );

    imgFileName.MakeAbsolute();

    if ( !justGenerate )
    {
        m_frame->Show( true );
        SetTopWindow( m_frame );
/*
        #ifdef __WXFB_DEBUG__
            wxLogWindow* log = dynamic_cast< wxLogWindow* >( AppData()->GetDebugLogTarget() );
            if ( log )
            {
                m_frame->AddChild( log->GetFrame() );
            }
        #endif //__WXFB_DEBUG__
*/
    }

    // This is not necessary for wxFB to work. However, Windows sets the Current Working Directory
    // to the directory from which a .fbp file was opened, if opened from Windows Explorer.
    // This puts an unneccessary lock on the directory.
    // This changes the CWD to the already locked app directory as a workaround
    #ifdef __WXMSW__
    ::wxSetWorkingDirectory( dataDir );
    #endif
/*
    if ( !projectToLoad.empty() )
    {
        if ( AppData()->LoadProject( projectToLoad, !justGenerate ) )
        {
            if ( justGenerate )
            {
                if ( hasLanguage )
                {
                    PObjectBase project = AppData()->GetProjectData();
                    PProperty codeGen = project->GetProperty( _("code_generation") );
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
            wxLogError( wxT("Unable to load project: %s"), projectToLoad.c_str() );
        }
    }
*/
    if ( justGenerate )
    {
        return 6;
    }
/*
    wxFBResource::Get()->NewProject();
    wxFBResource::Get()->LoadPlugins();

#ifdef __WXMAC__
    // document to open on startup
    if(!m_mac_file_name.IsEmpty())
    {
        if ( AppData()->LoadProject( m_mac_file_name ) )
            m_frame->InsertRecentProject( m_mac_file_name );
    }
#endif
*/
    return wxApp::OnRun();
}

bool wxFormBuilder::OnInit()
{
    // Initialization is done in OnRun, so MinGW SEH works for all code (it needs a local variable, OnInit is called before OnRun)
    return true;
}

int wxFormBuilder::OnExit()
{
    wxFBResource::Get()->Free();
/*
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
*/
    return wxApp::OnExit();
}

wxFormBuilder::~wxFormBuilder()
{
}
/*
#ifdef __WXMAC__
void wxFormBuilder::MacOpenFile(const wxString &fileName)
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
*/
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
                params << wxT("( ");

                for ( size_t i = 0; i < paramCount; ++i )
                {
                    wxString type, name, value;
                    if ( frame.GetParam( i, &type, &name, &value) )
                    {
                        params << type << wxT(" ") << name << wxT(" = ") << value << wxT(", ");
                    }
                }

                params << wxT(")");
            }

            wxString source;
            if ( frame.HasSourceLocation() )
            {
                source.Printf( wxT("%s@%i"), frame.GetFileName().c_str(), frame.GetLine() );
            }

            wxLogError( wxT("%03i %i %s %s %s %s"),
                            frame.GetLevel(),
                            frame.GetAddress(),
                            frame.GetModule().c_str(),
                            frame.GetName().c_str(),
                            params.c_str(),
                            source.c_str() );
        }
    };

    void wxFormBuilder::OnFatalException()
    {
        LogStack();
    }
#elif defined(_WIN32) && defined(__MINGW32__)
    static _CONTEXT* context = 0;
    EXCEPTION_DISPOSITION StructuredExceptionHandler( struct _EXCEPTION_RECORD *ExceptionRecord,
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
        wxLogError(_("A Fatal Error Occurred. Click Details for a backtrace.") );
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
