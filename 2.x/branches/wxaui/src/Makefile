CPP  = g++
CC   = gcc

RES  = 
OBJ  = model/database.o model/objectbase.o rad/bitmaps.o rad/guirad.o rad/mainframe.o rad/palette.o utils/stringutils.o utils/typeconv.o maingui.o rad/designer/visualobj.o utils/debug.o rad/cpppanel/cpppanel.o rad/appobserver.o rad/objecttree/objecttree.o rad/inspector/objinspect2.o rad/inspector/propeditor.o rad/designer/visualeditor.o rad/appdata.o rad/customkeys.o codegen/codegen.o codegen/cppcg.o rad/title.o rad/genericpanel.o model/types.o rad/xrcpanel/xrcpanel.o codegen/xrccg.o model/xrcfilter.o rad/about.o rad/cmdproc.o rad/menueditor.o rad/designer/menubar.o rad/designer/resizablepanel.o rad/global.o

LIBS = `wx-config --libs`   ../libs/tinyxml/tinyxml.a -lwx_gtk2_stc-2.6 -lwx_gtk2_propgrid-2.6
INCS = 
CXXINCS =
BIN  = ../bin/wxFormBuilder
CXXFLAGS = `wx-config --cxxflags` -I"../libs/tinyxml/" -I"." -I"../libs/boost_1_31_0" -DTIXML_USE_STL -D__WXFB_DEBUG__ -g
CFLAGS = `wx-config --cflags` -I"../libs/tinyxml/" -I"." -I"../libs/boost_1_31_0" -DTIXML_USE_STL -D__WXFB_DEBUG__ -g

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	rm -f $(OBJ) $(BIN)


$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) $(LIBS)


model/types.o: model/types.cpp
	$(CPP) -c model/types.cpp -o model/types.o $(CXXFLAGS)

rad/genericpanel.o: rad/genericpanel.cpp
	$(CPP) -c rad/genericpanel.cpp -o rad/genericpanel.o $(CXXFLAGS)
  
rad/title.o: rad/title.cpp
	$(CPP) -c rad/title.cpp -o rad/title.o $(CXXFLAGS)

rad/about.o: rad/about.cpp
	$(CPP) -c rad/about.cpp -o rad/about.o $(CXXFLAGS)
  
model/database.o: model/database.cpp
	$(CPP) -c model/database.cpp -o model/database.o $(CXXFLAGS)

model/objectbase.o: model/objectbase.cpp
	$(CPP) -c model/objectbase.cpp -o model/objectbase.o $(CXXFLAGS)

model/objects.o: model/objects.cpp
	$(CPP) -c model/objects.cpp -o model/objects.o $(CXXFLAGS)

model/xrcfilter.o: model/xrcfilter.cpp
	$(CPP) -c model/xrcfilter.cpp -o model/xrcfilter.o $(CXXFLAGS)
	
rad/bitmaps.o: rad/bitmaps.cpp
	$(CPP) -c rad/bitmaps.cpp -o rad/bitmaps.o $(CXXFLAGS)

rad/guirad.o: rad/guirad.cpp
	$(CPP) -c rad/guirad.cpp -o rad/guirad.o $(CXXFLAGS)

rad/mainframe.o: rad/mainframe.cpp
	$(CPP) -c rad/mainframe.cpp -o rad/mainframe.o $(CXXFLAGS)

rad/palette.o: rad/palette.cpp
	$(CPP) -c rad/palette.cpp -o rad/palette.o $(CXXFLAGS)

utils/stringutils.o: utils/stringutils.cpp
	$(CPP) -c utils/stringutils.cpp -o utils/stringutils.o $(CXXFLAGS)

utils/typeconv.o: utils/typeconv.cpp
	$(CPP) -c utils/typeconv.cpp -o utils/typeconv.o $(CXXFLAGS)

maingui.o: maingui.cpp
	$(CPP) -c maingui.cpp -o maingui.o $(CXXFLAGS)

rad/designer/visualobj.o: rad/designer/visualobj.cpp
	$(CPP) -c rad/designer/visualobj.cpp -o rad/designer/visualobj.o $(CXXFLAGS)

utils/debug.o: utils/debug.cpp
	$(CPP) -c utils/debug.cpp -o utils/debug.o $(CXXFLAGS)

rad/cpppanel/cpppanel.o: rad/cpppanel/cpppanel.cpp
	$(CPP) -c rad/cpppanel/cpppanel.cpp -o rad/cpppanel/cpppanel.o $(CXXFLAGS)

rad/xrcpanel/xrcpanel.o: rad/xrcpanel/xrcpanel.cpp
	$(CPP) -c rad/xrcpanel/xrcpanel.cpp -o rad/xrcpanel/xrcpanel.o $(CXXFLAGS)

rad/appobserver.o: rad/appobserver.cpp
	$(CPP) -c rad/appobserver.cpp -o rad/appobserver.o $(CXXFLAGS)

rad/objecttree/objecttree.o: rad/objecttree/objecttree.cpp
	$(CPP) -c rad/objecttree/objecttree.cpp -o rad/objecttree/objecttree.o $(CXXFLAGS)

rad/inspector/objinspect2.o: rad/inspector/objinspect2.cpp
	$(CPP) -c rad/inspector/objinspect2.cpp -o rad/inspector/objinspect2.o $(CXXFLAGS)

rad/inspector/propeditor.o: rad/inspector/propeditor.cpp
	$(CPP) -c rad/inspector/propeditor.cpp -o rad/inspector/propeditor.o $(CXXFLAGS)

rad/designer/visualeditor.o: rad/designer/visualeditor.cpp
	$(CPP) -c rad/designer/visualeditor.cpp -o rad/designer/visualeditor.o $(CXXFLAGS)

rad/appdata.o: rad/appdata.cpp
	$(CPP) -c rad/appdata.cpp -o rad/appdata.o $(CXXFLAGS)

rad/customkeys.o: rad/customkeys.cpp
	$(CPP) -c rad/customkeys.cpp -o rad/customkeys.o $(CXXFLAGS)

codegen/codegen.o: codegen/codegen.cpp
	$(CPP) -c codegen/codegen.cpp -o codegen/codegen.o $(CXXFLAGS)

codegen/cppcg.o: codegen/cppcg.cpp
	$(CPP) -c codegen/cppcg.cpp -o codegen/cppcg.o $(CXXFLAGS)

codegen/xrccg.o: codegen/xrccg.cpp
	$(CPP) -c codegen/xrccg.cpp -o codegen/xrccg.o $(CXXFLAGS)

rad/cmdproc.o: rad/cmdproc.cpp
	$(CPP) -c rad/cmdproc.cpp -o rad/cmdproc.o $(CXXFLAGS)

rad/menueditor.o: rad/menueditor.cpp
	$(CPP) -c rad/menueditor.cpp -o rad/menueditor.o $(CXXFLAGS)
	
rad/designer/menubar.o: rad/designer/menubar.cpp
	$(CPP) -c rad/designer/menubar.cpp -o rad/designer/menubar.o $(CXXFLAGS)

rad/designer/resizablepanel.o: rad/designer/resizablepanel.cpp
	$(CPP) -c rad/designer/resizablepanel.cpp -o rad/designer/resizablepanel.o $(CXXFLAGS)

rad/global.o: rad/global.cpp
	$(CPP) -c rad/global.cpp -o rad/global.o $(CXXFLAGS)

