#ifndef _EXTENSION_H
#define _EXTENSION_H

#include "smsdk_ext.h"
#include <IBinTools.h>

class CExtension : public SDKExtension
{
public:
    /**
     * @brief This is called after the initial loading sequence has been processed.
     *
     * @param error		Error message buffer.
     * @param maxlength	Size of error message buffer.
     * @param late		Whether or not the module was loaded after map load.
     * @return			True to succeed loading, false to fail.
     */
    virtual bool SDK_OnLoad(char *error, size_t maxlength, bool late);

    /**
     * @brief This is called once all known extensions have been loaded.
     */
    virtual void SDK_OnAllLoaded();
};

extern IGameConfig *g_pGameConf;
extern IBinTools *g_pBinTools;

#endif // !_EXTENSION_H
