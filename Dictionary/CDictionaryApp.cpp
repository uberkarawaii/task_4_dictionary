#include "pch.h"
#include "CDictionaryApp.h"
#include "DictionaryView.h"
#include "DictionaryDoc.h"
#include "MainFrm.h"

// Глобальный объект приложения
CDictionaryApp theApp;

CDictionaryApp::CDictionaryApp()
{
    m_nAppLook = 0; // например, стиль по умолчанию
}

BOOL CDictionaryApp::InitInstance()
{
    CWinApp::InitInstance();

    // Упрощенная инициализация без DocTemplate
    CMainFrame* pFrame = new CMainFrame;
    if (!pFrame->LoadFrame(IDR_MAINFRAME))
        return FALSE;

    m_pMainWnd = pFrame;
    pFrame->ShowWindow(SW_SHOW);
    pFrame->UpdateWindow();

    return TRUE;
}