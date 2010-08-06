#ifndef CODEPARSER_H_INCLUDED
#define CODEPARSER_H_INCLUDED

#include <wx/hashmap.h>
#include <wx/msgdlg.h>
#include <wx/string.h>
#include <wx/textfile.h>

// Stores all of the information for all of the parsed funtions
class Function
{
	public:
		Function()
		{}
		~Function()
		{}

		// Stores the code contained in the body of the function
		void SetContents( wxString contents );

		// Stores the whole first line of the function as a single string ex: "void fubar::DoSomething(int number)"
		void SetHeading( wxString heading );

		// Stores any code/documentation located between the previous function and the current function
		void SetDocumentation( wxString documentation )
		{
			m_documentation = documentation;
		}

		// Retrieves the body code
		wxString GetContents()
		{
			return m_functionContents;
		}

		// Retrieves the documentation
		wxString GetDocumentation()
		{
			return m_documentation;
		}
		// Retrieves everything including documentation
		wxString GetFunction();

	protected:
		wxString m_functionContents;
		wxString m_functionHeading;
		wxString m_documentation;
};

// Map class mapping Function* to function name
WX_DECLARE_STRING_HASH_MAP( Function*, FunctionMap );
#define funcIterator FunctionMap::iterator


// Parses the source and header files for all code added to the generated
class CodeParser
{
	public:
		//constructor
		CodeParser()
		{}

		~CodeParser()
		{}

		///////////////////////////////////////////////////////////////////
		
		// Returns all user header include code before the class declaration
		wxString GetUserIncludes()
		{
			return m_userInclude;
		}

		// Returns user class members
		wxString GetUserMembers()
		{
			return m_userMemebers;
		}
		
		// Returns the Documentation of a function by name
		wxString GetFunctionDocumentation( wxString function );
          
		// Returns the contents of a function by name and then removes it from the list of remaining functions
		wxString GetFunctionContents( wxString function );

		// Returns all ramaining functions including documentation as one string.
		// this may rearrange functions, but should keep them intact
		wxString GetRemainingFunctions();
		
		wxString GetTrailingCode()
		{
			return m_trailingCode;
		}

	protected:
		wxString m_userInclude;
		wxString m_className;
		wxString m_userMemebers;
		wxString m_trailingCode;

		FunctionMap m_functions;
		funcIterator m_functionIter;
};

// Parses the source and header files for all code added to the generated
class CCodeParser : public CodeParser
{
	private:
		wxString m_hFile;
		wxString m_cFile;
		
	public:
		//constructor
		CCodeParser()
		{
		}
		
		CCodeParser( wxString headerFileName, wxString sourceFileName )
		{
			m_hFile = headerFileName;
			m_cFile = sourceFileName;
		}

		~CCodeParser()
		{}

		/* c++ Parser */
		
			//opens the header and source,  'className' is the Inherited class
			void ParseCFiles( wxString className );

			//extracts the contents of the files.  take the the entire contents of both files in string form
			void ParseCCode( wxString header, wxString source );

			//extracts all user header include code before the class declaration
			void ParseCInclude( wxString code );

			//extracts the contents of the generated class declaration
			void ParseCClass( wxString code );
			
			wxString ParseSourceFunctions( wxString code );
			
			wxString ParseBrackets( wxString code, int& functionStart );
			
			void ParseCUserMembers( wxString code );
			
		/***************/
};

//class PCodeParser : public CodeParser

#endif // CODEPARSER_H_INCLUDED
