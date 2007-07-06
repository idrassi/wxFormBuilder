project.name = "wxAdditions"

dofile( "premake/scripts/additions.lua" )

-- Add projects here.
dopackage( "awx" )
dopackage( "things" )
dopackage( "plotctrl" )
dopackage( "ledBarGraph" )
if ( OS == "windows" ) then
	dopackage( "propgrid" )
	dopackage( "wxFlatNotebook" )
	dopackage( "wxScintilla" )
end
