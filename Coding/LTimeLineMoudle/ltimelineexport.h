#ifndef LTIMELINEEXPORT_H
#define LTIMELINEEXPORT_H

#if defined LTIMELINEMOUDLE_DLL
    #define LTIMELINEEXPORT __declspec(dllexport)
#else
    #define LTIMELINEEXPORT __declspec(dllimport)
#endif

#endif // LTIMELINEEXPORT_H