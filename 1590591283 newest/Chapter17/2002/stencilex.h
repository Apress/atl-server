#pragma once

#define STENCIL_ANDSTART         (STENCIL_USER_TOKEN_BASE + 0x00000001)
#define STENCIL_ANDPART          (STENCIL_USER_TOKEN_BASE + 0x00000002)
#define STENCIL_ORSTART          (STENCIL_USER_TOKEN_BASE + 0x00000003)
#define STENCIL_ORPART           (STENCIL_USER_TOKEN_BASE + 0x00000004)
#define STENCIL_IFNOT            (STENCIL_USER_TOKEN_BASE + 0x00000005)

#include <atlstencil.h>

class CCustomStencil : public CHtmlStencil
{
public:

    CCustomStencil(IAtlMemMgr *pMemMgr) throw()
        :CHtmlStencil(pMemMgr)
    {
    }

    // Parse the next method out of the tag
    // if preceded by a '!' then treat it as 'not Method' when evaluating
    bool GetNextMethodInfo(LPSTR *ppszStart, LPSTR szMethodName, LPSTR szHandlerName, DWORD *pdwNot) throw()
    {
        *pdwNot = 0;
        *szMethodName = '\0';
        *szHandlerName = '\0';

        LPSTR szStart = *ppszStart;

        char szTag[ATL_MAX_METHOD_NAME_LEN];
        LPSTR pszTag = szTag;
        LPSTR pszTagEnd = NULL;

        // handle {{! MethodName ...}} syntax
        if (*szStart == '!')
        {
            *pdwNot = 1;
            szStart++;

            // skip spaces between '!' and method name
            while (_istspace(*szStart))
                szStart++;
        }

        // get the tag name
        while (!_istspace(*szStart) && *szStart != '}')
            *pszTag++ = *szStart++;

        pszTagEnd = pszTag-1;
        pszTag = szTag;
        
        // get the handler and method names
        if (HTTP_SUCCESS != GetHandlerAndMethodNames(pszTag, pszTagEnd, 
                                    szMethodName, szHandlerName))
        {
            // method or handler is invalid
            return false;
        }

        // skip spaces before the next method
        while (_istspace(*szStart))
            szStart++;

        // set out parameter so we start where we left off
        *ppszStart = szStart;

        return true;
    }

    // if_and and if_or parse very similarly
    // this function will iterate over the methods in tag and add them as tokens
    // syntax is:
    // {{[if_and|if_or] ([!]<method_name>)*}}
    // the functionality is implemented by adding a STENCIL_ANDSTART or STENCIL_ORSTART 
    // token to mark the beginning of an {{if_and ...}} or {{if_or ...}} block
    // we then add STENCIL_ANDPART or STENCIL_ORPART tokens to represent
    // components of the tag
    // For example:
    //   {{if_and True !False TrueAgain TrueOrNot}}
    //   would be represented by the following tokens:
    //     STENCIL_ANDSTART : StencilToken::szMethodName = True
    //     STENCIL_ANDPART  : StencilToken::szMethodName = False 
    //                          (with StencilToken::dwData set to 1 to signify the '!')
    //     STENCIL_ANDPART  : StencilToken::szMethodName = TrueAgain
    //     STENCIL_ANDPART  : StencilToken::szMethodName = TrueOrNot
    //   when we render the token, we will loop over the parts -- see RenderAnd for details
    int ParseAndOr(LPSTR szTokenStart, DWORD dwTokenLen, DWORD dwTokenStart, DWORD dwTokenPart,
        LPSTR szTokenEnd, DWORD *pBlockStack, DWORD *pdwTop) throw()
    {
        LPSTR szStart = szTokenStart;
        LPSTR szEnd = szTokenEnd;

        FindTagArgs(szStart, szEnd, dwTokenLen);

        char szMethodName[ATL_MAX_METHOD_NAME_LEN];
        char szHandlerName[ATL_MAX_HANDLER_NAME_LEN];
        DWORD dwNot = 0;

        // at least the first method must be okay
        if (!GetNextMethodInfo(&szStart, szMethodName, szHandlerName, &dwNot))
            return -1;

        // add the start token -- we store information about whether or not it's a '! <method_name>' call
        // by setting the StencilToken::dwData member to 1 if it is a '! <method_name>' call
        // save the start index (dwIndexStart) so we close the block properly
        DWORD dwIndexStart = AddToken(szTokenStart, szTokenEnd, dwTokenStart, 
            szHandlerName, szMethodName, STENCIL_INVALIDINDEX, STENCIL_INVALIDINDEX,
            dwNot, NULL, STENCIL_BASIC_MAP);

        DWORD dwIndexRet = STENCIL_INVALIDINDEX;

        // while there are "AND/OR" components
        while (GetNextMethodInfo(&szStart, szMethodName, szHandlerName, &dwNot))
        {
            // add a component token -- we store information about whether or not it's a '! <method_name>' call
            // by setting the StencilToken::dwData member to 1 if it is a '! <method_name>' call
            dwIndexRet = AddToken(szTokenStart, szTokenEnd, dwTokenPart, 
                szHandlerName, szMethodName, STENCIL_INVALIDINDEX, STENCIL_INVALIDINDEX,
                dwNot, NULL, STENCIL_BASIC_MAP);

            if (szStart > szEnd)
                break;
        }

        // push the token on the block stack so that we can
        // close the block properly
        return PushToken(pBlockStack, pdwTop, dwIndexStart);
    }

    // delegate to ParseAndOr
    int ParseAnd(LPSTR szTokenStart, 
        LPSTR szTokenEnd, DWORD *pBlockStack, DWORD *pdwTop) throw()
    {
        return ParseAndOr(szTokenStart, sizeof("if_and")-1, STENCIL_ANDSTART, STENCIL_ANDPART,
            szTokenEnd, pBlockStack, pdwTop);
    }

    // delegate to ParseAndOr
    int ParseOr(LPSTR szTokenStart, 
        LPSTR szTokenEnd, DWORD *pBlockStack, DWORD *pdwTop) throw()
    {
        return ParseAndOr(szTokenStart, sizeof("if_or")-1, STENCIL_ORSTART, STENCIL_ORPART,
            szTokenEnd, pBlockStack, pdwTop);
    }

    // modify the behavior of the {{endif}} tag to accept if_and, if_or, and if_not
    DWORD ParseEndEx(LPSTR szTokenStart, LPSTR szTokenEnd, DWORD *pBlockStack, DWORD *pdwTop) throw()
    {
        // first check if it is an {{if ...}} or an {{else}}
        DWORD dwIndexTop = ParseEndIf(szTokenStart, szTokenEnd, pBlockStack, pdwTop);
        if (dwIndexTop == STENCIL_INVALIDINDEX)
        {
            // if not check {{if_and ...}}
            dwIndexTop = CheckTopAndPop(pBlockStack, pdwTop, STENCIL_ANDSTART);
            if (dwIndexTop == STENCIL_INVALIDINDEX)
            {
                // check {{if_or ...}}
                dwIndexTop = CheckTopAndPop(pBlockStack, pdwTop, STENCIL_ORSTART);
                if (dwIndexTop == STENCIL_INVALIDINDEX)
                {
                    // check {{if_not ...}}
                    dwIndexTop = CheckTopAndPop(pBlockStack, pdwTop, STENCIL_IFNOT);
                    if (dwIndexTop == STENCIL_INVALIDINDEX)
                        return dwIndexTop;
                }
            }

            // if it was if_and, if_or, or if_not, add a new token
            DWORD dwIndex = AddToken(NULL, NULL, STENCIL_CONDITIONALEND);
            GetToken(dwIndexTop)->dwLoopIndex = dwIndex;
            GetToken(dwIndex)->dwLoopIndex = dwIndexTop;
            dwIndexTop = dwIndex;
        }

        return dwIndexTop;
    }

    // modify the behavior of the {{else}} tag to accept if_and, if_or, and if_not
    DWORD ParseElseEx(LPSTR szTokenStart, LPSTR szTokenEnd, DWORD *pBlockStack, DWORD *pdwTop) throw()
    {
        // first check if it is an {{if ...}}
        DWORD dwTopIndex = ParseElse(szTokenStart, szTokenEnd, pBlockStack, pdwTop);
        if (dwTopIndex == STENCIL_INVALIDINDEX)
        {
            // if not check {{if_and ...}}
            dwTopIndex = CheckTopAndPop(pBlockStack, pdwTop, STENCIL_ANDSTART);
            if (dwTopIndex == STENCIL_INVALIDINDEX)
            {
                // check {{if_or ...}}
                dwTopIndex = CheckTopAndPop(pBlockStack, pdwTop, STENCIL_ORSTART);
                if (dwTopIndex == STENCIL_INVALIDINDEX)
                {
                    // check {{if_not ...}}
                    dwTopIndex = CheckTopAndPop(pBlockStack, pdwTop, STENCIL_IFNOT);
                    if (dwTopIndex == STENCIL_INVALIDINDEX)
                        return dwTopIndex;
                }
            }

            // if it was if_and, if_or, or if_not, add a new token
            DWORD dwIndex = AddToken(NULL, NULL, STENCIL_CONDITIONALELSE);
            GetToken(dwTopIndex)->dwLoopIndex = dwIndex;
            dwTopIndex = PushToken(pBlockStack, pdwTop, dwIndex);
        }

        return dwTopIndex;
    }

    // add an {{if_not ...}} tag, the syntax is:
    // {{if_not <method_name>}}
    // it will execute the block in the {{if_not ...}} if the method called return HTTP_S_FALSE
    DWORD ParseIfNot(LPSTR szTokenStart, LPSTR szTokenEnd, DWORD *pBlockStack, DWORD *pdwTop) throw()
    {
        // find the beginning and end of the method name
        FindTagArgs(szTokenStart, szTokenEnd, sizeof("if_not")-1);

        // delegate to ParseReplacement with the STENCIL_IFNOT value
        DWORD dwIndex = ParseReplacement(szTokenStart, szTokenEnd, STENCIL_IFNOT);
        if (dwIndex == STENCIL_INVALIDINDEX)
            return dwIndex;

        // push the token onto the stack
        return PushToken(pBlockStack, pdwTop, dwIndex);
    }

    // override parse token to understand the new tags:
    //   {{if_and ...}}
    //   {{if_or ...}}
    //   {{if_not ...}}
    //
    // override to change the behavior of the following tags:
    //   {{endif}}
    //   {{else}}
    // to accept the new tags
    virtual PARSE_TOKEN_RESULT ParseToken(LPSTR szTokenStart, 
        LPSTR szTokenEnd, DWORD *pBlockStack, DWORD *pdwTop) throw()
    {
        LPCSTR pStart = szTokenStart;
        pStart += 2; //skip curlies
        pStart = SkipSpace(pStart, GetCodePage());
        DWORD dwLen = (DWORD)(szTokenEnd - szTokenStart);

        int nIndex = -1;

        if (CheckTag("if_and", sizeof("if_and")-1, pStart, dwLen))
            nIndex = ParseAnd(szTokenStart, szTokenEnd, pBlockStack, pdwTop);
        else if (CheckTag("if_or", sizeof("if_or")-1, pStart, dwLen))
            nIndex = ParseOr(szTokenStart, szTokenEnd, pBlockStack, pdwTop);
        else if (CheckTag("endif", sizeof("endif")-1, pStart, dwLen))
            nIndex = ParseEndEx(szTokenStart, szTokenEnd, pBlockStack, pdwTop);
        else if (CheckTag("else", sizeof("else")-1, pStart, dwLen))
            nIndex = ParseElseEx(szTokenStart, szTokenEnd, pBlockStack, pdwTop);
        else if (CheckTag("if_not", sizeof("if_not")-1, pStart, dwLen))
            nIndex = ParseIfNot(szTokenStart, szTokenEnd, pBlockStack, pdwTop);
        else 
        {
            // delegate to base class
            return __super::ParseToken(szTokenStart, szTokenEnd,
                pBlockStack, pdwTop);
        }

        if (nIndex < 0)
            return INVALID_TOKEN;
        return RESERVED_TOKEN;
    }

    // override FinishParseReplacements to do error handling for the new tags:
    //   {{if_and ...}}
    //   {{if_or ...}}
    //   {{if_not ...}}
    bool FinishParseReplacements() throw()
    {
        DWORD dwSize = GetTokenCount();

        // iterate over the tokens
        for (DWORD dwIndex = 0; dwIndex < dwSize; dwIndex++)
        {
            StencilToken& token = *(GetToken(dwIndex));

            // only modify the new tags
            bool bModify = (token.type == STENCIL_ANDPART || 
                token.type == STENCIL_ORPART || 
                token.type == STENCIL_IFNOT ||
                 token.type == STENCIL_ANDSTART || 
                 token.type == STENCIL_ORSTART);

            // unclosed blocks are conditional start 
            // tags with the dwLoopIndex == STENCIL_INVALIDOFFSET
            bool bUnclosedBlock = 
                ((token.type == STENCIL_ANDSTART ||
                token.type == STENCIL_ORSTART || 
                token.type == STENCIL_IFNOT) 
                && token.dwLoopIndex == STENCIL_INVALIDOFFSET);

            if (bModify && token.szMethodName[0] && 
                (token.dwFnOffset == STENCIL_INVALIDOFFSET || bUnclosedBlock))
            {
                // if it is an unclosed block or if we cannot resolve the 
                // replacement method convert to text tags
                if (bUnclosedBlock || 
                    m_pReplacer->FindReplacementOffset(
                        token.szMethodName, &token.dwFnOffset, 
                        token.szHandlerName, &token.dwObjOffset, 
                        &token.dwMap, 
                        (void **)&token.dwData, m_pMemMgr) != HTTP_SUCCESS)
                {
                    DWORD dwStartIndex = dwIndex;

                    // if the token is STENCIL_ANDPART or STENCIL_ORPART, 
                    // find the start of the block
                    if (token.type == STENCIL_ANDPART || 
                        token.type == STENCIL_ORPART)
                    {
                        DWORD dwStartType = 
                            (token.type == STENCIL_ANDPART ? 
                            STENCIL_ANDSTART : STENCIL_ORSTART);
                        DWORD dwStartIndex = dwIndex-1;

                        while (IsValidIndex(dwStartIndex) && 
                            GetToken(dwStartIndex)->type != dwStartType)
                        {
                            --dwStartIndex;
                        }

                        if (GetToken(dwStartIndex)->type != dwStartType)
                            dwStartIndex = dwIndex;
                    }

                    DWORD dwLoopIndex = GetToken(dwStartIndex)->dwLoopIndex;

                    // if STENCIL_ANDSTART or STENCIL_ORSTART, 
                    // convert component tokens to STENCIL_CONDITIONALEND, 
                    // so they are skipped  during rendering and set 
                    // szMethodName to an empty string, so it is ignored by
                    // the base class's FinishParseReplacements
                    if (GetToken(dwStartIndex)->type == STENCIL_ANDSTART || 
                        GetToken(dwStartIndex)->type == STENCIL_ORSTART)
                    {
                        DWORD dwNextToken = dwIndex+1;
                        while (dwNextToken != dwLoopIndex && 
                            dwNextToken != STENCIL_INVALIDINDEX)
                        {
                            if (GetToken(dwNextToken)->type 
                                    == STENCIL_ANDPART || 
                                GetToken(dwNextToken)->type 
                                    == STENCIL_ORPART)
                            {
                                GetToken(dwNextToken)->type = 
                                    STENCIL_CONDITIONALEND;
                                GetToken(dwNextToken)->szMethodName[0] = 0;
                            }

                            dwNextToken++;
                        }
                    }

                    // unresolved replacement, convert it to a text token
                    GetToken(dwStartIndex)->type = STENCIL_TEXTTAG;
                    GetToken(dwStartIndex)->szMethodName[0] = 0;

                    // convert all linked tokens to text tokens as well
                    // this includes: endif, else, endwhile
                    while (dwLoopIndex != dwIndex && 
                        dwLoopIndex != STENCIL_INVALIDINDEX)
                    {
                        GetToken(dwLoopIndex)->type = STENCIL_TEXTTAG;
                        GetToken(dwLoopIndex)->szMethodName[0] = 0;
                        dwLoopIndex = GetToken(dwLoopIndex)->dwLoopIndex;
                    }
                }
            }
        }

        // call the base FinishParseReplacements to handle other tags
        return __super::FinishParseReplacements();
    }

    // render the {{if_and ...}} tag
    DWORD RenderAnd(
        DWORD dwIndex,
        ITagReplacer *pReplacer,
        DWORD *pdwErrorCode) const throw()
    {
        const StencilToken* ptoken = GetToken(dwIndex);
        DWORD dwNextToken = STENCIL_INVALIDINDEX;
        DWORD dwErrorCode = HTTP_SUCCESS;

        if (!ptoken)
            return STENCIL_INVALIDINDEX;

        // ensure that the function offset is valid
        if (ptoken->type == STENCIL_ANDSTART && 
            ptoken->dwFnOffset == STENCIL_INVALIDINDEX)
        {
            dwErrorCode = 
                HTTP_ERROR(500, ISE_SUBERR_STENCIL_INVALIDFUNCOFFSET);
        }
        else
        {    
            // ensure that we end with and {{endif}} or and {{else}}
            if (ptoken->dwLoopIndex == STENCIL_INVALIDINDEX)
            {
                dwErrorCode = HTTP_ERROR(500, ISE_SUBERR_STENCIL_MISMATCHIF);
            }
            else
            {
                // points to the end of the loop
                DWORD dwLoopIndex = ptoken->dwLoopIndex; 
                DWORD dwErr;

                // loop over the components of the if_and
                do
                {
                    // call the replacement method
                    dwErr = pReplacer->RenderReplacement(ptoken->dwFnOffset, 
                        ptoken->dwObjOffset, 
                        ptoken->dwMap, 
                        (void *)ptoken->dwData);

                    // check if it is'! <method_name>' call
                    if (ptoken->dwData)
                    {
                        // invert the return code
                        if (dwErr == HTTP_S_FALSE)
                            dwErr = HTTP_SUCCESS;
                        else if (dwErr == HTTP_SUCCESS)
                            dwErr = HTTP_S_FALSE;
                    }
                    
                    // short-circuit on failure
                    if (dwErr)
                        break;

                    // go to the next token
                    dwIndex++;

                    // ensure that the token is valid
                    if (STENCIL_SUCCESS == (dwErrorCode = IsValidIndex(dwIndex)))
                    {
                        ptoken = GetToken(dwIndex);
                    }
                    else
                    {
                        dwErr = dwErrorCode;
                        break;
                    }
                    
                    // loop until we reach the end of the {{if_and ...}} methods
                } while (ptoken->type == STENCIL_ANDPART);

                if (!dwErr)
                {
                    // if successful, dwIndex is the index of the
                    // first token inside the {{if_and ...}} block
                    dwNextToken = dwIndex;
                    dwErrorCode = HTTP_SUCCESS;
                }
                else if (dwErr == HTTP_S_FALSE)
                {
                    // if we failed, jump to the end of the block 
                    // ({{else}} or {{endif}})
                    // and increment by one
                    dwNextToken = dwLoopIndex+1;
                    dwErrorCode = HTTP_SUCCESS;
                }
                else
                {
                    // an error has occurred
                    dwNextToken = STENCIL_INVALIDINDEX;
                    dwErrorCode = dwErr;
                }
            }
        }

        if (pdwErrorCode)
            *pdwErrorCode = dwErrorCode;

        return dwNextToken;
    }

    // render the {{if_or ...}} tag
    DWORD RenderOr(
        DWORD dwIndex,
        ITagReplacer *pReplacer,
        DWORD *pdwErrorCode) const throw()
    {
        const StencilToken* ptoken = GetToken(dwIndex);
        DWORD dwNextToken = STENCIL_INVALIDINDEX;
        DWORD dwErrorCode = HTTP_SUCCESS;

        if (!ptoken)
            return STENCIL_INVALIDINDEX;

        // ensure that the function offset is valid
        if (ptoken->type == STENCIL_ORSTART && ptoken->dwFnOffset == STENCIL_INVALIDINDEX)
        {
            dwErrorCode = HTTP_ERROR(500, ISE_SUBERR_STENCIL_INVALIDFUNCOFFSET);
        }
        else
        {    
            // ensure that we end with and {{endif}} or and {{else}}
            if (ptoken->dwLoopIndex == STENCIL_INVALIDINDEX)
            {
                dwErrorCode = HTTP_ERROR(500, ISE_SUBERR_STENCIL_MISMATCHIF);
            }
            else
            {
                DWORD dwLoopIndex = ptoken->dwLoopIndex; // points to the end of the loop
                DWORD dwErr;

                // loop over the components of the if_or
                do
                {
                    // call the replacement method
                    dwErr = pReplacer->RenderReplacement(ptoken->dwFnOffset, 
                        ptoken->dwObjOffset, ptoken->dwMap, (void *)ptoken->dwData);

                    // check if it is'! <method_name>' call
                    if (ptoken->dwData)
                    {
                        // invert the return code
                        if (dwErr == HTTP_S_FALSE)
                            dwErr = HTTP_SUCCESS;
                        else if (dwErr == HTTP_SUCCESS)
                            dwErr = HTTP_S_FALSE;
                    }
                    
                    // short-circuit on success
                    if (!dwErr)
                        break;

                    // go to the next token
                    dwIndex++;

                    // ensure that the token is valid
                    if (STENCIL_SUCCESS == (dwErrorCode = IsValidIndex(dwIndex)))
                    {
                        ptoken = GetToken(dwIndex);
                    }
                    else
                    {
                        dwErr = dwErrorCode;
                        break;
                    }
                    
                } while (ptoken->type == STENCIL_ORPART); 
                // loop until we reach the end of the {{if_and ...}} methods

                if (!dwErr)
                {
                    // if successful, dwIndex is the index of the first of the
                    // {{if_or ...}} tokens to return success
                    dwErrorCode = HTTP_SUCCESS;
                    if (ptoken->type == STENCIL_ORPART || ptoken->type == STENCIL_ORSTART)
                    {
                        dwIndex++;

                        // loop over the remaining tokens until we reach the end
                        while ((STENCIL_SUCCESS == (dwErrorCode = IsValidIndex(dwIndex))) && 
                            (GetToken(dwIndex)->type == STENCIL_ORPART))
                        {
                            dwIndex++;
                        }
                    }

                    // if there was an error in reaching the end of the {{if_or ...}}
                    // components, return an error code
                    if (!dwErrorCode)
                        dwNextToken = dwIndex;
                    else
                        dwNextToken = STENCIL_INVALIDINDEX;
                }
                else if (dwErr == HTTP_S_FALSE)
                {
                    // if all of the methods failed, jump to the end of the loop
                    dwNextToken = dwLoopIndex+1;
                    dwErrorCode = HTTP_SUCCESS;
                }
                else
                {
                    // otherwise, an error occurred
                    dwNextToken = STENCIL_INVALIDINDEX;
                    dwErrorCode = dwErr;
                }
            }
        }

        if (pdwErrorCode)
            *pdwErrorCode = dwErrorCode;

        return dwNextToken;
    }

    // render the {{if_not ...}} tag
    DWORD RenderIfNot(
        DWORD dwIndex,
        ITagReplacer *pReplacer,
        DWORD *pdwErrorCode) const throw()
    {
        const StencilToken* ptoken = GetToken(dwIndex);
        DWORD dwNextToken = STENCIL_INVALIDINDEX;
        DWORD dwErrorCode = HTTP_SUCCESS;

        if (!ptoken)
            return STENCIL_INVALIDINDEX;

        // ensure the function is valid
        if (ptoken->type == STENCIL_IFNOT && 
            ptoken->dwFnOffset == STENCIL_INVALIDINDEX)
        {
            dwErrorCode = 
                HTTP_ERROR(500, ISE_SUBERR_STENCIL_INVALIDFUNCOFFSET);
        }
        else
        {
            // ensure that we end with an {{endif}} or an {{else}}
            if (ptoken->dwLoopIndex == STENCIL_INVALIDINDEX)
            {
                dwErrorCode = 
                    HTTP_ERROR(500, ISE_SUBERR_STENCIL_MISMATCHIF);
            }
            else
            {
                // points to the end of the loop
                DWORD dwLoopIndex = ptoken->dwLoopIndex; 

                // Call the replacement method.
                // If it returns HTTP_S_FALSE, we render everything up to
                //  the end of the conditional. 
                // if it returns HTTP_SUCCESS, the condition is not met 
                // and we render the else part if it exists or jump past 
                // the endif otherwise
                DWORD dwErr = pReplacer->RenderReplacement(ptoken->dwFnOffset, 
                    ptoken->dwObjOffset, ptoken->dwMap, (void *)ptoken->dwData);

                if (dwErr == HTTP_S_FALSE)
                {
                    // if the method returns false, execute the block
                    dwNextToken = dwIndex+1;
                    dwErrorCode = HTTP_SUCCESS;
                }
                else if (dwErr == HTTP_SUCCESS)
                {
                    // if the method returns true, 
                    // jump to the end of the block 
                    dwNextToken = dwLoopIndex+1;
                    dwErrorCode = HTTP_SUCCESS;
                }
                else
                {
                    // otherwise, an error occurred
                    dwNextToken = STENCIL_INVALIDINDEX;
                    dwErrorCode = dwErr;
                }
            }
        }

        if (pdwErrorCode)
            *pdwErrorCode = dwErrorCode;

        return dwNextToken;
    }

    // override RenderToken to render the new tags:
    //  {{if_and ...}}
    //  {{if_or ...}}
    //  {{if_not ...}}
    //
    // note that even though we overrode the parseing of {{endif}} and {{else}}
    // we don not need to override their runtime behavior.
    //
    // Any value returned from a replacement method other than HTTP_SUCCESS
    // will stop the rendering of the stencil.
    DWORD RenderToken(
        DWORD dwIndex,
        ITagReplacer* pReplacer,
        IWriteStream *pWriteStream,
        DWORD *pdwErrorCode,
        void* pState = NULL) const throw()
    {
        DWORD dwNextToken = STENCIL_INVALIDINDEX;
        DWORD dwErrorCode = HTTP_SUCCESS;
        const StencilToken* ptoken = GetToken(dwIndex);
        if (ptoken)
        {
            switch(ptoken->type)
            {
            case STENCIL_ANDSTART:
                // render the {{if_and ...}} tag
                dwNextToken = RenderAnd(dwIndex, pReplacer, &dwErrorCode);
                break;
            case STENCIL_ORSTART:
                // render the {{if_or ...}} tag
                dwNextToken = RenderOr(dwIndex, pReplacer, &dwErrorCode);
                break;
            case STENCIL_IFNOT:
                // render the {{if_not ...}} tag
                dwNextToken = RenderIfNot(dwIndex, pReplacer, &dwErrorCode);
                break;
            default:
                // delegate to the base class
                dwNextToken = __super::RenderToken(dwIndex, pReplacer,
                        pWriteStream, &dwErrorCode, (CStencilState *)pState);
                break;
            }
        }

        if (pdwErrorCode)
            *pdwErrorCode = dwErrorCode;

        return dwNextToken;
    }
}; // class CCustomStencil