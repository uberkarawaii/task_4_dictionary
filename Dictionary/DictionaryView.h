#pragma once
#include "Dictionary.h"
#include "Logger.h"
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

class CDictionaryView : public CFormView
{
    DECLARE_DYNCREATE(CDictionaryView)
public:
    CDictionaryView();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DICTIONARY_FORM };
#endif

    virtual void DoDataExchange(CDataExchange* pDX);
    virtual void OnInitialUpdate();

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnTranslateClicked();
    afx_msg void OnBnClickedButtonLoadDict();

private:
    CComboBox m_comboFrom;
    CComboBox m_comboTo;
    CEdit m_editWord;
    CListBox m_listResult;
    Dictionary m_dict;

    void LoadDictionaries();
    void UpdateLanguageComboBoxes();
    CString GetAppPath() const;
};
