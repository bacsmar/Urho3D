// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_system.h"

#ifdef TB_CLIPBOARD_DUMMY

#include <sys/time.h>
#include <stdio.h>


#if 0
#include <SDL/SDL.h>
#endif

namespace tb {

// == TBClipboard =====================================

TBStr tbclipboard; ///< Obviosly not a full implementation since it ignores the OS :)

void TBClipboard::Empty()
{
#if 0
    SDL_SetClipboardText("");
#else
	tbclipboard.Clear();
#endif
}

bool TBClipboard::HasText()
{
#if 0
    return SDL_HasClipboardText();
#else
	return !tbclipboard.IsEmpty();
#endif
}

bool TBClipboard::SetText(const char *text)
{
#if 0
    SDL_SetClipboardText(text);
    return true;
#else
	return tbclipboard.Set(text);
#endif
}

bool TBClipboard::GetText(TBStr &text)
{
#if 0
    const char* _text = SDL_GetClipboardText();
    return text.Set(_text ? _text : "");
#else
	return text.Set(tbclipboard);
#endif
}

}; // namespace tb

#endif // TB_CLIPBOARD_DUMMY
