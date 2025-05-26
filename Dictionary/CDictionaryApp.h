#pragma once

#include "resource.h" // если ты используешь ресурсы Windows
#include <afxwin.h>   // основной заголовок дл€ MFC-приложений

class CDictionaryApp : public CWinApp
{
public:
    CDictionaryApp();

    // ѕереопределени€
    virtual BOOL InitInstance();  // инициализаци€ приложени€

    // Ќастройки приложени€ (можно удалить, если не нужно)
    int m_nAppLook;
};

// Ёкземпл€р приложени€ (глобальный объект)
extern CDictionaryApp theApp;
