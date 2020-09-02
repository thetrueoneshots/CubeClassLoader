#ifndef MAIN_H
#define MAIN_H

// All necessary includes for the hooks and main.cpp
#include <vector>
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <map>
#include <windows.h>
// Include cwsdk library
#include "cwmods/cwsdk.h"
// Include src
#include "DButton.h"
#include "src/class.h"
#include "src/fileParser.h"
#include "src/public.h"
#include "src/memory/memory_helper.h"
// Include hooks
#include "src/hooks/menu_hook.h"
#include "src/hooks/item_restrictions_hook.h"
#include "src/hooks/abilities_hook.h"


#define MUST_IMPORT(dllname, name)\
dllname->name = GetProcAddress(dllname->handle, #name);\
            if (!dllname->name) {\
                char ERROR_MESSAGE_POPUP[512] = {0};\
                sprintf(ERROR_MESSAGE_POPUP, "%s does not export " #name ".\n", dllname->fileName.c_str());\
                Popup("Error", ERROR_MESSAGE_POPUP);\
                exit(1);\
            }

#endif // MAIN_H