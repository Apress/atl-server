#include "stdafx.h"
#include <atlenc.h>

int _tmain()
{
    char *data   = _T( "Hello World!" );
    int   dataLen = strlen( data );

    //
    // First determine how much memory to allocate to
    // hold the encoded data.
    //    
    int encodedDataLen  = Base64EncodeGetRequiredLength( dataLen );
    char* encodedData = new char[ encodedDataLen + 1 ];
    
    if( TRUE == Base64Encode( ( const BYTE*)data,
                              dataLen,
                              encodedData,
                              &encodedDataLen ) )
    {
        encodedData[ encodedDataLen ] = 0;
        printf( "Successfully encoded!\n%s", encodedData );
    }
    else
    {
        printf( "Error encoding!" );
    }

    return 0;
}