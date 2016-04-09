/*
@doc FAQ

@contents1 OpenFlight API FAQ |

@normal
This section contains answers to <m Frequently Asked Questions> regarding the OpenFlight API, 
OpenFlight Script and the OpenFlight File Format.

@group2
Questions
@faq_ref FAQ_00000000 | What is the OpenFlight API?
@faq_ref FAQ_00000001 | What is OpenFlight Script?
@faq_ref FAQ_00000002 | What is Creator Script?
@faq_ref FAQ_00000003 | What is the OpenFlight Scene Graph?
@faq_ref FAQ_00000004 | Is there a user forum on the web devoted to OpenFlight? 
@faq_ref FAQ_00000005 | Are newer versions of the OpenFlight API backward compatible with older versions?
@faq_ref FAQ_00000010 | Why do I get a Stack Overflow when I open a database in my stand-alone program? 
@faq_ref FAQ_00000011 | What does "SmartHeap Library - Out of Memory" error mean? 
@faq_ref FAQ_00000012 | When I run my stand-alone application, the wrong version of the OpenFlight API runs. Why? 
@faq_ref FAQ_00000013 | How do I control which plug-ins load when I run my stand-alone application or Creator? 
@faq_ref FAQ_00000100 | How do I run OpenFlight Scripts in a stand-alone program environment?
@faq_ref FAQ_00000101 | How do I run OpenFlight Scripts in Creator?
@faq_ref FAQ_00000102 | Why are some OpenFlight API function signatures different in C and OpenFlight Script?
@faq_ref FAQ_00000103 | Are there any OpenFlight Script samples I can start with?
@faq_ref FAQ_00000104 | Can I invoke Creator tools from the OpenFlight API or OpenFlight Script?
@faq_ref FAQ_00000105 | Why don't I have to "free" dynamically allocated memory in OpenFlight Script?
@faq_ref FAQ_00000200 | What format revisions of OpenFlight does the OpenFlight API support?
@faq_ref FAQ_00000201 | How do I load an OpenFlight file into memory?
@faq_ref FAQ_00000202 | How do I create a brand new, empty, OpenFlight file in memory?
@faq_ref FAQ_00000205 | After making changes to the OpenFlight file in memory, how do I save my changes to disk?
@faq_ref FAQ_00000206 | If I change an OpenFlight file in memory, how do I discard those changes so they are not saved?
@faq_ref FAQ_00000207 | How do I save my changes to an OpenFlight file with a different file name?
@faq_ref FAQ_00000208 | If I save my changes to an OpenFlight file, which OpenFlight format revision will be written?
@faq_ref FAQ_00000209 | I want to save my OpenFlight file to a different OpenFlight format revision - How do I do that?
@faq_ref FAQ_00000210 | Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?
@faq_ref FAQ_00001000 | What is an mgrec?
@faq_ref FAQ_00001001 | What is the OpenFlight Data Dictionary?
@faq_ref FAQ_00001002 | How can I tell what kind of record I have in an mgrec?
@faq_ref FAQ_00001003 | How do I get the attributes of a record in the database?
@faq_ref FAQ_00001004 | How do I set the attributes of a record in the database?
@faq_ref FAQ_00001005 | How do I get a string attribute of a record in the database?
@faq_ref FAQ_00001006 | How do I access a value in a record nested inside another record?
@faq_ref FAQ_00001007 | What is the best way to get the coordinates (position) of a vertex node record?
@faq_ref FAQ_00001008 | How do I get or set the comment attribute of a node record?
@faq_ref FAQ_00001009 | What is the difference between Color Index/Intensity and Creator Color Index attributes?
@faq_ref FAQ_00001010 | When I set a color intensity attribute on a node, the value I see on the node is not the exact value I set. Why is there a difference? 
@faq_ref FAQ_00001011 | How do I set up texture on a polygon? 
@faq_ref FAQ_00001012 | How do I determine the OpenFlight revision level of an OpenFlight database? 
@faq_ref FAQ_00001013 | Can I query the OpenFlight revision level of an OpenFlight file on disk without opening it? 
@faq_ref FAQ_00001014 | How do I set a color name on a polygon or mesh? 
@faq_ref FAQ_00001015 | How do I set the normal of a polygon? 
@faq_ref FAQ_00001016 | Which side of a polygon is the front and which is the back? 
@faq_ref FAQ_00001017 | How do I access an edge of a polygon? 
@faq_ref FAQ_00001018 | How do I select an edge of a polygon in Creator? 
@faq_ref FAQ_00001020 | How do I tell if a specific node is selected in Creator? 
@faq_ref FAQ_00001021 | How do I get the list of nodes that are currently selected in Creator? 
@faq_ref FAQ_00001022 | How do I tell if an edge of a polygon is selected in Creator? 
@faq_ref FAQ_00001023 | Why are the nodes in the select list in reverse order from how they were selected by the user in Creator?
@faq_ref FAQ_00001024 | How do I select nodes from my plug-in or script in Creator? 
@faq_ref FAQ_00001030 | How do I get the current modeling mode set in Creator? 
@faq_ref FAQ_00001031 | How do I tell the difference between vertex and edge modeling mode in Creator? 
@faq_ref FAQ_00001032 | How do I change the modeling mode in Creator from my plug-in or script? 
@faq_ref FAQ_00001040 | When I try to attach a node in the database hierarchy, sometimes it fails. What could be causing this?
@faq_ref FAQ_00001041 | Why can't I move a node from one database to another?
@faq_ref FAQ_00001042 | How do I create a new node in a database?
@faq_ref FAQ_00001043 | How do I create an external reference in a master database?
@faq_ref FAQ_00001044 | How do I create a simple polygon with vertices?
@faq_ref FAQ_00001050 | How do I apply a matrix (transformation) to a node?
@faq_ref FAQ_00001051 | How do I get the matrix (transformation) from a node?
@faq_ref FAQ_00001080 | What order does mgWalk visit the nodes in the hierarchy?
@faq_ref FAQ_00001090 | How do I hide or show a node in the Creator Graphics view?
@faq_ref FAQ_00001100 | If I change the position of a vertex, is there an easy way to recalculate its texture coordinates to match the original texture mapping?

////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000000 | Question

@question
What is the OpenFlight API?

@answer 
The Presagis OpenFlight API is a set of C Language header files and libraries 
that provides a programming interface to the OpenFlight database format as well 
as the Creator modeling system. The OpenFlight API provides functions to read 
and/or modify existing databases as well as those to create new databases. 
Using the OpenFlight API, you can create:

<unorderedliststart .>
<listelementstart NOINDENT> Translators to and from the OpenFlight format <listelementend>
<listelementstart NOINDENT> Real-time simulators and games <listelementend>
<listelementstart NOINDENT> Modeling applications <listelementend>
<listelementstart NOINDENT> Plug-ins that extend the functionality of Creator <listelementend>
<unorderedlistend>

@faqrelated
<faq_ref FAQ_00000001.What is OpenFlight Script?>
<faq_ref FAQ_00000104.Can I invoke Creator tools from the OpenFlight API or OpenFlight Script?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000001 | Question

@question
What is OpenFlight Script?

@answer 
OpenFlight Script is a cross-platform Python Language binding to the C Language 
OpenFlight API. Based on the Python scripting language, OpenFlight Script provides 
nearly all the functionality of the OpenFlight API levels 1 and 2 and much of the 
functionality of level 4. If you understand the concepts of the
OpenFlight API, you will find programming in either the C Language API or OpenFlight
Script very similar.  Both the C Language OpenFlight API and the Python Language bindings
for OpenFlight Script are included when you install the OpenFlight API Software Development
Kit (SDK).

@answer
You can use OpenFlight Script to do most things you could otherwise do with the C Language
API. Because OpenFlight Script is an interpreted language (based on Python), tools and
applications written in OpenFlight Script will likely run more slowly than comparable tools
written using the C Language API.  So if performance is an issue, consider using the C
Language API. Of course the benefit of using OpenFlight Script is that you don't need
to pre-compile your tools, you can simply run them.

@answer
You can use OpenFlight Script in either the stand-alone program environment or the
Creator modeling system.
In the Creator modeling system, you can execute Creator tools using OpenFlight Script
using <f mgExecute>.

@answer
A general knowledge of Python will help you get started quickly using OpenFlight Script.

@see <f mgExecute>

@faqrelated
<faq_ref FAQ_00000002.What is Creator Script?>
<faq_ref FAQ_00000104.Can I invoke Creator tools from the OpenFlight API or OpenFlight Script?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000003 | Question

@question
What is the OpenFlight Scene Graph?

@answer
The OpenFlight Scene Graph is the "in memory" representation of the OpenFlight database. As the name
implies, it is a multilevel, hierarchical <i graph> structure. At the "root" (top) of the graph is a 
database header (<f fltHeader>) node. At the bottom of the graph are vertex (<f fltVertex>) nodes. 
In between is a number of different types of organizational nodes, like <f fltGroup>, <f fltObject>, <f fltLod>,
<f fltDof>, <f fltPolgyon>, <f fltMesh>, etc.

@answer
Your code can load OpenFlight files into a scene graph using <f mgOpenDb> or create a new, empty scene 
graph using <f mgNewDb>. Once a scene graph is loaded, your code can modify it. You can add, delete or 
move nodes using functions like <f mgNewRec>, <f mgAttach>, <f mgDetach> and <f mgDelete>. Your code can
also modify node attributes using <f mgSetAttList>. There are many other operations your code can perform
on the OpenFlight Scene Graph, these are just a few.

@answer
After making changes to the scene graph, your code can save it to an OpenFlight file using functions
like <f mgWriteDb>, <f mgSaveAsDb> and <f mgExportDb>.

@faqrelated
<faq_ref FAQ_00001000.What is an mgrec?>
<faq_ref FAQ_00000201.How do I load an OpenFlight file into memory?>
<faq_ref FAQ_00001042.How do I create a new node in a database?>
<faq_ref FAQ_00001004.How do I set the attributes of a record in the database?>
<faq_ref FAQ_00000205.After making changes to the OpenFlight file in memory, how do I save my changes to disk?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000002 | Question

@question
What is Creator Script?

@answer
Creator Script is the same as OpenFlight Script. Note that in OpenFlight Script
you can invoke Creator tools.  An OpenFlight script that invokes a Creator tool 
is often referred to as a "Creator Script" but under the hood it is really just
an OpenFlight Script.

@faqrelated
<faq_ref FAQ_00000001.What is OpenFlight Script?>
<faq_ref FAQ_00000104.Can I invoke Creator tools from the OpenFlight API or OpenFlight Script?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000004 | Question

@question
Is there a user forum on the web devoted to OpenFlight? 
@answer There are many user forums on the web devoted to all the Presagis products.
Among them, there are 3 forums related specifically to OpenFlight. These are located at:

@answer
<tlink _blank.http\:\/\/www\.presagis\.com\/standards_forum\/.http\:\/\/www\.presagis\.com\/standards_forum\/>

@answer
In addition to the OpenFlight standards forum, the OpenFlight API and OpenFlight Script is 
often discussed on the Creator product forum, located at:

@answer
<tlink _blank.http\:\/\/www\.presagis\.com\/peer_forum\/.http\:\/\/www\.presagis\.com\/peer_forum\/>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000005 | Question

@question
Are newer versions of the OpenFlight API backward compatible with older versions?

@answer
Yes... function signatures do not change, nor are functions or symbols removed in newer versions
of the OpenFlight API. In most cases an application or plug-in built with an <i older> version
of the OpenFlight API will simply run with a <i newer> version of the API without recompiling.

@answer
There are cases when this is not true.  For example, when Creator migrated from VC6 to VC8 (v3.4),
plug-ins built with OpenFlight API v3.3 or earlier would not run in Creator 3.4.  These plug-ins
required recompilation in order to be compatible with the new VC8 binary format.

@answer 
When a new version of the OpenFlight API is released, we do recommend that you rebuild your plug-ins
and applications just to be safe.

@answer
While functions and symbols are not removed in newer versions of the OpenFlight API (as mentioned above),
some are deprecated when it makes sense.  A deprecated function, for example, is one for which
an improved replacement has been developed.  The original (deprecated) function is not removed
but we recommend that you begin using the new function.  There is a <b Deprecated API>
section in the Release Notes section of this reference document.  Refer to that section for more
information on deprecated API.
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000010 | Question

@question
Why am I getting a Stack Overflow when I run my stand-alone program? 

@answer
This problem is most likely related to the Stack Size of your application.
When you build your application (in Visual Studio, for example), you set the maximum 
stack size as a linker option. This is the maximum size your program stack is allowed 
to grow during program execution. If you don't set this explicitly, you get defaults
from your build environment (Visual Studio gives you 1MB typically by default).

@answer
If you are building a stand-alone program using the OpenFlight API, we recommend 
64MB for the stack size.  Due to the nature of OpenFlight database hierarchies and 
the recursive functions used in the OpenFlight API to traverse them, 
we have found that stack can get used up quickly and 64MB seems to work well. 
By the way, Creator uses a 64MB stack size so if you can open an OpenFlight file
in Creator but not your application, this may be why.

@answer
If you are working in Visual Studio, check the <mono /STACK> linker option when 
building your application.  Try setting it to:

@answer
<q /STACK\:64388608,65536>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000011 | Question

@question
What does "SmartHeap Library - Out of Memory" error mean? 

@answer
The OpenFlight API uses a 3rd party memory management library called SmartHeap.
All heap memory allocations made by the OpenFlight API are managed by SmartHeap.
When you get this error (typically when trying to open an OpenFlight database 
using <f mgOpenDb>), SmartHeap is reporting that it has run out of Virtual Memory.  
There are several possible causes for this.

@answer
The first thing to check is the Virtual Memory setting on your computer.
Verify in your Windows Control Panel Settings that you have at least ~2GB Virtual 
Memory set.  If you are running a 32 bit application, any more will not be useful.
If you are running a 64 bit application, you can increase this value if you have
enough disk space to accommodate the swap file required.

@answer
On Windows XP, you can find this setting at:<nl>
<q Control Panel\: Advanced\: Performance\: Settings\: Advanced\: Virtual Memory>

@answer
On Windows 7, you can find this setting at:<nl>
<q Control Panel\: System\: Advanced system settings\: Advanced Performance Settings\: Advanced\: Virtual memory>

@answer
If you have adjusted your Virtual Memory setting and still get this error,
it could be that the database you are loading is just too large.  If you have
Creator, try opening it there. If your database is a master file with external
references, try setting <f mgSetReadExtFlag> to <e mgbool.MG_FALSE> before opening
the database. This tells the OpenFlight API to NOT read the external reference
files (which would decrease the amount of virtual memory needed to load the 
database). Similarly, try setting <f mgSetReadTexturesFlag> to <e mgbool.MG_FALSE> 
as well. This tells the OpenFlight API to NOT read textures into memory when loading
the texture palette of the database it is opening.

@see <f mgSetReadExtFlag>, <f mgSetReadTexturesFlag>, <f mgOpenDb>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000012 | Question

@question
When I run my stand-alone application, the wrong version of the OpenFlight API runs. Why? 

@answer
Even though you link your application with a specific version of the OpenFlight API <i Link 
Libraries>, Windows might load a different version of the <i Dynamic Link Libraries> (DLLs) if 
your runtime environment is not set up correctly.

@answer
First some background on how your application will find the OpenFlight API DLLs (and all 
the other DLLs it depends on) when you run it on Windows.

@answer
On Windows, the OpenFlight API Dynamic Link Libraries (DLLs) are required when you run your 
stand-alone application. When you run your application, Windows searches for all DLLs 
(including the OpenFlight API DLLs) in the following sequence:

<orderedliststart .>

<listelementstart NOINDENT>
The directory where your stand-alone executable is located.
<listelementend>

<listelementstart NOINDENT>
The current directory.
<listelementend>

<listelementstart NOINDENT>
The Windows system directory. The Windows function <mono GetSystemDirectory> function retrieves
the path of this directory.
<listelementend>

<listelementstart NOINDENT>
The Windows directory. The Windows function <mono GetWindowsDirectory> function retrieves the 
path of this directory.
<listelementend>

<listelementstart NOINDENT>
The directories listed in the <mono PATH> environment variable.
<listelementend>

<orderedlistend>

@answer
Also when your application calls <f mgInit>, the OpenFlight API echoes out the version being 
run. Check the output of your program to make sure you see the version number you expect to 
make sure you are running the OpenFlight API version you intend.

@answer
You can also query which version of the OpenFlight API is running using <f mgGetVersion>.
The version returned by this function is the same as that echoed by <f mgInit>.

@answer
One final note... A useful Windows utility is <b depends>.  You can run this tool on 
your executable file (.exe) and it will show you exactly which version of the DLLs will 
be found at runtime given the current configuration on your computer.

@see <f mgInit>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000013 | Question

@question
How do I control which plug-ins load when I run my stand-alone application or Creator? 

@answer
Plug-ins are loaded into the stand-alone program and Creator runtime environments
in very similar ways. In order for a plug-in to be available in either environment, 
it must be located in or below the <i plug-in runtime directory>. This is a platform 
specific directory that is accessible at runtime.

@answer When the runtime environment system starts up, this directory and all
directories below it will be searched for compatible plug-ins. All compatible plug-ins
found will be loaded and will be accessible in the runtime environment. Since plug-in 
modules may be distributed with a host of companion files (preference file, help file, 
etc), it may be convenient to install each plug-in in its own 
subdirectory below the <i plug-in runtime directory>. This is possible since the
<i plug-in runtime directory> is searched recursively.

@answer Creator loads plug-ins automatically when it starts. Creator searches for plug-ins
in the following locations (in the order listed). As soon as a folder is found in one of these 
locations, Creator stops searching for other locations and loads the plug-ins it finds in
the first folder found.

<orderedliststart .>

<listelementstart NOINDENT>
The directory (or directories) specified by the environmental variable <b PRESAGIS_CREATOR_PLUGIN_DIR>. 
This environmental variable may specify any accessible directory on your computer or may specify 
multiple directories using a semi-colon to delimit each path.
<listelementend>

<listelementstart NOINDENT>
A directory named <m plugins> in the Creator configuration folder. This folder 
is located at:

<q PRESAGIS_ROOT/Creator/config/plugins>
<listelementend>

<orderedlistend>

@answer Plug-ins are loaded in the stand-alone program environment when your program or script
calls the OpenFlight API function <f mgInit>. <f mgInit> searches for plug-ins in the following
locations (in the order listed). As soon as a folder is found in one of these 
locations, <f mgInit> stops searching for other locations and loads the plug-ins it finds in
the first folder found.

<orderedliststart .>

<listelementstart NOINDENT>
The directory (or directories) your program specifies when calling <f mgSetPluginFolder>. If you call 
this function before <f mgInit>, the location(s) you specify will be used to search
for plug-ins.
<listelementend>

<listelementstart NOINDENT>
The directory (or directories) specified by the environmental variable <b PRESAGIS_OPENFLIGHT_PLUGIN_DIR>. 
This environmental variable may specify any accessible directory on your computer or may specify 
multiple directories using a semi-colon to delimit each path.
<listelementend>

<listelementstart NOINDENT>
A directory named <m plugins> immediately below the directory that contains the executable being run. 
<listelementend>

<orderedlistend>

@see <f mgSetPluginFolder>, <f mgInit>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000100 | Question

@question
How do I run OpenFlight Scripts in a stand-alone program environment?

@answer
Before you can use OpenFlight Script in a stand-alone program environment, you
will need to install a Python environment (Python 2.7.X is required) on your computer. 
There are many Python distributions available. A good place to start is:

@answer
<tlink _blank.http\:\/\/www\.python\.org.http\:\/\/www\.python\.org>

@answer
Remember that OpenFlight Script requires Python 2.7.X.

@answer
After installing a Python environment on your computer, you must tell Python where to
locate the OpenFlight Script module. The OpenFlight Script module is comprised of the
OpenFlight API dynamic link libraries (including <mono fltdata\.dll>) and two additional
Python specific files included in the OpenFlight API distribution. These additional Python
files are:

@answer
<unorderedliststart .>
<listelementstart NOINDENT> <mono _mgapilib\.pyd> <listelementend>
<listelementstart NOINDENT> <mono mgapilib\.py><listelementend>
<unorderedlistend>

@answer
Both Python files (and the dynamic link library files) are located in:

@answer
<mono $(PRESAGIS_OPENFLIGHT_API)/bin/release (Win32)><nl>
or<nl>
<mono $(PRESAGIS_OPENFLIGHT_API)/bin_x64/release (x64)><nl>

@answer
Here are the steps to make the OpenFlight Script module available in Python:

<orderedliststart .>
<listelementstart NOINDENT>
Set the <mono PYTHONPATH> environment variable to include the folder where the OpenFlight
Script module files (dynamic link library files, <mono _mgapilib\.pyd> and <mono mgapilib\.py>)
are located.
<listelementend>

<listelementstart NOINDENT>
Set the <mono PRESAGIS_OPENFLIGHT_SCRIPT> environment variable to be the folder
where the OpenFlight Script module files are located.
<listelementend>

<orderedlistend>

@answer
After you configure your Python environment to include the OpenFlight Script module you
are ready to create and run OpenFlight Scripts in your stand-alone program environment. 

@faqrelated
<faq_ref FAQ_00000101.How do I run OpenFlight Scripts in Creator?>
<faq_ref FAQ_00000103.Are there any OpenFlight Script samples I can start with?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000101 | Question

@question
How do I run OpenFlight Scripts in Creator?

@answer
You do not need to install Python to run OpenFlight scripts in Creator
as Creator includes a built-in Python environment.  After installing
Creator, you are ready to go.  If you want to use additional Python modules that
are not included in Creator's Python environment, you will need to install Python
as well as those additional modules.

@answer
Creator includes the OpenFlight Script Editor 
which allows you to create, edit, test and run scripts directly while you are 
modeling.  The OpenFlight Script Editor provides a fully functional text editor 
with advanced features like auto-completion, error highlighting and context sensitive help.
It also provides a powerful script interpreter that helps you to create and test scripts rapidly.

@faqrelated
<faq_ref FAQ_00000100.How do I run OpenFlight Scripts in a stand-alone program environment?>
<faq_ref FAQ_00000103.Are there any OpenFlight Script samples I can start with?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000102 | Question

@question
Why are some OpenFlight API function signatures different in C and OpenFlight Script?

@answer
Most of the functions in OpenFlight Script are identical in calling method and functionality
to that of the corresponding C language API. There are a few exceptions due to the
inherent differences between the C and Python languages. Most of these exceptions exist
when a C language function has one or more output parameters. Output parameters are
those that get modified in the function and hence returned to the caller. Since C functions
have only a single return value, output parameters are commonly used for a function to
return multiple values simultaneously.

@answer
In general Python does not support output parameters for functions. To compensate for this
Python does support multiple return values for functions in the form of "lists" or "tuples".
For C language functions that do have output parameters, there will be a different function
signature for the Python equivalent. This is best explained by example (see below).

@exref Consider the OpenFlight function <f mgGetVtxCoord>. In C, its function signature is:
<q mgbool mgGetVtxCoord (mgrec* vtx, double* x, double* y, double* z);> 
This C function returns 4 "bits" of information.  It returns a status (whether the function
succeeded or failed) in the function return value.  It also returns the x, y, z coordinates 
of a vertex in the output parameters <p x>, <p y> and <p z>, respectively. 

In Python, remember, output parameters are not supported. For that reason,
the Python signature for this same function is different:
<q mgbool, x, y, z mgGetVtxCoord (mgrec* vtx)>

The Python version of this function returns the same 4 "bits" of information as the C version
but uses a different "return" mechanism to pass the values back to the caller.  Because Python has 
no notion of output parameters, the Python version of <f mgGetVtxCoord> returns the status as well 
as the x, y and z coordinates as a list (or tuple). 

Note that when the C and Python signatures for an OpenFlight function differ, each signature
is listed in the OpenFlight API Reference. When there is no difference between the C
and Python signature for a function, a single (common) signature is listed.

The syntax for calling this function in both C and Python is shown below in the examples. |

@ex Here is how you would call <f mgGetVtxCoord> in C: |
   double x, y, z;
   mgbool status;
   status = mgGetVtxCoord (vtx, &x, &y, &z);
   if (status == MG_TRUE) {
      // x, y and z contain valid values
   }

@pyex Here is how you would call <f mgGetVtxCoord> in Python: |
   status, x, y, z = mgGetVtxCoord (vtx)
   if (status == MG_TRUE):
      # x, y and z contain valid values

@faqrelated
<faq_ref FAQ_00000001.What is OpenFlight Script?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000103 | Question

@question
Are there any OpenFlight Script samples I can start with?

@answer
Perhaps the easiest way to get started is to
study the sample scripts included with the OpenFlight API distribution. These sample
scripts are located at:

@answer
<mono $(PRESAGIS_OPENFLIGHT_API)/samples/scripts>

@answer
The files (immediately) in this folder are stand-alone scripts in that they are 
designed to run in a stand-alone program environment (not in Creator).

@answer
There are also sample scripts that are designed to run in Creator.  These mimic
several common tools in Creator.  You can use them to see how tools
might be implemented in OpenFlight Script.  These scripts are located at:

@answer
<mono $(PRESAGIS_OPENFLIGHT_API)/samples/scripts/creatortools>

@faqrelated
<faq_ref FAQ_00000001.What is OpenFlight Script?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000104 | Question

@question
Can I invoke Creator tools from the OpenFlight API or OpenFlight Script?

@answer
You can execute Creator tools from your plug-in tool or OpenFlight Script in the
Creator modeler environment using the function <f mgExecute>.

@answer
Note that you cannot use this function in a stand-alone application or script.

@exref The following examples (in C and Python) show how you might use
<f mgExecute> to execute the Creator Tool <b Translate>.  Use the C code
to invoke a Creator Tool from your plugin.  Use the Python code in your
OpenFlight script: |

@ex | 
	// create a parameter block for the Translate command
	// the parameter block is initialized with default values
	mgparamblock paramBlock = mgGetParamBlock ("Translate");

	// set the values for each parameter in the block
	mgParamSetDouble3 (paramBlock, "From Point", 0, 0, 0);
	mgParamSetDouble3 (paramBlock, "To Point", 0, 0, 0);

	// execute the Translate command using the parameters set
	mgExecute ("Translate", paramBlock);

@pyex | 
	# create a parameter block for the Translate command
	# the parameter block is initialized with default values
	paramBlock = mgGetParamBlock ("Translate")

	# set the values for each parameter in the block
	mgParamSetDouble3 (paramBlock, "From Point", 0, 0, 0)
	mgParamSetDouble3 (paramBlock, "To Point", 0, 0, 0)

	# execute the Translate command using the parameters set
	mgExecute ("Translate", paramBlock)

@see <f mgExecute>

@faqrelated
<faq_ref FAQ_00000001.What is OpenFlight Script?>
<faq_ref FAQ_00000002.What is Creator Script?>
<faq_ref FAQ_00000103.Are there any OpenFlight Script samples I can start with?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000105 | Question

@question
Why don't I have to "free" dynamically allocated memory in OpenFlight Script?

@answer
OpenFlight Script is based on the Python scripting language. Python has "automatic"
garbage collection so your scripts do not have to explicitly free memory in the 
same way your C language code would have to.

@faqrelated
<faq_ref FAQ_00000001.What is OpenFlight Script?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000200 | Question

@question
What format revisions of OpenFlight does the OpenFlight API support?

@answer
The OpenFlight API can <i read> any format revision of OpenFlight going back to the early days
when the format was called simply "Flight" and was maintained by Software Systems in the mid 1980s.
The most recent OpenFlight format revision is 16.4. 

@answer
You use <f mgOpenDb> to read an OpenFlight file of any format revision. When you do this the file
is read into memory into the "OpenFlight Scene Graph" format. The in memory scene graph format
has no format revision, per se. It contains all the data necessary to write the most current (native)
OpenFlight format revision as well as all supported past revisions. You can examine or edit
the OpenFlight Scene Graph and then, optionally, save any changes you make.

@answer 
The OpenFlight API can <i write> only certain (newer) format revisions of OpenFlight. Those format 
revisions include:<nl>
15.4<nl>
15.6<nl>
15.7<nl>
15.8<nl>
16.0<nl>
16.1<nl>
16.2<nl>
16.3<nl>
16.4

@answer You use <f mgWriteDb>, <f mgSaveAsDb> or <f mgExportDb> to write (or save) an OpenFlight file.

@see <f mgOpenDb>, <f mgWriteDb>, <f mgSaveAsDb>, <f mgExportDb>

@faqrelated
<faq_ref FAQ_00000201.How do I load an OpenFlight file into memory?>
<faq_ref FAQ_00000202.How do I create a brand new, empty, OpenFlight file in memory?>
<faq_ref FAQ_00001012.How do I determine the OpenFlight revision level of an OpenFlight database?>
<faq_ref FAQ_00000205.After making changes to the OpenFlight file in memory, how do I save my changes to disk?>
<faq_ref FAQ_00000206.If I change an OpenFlight file in memory, how do I discard those changes so they are not saved?>
<faq_ref FAQ_00000207.How do I save my changes to an OpenFlight file with a different file name?>
<faq_ref FAQ_00000208.If I save my changes to an OpenFlight file, which OpenFlight format revision will be written?>
<faq_ref FAQ_00000209.I want to save my OpenFlight file to a different OpenFlight format revision - How do I do that?>
<faq_ref FAQ_00000210.Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000201 | Question

@question
How do I load an OpenFlight file into memory?

@answer
You use <f mgOpenDb> to open and load the contents of an OpenFlight file into memory - presumably so you can
examine or modify it. In memory, the contents of the OpenFlight file is stored in a <i graph> of hierarchical 
structures, collectively known as the "OpenFlight Scene Graph". The function <f mgOpenDb> returns
the "root node" of this graph. This "root node" is called the "header" or "database header".

@answer
Once the file is loaded in memory, you can examine or edit nodes in the OpenFlight Scene Graph. 
If you make changes to the OpenFlight Scene Graph, you can save those changes using <f mgWriteDb>, 
<f mgSaveAsDb> or <f mgExportDb>. When you no longer need the file loaded in memory, you should 
close the file and deallocate all associated memory using <f mgCloseDb>.

@exref The following examples (in C and Python) load an OpenFlight file into memory,
examine the OpenFlight Scene Graph (but make no changes) and then close the file. |

@ex |
   // load "file.flt" into the OpenFlight Scene Graph
   mgrec* db = mgOpenDb ("file.flt");

   // examine the db (or parts of it)
   ...

   // no changes, just close the file
   mgCloseDb (db);

@pyex |
   # load "file.flt" into the OpenFlight Scene Graph
   db = mgOpenDb ("file.flt")

   # examine the db (or parts of it)
   ...

   # no changes, just close the file
   mgCloseDb (db)

@see <f mgOpenDb>, <f mgWriteDb>, <f mgSaveAsDb>, <f mgExportDb>, <f mgCloseDb>

@faqrelated
<faq_ref FAQ_00000003.What is the OpenFlight Scene Graph?>
<faq_ref FAQ_00000200.What format revisions of OpenFlight does the OpenFlight API support?>
<faq_ref FAQ_00001012.How do I determine the OpenFlight revision level of an OpenFlight database?>
<faq_ref FAQ_00000205.After making changes to the OpenFlight file in memory, how do I save my changes to disk?>
<faq_ref FAQ_00000206.If I change an OpenFlight file in memory, how do I discard those changes so they are not saved?>
<faq_ref FAQ_00000207.How do I save my changes to an OpenFlight file with a different file name?>
<faq_ref FAQ_00000208.If I save my changes to an OpenFlight file, which OpenFlight format revision will be written?>
<faq_ref FAQ_00000209.I want to save my OpenFlight file to a different OpenFlight format revision - How do I do that?>
<faq_ref FAQ_00000210.Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000202 | Question

@question
How do I create a brand new, empty, OpenFlight file in memory?

@answer
If you want to load an <i existing> OpenFlight file into memory, you use <f mgOpenDb>. If you want to create
a <i new> OpenFlight file in memory, use <f mgNewDb>. Both functions return a header node for the corresponding
OpenFlight Scene Graph. The header node returned by <f mgNewDb> will not be completely empty. 
By convention the OpenFlight API creates two child group (<f fltGroup>) nodes below the new db header as shown
here:<nl>
<jpg mgNewDb>

@exref The following examples (in C and Python) create a new OpenFlight file into memory,
and print out the names of the two groups created. |

@ex |
   // create a new OpenFlight file
   mgrec* db = mgNewDb ("newfile.flt");

   // get the two group nodes created by convention
   mgrec* g1 = mgGetChild (db);
   mgrec* g2 = mgGetChild (g1);

   // get the names of these nodes
   char* g1Name = mgGetName (g1);
   char* g2Name = mgGetName (g2);

   // print the names
   printf ("g1 name: %s&#92;n", g1Name);
   printf ("g2 name: %s&#92;n", g2Name);

   // free the strings allocated for the names returned
   mgFree (g1Name);
   mgFree (g2Name);

   // no changes, just close the file
   mgCloseDb (db);

@pyex |
   # create a new OpenFlight file
   db = mgNewDb ("newfile.flt")

   # get the two group nodes created by convention
   g1 = mgGetChild (db)
   g2 = mgGetChild (g1)

   # get the names of these nodes
   g1Name = mgGetName (g1)
   g2Name = mgGetName (g2)

   # print the names
   print "g1 name:",g1Name
   print "g2 name:",g2Name

   # in Python, you don't "free" the strings

   # no changes, just close the file
   mgCloseDb (db)

@see <f mgNewDb>, <f mgOpenDb>, <f mgWriteDb>, <f mgSaveAsDb>, <f mgExportDb>, <f mgCloseDb>,
<f mgGetName>, <f mgFree>, <f mgGetChild>

@faqrelated
<faq_ref FAQ_00000003.What is the OpenFlight Scene Graph?>
<faq_ref FAQ_00000200.What format revisions of OpenFlight does the OpenFlight API support?>
<faq_ref FAQ_00001012.How do I determine the OpenFlight revision level of an OpenFlight database?>
<faq_ref FAQ_00000205.After making changes to the OpenFlight file in memory, how do I save my changes to disk?>
<faq_ref FAQ_00000206.If I change an OpenFlight file in memory, how do I discard those changes so they are not saved?>
<faq_ref FAQ_00000207.How do I save my changes to an OpenFlight file with a different file name?>
<faq_ref FAQ_00000208.If I save my changes to an OpenFlight file, which OpenFlight format revision will be written?>
<faq_ref FAQ_00000209.I want to save my OpenFlight file to a different OpenFlight format revision - How do I do that?>
<faq_ref FAQ_00000210.Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000205 | Question

@question
After making changes to the OpenFlight file in memory, how do I save my changes to disk?

@answer
There are several functions in the OpenFlight API to save OpenFlight files to disk. 
First, be aware that a database header node keeps track the OpenFlight file
to which it is currently associated. You can use the function <f mgRec2Filename>
to query this "file name". 

@answer
To save the OpenFlight Scene Graph of a header node to the file name currently associated
to the header node, use <f mgWriteDb>. To save the file to a different file name, use 
<f mgSaveAsDb>. To save the file to a different file name or different OpenFlight format 
revision, use <f mgExportDb>.

@exref The following examples (in C and Python) load an OpenFlight file into memory,
make some changes to the OpenFlight Scene Graph, save the changes to the original
file name, make a backup copy, and then finally close the file. |

@ex |
   // load "file.flt" into the OpenFlight Scene Graph
   mgrec* db = mgOpenDb ("file.flt");

   // make some changes to the db
   ...

   // save the changes to file.flt
   mgWriteDb (db);

   // also save a copy for "backup"
   mgSaveAsDb (db, "file_copy.flt");

   // finally, close the file
   mgCloseDb (db);

@pyex |
   # load "file.flt" into the OpenFlight Scene Graph
   db = mgOpenDb ("file.flt")

   # make some changes to the db
   ...

   # save the changes to file.flt
   mgWriteDb (db)

   # also save a copy for "backup"
   mgSaveAsDb (db, "file_copy.flt")

   # finally, close the file
   mgCloseDb (db)

@see <f mgOpenDb>, <f mgNewDb>, <f mgWriteDb>, <f mgSaveAsDb>, <f mgExportDb>, <f mgCloseDb>

@faqrelated
<faq_ref FAQ_00000200.What format revisions of OpenFlight does the OpenFlight API support?>
<faq_ref FAQ_00000201.How do I load an OpenFlight file into memory?>
<faq_ref FAQ_00000202.How do I create a brand new, empty, OpenFlight file in memory?>
<faq_ref FAQ_00001012.How do I determine the OpenFlight revision level of an OpenFlight database?>
<faq_ref FAQ_00000206.If I change an OpenFlight file in memory, how do I discard those changes so they are not saved?>
<faq_ref FAQ_00000207.How do I save my changes to an OpenFlight file with a different file name?>
<faq_ref FAQ_00000208.If I save my changes to an OpenFlight file, which OpenFlight format revision will be written?>
<faq_ref FAQ_00000209.I want to save my OpenFlight file to a different OpenFlight format revision - How do I do that?>
<faq_ref FAQ_00000210.Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000206 | Question

@question
If I change an OpenFlight file in memory, how do I discard those changes so they are not saved?

@answer
If you make changes to the OpenFlight Scene Graph in memory, those changes are only saved to 
disk if you explicitly do so using <f mgWriteDb>, <f mgSaveAsDb>, or <f mgExportDb>. If you call
<f mgCloseDb> without "saving" the file first, your in-memory changes will be discarded automatically.

@exref The following examples (in C and Python) open a file, make some changes but do not
save them before closing the file. If you do this, your changes are discarded. |

@ex |
   mgrec* db = mgOpenDb ("file.flt");
   // get the first group in the database
   mgrec* g1 = mgGetChild (db);
   // delete it, effectively deleting the entire contents
   mgDelete (g1);

   // but don't save changes... just close the file. file.flt remains intact
   mgCloseDb (db);

@pyex |
   db = mgOpenDb ("file.flt")
   # get the first group in the database
   g1 = mgGetChild (db)
   # delete it, effectively deleting the entire contents
   mgDelete (g1)

   # but don't save changes... just close the file. file.flt remains intact
   mgCloseDb (db)

@see <f mgOpenDb>, <f mgNewDb>, <f mgWriteDb>, <f mgSaveAsDb>, <f mgExportDb>, <f mgCloseDb>

@faqrelated
<faq_ref FAQ_00000200.What format revisions of OpenFlight does the OpenFlight API support?>
<faq_ref FAQ_00000201.How do I load an OpenFlight file into memory?>
<faq_ref FAQ_00000202.How do I create a brand new, empty, OpenFlight file in memory?>
<faq_ref FAQ_00001012.How do I determine the OpenFlight revision level of an OpenFlight database?>
<faq_ref FAQ_00000205.After making changes to the OpenFlight file in memory, how do I save my changes to disk?>
<faq_ref FAQ_00000207.How do I save my changes to an OpenFlight file with a different file name?>
<faq_ref FAQ_00000208.If I save my changes to an OpenFlight file, which OpenFlight format revision will be written?>
<faq_ref FAQ_00000209.I want to save my OpenFlight file to a different OpenFlight format revision - How do I do that?>
<faq_ref FAQ_00000210.Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000207 | Question

@question
How do I save my changes to an OpenFlight file with a different file name?

@answer
The function <f mgWriteDb> writes a database to the file name currently associated
to the corresponding header node. To save the database to a different file name, 
use <f mgSaveAsDb>. Note that Once the file has been saved to a "new" name, subsequent 
calls to <f mgWriteDb> will save the "new name", not the original name.

@exref The following examples (in C and Python) open a file, make some changes 
and save them out to a new file. |

@ex |
   mgrec* db = mgOpenDb ("fileA.flt");

   // make some changes to db
   ...

   // save changes to a new file
   mgSaveAsDb (db, "fileB.flt");

   // make some MORE changes to db
   ...

   // save changes again, this time using mgWriteDb
   // this will save (again) to "fileB.flt"
   mgWriteDb (db);

   // and as always, close the database when you're done
   mgCloseDb (db);

@pyex |
   db = mgOpenDb ("fileA.flt")

   # make some changes to db
   ...

   # save changes to a new file
   mgSaveAsDb (db, "fileB.flt")

   # make some MORE changes to db
   ...

   # save changes again, this time using mgWriteDb
   # this will save (again) to "fileB.flt"
   mgWriteDb (db)

   # and as always, close the database when you're done
   mgCloseDb (db)

@see <f mgOpenDb>, <f mgNewDb>, <f mgWriteDb>, <f mgSaveAsDb>, <f mgExportDb>, <f mgCloseDb>

@faqrelated
<faq_ref FAQ_00000200.What format revisions of OpenFlight does the OpenFlight API support?>
<faq_ref FAQ_00000201.How do I load an OpenFlight file into memory?>
<faq_ref FAQ_00000202.How do I create a brand new, empty, OpenFlight file in memory?>
<faq_ref FAQ_00001012.How do I determine the OpenFlight revision level of an OpenFlight database?>
<faq_ref FAQ_00000205.After making changes to the OpenFlight file in memory, how do I save my changes to disk?>
<faq_ref FAQ_00000206.If I change an OpenFlight file in memory, how do I discard those changes so they are not saved?>
<faq_ref FAQ_00000208.If I save my changes to an OpenFlight file, which OpenFlight format revision will be written?>
<faq_ref FAQ_00000209.I want to save my OpenFlight file to a different OpenFlight format revision - How do I do that?>
<faq_ref FAQ_00000210.Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000208 | Question

@question
If I save my changes to an OpenFlight file, which OpenFlight format revision will be written?

@answer
Each version of the OpenFlight API is built for a specific OpenFlight format revision. The format
revision built into a specific release of the OpenFlight API is often referred to as the <i native>
OpenFlight format revision of that OpenFlight API release. For example, the native OpenFlight 
format revision of OpenFlight API v14.0 is OpenFlight 16.4. So depending on which version of 
the OpenFlight API you are using, the native OpenFlight format revision of that release will
be written by default when you use <f mgWriteDb> or <f mgSaveAsDb>. 

@answer
As noted here, <f mgWriteDb> or <f mgSaveAsDb> will write the native OpenFlight format revision
of the OpenFlight API version you are using. If you need to write out a specific OpenFlight 
format revision, you can use <f mgExportDb>.

@answer
The table below lists the native OpenFlight format revisions corresponding to the current
and many past versions of the OpenFlight API.

<tablestart SIMPLE>
<tablerowstart HEADER>
<tableelementstart BORDER> OpenFlight API Version <tableelementend>
<tableelementstart BORDER> Native OpenFlight Format Revision <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v14.0 <tableelementend>
<tableelementstart BORDER> 16.4 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v5.0 (13.0) <tableelementend>
<tableelementstart BORDER> 16.4 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v4.2 <tableelementend>
<tableelementstart BORDER> 16.4 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v4.1 <tableelementend>
<tableelementstart BORDER> 16.4 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v4.0 <tableelementend>
<tableelementstart BORDER> 16.4 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v3.5 <tableelementend>
<tableelementstart BORDER> 16.3 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v3.4 <tableelementend>
<tableelementstart BORDER> 16.3 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v3.3 <tableelementend>
<tableelementstart BORDER> 16.2 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v3.2 <tableelementend>
<tableelementstart BORDER> 16.2 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v3.1 <tableelementend>
<tableelementstart BORDER> 16.1 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v3.0 <tableelementend>
<tableelementstart BORDER> 16.0 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v2.6 <tableelementend>
<tableelementstart BORDER> 15.8 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v2.5 <tableelementend>
<tableelementstart BORDER> 15.7 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v2.4 <tableelementend>
<tableelementstart BORDER> 15.7 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v2.3 <tableelementend>
<tableelementstart BORDER> 15.6 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v2.2 <tableelementend>
<tableelementstart BORDER> 15.6 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> v2.1 <tableelementend>
<tableelementstart BORDER> 15.6 <tableelementend>
<tablerowend>

<tableend>

@see <f mgOpenDb>, <f mgNewDb>, <f mgWriteDb>, <f mgSaveAsDb>, <f mgExportDb>, <f mgCloseDb>

@faqrelated
<faq_ref FAQ_00000200.What format revisions of OpenFlight does the OpenFlight API support?>
<faq_ref FAQ_00000201.How do I load an OpenFlight file into memory?>
<faq_ref FAQ_00000202.How do I create a brand new, empty, OpenFlight file in memory?>
<faq_ref FAQ_00001012.How do I determine the OpenFlight revision level of an OpenFlight database?>
<faq_ref FAQ_00000205.After making changes to the OpenFlight file in memory, how do I save my changes to disk?>
<faq_ref FAQ_00000206.If I change an OpenFlight file in memory, how do I discard those changes so they are not saved?>
<faq_ref FAQ_00000207.How do I save my changes to an OpenFlight file with a different file name?>
<faq_ref FAQ_00000209.I want to save my OpenFlight file to a different OpenFlight format revision - How do I do that?>
<faq_ref FAQ_00000210.Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000209 | Question

@question
I want to save my OpenFlight file to a different OpenFlight format revision - How do I do that?

@answer
By default <f mgWriteDb> or <f mgSaveAsDb> will write the native OpenFlight format revision
of the OpenFlight API version you are using. If you need to write out a different OpenFlight 
format revision, you can use <f mgExportDb>.

@answer
The OpenFlight API can export to the following OpenFlight format revisions:<nl>
16.3<nl>
16.2<nl>
16.1<nl>
16.0<nl>
15.8<nl>
15.7<nl>
15.6<nl>
15.4

@see <f mgOpenDb>, <f mgNewDb>, <f mgWriteDb>, <f mgSaveAsDb>, <f mgExportDb>, <f mgCloseDb>

@faqrelated
<faq_ref FAQ_00000200.What format revisions of OpenFlight does the OpenFlight API support?>
<faq_ref FAQ_00000201.How do I load an OpenFlight file into memory?>
<faq_ref FAQ_00000202.How do I create a brand new, empty, OpenFlight file in memory?>
<faq_ref FAQ_00001012.How do I determine the OpenFlight revision level of an OpenFlight database?>
<faq_ref FAQ_00000205.After making changes to the OpenFlight file in memory, how do I save my changes to disk?>
<faq_ref FAQ_00000206.If I change an OpenFlight file in memory, how do I discard those changes so they are not saved?>
<faq_ref FAQ_00000207.How do I save my changes to an OpenFlight file with a different file name?>
<faq_ref FAQ_00000208.If I save my changes to an OpenFlight file, which OpenFlight format revision will be written?>
<faq_ref FAQ_00000210.Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00000210 | Question

@question
Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?

@answer
Unlike Creator, the OpenFlight API cannot export to other file formats. 
The OpenFlight API can only write the OpenFlight file format. 

@answer
Use functions <f mgWriteDb> or <f mgSaveAsDb> to write the native OpenFlight format 
revision of the OpenFlight API version you are using. Use <f mgExportDb> to write 
out a different OpenFlight format revision.

@see <f mgOpenDb>, <f mgNewDb>, <f mgWriteDb>, <f mgSaveAsDb>, <f mgExportDb>, <f mgCloseDb>

@faqrelated
<faq_ref FAQ_00000200.What format revisions of OpenFlight does the OpenFlight API support?>
<faq_ref FAQ_00000201.How do I load an OpenFlight file into memory?>
<faq_ref FAQ_00000202.How do I create a brand new, empty, OpenFlight file in memory?>
<faq_ref FAQ_00001012.How do I determine the OpenFlight revision level of an OpenFlight database?>
<faq_ref FAQ_00000205.After making changes to the OpenFlight file in memory, how do I save my changes to disk?>
<faq_ref FAQ_00000206.If I change an OpenFlight file in memory, how do I discard those changes so they are not saved?>
<faq_ref FAQ_00000207.How do I save my changes to an OpenFlight file with a different file name?>
<faq_ref FAQ_00000208.If I save my changes to an OpenFlight file, which OpenFlight format revision will be written?>
<faq_ref FAQ_00000210.Can I save the OpenFlight file as a different format, like Wavefront OBJ or AutoCAD DXF?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001050 | Question

@question
How do I apply a matrix (transformation) to a node?

@answer
To transform a node, you will attach one or more transformation records to it.
Each transformation record describes a discrete transformation (translate, rotate, scale,
etc) applied to the node.  
The order the transformation records are attached to the node define the order in
which the transformations are applied.  For example a node transformed 
by a translate and then a scale will be different than if it was transformed
by the scale and then the translate.

@answer 
There are many benefits (from a modeling and programming point of view) to attaching
separate transformations rather than just one single matrix.  The biggest benefit is that you
can more easily compose and decompose the transformation if they are broken out into separate 
parts.  For example if you Translate, Rotate and Scale a node, you can modify the Rotate part 
separately without having to do all the matrix math to make the "final" matrix.

@answer
<tablestart SIMPLE>
<tablerowstart HEADER>
<tableelementstart BORDER> Transformation Type <tableelementend>
<tableelementstart BORDER> Description <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltXmGeneral> <tableelementend>
<tableelementstart BORDER> General 4x4 Matrix <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltXmPut> <tableelementend>
<tableelementstart BORDER> Put <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltXmRotate> <tableelementend>
<tableelementstart BORDER> Rotate about Point <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltXmRotateEdge> <tableelementend>
<tableelementstart BORDER> Rotate about Edge <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltXmScale> <tableelementend>
<tableelementstart BORDER> Scale <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltXmScaleToPoint> <tableelementend>
<tableelementstart BORDER> Scale to Point <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltXmTranslate> <tableelementend>
<tableelementstart BORDER> Translate <tableelementend>
<tablerowend>

<tableend>

@answer
You create a transformation record using <f mgNewRec>.  
You set the attributes of a transformation record just like any other
record type using <f mgSetAttList>, <f mgSetCoord3d>, etc.
Finally you attach a transformation record to a node using 
<f mgAttach>, <f mgAppend> or <f mgInsert>.

@exref The following examples (in C and Python) apply a scale and 
then a translate transformation (in that order) to a <p node>. |

@ex |
   mgrec* scale;
   mgrec* translate;

   // create the scale transformation
   scale = mgNewRec (fltXmScale);

   // create the translate transformation
   translate = mgNewRec (fltXmTranslate);

   // set the parameters of the scale
   // scale about the origin
   mgSetCoord3d (scale, fltXmScaleCenter, 0.0, 0.0, 0.0);

   // scale uniformly by 2
   mgSetAttList (scale, 
         fltXmScaleX, 2.0, 
         fltXmScaleY, 2.0, 
         fltXmScaleZ, 2.0, 
         MG_NULL);

   // set the parameters of the translation
   // translate by 10,10
   mgSetCoord3d (translate, fltXmTranslateDelta, 10.0, 10.0, 0.0);

   // attach the transformations so we scale first, then translate
   mgAttach (node, scale);
   mgAppend (node, translate);  // note the translate is "appended"

@pyex |
   # create the scale transformation
   scale = mgNewRec (fltXmScale)

   # create the translate transformation
   translate = mgNewRec (fltXmTranslate)

   # set the parameters of the scale
   # scale about the origin
   mgSetCoord3d (scale, fltXmScaleCenter, 0.0, 0.0, 0.0)

   # scale uniformly by 2
   mgSetAttList (scale, 
         fltXmScaleX, 2.0, 
         fltXmScaleY, 2.0, 
         fltXmScaleZ, 2.0)

   # set the parameters of the translation
   # translate by 10,10
   mgSetCoord3d (translate, fltXmTranslateDelta, 10.0, 10.0, 0.0)

   # attach the transformations so we scale first, then translate
   mgAttach (node, scale)
   mgAppend (node, translate)  # note the translate is "appended"

@see <f mgNewRec>, <f mgAttach>, <f mgAppend>, <f mgInsert>

@faqrelated
<faq_ref FAQ_00001051.How do I get the matrix (transformation) from a node?>
<faq_ref FAQ_00001043.How do I create an external reference in a master database?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001044 | Question

@question
How do I create a simple polygon with vertices?

@answer
As you create any new node in your database, you use <f mgNewRec> to make a polygon node,
specifying <f fltPolygon>. Then for each vertex of the polygon, you use <f mgNewRec>
again, this time specifying <f fltVertex>. You will add the polygon into the hierarchy
and attach each new vertex to the new polygon. You will use <f mgAttach>, <f mgAppend> or
<f mgInsert> to add the polygon to the scene graph as well as the vertices to the new polygon.

@exref The following examples (in C and Python) define a function
to create a new quadrilateral polygon. It's lower left corner will be the 
origin and will be positioned on the XY plane. It will measure 2 units in the X 
direction and 1 unit in Y. The new polygon will be "lit" and the vertex normals will be 
set to point in the same direction as the polygon normal. |

@ex |

   static void CreatePolygon (mgrec* parentObject)
   {
      mgvectord faceNormal;
      mgrec* vtx1;
      mgrec* vtx2;
      mgrec* vtx3;
      mgrec* vtx4;
      mgrec* face;
 
      // create a polygon node
      face = mgNewRec (fltPolygon);

      // attach the new polygon as the first child of the parent object
      mgAttach (parentObject, face);

      // create 4 vertices (for the quadrilateral)
      vtx1 = mgNewRec (fltVertex);
      vtx2 = mgNewRec (fltVertex);
      vtx3 = mgNewRec (fltVertex);
      vtx4 = mgNewRec (fltVertex);

      // attach the vertices. mgAttach is the most efficient
      // but attaches as first child. To get in proper order
      // using mgAttach, attach last vertex first.

      mgAttach (face, vtx4);
      mgAttach (face, vtx3);
      mgAttach (face, vtx2);
      mgAttach (face, vtx1);     // vtx1 is "first" vertex of polygon

      // set the positions of the new vertices
      mgSetVtxCoord (vtx1, 0.0, 0.0, 0.0);
      mgSetVtxCoord (vtx2, 2.0, 0.0, 0.0);
      mgSetVtxCoord (vtx3, 2.0, 1.0, 0.0);
      mgSetVtxCoord (vtx4, 0.0, 1.0, 0.0);

      // we know the polygon normal is (0,0,1) because it lies in 
      // the XY plane but we'll calculate it for sake of example
      mgGetPolyNormal (face, &faceNormal.i, &faceNormal.j, &faceNormal.k);

      // apply this normal to each vertex
      mgSetVtxNormal (vtx1, faceNormal.i, faceNormal.j, faceNormal.k);
      mgSetVtxNormal (vtx2, faceNormal.i, faceNormal.j, faceNormal.k);
      mgSetVtxNormal (vtx3, faceNormal.i, faceNormal.j, faceNormal.k);
      mgSetVtxNormal (vtx4, faceNormal.i, faceNormal.j, faceNormal.k);

      // finally, set the polygon to be lit
      mgSetAttList (face, fltGcLightMode, 2, MG_NULL);
   }

@pyex |

   def CreatePolygon (parentObject):
      # create a polygon node
      face = mgNewRec (fltPolygon)

      # attach the new polygon as the first child of the parent object
      mgAttach (parentObject, face)

      # create 4 vertices (for the quadrilateral)
      vtx1 = mgNewRec (fltVertex)
      vtx2 = mgNewRec (fltVertex)
      vtx3 = mgNewRec (fltVertex)
      vtx4 = mgNewRec (fltVertex)

      # attach the vertices. mgAttach is the most efficient
      # but attaches as first child. To get in proper order
      # using mgAttach, attach last vertex first.

      mgAttach (face, vtx4)
      mgAttach (face, vtx3)
      mgAttach (face, vtx2)
      mgAttach (face, vtx1)	# vtx1 is "first" vertex of polygon

      # set the positions of the new vertices
      mgSetVtxCoord (vtx1, 0.0, 0.0, 0.0)
      mgSetVtxCoord (vtx2, 2.0, 0.0, 0.0)
      mgSetVtxCoord (vtx3, 2.0, 1.0, 0.0)
      mgSetVtxCoord (vtx4, 0.0, 1.0, 0.0)

      # we know the polygon normal is (0,0,1) because it lies in 
      # the XY plane but we'll calculate it for sake of example

      b, i, j, k = mgGetPolyNormal (face)

      # apply this normal to each vertex
      mgSetVtxNormal (vtx1, i, j, k)
      mgSetVtxNormal (vtx2, i, j, k)
      mgSetVtxNormal (vtx3, i, j, k)
      mgSetVtxNormal (vtx4, i, j, k)

      # finally, set the polygon to be lit
      mgSetAttList (face, fltGcLightMode, 2)

@see <f mgNewRec>, <f mgAttach>, <f mgAppend>, <f mgInsert>, 
<f mgSetVtxCoord>, <f mgSetVtxNormal>, <f mgSetAttList>

@faqrelated
<faq_ref FAQ_00001042.How do I create a new node in a database?>
<faq_ref FAQ_00001043.How do I create an external reference in a master database?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001051 | Question

@question
How do I get the matrix (transformation) from a node?

@answer
The effective transformation applied to a node is the cumulation
of all the transformation records attached to the node.  There are two ways 
to get to the transformations applied to a node.

@answer
The first, if you just want the composite matrix, is to use
<f mgGetMatrix>.  This returns the cumulative matrix calculated from
each of the transformations attached to a node.  Note that this
cumulative matrix does not include any transformations applied 
to the parent or children of the node.  

@answer
The second, if you want each of the separate transformations, is to use
<f mgGetXform> and then <f mgGetNext> to loop through each of the
transformations applied.

@exref The following examples (in C and Python) show how to get the
transformation(s) applied to a <p node>. |

@ex This example shows how to get the composite matrix representing 
all the transformation records applied to a <p node> : |

   mgmatrix matrix;

   mgGetMatrix (node, fltMatrix, &matrix);

@ex This example shows how to loop over all the transformation records
applied to a <p node> : |
   mgbool hasXforms;

   hasXforms = mgHasXform (node);

   if (hasXforms == MG_TRUE) 
   {
      mgrec* transform;
      int transformType;

      // get the first transformation attached
      transform = mgGetXform (node);

      while (transform != MG_NULL) {
         // check what kind of transformation this is
         transformType = mgGetXformType (transform);
         
         // here are the possible types:
         switch (transformType) 
         {
         case MXLL_TRANSLATE: printf ("MXLL_TRANSLATE&#92;n"); break;
         case MXLL_SCALE:     printf ("MXLL_SCALE&#92;n");     break;
         case MXLL_ROTEDGE:   printf ("MXLL_ROTEDGE&#92;n");   break;
         case MXLL_ROTPT:     printf ("MXLL_ROTPT&#92;n");     break;
         case MXLL_PUT:       printf ("MXLL_PUT&#92;n");       break;
         case MXLL_TOPOINT:   printf ("MXLL_TOPOINT&#92;n");   break;
         case MXLL_GENERAL:   printf ("MXLL_GENERAL&#92;n");   break;
         }

         // get the next transformation attached
         transform = mgGetNext (transform);
      }
   }

@pyex This example shows how to get the composite matrix representing 
all the transformation records applied to a <p node> : |
   b, matrix = mgGetMatrix (node, fltMatrix);

@pyex This example shows how to loop over all the transformation records
applied to a <p node> : |
   if (hasXforms == MG_FALSE):
      return;

   # get the first transformation attached
   transform = mgGetXform (node)	
   while (transform):
      # check what kind of transformation this is
      transformType = mgGetXformType (transform)

      if (transformType == MXLL_TRANSLATE):
         print "MXLL_TRANSLATE"
      elif (transformType == MXLL_SCALE):
         print "MXLL_SCALE"
      elif (transformType == MXLL_ROTEDGE):
         print "MXLL_ROTEDGE"
      elif (transformType == MXLL_ROTPT):
         print "MXLL_ROTPT"
      elif (transformType == MXLL_PUT):
         print "MXLL_PUT"
      elif (transformType == MXLL_SCALE):
         print "MXLL_SCALE"		
      elif (transformType == MXLL_TOPOINT):
         print "MXLL_TOPOINT"
      elif (transformType == MXLL_GENERAL):
         print "MXLL_GENERAL"

      # get the next transformation attached
      transform = mgGetNext (transform)

@see <f mgHasXform>, <f mgGetXformType>, <f mgGetNext>, <f mgGetMatrix>

@faqrelated
<faq_ref FAQ_00001050.How do I apply a matrix (transformation) to a node?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001000 | Question

@question
What is an mgrec?

@answer
The <t mgrec> type is a generic (polymorphic) type used to access different 
types of records defined by the OpenFlight API.  Primarily, objects of type 
<t mgrec> represent nodes in the OpenFlight hierarchy.  Other objects (records)
represented as <t mgrec> include Transformation records, Palette records, 
Bounding Box records, etc.

@answer
The <t mgrec> type is an opaque type.  In other words you cannot access the
fields of this structure directly.  The OpenFlight API provides functions to
access the fields of the records of this type.  Different functions in the
API access different types of <t mgrec> records.  The <b Function Categories>
section of this reference document is organized (loosely) based on these different
record types.

@faqrelated
<faq_ref FAQ_00000003.What is the OpenFlight Scene Graph?>
<faq_ref FAQ_00001001.What is the OpenFlight Data Dictionary?>
<faq_ref FAQ_00001002.How can I tell what kind of record I have in an mgrec?>
<faq_ref FAQ_00001003.How do I get the attributes of a record in the database?>
<faq_ref FAQ_00001004.How do I set the attributes of a record in the database?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001001 | Question

@question
What is the OpenFlight Data Dictionary?

@answer
The OpenFlight Data Dictionary is a data schema that defines the records and fields
that comprise all the elements in an OpenFlight database.  In this way, the OpenFlight
Data Dictionary can be thought of as a "map" that you will use to access elements
in the OpenFlight scene.

@answer
Each record type defined in the OpenFlight Data Dictionary has a unique code associated
to it.  This code is used to identify the type of record it is.  For each record type
there is a corresponding record schema that
defines the fields of that record.  Like a record, each field also has a unique
code associated to it.  The definition of a record field includes its
<b code> and <b type> as well as a brief description of the field.  The <b code> and 
<b type> of a record field are very important.  The <b code> is the "key" by which
that field is known and accessed.  The <b type> tells you the kind and size of the
data type used to hold field values.

@answer
The OpenFlight Data Dictionary is documented as a part of this reference document.
You will find it a valuable resource as you develop OpenFlight API programs and 
plug-ins as well as OpenFlight scripts.  

@answer
Here is a link to the OpenFlight Data Dictionary for you to bookmark:

@answer
<tlink _blank.\.\./openflightdd/default\.htm.OpenFlight Data Dictionary>

@faqrelated
<faq_ref FAQ_00001000.What is an mgrec?>
<faq_ref FAQ_00000003.What is the OpenFlight Scene Graph?>
<faq_ref FAQ_00001003.How do I get the attributes of a record in the database?>
<faq_ref FAQ_00001004.How do I set the attributes of a record in the database?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001002 | Question

@question
How can I tell what kind of record I have in an mgrec?

@answer
As mentioned above, the <t mgrec> type is a generic type used to access different 
types of records defined by the OpenFlight API.  Since that is the case, you may not 
always know what kind of record you have in any given <t mgrec>.  For the most part, 
this should not be a problem in your code when you know where the record came
from.  For example if the record was returned by <f mgOpenDb> or <f mgNewDb>, 
you know it is a node record of type <flt fltHeader>.

@answer
There will be situations in which you don't know what kind of record you have.
Consider this scenario.  You want to find all the polygon nodes in the scene 
and perform some action on each of them.  You would likely use <f mgWalk> to 
visit all the nodes in a database hierarchy and when you find a polygon node, 
perform the action on each that you find.  When you use <f mgWalk> you provide
walk action functions that will be called for each node in the hierarchy as 
it is visited.  The node currently being visited is passed as a parameter to
your walk action function.  To filter out all but the polygon node records,
your action function would query the node it is passed.  In this way your 
function could simply ignore records that are not polygon nodes and process 
only those that are.

@answer
This is very easy to do using <f mgGetCode>.  You pass an <t mgrec> record to 
<f mgGetCode> and it returns the unique code associated to that record.  This 
code tells you exactly what kind of record you have.  

@exref The following examples (in C and Python) show how to use <f mgGetCode>
to interrogate a record <p rec> for its type (<p code>).  You can see how easily 
this code could be included in your walk action function and used to find
just the polygon node records. |

@ex |

   // call mgGetCode to return the "code" associated to rec
   mgcode code = mgGetCode (rec);

   // there are many possible record "codes"
   // here are some common types

   if (code == fltHeader)           // database header node
      printf ("fltHeader");
   else if (code == fltGroup)       // group node
      printf ("fltGroup");
   else if (code == fltObject)      // object node
      printf ("fltObject");
   else if (code == fltPolygon)     // polygon node
      printf ("fltPolygon");
   else if (code == fltVertex)      // vertex node
      printf ("fltVertex");
   else if (code == fltXmTranslate) // translate transformation
      printf ("fltXmTranslate");
   else if (code == fltFMaterial)   // material palette entry
      printf ("fltFMaterial");
   else
      printf ("some other kind, there are many!!");

@pyex |

   # call mgGetCode to return the "code" associated to rec
   code = mgGetCode (rec)

   # there are many possible record "codes"
   # here are some common types

   if (code == fltHeader):        # database header node
      print "fltHeader"
   elif (code == fltGroup):       # group node
      print "fltGroup"
   elif (code == fltObject):      # object node
      print "fltObject"   
   elif (code == fltPolygon):     # polygon node
      print "fltPolygon"
   elif (code == fltVertex):      # vertex node
      print "fltVertex"   
   elif (code == fltXmTranslate): # translate transformation
      print "fltXmTranslate"
   elif (code == fltFMaterial):   # material palette entry
      print "fltFMaterial"
   else:
      print "some other kind, there are many!!"

@see <f mgGetCode>

@faqrelated
<faq_ref FAQ_00001000.What is an mgrec?>
<faq_ref FAQ_00000003.What is the OpenFlight Scene Graph?>
<faq_ref FAQ_00001001.What is the OpenFlight Data Dictionary?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001003 | Question

@question
How do I get the attributes of a record in the database?

@answer
The <OFDD> defines the fields
that are contained in any record type.  If you know what kind of 
record you have, check the <OFDD> to see the fields that are defined
for that record type.  You then choose which field you want to "get" 
and use one of several OpenFlight API functions to access that field data.

@answer
The most common function to use is <f mgGetAttList>.  In its simplest
form (to retrieve a single value), you provide a <p rec>, a field <p code>
and an <p address>.  The <p rec> is the record you want to query.  
The <p code> identifies the field whose value you want.  The <p address> points 
to memory that is appropriate (in size and type) to receive the value of the 
record attribute.  Note that you can provide additional <p code> and
<p address> pairs to retrieve multiple values simultaneously.

@answer
The <p address> part can be a bit tricky.  This is where the <OFDD> can 
really help.  Here is an excerpt from the <OFDD> showing some of the
fields of the <flt fltPolyon> record. 

@answer
<q
record fltPolygon {
&nbsp;&nbsp;&nbsp;\.\.\.
&nbsp;&nbsp;&nbsp;short(2)         fltPolyTexture            Texture pattern index (-1 if none)
&nbsp;&nbsp;&nbsp;unsigned int(4)  fltPolyPrimeColor         Primary Color Index
&nbsp;&nbsp;&nbsp;float(4)         fltPolyPrimeIntensity     Primary Color Intensity
&nbsp;&nbsp;&nbsp;mgbool(4)        fltPolyTerrain            TRUE if geometry is terrain
&nbsp;&nbsp;&nbsp;char*(variable)  fltComment                Comment Text
&nbsp;&nbsp;&nbsp;\.\.\.
}
>

@answer
The second column is the <b code> associated to the field. For each field
defined in the record, a data type (and size) is listed in the first column.
This tells you what kind of <p address> to provide to <f mgGetAttList> for each field.

@answer
In the excerpt shown above, you can see that the <b fltPolyTexture> field is a <mono short>
integer of length 2 bytes.  Similarly, <b fltPolyPrimeColor> is an <mono unsigned int>
(4 bytes) and <b fltPolyPrimeIntensity> is a <mono float> (4 bytes).

@exref The examples below (in C and Python) 
show you how you would use <f mgGetAttList> (and what kind
of address to use for each of these attributes) to retrieve the texture and color
fields from a polygon node record <p polygon>. |

@ex |
   short textureIndex;
   unsigned int colorIndex;
   float colorIntensity;
   int numAttr;

   numAttr = mgGetAttList (polygon, 
                  fltPolyTexture, &textureIndex,
                  fltPolyPrimeColor, &colorIndex,
                  fltPolyPrimeIntensity, &colorIntensity,
                  MG_NULL);
   if (numAttr == 3)
   {
      // all the values were retrieved successfully
      printf ("Texture Index:   %d&#92;", textureIndex);
      printf ("Color Index:     %d&#92;", colorIndex);
      printf ("Color Intensity: %f&#92;", colorIntensity);
   }

@pyex |

   outs = mgGetAttList (polygon, 
         fltPolyTexture, fltPolyPrimeColor, fltPolyPrimeIntensity)

   # outs is a tuple with 7 elements as follows:
   # outs[0] = number of attributes returned, 3 if successful
   # outs[1] = fltPolyTexture
   # outs[2] = value of fltPolyTexture
   # outs[3] = fltPolyPrimeColor
   # outs[4] = value of fltPolyPrimeColor
   # outs[5] = fltPolyPrimeIntensity
   # outs[6] = value of fltPolyPrimeIntensity

   numAttr = outs[0]
   if (numAttr == 3):
      # all the values were retrieved successfully
      print "Texture Index:  ",outs[2]
      print "Color Index:    ",outs[4]
      print "Color Intensity:",outs[6]

@see <f mgGetAttList>

@faqrelated
<faq_ref FAQ_00001000.What is an mgrec?>
<faq_ref FAQ_00001001.What is the OpenFlight Data Dictionary?>
<faq_ref FAQ_00001004.How do I set the attributes of a record in the database?>
<faq_ref FAQ_00001005.How do I get a string attribute of a record in the database?>
<faq_ref FAQ_00001007.What is the best way to get the coordinates (position) of a vertex node record?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001004 | Question

@question
How do I set the attributes of a record in the database?

@answer
The <OFDD> defines the fields
that are contained in any record type.  If you know what kind of 
record you have, check the <OFDD> to see the fields that are defined
for that record type.  You then choose which field you want to "set" 
and use one of several OpenFlight API functions to set that field data.

@answer
The most common function to use is <f mgSetAttList>.  In its simplest
form (to set a single value), you provide a <p rec>, a field <p code>
and a <p value>.  The <p rec> is the record whose value you want to set.  
The <p code> identifies the field of the record you want to set.  
The <p value> is the value you want to set.  Note that you can provide 
additional <p code> and <p value> pairs to set multiple values simultaneously.

@answer
The <OFDD> can help you with the <p value> parameter.
Here is an excerpt showing some of the
fields of the <flt fltObject> record. 

@answer
<q
record fltObject {
&nbsp;&nbsp;&nbsp;\.\.\.
&nbsp;&nbsp;&nbsp;mgbool(4)        fltObjNoDay            Do not display in daylight
&nbsp;&nbsp;&nbsp;char*(variable)  fltComment             Comment Text
&nbsp;&nbsp;&nbsp;\.\.\.
}
>

@answer
The second column is the <b code> associated to the field.  For each field
defined in the record, a data type (and size) is listed in the first column.
This tells you what kind of <p value> to provide to <f mgSetAttList> for each field.

@answer
In the excerpt shown above, you can see that the <b fltObjNoDay> field is a <mono mgbool>
value and that <b fltComment> is a <mono char*> (string) value.  

@exref The examples below (in C and Python) 
show you how you would use <f mgSetAttList> to set the Inhibit Display Day flag and 
comment for an object node record <p object>. |

@ex |
   int numAttr;

   numAttr = mgSetAttList (object, 
                  fltObjNoDay, MG_TRUE,
                  fltComment, "This object is not drawn in day",
                  MG_NULL);
   if (numAttr == 2)
   {
      // all the values were set successfully
      printf ("Object attributes set successfully");
   }

@pyex |

   numAttr = mgSetAttList (object, 
                  fltObjNoDay, MG_TRUE,
                  fltComment, "This object is not drawn in day")
   if (numAttr == 2):
      # all the values were set successfully
      print "Object attributes set successfully"

@see <f mgSetAttList>

@faqrelated
<faq_ref FAQ_00001000.What is an mgrec?>
<faq_ref FAQ_00001001.What is the OpenFlight Data Dictionary?>
<faq_ref FAQ_00001003.How do I get the attributes of a record in the database?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001005 | Question

@question
How do I get a string attribute of a record in the database?

@answer
When you use <f mgGetAttList> to retrieve a string attribute from a record, 
there are some special considerations to keep in mind.  For this discussion, 
consider the <fltf fltHeader.fltHdrLastDate> field of the <flt fltHeader> record as shown
in this excerpt from the <OFDD>:

@answer
<q
record fltHeader {
&nbsp;&nbsp;&nbsp;\.\.\.
&nbsp;&nbsp;&nbsp;char* (32)	     fltHdrLastDate	       Date and time of last revision
&nbsp;&nbsp;&nbsp;\.\.\.
}
>

@answer
You can see that this attribute is a <mono char*> of length 32 bytes. In 
other words, it is a string of length 32.  The <p address> you provide
to <f mgGetAttList> for string attributes should be the "address" of a 
<mono char*> value.  If <f mgGetAttList> succeeds, it will allocate a 
string and copy the value of the record attribute to the allocated string.
The address you provide will "point" to the allocated string.
Since the string attribute is allocated, you must deallocate
it after you are done with it (in C, but not in Python) to avoid 
a memory leak.

@exref The following examples (in C and Python) show how to retrieve
a string attribute from a node record and how to dispose of it when
you are done with it. |

@ex |
   char* date = MG_NULL;
   int numAttr;
   
   numAttr = mgGetAttList (header,
                  fltHdrLastDate, &date,
                  MG_NULL);

   if ((numAttr == 1) && (date != NULL)) {
      // date now points to a character string filled with 
      // the fltHdrLastDate attribute value
      printf ("Last modified: %s&#92;", date);

      // you need to free the memory when you are done with it!
      mgFree (date);
   }

@pyex |
   outs = mgGetAttList (header, fltHdrLastDate)
   # outs is a tuple with 3 elements as follows:
   # outs[0] = number of attributes returned, 1 if successful
   # outs[1] = fltHdrLastDate
   # outs[2] = value of fltHdrLastDate
   numAttr = outs[0]
   if (numAttr == 1):
      date = outs[2]
      print "Last modified:", date
      # no need to deallocate the memory in Python

@see <f mgGetAttList>

@faqrelated
<faq_ref FAQ_00001003.How do I get the attributes of a record in the database?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001006 | Question

@question
How do I access a value in a record nested inside another record?

@answer
The <OFDD> defines the fields that are contained in any record type.
Fields contained in a record may be values or may be nested records
themselves that contain other fields, etc.

@answer
To access any value (nested or not) of a record, you typically will use
<f mgGetAttList> (to get the value) and <f mgSetAttList> (to set the value).  
For each of these functions, you specify a <p rec> and a <p code>.  The <p code>
represents the field in <p rec> you want to get or set.  These functions will 
automatically look for <p code> in nested records of <p rec> - so you don't have 
to do anything special as long as <p code> is found in just one nested record.

@answer
Consider the <flt fltVertex> record in the <OFDD> as shown here:

@answer
<q
record fltVertex {
&nbsp;&nbsp;&nbsp;\.\.\.
&nbsp;&nbsp;&nbsp;record fltCoord3d  fltCoord3d   double precision float coordinate X,Y,Z
&nbsp;&nbsp;&nbsp;\.\.\.
}
record fltCoord3d {
&nbsp;&nbsp;&nbsp;double(8)          fltCoord3dX  X component of coordinate
&nbsp;&nbsp;&nbsp;double(8)          fltCoord3dY  Y component of coordinate
&nbsp;&nbsp;&nbsp;double(8)          fltCoord3dZ  Z component of coordinate
}
>

@answer
Notice that <flt fltVertex> contains a nested <flt fltCoord3d> record.
If you wanted to set the <b fltCoord3dX> attribute of the nested <flt fltCoord3d> record 
on a <flt fltVertex>, simply pass a <flt fltVertex> record to <f mgSetAttList> and specify
<b fltCoord3dX> for <p code>.  Since <b fltCoord3dX> is defined just once in the nested 
record structure, <f mgSetAttList> will know which field you mean.

@answer
<q mgSetAttList (vertex, fltCoord3dX, 2\.0, MG_NULL);>

@answer
Now if <p code> is contained in more than one nested record, there is an ambiguity and
<f mgGetAttList> and <f mgSetAttList> won't know which <p code> you mean.  Note that these 
functions will find one of the nested fields but it is not defined which field that will be.

@answer
Consider the <flt fltXmTranslate> record which contains two nested <flt fltCoord3d> records:

<q
record fltXmTranslate  {
&nbsp;&nbsp;&nbsp;record fltCoord3d	fltXmTranslateFrom   reference FROM point
&nbsp;&nbsp;&nbsp;record fltCoord3d	fltXmTranslateDelta  Delta to translate node by
}
>

@answer 
In this case if you wanted to set the <b fltCoord3dX> attribute of the nested 
<fltf fltXmTranslate.fltXmTranslateFrom> record on <flt fltXmTranslate>, you cannot simply pass 
a <flt fltXmTranslate> record to <f mgSetAttList> because <b fltCoord3dX> is defined 
in both <fltf fltXmTranslate.fltXmTranslateFrom> and <flt fltXmTranslateDelta> nested records.
<f mgSetAttList> won't know which <b fltCoord3dX> you mean.

@answer
To resolve this ambiguity you have two choices.  For common nested record types,
like <flt fltCoord3d> and several others, the OpenFlight API provides "convenience" functions to 
get/set the nested record components.  For example <f mgGetCoord3d> retrieves the X, Y and Z 
components of a nested <flt fltCoord3d> record while <f mgSetCoord3d> sets them.  You specify 
the code of the nested <flt fltCoord3d> record you want to access.  In the case of <flt fltXmTranslate> 
above, the following example shows how you would set values on each of the nested <flt fltCoord3d> records.

@answer
<q
   // set the components on the fltXmTranslateFrom nested record
   mgSetCoord3d (translate, fltXmTranslateFrom, 0\.0, 0\.0, 0\.0);
 &nbsp;
   // set the components on the fltXmTranslateDelta nested record
   mgSetCoord3d (translate, fltXmTranslateDelta, 10\.0, 5\.0, 0\.0);>

@answer
As noted above, there are several nested records for which OpenFlight API convenience functions
are defined.  Here are some:

@answer
<tablestart SIMPLE>
<tablerowstart HEADER>
<tableelementstart BORDER> Nested Record Type <tableelementend>
<tableelementstart BORDER> Get Function <tableelementend>
<tableelementstart BORDER> Set Function <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltCoord2i> <tableelementend>
<tableelementstart BORDER> <f mgGetCoord2i> <tableelementend>
<tableelementstart BORDER> <f mgSetCoord2i> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltCoord3f> <tableelementend>
<tableelementstart BORDER> <f mgGetCoord3f> <tableelementend>
<tableelementstart BORDER> <f mgSetCoord3f> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltCoord3d> <tableelementend>
<tableelementstart BORDER> <f mgGetCoord3d> <tableelementend>
<tableelementstart BORDER> <f mgSetCoord3d> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltDPlane> <tableelementend>
<tableelementstart BORDER> <f mgGetPlane> <tableelementend>
<tableelementstart BORDER> <f mgSetPlane> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltMatrix> <tableelementend>
<tableelementstart BORDER> <f mgGetMatrix> <tableelementend>
<tableelementstart BORDER> <f mgSetMatrix> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltColorRGBA> <tableelementend>
<tableelementstart BORDER> <f mgGetColorRGBA> <tableelementend>
<tableelementstart BORDER> <f mgSetColorRGBA> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltNormColor> <tableelementend>
<tableelementstart BORDER> <f mgGetNormColor> <tableelementend>
<tableelementstart BORDER> <f mgSetNormColor> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltVector> <tableelementend>
<tableelementstart BORDER> <f mgGetVector> <tableelementend>
<tableelementstart BORDER> <f mgSetVector> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <flt fltVectord> <tableelementend>
<tableelementstart BORDER> <f mgGetVectord> <tableelementend>
<tableelementstart BORDER> <f mgSetVectord> <tableelementend>
<tablerowend>

<tableend>

@answer
Finally you have one more option when accessing fields of nested records.
The function <f mgGetAttRec> can be used to get a pointer to the nested
record which in turn can be passed to <f mgGetAttList> or <f mgSetAttList>.
In this way, you control how to resolve any ambiguity in the nested record 
structure.  The following example shows how <f mgGetAttRec> could be used
to resolve the ambiguity when accessing fields of nested records in
<flt fltXmTranslate>.  While the example shows how to set the field 
in the nested record using <f mgSetAttList>, it works the same way when 
using <f mgGetAttList> to get the field value.

<q
   mgrec* coordRec;
   // get the nested fltXmTranslateFrom record
   coordRec = mgGetAttRec (translate, fltXmTranslateFrom, MG_NULL);
   // set the components on the nested record
   mgSetAttList (coordRec,
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fltCoord3dX, 0\.0, 
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fltCoord3dY, 0\.0, 
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fltCoord3dZ, 0\.0,
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;MG_NULL);
 &nbsp;
   // get the nested fltXmTranslateDelta record
   coordRec = mgGetAttRec (translate, fltXmTranslateDelta, MG_NULL);
   // set the components on the nested record
   mgSetAttList (coordRec,
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fltCoord3dX, 10\.0, 
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fltCoord3dY, 5\.0, 
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;fltCoord3dZ, 0\.0,
   &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;MG_NULL);
>

@see <f mgGetAttList>, <f mgSetAttList>, <f mgGetAttRec>,
<f mgGetCoord2i>, <f mgSetCoord2i>,
<f mgGetCoord3f>, <f mgSetCoord3f>,
<f mgGetCoord3d>, <f mgSetCoord3d>,
<f mgGetPlane>, <f mgSetPlane>,
<f mgGetMatrix>, <f mgSetMatrix>,
<f mgGetColorRGBA>, <f mgSetColorRGBA>,
<f mgGetNormColor>, <f mgSetNormColor>,
<f mgGetVector>, <f mgSetVector>,
<f mgGetVectord>, <f mgSetVectord>

@faqrelated
<faq_ref FAQ_00001007.What is the best way to get the coordinates (position) of a vertex node record?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001007 | Question

@question
What is the best way to get the coordinates (position) of a vertex node record?

@answer
When you look in the <OFDD> at the <flt fltVertex> record, you will see that
the XYZ coordinates of the vertex are contained in a nested record of type 
<flt fltCoord3d>.

@answer
<q
record fltVertex {
&nbsp;&nbsp;&nbsp;\.\.\.
&nbsp;&nbsp;&nbsp;record fltCoord3d  fltCoord3d   double precision float coordinate X,Y,Z
&nbsp;&nbsp;&nbsp;\.\.\.
}
>

@answer
The nested <flt fltCoord3d> record is defined as follows:
<q
record fltCoord3d {
&nbsp;&nbsp;&nbsp;double(8)          fltCoord3dX  X component of coordinate
&nbsp;&nbsp;&nbsp;double(8)          fltCoord3dY  Y component of coordinate
&nbsp;&nbsp;&nbsp;double(8)          fltCoord3dZ  Z component of coordinate
}
>

@answer
Like any other attribute, you can always use <f mgGetAttList> to get the values of the
vertex record.  But the OpenFlight API provides some "convenience" functions for getting
attributes that you are likely to use often.  These convenience functions are both
easier to use and more efficient.  

@answer
The first convenience function, <f mgGetCoord3d>, retrieves the x, y and z coordinates
of a nested <flt fltCoord3d> record from any record that contains one.  The second
convenience function, <f mgGetVtxCoord>, retrieves the x, y and z coordinates from
a <flt fltVertex> record specifically.  Of these three functions, <f mgGetVtxCoord>
is the most efficient and easiest function to use.  For that reason, it is the "best"
way to get the coordinates (position) of a vertex node record.

@exref The following examples (in C and Python) show different ways to
retrieve the coordinates (position) of a vertex node record <p vertex> using
<f mgGetAttList> and the two convenience functions <f mgGetCoord3d> and 
<f mgGetVtxCoord>. |

@ex |
   double x, y, z;
   int numAttr;
   mgbool status;

   // like any attribute, you can use mgGetAttList:
   numAttr = mgGetAttList (vertex,
         fltCoord3dX, &x,
         fltCoord3dY, &y,
         fltCoord3dZ, &z,
         MG_NULL);

   // or you can use the convenience function mgGetCoord3d
   // to retrieve a nested fltCoord3d record:
   status = mgGetCoord3d (vertex, fltCoord3d, &x, &y, &z);

   // or you can use a very specialized convenience function
   // mgGetVtxCoord to get the vertex coordinates:
   status = mgGetVtxCoord (vertex, &x, &y, &z);

@pyex |
   # like any attribute, you can use mgGetAttList:
   outs = mgGetAttList (vertex,
         fltCoord3dX,
         fltCoord3dY,
         fltCoord3dZ)
   numAttr = outs[0]
   if (numAttr == 3):
      x = outs[2];
      y = outs[4];
      z = outs[6];

   # or you can use the convenience function mgGetCoord3d
   # to retrieve a nested fltCoord3d record:
   status, x, y, z = mgGetCoord3d (vertex, fltCoord3d)

   # or you can use a very specialized convenience function
   # mgGetVtxCoord to get the vertex coordinates:
   status, x, y, z = mgGetVtxCoord (vertex)

@faqrelated
<faq_ref FAQ_00001003.How do I get the attributes of a record in the database?>
<faq_ref FAQ_00001006.How do I access a value in a record nested inside another record?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001008 | Question

@question
How do I get or set the comment attribute of a node record?

@answer
Like any other attribute, you can use <f mgGetAttList> and <f mgSetAttList>
to get and set the comment text of a node record.  The attribute code for
the comment text is <b fltComment>.  In addition, the OpenFlight API provides
"convenience" functions for getting and setting the comment text of a node.
Depending on your preference, you can use the set of functions you find easier.

@answer
The convenience function for getting the comment text of a node is <f mgGetComment>.
It allocates and returns the comment text (if any).  In C, remember to free
the string returned after you are done with it using <f mgFree>.

@answer
The convenience function for setting the comment text of a node is <f mgSetComment>.

@exref The following examples (in C and Python) show different ways to get
and set the comment text of polygon node record <p poly> using
<f mgGetAttList> and <f mgSetAttList> as well as the convenience functions 
<f mgGetComment> and <f mgSetComment>. |

@ex |
   char* comment1 = NULL;
   char* comment2 = NULL;
   int numAttr;

   // get the comment using both techniques...

   // like any attribute, you can use mgGetAttList:
   numAttr = mgGetAttList (poly, fltComment, &comment1, MG_NULL);

   // or you can use the convenience function mgGetComment
   comment2 = mgGetComment (poly);

   // at this point comment1 and comment2 will be the same
   // no matter which technique you use, remember to free the 
   // string when you are done with it
   mgFree (comment1);
   mgFree (comment2);

   // set the comment using both techniques

   // like any attribute, you can use mgSetAttList:
   numAttr = mgSetAttList (poly, fltComment, "Comment String", MG_NULL);

   // or you can use the convenience function mgSetComment
   mgSetComment (poly, "Comment String");

@pyex |
   # get the comment using both techniques...

   # like any attribute, you can use mgGetAttList:
   numAttr,code,comment1 = mgGetAttList (poly, fltComment)

   # or you can use the convenience function mgGetComment
   comment2 = mgGetComment (poly)

   # at this point comment1 and comment2 will be the same
   # Note that in Python, you don't have to free the strings

   # set the comment using both techniques

   # like any attribute, you can use mgSetAttList:
   numAttr,code = mgSetAttList (poly, fltComment, "Comment String")

   # or you can use the convenience function mgSetComment
   mgSetComment (poly, "Comment String")

@see <f mgGetAttList>, <f mgSetAttList>, <f mgGetComment>, <f mgSetComment>

@faqrelated
<faq_ref FAQ_00001001.What is the OpenFlight Data Dictionary?>
<faq_ref FAQ_00001003.How do I get the attributes of a record in the database?>
<faq_ref FAQ_00001004.How do I set the attributes of a record in the database?>
<faq_ref FAQ_00001005.How do I get a string attribute of a record in the database?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001009 | Question

@question
What is the difference between Color Index/Intensity and 
Creator Color Index attributes?

@answer
Several nodes in the OpenFlight scene have color index attributes.  These 
nodes include <flt fltPolygon>, <flt fltMesh>, <flt fltCat>, <flt fltText>, 
<flt fltVertex> and <flt fltLpAppearancePalette>.  The color attributes
on these nodes can be specified in two different ways.  They may be specified
by an Index/Intensity value pair or by a Creator Color Index value - both
are equivalent.  The difference between these specifications are 
explained here.

@answer
To understand what the color index values mean, it helps to know how the
color palette is constructed.  The database color palette contains 1024
color entries.  Each color entry is defined by red, green and blue (RGB)
values ranging from 0 to 255.  Each entry is further divided into a band 
of 128 shades, or intensities ranging from 0 to 127. 

@answer
As noted above, you can specify a color using either an Index/Intensity
value pair or a Creator Color Index.  These are just two different ways
of specifying the same thing.

@answer
When you specify a color by Index/Intensity pair, you specify the color
palette entry (0..1023) and the intensity (0.0 .. 1.0).  An intensity value
of 0.0 is  black and an intensity value of 1.0 is the full-intensity
of the RGB values of that color entry.

@answer
When you specify a color by Creator Color Index, you specify a different
index which encodes both the Index and Intensity values described above 
into a single value.  This is how Creator displays the color index values 
on the Attribute Pages.  The 128 colors specified by Index <mono N>, 
Intensity <mono I> (ranging from 0.0 - 1.0) are encoded into the 
Creator Color Indices <mono X> .. <mono Y>, where <mono X> is:

<q
(N * 128) + round(I * 127\.0) 
>

@answer
and <mono Y> is:

<q
X + 128
>

@answer
Color Index <mono 0>, Intensity <mono 1\.0>, therefore would be Creator Color Index <mono 127>.
Similarly Color Index <mono 5>, Intensity <mono 0\.5> would be Creator Color Index <mono 704>.  

@answer
The following excerpt from the <OFDD> shows the primary and alternate color index
attributes of the <flt fltPolyon> record. 

<q
record fltPolygon {
&nbsp;&nbsp;&nbsp;\.\.\.
&nbsp;&nbsp;&nbsp;unsigned int(4)  fltPolyCreatorPrimeColor  Creator Primary Color Index
&nbsp;&nbsp;&nbsp;unsigned int(4)  fltPolyPrimeColor         Primary Color Index
&nbsp;&nbsp;&nbsp;float(4)         fltPolyPrimeIntensity     Primary Color Intensity
&nbsp;&nbsp;&nbsp;\.\.\.
&nbsp;&nbsp;&nbsp;unsigned int(4)  fltPolyCreatorAltColor    Creator Alternate Color Index
&nbsp;&nbsp;&nbsp;unsigned int(4)  fltPolyAltColor           Alternate Color Index
&nbsp;&nbsp;&nbsp;float(4)         fltPolyAltIntensity       Alternate Color Intensity
&nbsp;&nbsp;&nbsp;\.\.\.
}
>

@answer
Notice that the <OFDD> provides codes for both color index values.  Specifically, 
<fltf fltPolygon.fltPolyPrimeColor> and <fltf fltPolygon.fltPolyPrimeIntensity> represent the primary color
index as an Index/Intensity pair and <fltf fltPolygon.fltPolyCreatorPrimeColor> represents
the primary color as a Creator Color Index.  The same applies for alternate color.
The attributes <fltf fltPolygon.fltPolyAltColor> and <fltf fltPolygon.fltPolyAltIntensity> represent
the alternate color as an Index/Intensity pair and <fltf fltPolygon.fltPolyCreatorAltColor>
as a Creator Color Index.

@exref The following examples (in C and Python) show both ways to specify
the primary color value for <flt fltPolygon> nodes. |

@ex |
   // set both node1 and node2 to the same color
   // use different color index attributes to do it
   
   // set using Color Index/Intensity pair
   mgSetAttList (node1, 
         fltPolyPrimeColor, 0, 
         fltPolyPrimeIntensity, 1.0,
         MG_NULL);

   // set using Creator Color Index
   mgSetAttList (node2, 
         fltPolyCreatorPrimeColor, 127,
         MG_NULL);

@pyex |
   # set both node1 and node2 to the same color
   # use different color index attributes to do it

   # set using Color Index/Intensity pair
   mgSetAttList (node1, 
         fltPolyPrimeColor, 0, 
         fltPolyPrimeIntensity, 1.0)

   # set using Creator Color Index
   mgSetAttList (node2, 
         fltPolyCreatorPrimeColor, 127) 

@see <f mgGetAttList>, <f mgSetAttList>

@faqrelated
<faq_ref FAQ_00001010.When I set a color intensity attribute on a node, the value I see on the node is not the exact value I set - why is there a difference?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001010 | Question

@question
When I set a color intensity attribute on a node, the value I see
on the node is not the exact value I set.  Why is there a difference?

@answer
Several nodes in the OpenFlight scene have color attributes.  These 
nodes include <flt fltPolygon>, <flt fltMesh>, <flt fltCat>, <flt fltText>, 
<flt fltVertex> and <flt fltLpAppearancePalette>.  The color attributes
are represented on the nodes as Index/Intensity value pairs.

@answer
To help explain this problem, it will be useful to understand how the
color palette is constructed.  The database color palette contains 1024
color entries.  Each color entry is defined by red, green and blue (RGB)
values ranging from 0 to 255.  Each entry is further divided into a band 
of 128 shades, or intensities ranging from 0 to 127.  This is how the
OpenFlight color palette is stored on disk.

@answer
The problem stems from that fact that the intensity value of a color
(stored on disk as an integer value, range 0 to 127) is expressed in the 
OpenFlight API using a floating point number whose range is 0.0 .. 1.0.  
Since these 128 integer intensity values are quantized into floating point
numbers, only 128 discrete floating point values can be represented.
The 128 floating  point numbers that are represented for Intensity <mono I> 
(ranging from 0..127) can be expressed by this equation:

<q
I / 127\.0
>

@answer
As you can see in the table below, only a small number of all the 
floating point numbers between 0.0 and 1.0 can be represented by
128 integer intensities in the range 0..127:

<tablestart SIMPLE>
<tablerowstart HEADER>
<tableelementstart BORDER> Integer Intensity <tableelementend>
<tableelementstart BORDER> Floating Point Intensity <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono 0> <tableelementend>
<tableelementstart BORDER> <mono 0\.000000000000> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono 1> <tableelementend>
<tableelementstart BORDER> <mono 0\.007874015718> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono 2> <tableelementend>
<tableelementstart BORDER> <mono 0\.015748031437> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono 3> <tableelementend>
<tableelementstart BORDER> <mono 0\.023622047156> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono \.\.\.> <tableelementend>
<tableelementstart BORDER> <mono \.\.\.> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono 125> <tableelementend>
<tableelementstart BORDER> <mono 0\.984251976013> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono 126> <tableelementend>
<tableelementstart BORDER> <mono 0\.992125988007> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono 127> <tableelementend>
<tableelementstart BORDER> <mono 1\.000000000000> <tableelementend>
<tablerowend>

<tableend>

@answer 
This quantization explains why the floating point value you set for
a color intensity attribute on a node may not be the exact value you
get.  For example, if you set the intensity value to <mono 0\.007>, 
the actual value you will get is <mono 0\.007874015718>.

@see <f mgGetAttList>, <f mgSetAttList>

@faqrelated
<faq_ref FAQ_00001009.What is the difference between Color Index/Intensity and Creator Color Index attributes?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001011 | Question

@question
How do I set up texture on a polygon?

@answer
To set up a texture on a polygon, you will do the following:

<unorderedliststart .>
<listelementstart NOINDENT> Load a texture in the texture palette of the database <listelementend>
<listelementstart NOINDENT> Assign the texture index on the polygon <listelementend>
<listelementstart NOINDENT> Assign texture coordinates (UVs) on each vertex of the polygon <listelementend>
<unorderedlistend>

@answer
To assign a texture to a polygon, the texture must be in the texture palette of the 
database. When a texture is in the texture palette, it will have an <i index> 
associated to it.  This index is used by many OpenFlight API functions to reference 
the texture in the palette and is needed, specifically in this situation, to assign 
to the polygon.  If the texture you want to 
assign is already in the texture palette of the database, just note the index 
and skip this step.  Otherwise, you will need to load the texture in the texture
palette before you can assign it to a polygon. 

@answer
There are a couple of similar functions to load a texture in the texture palette: 
<f mgInsertTexture> and <f mgReadTexture>.  
If you want to assign a specific index to the texture in the palette, use <f mgReadTexture>.  
If you do this, make sure the index is not already in use.  If you use 
<f mgInsertTexture>, a "free" index will be assigned to the texture you
load in the texture palette.  The new index assigned is returned by <f mgInsertTexture>.

@answer
When you have the index of the texture in the texture palette, you are ready to assign it
to the polygon.  This is very simple using <f mgSetAttList> and the attribute code
<fltf fltPolygon.fltPolyTexture>.  The attribute value you provide is simply the 
texture palette index of the texture you want to assign to the polygon. Note that 
the attribute code <fltf fltPolygon.fltPolyTexture> is used to assign the <i base>
texture layer.  Use <fltf fltPolygon.fltLayerTexture1>, <fltf fltPolygon.fltLayerTexture2>,
... <fltf fltPolygon.fltLayerTexture7> to assign other texture layers on the polygon.
If your runtime supports detail texture, you can also assign <fltf fltPolygon.fltPolyDetailTexture>
to the polygon.

@answer
After you have assigned the texture index to the polygon, you must set texture coordinates
(UVs) on the vertices of the polygon.  Like any other attribute, you use <f mgSetAttList> 
to assign UVs to vertex nodes.  You must assign UVs to each vertex of the polygon. Use
the attribute codes <fltf fltVertex.fltVU> and <fltf fltVertex.fltVV> to assign the base
texture UVs on a vertex.  Use attribute codes <fltf fltVertex.fltLayerU1>, 
<fltf fltVertex.fltLayerV1>, <fltf fltVertex.fltLayerU2>, 
<fltf fltVertex.fltLayerV2>, ... <fltf fltVertex.fltLayerU7>, 
<fltf fltVertex.fltLayerV7> to assign UVs for other texture layers on a vertex.

@exref The following examples (in C and Python) show how to load a texture in the
palette of a database <p db> and set it up on a quadrilateral polygon <p poly>. |

@ex |

   // load a texture in the palette, get its index
   index = mgInsertTexture (db, "C:/textures/brick.rgb");

   // assign the texture to the polygon
   mgSetAttList (poly, fltPolyTexture, index, MG_NULL);

   // get the 4 vertices of the quad polygon
   vtx1 = mgGetChild (poly);
   vtx2 = mgGetNext (vtx1);
   vtx3 = mgGetNext (vtx2);
   vtx4 = mgGetNext (vtx3);

   // assign simple UV mapping to each vertex of the quad
   mgSetAttList (vtx1, fltVU, 0.0, fltVV, 0.0, MG_NULL);
   mgSetAttList (vtx2, fltVU, 1.0, fltVV, 0.0, MG_NULL);
   mgSetAttList (vtx3, fltVU, 1.0, fltVV, 1.0, MG_NULL);
   mgSetAttList (vtx4, fltVU, 0.0, fltVV, 1.0, MG_NULL);

@pyex |

   # load a texture in the palette, get its index
   index = mgInsertTexture (db, "C:/textures/brick.rgb")

   # assign the texture to the polygon
   mgSetAttList (poly, fltPolyTexture, index)

   # get the 4 vertices of the quad polygon
   vtx1 = mgGetChild (poly)
   vtx2 = mgGetNext (vtx1)
   vtx3 = mgGetNext (vtx2)
   vtx4 = mgGetNext (vtx3)

   #  assign simple UV mapping to each vertex of the quad
   mgSetAttList (vtx1, fltVU, 0.0, fltVV, 0.0)
   mgSetAttList (vtx2, fltVU, 1.0, fltVV, 0.0)
   mgSetAttList (vtx3, fltVU, 1.0, fltVV, 1.0)
   mgSetAttList (vtx4, fltVU, 0.0, fltVV, 1.0)

@see <f mgSetAttList>, <f mgInsertTexture>, <f mgReadTexture>

@faqrelated
<faq_ref FAQ_00001004.How do I set the attributes of a record in the database?>
<faq_ref FAQ_00001014.How do I set a color name on a polygon or mesh?>
<faq_ref FAQ_00001015.How do I set the normal of a polygon?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001012 | Question

@question
How do I determine the OpenFlight revision level of an OpenFlight database?

@answer
After the database is opened (using <f mgOpenDb> or <f mgNewDb>), you can access
the OpenFlight revision level as an attribute of the OpenFlight database
<flt fltHeader> node.  The attribute code for this is <fltf fltHeader.fltHdrFormatRev>.  
You can get this value (like you do any attribute value for any node type) using 
<f mgGetAttList>.  Note that you cannot set this value using <f mgSetAttList>,
it is automatically set when you save or export the database file.

@answer
If you want to query the OpenFlight revision level of a database file on disk 
(without opening it) you can use the function <f mgGetDbVersion>.

@exref The following examples (in C and Python) show how to get the OpenFlight revision
level attribute from an open database <p db>. |

@ex |

   int formatRev;
   int numAttr = mgGetAttList (db, fltHdrFormatRev, &formatRev, MG_NULL);

   // formatRev will be an integer number encoded like 1650, 1640, 1630, 1620, etc
   // specifying the OpenFlight format revision of this OpenFlight file. 

@pyex |

   numAttr, code, formatRev = mgGetAttList (db, fltHdrFormatRev)

   # formatRev will be an integer number encoded like 1650, 1640, 1630, 1620, etc
   # specifying the OpenFlight format revision of this OpenFlight file. 

@see <f mgGetAttList>, <f mgGetDbVersion>

@faqrelated
<faq_ref FAQ_00001013.Can I query the OpenFlight revision level of an OpenFlight file on disk without opening it?>
<faq_ref FAQ_00001003.How do I get the attributes of a record in the database?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001013 | Question

@question
Can I query the OpenFlight revision level of an OpenFlight file on disk
without opening it? 

@answer
You can use the function <f mgGetDbVersion> to query the OpenFlight revision level
of a file on disk.

@exref The following examples (in C and Python) show how to get the OpenFlight revision
level for an OpenFlight file on disk. |

@ex |

   int formatRev;
   formatRev = mgGetDbVersion ("c:/MyDatabases/myfile.flt");

   // if the file is an OpenFlight file, formatRev will be an integer number 
   // encoded like 1650, 1640, 1630, 1620, etc specifying the OpenFlight format 
   // revision of this OpenFlight file. 
   //
   // if the file is not an OpenFlight file, formatRev will be 0.

@pyex |

   formatRev = mgGetDbVersion ("c:/MyDatabases/myfile.flt")

   # if the file is an OpenFlight file, formatRev will be an integer number 
   # encoded like 1650, 1640, 1630, 1620, etc specifying the OpenFlight format 
   # revision of this OpenFlight file. 
   # 
   # if the file is not an OpenFlight file, formatRev will be 0.

@see <f mgGetDbVersion>

@faqrelated
<faq_ref FAQ_00001012.How do I determine the OpenFlight revision level of an OpenFlight database?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001014 | Question

@question
How do I set a color name on a polygon or mesh? 

@answer
You can use the functions <f mgSetPolyColorName> and <f mgSetPolyAltColorName> to
set the primary and alternate color names on polygons and meshes.

@answer
Similarly, use functions <f mgGetPolyColorName> and <f mgGetPolyAltColorName> to
get the primary and alternate color names assigned to polygons and meshes.

@see <f mgSetPolyColorName>, <f mgSetPolyAltColorName>, <f mgGetPolyColorName> 
and <f mgGetPolyAltColorName>.

@faqrelated
<faq_ref FAQ_00001011.How do I set up texture on a polygon?>
<faq_ref FAQ_00001015.How do I set the normal of a polygon?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001015 | Question

@question
How do I set the normal of a polygon?

@answer
There is no attribute stored on the <f fltPolygon> node for its normal so you
cannot <i set> this explicitly. The polygon normal is calculated based on the
plane containing the vertices of the polygon and therefore may change as the 
positions of one or more of its vertices are changed. Note that if not all of
the vertices of the polygon are coplanar, the calculated normal may not be 
what you expect. 

@answer
The polygon normal points in the same direction the "front" of the polygon faces. See 
<faq_ref_inline FAQ_00001016.Which side of a polygon is the front and which is the back?> 
for more information.

@answer
You can query the normal of a polygon using <f mgGetPolyNormal> 
but there is no corresponding function to set the polygon normal.

@see <f mgGetPolyNormal>, <f mgGetVtxNormal>, <f mgSetVtxNormal>

@faqrelated
<faq_ref FAQ_00001016.Which side of a polygon is the front and which is the back?>
<faq_ref FAQ_00001004.How do I set the attributes of a record in the database?>
<faq_ref FAQ_00001011.How do I set up texture on a polygon?>
<faq_ref FAQ_00001014.How do I set a color name on a polygon or mesh?> 
<faq_ref FAQ_00001017.How do I access an edge of a polygon?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001016 | Question

@question
Which side of a polygon is the front and which is the back?

@answer
The order of the vertices in the polygon define which side of the polygon is front
and which is back. When looking at the "front" of a polygon, the vertices will be 
ordered in a counter-clockwise direction. The polygon normal will point towards you 
if you are looking "down" on the "front" of the polygon. If you are looking at the
"back" of the polygon, the normal will point away from you.

@answer
In OpenFlight, solid polygons can be defined in such a way that "both" sides
are rendered. This is often called "Both Sides Visible". To make a polygon draw
both sides, set the polygon attribute <f fltPolyDrawType> to 1 (Solid, Both
Sides Visible) using <f mgSetAttList>. Note that this does not affect the order
of the vertices on the polygon or the polygon normal. A polygon defined in this 
way will still have a "front" side and a "back" side but both will be drawn.

@see <f mgGetPolyNormal>, <f mgGetVtxNormal>, <f mgSetVtxNormal>, <f mgSetAttList>

@faqrelated
<faq_ref FAQ_00001015.How do I set the normal of a polygon?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001017 | Question

@question
How do I access an edge of a polygon? 

@answer
In the OpenFlight scene graph, there is no explicit node type for an edge of a polygon. 
Similar to how a polygon normal is <i calculated> based on the current positions of all 
its vertices, a polygon edge is <i calculated> based on the positions of two <i adjacent>
vertices of the polygon. 

@answer
A closed polygon with N vertices has exactly N edges. The nth edge (n \< N) of a closed polygon
with N vertices is defined by vertex n and vertex n+1. The Nth edge is defined by the last vertex
(vertex N) wrapping back to the first vertex (vertex 1). An unclosed polygon with N vertices has 
exactly N-1 edges. The nth edge (n \<= N-1) of an unclosed polygon is defined by vertex n and 
vertex n+1. For unclosed polygons the last vertex does not attach to the first vertex so 
does not form an edge.

@answer
When you are working with vertices and their attributes in the scene graph, you do not 
generally need to worry about (nor do you have explicit access to) edges, only the vertices
that comprise the edge. So, to reposition an edge you simply reposition the vertices that 
comprise that edge. Note, however that if you reposition any <i one> vertex of a closed polygon,
you will implicitly change the position of <i two> edges. This is because in a closed polygon, 
each vertex is part of two edges. Each vertex of a closed polygon is the <i first> vertex of 
one edge and the <i last> vertex of the <i previous> edge of that polygon. For unclosed polygons, 
the first and last vertices of the polygon are each part of only one edge, the first 
and last edge, respectively. 

@answer
In Creator, however, the user can select vertices or edges. This is one instance in which
you do treat vertices different than edges. See 
<faq_ref_inline FAQ_00001018.How do I select an edge of a polygon in Creator?> for
more information on this.  

@faqrelated
<faq_ref FAQ_00001015.How do I set the normal of a polygon?>
<faq_ref FAQ_00001018.How do I select an edge of a polygon in Creator?>
<faq_ref FAQ_00001022.How do I tell if an edge of a polygon is selected in Creator?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001018 | Question

@question
How do I select an edge of a polygon in Creator?

@answer
As discussed in <faq_ref_inline FAQ_00001017.How do I access an edge of a polygon?>
there is no explicit node type for polygon edges. In Creator, however, the user can select
vertices or edges. As there is no node type in the OpenFlight scene graph for an edge
(only for vertices), Creator makes this work by attaching a special attribute to a vertex 
node when it is selected to indicate whether the vertex is selected <i as a vertex> or is
selected <i as an edge>.

@answer 
When the user selects an edge in Creator, Creator (behind the scenes) selects the first vertex
of the edge and automatically sets this special vertex attribute to indicate that the vertex 
is selected as an edge. To select an edge from your plug-in or script, use <f mgSelectOneEdge>
passing the first vertex of the edge you want to select. When you do this, the vertex will be 
selected but marked as "selected as an edge". If you want to select the vertex instead
(not the edge it defines) use <f mgSelectOne>. In both situations, you pass the same vertex.
Using <f mgSelectOneEdge> selects the vertex as an edge, <f mgSelectOne> selects the vertex 
as a vertex.

@exref The following examples (in C and Python) show how to select a vertex as
a vertex and how to select the same vertex as an edge. |

@ex |

   // this function selects the first --vertex-- of a polygon
   static void SelectFirstVertexOfFace (mgrec* face)
   {
      // get the first child of the face, this is 
      // the first vertex of that face
      mgrec* firstVertex = mgGetChild (face);

      // select the first vertex as a vertex
      mgSelectOne (firstVertex);
   }

   // this function selects the first --edge-- of a polygon
   static void SelectFirstEdgeOfFace (mgrec* face)
   {
      // get the first child of the face, this is the
      // first vertex of that face and defines (with 
      // the second vertex) the first edge of the face
      mgrec* firstVertex = mgGetChild (face);
      
      // select the first vertex as an edge
      mgSelectOneEdge (firstVertex);
   }

@pyex |

   # this function selects the first --vertex-- of a polygon
   def SelectFirstVertexOfFace (face):
      # get the first child of the face, this is 
      # the first vertex of that face
      firstVertex = mgGetChild (face)

      # select the first vertex as a vertex
      mgSelectOne (firstVertex)

   # this function selects the first --edge-- of a polygon
   def SelectFirstEdgeOfFace (face):
      # get the first child of the face, this is the
      # first vertex of that face and defines (with 
      # the second vertex) the first edge of the face
      firstVertex = mgGetChild (face)

      # select the first vertex as an edge
      mgSelectOneEdge (firstVertex)

@see <f mgSelectOne>, <f mgSelectOneEdge>,
<f mgIsSelected>, <f mgIsSelectedEdge>

@faqrelated
<faq_ref FAQ_00001017.How do I access an edge of a polygon?>
<faq_ref FAQ_00001022.How do I tell if an edge of a polygon is selected in Creator?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001020 | Question

@question
How do I tell if a specific node is selected in Creator?

@answer
You use the function <f mgIsSelected> to determine if a specific node is selected. For
<f fltVertex> nodes, you can further qualify this using <f mgIsSelectedEdge> to determine
if the vertex is selected as a vertex or is selected as an edge.

@answer
Note that node selection in Creator is <i implicitly> hierarchical. That means that when
a user selects, say, an object node in Creator, the children (polygons) below that object
are <i implicitly> (not <i explicitly>) selected as well. To exemplify this, consider
the situation in which <i p1> and <i p2> (both polygons) are children of object <i o1>.
In this example, if the user were to select <i o1> in object mode in Creator, 
<f mgIsSelected> would return <e mgbool.MG_TRUE> for <i o1> but <e mgbool.MG_FALSE>
for <i p1> and <i p2> even though <i p1> and <i p2> are <i implicitly> selected by 
begin children of <i o1> which is <i explicitly> selected.

@see <f mgIsSelected>, <f mgIsSelectedEdge>,
<f mgSelectOne>, <f mgSelectOneEdge>

@faqrelated
<faq_ref FAQ_00001021.How do I get the list of nodes that are currently selected in Creator?>
<faq_ref FAQ_00001022.How do I tell if an edge of a polygon is selected in Creator?>
<faq_ref FAQ_00001023.Why are the nodes in the select list in reverse order from how they were selected by the user in Creator?>
<faq_ref FAQ_00001024.How do I select nodes from my plug-in or script in Creator?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001021 | Question

@question
How do I get the list of nodes that are currently selected in Creator? 

@answer
You use the function <f mgGetSelectList> to get a record list containing all the currently 
selected nodes in a specified database. Once you have this list, you can use <f mgGetRecListCount>
to query how many nodes are in the list, <f mgGetNextRecInList> or <f mgGetNthRecInList> to get nodes
from the list and <f mgIsRecInList> to determine if a specific node is in the list. 

@answer
When you are done accessing the record list returned by <f mgGetSelectList>, you should dispose of 
it using <f mgFreeRecList>.

@answer
Note that <f mgGetSelectList> only works inside of Creator since there is no notion
of "selected nodes" in your stand-alone program or script. 

@exref The following examples (in C and Python) show you how you might use the select list in Creator. |

@ex |
   mgrec* rec;
   mgmatrix selectMatrix;
   mgreclist selectList = mgGetSelectList (db);

   rec = mgGetNextRecInList (selectList, &selectMatrix);
   while (rec)
   {
      // do something with rec
      rec = mgGetNextRecInList (selectList, &selectMatrix);
   }
   // all done with record list, deallocate it
   mgFreeRecList (selectList);

@pyex |
   selectList = mgGetSelectList (db)
   num = mgGetRecListCount (selectList)

   for i in range (0, num):
      rec,matrix = mgGetNextRecInList (selectList)

   # you don't need to deallocate the record list in Python

@faqrelated
<faq_ref FAQ_00001022.How do I tell if an edge of a polygon is selected in Creator?>
<faq_ref FAQ_00001023.Why are the nodes in the select list in reverse order from how they were selected by the user in Creator?>
<faq_ref FAQ_00001024.How do I select nodes from my plug-in or script in Creator?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001022 | Question

@question
How do I tell if an edge is selected in Creator?

@answer
As discussed in <faq_ref_inline FAQ_00001017.How do I access an edge of a polygon?> and
<faq_ref_inline FAQ_00001018.How do I select an edge of a polygon in Creator?> the OpenFlight
scene graph does not explicitly define polygon edges. Rather, an edge is defined (virtually) by
two adjacent vertices of a polygon. In Creator, however, the user can select vertices or edges.
In both cases a single vertex is selected. When an edge is selected, the vertex selected has
a special attribute set to specify that it is selected <i as an edge>. Without that attribute
set, the vertex is simply selected <i as a vertex>.

@answer
To determine whether any node is selected use <f mgIsSelected>. When the node is a <f fltVertex>
this may not tell you everything you need to know. When <f mgIsSelected> returns <e mgbool.MG_TRUE>
for a <f fltVertex> node, you still don't know if the vertex is selected as a vertex or is selected as 
an edge. If your plug-in or script needs to know this, you can call <f mgIsSelectedEdge>. <f mgIsSelectedEdge>
will return <e mgbool.MG_TRUE> if the vertex is selected as an edge, <e mgbool.MG_FALSE> if the vertex
is selected as a vertex.

@answer
To reiterate, when a <f fltVertex> is selected as a vertex, <f mgIsSelected> will return <e mgbool.MG_TRUE> and 
<f mgIsSelectedEdge> will return <e mgbool.MG_FALSE>. When a <f fltVertex> is selected as an edge,
<f mgIsSelected> and <f mgIsSelectedEdge> will both return <e mgbool.MG_TRUE>. 

@exref The following examples (in C and Python) define convenience functions you might use to determine
whether a vertex is selected as a vertex or selected as an edge. |

@ex |

   // this function returns MG_TRUE if a vertex is selected as a vertex
   static mgbool IsVertexSelectedAsVertex (mgrec* vtx)
   {
      mgbool isSelected = mgIsSelected(vtx);
      mgbool isSelectedAsEdge = mgIsSelectedEdge(vtx);
      if ((isSelected == MG_TRUE) && (isSelectedAsEdge == MG_FALSE))
         return MG_TRUE;
      else
         return MG_FALSE;
   }

   // this function returns MG_TRUE if a vertex is selected as an edge
   static mgbool IsVertexSelectedAsEdge (mgrec* vtx)
   {
      mgbool isSelected = mgIsSelected(vtx);
      mgbool isSelectedAsEdge = mgIsSelectedEdge(vtx);
      if ((isSelected == MG_TRUE) && (isSelectedAsEdge == MG_TRUE))
         return MG_TRUE;
      else
         return MG_FALSE;
   }

@pyex |

   # this function returns True if a vertex is selected as a vertex
   def IsVertexSelectedAsVertex (vtx):
      isSelected = mgIsSelected(vtx)
      isSelectedAsEdge = mgIsSelectedEdge(vtx)
      return (isSelected == MG_TRUE) and (isSelectedAsEdge == MG_FALSE)

   # this function returns True if a vertex is selected as an edge
   def IsVertexSelectedAsEdge (vtx):
      isSelected = mgIsSelected(vtx)
      isSelectedAsEdge = mgIsSelectedEdge(vtx)
      return (isSelected == MG_TRUE) and (isSelectedAsEdge == MG_TRUE)

@see <f mgIsSelected>, <f mgIsSelectedEdge>,
<f mgSelectOne>, <f mgSelectOneEdge>

@faqrelated
<faq_ref FAQ_00001017.How do I access an edge of a polygon?>
<faq_ref FAQ_00001018.How do I select an edge of a polygon in Creator?>
<faq_ref FAQ_00001020.How do I tell if a specific node is selected in Creator?>
<faq_ref FAQ_00001021.How do I get the list of nodes that are currently selected in Creator?>
<faq_ref FAQ_00001023.Why are the nodes in the select list in reverse order from how they were selected by the user in Creator?>
<faq_ref FAQ_00001024.How do I select nodes from my plug-in or script in Creator?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001023 | Question

@question
Why are the nodes in the select list in reverse order from how they were selected by the user in Creator?

@answer
Admittedly this is a bit quirky and perhaps the result of a regrettable decision when the OpenFlight API
was first released. To explain this, the select list is stored by Creator as a LIFO (Last In First Out) 
list. As the Creator user adds items to the select list, they are added to the "front" of the list. 
Historically (before the OpenFlight API was released) all tools written in Creator would take this 
into account (if order mattered to the tool) and adjust accordingly. 

@answer
When the OpenFlight API was first released and provided access to the select list to callers, the
selected nodes were "packaged" in the <t mgreclist> in the same order they were stored by Creator. This was
perhaps a regrettable decision and one area in which the initial implementation of the OpenFlight API might 
have been improved. In hindsight, it might have made more sense to package the nodes in the select list
in the order selected by the user, but alas, that was not done. Now that the OpenFlight API has been released
(and widely adopted by developers) using this convention, it would be impossible to change this
without breaking existing user's code that might depend on this reverse ordering. For that
reason, the OpenFlight API will continue to package the <t mgreclist> in the "reverse" order
from how the nodes were originally selected by the user in Creator.

@answer
For many tools you write, you may find that the order of the nodes in the select list is not important. 
For those cases in which the order is important, the OpenFlight API provides a simple mechanism whereby
your plug-in or script can access the select list nodes in the order they were selected by the user 
in Creator.

@exref The following examples (in C and Python) show you a simple technique to access nodes contained
in a <t mgreclist> in the order they were selected by the user. |

@ex |
   mgrec* rec;
   mgmatrix selectMatrix;
   mgreclist selectList = mgGetSelectList (db);
   int num = mgGetRecListCount (selectList);
   int i;

   // simply get the last item first and the first item last!
   for (i = num; i > 0; i--) {
      rec = mgGetNthRecInList (selectList, &selectMatrix, i);
   }

   // all done with record list, deallocate it
   mgFreeRecList (selectList);

@pyex |
   selectList = mgGetSelectList (db)
   num = mgGetRecListCount (selectList)

   # simply loop over the items in reverse order!
   for i in range (num, 0, -1):
      rec,matrix = mgGetNthRecInList (selectList, i)

   # you don't need to deallocate the record list in Python

@see <f mgGetSelectList>, <f mgGetNthRecInList>

@faqrelated
<faq_ref FAQ_00001020.How do I tell if a specific node is selected in Creator?>
<faq_ref FAQ_00001021.How do I get the list of nodes that are currently selected in Creator?>
<faq_ref FAQ_00001022.How do I tell if an edge of a polygon is selected in Creator?>
<faq_ref FAQ_00001024.How do I select nodes from my plug-in or script in Creator?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001024 | Question

@question
How do I select nodes from my plug-in or script in Creator? 

@answer
There are several functions in the OpenFlight API you can use to change what is selected in Creator.
To deselect all nodes, use <f mgDeselectAll>. To select a node, use <f mgSelectOne>. 
To deselect a node, use <f mgDeselectOne>. Finally, to select all the nodes contained 
in a record list, use <f mgSelectList>.

@answer
Note that when you use <f mgSelectOne> to select a node or <f mgSelectList> to select
several nodes, any nodes that are currently selected remain selected. If you want to 
make a node the only node selected or a set of nodes in a record list the only nodes
selected, call <f mgDeselectAll> <i before> calling <f mgSelectOne> or <f mgSelectList>, 
respectively.

@answer
Selecting edges is a bit tricky. Since <f fltVertex> is used to represent both vertices
and edges in the OpenFlight scene graph 
(see <faq_ref_inline FAQ_00001017.How do I access an edge of a polygon?> to learn
how vertices are distinguished from edges), 
there is a special function, <f mgSelectOneEdge>, to use for selecting edges. 
See <faq_ref_inline FAQ_00001018.How do I select an edge of a polygon in Creator?> for
more information on this.  

@answer
Note that these selection functions only work inside of Creator since there is no notion
of "selected nodes" in your stand-alone program or script. 

@see <f mgDeselectAll>, <f mgDeselectOne>, <f mgSelectOne>, <f mgSelectOneEdge>,
<f mgSelectList>

@faqrelated
<faq_ref FAQ_00001017.How do I access an edge of a polygon?>
<faq_ref FAQ_00001018.How do I select an edge of a polygon in Creator?>
<faq_ref FAQ_00001020.How do I tell if a specific node is selected in Creator?>
<faq_ref FAQ_00001021.How do I get the list of nodes that are currently selected in Creator?>
<faq_ref FAQ_00001022.How do I tell if an edge of a polygon is selected in Creator?>
<faq_ref FAQ_00001023.Why are the nodes in the select list in reverse order from how they were selected by the user in Creator?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001030 | Question

@question
How do I get the current modeling mode set in Creator?

@answer
You use the function <f mgGetModelingMode> to get the current modeling mode selected
by the user in Creator. The modeling mode is returned as the <t mgcode> corresponding
to that node type (<f fltGroup>, <f fltObject>, etc).

@answer
The edge modeling mode is a bit tricky. Since <f fltVertex> is used 
to represent both vertices and edges in the OpenFlight scene graph 
(see <faq_ref_inline FAQ_00001017.How do I access an edge of a polygon?>
to learn how vertices are distinguished from edges), there is a special function, 
<f mgIsModelingModeEdge>, you can use to know when the modeling mode is edge. 
See <faq_ref_inline FAQ_00001031.How do I tell the difference between vertex and 
edge modeling mode in Creator?> for more information on this.  

@exref The following examples (in C and Python) show how to use this
function for different modeling modes: |

@ex |
   mgcode mode;

   mode = mgGetModelingMode (db);
   if (mode == fltGroup) {
      printf ("modeling mode is group&#92;n");
   }
   else if (mode == fltObject) {
      printf ("modeling mode is object&#92;n");
   }
   else {
      // as noted above, fltVertex will be reported
      // here if modeling mode is vertex or edge
      // use mgIsModelingModeEdge to know the difference
      printf ("modeling mode is %s&#92;n", ddGeName(mode));
   }

@pyex |
   mode = mgGetModelingMode (db)
   if (mode == fltGroup):
      print "modeling mode is group"
   elif (mode == fltObject:
      print "modeling mode is object"
   else:
      # as noted above, fltVertex will be reported
      # here if modeling mode is vertex or edge
      # use mgIsModelingModeEdge to know the difference
      print "modeling mode is",ddGetName(mode)

@see <f mgGetModelingMode>, <f mgIsModelingModeEdge>

@faqrelated
<faq_ref FAQ_00001017.How do I access an edge of a polygon?>
<faq_ref FAQ_00001031.How do I tell the difference between vertex and edge modeling mode in Creator?>
<faq_ref FAQ_00001032.How do I change the modeling mode in Creator from my plug-in or script?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001031 | Question

@question
How do I tell the difference between vertex and edge modeling mode in Creator?

@answer
As discussed in <faq_ref_inline FAQ_00001017.How do I access an edge of a polygon?> the OpenFlight
scene graph does not explicitly differentiate between vertices and edges. Edges are defined (virtually)
by two adjacent vertices of a polygon. In Creator, however, the user can set the modeling mode
to vertex or edge. So how does that work?

@answer
The current modeling mode is returned by <f mgGetModelingMode>. This function returns <f fltVertex>
if the modeling mode is either vertex or edge. To tell the difference, use the function 
<f mgIsModelingModeEdge>. If the modeling mode is vertex, <f mgGetModelingMode> will return <f fltVertex>
and <f mgIsModelingModeEdge> will return <e mgbool.MG_FALSE>. If the modeling mode is edge, 
<f mgGetModelingMode> will return <f fltVertex> and <f mgIsModelingModeEdge> will return
<e mgbool.MG_TRUE>.

@see <f mgGetModelingMode>, <f mgIsModelingModeEdge>

@faqrelated
<faq_ref FAQ_00001017.How do I access an edge of a polygon?>
<faq_ref FAQ_00001018.How do I select an edge of a polygon in Creator?>
<faq_ref FAQ_00001030.How do I get the current modeling mode set in Creator?>
<faq_ref FAQ_00001032.How do I change the modeling mode in Creator from my plug-in or script?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001032 | Question

@question
How do I change the modeling mode in Creator from my plug-in or script?

@answer
You use the function <f mgSetModelingMode> to change the current modeling mode
in Creator. You specify the modeling mode as the <t mgcode> corresponding
to the node type (<f fltGroup>, <f fltObject>, etc) you want.

@answer
The edge modeling mode is a bit tricky. Since <f fltVertex> is used 
to represent both vertices and edges in the OpenFlight scene graph
you must use a special function, <f mgSetModelingModeEdge> to set the
modeling mode to edge. To reiterate, use <f mgSetModelingMode> to set
the modeling mode to vertex (or for any mode other than edge) and use
<f mgSetModelingModeEdge> to set the modeling mode to edge.

@see <f mgSetModelingMode>, <f mgSetModelingModeEdge>

@faqrelated
<faq_ref FAQ_00001030.How do I get the current modeling mode set in Creator?>
<faq_ref FAQ_00001031.How do I tell the difference between vertex and edge modeling mode in Creator?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001040 | Question

@question
When I try to attach a node in the database hierarchy, sometimes it fails. 
What could be causing this?

@answer
Here are some common reasons a node may fail to attach in the hierarchy: 
<unorderedliststart .>
<listelementstart NOINDENT> The node is already attached
in the hierarchy. <listelementend>
<listelementstart NOINDENT> The node was created 
in a different database than the one to which you are trying to attach now. <listelementend>
<listelementstart NOINDENT> The node is not a valid 
child type for the (parent) node to which you are trying to attach. <listelementend>
<unorderedlistend>

@answer
Each of these situations are described below.

@answer
A node (that is not a reference) can be attached in the hierarchy to no more
than one single parent. If you try to attach a node that is already attached, 
you will get an error.  To determine whether a node is attached, use 
<f mgGetParent> and <f mgGetNestedParent>.  To move a node from one parent
to another, you must first detach the node from its current parent 
using <f mgDetach> then attach the node to its new parent.

@answer
When a node is created, it is bound to a specific database and can only be
attached in that database hierarchy
(there are technical reasons for this, see
<faq_ref_inline FAQ_00001041.Why can't I move a node from one database to another?>
for more information). There are two functions to create new nodes: <f mgNewRec> and
<f mgNewRecDb>.  If you use <f mgNewRec> to create a new node, the node is bound to
the current database (see <f mgSetCurrentDb> and <f mgGetCurrentDb>). If you use 
<f mgNewRecDb> to create a new node, the node is bound to the database you specify
as the <p db> parameter to <f mgNewRecDb>.  Regardless of which function you use
to create the new node, the node can only be attached in the hierarchy of the
database to which it is bound.  If you try to attach a node to a 
database other than the database to which it is bound, you will get an error.
You can use the function <f mgRec2Db> to determine the database to which a node
is bound.

@answer
Nodes in the OpenFlight hierarchy are different types (see 
<faq_ref_inline FAQ_00001002.How can I tell what kind of record I have in an mgrec?> for
more information).  There are implicit rules defining what types of nodes can be 
attached to other node types.  For example a <flt fltGroup> node can be attached to 
many other node types, including <flt fltHeader>, <flt fltGroup>, <flt fltLod>, <flt fltDof>, etc.
A <flt fltGroup> node cannot, however, be attached to a <flt fltObject>, <flt fltPolygon>, 
<flt fltMesh> or <flt fltVertex>.  If you try to attach a child node to a parent node that
does not allow that child type, you will get an error.

@faqrelated
<faq_ref FAQ_00001041.Why can't I move a node from one database to another?>

@see <f mgNewRec>, <f mgNewRecDb>, <f mgSetCurrentDb>, <f mgGetCurrentDb>,
<f mgRec2Db>, <f mgGetParent>, <f mgGetNestedParent>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001041 | Question

@question
Why can't I move a node from one database to another?

@answer
When a node is created, it is allocated from a pool of memory that is owned by
the database in which the node is contained.  In this way, when the database is
closed, all memory allocated for all the nodes it contains can be deallocated
correctly.  For this reason, you are not allowed to simply move nodes from one
database hierarchy to another by detaching from one database and re-attaching
to another.

@answer
If you do need to move a node from one database to another, you will create a
duplicate of the node you want to move (in the context of the destination
database), attach the copy in the destination database hierarchy
and then delete the original node.  

@exref The following examples (in C and Python) show how to move a node
from one database <p srcDb> to another <p dstDb>.  In both cases <p srcNode>
is the node you want to move.  It is attached to <p srcParent>.  You want
to move it to <p dstDb> under parent <p dstParent>. |

@ex |

   // create a copy of srcNode in the destination database
   // note that this duplicates srcNode and all its descendants
   mgrec* dstNode = mgDuplicateToDb (srcNode, dstDb);

   // attach the copy to its new parent in destination database
   mgAttach (dstParent, dstNode);

   // delete the original node
   // no need to detach it, mgDelete detaches and deletes
   mgDelete (srcNode);

@pyex |

   # create a copy of srcNode in the destination database
   # note that this duplicates srcNode and all its descendants
   dstNode = mgDuplicateToDb (srcNode, dstDb)

   # attach the copy to its new parent in destination database
   mgAttach (dstParent, dstNode)

   # delete the original node
   # no need to detach it, mgDelete detaches and deletes
   mgDelete (srcNode)

@see <f mgDuplicateToDb>, <f mgAttach>, <f mgDelete>

@faqrelated
<faq_ref FAQ_00001040.When I try to attach a node in the database hierarchy, sometimes it fails\.  What could be causing this?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001042 | Question

@question
How do I create a new node in a database?

@answer
When you add a new node to a database, you simply create the node and add
it to the hierarchy. Optionally, if the default attributes of the node are 
not what you want, you can also modify one or more of the new node's attributes.

@answer
To create a new node use <f mgNewRec>. You specify the <t mgcode> of
the node type you want to create. To create a group node, for example,
specify <f fltGroup>. After you create the node, you will add
it into the OpenFlight Scene Graph using <f mgAttach>, <f mgAppend>,
<f mgInsert> or <f mgReference>. Each of these functions add a node
into the hierarchy in different ways. To modify a node's attributes
use <f mgSetAttList>.

@exref The following examples (in C and Python) define a function
to create a new object node and attach it to the specified group
parent as its first child. |

@ex |

static void CreateObject (mgrec* parentGroup)
{
   // create an object node
   mgrec* object = mgNewRec (fltObject);

   // attach the new object as the first child of the parent group
   mgAttach (parentGroup, object);
}

@pyex |

def CreateObject (parentGroup):
   # create an object node
   object = mgNewRec (fltObject)

   # attach the new object as the first child of the parent group
   mgAttach (parentGroup, object)

@see <f mgNewRec>, <f mgAttach>, <f mgAppend>, <f mgInsert>, <f mgReference>,
<f mgSetAttList>

@faqrelated
<faq_ref FAQ_00001000.What is an mgrec?>
<faq_ref FAQ_00001002.How can I tell what kind of record I have in an mgrec?>
<faq_ref FAQ_00001040.When I try to attach a node in the database hierarchy, sometimes it fails\.  What could be causing this?>
<faq_ref FAQ_00001044.How do I create a simple polygon with vertices?>
<faq_ref FAQ_00001004.How do I set the attributes of a record in the database?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001043 | Question

@question
How do I create an external reference in a master database?

@answer
Just like groups or objects (and all other node types), external references are simply
nodes in the master database. Whereas groups are type <flt fltGroup> and objects are 
type <flt fltObject>, external references are type <flt fltXref>. The <flt fltXrefFilename>
attribute of the <flt fltXref> node is the file associated to the external reference. 
Just as you would create any node in the db you would use <f mgNewRec> to create the 
external reference, passing <flt fltXref> as the code for the new node. Use <f mgSetAttList>
to set the <flt fltXrefFilename> attribute to associate an OpenFlight file to the external
reference.

@answer
And just like other node types, you need to attach the external reference node in the scene. 
Use <f mgAttach>, <f mgAppend> or <f mgInsert> depending on where you want to attach it. 
Similarly, you can apply transformations to the external reference just like you would 
other node types.

@exref The following examples (in C and Python) show how to create an external reference
in a master database. The new node is attached to the existing node <p parentNode>. |

@ex |

   // create the external reference node
   mgrec* xRef = mgNewRec (fltXref);

   // associate an OpenFlight file to the new external reference
   mgSetAttList (xRef, "c:/MyDatabases/xRef.flt", MG_NULL);

   // attach the new node
   mgAttach (parentNode, xRef);

@pyex |

   # create the external reference node
   xRef = mgNewRec (fltXref))

   # associate an OpenFlight file to the new external reference
   mgSetAttList (xRef, "c:/MyDatabases/xRef.flt")

   # attach the new node
   mgAttach (parentNode, xRef)

@see <f mgNewRec>, <f mgSetAttList>, <f mgAttach>

@faqrelated
<faq_ref FAQ_00001050.How do I apply a matrix (transformation) to a node?>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001080 | Question

@question
What order does mgWalk visit the nodes in the hierarchy?

@answer
<f mgWalk> and <f mgWalkEx> traverse the hierarchy using a depth-first traversal.  
The diagram below shows the order in which the nodes in a simple hierarchy <p g1>
would be visited.<nl>
<jpg mgwalkorder>

@answer
See the example code in <f mgWalk> for more information on how the <p preAction> and
<p postAction> functions for <f mgWalk> are called in the context of the depth-first 
traversal.

@see <f mgWalk>, <f mgWalkEx>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001090 | Question

@question
How do I hide or show a node in the Creator Graphics view?

@answer
In Creator you use the <b Toggle Display> command to hide or show nodes in
the Graphics View.  You can also do this programmatically in your plug-in 
or stand-alone application.  The <b On>/<b Off> state (visibility) of a 
node is an attribute (<f fltIOn>) of the node that can set or get 
using <f mgSetAttList> or <f mgGetAttList>, respectively.

@answer
In Creator, this attribute controls whether a node is visible in the Graphics
view.  In the Hierarchy view, nodes that are <b Off> are still drawn, but drawn
with a solid outline and transparent box. In both Creator and your stand-alone
application, this attribute controls whether or not a node is visited by 
<f mgWalk> or <f mgWalkEx> when <m MWALK_ON> is used.

@exref The following examples (in C and Python) show how to hide a node
using <f mgSetAttList>. |

@ex |

   // hide node
   mgSetAttList (node, fltIOn, 0, MG_NULL);

@pyex |

   # hide node
   mgSetAttList (node, fltIOn, 0)

@answer
Note that the visibility of a node is hierarchical.  In other words, a node is 
visible only if it is visible <b -AND-> all of its ancestors are visible. Conversely,
a node is NOT visible if it is NOT visible <b -OR-> any of its ancestors are NOT visible.
These rules imply that if you set a node's visibility <b On> and any of its ancestors are <b Off>,
the node will remain NOT visible.  In the same way, if you set a node's visibility to <b Off>, all its 
descendants will be NOT visible.

@answer
Also note that the <f fltIOn> attribute is not saved with the OpenFlight file.
It is a transient attribute that only applies to a node while the node is in memory.
It applies only to node records above the <f fltVertex> level.

@see <f mgSetAttList>, <f mgGetAttList>, <f mgWalk>
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
@faq FAQ_00001100 | Question

@question
If I change the position of a vertex, is there an easy way to recalculate its
texture coordinates to match the original texture mapping?

@answer
There is a useful utility function called <f mgMatrixFormXYZToUV> that can help.  
It creates a matrix that represents the transformation from XYZ coordinates 
to UV texture coordinates for a polygon in a given texture layer.  So if you calculate 
and store this matrix before you change the position of any vertex of the polygon, you 
can then use this matrix after moving the vertex to calculate the UV texture coordinates 
of the vertex in its new XYZ position.

@exref The following examples (in C and Python) show how you might use 
<f mgMatrixFormXYZToUV>. |

@ex |

	mgcoord3d xyz;
	mgcoord3d uv;
	mgrec* vtx;
	mgmatrix uvMat;

	// get the UV matrix that transforms XYZ coordinates to
	// UV texture coordinates for texture layer 0 of poly
	mgMatrixFormXYZToUV (&uvMat, poly, 0);

	// move the Z coordinate of the first vertex to 0
	vtx = mgGetChild (poly);

	mgGetVtxCoord (vtx, &xyz.x, &xyz.y, &xyz.z);
	xyz.z = 0.0;

	mgSetVtxCoord (vtx, &xyz.x, &xyz.y, &xyz.z);

	// after moving the vertex, recalculate the UV texture
	// coordinates for the new vertex position
	uv = mgCoord3dTransform (uvMat, &xyz);

	// finally update the UV texture coordinates on the vertex
	// the new U value is in the x coordinate
	// the new V value is in the y coordinate
	// the z coordinate is not interesting here
	mgSetAttList (vtx, fltVU, uv.x, fltVV, uv.y, MG_NULL);

@pyex |

	# get the UV matrix that transforms XYZ coordinates to
	# UV texture coordinates for texture layer 0 of poly
	b, uvMat = mgMatrixFormXYZToUV (poly, 0)

	# move the Z coordinate of the first vertex to 0
	vtx = mgGetChild (poly)
	xyz = mgcoord3d()
	b, xyz.x, xyz.y, xyz.z = mgGetVtxCoord (vtx)
	xyz.z = 0.0
	mgSetVtxCoord (vtx, xyz.x, xyz.y, xyz.z)

	# after moving the vertex, recalculate the UV texture
	# coordinates for the new vertex position
	uv = mgCoord3dTransform (uvMat, xyz)

	# finally update the UV texture coordinates on the vertex
	# the new U value is in the x coordinate
	# the new V value is in the y coordinate
	# the z coordinate is not interesting here
	mgSetAttList (vtx, fltVU, uv.x, fltVV, uv.y)

@answer
Note that <f mgMatrixFormXYZToUV> works well if your polygon 
was texture mapped "nicely" (like using 3 Point Put, for example). 
If you have any warping applied, it will not work so well.

@see <f mgSetAttList>, <f mgGetAttList>, <f mgMatrixFormXYZToUV>, <f mgCoord3dTransform>
//
////////////////////////////////////////////////////////////////////////////////
