
/*
@doc MAIN

@contents1 Introduction |

Last revised: <date>

@group1

@group2 
What Is the OpenFlight API?

@normal
The <i OpenFlight API> is a set of C header files and libraries that provides a 
programming interface to Creator and the OpenFlight database format. The API is divided 
conceptually into four levels: Read, Write, Extensions, and Tools. This document contains
the reference pages for all levels of the OpenFlight API.  All levels of the API are available 
on the Windows platform. Levels 1, 2 and 3 are available on the Linux platform.

<i OpenFlight Script> is a cross-platform Python Language binding to the C Language OpenFlight API. 
Based on the Python scripting language, OpenFlight Script provides nearly all the functionality of  
the OpenFlight API. If you understand the concepts of the OpenFlight API, you 
will find programming in either the C Language API or OpenFlight Script very similar.

You can use OpenFlight Script to do nearly everything you could otherwise do with the C Language API. 
In general, OpenFlight Script applications run more slowly than comparable tools written 
using the C Language API, so if performance is an issue, consider using the C Language API.

@group2 
Audience

@normal

This document is written for modelers and programmers who want to write stand-alone applications,
plug-ins, or scripts using OpenFlight API interfaces.  To use the OpenFlight API, 
and this document, you should be comfortable with the American National Standards Institute
(ANSI) C programming language and have some understanding of 3D modeling.  Familiarity
with Presagis modeling tools and the OpenFlight format is helpful, but is not required.

@group2 
About This Document

@normal

This document provides detailed information on functions included in the OpenFlight API.  
This document is intended to be used in conjunction with the <i OpenFlight API Developer Guide>.

@group2 
What can I distribute to others?

@normal

Users may develop and share their own content, code, and plug-ins freely at their own 
discretion. The OpenFlight API DLLs used by the applications and plug-ins you develop
may only be distributed with a signed <i Amendment to Software License Agreement>. 
This agreement includes a description of the intended use of the files, and outlines 
the usage rights.  This agreement (OpenFlight_API_Amendment_to_SLA_Presagis_051109.pdf)
is included in the documentation folder of the OpenFlight API distribution or can be obtained 
by contacting Presagis for more information e-mail: openflight@presagis.com. Under no
circumstances are you allowed to distribute the debug version of the OpenFlight
API DLLs.

@group2 
What is not allowed?

@normal

Users of the OpenFlight API are not allowed under any circumstances to redistribute 
the header files, sample code, import libraries (.lib files), and documentation (including
reference document, tutorials and any developers guides associated with the OpenFlight API
and Presagis Creator software product).

@group2 
How to Contact Presagis

@normal
  
Technical Support:<nl>
creator@presagis.com<nl>
877 289-5670 (toll free)<nl>
http://www.presagis.com<nl>

Creator Sales:<nl>
sales@presagis.com<nl>
http://www.presagis.com<nl>

@group2 
Use and Disclosure of Data

@normal

PROPRIETARY NOTICE: This document, including the information contained herein, 
is confidential and/or proprietary to Presagis Canada Inc. and/or Presagis USA Inc. 
and shall not be reproduced or disclosed in whole or in part, or used for any 
purpose whatsoever without the prior written authorization of Presagis Canada Inc. 
or Presagis USA Inc.

@contents1 OpenFlight API Release Notes |

Last revised: <date>

@normal
This section contains the release notes for all versions of the
OpenFlight API beginning with v2.1 and ending with the current version.
The release notes are listed here in reverse chronological order (i.e., 
the most recent version first). In addition to version specific release notes, 
there is also a general release notes section here containing information 
applicable to the most current version.

@group1 General

@group2 Visual Studio Compatibility
@normal
The OpenFlight API is distributed in the following binary formats for the 
Windows platform:<nl>

<tablestart SIMPLE>

<tablerowstart HEADER>
<tableelementstart BORDER> Visual Studio Version <tableelementend>
<tableelementstart BORDER> Compiler-Platform <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> Visual Studio 2005 <tableelementend>
<tableelementstart BORDER> <mono VC8-Win32> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> Visual Studio 2005 <tableelementend>
<tableelementstart BORDER> <mono VC8-x64> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> Visual Studio 2008 <tableelementend>
<tableelementstart BORDER> <mono VC9-Win32> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> Visual Studio 2008 <tableelementend>
<tableelementstart BORDER> <mono VC9-x64> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> Visual Studio 2013 <tableelementend>
<tableelementstart BORDER> <mono VC12-Win32> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> Visual Studio 2013 <tableelementend>
<tableelementstart BORDER> <mono VC12-x64> <tableelementend>
<tablerowend>

<tableend>

@normal
If you are developing plug-ins for Creator 15, you should
install and use <b VC12-Win32> or <b VC12-x64> depending on which version
of Creator you are using (32 or 64 bit, respectively) so your plug-ins are
compatible.<nl>

@normal
If you are developing plug-ins for Creator 14, you should
install and use <b VC9-Win32> so your plug-ins are compatible.<nl>

If you are developing plug-ins for Creator 13 (v5.0), you should
install and use <b VC9-Win32> so your plug-ins are compatible.<nl>

@normal
If you are developing plug-ins for Creator v3.4 through v4.2, you should
install use <b VC8-Win32> so your plug-ins are compatible.<nl>

@normal
If you are developing stand-alone OpenFlight Scripts, you should
install <b VC9-Win32> or <b VC9-x64>. The necessary Python binding 
files (.pyd) are only available with these formats. You will also
need to install Python 2.7.X if you are developing stand-alone scripts.
You do not need to install Python if you are using OpenFlight script
exclusively within Creator.
<nl>

@normal
If you are developing stand-alone applications, you can install and
use any format.

@normal
Both of the VC9 versions of the OpenFlight API DLLs are dependent on
VC90 CRT version 9.0.21022.8.  The OpenFlight API installer automatically
installs the proper Microsoft Visual Studio 2008 (release) redistributable package
if your computer does not already have it.  The debug version of the CRT should
be installed on your computer when you apply the proper patches/service packs
to Visual Studio 2008.

@normal
Both of the VC8 versions of the OpenFlight API DLLs are dependent on 
VC80 CRT version 8.0.50727.4053.  The OpenFlight API installer automatically
installs the proper Microsoft Visual Studio 2005 (release) redistributable package 
if your computer does not already have it.  The debug version of the CRT should
be installed on your computer when you apply the proper patches/service packs 
to Visual Studio 2005.

@normal
When you install the OpenFlight API, you can choose which binary format
you want or you can choose to install them all. In this way, you can
have multiple binary formats installed on your computer simultaneously 
and then choose (at runtime) which format to run with.

@group2 Installed Directories
@normal
On both Windows and Linux platforms, the OpenFlight API is installed into
the Presagis Common Directory Organization.  The OpenFlight API files are
distributed into several subfolders under the root of this organization. 
This root folder is different depending on the platform but the subfolder
structure below this root is the same for all platforms.

By convention, the environment variable <m PRESAGIS_OPENFLIGHT_API> is used
to specify the root installation folder of the OpenFlight API.  Additionally, 
environment variables of the form <m PRESAGIS_OPENFLIGHT_API_version> where 
<m version> specifies the major and minor version numbers of the distribution, 
are used to maintain multiple versions of the OpenFlight API simultaneously.  
For example, the environment variable <m PRESAGIS_OPENFLIGHT_API_15_0> would 
correspond to OpenFlight API version 15.

The Windows installer creates these two environment variables automatically.

The Linux installer includes a tcsh script file that you can execute to
set these environment variables manually.

The following sections describe the subfolders below the OpenFlight
installation root folder.  Depending on which platform and 
compiler/architecture you choose to install, <mono \<platform\>>
in the following sections will be:

<tablestart SIMPLE>

<tablerowstart .>
<tableelementstart BORDER> <mono \<empty\>> <tableelementend>
<tableelementstart BORDER> if you installed VC12-Win32 or Linux <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono _x64> <tableelementend>
<tableelementstart BORDER> if you installed VC12-x64 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono _vc9> <tableelementend>
<tableelementstart BORDER> if you installed VC9-Win32<tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono _vc9_x64> <tableelementend>
<tableelementstart BORDER> if you installed VC9-x64 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono _vc8> <tableelementend>
<tableelementstart BORDER> if you installed VC8-Win32 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono _vc8_x64> <tableelementend>
<tableelementstart BORDER> if you installed VC8-x64 <tableelementend>
<tablerowend>

<tableend>

@group3 C source header files
@normal
The C source header files are located in:
<q PRESAGIS_OPENFLIGHT_API/include>

@group3 Link libraries
@normal
The link libraries are located in:
<q PRESAGIS_OPENFLIGHT_API/lib\<platform\>>

@normal
where <mono lib\<platform\>> is:

<tablestart SIMPLE>

<tablerowstart HEADER>
<tableelementstart BORDER> Link Library Folder <tableelementend>
<tableelementstart BORDER> Contents <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib> <tableelementend>
<tableelementstart BORDER> Link libraries for VC12-Win32 or Linux <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib_x64> <tableelementend>
<tableelementstart BORDER> Link libraries for VC12-x64 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib_vc9> <tableelementend>
<tableelementstart BORDER> Link libraries for VC9-Win32 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib_vc9_x64> <tableelementend>
<tableelementstart BORDER> Link libraries for VC9-x64 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib_vc8> <tableelementend>
<tableelementstart BORDER> Link libraries for VC8-Win32 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib_vc8_x64> <tableelementend>
<tableelementstart BORDER> Link libraries for VC8-x64 <tableelementend>
<tablerowend>

<tableend>

@group3 Dynamic Link Libraries
@normal
Both Debug and Release versions of the dynamic link libraries 
are included. Dynamic link libraries are located in:<nl>

@group4 On Windows

<q PRESAGIS_OPENFLIGHT_API/bin\<platform\>>

@normal
where <mono bin\<platform\>> is:

<tablestart SIMPLE>

 
<tableelementstart BORDER> Dynamic Link Library Folder <tableelementend>
<tableelementstart BORDER> Contents <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin> <tableelementend>
<tableelementstart BORDER> Dynamic Link libraries for VC12-Win32 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin_x64> <tableelementend>
<tableelementstart BORDER> Dynamic Link libraries for VC12-x64 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin_vc9> <tableelementend>
<tableelementstart BORDER> Dynamic Link libraries for VC9-Win32 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin_vc9_x64> <tableelementend>
<tableelementstart BORDER> Dynamic Link libraries for VC9-x64 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin_vc8> <tableelementend>
<tableelementstart BORDER> Dynamic Link libraries for VC8-Win32 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin_vc8_x64> <tableelementend>
<tableelementstart BORDER> Dynamic Link libraries for VC8-x64 <tableelementend>
<tablerowend>

<tableend>

@group4 On Linux

<q PRESAGIS_OPENFLIGHT_API/lib>

@normal
The Dynamic Link Library folders (for both Windows and Linux) contain Debug 
and Release versions in their respective subfolders:

<tablestart SIMPLE>

<tablerowstart HEADER>
<tableelementstart BORDER> Dynamic Link Library Subfolder <tableelementend>
<tableelementstart BORDER> Contents <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono debug> <tableelementend>
<tableelementstart BORDER> Debug dynamic link libraries <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono release> <tableelementend>
<tableelementstart BORDER> Release dynamic link libraries <tableelementend>
<tablerowend>

<tableend>

@group3 Documentation
@normal

The documents included with the OpenFlight API include:

<i OpenFlight API Installation Guide><nl>
<i OpenFlight API Release Notes><nl>
<i OpenFlight API Developer Guide><nl>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<i Volume 1 (Read/Write)><nl>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<i Volume 2 (Extensions/Tools)><nl>
<i OpenFlight API Reference Set><nl>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<i OpenFlight API Reference><nl>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<i OpenFlight Data Dictionary><nl>
<i Amendment to Software License Agreement><nl>

These files are installed in different locations depending on the platform: 

@group4 On Windows
@normal

For the Windows platform, the documentation for the OpenFlight API is included
in the <i Presagis Documentation Library>. The <i Presagis Documentation Library> is 
Compiled HTML Help (CHM) format and includes documentation for all the Presagis
products you have installed. The <i Presagis Documentation Library> is located at:

<q PRESAGIS_ROOT/docs/Presagis_MS\.chm>

where <m PRESAGIS_ROOT> is the root folder where your Presagis products are 
installed. To view the OpenFlight documentation, as well as all Presagis product
documentation, open this file and browse to the OpenFlight API section
in the viewer that is displayed.  You can also access the
<i Presagis Documentation Library> via the Windows Start Menu.

In addition to the CHM versions of these documents, some documents are provided 
in alternative formats:

<i OpenFlight API Installation Guide> and <i OpenFlight API Release Notes> (PDF) - both 
located in:
<q PRESAGIS_ROOT/docs/>

<i OpenFlight API Developer Guide> (PDF) - located in:
<q PRESAGIS_OPENFLIGHT_API/docs/developerguide>

<i OpenFlight API Reference Set> (HTML) - located in:
<q PRESAGIS_OPENFLIGHT_API/docs/reference/OpenFlight_API_Reference_Set\.htm>

@group4 On Linux
@normal

For the Linux platform, the documentation is located in:
<q PRESAGIS_OPENFLIGHT_API/docs>

The <i OpenFlight API Installation Guide> and <i OpenFlight API Release Notes>
are located in the root (docs) folder.

The <i OpenFlight API Developer Guide> (PDF format) is located in the folder:
<q PRESAGIS_OPENFLIGHT_API/docs/developerguide>

The <i OpenFlight API Reference Set> (HTML format) is located in:
<q PRESAGIS_OPENFLIGHT_API/docs/reference/OpenFlight_API_Reference_Set\.htm>

@group3 Sample Code
@normal
Sample code is located in:
<q PRESAGIS_OPENFLIGHT_API/samples>

with subfolders for the individual kinds of samples:

<tablestart SIMPLE>

<tablerowstart .>
<tableelementstart BORDER> <b Samples Subfolder> <tableelementend>
<tableelementstart BORDER> <b Contents> <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono apps> <tableelementend>
<tableelementstart BORDER> sample stand-alone programs <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono extensions> <tableelementend>
<tableelementstart BORDER> sample OpenFlight data extensions <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono plugins> <tableelementend>
<tableelementstart BORDER> sample plug-ins (not included in the Linux distribution) <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono scripts> <tableelementend>
<tableelementstart BORDER> sample OpenFlight and Creator scripts <tableelementend>
<tablerowend>

<tableend>

@group3 Tools
@normal
Tools are located in:
<q PRESAGIS_OPENFLIGHT_API/tools>

@normal
There is one single tool located here.  That is <mono ddbuild\.exe>.  You use this
program to build OpenFlight Extensions. See the <i OpenFlight API Developer Guide, Volume 2>
for more information.

@group3 Redistributable OpenFlight API Binaries
@normal

If you need to redistribute the OpenFlight API binaries,
you would redistribute the Release version of the Dynamic
Link Libraries as described in the previous section. 
Note that under no 
circumstances are you allowed to redistribute the debug
versions.

@group2 Plug-in Runtime Directory
@normal
Plug-ins are loaded in the stand-alone program environment when your program or script
calls the OpenFlight API function <f mgInit>. <f mgInit> searches for plug-ins in the
following locations (in the order listed). As soon as a folder is found in
one of these locations, <f mgInit> stops searching for other locations and 
loads the plug-ins it finds in the first folder found.

<orderedliststart .>

<listelementstart NOINDENT>
The directory (or directories) your program specifies when calling <f mgSetPluginFolder>. If you call 
this function before <f mgInit> to specify one or more directories, the folder(s)
you specify will be searched for plug-ins. To specify more than one directory, pass a 
semi-colon delimited list of paths to <f mgSetPluginFolder>. 
<listelementend>

<listelementstart NOINDENT>
The directory (or directories) specified by the environmental variable <b PRESAGIS_OPENFLIGHT_PLUGIN_DIR>. 
This environmental variable may specify any accessible directory on your computer or 
may specify multiple directories using a semi-colon to delimit each path.
<listelementend>

<listelementstart NOINDENT>
A directory named <m plugins> immediately below the directory that contains the executable being run. 
<listelementend>

<orderedlistend>

@normal
Creator loads plug-ins automatically when it starts. Creator searches for plug-ins in the
following locations (in the order listed). As soon as a folder is found in one of these 
locations, Creator stops searching for other locations and loads the plug-ins it finds in
the first folder found.

<orderedliststart .>

<listelementstart NOINDENT>
The directory (or directories) specified by the environmental variable <b PRESAGIS_CREATOR_PLUGIN_DIR>. 
This environmental variable may specify any accessible directory on your computer or 
may specify multiple directories using a semi-colon to delimit each path.
<listelementend>

<listelementstart NOINDENT>
A directory named <m plugins> in the Creator configuration folder. This folder 
is located at:

<q PRESAGIS_ROOT/Creator/config/plugins>
<listelementend>

<orderedlistend>

@group2 Visual Studio Project Settings

@normal
It is very important that your plug-in module be linked with the correct system 
run-time libraries to match Creator.  In particular, multithreaded DLLs are 
required.  In Visual Studio, open the <m Project Properties> window, 
select the <m C/C++> tab and then select the <m Code Generation> category.
For <m Runtime Library>, select <m Multi-threaded Debug DLL> for the 
Win32 Debug configuration and <m Multi-threaded DLL> for the Win32 Release
configuration.

@group2 Deprecated API

@normal
Please review the list of deprecated API symbols and functions that
appear in the <m Deprecated API> section of this reference document.  
For each symbol that appears in this section, an appropriate 
replacement symbol or strategy is also given.  Although deprecated
API symbols are still supported in the current version of the API,
they may not be in future releases.  To ensure that code you develop
using the MultiGen OpenFlight API remains compatible with future
versions of the API, you should eliminate any deprecated symbols
from your code.

When you compile code that uses a deprecated symbol, the compiler
may issue a warning message stating that the symbol is not defined
or has been deprecated.
This is expected and is an indication to you that action should be
taken to replace that symbol as described above.  Note that even
though the compiler issues this warning message, your program or
plug-in should link successfully even when it uses a deprecated
symbol.

@group1 v15.0
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.5.

@group2 Visual Studio Compatibility
@normal
The OpenFlight API is distributed in several binary formats for the Windows platform:<nl>
Visual Studio 2013 (VC12-Win32)<nl>
Visual Studio 2013 (VC12-x64)<nl>
Visual Studio 2008 (VC9-Win32)<nl>
Visual Studio 2008 (VC9-x64)<nl>
Visual Studio 2005 (VC8-Win32)<nl>
Visual Studio 2005 (VC8-x64)<nl>
Support for Visual Studio 6 was terminated

@group2 New Functions

@group3 I/O Functions
@normal
<f mgIsInitialized><nl>

@group3 Tool Activation Functions
@normal
<f mgGetActivationKeyboardFlags><nl>

@group2 New Symbols
@normal
<m MEFV_1650> for <f mgExportDb>

@group2 New Fields
@normal

The field <b activateReason> was added to the <t mgtextactivatecallbackrec> structure.

@group2 New in the OpenFlight Data Dictionary
@normal

The following fields were added to <flt fltIMaterial> to provide access to the new 
Physical Material Map record in the Extended Material:<nl>
fltPhysicalMaterialMapEx<nl>
fltPhysicalMaterialMapExTexture<nl>

@group2 Fixes/Enhancements
@normal

Enhanced <f mgExportDb> to allow you to write the current version of OpenFlight.

Fixed the following functions to work correctly in OpenFlight Script (Python):<nl>
<f mgExtensionFieldGetString><nl>
<f mgExtensionFieldGetXMLString><nl>

Fixed <t mgwalkfunc> functions to propagate exceptions correctly in OpenFlight Script (Python) for:<nl>
<f mgWalk><nl>
<f mgWalkEx><nl>
<f mgWalkRecList><nl>
<f mgFind><nl>
<f mgFindEx><nl>
<f mgIterateRecList><nl>

Fixed crash in <f mgOpenDb> when OpenFlight file does not contain a Vertex Palette record (opcode 67) but
references it within a Vertex List record (opcode 72). 

Enhanced <f mgIsDb> to examine the database file more thoroughly to check if it is an OpenFlight file.

Fixed <f mgGraphicsViewSettingSetInteger> to set <m MGVI_WINDOWVIEW> properly when no graphics view is open.

@group1 v14.0
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.4.

@group2 Loading plug-ins

@group3 Loading plug-ins in stand-alone programs

@normal
The way in which plug-ins are located by stand-alone programs has changed.

A new function, <f mgSetPluginFolder>, was added that allows you to specify the
directory (or directories) from which plug-ins will be loaded into your stand-alone
program. You must call this function before <f mgInit>. When you do, the folder(s)
you specify will be searched for plug-ins by <f mgInit>. In this way, 
you can control exactly which plug-ins you want to load into your 
stand-alone program environment. To specify more than one directory, pass
a semi-colon delimited list of paths to <f mgSetPluginFolder>.

Stand-alone programs no longer use the <b PRESAGIS_CREATOR_PLUGIN_DIR>
environment variable to locate plug-ins. Instead they use the environment
variable <b PRESAGIS_OPENFLIGHT_PLUGIN_DIR>. This allows more control 
on systems where both Creator and stand-alone applications are used simultaneously.
Furthermore, the environment variable <b PRESAGIS_OPENFLIGHT_PLUGIN_DIR> may now
specify multiple directories, each delimited by a semi-colon.

@group3 Loading plug-ins in Creator

@normal
The way in which plug-ins are located by Creator has changed.

Creator still uses the <b PRESAGIS_CREATOR_PLUGIN_DIR>
environment variable to locate plug-ins. However, the value
of this environment variable may now specify multiple directories, 
each delimited by a semi-colon.

Creator no longer searches for a folder named <m plugins> immediately below
the directory that contains the Creator executable. When an alternative plug-in 
folder is desired, use the environment variable <b PRESAGIS_CREATOR_PLUGIN_DIR>.

@group2 New Functions

@group3 Base Functions
@normal
<f mgSetPluginFolder><nl>

@group3 Editor Context Functions
@normal
<f mgEditorCancelTool>

@group3 Geometry Functions
@normal
<f mgCoord3dDistanceSquared><nl>
<f mgVectorfSetUnitized><nl>
<f mgVectorfUnitize><nl>
<f mgVectorfEqual><nl>
<f mgVectordEqual><nl>

@group3 Preference Functions
@normal
<f mgSetReadTexturesFlag><nl>
<f mgSetSaveUnreferencedUVs><nl>

@group3 Structure Functions
@normal
<f mgIsRelated><nl>
<f mgCountXform><nl>

@group3 Tool Registration Functions
@normal
<f mgEditorSetCloseDialogFunc>

@group2 New Symbols
@normal
<e mgcontrolattribute.MCA_TEXTACTIVATEONCHANGED> for <f mgControlSetAttribute><nl>
<m MPREFI_TEXTUREPALETTEDIMENSION> for <f mgModelingPrefGetInteger><nl>
<m mgeditorclosedialogfunc> for <f mgEditorSetCloseDialogFunc><nl>
<m mgclosedialogcallbackrec> for <f mgEditorSetCloseDialogFunc>

@group2 New Tool Attributes for Editor Tools 
@normal
(see <f mgRegisterEditor>)

<m MTA_NODIALOGPOSITIONPREFERENCE><nl>

@group2 New in the OpenFlight Data Dictionary
@normal

The following field was added to <flt fltImage> to 
provide access to Texture Type attribute on <flt fltImage> records.
fltImgTextureType<nl>

@group2 Fixes/Enhancements
@normal

Fixed <f mgGetSelectList> to provide (via <f mgGetNextRecInList> and <f mgGetNthRecInList>) the 
correct matrix for selected nodes contained below instances and/or external reference nodes.

Fixed <f mgSetMatrix> to refresh the Creator graphics view and mark the database as modified
correctly when called from a plug-in or script in Creator to update Transformation record codes.

Fixed <f mgReplaceTexture> to return <e mgbool.MG_TRUE> only if the new texture assigned to
the texture palette has a different name than the original texture at that index.

Corrected the OpenFlight API Reference page for <f mgGetCurrentGridMatrix> to correctly
describe the matrix returned.

Fixed <f mgGetTextureSaveName> to return correct name when texture file has absolute path.

Fixed <f mgWalk> to visit extension nodes correctly when extension DLL is not present.

Fixed sample code in <f mgPromptDialogFile> to show correct usage for <m MPFA_FLAGS>.

Fixed the following functions to work correctly in OpenFlight Script (Python):<nl>
<f mgGetMatTextureLayer><nl>
<f mgGetModelingParentMatrix><nl>
<f mgMeshGetVtxColor><nl>
<f mgMeshGetVtxColorAlpha>

Fixed the following functions to refresh the Light Point Palette window and mark 
the database as modified correctly when called from a plug-in or script in Creator:<nl>
<f mgNewLightPointAppearance><nl>
<f mgNewLightPointAnimation><nl>
<f mgDeleteLightPointAppearance><nl>
<f mgDeleteLightPointAnimation><nl>
<f mgLightPointAnimationSequenceSet>

Fixed <f mgReadColorPalette> to refresh the Color Palette window, redraw the scene and mark 
the database as modified correctly when called from a plug-in or script in Creator.

Corrected the reference page for <f mgMeshPrimitiveGetVtxIndexArray> to show 
the correct Python signature.

Corrected the reference page for <m MPRIM_QUAD_STRIP> to show 
the correct formula for determining vertices for a quadrilateral strip
of a <flt fltMesh>.

Corrected the reference page for <m MPRIM_TRI_STRIP> to clarify 
the description on how vertices for a triangle strip are calculated
for a <flt fltMesh>.

Changed the description of the fltPolyTemplate field of the <flt fltPolyon>
node record in the OpenFlight Data Dictionary.

@group2 Constant Qualifiers in Function Declarations
@normal

The signatures for several function calls have been modified to include the
C language 'const' qualifier where appropriate.  In most instances this will 
not affect your existing code.  Following is a list of the affected functions:

<f mgNewConstructVertex><nl>
<f mgSetConstructVertexCoords><nl>
<f mgNewConstructEdge><nl>
<f mgSetConstructEdgeCoords><nl>

In addition the signature of the file locator function <t mgfilelocatorfunc> has
also been changed to include the C language 'const' qualifier for the <p inputFileName>
parameter. If you have defined a file locator function in your application, you will have
to modify its signature to accommodate this change.

@group1 v5.0
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.4. 

@group2 Visual Studio Compatibility
@normal
The OpenFlight API is distributed in several binary formats for the Windows platform:<nl>
Visual Studio 2008 (VC9-Win32)<nl>
Visual Studio 2008 (VC9-x64)
Visual Studio 2005 (VC8-Win32)<nl>
Visual Studio 2005 (VC8-x64)<nl>
Visual Studio 6 (VC6-Win32)<nl>

@normal
If you are developing plug-ins for Creator 13 (v5.0) you should use VC9-Win32.  

@normal If you are developing plug-ins for Creator v3.4 - v4.2, you should use VC8-Win32.  

@normal If you are developing plug-ins for Creator v3.3 or earlier, you should use VC6-Win32. 

@normal If you are developing stand-alone applications, you can choose any format.  

@normal If you are developing stand-alone OpenFlight Scripts, you should
install VC9-Win32 or VC9-x64 as the necessary Python binding 
files (.pyd) are only available with these VC9 formats.

@normal
The OpenFlight API installer for the Windows platform includes the binary 
files for all platforms.  When you install the OpenFlight API on Windows, 
you can choose which platform you want or you can choose to install them all.

@normal
Both of the VC9 versions of the OpenFlight API DLLs are dependent on 
VC90 CRT version 9.0.21022.8.  The OpenFlight API installer automatically
installs the proper Microsoft Visual Studio 2008 (release) redistributable package if your 
computer does not already have it.  The debug version of the CRT should be installed on
your computer when you apply the proper patches/service packs to Visual Studio 2008.

@normal
Both of the VC8 versions of the OpenFlight API DLLs are dependent on 
VC80 CRT version 8.0.50727.4053.  The OpenFlight API installer automatically
installs the proper Microsoft Visual Studio 2005 (release) redistributable package if your 
computer does not already have it.  The debug version of the CRT should be installed on
your computer when you apply the proper patches/service packs to Visual Studio 2005.

@group2 Common Directory Organization
@normal
The OpenFlight API is now installed into the updated Presagis Common Directory Organization. 
This structure is slightly different than previous installations and affects the developer
in the following areas:

Location of link libraries<nl>
Location of documentation<nl>
Location of redistributable OpenFlight API binaries<nl>
Location of ddbuild parser utility<nl>

Note that the relocation of the link libraries will cause developers to update their
Visual Studio Project files and/or makefiles before
the corresponding application(s) or plug-in(s) can be rebuilt
with this version of the OpenFlight API.

@group3 Location of link libraries
@normal
The subfolder containing the link libraries has been changed to include a platform
designator:

<q PRESAGIS_OPENFLIGHT_API/lib\<platform\>>

@normal
where <mono lib\<platform\>> is:

<tablestart SIMPLE>

<tablerowstart HEADER>
<tableelementstart BORDER> Link Library Folder <tableelementend>
<tableelementstart BORDER> Contents <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib> <tableelementend>
<tableelementstart BORDER> Link libraries for VC9-Win32 or Linux <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib_x64> <tableelementend>
<tableelementstart BORDER> Link libraries for VC9-x64 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib_vc8> <tableelementend>
<tableelementstart BORDER> Link libraries for VC8-Win32 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib_vc8_x64> <tableelementend>
<tableelementstart BORDER> Link libraries for VC8-x64 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono lib_vc6> <tableelementend>
<tableelementstart BORDER> Link libraries for VC6-Win32 <tableelementend>
<tablerowend>

<tableend>

@group3 Location of dynamic link libraries
@normal
The subfolder containing the dynamic link libraries has been changed
to include a platform designator:

<q PRESAGIS_OPENFLIGHT_API/bin\<platform\>>

@normal
where <mono bin\<platform\>> is:

<tablestart SIMPLE>

<tablerowstart HEADER>
<tableelementstart BORDER> Dynamic Link Library Folder <tableelementend>
<tableelementstart BORDER> Contents <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin> <tableelementend>
<tableelementstart BORDER> Dynamic link libraries for VC9-Win32 or Linux <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin_x64> <tableelementend>
<tableelementstart BORDER> Dynamic link libraries for VC9-x64 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin_vc8> <tableelementend>
<tableelementstart BORDER> Dynamic link libraries for VC8-Win32 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin_vc8_x64> <tableelementend>
<tableelementstart BORDER> Dynamic link libraries for VC8-x64 <tableelementend>
<tablerowend>

<tablerowstart .>
<tableelementstart BORDER> <mono bin_vc6> <tableelementend>
<tableelementstart BORDER> Dynamic link libraries for VC6-Win32 <tableelementend>
<tablerowend>

<tableend>

@group3 Location of documentation
@normal

On the Windows platform, the documentation for the OpenFlight API is now included
in the <i Presagis Documentation Library>. The <i Presagis Documentation Library> 
is Compiled HTML Help (CHM) format and includes documentation for all the Presagis 
products you have installed. The <i Presagis Documentation Library> is located at:

<q PRESAGIS_ROOT/docs/Presagis_MS\.chm>

where <m PRESAGIS_ROOT> is the root folder where your Presagis products are 
installed. To view the OpenFlight documentation, as well as all Presagis product
documentation, open this file and browse to the OpenFlight API section
in the <i Presagis Documentation Library> viewer that is displayed.  You can also access the
<i Presagis Documentation Library> via the Windows Start Menu.

On the Linux platform, the documentation is still located in: 
<q PRESAGIS_OPENFLIGHT_API/docs>

@group3 Location of ddbuild parser utility
@normal
The ddbuild parser (used to help you create your OpenFlight 
extension plug-ins) is now located in:

<q PRESAGIS_OPENFLIGHT_API/tools>

@group2 OpenFlight API Users Guide
@normal
The <i OpenFlight API Users Guide> has been renamed <i OpenFlight API Developer Guide>.

@group2 OpenFlight Script
@normal
OpenFlight Script was updated to run with Python 2.7.X.
To run stand-alone OpenFlight Scripts, a Python 2.7.X installation is required.
No Python installation is required to run OpenFlight Scripts in Creator. 

@group2 New Functions

@group3 Attribute Functions
@normal
<f mgGetVtxBackColorRGB><nl>
<f mgSetVtxBackColorRGB><nl>

@group3 Editor Context Functions
@normal
<f mgEditorGetToolActivation><nl>

@group3 Geometry Functions
@normal
<f mgVectordNegate><nl>
<f mgVectorfZero><nl>
<f mgVectorfXAxis><nl>
<f mgVectorfNegativeXAxis><nl>
<f mgVectorfYAxis><nl>
<f mgVectorfNegativeYAxis><nl>
<f mgVectorfZAxis><nl>
<f mgVectorfNegativeZAxis><nl>
<f mgVectorfCross><nl>
<f mgVectorfDot><nl>
<f mgVectorfNegate><nl>
<f mgVectorfLerp><nl>

@group3 Graphics View Functions
@normal
<f mgNewPaneLayout><nl>
<f mgFreePaneLayout><nl>
<f mgGetPaneLayout><nl>
<f mgSetPaneLayout><nl>

@group3 I/O Functions
@normal
<f mgGetDbVersion><nl>

@group3 Line Style Functions
@normal
<f mgGetLineStyle><nl>
<f mgGetLineStyleCount><nl>
<f mgGetFirstLineStyle><nl>
<f mgGetNextLineStyle><nl>
<f mgNewLineStyle><nl>
<f mgDeleteLineStyle><nl>
<f mgGetCurrentLineStyle><nl>
<f mgSetCurrentLineStyle><nl>

@group3 Online Help Functions
@normal
<f mgPluginSetHelpContext>

@group3 Parameter Block Functions
@normal
<f mgParamExists><nl>
<f mgParamGetStringAlloc><nl>
<f mgParamGetStringNthAlloc><nl>

@group3 Structure Functions
@normal
<f mgNewRecDb><nl>
<f mgWalkRecList><nl>

@group3 Texture Functions
@normal
<f mgIsTextureInPalette>

@group2 New Symbols
@normal
<m MPREFI_MOUSEUPZOOMOUT> for <f mgModelingPrefGetInteger><nl>

@group2 Fixes/Enhancements
@normal

Fixed <f mgMoreDetail>, <f mgLessDetail>, to return <e mgbool.MG_FALSE> properly when called
on empty database nodes.

Enhanced <f mgOpenDb> to set the initial fltIOn state correctly for nodes below <flt fltGroup>
animation nodes.

Enhanced <f mgWalk> and <f mgWalkEx> to function properly if you delete
(<f mgDelete>) the node currently being visited in the <p postAction> function.

Enhanced <f mgSetConstructEdgeCoords> to allow you to set either endpoint 
coordinate of a construction edge node without having to set both.

Enhanced <f mgGetConstructEdgeCoords> to allow you to get either endpoint 
coordinate of a construction edge node without having to get both.

Fixed <f mgSetTextureTexels> to function correctly (do nothing) when passed the same texels 
returned by <f mgGetTextureTexels>.

Fixed <f mgSelectList> to select edges correctly.

Fixed <f mgWalk> to walk single vertices correctly.

Fixed <f mgCloseDb> to return <e mgbool.MG_FALSE> properly when called in Creator on a database
that is currently open on the Creator desktop.

Fixed <f mgSetAttList> to return the correct number of attributes modified when 
trying to set "read-only" attributes, such as:<nl>
fltLpSequenceLength<nl>
fltVRgbMode<nl>
fltPolyRgbMode<nl>
fltMappingType<nl>
fltSwMaxMask<nl>
fltSwCount<nl>
fltMeshNumPrimitives<nl>
fltMeshNumVtx

Fixed <f mgSetAttList> to refresh the Creator graphics view and mark the database as modified
correctly when called from a plug-in or script in Creator for the Transformation record codes:<nl>
fltXmGeneral<nl>
fltXmHeader<nl>
fltXmPut<nl>
fltXmRotate<nl>
fltXmRotateEdge<nl>
fltXmScale<nl>
fltXmScaleToPoint<nl>
fltXmTranslate

Fixed <f mgIsTextureIndexInPalette> to return correct result when run in Creator in the case
where texture was not already loaded.

Fixed <f mgMostDetail>, <f mgLeastDetail>, <f mgMoreDetail> and <f mgLessDetail>
to fail properly when node is not a <flt fltHeader> node.

Corrected the OpenFlight API Reference page for <f mgGetAttBuf> to state that this function
is not available for Python.

Corrected the OpenFlight API Reference page for <f mgPromptDialogTexture> to show correct
usage for Python.

Corrected the OpenFlight Data Dictionary reference to show correct types for fields:<nl>
fltLineStyleId<nl>
fltLineStylePatternMask

@group1 v4.2
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.4. 

@group2 Visual Studio Compatibility
@normal
The OpenFlight API is distributed in three binary formats
for the Windows platform; Visual Studio 6 (VC6-Win32), Visual Studio 2005
(VC8-Win32) and Visual Studio 2005 (VC8-x64).  If you are developing plug-ins
for Creator v3.4 or later, you must use VC8-Win32 so your plug-ins are 
compatible with Creator.  If you are developing plug-ins for Creator v3.3 or 
earlier, you must use VC6-Win32. If you are developing stand-alone applications, 
you can choose any format.

@normal
The OpenFlight API installer for the Windows platform was consolidated for this
version to contain the binary files for all platforms.  When you install the
OpenFlight API on Windows, you can choose which platform you want or you can
choose to install them all.

@normal
Both of the VC8 versions of the OpenFlight API DLLs are dependent on 
VC80 CRT version 8.0.50727.4053.  The OpenFlight API installer automatically
installs the proper Microsoft Visual Studio 2005 (release) redistributable package if your 
computer does not already have it.  The debug version of the CRT should be installed on
your computer when you apply the proper patches/service packs to Visual Studio 2005.

@group2 OpenFlight API FAQ
@normal
A new section, <m FAQ>, was added to the OpenFlight API Reference that contains
answers to frequently asked questions about the OpenFlight API and OpenFlight Script.

@group2 Access to Creator Tools
@normal
The OpenFlight API now allows your plug-in tool or OpenFlight Script to execute tools
in the Creator modeler environment.  If you develop an editor plug-in tool, you can include
your tool in this mechanism (allow other plug-ins or scripts to execute your tool).  See
<f mgPluginToolSetDefaultParamBlock> for more information.

@group2 Using OpenFlight Script with your Data Dictionary
@normal
The record and field codes you define in your Data Dictionary are now accessible
in OpenFlight Script.  In the OpenFlight Script editor in Creator, the codes are
automatically made available to you when writing scripts there.  If you want to access
your Data Dictionary codes in your stand-alone scripts, you can use the updated <m ddbuild>
utility to generate a Python module containing your record and field codes.  Your 
stand-alone script, then, will import this module to gain access to your record
and field codes.

@group2 New Functions

@group3 Editor Context Functions
@normal
<f mgExecute><nl>

@group3 Extension Functions
@normal
<f mgExtensionMakeGUID><nl>

@group3 Geometry Functions
@normal
<f mgCoord3dProjectOnPlane><nl>

@group3 I/O Functions
@normal
<f mgSetDbModified><nl>

@group3 Parameter Block Functions
@normal
<f mgNewParamBlock><nl>
<f mgGetParamBlock><nl>
<f mgFreeParamBlock><nl>

<f mgParamAddInteger><nl>
<f mgParamAddDouble><nl>
<f mgParamAddDouble2><nl>
<f mgParamAddDouble3><nl>
<f mgParamAddFloat><nl>
<f mgParamAddBool><nl>
<f mgParamAddString><nl>

<f mgParamGetInteger><nl>
<f mgParamGetDouble><nl>
<f mgParamGetDouble2><nl>
<f mgParamGetDouble3><nl>
<f mgParamGetFloat><nl>
<f mgParamGetBool><nl>
<f mgParamGetString><nl>

<f mgParamGetIntegerNth><nl>
<f mgParamGetDoubleNth><nl>
<f mgParamGetDouble2Nth><nl>
<f mgParamGetDouble3Nth><nl>
<f mgParamGetFloatNth><nl>
<f mgParamGetBoolNth><nl>
<f mgParamGetStringNth><nl>

<f mgParamSet><nl>
<f mgParamSetInteger><nl>
<f mgParamSetDouble><nl>
<f mgParamSetDouble2><nl>
<f mgParamSetDouble3><nl>
<f mgParamSetFloat><nl>
<f mgParamSetBool><nl>
<f mgParamSetString><nl>

<f mgParamAppend><nl>
<f mgParamAppendInteger><nl>
<f mgParamAppendDouble><nl>
<f mgParamAppendDouble2><nl>
<f mgParamAppendDouble3><nl>
<f mgParamAppendFloat><nl>
<f mgParamAppendBool><nl>
<f mgParamAppendString><nl>

<f mgParamSetDimension><nl>
<f mgParamGetDimension><nl>
<f mgParamGetSize><nl>

<f mgParamSetDoubleMinGE><nl>
<f mgParamSetDoubleMinGT><nl>
<f mgParamSetDoubleMaxLE><nl>
<f mgParamSetDoubleMaxLT><nl>

<f mgParamSetIntegerMinGE><nl>
<f mgParamSetIntegerMinGT><nl>
<f mgParamSetIntegerMaxLE><nl>
<f mgParamSetIntegerMaxLT><nl>
<f mgParamSetEnumerant><nl>

@group3 Preference Functions
@normal
<f mgModelingPrefSetDouble><nl>
<f mgModelingPrefSetInteger><nl>

@group3 Tool Registration Functions
@normal
<f mgPluginToolSetDefaultParamBlock>

@group2 New Symbols
@normal
<e mgnotifierevent.MNOTIFY_DATABASEPRESAVE> for <f mgRegisterNotifier><nl>

@group2 New Tool Attributes for Editor Tools 
@normal
(see <f mgRegisterEditor>)

<m MTA_SCRIPTABLE><nl>

@group2 New in the OpenFlight Data Dictionary
@normal

The following fields were added to <flt fltPolygon> and <flt fltMesh> to 
provide access to the Creator Primary and Alternate Color indices
on polygon and mesh nodes:<nl>
fltPolyCreatorPrimeColor<nl>
fltPolyCreatorAltColor<nl>

The following field was added to <flt fltVertex> to 
provide access to the Creator Color index on vertex nodes<nl>
fltVCreatorColor<nl>

The following fields were added to <flt fltText> to provide access to the 
Creator Primary and Alternate Color indices on text nodes:<nl>
fltTextCreatorColor<nl>
fltTextCreatorAltColor<nl>

The following field was added to <flt fltLpAppearancePalette> to provide
access to the Creator Back Color index on light point
appearance palette records<nl>
fltLpCreatorBackColor<nl>

The following field was added to several node type records to provide
access to the comment text (an alternate to <f mgGetComment> and <f mgSetComment>)
on those node type records<nl>
fltComment<nl>

@group2 Fixes/Enhancements
@normal

Enhanced <f mgDelete> to delete tag-along extension records. Use <f mgGetExtRec>
to get a tag-along extension record attached to a node.

Fixed <f mgLightPointAnimationSequenceGet> to fail properly when node is not a 
light point animation palette node.

Fixed <f mgLightPointAnimationSequenceSet> to fail properly when node is not a 
light point animation palette node.

Fixed <f mgGetNextLightPointAnimation> to fail properly when node is not a 
light point animation palette node.

Fixed <f mgGetNextLightPointAppearance> to fail properly when node is not a 
light point appearance palette node.

Fixed <f mgShaderGetVertexProgramNth>, <f mgShaderGetFragmentProgramNth>,
<f mgShaderAddVertexProgram>, <f mgShaderAddFragmentProgram>, <f mgShaderSetVertexProgramNth>
and <f mgShaderSetFragmentProgramNth> to fail properly when node is not a shader palette node.

Fixed <f mgShaderGetVertexProgramNth>, <f mgShaderGetFragmentProgramNth>,
<f mgDeleteShader>
to fail properly if index negative.

Fixed <f mgDuplicate>, <f mgDuplicateEx> and <f mgDuplicateToDb> to copy
group bounding box records.

Fixed <f mgDuplicate>, <f mgDuplicateEx> and <f mgDuplicateToDb> to copy
switch mask names properly.

Fixed <f mgGetModelingMode> to return <flt fltVertex> in both vertex and
edge mode. For edge mode, use <f mgIsModelingModeEdge> to differentiate from
vertex mode.

Fixed <f mgSetCurrentMaterial> to return <e mgbool.MG_TRUE> properly when
current material is already set to the desired index.

Fixed <f mgSetCurrentTexture> to return <e mgbool.MG_TRUE> properly when
current texture is already set to the desired index.

@group1 v4.1.2
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.4. 

@normal
No new functions were added for this release.

@group2 Fixes/Enhancements
@normal

Fixed <f mgReadLightPointFile> and <f mgWriteLightPointFile> to include the
<fltf fltLpAppearancePalette.fltLpNoBackColor> attribute of the <flt fltLpAppearancePalette> palette
entries.

@group1 v4.1.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.4. 

@normal
No new functions were added for this release.

@group2 Fixes/Enhancements
@normal

Fixed crash in <f mgDuplicate> and <f mgDuplicateEx> when duplicated geometry contains
<flt fltMesh> nodes.

@group1 v4.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.4. 

@group2 64 bit support
@normal
Levels 1, 2 and 3 of the OpenFlight API were implemented on 64 bit operating systems 
(both Windows and Linux platforms).

@group2 Visual Studio Compatibility
@normal
The OpenFlight API is distributed in three binary formats
for the Windows platform; Visual Studio 6 (VC6-Win32), Visual Studio 2005
(VC8-Win32) and Visual Studio 2005 (VC8-x64).  Only one distribution can be
installed at one time on the same computer.  If you are developing plug-ins
for Creator v3.4 or later, you must use VC8-Win32 so your plug-ins are 
compatible with Creator.  If you are developing plug-ins for Creator v3.3 or 
earlier, you must use VC6-Win32. If you are developing stand-alone applications, 
you can choose any format.

@normal
In order to support both 32 and 64 bit versions of the OpenFlight API, the signature 
for <f mgMalloc> was changed (cosmetically).  Its single parameter was changed from
type <t unsigned int> to type <t mgsize_t>.
For 32 bit versions of the OpenFlight API, this type is unsigned 32 bit integer.
For 64 bit versions of the OpenFlight API, this type is unsigned 64 bit integer.

Note that this will not affect your 32 bit applications or plug-ins.  Since the 
underlying type of this parameter has not changed (for 32 bit versions) your existing
applications and plug-ins will continue to work without recompilation.  When you do
recompile, your code will require no changes.

@group2 Debug Dynamic Link Libraries
@normal
Starting with this version, both release and debug versions of the dynamic
link libraries are distributed with the OpenFlight API.

@group2 New Data Types
@normal
<t mgsize_t><nl>
<t mglistactivatereason><nl>
<t mglistactivatecallbackrec><nl>

@group2 New Functions

@group3 Attribute Functions
@normal
<f mgGetConvexHull><nl>
<f mgFreeConvexHull><nl>
<f mgConvexHullGetTriangleCount><nl>
<f mgConvexHullGetTriangleNth><nl>
<f mgNewConvexHullBuilder><nl>
<f mgFreeConvexHullBuilder><nl>
<f mgConvexHullBuilderExpandCoord3d><nl>
<f mgConvexHullBuilderClose><nl>
<f mgGetVtxColorName><nl>
<f mgSetVtxColorName><nl>

@group3 I/O Functions
@normal
<f mgGetAbsoluteFilename><nl>

@group3 Preference Functions
@normal
<f mgPluginPrefDelete><nl>
<f mgPluginToolPrefDelete><nl>
<f mgSetFreezeLODCentersFlag><nl>

@group3 Select List Functions
@normal
<f mgSelectOneEx><nl>

@group3 Tab Ruler Functions
@normal
<f mgNewTabRuler><nl>
<f mgFreeTabRuler><nl>
<f mgTabRulerSetOptions><nl>
<f mgTabRulerRangeDrawCallback><nl>
<f mgTabRulerRangeMouseCallback><nl>
<f mgTabRulerSetGuiCallback><nl>
<f mgTabRulerSetMouseCallback><nl>
<f mgTabRulerGetTabCount><nl>
<f mgTabRulerGetTabPosition><nl>
<f mgTabRulerSetTabPosition><nl>
<f mgTabRulerSetTabFrozen><nl>
<f mgTabRulerNewTab><nl>
<f mgTabRulerDeleteTab><nl>
<f mgTabRulerGetSelectedTab><nl>
<f mgTabRulerSelectTab><nl>

@group3 Texture Functions
@normal
<f mgPurgeTextures> (previously undocumented, now fully supported)<nl>
<f mgReadImageInfo> (added OpenFlight Script version)<nl>
<f mgReadImageGeoInfo> (added OpenFlight Script version)<nl>
<f mgReadImageHeader> (added OpenFlight Script version)<nl>

@group2 New Symbols
@normal
<m MSEL_ALLOWRECURSIVE> for <f mgSelectOneEx><nl>

<e mgnotifierevent.MNOTIFY_EXTENSIONCHANGED> for <f mgRegisterNotifier><nl>

@group2 Fixes/Enhancements
@normal

List controls in your plug-in dialogs can now distinguish between "click" 
and "double click" selection.  See <t mglistactivatecallbackrec> for more information.

Enhanced <f mgDelete> to free texture attribute records returned by <f mgReadImageAttributes>.

Fixed <f mgExit> to free all memory allocated by the OpenFlight API between the
<f mgInit> and <f mgExit> calls.

Enhanced <f mgGuiSetToolTip> to allow empty string to clear the control tool tip.

Enhanced <f mgSetPolyColorName> and <f mgSetPolyAltColorName> to clear the color name
given a NULL or empty string.

Enhanced 
<f mgGetPlane>,
<f mgGetCoord3d>,
<f mgGetCoord3f>,
<f mgGetMatTextureLayer>,
<f mgGetNormColor>,
<f mgGetVector>,
<f mgGetVectord>, and
<f mgGetPolyNormal>
to accept one or more (but not all) NULL addresses in order to specify which components you want to receive.

Fixed <f mgExportDb> to function correctly for <m MEFV_1630>.

Fixed <f mgUpdateTextureMapping> to return <e mgbool.MG_TRUE> properly when mapping is updated.

Fixed <f mgSetColorIndex> to only set colors on valid palette indices.

Fixed <f mgMeshSetVtxColor> to fail properly if color or intensity values out of range.

Fixed <f mgCoord2dAngle> to measure angle between coincident coordinates properly.

Fixed <f mgCoord3dAngle> to measure angle between coincident coordinates properly.

Fixed <f mgAttach> to fail when node is already attached.

Fixed <f mgDetach> to fail when node is already detached.

Fixed <f mgDetach> to properly unlink siblings when used on a transformation record.

Fixed <f mgDelete> to work properly on a detached transformation record.

Fixed <f mgReference> to fail when node already references another node.

Fixed <f mgIsDbUntitled> to work properly on a detached transformation record.

Fixed <f mgNewColorName> to fail for NULL or empty string name.

Fixed <f mgGetTexturePosition> to fail if texture does not refer to a valid palette entry.

Fixed <f mgReplaceTexture> to fail if texture does not refer to a valid palette entry.

Fixed <f mgMoveTexture> to fail if source texture does not refer to a valid palette entry.

Fixed <f mgReadTexturePalette> to close file handle when done reading texture palette file.

Fixed <f mgSendMessage> to return <e mgbool.MG_TRUE> properly when messages are enabled.

Fixed <f mgSendMessage> to handle NULL message string properly.

Fixed <f mgAddSwitchMask> to fail properly when node is not a switch node.

Fixed <f mgDeleteSwitchMask> to fail properly when node is not a switch node 
or mask number parameter does not specify a valid mask of the switch node.

Fixed <f mgGetSwitchBit> to fail properly when node is not a switch node,
mask number parameter does not specify a valid mask of the switch node,
bit number parameter does not specify a valid bit of the mask or
on parameter is not a valid address.

Fixed <f mgGetSwitchMaskCount> to fail properly when node is not a switch node.

Fixed <f mgGetSwitchMaskName> to fail properly when node is not a switch node
or mask number parameter does not specify a valid mask of the switch node.

Fixed <f mgGetSwitchMaskNo> to fail properly when node is not a switch node or 
mask number parameter is not a valid address.

Fixed <f mgInitSwitchMask> to fail properly when node is not a switch node or 
mask number parameter does not specify a valid mask of the switch node.

Fixed <f mgSetSwitchBit> to fail properly when node is not a switch node,
mask number parameter does not specify a valid mask of the switch node or
bit number parameter does not specify a valid bit of the mask.

Fixed <f mgSetSwitchMaskName> to fail properly when node is not a switch node
or mask number parameter does not specify a valid mask of the switch node.

Fixed 
<f mgMatrixSetXAxis>, 
<f mgMatrixSetYAxis>, 
<f mgMatrixSetZAxis>, 
<f mgMatrixSetTranslation>,
<f mgMatrixFormReflectX>,
<f mgMatrixFormReflectY>,
<f mgMatrixFormReflectZ>,
<f mgMatrixFormReflect>,
<f mgMatrixFormPitchUp90>,
<f mgMatrixFormPitchDown90>,
<f mgMatrixFormRollLeft90>,
<f mgMatrixFormRollRight90>,
<f mgMatrixFormYawLeft90>,
<f mgMatrixFormYawRight90>,
<f mgMatrixReflectX>,
<f mgMatrixReflectY>,
<f mgMatrixReflectZ>,
<f mgMatrixReflect>,
<f mgMatrixPitchDown90>,
<f mgMatrixPitchUp90>,
<f mgMatrixRollLeft90>,
<f mgMatrixRollRight90>,
<f mgMatrixYawLeft90>,
<f mgMatrixYawRight90>,
<f mgMatrixCompose>,
<f mgMatrixGetTranslation>,
<f mgMatrixGetXAxis>,
<f mgMatrixGetYAxis>,
<f mgMatrixGetZAxis>,
<f mgMatrixFormNormal>,
<f mgMatrixTranspose>,
<f mgMatrixMultiply>,
and <f mgMatrixCopy> to fail if NULL parameters passed in.

Fixed 
<f mgFreeMatrixStack>,
<f mgMatrixStackPush>,
<f mgMatrixStackPop>,
<f mgMatrixStackLoadIdentity>,
<f mgMatrixStackLoadMatrix>,
<f mgMatrixStackGetMatrix>,
<f mgMatrixStackIsIdentity>,
<f mgMatrixStackMultiply>,
<f mgMatrixStackScale>,
<f mgMatrixStackRotate>,
<f mgMatrixStackRotateX>,
<f mgMatrixStackRotateY>,
<f mgMatrixStackRotateZ>,
and <f mgMatrixStackTranslate> to fail if NULL parameters passed in.

Fixed <f mgMatrixFormXYZToUV> to use the correct texture layer.

Fixed <f mgMatrixInvert> to fail properly when matrix or result matrix are NULL.

Fixed <f mgMeshGetVtxOffset> to return correct offset for MMESH_VTXCOLORRGB when 
color RGB values not really present.

Fixed <f mgMeshPrimitiveGetVtxIndexArray> to fail properly when index array is NULL.

Fixed
<f mgMeshSetVtxMask>,
<f mgMeshSetVtxCoord>,
<f mgMeshSetVtxColor>,
<f mgMeshSetVtxColorRGBA>,
<f mgMeshSetVtxColorRGB>,
<f mgMeshSetVtxColorAlpha>,
<f mgMeshSetVtxNormal>,
<f mgMeshSetVtxUV>,
<f mgMeshSetVtxNormal>,
<f mgMeshSetVtxNormal>, and
<f mgMeshSetVtxColor> to refresh the Creator graphics view and mark the database as modified
when called from a plug-in or script in Creator.

Fixed <f mgMeshGetVtxCoord> to fail properly if all three output coordinate component addresses are NULL.

Fixed <f mgMeshGetVtxColor> to fail properly if both output addresses are NULL.

Fixed <f mgMeshGetVtxColorRGB> to fail properly if all three output addresses are NULL.

Fixed <f mgMeshGetVtxColorRGBA> to fail properly if all four output addresses are NULL.

Fixed <f mgMeshGetVtxColorAlpha> to fail properly if output alpha address is NULL.

Fixed <f mgMeshGetVtxNormal> to fail properly if all three output normal component addresses are NULL.

Fixed <f mgMeshGetVtxUV> to fail properly if both output addresses are NULL.

Fixed <f mgMeshSetVtxMask> and <f mgMeshCreateVtxPool> to fail properly if 
both MMESH_VTXCOLOR and MMESH_VTXCOLORRGB are specified in the vertex mask.

Fixed <f mgSetName> to fail properly if called to rename a <flt fltVertex> node
or if the name specified is empty.

Fixed <f mgGetPolyNormal> to fail properly if all three output normal component addresses are NULL.

Fixed <f mgGetVtxCoord> to fail properly if all three output coordinate addresses are NULL.

Fixed <f mgGetVtxNormal> to fail properly if all three output normal component addresses are NULL.

Fixed <f mgGetPolyColorRGB> to fail properly if all three output normal component addresses are NULL.

Fixed <f mgGetVtxColorRGB> to fail properly if all three output color component addresses are NULL.

Fixed <f mgGetVtxColorRGBA> to fail properly if all four output color component addresses are NULL.

Fixed <f mgPtrArrayBSearch> to handle NULL compare function parameter properly,

Fixed <f mgPtrArrayBSearch> to fail properly if output position parameter is NULL.

Fixed <f mgDeleteSound> to return <e mgbool.MG_TRUE> properly when sound is deleted.

Fixed <f mgDeleteSound> to fail properly when index is -1.

Fixed
<f mgGetSoundCount>,
<f mgDeleteSound>,
<f mgGetFirstSound>,
<f mgNameOfSound>,
<f mgIndexOfSound>,
<f mgGetCurrentSound>, and
<f mgSetCurrentSound>
to fail properly if db is not a <flt fltHeader> node.

Fixed
<f mgGetLightSourceCount>,
<f mgDeleteLightSource>,
<f mgIndexOfLightSource>,
<f mgNameOfLightSource>,
<f mgReadLightSourceFile>,
<f mgGetCurrentLightSource>, and
<f mgSetCurrentLightSource>
to fail properly if db is not a <flt fltHeader> node.

Fixed <f mgReadMaterialFile>, <f mgWriteMaterialFile> and <f mgWriteMaterialFileVersion>
to fail properly if db is not a <flt fltHeader> node.

Fixed <f mgWriteSoundFile> to fail properly if db is not a <flt fltHeader> node.

Fixed <f mgReadColorPalette> and <f mgWriteColorPalette> to fail properly if db is 
not a <flt fltHeader> node.

Fixed
<f mgSetColorIndex>,
<f mgNewColorName>, 
<f mgDeleteColorName>,
<f mgSetCurrentColorName>,
<f mgGetCurrentColorName>,
<f mgGetPolyColorName>, 
<f mgGetPolyAltColorName>,
<f mgGetNextColorName>, and
<f mgGetColorNameList>
to fail properly if db is not a <flt fltHeader> node.

Fixed <f mgGetNextColorName> and <f mgGetColorNameList> to only get 
color names for valid palette indices.

Fixed <f mgDeleteColorName> to return <e mgbool.MG_TRUE> properly when name is deleted.

Fixed <f mgRGB2Index> to fail properly if db is not a <flt fltHeader> node.

Fixed
<f mgSetColorIndex>,
<f mgRGB2Index>,
<f mgMeshSetVtxColorRGBA>,
<f mgMeshSetVtxColorRGB>,
<f mgMeshSetVtxColorAlpha>,
<f mgSetPolyColorRGB>, and 
<f mgSetPolyAltColorRGB>
to fail properly if color values are outside valid range (0..255).

Fixed
<f mgSetPolyColorName>,
<f mgSetPolyAltColorName>,
<f mgGetPolyColorName>, and
<f mgGetPolyAltColorName>
to work properly on <flt fltMesh> nodes.

Fixed <f mgGetAttList> to handle NULL attribute addresses properly.

Fixed <f mgDeleteShader> to work properly.

Corrected the reference page for <f mgWalkGetMatrix> to show the correct Python signature.

Now that the OpenFlight Script version of <f mgReadImageInfo> has been implemented,
the following functions can be used in OpenFlight Script correctly:
<f mgGetTextureWidth>,
<f mgGetTextureHeight>,
<f mgGetTextureType>,
<f mgGetTextureSampleSize>,
<f mgGetTextureTiledFlag>,
<f mgGetTextureMinMax>,
<f mgHasTextureTransparentValue>,
<f mgGetTextureTransparentValue>, and
<f mgGetTextureSignedFlag>.

Now that the OpenFlight Script version of <f mgReadImageGeoInfo> has been implemented,
the following functions can be used in OpenFlight Script correctly:
<f mgGetTextureGeoType>,
<f mgGetTextureGeoProjection>,
<f mgGetTextureGeoEarthModel>,
<f mgGetTextureGeoUTMZone>,
<f mgGetTextureGeoUTMHemisphere>,
<f mgGetTextureGeoImageOrigin>,
<f mgGetTextureGeoNumCtlPts>, and
<f mgGetTextureGeoCtlPt>.

@group2 Constant Qualifiers in Function Declarations
@normal

The signatures for several function calls have been modified to include the
C language 'const' qualifier where appropriate.  In most instances this will 
not affect your existing code.  Following is a list of the affected functions:

<f mgShowHelpContext><nl>
<f mgGuiSetHelpContext><nl>

@group2 Signed vs Unsigned integer Function Declarations
@normal

The signatures for the following function calls have been modified to include the
C language 'unsigned' qualifier for integer type parameters where appropriate.  
In most instances this will not affect your existing code.  Following is a list 
of the affected functions:

<f mgDuplicateEx><nl>
<f mgDuplicateToDbEx><nl>
<f mgWalk><nl>
<f mgWalkEx><nl>
<f mgFind><nl>
<f mgFindEx><nl>
<f mgMessageDialog><nl>

@group1 v4.0
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.4. 

@group2 Visual Studio Compatibility
@normal
This version of the OpenFlight API is distributed in two binary formats
for the Windows platform; Visual Studio 6 (VC6-Win32) and Visual Studio 2005
(VC8-Win32).  Both distributions cannot be installed simultaneously on the same computer.
If you are developing plug-ins for Creator v3.4 or later, you must use VC8 so your 
plug-ins are compatible with Creator.  If you are developing plug-ins for Creator v3.3 or 
earlier, you must use VC6-Win32.  If you are developing stand-alone applications, you can 
choose either format.

@group2 New Functions

@group3 Extension Functions
@normal
<f mgExtensionSiteAdd><nl>
<f mgExtensionSiteGetName><nl>
<f mgExtensionSiteSetName><nl>

<f mgExtensionFieldAdd><nl>
<f mgExtensionFieldGetName><nl>
<f mgExtensionFieldSetName><nl>
<f mgExtensionFieldGetAttach><nl>
<f mgExtensionFieldSetAttach><nl>
<f mgExtensionFieldGetType><nl>
<f mgExtensionFieldSetType><nl>

<f mgExtensionFieldGetInteger><nl>
<f mgExtensionFieldSetInteger><nl>
<f mgExtensionFieldGetDouble><nl>
<f mgExtensionFieldSetDouble><nl>
<f mgExtensionFieldGetFloat><nl>
<f mgExtensionFieldSetFloat><nl>
<f mgExtensionFieldGetBool><nl>
<f mgExtensionFieldSetBool><nl>
<f mgExtensionFieldGetString><nl>
<f mgExtensionFieldSetString><nl>
<f mgExtensionFieldGetXMLString><nl>
<f mgExtensionFieldSetXMLString><nl>

<f mgExtensionFieldDelete><nl>
<f mgExtensionFieldDefined><nl>

@group3 Geometry Functions
@normal
<f mgVectordZero><nl>

@group3 I/O Functions
@normal
<f mgIsDbOnDesktop><nl>
<f mgIsFileOnDesktop><nl>
<f mgGetDbOnDesktop><nl>

@group3 Projection Functions
@normal
<f mgNewProjection><nl>
<f mgFreeProjection><nl>
<f mgProjectionConvertXYZtoLLE><nl>
<f mgProjectionConvertLLEtoXYZ><nl>

@group3 Texture Functions
@normal
<f mgSelectTextureIndex><nl>
<f mgDeselectTextureIndex><nl>
<f mgDeselectAllTextures><nl>
<f mgGetFirstSelectedTexture><nl>
<f mgGetNextSelectedTexture><nl>
<f mgGetSelectedTextureCount><nl>
<f mgIsTextureIndexSelected><nl>

@group3 Tool Activation Functions
@normal
<f mgSetModelingParent><nl>
<f mgSetModelingModeEdge><nl>
<f mgIsModelingModeEdge><nl>

@group2 New Symbols
@normal
<e mgnotifierevent.MNOTIFY_TEXTURESELECTCHANGED> for <f mgRegisterNotifier><nl>
<m MEFV_1640> for <f mgExportDb><nl>
<e mgtagtype.MTYPE_XML> for <t mgtagtype><nl>

@group2 Fixes
@normal
Fixed <f mgReadMaterialFile>, <f mgWriteMaterialFile> and <f mgWriteMaterialFileVersion>
to return <e mgbool.MG_TRUE> only when successful.


@group1 v3.5.2
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.3. 

@normal
The VC8 versions of the OpenFlight API DLLs were corrected to contain 
the proper embedded manifests.  When the OpenFlight API DLLs are loaded 
into memory, the operating system DLL loader uses the embedded manifests 
to resolve dependencies for the OpenFlight API DLLs.  This fix will allow 
the OpenFlight API DLLs to be used in both Debug and Release versions of 
your stand-alone applications. This fix will also enable the VC8 versions 
to be used in OpenFlight Script (Python).

@group1 v3.5.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.3. 

@normal
No new functions were added for this release.

@group1 v3.5
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.3. 

@group2 Visual Studio Compatibility
@normal
This version of the OpenFlight API is distributed in two binary formats
for the Windows platform; Visual Studio 6 (VC6-Win32) and Visual Studio 2005
(VC8-Win32).  Both distributions cannot be installed simultaneously on the same computer.
If you are developing plug-ins for Creator v3.4 or later, you must use VC8 so your 
plug-ins are compatible with Creator.  If you are developing plug-ins for Creator v3.3 or 
earlier, you must use VC6-Win32.  If you are developing stand-alone applications, you can 
choose either VC6-Win32 or VC8-Win32.
either format.

@group2 OpenFlight Script
@normal
The OpenFlight Script scripting language was introduced.  Based on Python, 
OpenFlight Scripts can be run in either the stand-alone program environment 
or in Creator.  See the <i OpenFlight API Developer Guide> and <i Creator Help>,
respectively, for more information.

@normal
To run stand-alone OpenFlight Scripts, a Python 2.5.X installation is required.
No Python installation is required to run OpenFlight Scripts in Creator. 

@group2 OpenFlight API Installation Root
@normal
The OpenFlight API is now installed into the Presagis Common Directory Organization.
The root of this directory structure is:
<q c\:/presagis>

@normal
The directory structure below this root folder has not changed from previous
installations.  The names of the environment variables created by the installer
have changed to <m PRESAGIS_OPENFLIGHT_API> and <m PRESAGIS_OPENFLIGHT_API_version>,
where <m version> specifies the major and minor version numbers of the distribution. 
For OpenFlight API 3.5 the environment variable is <m PRESAGIS_OPENFLIGHT_API_3_5>. 
The values for both these variables are the same.  They specify the root of the
OpenFlight API installation. 

@group2 New Data Types
@normal
<t mgnodeexpression><nl>
<t mgnodeexpressionoperator><nl>

@group2 New Functions

@group3 Color Functions
@normal
<f mgGetColorNameList><nl>

@group3 Geometry Functions
@normal
<f mgCoord2dLerp><nl>
<f mgCoord3dLerp><nl>
<f mgVectordLerp><nl>

@group3 Structure Functions
@normal
<f mgFind><nl>
<f mgFindEx><nl>
<f mgEvaluateAsBool><nl>
<f mgFreeNodeExpression><nl>
<f mgNewNodeExpressionCallback><nl>
<f mgNewNodeExpressionDouble><nl>
<f mgNewNodeExpressionGetAtt><nl>
<f mgNewNodeExpressionInteger><nl>
<f mgNewNodeExpressionOperator><nl>
<f mgnodeexpressionfunc><nl>
<f mgNodeExpressionLoadFromString><nl>
<f mgNodeExpressionSetLeft><nl>
<f mgNodeExpressionSetRight><nl>

@group3 Select List Functions
@normal
<f mgIterateRecList><nl>
<f mgAppendRecList><nl>
<f mgNewRecList><nl>

@group3 Text Functions
@normal
<f mgTextAppendString><nl>
<f mgTextGetSelectionRange><nl>

@group3 General Controls
@normal
<f mgControlSubclass><nl>

@group3 Dialog Functions
@normal
<f mgDialogSubclass><nl>

@group3 Editor Context Functions
@normal
<f mgNewEditorContext><nl>

@group2 New Symbols
@normal

<m MPREFI_SHADEWIRE> for <f mgModelingPrefGetInteger><nl>
<e mgpaletteid.MPID_SHADERPALETTE> for <f mgShowPalette><nl>

@group2 New Menu Locations for Editor and Viewer Tools 
@normal
(see <m MTA_MENULOCATION>)

@normal
<m MMENU_SCRIPTS><nl>

@group1 v3.4.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.3. 

@normal
The following functions were inadvertently omitted from the OpenFlight API 
3.4 distribution. They are included with this version of the OpenFlight API.<nl>
<f mgWriteMaterialFileVersion><nl>
<f mgReadLightSourceFile><nl>

@group2 Fixes
@normal
Fixed <f mgListAddItemData> to attach user data to list item properly.

@group1 v3.4
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.3. 

@group2 Visual Studio Compatibility
@normal
This version of the OpenFlight API is distributed in two binary formats
for the Windows platform; Visual Studio 6 (VC6-Win32) and Visual Studio 2005
(VC8-Win32).  Both distributions cannot be installed simultaneously on the same computer.
If you are developing plug-ins for Creator v3.4 or later, you must use VC8 so your 
plug-ins are compatible with Creator.  If you are developing plug-ins for Creator v3.3 or 
earlier, you must use VC6-Win32.  If you are developing stand-alone applications, you can 
choose either format.

@normal
If you are using VC8, you must link your stand-alone application with the
Release versions of the MicroSoft C Runtime libraries (even in Debug configurations).
This is necessary because in VC8, it is recommended NOT to mix Debug and Release
versions of the C Runtime libraries.  Since the OpenFlight API DLLs link against
the Release versions, so should your application.  In Visual Studio, open 
the <m Project Properties> window, select the <m C/C++> tab and then select the 
<m Code Generation> category.  For <m Runtime Library> field, select 
<m Multithreaded DLL> (/Md) for both Win32 Debug and Release configurations.


@group2 Extended Material Palette Entries
@normal
A new kind of material entry has been introduced.  A material palette can now be
composed of either old (standard) or new (extended) material entries (or a mixture
of both kinds).  This new extended material entry is composed of several optional 
properties.  These properties are listed below.  This change to the material palette
affects the format of material palette files saved to disk by <f mgWriteMaterialFile>.  
While <f mgWriteMaterialFile> now writes the "new" material palette file format,
<f mgWriteMaterialFileVersion> was introduced to write either the "old" or "new" 
format.  Similarly, when saving a material palette file in Creator, you can
choose to write the "old" or "new" format.  Note that <f mgReadMaterialFile>
will read either the "old" or "new" material palette file format.

@group3 Material Palette Nodes
@normal
The following records were added to <flt fltIMaterial><nl>
<flt fltAmbientEx><nl>
<flt fltDiffuseEx><nl>
<flt fltSpecularEx><nl>
<flt fltEmissiveEx><nl>
<flt fltAlphaEx><nl>
<flt fltBumpMapEx><nl>
<flt fltNormalMapEx><nl>
<flt fltLightMapEx><nl>
<flt fltShadowMapEx><nl>
<flt fltReflectionMapEx><nl>

@group2 New Functions

@group3 Attribute Functions
@normal
<f mgGetMatTextureLayer><nl>
<f mgSetMatTextureLayer><nl>
<f mgSetNameUnique><nl>
<f mgSetPolyCurrentColor><nl>
<f mgSetPolyCurrentAltColor><nl>
<f mgSetPolyCurrentMaterial><nl>
<f mgSetPolyCurrentShader><nl>
<f mgSetPolyCurrentTexture><nl>
<f mgSetPolyCurrentTextureMapping><nl>

@group3 Eyepoint Functions
@normal
<f mgGetSwitchDistance><nl>
<f mgSetSwitchDistance><nl>

@group3 Light Source Functions
@normal
<f mgReadLightSourceFile><nl>

@group3 Material Functions
@normal
<f mgWriteMaterialFileVersion><nl>

@group3 Select List Functions
@normal
<f mgIsRecInList><nl>

@group3 Tool Registration Functions
@normal
<f mgGetModulePath>

@group2 New Symbols
@normal
<m MEFV_1630> for <f mgExportDb> and <f mgWriteMaterialFileVersion><nl>
<m MEFV_1620> for <f mgExportDb> and <f mgWriteMaterialFileVersion><nl>

For <f mgGraphicsViewSettingGetInteger> and <f mgGraphicsViewSettingSetInteger>:<nl>
<m MGVI_SKYCOLOR><nl>

<e mgnotifierevent.MNOTIFY_DESKTOPINIT> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_DESKTOPEXIT> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_DATABASEOPENED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_DATABASESAVED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_NODECHANGED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_NODEDELETED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_NODECREATED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_NODEREPARENTED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_COLORPALETTECHANGED> for <f mgRegisterPaletteNotifier><nl>
<e mgnotifierevent.MNOTIFY_TEXTUREPALETTECHANGED> for <f mgRegisterPaletteNotifier><nl>
<e mgnotifierevent.MNOTIFY_MATERIALPALETTECHANGED> for <f mgRegisterPaletteNotifier><nl>
<e mgnotifierevent.MNOTIFY_TEXTUREMAPPINGPALETTECHANGED> for <f mgRegisterPaletteNotifier><nl>
<e mgnotifierevent.MNOTIFY_LIGHTPOINTAPPEARANCEPALETTECHANGED> for <f mgRegisterPaletteNotifier><nl>
<e mgnotifierevent.MNOTIFY_LIGHTPOINTANIMATIONPALETTECHANGED> for <f mgRegisterPaletteNotifier><nl>
<e mgnotifierevent.MNOTIFY_SHADERPALETTECHANGED> for <f mgRegisterPaletteNotifier><nl>
<e mgnotifierevent.MNOTIFY_SOUNDPALETTECHANGED> for <f mgRegisterPaletteNotifier><nl>
<e mgnotifierevent.MNOTIFY_LIGHTSOURCEPALETTECHANGED> for <f mgRegisterPaletteNotifier><nl>
<e mgnotifierevent.MNOTIFY_SWITCHDISTANCECHANGED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_TIMEOFDAYCHANGED> for <f mgRegisterNotifier><nl>

@group2 New in the OpenFlight Data Dictionary
@normal

The following fields were added to <flt fltIMaterial>:<nl>
fltMatType<nl>
fltMatShadeModel<nl>

@group1 v3.3
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.2. 

@normal
Levels 1, 2 and 3 of the API were implemented on the Linux platform.

@group2 New Functions

@group3 General Controls
@normal
<f mgSetFocus><nl>

@group3 Preference Functions
@normal
<f mgPluginPrefGetBool><nl>
<f mgPluginPrefSetBool><nl>
<f mgPluginToolPrefGetBool><nl>
<f mgPluginToolPrefSetBool><nl>

@group2 New Symbols
@normal

For <f mgGraphicsViewSettingGetInteger> and <f mgGraphicsViewSettingSetInteger>:<nl>
<m MGVI_XRAYMODE><nl>
<m MGVI_DYNAMICBILLBOARDS><nl>
<m MGVI_DYNAMICTEXTURE><nl>
<m MGVI_DYNAMICWIREFRAME><nl>

@group1 v3.2.2
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.2.

@normal
Significant improvements were made in this distribution in the following areas:<nl>
Memory leaks fixed relating to Transformation nodes.<nl>
OpenFlight extensions for palette nodes.<nl>
UNC file name handling.<nl>

@group2 New Symbols
@normal
<e mgnotifierevent.MNOTIFY_LIGHTPOINTPALETTEIZED> for <f mgRegisterNotifier><nl>

@group1 v3.2.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.2.

@normal
The OpenFlight API Reference distributed with OpenFlight API 3.2 was not the 
correct version.  The correct version has been included in this distribution and has
been updated accordingly with new functions 
for 3.2.1.

@group2 New Functions
@group3 Structure Functions
@normal
<f mgIsXformEmpty><nl>

@group1 v3.2
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.2. 

@group2 Constant Qualifiers in Function Declarations
@normal
The signatures for several function calls have been modified to include the
C language 'const' qualifier where appropriate.  In most instances this will 
not affect your existing code.  Following is a list of the affected functions:

<f mgGetRecByName><nl>
<f mgSetName><nl>
<f mgSetTextString><nl>
<f mgSetComment><nl>
<f mgSetSwitchMaskName><nl>

<f mgGuiPutProperty><nl>
<f mgGuiGetProperty><nl>
<f mgGuiDeleteProperty><nl>

<f mgRecPutProperty><nl>
<f mgRecGetProperty><nl>
<f mgRecDeleteProperty><nl>

<f mgPluginToolPrefGetString><nl>

<f mgEditorPutProperty><nl>
<f mgEditorGetProperty><nl>
<f mgEditorDeleteProperty><nl>
<f mgEditorSetPrompt><nl>
<f mgEditorAddUndo><nl>
<f mgEditorAppendUndo><nl>
<f mgEditorAddUndoForCreate><nl>
<f mgEditorAppendUndoForCreate><nl>
<f mgEditorAddUndoForDelete><nl>
<f mgEditorAppendUndoForDelete><nl>
<f mgEditorAddUndoForMove><nl>
<f mgEditorAppendUndoForMove><nl>

<f mgPluginPutProperty><nl>
<f mgPluginGetProperty><nl>
<f mgPluginDeleteProperty><nl>
<f mgPluginToolPutProperty><nl>
<f mgPluginToolGetProperty><nl>
<f mgPluginToolDeleteProperty><nl>

<f mgNewShader><nl>
<f mgIndexOfShader><nl>
<f mgDeleteShader><nl>

<f mgNewLightPointAppearance><nl>
<f mgIndexOfLightPointAppearance><nl>
<f mgNewLightPointAnimation><nl>
<f mgIndexOfLightPointAnimation><nl>
<f mgReadLightPointFile><nl>
<f mgWriteLightPointFile><nl>

<f mgNewTextureMapping><nl>
<f mgIndexOfTextureMapping><nl>
<f mgDeleteTextureMappingByName><nl>
<f mgReadTextureMappingFile><nl>
<f mgWriteTextureMappingFile><nl>

<f mgNewMaterial><nl>
<f mgIndexOfMaterial><nl>
<f mgDeleteMaterialByName><nl>
<f mgReadMaterialFile><nl>
<f mgWriteMaterialFile><nl>

<f mgNewColorName><nl>
<f mgGetColorIndexByName><nl>
<f mgDeleteColorName><nl>
<f mgReadColorPalette><nl>
<f mgWriteColorPalette><nl>
<f mgWriteDefaultColorPalette><nl>
<f mgSetCurrentColorName><nl>
<f mgSetPolyColorName><nl>
<f mgSetPolyAltColorName><nl>

<f mgSendMessage><nl>
<f mgSendStatus><nl>
<f mgSendWarning><nl>
<f mgSendError><nl>

<f mgIsDb><nl>
<f mgNewDb><nl>
<f mgOpenDb><nl>
<f mgSaveAsDb><nl>
<f mgExportDb><nl>

@group2 New Data Types
@normal
<t mgboxd><nl>

@group2 New Functions

@group3 Attribute Functions
@normal
<f mgGetBounds><nl>
<f mgGetBoundsForRecList><nl>
<f mgGetBoundsForSelect><nl>
<f mgIsPolyCoplanar><nl>

@group3 List Controls
@normal
<f mgListAddItemData><nl>
<f mgListAppendItemData><nl>
<f mgListSetItemDataAtPos><nl>
<f mgListGetItemDataAtPos><nl>

@group3 Matrix Functions
@normal 
<f mgMatrixFormXYZToUV><nl>

@group3 Geometry Functions
@normal
<f mgMakePlaned><nl>
<f mgMakeBox><nl>
<f mgBoxGetXSize><nl>
<f mgBoxGetYSize><nl>
<f mgBoxGetZSize><nl>
<f mgBoxGetDiagonalSize><nl>
<f mgBoxGetCenter><nl>
<f mgBoxGetCenterBottom><nl>
<f mgBoxExpandCoord3d><nl>
<f mgBoxExpandBox><nl>
<f mgBoxContainsCoord3d><nl>
<f mgBoxContainsBox><nl>
<f mgBoxIntersectsBox><nl>

@group3 GL Controls
@normal
<f mgDrawControlNow><nl>
  
@group3 Graphics View Functions
@normal
<f mgFitOnNode><nl>
<f mgFitOnGrid><nl>
<f mgFitOnRecList><nl>
<f mgFitOnSelect><nl>
<f mgResetView><nl>
<f mgGraphicsViewSettingGetMatrix><nl>
<f mgGraphicsViewSettingSetMatrix><nl>

@group3 List Controls
@normal
<f mgListAddItemData><nl>
<f mgListAppendItemData><nl>
<f mgListSetItemDataAtPos><nl>
<f mgListGetItemDataAtPos><nl>

@group3 Matrix Functions
@normal 
<f mgMatrixFormXYZToUV><nl>

@group2 New Symbols
@normal

For <f mgResourceGetPixmap>:<nl>
<m MPIXMAP_NEWFILE><nl>
<m MPIXMAP_OPENFILE><nl>
<m MPIXMAP_SAVEFILE><nl>
<m MPIXMAP_CUT><nl>
<m MPIXMAP_COPY><nl>
<m MPIXMAP_PASTE><nl>
<m MPIXMAP_DELETE><nl>
<m MPIXMAP_EDIT><nl>
<m MPIXMAP_TEST><nl>
<m MPIXMAP_UNDO><nl>
<m MPIXMAP_REDO><nl>
<m MPIXMAP_ROTATEVIEW><nl>
<m MPIXMAP_PANVIEW><nl>
<m MPIXMAP_ZOOMVIEW><nl>
<m MPIXMAP_ARROW><nl>
<m MPIXMAP_FENCE><nl>
<m MPIXMAP_LASSO><nl>
<m MPIXMAP_FITONFENCE><nl>

For <f mgGraphicsViewSettingGetInteger> and <f mgGraphicsViewSettingSetInteger>:<nl>
<m MGVI_DRAWORDER><nl>

For <f mgGraphicsViewSettingGetMatrix> and <f mgGraphicsViewSettingSetMatrix>:<nl>
<m MGVM_PROJECTION><nl>
<m MGVM_MODELVIEW><nl>
<m MGVM_MODELVIEWPROJECTION><nl>

For <f mgModelingPrefGetInteger>:<nl>
<m MPREFI_SIZEHANDLES><nl>
<m MPREFI_SCALEHANDLES><nl>
<m MPREFI_HANDLETHICKNESS><nl>
<m MPREFI_DRAWHANDLESONTOP><nl>

<m MEFV_1610> for <f mgExportDb><nl>

@group2 New in the OpenFlight Data Dictionary
@normal

@group3 External Reference Nodes
@normal
The following field was exposed in <flt fltXref><nl>
fltXrefViewAsBox<nl>

@group3 Object Nodes
@normal
The following field was added to <flt fltObject><nl>
fltObjPreserveAtRuntime<nl>

@group3 Group Nodes
@normal
The following field was added to <flt fltGroup><nl>
fltGrpPreserveAtRuntime<nl>

@group1 v3.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.1. 

@group2 Common Directory Organization
@normal
The OpenFlight API is now installed into the updated MultiGen-Paradigm
Common Directory Organization.  This structure is significantly different
than previous installations and affects the developer in the following areas:

OpenFlight API installation root<nl>
Location of C source header files<nl>
Location of link libraries<nl>
Location of documentation<nl>
Location of sample code<nl>
Location of redistributable OpenFlight API binaries<nl>

Note that the relocation of the C source header files
and link libraries will cause developers to update their
Visual Studio Project files and/or makefiles before
the corresponding application(s) or plug-in(s) can be rebuilt
with this version of the OpenFlight API.

@group3 OpenFlight API Installation Root
@normal
The installer now creates two environment variables <m MPI_LOCATE_OPENFLIGHT_API> 
and <m MPI_LOCATE_OPENFLIGHT_API_version>, where <m version> 
specifies the major and minor version numbers of the distribution.  For 
OpenFlight API 3.1 the environment variable is <m MPI_LOCATE_OPENFLIGHT_API_3_1>.  
The values for both these variables are the same.  They specify the root of the
OpenFlight API installation. The unversioned variable is the same as in previous 
installations.  The new "versioned" variable is intended to better support multiple
installations of the OpenFlight API to coexist on your computer.

@group3 Location of C source header files
@normal
The C source header files have been relocated to:
<q MPI_LOCATE_OPENFLIGHT_API/include>

@group3 Location of link libraries
@normal
The link libraries have been relocated to:
<q MPI_LOCATE_OPENFLIGHT_API/lib>

@group3 Location of documentation
@normal
The documentation has been relocated to:
<q MPI_LOCATE_OPENFLIGHT_API/docs>

@group3 Location of sample code
@normal
The samples have been relocated to:
<q MPI_LOCATE_OPENFLIGHT_API/samples>

with subfolders for the individual kinds of samples:
<q
/apps - sample stand-alone programs
/extensions - sample OpenFlight data extensions
/plugins - sample plug-ins>

@group3 Location of redistributable OpenFlight API binaries
@normal
If you need to redistribute the OpenFlight API binaries,
the dynamic link libraries you will need are located at:

<q MPI_LOCATE_OPENFLIGHT_API/samples/apps/bin>

@group2 New Functions

@group3 Dialog Functions
@normal
<f mgPromptDialogTexture><nl>

@group3 General Controls
@normal
<f mgGuiGetId><nl>

@group3 Geometry Functions
@normal
<f mgVectordToCoord3d><nl>
<f mgCoord3dToVectord><nl>
<f mgVectordXAxis><nl>
<f mgVectordNegativeXAxis><nl>
<f mgVectordYAxis><nl>
<f mgVectordNegativeYAxis><nl>
<f mgVectordZAxis><nl>
<f mgVectordNegativeZAxis><nl>
<f mgCoord3fTransform><nl>
<f mgVectorfTransform><nl>

@group3 Graphics View Functions
@normal
<f mgSetCurrentGridPoints><nl>
<f mgGetCurrentGridPoints><nl>

@group3 Image To Geometry Projection Function
@normal
<f mgImageToXYZMatrix><nl>

@group3 Matrix Functions
@normal
<f mgMatrixEqual><nl>

@group3 Preference Functions
@normal
<f mgSetCompressVertexTableFlag><nl>
<f mgSetAutoUpdatePriorityFlag><nl>

@group3 Projection Functions
@normal
<f mgProject><nl>
<f mgUnproject><nl>

@group3 Select List Functions
@normal
<f mgIsSelectedEdge><nl>
<f mgSelectOneEdge><nl>

@group3 Shader Functions
@normal
<f mgShaderGetVertexProgramNth><nl>
<f mgShaderGetFragmentProgramNth><nl>
<f mgShaderAddFragmentProgram><nl>
<f mgShaderAddVertexProgram><nl>
<f mgShaderSetVertexProgramNth><nl>
<f mgShaderSetFragmentProgramNth><nl>
<f mgShaderDeleteVertexProgramNth><nl>
<f mgShaderDeleteFragmentProgramNth><nl>

@group3 Texture Functions
@normal
<f mgSubTextureGetBounds><nl>

@group3 Tool Action Functions
@normal
<f mgPluginToolNewAction><nl>
<f mgPluginToolFreeAction><nl>
<f mgPluginToolGetAction><nl>
<f mgToolActionGetName><nl>
<f mgToolActionSetShortCut><nl>
<f mgToolActionGetShortCut><nl>
<f mgToolActionGetShortCutString><nl>
<f mgSetGuiToolAction><nl>

@group2 New Data Types
@normal
<t mgprojcoord><nl>
<t mgtoolaction><nl>
<t mgkeysequence><nl>
<t mgkeytype><nl>

@group2 New Symbols
@normal
<e mgmessageseverityenum.MMSG_TIP> for <f mgSendMessage><nl>
<m MPREFI_AUTOAPPLYSHADELIT2D> for <f mgModelingPrefGetInteger><nl>
<m MPREFI_AUTOAPPLYSHADELIT3D> for <f mgModelingPrefGetInteger><nl>
<m MPREFI_FLIPDDSIMAGES> for <f mgModelingPrefGetInteger><nl>
<m MPREFI_SNAPROTATION> for <f mgModelingPrefGetInteger><nl>
<m MPREFI_SNAPHANDLES> for <f mgModelingPrefGetInteger><nl>
<m MPREFD_SNAPTOANGLE> for <f mgModelingPrefGetDouble><nl>
<m MEFV_1600> for <f mgExportDb><nl>
<e mgcontrolattribute.MCA_SPINAUTOINCREMENT> for <f mgControlSetAttribute><nl>

@group2 New Tool Attributes for Editor Tools 
@normal
(see <f mgRegisterEditor>)

<m MTA_REPEATABLE><nl>
<m MTA_NOHIDESELECTOUTLINE><nl>

@group2 New Palette Locations for Editor and Viewer Tools 
@normal
(see <m MTA_PALETTELOCATION>)

@normal
<m MPAL_DEFORMTOOLS><nl>

@group2 New in the OpenFlight Data Dictionary
@normal

@group3 Shader Palette Nodes
@normal
The following field was added to <flt fltShaderPalette><nl>
fltShaderNumVertexPrograms<nl>
fltShaderNumFragmentPrograms<nl>

@group3 Texture Mapping Palette Nodes
@normal
The following field was added to <flt fltTextureMapping><nl>
fltMappingTransformMatrix<nl>

@group1 v3.0
@normal
This version of the OpenFlight API corresponds to OpenFlight version 16.0.

@group2 Loading Textures in Stand-Alone Applications
@normal
Prior to this version of the API, the texels of textures referenced by a database 
were loaded in memory when you opened the database in stand-alone applications.  
Starting in this version, the texels are not loaded in memory until your application
explicitly requests them (using functions like mgGetTextureTexels or mgReadImage, for
example).

@group2 New Functions

@group3 Dialog Functions
@normal
<f mgHideDialogCallback><nl>
<f mgDestroyDialogCallback><nl>
<f mgRefreshDialogCallback><nl>

@group3 Editor Context Functions
@normal
<f mgEditorSetSnapFace><nl>
<f mgEditorAddRedo><nl>
<f mgEditorAddUndoForRedo><nl>
<f mgEditorAddUndoForCreate><nl>
<f mgEditorAppendUndoForCreate><nl>
<f mgEditorAddUndoForDelete><nl>
<f mgEditorAppendUndoForDelete><nl>
<f mgEditorAddUndoForMove><nl>
<f mgEditorAppendUndoForMove><nl>
<f mgEditorGetPluginTool><nl>
<f mgEditorGetProperty><nl>
<f mgEditorPutProperty><nl>
<f mgEditorDeleteProperty><nl>

@group3 EyePoint Functions
@normal
<f mgGetEyePointLookAt><nl>

@group3 Geometry Functions
@normal
<f mgCoord2dAdd><nl>
<f mgCoord2dSubtract><nl>
<f mgCoord2dMultiply><nl>
<f mgCoord2dDivide><nl>
<f mgCoord2dNegate><nl>
<f mgCoord2dDot><nl>
<f mgCoord2dAngle><nl>
<f mgCoord2dRotateCW><nl>
<f mgCoord2dRotate90CW><nl>
<f mgCoord2dRotateCCW><nl>
<f mgCoord2dRotate90CCW><nl>
<f mgCoord2dReflectX><nl>
<f mgCoord2dReflectY><nl>
<f mgCoord2dReflect><nl>
<f mgCoord2dScalarProject><nl>
<f mgCoord2dVectorProject><nl>
<f mgCoord2dOrthoProject><nl>
<f mgCoord2dXAxis><nl>
<f mgCoord2dNegativeXAxis><nl>
<f mgCoord2dYAxis><nl>
<f mgCoord2dNegativeYAxis><nl>
<f mgCoord2dZero><nl>
<f mgCoord2dOne><nl>
<f mgCoord2dNegativeOne><nl>
<f mgCoord2dLength><nl>
<f mgCoord2dLengthSquared><nl>
<f mgCoord2dSetUnitized><nl>
<f mgCoord2dUnitize><nl>
<f mgCoord3dAdd><nl>
<f mgCoord3dSubtract><nl>
<f mgCoord3dMultiply><nl>
<f mgCoord3dDivide><nl>
<f mgCoord3dNegate><nl>
<f mgCoord3dDot><nl>
<f mgCoord3dCross><nl>
<f mgCoord3dAngle><nl>
<f mgCoord3dPitchDown><nl>
<f mgCoord3dPitchDown90><nl>
<f mgCoord3dPitchUp><nl>
<f mgCoord3dPitchUp90><nl>
<f mgCoord3dRollLeft><nl>
<f mgCoord3dRollLeft90><nl>
<f mgCoord3dRollRight><nl>
<f mgCoord3dRollRight90><nl>
<f mgCoord3dYawLeft><nl>
<f mgCoord3dYawLeft90><nl>
<f mgCoord3dYawRight><nl>
<f mgCoord3dYawRight90><nl>
<f mgCoord3dReflectX><nl>
<f mgCoord3dReflectY><nl>
<f mgCoord3dReflectZ><nl>
<f mgCoord3dReflect><nl>
<f mgCoord3dScalarProject><nl>
<f mgCoord3dVectorProject><nl>
<f mgCoord3dOrthoProject><nl>
<f mgCoord3dXAxis><nl>
<f mgCoord3dNegativeXAxis><nl>
<f mgCoord3dYAxis><nl>
<f mgCoord3dNegativeYAxis><nl>
<f mgCoord3dZAxis><nl>
<f mgCoord3dNegativeZAxis><nl>
<f mgCoord3dZero><nl>
<f mgCoord3dOne><nl>
<f mgCoord3dNegativeOne><nl>
<f mgCoord3dAlmostEqual><nl>
<f mgCoord3dEqual><nl>
<f mgCoord3dLength><nl>
<f mgCoord3dLengthSquared><nl>
<f mgCoord3dSetUnitized><nl>
<f mgCoord3dUnitize><nl>
<f mgCoord3dTransform><nl>
<f mgGetTriangleList><nl>
<f mgCoord3fToCoord3d><nl>
<f mgVectorfToVectord><nl>
<f mgVectordToVectorf><nl>
<f mgVectordDot><nl>
<f mgVectordCross><nl>
<f mgVectordSetUnitized><nl>
<f mgVectordUnitize><nl>

@group3 Graphics View Functions
@normal
<f mgGraphicsViewSettingGetInteger><nl>
<f mgGraphicsViewSettingGetDouble><nl>
<f mgGraphicsViewSettingSetInteger><nl>
<f mgGraphicsViewSettingSetDouble><nl>

@group3 I/O Functions
@normal
<f mgExportDb><nl>
<f mgIsDbModified><nl>

@group3 License Functions
@normal
<f mgNewLicense><nl>
<f mgCheckoutLicense><nl>
<f mgCheckinLicense><nl>
<f mgFreeLicense><nl>

@group3 List Controls
@normal
<f mgListGetTopPos><nl>

@group3 Matrix Functions
@normal
<f mgMatrixGetXAxis><nl>
<f mgMatrixGetYAxis><nl>
<f mgMatrixGetZAxis><nl>
<f mgMatrixGetTranslation><nl>
<f mgMatrixSetXAxis><nl>
<f mgMatrixSetYAxis><nl>
<f mgMatrixSetZAxis><nl>
<f mgMatrixSetTranslation><nl>
<f mgMatrixFormNormal><nl>
<f mgMatrixFormReflectX><nl>
<f mgMatrixFormReflectY><nl>
<f mgMatrixFormReflectZ><nl>
<f mgMatrixFormReflect><nl>
<f mgMatrixFormPitchDown90><nl>
<f mgMatrixFormPitchUp90><nl>
<f mgMatrixFormRollLeft90><nl>
<f mgMatrixFormRollRight90><nl>
<f mgMatrixFormYawLeft90><nl>
<f mgMatrixFormYawRight90><nl>
<f mgMatrixReflectX><nl>
<f mgMatrixReflectY><nl>
<f mgMatrixReflectZ><nl>
<f mgMatrixReflect><nl>
<f mgMatrixPitchDown90><nl>
<f mgMatrixPitchUp90><nl>
<f mgMatrixRollLeft90><nl>
<f mgMatrixRollRight90><nl>
<f mgMatrixYawLeft90><nl>
<f mgMatrixYawRight90><nl>
<f mgMatrixCompose><nl>
<f mgMatrixTranspose><nl>
<f mgMatrixFormXYZToUV><nl>

@group3 Option Menu Functions
@normal
<f mgOptionMenuSelectItem><nl>
<f mgOptionMenuDeleteItem><nl>
<f mgOptionMenuDeleteItemAtPos><nl>
<f mgOptionMenuGetItemStringAtPos><nl>

@group3 Tool Registration Functions
@normal
<f mgPluginPutProperty><nl>
<f mgPluginGetProperty><nl>
<f mgPluginDeleteProperty><nl>

<f mgPluginToolPutProperty><nl>
<f mgPluginToolGetProperty><nl>
<f mgPluginToolDeleteProperty><nl>

<f mgPluginToolGetPlugin><nl>
<f mgPluginToolGetUserData><nl>

@group3 Pointer Array/Stack Functions
@normal
<f mgPtrArrayClear><nl>
<f mgPtrArraySearch><nl>
<f mgPtrArrayBSearch><nl>

<f mgNewPtrStack><nl>
<f mgFreePtrStack><nl>
<f mgPtrStackPush><nl>
<f mgPtrStackPop><nl>
<f mgPtrStackTop><nl>
<f mgPtrStackClear><nl>
<f mgPtrStackLength><nl>

@group3 Select List Functions
@normal
<f mgSelectList><nl>

@group3 Shader Functions
@normal
<f mgGetShader><nl>
<f mgIndexOfShader><nl>
<f mgNameOfShader><nl>
<f mgGetShaderCount><nl>
<f mgGetFirstShader><nl>
<f mgGetNextShader><nl>
<f mgShaderGetLocatorFunc><nl>
<f mgShaderSetLocatorFunc><nl>
<f mgNewShader><nl>
<f mgDeleteShader><nl>
<f mgDeleteShaderByName><nl>
<f mgGetCurrentShader><nl>
<f mgSetCurrentShader><nl>
<f mgShaderGetSavePathType><nl>
<f mgShaderSetSavePathType><nl>

@group3 Structure Functions
@normal
<f mgDuplicateEx><nl>

@group3 Texture Functions
@normal
<f mgMoveTexture><nl>
<f mgTextureGetSavePathType><nl>
<f mgTextureSetSavePathType><nl>

@group2 Light Point API Compatibility
@normal
In version 2.6 of the OpenFlight API, the attributes of light point nodes
(<flt fltLightPoint>) were "palette-ized".  This introduced a level of indirection 
on the light node (similar to color, material and texture on <flt fltPolygon> and 
<flt fltMesh> nodes) into two separate palette entries, 
the Light Point Appearance Palette and Light Point Animation Palette, 
<flt fltLpAppearancePalette> and <flt fltLpAnimationPalette>, respectively.

Regrettably, this "broke" existing applications that use <f mgGetAttList>
and <f mgSetAttList> to access attributes directly on light point nodes. 
In order to function correctly, such applications had to be updated to
first retrieve the appropriate light point palette record referenced by 
a light point node and then use <f mgGetAttList> and <f mgSetAttList> on 
that palette record rather than the light point node directly.

In this version of the OpenFlight API, this situation has been addressed by enhancing
<f mgGetAttList> and <f mgSetAttList> to allow access to light point palette
attributes directly from the light point node.  Specifically, if you now call
<f mgSetAttList> on a light point node specifying any attribute from
the Light Point Appearance Palette or Light Point Animation Palette, the 
corresponding attribute of the palette entry referenced by the light 
point node will be set. Similarly, if you use <f mgGetAttList> on a light 
point node to get a light point palette attribute, the attribute of the
palette entry referenced by the light point node will be retrieved.

Note that if you call <f mgGetAttList> or <f mgSetAttList> on a light point
node to access a palette attribute and the light point node does not yet have 
a palette entry associated, a new palette entry will be created, the corresponding
index on the light point node will be updated to reference this new palette
entry and this new palette entry will be accessed.

@group2 Changed Functions
@normal
<f mgOpenDb>, <f mgCloseDb>, <f mgWriteDb> and <f mgSaveAsDb> can now safely
be called from plug-ins.  See the documentation on these functions for some
limitations.<nl>

The start function registered by <f mgRegisterImporter> is now expected to return
a meaningful value indicating the success or failure of the import processing.<nl>

The dialog displayed by <f mgPromptDialogFolder> now displays a button labeled
"New Folder" that when pressed creates a new folder below the currently selected
folder in the dialog.

In previous versions, the image attribute record returned by the function
<f mgReadImageAttributes> was never freed, resulting in a memory leak.  In this 
version, this record is now freed when the associated database is closed.

The functions <f mgDuplicate>, <f mgDuplicateEx> and <f mgDuplicateToDb> can
now be used to duplicate transformation records (<f fltXmTranslate>,
<f fltXmRotate>, <f fltXmScale>, etc). 

@group2 New Symbols
@normal
<m MGMA_WHEEL> for <f mgGLSetMouseFunc><nl>

<m MPFA_DIALOGID> for <f mgPromptDialogFile><nl>
<m MPFA_RESOURCE> for <f mgPromptDialogFile><nl>
<m MPFA_DIALOGFUNC> for <f mgPromptDialogFile><nl>
<m MPFA_CALLBACKMASK> for <f mgPromptDialogFile><nl>
<m MPFA_USERDATA> for <f mgPromptDialogFile><nl>

<m MCURS_SPLITH> for <f mgResourceGetCursor><nl>
<m MCURS_SPLITV> for <f mgResourceGetCursor><nl>

<m MWALK_NONESTED> for <f mgWalk> and <f mgWalkEx><nl>

<e mgnotifierevent.MNOTIFY_CURRENTLIGHTSOURCECHANGED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_CURRENTSOUNDCHANGED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_CURRENTSHADERCHANGED> for <f mgRegisterNotifier><nl>

@group2 New Menu Locations for Editor and Viewer Tools 
@normal
(see <m MTA_MENULOCATION>)

@normal
<m MMENU_HELP><nl>

@group2 New Palette Locations for Editor and Viewer Tools 
@normal
(see <m MTA_PALETTELOCATION>)

@normal
<m MPAL_BOOLEANTOOLS><nl>
<m MPAL_WIZARDTOOLS><nl>
<m MPAL_CONSTRUCTIONTOOLS><nl>

@group2 New in the OpenFlight Data Dictionary
@normal

You can now define OpenFlight extensions for the following palette types:<nl>
Light Point Appearance Palette (<flt fltLpAppearancePalette>)<nl>
Light Point Animation Palette (<flt fltLpAnimationPalette>)<nl>
Material Palette (<flt fltFMaterial>)<nl>
Shader Palette (<flt fltShaderPalette>)<nl>
Light Source Palette (<flt fltLightSourcePalette>)<nl>
Texture Palette (<flt fltImage>)<nl>
Texture Mapping Palette (<flt fltTextureMapping>)

@group3 Polygon Nodes
@normal
The following field was added to <flt fltPolygon><nl>
fltPolyShader<nl>

@group3 Mesh Nodes
@normal
The following field was added to <flt fltMesh><nl>
fltPolyShader<nl>

@group3 External Reference Nodes
@normal
The following field was added to <flt fltXref><nl>
fltGcShaderPal<nl>

@group3 Shader Palette Nodes
@normal
The following palette node was added<nl>
<flt fltShaderPalette><nl>

@group3 Light Point Appearance Palette Nodes
@normal
The following field was added to <flt fltLpAppearancePalette><nl>
fltLpTexture<nl>

@group2 Deprecated API
@normal
The following symbols have been deprecated in this version of 
the API. For each symbol that appears in this section, an appropriate 
replacement symbol or strategy is also given.  These deprecated symbols
are still supported in this version of the OpenFlight API and will likely remain
supported indefinitely in future versions.  However, it is recommended
(but not required) that you replace any deprecated symbols in your code
with the suggested replacements.  This will ensure that code you develop
using the MultiGen OpenFlight API remains compatible with future versions
of the API.

@normal
In this version, a significant number of new geometry functions were added
to help users work with 2D and 3D coordinates.  To help distinguish the
2D and 3D function names (as well as those for vectors) a new naming
convention has been adopted for all geometry functions.  Several existing
functions were affected by the new naming convention and for that reason,
they have been deprecated.  Here is a list of those functions:<nl>
@normal
<f mgAddCoord> replaced by <f mgCoord3dAdd><nl>
<f mgCoordDif> replaced by <f mgCoord3dSubtract><nl>
<f mgCoord3dTof> replaced by <f mgCoord3dToCoord3f><nl>
<f mgCoordsEqual> replaced by <f mgCoord3dAlmostEqual><nl>
<f mgDistance> replaced by <f mgCoord3dDistance><nl>
<f mgVectorCross> replaced by <f mgVectordCross><nl>
<f mgVectorDot> replaced by <f mgVectordDot><nl>
<f mgVectorFromLine> replaced by <f mgVectordFromLine><nl>
<f mgMoveCoordAlongVectorf> replaced by <f mgCoord3dMoveAlongVectorf><nl>
<f mgMoveCoordAlongVector> replaced by <f mgCoord3dMoveAlongVectord><nl>
<f mgTransformCoord> replaced by <f mgCoord3dTransform><nl>
<f mgTransformVector> replaced by <f mgVectordTransform><nl>
<f mgUnitizeVector> replaced by <f mgVectordSetUnitized><nl>
<f mgMakeVector> replaced by <f mgMakeVectord><nl>
<f mgMakeUnitVector> replaced by <f mgMakeUnitVectord><nl>
<f mgVectordTof> replaced by <f mgVectordToVectorf><nl>

@normal
In Creator, the Vertex and Edge construction tool boxes were combined
into one, the Construction tool box.  For that reason, the following
symbols were deprecated:<nl>

<m MPAL_EDGETOOLS> deprecated, use <m MPAL_CONSTRUCTIONTOOLS><nl>
<m MPAL_VERTEXTOOLS> deprecated, use <m MPAL_CONSTRUCTIONTOOLS><nl>

If you continue to use either of these deprecated symbols when you
register your plug-in tool, the pixmap for your tool will appear
in the Construction tool box.

@group1 v2.6.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 15.8.

@normal
No new functions were added for this release.  The OpenFlight API
Reference was updated, however, to correct assorted typographical
errors, broken links, etc. 

@group1 v2.6
@normal
This version of the OpenFlight API corresponds to OpenFlight version 15.8.

@group2 Common Directory Organization
@normal
The OpenFlight API is now installed into the MultiGen-Paradigm
Common Directory Organization.  This structure is significantly different
than previous installations and affects the developer in the following areas:

OpenFlight API installation root<nl>
Location of C source header files<nl>
Location of link libraries<nl>
Location of documentation<nl>
Location of sample code<nl>
Location of redistributable OpenFlight API binaries<nl>
Location of plug-in runtime directory

Note that the relocation of the C source header files
and link libraries will cause developers to update their
Visual Studio Project files and/or IRIX makefiles before
the corresponding application(s) or plug-in(s) can be rebuilt
with this version of the OpenFlight API.

@group3 OpenFlight API Installation Root
@normal
The installer now creates an environment variable <m MPI_LOCATE_OPENFLIGHT_API>
whose value specifies the root of the OpenFlight API installation.  This
replaces the environment variable <m MGAPIDIST> used by previous versions.

@group3 Location of C source header files
@normal
The C source header files have been relocated to:
<q MPI_LOCATE_OPENFLIGHT_API/include/openflightapi>

@group3 Location of link libraries
@normal
The link libraries have been relocated to:
<q MPI_LOCATE_OPENFLIGHT_API/lib>

@group3 Location of documentation
@normal
The documentation has been relocated to:
<q MPI_LOCATE_OPENFLIGHT_API/docs/openflightapi>

@group3 Location of sample code
@normal
The samples have been relocated to:
<q MPI_LOCATE_OPENFLIGHT_API/resources/samples/openflightapi>

with subfolders for the individual kinds of samples:
<q
/apps - sample stand-alone programs
/extensions - sample OpenFlight data extensions
/plugins - sample plug-ins>

@group3 Location of redistributable OpenFlight API binaries
@normal
If you need to redistribute the OpenFlight API binaries,
the dynamic link libraries you will need are located at:

<q MPI_LOCATE_OPENFLIGHT_API/resources/samples/openflightapi/apps/bin>

@group3 Location of plug-in runtime directory
@normal
At start up, Creator and stand-alone OpenFlight API applications
now use the environment variable <m MPI_CREATOR_PLUGIN_DIR> to locate
plug-ins.  This replaces the environment variable <m MGPLUGINDIR> used
by previous versions.
  
@group2 Light Points
@normal
Light Points were changed significantly in this version.  Prior to this
version, light point attributes were completely contained within the 
<flt fltLightPoint> node.  Starting with this version, the light point
attributes have been moved from the light point node into two separate
palettes.  This introduces a level of indirection (similar to color, 
material and texture on <flt fltPolygon> and <flt fltMesh> nodes) 
on the light point node into two separate palette entries.

@normal
The new light point palettes include the Light Point Appearance Palette 
and Light Point Animation Palette, <flt fltLpAppearancePalette> and
<flt fltLpAnimationPalette>, respectively.  Entries in the Light Point 
Appearance palette describe the visual "appearance" of a light point
(color, directionality, etc) while entries in the Light Point Animation
palette describe how a light point behaves (flashes, rotates, etc).  

@normal
See the Read/Write User’s Guide for more information on light points
in this version.

@group2 New Functions

@group3 Light Point Functions
@normal
<f mgGetLightPointAppearance><nl>
<f mgIndexOfLightPointAppearance><nl>
<f mgNameOfLightPointAppearance><nl>
<f mgGetLightPointAppearanceCount><nl>
<f mgGetFirstLightPointAppearance><nl>
<f mgGetNextLightPointAppearance><nl>
<f mgGetLightPointAnimation><nl>
<f mgIndexOfLightPointAnimation><nl>
<f mgNameOfLightPointAnimation><nl>
<f mgGetLightPointAnimationCount><nl>
<f mgGetFirstLightPointAnimation><nl>
<f mgGetNextLightPointAnimation><nl>
<f mgReadLightPointFile><nl>
<f mgNewLightPointAppearance><nl>
<f mgDeleteLightPointAppearance><nl>
<f mgNewLightPointAnimation><nl>
<f mgDeleteLightPointAnimation><nl>
<f mgWriteLightPointFile><nl>
<f mgGetCurrentLightPointAppearance><nl>
<f mgSetCurrentLightPointAppearance><nl>
<f mgGetCurrentLightPointAnimation><nl>
<f mgSetCurrentLightPointAnimation><nl>
<f mgLightPointAnimationSequenceGet><nl>
<f mgLightPointAnimationSequenceSet><nl>

@group3 Attribute Functions
@normal
<f mgGetVtxColorRGBA><nl>
<f mgSetVtxColorRGBA><nl>
<f mgSetPlane><nl>

@group3 Structure Functions
@normal
<f mgWalkEx><nl>
<f mgWalkGetMatrix><nl>
<f mgValidAttach><nl>

@group3 Tool Activation Functions
@normal
<f mgGetDefaultModelingParent><nl>

@group3 Matrix Functions
@normal
<f mgNewMatrix><nl>
<f mgFreeMatrix><nl>
<f mgMatrixIdentity><nl>
<f mgMatrixIsIdentity><nl>
<f mgMatrixInvert><nl>
<f mgMatrixMultiply><nl>
<f mgMatrixCopy><nl>
<f mgMatrixFormTranslate><nl>
<f mgMatrixFormScale><nl>
<f mgMatrixFormRotateX><nl>
<f mgMatrixFormRotateY><nl>
<f mgMatrixFormRotateZ><nl>
<f mgMatrixFormQuadToQuad><nl>
<f mgMatrixTranslate><nl>
<f mgMatrixScale><nl>
<f mgMatrixRotateX><nl>
<f mgMatrixRotateY><nl>
<f mgMatrixRotateZ><nl>

@group3 Matrix Stack Functions
@normal
<f mgNewMatrixStack><nl>
<f mgFreeMatrixStack><nl>
<f mgMatrixStackPush><nl>
<f mgMatrixStackPop><nl>
<f mgMatrixStackLoadIdentity><nl>
<f mgMatrixStackLoadMatrix><nl>
<f mgMatrixStackGetMatrix><nl>
<f mgMatrixStackIsIdentity><nl>
<f mgMatrixStackMultiply><nl>
<f mgMatrixStackTranslate><nl>
<f mgMatrixStackScale><nl>
<f mgMatrixStackRotate><nl>
<f mgMatrixStackRotateX><nl>
<f mgMatrixStackRotateY><nl>
<f mgMatrixStackRotateZ><nl>
<f mgMatrixStackTransformCoord><nl>
<f mgMatrixStackTransformVector><nl>

@group3 Geometry Functions
@normal
<f mgMoveCoordAlongVector><nl>
<f mgMoveCoordAlongVectorf><nl>
<f mgVectorCross><nl>
<f mgVectorDot><nl>
<f mgReversePoly><nl>
<f mgCoordsEqual><nl>
<f mgMakeUnitVector><nl>
<f mgMakeCoord3d><nl>
<f mgMakeCoord3f><nl>
<f mgMakeCoord2d><nl>
<f mgMakeCoord2i><nl>
<f mgTransformVector><nl>

@group3 Dialog Functions
@normal
<f mgShowPalette><nl>

@group3 Text Controls
@normal
<f mgTextSetFilename><nl>

@group3 Pointer Array Functions
@normal
<f mgPtrArraySort><nl>

@group3 Mesh Functions
@normal
<f mgMeshSetVtxMask><nl>
<f mgMeshGetVtxColorRGBA><nl>
<f mgMeshGetVtxColorAlpha><nl>
<f mgMeshSetVtxColorRGBA><nl>
<f mgMeshSetVtxColorAlpha><nl>

@group3 Switch Functions
@normal
<f mgGetSwitchMaskName><nl>
<f mgSetSwitchMaskName><nl>

@group3 Info Functions
@normal
<f mgGetOpenFlightVersion><nl>

@group3 Texture Functions
@normal
<f mgIsTextureIndexInPalette><nl>

@group3 Preference Functions
@normal
<f mgSetSaveNonIndexedLightPoints><nl>
<f mgModelingPrefGetInteger><nl>
<f mgModelingPrefGetDouble><nl>

@group3 Plugin Registration Functions
@normal
<f mgGetRegistryString><nl>
<f mgSetRegistryString><nl>

@group2 New Data Types
@normal
<t mgptrarraycomparefunc><nl>

@group2 New Symbols
@normal
<e mgnotifierevent.MNOTIFY_CURRENTTEXTUREMAPPINGCHANGED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_CURRENTLIGHTPOINTAPPEARANCECHANGED> for <f mgRegisterNotifier><nl>
<e mgnotifierevent.MNOTIFY_CURRENTLIGHTPOINTANIMATIONCHANGED> for <f mgRegisterNotifier><nl>

<e mgcontrolattribute.MCA_BOLDFONT> for <f mgControlSetAttribute><nl>
<e mgcontrolattribute.MCA_ITALICFONT> for <f mgControlSetAttribute><nl>
<m MVERSION_OPENFLIGHT><nl>
<m MWALK_MATRIXSTACK> for <f mgWalk> and <f mgWalkEx><nl>

@group2 Sample Plugins
@normal
Two new sample plug-ins, <m dfdtest> and <m walktest>, were added to the sample plug-ins
folder.  The first <m dfdtest> shows you how to use the DFD API in the context of a
Creator plug-in.  It also shows some interesting OpenGL drawing
techniques.  The second <m walktest> shows you how to use the new functions
<f mgWalkEx> and <f mgWalkGetMatrix>.

The existing plug-in, <m attrviewer>, was updated to include all the new attributes
added in OpenFlight version 15.8.

@group2 Fixes
@normal
Fixed <f mgSetAttList> when used to set fltPolyTexWhite (see <flt fltPolygon>).

Fixed <f mgGLMaterialIndex> to render transparent materials properly.

Fixed <f mgGLTextureIndex> to load a pattern's pixels when necessary.

Fixed <f mgWriteDb> to calculate LOD centers (when applicable) properly.

Fixed <f mgPtrArrayAppend> to return the proper array length.

Fixed <f mgReadTexturePalette> and <f mgCopyTexturePalette> to update
the Texture Palette window properly.

Fixed <f mgReadMaterialFile>, <f mgDeleteMaterial>, <f mgDeleteMaterialByName>,
and <f mgNewMaterial> to update the Material Palette window properly.

Fixed <f mgEditorResetUndo> to clear the Undo Menu properly when invoked
from a tool that does not display a dialog.
 
Fixed <f mgInsert> to properly insert nested children (subfaces) and
transformation nodes.
 
The pick function assigned for editor plug-in tools is now called when the user
selects nodes in the hierarchy view.

Fixed <f mgSelectOne> to always select a valid transformation path above
selected node.

@group2 Deprecated API
@normal
The following symbols have been deprecated in this version of 
the OpenFlight API. For each symbol that appears in this section, an appropriate 
replacement symbol or strategy is also given.  These deprecated symbols
are still supported in this version of the OpenFlight API and will likely remain
supported indefinitely in future versions.  However, it is recommended
(but not required) that you replace any deprecated symbols in your code
with the suggested replacements.  This will ensure that code you develop
using the MultiGen OpenFlight OpenFlight API remains compatible with future versions
of the API.

@normal
<f mgVectorMove> replaced by <f mgMoveCoordAlongVectorf><nl>
<f mgCrossProdVector> replaced by <f mgVectorCross><nl>
<f mgDelLightSource> replaced by <f mgDeleteLightSource><nl>
<f mgDelSound> replaced by <f mgDeleteSound><nl>
<f mgDelMaterial> replaced by <f mgDeleteMaterial><nl>
<f mgDelMaterialByName> replaced by <f mgDeleteMaterialByName><nl>
<f mgDelTextureMapping> replaced by <f mgDeleteTextureMapping><nl>
<f mgDelTextureMappingByName> replaced by <f mgDeleteTextureMappingByName><nl>
<flt fltLpAttr> replaced by <flt fltLpAppearancePalette> and <flt fltLpAnimationPalette>

@group2 New in the OpenFlight Data Dictionary
@normal

@group3 Header Nodes
@normal
The following fields were added to <flt fltHeader>:<nl>
fltHdrEarthMinorAxis<nl>
fltHdrEarthMajorAxis<nl>

@group3 LOD Nodes
@normal
The following fields were added to <flt fltLod>:<nl>
fltLodSignificantSize<nl>

@group3 Group Nodes
@normal
The following fields were added to <flt fltGroup>:<nl>
fltGrpLoopCount<nl>
fltGrpLoopDuration<nl>
fltGrpLastFrameDuration<nl>

@group3 Switch Nodes
@normal
The following fields were added to <flt fltSwitch>:<nl>
Individual masks of Switch Nodes can now be named.
See <f mgGetSwitchMaskName> and <f mgSetSwitchMaskName>.

@group3 Polygon Nodes
@normal
The following fields were added to <flt fltPolygon>:<nl>
fltPolyRoofline<nl>

@group3 Mesh Nodes
@normal
The following fields were added to <flt fltMesh>:<nl>
fltPolyRoofline<nl>

@group3 Vertex Nodes
@normal
Vertex Nodes now can include alpha color components which is represented by the following new field in <flt fltVertex><nl>
fltVAlpha<nl>

And the following functions were added to access the vertex alpha color component<nl>
<f mgGetVtxColorRGBA><nl>
<f mgSetVtxColorRGBA><nl>

@group3 External Reference Nodes
@normal
The following field was added to <flt fltXref><nl>
fltGcLpPal<nl>

@group3 Light Point Nodes
@normal
The following fields were added to <flt fltLightPoint>:<nl>
fltLpAppearance<nl>
fltLpAnimation<nl>

@group3 Light Point Palette Nodes
@normal
The following palette nodes were added<nl>
<flt fltLpAppearancePalette><nl>
<flt fltLpAnimationPalette><nl>

@group1 v2.5.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 15.7.

@normal
No new functions were added for this release.

@group1 v2.5
@normal
This version of the OpenFlight API corresponds to OpenFlight version 15.7.

@group2 OpenFlight API version number
@normal
When you call <f mgInit>, it now displays the OpenFlight API version
number currently loading.  This can help stand-alone program developers
and users verify that the correct version of the OpenFlight API libraries
are loading at runtime.  You can disable this as well as other messages
issued by the OpenFlight API using the function <f mgSetMessagesEnabled>.

@group2 Menus in Plugin Dialogs
@normal
Menus are now supported within plug-in dialogs.
See the <i OpenFlight API Developer Guide, Volume 2> for more 
information. Also, see the new supporting functions
<f mgMenuSetState> and <m mgMenuGetState>.

@group2 Mouse Motion Events in GL Controls
@normal
GL controls in plug-in dialogs can now receive mouse motion events
even when a mouse button is not pressed.  This allows a plug-in to
"monitor" the cursor location as the user moves the mouse
(without pressing a mouse button) over the GL control.  See 
<f mgGLSetMouseFunc>, <m MGMA_MOTION>, and <t mgglmousemotiondatarec>.

@group2 New Data Types
@normal
<t mgglmousemotiondatarec><nl>
<t mgcontrolattribute><nl>

@group2 New Symbols
@normal
<m MGMA_MOTION> for <f mgGLSetMouseFunc><nl>
<e mgcontrolattribute.MCA_GLBORDERSTYLE> for <f mgControlSetAttribute><nl>
<m MGLBS_NONE> for <e mgcontrolattribute.MCA_GLBORDERSTYLE><nl>
<m MGLBS_SUNKEN> for <e mgcontrolattribute.MCA_GLBORDERSTYLE><nl>
<m MGLBS_RAISED> for <e mgcontrolattribute.MCA_GLBORDERSTYLE><nl>
<m MGLBS_SOLID> for <e mgcontrolattribute.MCA_GLBORDERSTYLE><nl>
 
@group2 New Functions
@normal

<f mgMenuSetState><nl>
<f mgMenuGetState><nl>
<f mgControlSetAttribute><nl>

@group2 Sample Plugins
@normal
A new sample plug-in, called <m menutest>, was added to the <m sample_plugins>
folder. This plug-in shows you how to add menus to your plug-in tool 
dialogs using the new menu capabilities included in this version
of the OpenFlight API.

The existing plug-in, <m attrviewer>, was updated to show you how to add
a custom Windows control (in this case, a tree view control) to
a plug-in tool dialog.  The example includes how to access native
Windows GUI constructs through the OpenFlight API.
  
@group1 v2.4.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 15.7.

@group2 Debugging Plug-ins in the Creator environment

@normal
When debugging your plug-in initialization code on Windows, you may
find that the Creator splash screen occludes your workspace.  To avoid
this, you can disable the Creator splash screen by setting the environment
variable <m MGNOSPLASH> to <m 1>, <m TRUE>, or <m true> before running
Creator.  To re-enable
the splash screen, un-set this environment variable or set it to
<m 0>, <m FALSE>, or <m false>.

Note: After you change an environment variable on the Windows
platform, you must exit and restart your development environment
(Visual Studio, etc) before the change you make takes effect in
your environment.

@group1 v2.4
@normal
This version of the OpenFlight API corresponds to OpenFlight version 15.7.

@group2 New Tool Attributes for Editor and Viewer Tools 
@normal
(see <f mgRegisterEditor> and <f mgRegisterViewer>)

<m MTA_MENUPOSITION><nl>
<m MTA_MENUSUBMENU><nl>

@group2 New Data Types
@normal
<t mgreclist> - formerly <t mgselectlist><nl>
<t mgcursorid><nl>
<t mgcursor><nl>
<t mgcursorhandle><nl>
<t mgptrarray><nl>

@group2 New Symbols
@normal

<m MPRIM_TRI_STRIP><nl>
<m MPRIM_TRI_FAN><nl>
<m MPRIM_QUAD_STRIP><nl>
<m MPRIM_INDEXED_POLY><nl>

<m MMESH_VTXCOORD><nl>
<m MMESH_VTXCOLOR><nl>
<m MMESH_VTXCOLORRGB><nl>
<m MMESH_VTXNORMAL><nl>
<m MMESH_VTXUV0><nl>
<m MMESH_VTXUV1><nl>
<m MMESH_VTXUV2><nl>
<m MMESH_VTXUV3><nl>
<m MMESH_VTXUV4><nl>
<m MMESH_VTXUV5><nl>
<m MMESH_VTXUV6><nl>
<m MMESH_VTXUV7><nl>

@group2 New Functions

@group3 Mesh Functions
@normal
<f mgMeshGetVtxPool><nl>
<f mgMeshGetVtxMask><nl>
<f mgMeshGetVtxStride><nl>
<f mgMeshGetVtxOffset><nl>
<f mgMeshPrimitiveGetType><nl>
<f mgMeshPrimitiveGetNumVtx><nl>
<f mgMeshPrimitiveGetVtxIndexArray><nl>
<f mgMeshGetVtxCoord><nl>
<f mgMeshGetVtxColor><nl>
<f mgMeshGetVtxColorRGB><nl>
<f mgMeshGetVtxNormal><nl>
<f mgMeshGetVtxUV><nl>

<f mgMeshCreateVtxPool><nl>
<f mgMeshCreatePrimitives><nl>
<f mgMeshPrimitiveSetType><nl>
<f mgMeshPrimitiveSetVtxIndexArray><nl>
<f mgMeshSetVtxCoord><nl>
<f mgMeshSetVtxColor><nl>
<f mgMeshSetVtxColorRGB><nl>
<f mgMeshSetVtxNormal><nl>
<f mgMeshSetVtxUV><nl>

@group3 Database/Attribute Functions
@normal
<f mgIsDbUntitled><nl>

<f mgDuplicateToDb><nl>

<f mgGetVectord><nl>
<f mgSetVectord><nl>

<f mgGeoCoordCount><nl>

<f mgGetTextureSaveName><nl>

<f mgGetConstructList><nl>

@group3 Texture Functions
@normal
<f mgSubTextureCount><nl>
<f mgSubTextureGet><nl>
<f mgSubTextureAdd><nl>
<f mgSubTextureDelete><nl>

@group3 Texture Layer Functions
@normal
<f mgGetCurrentTextureLayer><nl>
<f mgSetCurrentTextureLayer><nl>

@group3 Dialog/Control Functions
@normal
<f mgListDeselectItemAtPos><nl>
<f mgListGetItemStringAtPos><nl>
<f mgListReplaceItemAtPos><nl>

<f mgTextGetDMS><nl>
<f mgTextSetDMS><nl>

<f mgResourceGetCursor><nl>
<f mgGetCursorHandle><nl>
<f mgSetCursor><nl>

<f mgGuiSetFixedFont><nl>
<f mgRefreshControl><nl>

@group3 Convenience Dialog Functions
@normal
<f mgPromptDialogFile><nl>
<f mgPromptDialogColor><nl>
<f mgPromptDialogFolder><nl>

@group3 Select List Functions
@normal
<f mgGetSelectList> - formerly <f mgNewSelectList><nl>
<f mgFreeRecList> - formerly <f mgFreeSelectList><nl>
<f mgResetRecList> - formerly <f mgResetSelectList><nl>
<f mgGetNextRecInList> - formerly <f mgGetNextSelected><nl>
<f mgGetNthRecInList> - formerly <f mgGetNthSelected><nl>
<f mgGetRecListCount> - formerly <f mgGetSelectListCount><nl>
<f mgGetRecListLevel> - formerly <f mgGetSelectListLevel><nl>

@group3 Pointer Array Functions
@normal
<f mgNewPtrArray><nl>
<f mgFreePtrArray><nl>
<f mgPtrArrayAppend><nl>
<f mgPtrArrayInsert><nl>
<f mgPtrArrayReplace><nl>
<f mgPtrArrayGet><nl>
<f mgPtrArrayRemove><nl>
<f mgPtrArrayLength><nl>

@group2 Changed Functions
@normal
<f mgSetMessagesEnabled> can now be called before <f mgInit> within
the stand-alone program environment to control message display
during the OpenFlight API initialization function.<nl>

@group2 New in the OpenFlight Data Dictionary
@normal

@group3 Mesh Nodes
@normal
Mesh nodes were introduced (<flt fltMesh>) and include the following fields<nl>
fltMeshNumPrimitives<nl>
fltMeshNumVtx<nl>

In addition, mesh nodes use the <flt fltPolygon> attributes.

@group3 MultiTexture
@normal

For <flt fltPolygon> nodes and <flt fltMesh> nodes:

fltLayerTexture1<nl>
fltLayerTexture2<nl>
fltLayerTexture3<nl>
fltLayerTexture4<nl>
fltLayerTexture5<nl>
fltLayerTexture6<nl>
fltLayerTexture7<nl>

fltLayerTexmap1<nl>
fltLayerTexmap2<nl>
fltLayerTexmap3<nl>
fltLayerTexmap4<nl>
fltLayerTexmap5<nl>
fltLayerTexmap6<nl>
fltLayerTexmap7<nl>

fltLayerEffect1<nl>
fltLayerEffect2<nl>
fltLayerEffect3<nl>
fltLayerEffect4<nl>
fltLayerEffect5<nl>
fltLayerEffect6<nl>
fltLayerEffect7<nl>

fltLayerData1<nl>
fltLayerData2<nl>
fltLayerData3<nl>
fltLayerData4<nl>
fltLayerData5<nl>
fltLayerData6<nl>
fltLayerData7<nl>

For <flt fltVertex> nodes:

fltLayerU1<nl>
fltLayerU2<nl>
fltLayerU3<nl>
fltLayerU4<nl>
fltLayerU5<nl>
fltLayerU6<nl>
fltLayerU7<nl>

fltLayerV1<nl>
fltLayerV2<nl>
fltLayerV3<nl>
fltLayerV4<nl>
fltLayerV5<nl>
fltLayerV6<nl>
fltLayerV7<nl>

@group3 Header Node
@normal
The following fields were added to <flt fltHeader>:<nl>
fltUTMZone<nl>
fltTerTransX<nl>
fltTerTransY<nl>
fltTerTransZ<nl>
fltDBRadius<nl>


@group2 Deprecated API
@normal
The following symbols have been deprecated in this version of the 
OpenFlight API. For each symbol that appears in this section, an appropriate 
replacement symbol or strategy is also given.  These deprecated symbols
are still supported in this version of the API and will likely remain
supported indefinitely in future versions.  However, it is recommended
(but not required) that you replace any deprecated symbols in your code
with the suggested replacements. This will ensure that code you develop
using the MultiGen OpenFlight API remains compatible with future versions
of the API.

@normal
<t mgselectlist> replaced by <t mgreclist><nl>
<f mgNewSelectList> replaced by <f mgGetSelectList><nl>
<f mgFreeSelectList> replaced by <f mgFreeRecList><nl>
<f mgResetSelectList> replaced by <f mgResetRecList><nl>
<f mgGetNextSelected> replaced by <f mgGetNextRecInList><nl>
<f mgGetNthSelected> replaced by <f mgGetNthRecInList><nl>
<f mgGetSelectListCount> replaced by <f mgGetRecListCount><nl>
<f mgGetSelectListLevel> replaced by <f mgGetRecListLevel><nl>

<f fltHdrFlagVtxNorms> replaced by fltHdrSaveVtxNorms

<f fltPolyMgTemplate> replaced by fltPolyTemplate<nl>
<f fltPolyTexture1> replaced by fltPolyDetailTexture<nl>
<f fltPolyTexmap1> replaced by fltPolyDetailTexmap<nl>
<f fltCatTexture1> replaced by fltCatDetailTexture<nl>

<f fltPolyFlagNocolor> replaced by fltPolyNoPrimeColor<nl>
<f fltPolyFlagNocolor2> replaced by fltPolyNoAltColor<nl>
<f fltPolyFlagRgbMode> replaced by fltPolyRgbMode<nl>
<f fltPolyFlagTerrain> replaced by fltPolyTerrain<nl>
<f fltPolyFlagHidden> replaced by fltPolyHidden<nl>
<f fltPolyFlagFootprint> replaced by fltPolyFootprint<nl>

<f fltObjFlagDay> replaced by fltObjNoDay<nl>
<f fltObjFlagDusk> replaced by fltObjNoDusk<nl>
<f fltObjFlagNight> replaced by fltObNoNight<nl>
<f fltObjFlagNoillum> replaced by fltObjNoIllum<nl>
<f fltObjFlagNoshade> replaced by fltObjNoShade<nl>
<f fltObjFlagShadow> replaced by fltObjShadow<nl>

<f fltGrpFlagAnimation> replaced by fltGrpAnimation<nl>
<f fltGrpFlagAnimationFB> replaced by fltGrpAnimationFB<nl>
<f fltGrpFlagBoxed> replaced by fltGrpBoxed<nl>
<f fltGrpFlagFreezeBox> replaced by fltGrpFreezeBox<nl>

<f fltLodFlagAdditive> replaced by fltLodAdditive<nl>
<f fltLodFlagFreezeCenter> replaced by fltLodFreezeCenter<nl>
<f fltLodFlagRange> replaced by fltLodUsePrevRange<nl>

<f fltDofFlagTxtRepeat> replaced by fltDofTxtRepeat<nl>
<f fltDofFlagMembrane> replaced by fltDofMembrane<nl>

<f fltDofCurAzim> replaced by fltDofCurXRot<nl>
<f fltDofMinAzim> replaced by fltDofMinXRot<nl>
<f fltDofMaxAzim> replaced by fltDofMaxXRot<nl>
<f fltDofIncrementAzim> replaced by fltDofIncXRot<nl>
<f fltDofFlagAzimLimited> replaced by fltDofLimitXRot<nl>

<f fltDofCurIncl> replaced by fltDofCurYRot<nl>
<f fltDofMinIncl> replaced by fltDofMinYRot<nl>
<f fltDofMaxIncl> replaced by fltDofMaxYRot<nl>
<f fltDofIncrementIncl> replaced by fltDofIncYRot<nl>
<f fltDofFlagInclLimited> replaced by fltDofLimitYRot<nl>

<f fltDofCurTwist> replaced by fltDofCurZRot<nl>
<f fltDofMinTwist> replaced by fltDofMinZRot<nl>
<f fltDofMaxTwist> replaced by fltDofMaxZRot<nl>
<f fltDofIncrementTwist> replaced by fltDofIncZRot<nl>
<f fltDofFlagTwistLimited> replaced by fltDofLimitZRot<nl>

<f fltDofIncrementX> replaced by fltDofIncX<nl>
<f fltDofIncrementY> replaced by fltDofIncY<nl>
<f fltDofIncrementZ> replaced by fltDofIncZ<nl>

<f fltDofFlagXLimited> replaced by fltDofLimitX<nl>
<f fltDofFlagYLimited> replaced by fltDofLimitY<nl>
<f fltDofFlagZLimited> replaced by fltDofLimitZ<nl>

<f fltDofIncrementXScale> replaced by fltDofIncXScale<nl>
<f fltDofIncrementYScale> replaced by fltDofIncYScale<nl>
<f fltDofIncrementZScale> replaced by fltDofIncZScale<nl>

<f fltDofFlagXScaleLimited> replaced by fltDofLimitXScale<nl>
<f fltDofFlagYScaleLimited> replaced by fltDofLimitYScale<nl>
<f fltDofFlagZScaleLimited> replaced by fltDofLimitZScale<nl>

@normal


@group1 v2.3
@normal
This version of the OpenFlight API corresponds to OpenFlight version 15.6.

@normal
The Level 4 API was implemented on the SGI/Irix
platform.  The OpenFlight API libraries were distributed
on SGI/Irix using n32 binary format.

@group2 New Functions
@normal
<f mgGetExtRec>

@group2 Changed Functions
@normal
<f mgAttach> was modified to support attaching tag-along
extension records to nodes programmatically.<nl>


@group1 v2.2.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 15.6.

@group2 New Functions
@normal
<f mgTextureGetLocatorFunc><nl>
<f mgTextureSetLocatorFunc><nl>
<f mgExtRefGetLocatorFunc><nl>
<f mgExtRefSetLocatorFunc>

@group2 New Data Types
@normal
<t mgfilelocatorfunc>

@group1 v2.2
@normal
This version of the OpenFlight API corresponds to OpenFlight version 15.6.

@normal
Access to the following OpenFlight node types was added to the
OpenFlight Data Dictionary:

@normal
<flt fltGrid><nl>
<flt fltHelper><nl>
<flt fltSurface><nl>
<flt fltTorsion><nl>

@group1 v2.1
@normal
This version of the OpenFlight API corresponds to OpenFlight version 15.6.

@group2 Plug-in Runtime Directory

@normal
The directory specified by the environment variable <m MGPLUGINDIR> supersedes
all other plug-in runtime directories searched.  Additionally, once a plug-in 
runtime directory is located, it and all subdirectories below it are recursively
searched for plug-in modules.  See the <i OpenFlight API Developer Guide, Volume 2>
for more information.

@group2 Automatic Version Update for Data Extension Records

@normal
Padding is no longer required to reserve space for future additions to
<m struct> definitions.  When the OpenFlight API finds an extension record in a
database file that is shorter than the current corresponding <m struct>
definition, the extension record (when it is read into memory) is automatically
expanded to accommodate for the new fields at the end of the new <m struct>
definition.  When this happens, the values for these new fields are 
initialized to 0.  See the <i OpenFlight API Developer Guide, Volume 2>
for more information.

@group2 Changed Functions

@normal
<f mgIndex2RGB> was changed to return <t mgbool>.<nl>
<f mgRGB2Index> was changed to return <t mgbool>.<nl>
<f mgRegisterPostEdit> was changed to return <t mgstatus>.<nl>
<f mgRegisterPreEdit> was changed to return <t mgstatus>.<nl>
<f mgResourceGetPixmap> now supports icons in addition to bitmaps on Windows.<nl>


@group2 Changes to OpenFlight record/data codes

@normal
Typo in <m fltTxtGetCoordLst> was corrected to <m fltTxtGeoCoordLst>

@group2 Previously Undocumented Functions

@normal
<f ddIsField><nl>
<f ddIsFieldFollowAll><nl>
<f ddIsFieldFollowPointer><nl>
<f ddIsFieldFollowInLine><nl>
<f ddLabelToCode><nl>
<f ddNameToCode><nl>

@group2 New Control and Dialog Events

@normal
<m MGCB_SIZE><nl>
<m MGCB_DRAW><nl>

@group2 New Menu Locations for Editor and Viewer Tools 
@normal
(see <m MTA_MENULOCATION>)

@normal
<m MMENU_TERRAIN><nl>
<m MMENU_ROAD><nl>
<m MMENU_GEOFEATURE><nl>
<m MMENU_SOUND><nl>
<m MMENU_INSTRUMENTS><nl>
<m MMENU_BSP><nl>

@group2 New Tool Attributes
 
@normal
<m MTA_HELPCONTEXT><nl>

@group2 New Data Types

@normal
<t mgglmousefunc><nl>
<t mgglmousedatatype><nl>
<t mgglmouseaction><nl>
<t mgglmousedatarec><nl>
<t mgglmousebuttondatarec><nl>
<t mgglmousedoubleclickdatarec><nl>
<t mgguicalldatatype><nl>
<t mgtextactivatecallbackrec><nl>
<t mgtabruleractivatecallbackrec><nl>
<t mgscaleactivatecallbackrec><nl>
<t mggldrawcallbackrec><nl>
<t mgdialogsizecallbackrec><nl>
<t mgtimer><nl>
<t mgtimerfunc><nl>
<t mgeditorfocusvertexfunc><nl>
<t mgcreatefunc><nl>
<t mginputdevicestartfunc><nl>
<t mginputdevicestopfunc><nl>
<t mginputdevicesetinputtypefunc><nl>
<t mginputdevicestartfunc><nl>
<t mgdeviceinputdata><nl>
<t mginputdevice><nl>
<t mggraphicdrawfunc><nl>
<t mggraphicviewdata><nl>
<t mggraphicdrawmode><nl>
<t mghierarchydrawfunc><nl>
<t mghierarchyviewdata><nl>
<t mgglcontext><nl>
<t mghelpcontext><nl>

@group2 New Functions

@group3 Info Functions

@normal
<f mgGetVersion><nl>

@group3 I/O Functions

@normal
<f mgIsDb><nl>

@group3 Attribute Functions

@normal
<f mgGetVtxCoord><nl>
<f mgSetVtxCoord><nl>
<f mgRemoveVtxNormal><nl>

@group3 Input Device Plug-in Tool Class
@normal

<f mgRegisterInputDevice><nl>
<f mgInputDeviceGetHandle><nl>
<f mgInputDeviceSetVertex><nl>
<f mgInputDeviceSetPoint><nl>
<f mgInputDeviceSetButtonStatus><nl>
<f mgInputDeviceSetDeviceData><nl>
<f mgInputDeviceSendEvent><nl>
<f mgInputDeviceGetDeviceData><nl>
<f mgInputDeviceGetButtonStatus><nl>

@group3 Image Importer Plug-in Tool Class
@normal

Function <f mgSetTextureSampleSize> now allows sample sizes of
8 or 16 bits.

<f mgSetTextureMinMax><nl>
<f mgSetTextureTransparentValue><nl>
<f mgSetTextureSignedFlag><nl>
<f mgSetReadImageGeoInfoFunc><nl>
<f mgSetTextureGeoType><nl>
<f mgSetTextureGeoProjection><nl>
<f mgSetTextureGeoEarthModel><nl>
<f mgSetTextureGeoUTMZone><nl>
<f mgSetTextureGeoUTMHemisphere><nl>
<f mgSetTextureGeoImageOrigin><nl>
<f mgSetTextureGeoNumCtlPts><nl>
<f mgSetTextureGeoCtlPt><nl>

@group3 Image Geo Coordinate Access
@normal

<f mgGeoCoordGet><nl>
<f mgGeoCoordAdd><nl>
<f mgGeoCoordDelete><nl>

@group3 Data Extension Site Functions
@normal

<f mgRegisterGraphicDraw><nl>
<f mgRegisterHierarchyDraw><nl>
<f mgRegisterCreate><nl>

@group3 Image Info Functions
@normal

<f mgReadImageInfo><nl>
<f mgGetTextureType><nl>
<f mgGetTextureWidth><nl>
<f mgGetTextureHeight><nl>
<f mgGetTextureSampleSize><nl>
<f mgGetTextureTiledFlag><nl>
<f mgGetTextureMinMax><nl>
<f mgHasTextureTransparentValue><nl>
<f mgGetTextureTransparentValue><nl>
<f mgGetTextureSignedFlag><nl>
<f mgFreeImageInfo><nl>

@group3 Georeferenced Image Info Functions
@normal

<f mgReadImageGeoInfo><nl>
<f mgGetTextureGeoType><nl>
<f mgGetTextureGeoProjection><nl>
<f mgGetTextureGeoEarthModel><nl>
<f mgGetTextureGeoUTMZone><nl>
<f mgGetTextureGeoUTMHemisphere><nl>
<f mgGetTextureGeoImageOrigin><nl>
<f mgGetTextureGeoNumCtlPts><nl>
<f mgGetTextureGeoCtlPt><nl>
<f mgFreeImageGeoInfo><nl>

@group3 General Controls

@normal
<f mgGuiSetToolTip><nl>

@group3 Scale Controls

@normal
<f mgScaleSetValue><nl>
<f mgScaleGetValue><nl>
<f mgScaleSetMinMax><nl>
<f mgScaleGetMinMax><nl>
<f mgScaleSetSpinBuddy><nl>
<f mgScaleSetTextBuddy><nl>
<f mgScaleSetSpinIncrement><nl>
<f mgScaleSetTextFormat><nl>

@group3 Progress Controls

@normal
<f mgProgressSetValue><nl>
<f mgProgressGetValue><nl>
<f mgProgressStepValue><nl>
<f mgProgressSetMinMax><nl>
<f mgProgressGetMinMax><nl>
<f mgProgressSetStepIncrement><nl>

@group3 Text Controls

@normal
<f mgTextSetSpinBuddy><nl>
<f mgTextSetSpinIncrement><nl>
<f mgTextSetTextFormat><nl>

@group3 GL Controls

@normal
<f mgGLSetMouseFunc><nl>
<f mgDrawControl><nl>

@group3 Online Help

@normal
<f mgRegisterHelpFile><nl>
<f mgGuiSetHelpContext><nl>
<f mgShowHelpContext><nl>
<m MTA_HELPCONTEXT><nl>

@group3 Timers

@normal
<f mgRegisterTimer><nl>
<f mgUnregisterTimer><nl>

@group3 Sizing and Positioning Controls and Dialogs

@normal
<f mgGuiGetSize><nl>
<f mgGuiSetSize><nl>
<f mgGuiGetPos><nl>
<f mgGuiSetPos><nl>
<f mgGuiGetViewSize><nl>
<f mgDialogSetAttribute><nl>

@group3 Property Lists for Controls and Dialogs

@normal
<f mgGuiPutProperty><nl>
<f mgGuiGetProperty><nl>
<f mgGuiDeleteProperty><nl>

@group3 Focus Vertex Lists

@normal
<f mgClearFocusVertex><nl>
<f mgFocusVertexListAddItem><nl>
<f mgFocusVertexListDeleteAllItems><nl>
<f mgFocusVertexListDeleteItem><nl>
<f mgGetFocusVertex><nl>
<f mgSetFocusVertex><nl>

@group3 Eyepoint Look At

@normal
<f mgGetCurrentLookAt><nl>
<f mgSetCurrentLookAt><nl>

@group3 Texture Mapping Palette

@normal
<f mgGetTextureMapping><nl>
<f mgIndexOfTextureMapping><nl>
<f mgGetTextureMappingCount><nl>
<f mgNewTextureMapping><nl>
<f mgDelTextureMapping><nl>
<f mgDelTextureMappingByName><nl>
<f mgReadTextureMappingFile><nl>
<f mgWriteTextureMappingFile><nl>

@end
*/

/* module stuff */

/*
@doc MODULE

@submodule Attribute Functions |
List of attribute functions
@synopsis func | ATTRIBUTEFUNC

@submodule Focus Vertex Functions |
List of focus vertex functions
@synopsis func | FOCUSVERTEXFUNC

@submodule Switch Functions |
List of switch functions
@synopsis func | SWITCHFUNC

@submodule Mesh Functions |
List of mesh functions
@synopsis func | MESHFUNC

@submodule EyePoint Functions |
List of eyepoint functions
@synopsis func | EYEFUNC

@submodule Graphics View Functions |
List of graphics view functions
@synopsis func | GRAPHICVIEWFUNC

@submodule Base Functions |
List of basic functions
@synopsis func | BASEFUNC

@submodule Color Functions |
List of color functions
@synopsis func | COLORFUNC

@submodule Extension Functions |
List of texture functions
@synopsis func | EXTENSIONFUNC

@submodule Info Functions |
List of info functions
@synopsis func | INFOFUNC

@submodule Input Device Functions |
List of input device functions
@synopsis func | INPUTDEVFUNC

@submodule I/O Functions |
List of I/O functions
@synopsis func | IOFUNC

@submodule Material Functions |
List of material functions
@synopsis func | MATERIALFUNC

@submodule Light Source Functions |
List of light source functions
@synopsis func | LIGHTSOURCEFUNC

@submodule Light Point Functions |
List of light point functions
@synopsis func | LIGHTPOINTFUNC

@submodule Line Style Functions |
List of light source functions
@synopsis func | LINESTYLEFUNC

@submodule Shader Functions |
List of shader functions
@synopsis func | SHADERFUNC

@submodule Sound Functions |
List of sound functions
@synopsis func | SOUNDFUNC

@submodule Texture Functions |
List of texture functions
@synopsis func | TEXTUREFUNC

@submodule Texture Mapping Functions |
List of texture mapping functions
@synopsis func | TXTRMAPFUNC

@submodule Dynamic Array/Stack Functions |
List of dynamic array/stack functions
@synopsis func | POINTERARRAYFUNC

@submodule Preference Functions |
List of preference functions
@synopsis func | PREFFUNC

@submodule Structure Functions |
List of structure functions
@synopsis func | STRUCFUNC

@submodule Select List Functions |
List of select list functions
@synopsis func | SELECTFUNC

@submodule Geometry Functions |
List of geometry functions
@synopsis func | GEOMETRYFUNC

@submodule Matrix Functions |
List of matrix functions
@synopsis func | MATRIXFUNC

@submodule Projection Functions |
List of projection functions
@synopsis func | PROJECTIONFUNC

@submodule Matrix Stack Functions |
List of matrix stack functions
@synopsis func | MATRIXSTACKFUNC

@submodule Resource Functions |
List of functions used to access the contents of a resource, including
dialogs, pixmaps and string definitions.
@synopsis func | RESOURCEFUNC

@submodule Dialog Functions |
List of functions used to manipulate all classes of dialogs.
@synopsis func | DIALOGFUNC

@submodule General Controls |
List of functions applicable to all classes of controls.
@synopsis func | GENERALCONTROLFUNC

@submodule Text Controls |
List of functions used to manipulate text controls.
@synopsis func | TEXTCONTROLFUNC

@submodule GL Controls |
List of functions used to manipulate GL controls.
@synopsis func | GLFUNC

@submodule Toggle Button Controls |
List of functions used to manipulate toggle button controls.
@synopsis func | TOGGLEBUTTONCONTROLFUNC

@submodule Menu Controls |
List of functions used to manipulate menu controls.
@synopsis func | MENUCONTROLFUNC

@submodule Option Menu Controls |
List of functions used to manipulate option menu controls.
@synopsis func | OPTIONMENUCONTROLFUNC

@submodule List Controls |
List of functions used to manipulate list controls.
@synopsis func | LISTCONTROLFUNC

@submodule Tab Ruler Controls |
List of functions used to manipulate tab ruler controls.
@synopsis func | TABRULERCONTROLFUNC

@submodule Scale Controls |
List of functions used to manipulate scale controls.
@synopsis func | SCALECONTROLFUNC

@submodule Progress Controls |
List of functions used to manipulate progress controls.
@synopsis func | PROGRESSFUNC

@submodule Notifier Functions |
List of notifier functions
@synopsis func | NOTIFIERFUNC

@submodule Tool Action Functions |
List of tool action functions
@synopsis func | TOOLACTIONFUNC

@submodule Tool Registration Functions |
List of tool registration functions
@synopsis func | TOOLREGISTERFUNC

@submodule Parameter Block Functions |
List of parameter block functions
@synopsis func | PARAMETERFUNC

@submodule Extension Registration Functions |
List of data extension registration functions
@synopsis func | SITEREGISTERFUNC

@submodule Editor Context Functions |
List of editor context functions
@synopsis func | EDITORCONTEXTFUNC

@submodule Construction Functions |
List of Construction functions
@synopsis func | CONSTRUCTIONFUNC

@submodule Tool Activation Functions |
List of tool activation functions
@synopsis func | TOOLACTIVATIONFUNC

@submodule Timer Functions |
List of Timer functions
@synopsis func | TIMERFUNC

@submodule Data Dictionary Functions |
List of data dictionary functions
@synopsis func | DATADICTIONARYFUNC

@submodule Online Help Functions |
List of online help functions
@synopsis func | ONLINEHELPFUNC

@submodule License Functions |
List of license functions
@synopsis func | LICENSEFUNC

*/

/* index stuff */

/*

@doc INDEX

@contents1 |

@menu Index |
@subindex Introduction | mgapi.htm#Introduction TARGET=content
@subindex OpenFlight API Version | mgapi.htm#OpenFlight_API_Version TARGET=content
@subindex OpenFlight Format Version | mgapi.htm#OpenFlight_Format_Version TARGET=content
@subindex Release Notes | mgapi.htm#OpenFlight_API_Release_Notes TARGET=content
@subindex FAQ | mgapi.htm#OpenFlight_API_FAQ TARGET=content
@subindex Required Plugin Symbols |
@subindex Data Types |
@subindex Constants |
@subindex Macros |
@subindex Obsolete API |
@subindex Deprecated API |
@subindex Function Categories |
@subindex Functions |
@subindex OpenFlight Data Dictionary | ../openflightdd/default.htm TARGET=_blank

@module Data Types |
@index struct,structtype,enum,enumtype,flagtype,type,uniontype,cb |

@module Constants | 
@index msg |

@module Macros | 
@index macro |

@module Deprecated API |
@index deprecated | 

@module Obsolete API |
@index obsolete |

@module Required Plugin Symbols |
This section lists all the symbols a plug-in module must declare
to be recognized as a valid plug-in module.
@index func | REQUIREDFUNC

@module Function Categories |
@linkindex submodule | | s/HREF=mgapi.htm#(.*?) TARGET=content/HREF=#$1/g

@module Functions |
@index func |

*/

