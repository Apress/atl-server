========================================================================
       ATL SERVER : WebJukeboxIsapi Project Overview
========================================================================

AppWizard has created this WebJukeboxIsapi application for you.  This application
not only demonstrates the basics of using the ATL Server Classes but is also a starting 
point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your WebJukeboxIsapi application.

WebJukeboxIsapi.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.
 
WebJukeboxIsapi.cpp
    This file is your root ISAPI Extension file.  It contains the ISAPI Extension code 
    and additional ATL Server code.  You can customize the ATL Server code to the 
    specific needs of your projects.
 
WebJukeboxIsapi.def
    This file contains the functions that will be exported from your ISAPI Extension DLL.  
    This includes the ISAPI Extension functions HttpExtensionProc, GetExtensionVersion, 
    and TerminateExtension. These functions are delegated to the instance of your
    CWebJukeboxExtension class.
    The DLL also exports functions needed for perfmormance monitoring 
    support, however these do not appear in the WebJukeboxIsapi.def file.
 
WebJukeboxIsapi.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It contains the version resource for your ISAPI DLL, and it
    also includes the atlsrv.rc file for the language you specified in the wizard.  
    This file can be directly edited in Microsoft Visual C++.
 
WebJukeboxextension.h
    This file contains your CIsapiExtension derived ISAPI Extension class:
    CWebJukeboxExtension that is customized based on the options you chose 
    in the AppWizard.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    and a precompiled types file.

/////////////////////////////////////////////////////////////////////////////

Other notes:
 
AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
