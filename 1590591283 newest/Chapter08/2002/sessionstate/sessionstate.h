// sessionstate.h : Defines the ATL Server request handler class
//
#pragma once

[ request_handler("Default") ]
class CsessionstateHandler
{
private:
	// Put private members here
	// uncomment the service declaration(s) if you want to use
	// a service that was generated with your ISAPI extension

	// Session service support
	CComPtr<ISessionStateService> m_spSessionSvc;
	CComPtr<ISession> m_spSession;

protected:
	// Put protected members here

public:
	// Put public members here

	HTTP_CODE ValidateAndExchange()
	{
		// TODO: Put all initialization and validation code here
		
		// Set the content-type
		m_HttpResponse.SetContentType("text/html");

		// Get the ISessionStateService from the ISAPI extension
		if (FAILED(m_spServiceProvider->QueryService(__uuidof(ISessionStateService), 
													 &m_spSessionSvc)))
			return HTTP_FAIL;
		
		// see if we have a session
		const CCookie& sessionCookie = m_HttpRequest.Cookies("session");
	
		if (sessionCookie.IsEmpty())
		{
			// we don't have a cookie by that name so create a new session
			CHAR  sessionName[CSessionNameGenerator::MIN_SESSION_KEY_LEN + 1];
			DWORD sessionLen = 0;
			if (FAILED(m_spSessionSvc->CreateNewSession(sessionName, &sessionLen, &m_spSession)))
			{
				// could not create a session, return an error
				return HTTP_S_FALSE;
			}
			sessionName[sessionLen - 1] = 0;
			// send the session name back in a cookie
			m_HttpResponse.AppendCookie("session", sessionName);
		}
		else
		{
			// we have a current session
			CString sessionName;
			if (!sessionCookie.GetValue(sessionName))
			{
				// could not get a value from our session name cookie
				return HTTP_S_FALSE;
			}

			if (FAILED(m_spSessionSvc->GetSession(sessionName, &m_spSession)))
			{
				// could not create a session, return an error
				return HTTP_S_FALSE;
			}
		}
		
		return HTTP_SUCCESS;
	}
 
protected:
	// Here is an example of how to use a replacement tag with the stencil processor
	[ tag_name(name="Hello") ]
	HTTP_CODE OnHello(void)
	{
		m_HttpResponse << "Hello World!";
		return HTTP_SUCCESS;
	}
}; // class CsessionstateHandler
