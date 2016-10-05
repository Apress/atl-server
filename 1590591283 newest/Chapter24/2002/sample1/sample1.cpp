// sample1.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <atlsmtpconnection.h>
#include <atlmime.h>

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);
	{
		CSMTPConnection smtpConnection;		
		if (!smtpConnection.Connect("localhost"))
		{
			printf("error connecting to SMTP server\n");
			return 1;
		}
	
		if (!smtpConnection.SendSimple(	"recipient@atlserverworld.com", 
										"sender@atlserverworld.com", 
										"Hello World!", 
										"Sending email with ATL Server is easy!"))
		{
			printf("error sending message!\n");
		}
		else
		{
			printf("message sent!\n");
		}

		smtpConnection.Disconnect();

		CMimeMessage msg;
		msg.AttachFile("newemail.wav");
		CString contentType;
		::GetContentTypeFromFileName("newemail.wav", contentType);
		printf("->%s\n", contentType);
	}
	CoUninitialize();
	return 0;
}
