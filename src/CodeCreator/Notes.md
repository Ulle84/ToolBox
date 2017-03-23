# Remarks
* Most of this code was programmed by Ulrich Belitz in his leisure time.

# Description
* This tool generates C++ Code.
* There are several generators.
* This tool is easily extentable.

# Bugs

# ToDo
## General
* copy name to clipboard after pressing button "generate"
* remove Template for QtDesignerWidget if not needed anymore
* put generated file links in clipboard so the new generatd files can be easily added to a open visual studio project
* button - open output-folder in explorer / DoubleCommander
* ask user if he really wants to clear the history
* change base class of CodeCreator to QMainWindow
* QMainWindow - statusBar -> show information about successfully generated files -> do not show message-box anymore
* Menu - Dialog Options -> show options like author etc.
* check comman line arguments -> set output path depeding on command line argument
* ExperimentElementTemplate -> Resources Folder -> move away all unnecessary stuff
* New Generator for getter/Setter of members - using classgenerator
* New Generator for QtDesignerPlugin
* New Generator for ConsoleApplication
* if folder does not exist -> try to create folder
* option add to svn -> calls command line or tortoise svn
* open explorer/DoubleCommander with folder where the files are generated
* check occurences of friend classes
* CodeHelper -> get Interfacename etc --> all conventions (trailing I etc) should be encapsulated -> same procedure for member
* Generators for CMake based DLL/EXE/QtDLL/QtEXE

# QtWidgetsApplication
* Menu About Program
* Version number of program -> needs to be adjusted in resource file
* add help file (qrh)?

## Class
* create ui file
* members: auto include headers of used members (?)
* full move operator and move constructor support (with member copy etc.)
* improve include handling - include of template parameters

## Experiment Element
* CMake: glob all - correct deployment of headers
* include UI file

## Decorator
* !!! Next TODO !!!
* decorator: declare default constructor private?
* decorator: implement custom cunstructor
* complete generator for decorator
* test code

## State
* understand state pattern
* complete generator for state

## Misc
* List-Widget - button duplicate
* monotype font for code inputs
* namespace support for all generators

# Ideas
* save and laod interfaces - define a interface with the interface-generator and use it in class-generator for example
* support for operators (<, >, ==, != etc.)
* save current folder at folder selection
* class: q-Pointer support -> pointing to overlaying class
* const method support
* type input (bool, int, double etc.) with suggestions and or combo-box
* Templates -> generate project per template?
* template for exporting dll
* more patterns
  * Factory
  * Command
  * Adapter
  * Template Method
  * Iterator
  * Composite
  * State
  * Proxy
* CodePreview: searchable tree for files instead of combobox

# Documentation

# How to add a new Generator (template based)
* create template-files in \Resources\Templates
* append new template-files to Resources\Resources.qrc
* create new generator via CodeCreator itself
* add new created generator to CodeCreator
  * run cmake
  * add include line in CodeCrator.cpp
  * add new generator in `void CodeCreator::initGenerators()` method
  * change code of new created generator