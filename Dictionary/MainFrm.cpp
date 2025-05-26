#include "pch.h"
#include "framework.h"
#include "Dictionary.h"
#include "resource.h"
#include "MainFrm.h"
#include "CDictionaryApp.h"
#include "DictionaryView.h"  // Добавляем для CDictionaryView

extern CDictionaryApp theApp;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
    ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
END_MESSAGE_MAP()

static UINT indicators[] =
{
    ID_SEPARATOR,
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame() noexcept
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
    {
        TRACE0("Не удалось создать панель инструментов\n");
        return -1;
    }

    if (!m_wndStatusBar.Create(this))
    {
        TRACE0("Не удалось создать строку состояния\n");
        return -1;
    }
    m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndToolBar);

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CFrameWnd::PreCreateWindow(cs))
        return FALSE;
    return TRUE;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
    // Полностью отказываемся от разделителей
    // Создаем представление напрямую как дочернее окно фрейма
    CRect rect;
    GetClientRect(&rect);

    CView* pView = (CView*)RUNTIME_CLASS(CDictionaryView)->CreateObject();
    if (!pView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
        rect, this, AFX_IDW_PANE_FIRST, pContext))
    {
        TRACE0("Failed to create view\n");
        return FALSE;
    }

    SetActiveView(pView);
    return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}
#endif

void CMainFrame::OnApplicationLook(UINT id)
{
    // ... существующий код ...
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
    // ... существующий код ...
}