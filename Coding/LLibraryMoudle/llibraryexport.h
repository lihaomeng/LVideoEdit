#ifndef LLIBARYEXPORT_H
#define LLIBARYEXPORT_H

#if defined LLIBRARYMOUDLE_DLL
    #define LLIBARYEXPORT __declspec(dllexport)
#else
    #define LLIBARYEXPORT __declspec(dllimport)
#endif

#endif // LLIBARYEXPORT_H