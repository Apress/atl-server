========================================================================
       ATL SERVER : RemoteWeatherService Project Overview
========================================================================

AppWizard has created this RemoteWeatherService application for you.  This application
not only demonstrates the basics of using the ATL Server Classes but is also a starting 
point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your RemoteWeatherService application.

RemoteWeatherService.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.
 
RemoteWeatherService.cpp
    This file is your root ISAPI Extension file.  It contains the ISAPI Extension code 
    and additional ATL Server code.  You can customize the ATL Server code to the 
    specific needs of your projects.
 
RemoteWeatherService.h
    This file contains your ATL Server request handler class customized based on the 
    options you chose in the the ATL Server Wizard.
 
RemoteWeatherService.def
    This file contains the functions that will be exported from your ISAPI Extension DLL.  
    This includes the ISAPI Extension functions HttpExtensionProc, GetExtensionVersion, 
    and TerminateExtension. These functions are delegated to the instance of your
    CIsapiExtension class.
 
RemoteWeatherService.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It contains the version resource for your ISAPI DLL, and it
    also includes the atlsrv.rc file for the language you specified in the wizard.  
    This file can be directly edited in Microsoft Visual C++.
 
RemoteWeatherService.disco
    This file contains information that allows your web service to be exposed via
    web servers supporting the DISCO protocol.
	
RemoteWeatherService.htm
    This is a webpage containing a description of your web service.  It is referenced
    in RemoteWeatherService.disco.  You should update this file when adding or
    removing methods from your web service.

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
