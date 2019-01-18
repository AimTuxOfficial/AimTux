#pragma once

typedef void* FileNameHandle_t;

class IFileSystem
{
public:
    bool String( const FileNameHandle_t& handle, char *buf, int buflen )
    {
        typedef bool (* String)(void*, const FileNameHandle_t& handle, char *buf, int buflen);
        return getvfunc<String>(this, 42)(this, handle, buf, buflen);
    }
};