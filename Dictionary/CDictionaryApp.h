#pragma once

#include "resource.h" // ���� �� ����������� ������� Windows
#include <afxwin.h>   // �������� ��������� ��� MFC-����������

class CDictionaryApp : public CWinApp
{
public:
    CDictionaryApp();

    // ���������������
    virtual BOOL InitInstance();  // ������������� ����������

    // ��������� ���������� (����� �������, ���� �� �����)
    int m_nAppLook;
};

// ��������� ���������� (���������� ������)
extern CDictionaryApp theApp;
