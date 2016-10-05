// UserInput.h : Defines the ATL Server request handler class
//
#pragma once

[ request_handler("Default") ]
class CUserInputHandler
{
private:
    CValidateContext m_validateContext;
    bool             m_formHasBeenSubmitted;

protected:
	// Put protected members here

public:
    HTTP_CODE ValidateAndExchange()
    {    
        m_HttpResponse.SetContentType("text/html");

        const CHttpRequestParams *requestParams(NULL);
        if (m_HttpRequest.GetMethod() == CHttpRequest::HTTP_METHOD::HTTP_METHOD_POST)
        {        
            requestParams = &(this->m_HttpRequest.GetFormVars());
        }
        else
        {      
            requestParams = &(this->m_HttpRequest.GetQueryParams());
        }

        m_formHasBeenSubmitted = (requestParams->GetCount() == 0) ?  false : true;
    
        if (!m_formHasBeenSubmitted)
        {   
            return HTTP_SUCCESS;
        }   

        m_validateContext.m_dwFlags = VALIDATION_S_EMPTY | VALIDATION_E_PARAMNOTFOUND;

        CString fruit;
        requestParams->Exchange("fruit", &fruit, &m_validateContext);

        bool isOrganic;
        requestParams->Exchange("is_organic", &isOrganic, &m_validateContext);
        
        int quantity;
        requestParams->Exchange("quantity", &quantity, &m_validateContext);
    
        return HTTP_SUCCESS;
    } 

protected:

    [tag_name("HasErrors")]
    HTTP_CODE OnHasErrors()
    {
        if (!m_formHasBeenSubmitted)
        {   
            return HTTP_S_FALSE;
        }   
        else
        {      
            return (!m_validateContext.ParamsOK()) ? HTTP_SUCCESS : HTTP_S_FALSE;
        }
    }
    
    [tag_name("GetError")]
    HTTP_CODE OnGetError(int *index)
    {    
        if (!m_formHasBeenSubmitted)
        {   
            return HTTP_SUCCESS;
        }   
 
        DWORD   errorType; 
        CString szName;
        if (!m_validateContext.GetResultAt(*index, szName, errorType))
        {
            return HTTP_SUCCESS;
        }
        else
        {
            m_HttpResponse << "A value for " << ( const char*) szName;
    
            switch (errorType)
            {
                case VALIDATION_S_EMPTY:            
                    m_HttpResponse << " cannot be an empty value!";
                    break;
     
                case VALIDATION_E_PARAMNOTFOUND:                
                    m_HttpResponse << " was not found!";
                    break;
     
                case VALIDATION_E_INVALIDPARAM:                
                    m_HttpResponse << " was entered, but in an incorrect format!";
                    break;
     
                default:            
                    m_HttpResponse << " was not a valid value!";
                    break; 
            }
        }
           
        return HTTP_SUCCESS;
    }   	
}; // class CUserInputHandler
