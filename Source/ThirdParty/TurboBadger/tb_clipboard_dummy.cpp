// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_system.h"

#ifdef TB_CLIPBOARD_DUMMY

#include <sys/time.h>
#include <stdio.h>

#include <SDL/SDL.h>

namespace tb {

// == TBClipboard =====================================

void TBClipboard::Empty()
{
#if 0
    SDL_SetClipboardText("");
#endif
}

bool TBClipboard::HasText()
{
#if 0
    return SDL_HasClipboardText();
#else
	return false;
#endif
}

bool TBClipboard::SetText(const char *text)
{
#if 0
    SDL_SetClipboardText(text);
    return true;
#else
	return false;
#endif
}

bool TBClipboard::GetText(TBStr &text)
{
#if 0
    const char* _text = SDL_GetClipboardText();
    return text.Set(_text ? _text : "");
#else
	return false;
#endif
}

}; // namespace tb

#endif // TB_CLIPBOARD_DUMMY
