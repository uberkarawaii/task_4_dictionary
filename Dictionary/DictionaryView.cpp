#include "pch.h"
#include "resource.h"
#include "Dictionary.h"
#include "DictionaryView.h"
#include "afxdialogex.h"

IMPLEMENT_DYNCREATE(CDictionaryView, CFormView)

CDictionaryView::CDictionaryView() : CFormView(IDD_DICTIONARY_FORM) {}

void CDictionaryView::DoDataExchange(CDataExchange* pDX) {
    CFormView::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_FROM, m_comboFrom);
    DDX_Control(pDX, IDC_COMBO_TO, m_comboTo);
    DDX_Control(pDX, IDC_EDIT_WORD, m_editWord);
    DDX_Control(pDX, IDC_LIST_RESULT, m_listResult);
}

BEGIN_MESSAGE_MAP(CDictionaryView, CFormView)
    ON_BN_CLICKED(IDC_BUTTON_TRANSLATE, &CDictionaryView::OnTranslateClicked)
    ON_BN_CLICKED(IDC_BUTTON_LOAD_DICT, &CDictionaryView::OnBnClickedButtonLoadDict)
END_MESSAGE_MAP()

void CDictionaryView::OnInitialUpdate() {
    CFormView::OnInitialUpdate();
    LoadDictionaries();
}

void CDictionaryView::LoadDictionaries() {
    try {
        m_dict.LoadFromFile("немецкий - русский.txt");
        m_dict.LoadFromFile("английский - русский.txt");

        // Очищаем и заполняем комбобоксы
        m_comboFrom.ResetContent();
        m_comboTo.ResetContent();

        auto langs = m_dict.GetLanguages();
        for (const auto& lang : langs) {
            CString str(lang.c_str());
            m_comboFrom.AddString(str);
            m_comboTo.AddString(str);
        }

        // Устанавливаем разумные значения по умолчанию
        if (m_comboFrom.FindString(-1, _T("немецкий")) != CB_ERR)
            m_comboFrom.SelectString(-1, _T("немецкий"));
        if (m_comboTo.FindString(-1, _T("русский")) != CB_ERR)
            m_comboTo.SelectString(-1, _T("русский"));

        Logger::Instance().Log("Dictionaries loaded successfully");
    }
    catch (const std::exception& ex) {
        AfxMessageBox(_T("Ошибка загрузки словарей"));
        Logger::Instance().Log(ex.what(), "ERROR");
    }
}

void CDictionaryView::OnBnClickedButtonLoadDict() {
    CFileDialog fileDlg(TRUE, _T(".txt"), NULL,
        OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
        _T("Текстовые файлы (*.txt)|*.txt||"), this);

    if (fileDlg.DoModal() == IDOK) {
        CString filePath = fileDlg.GetPathName();
        try {
            // Простое чтение файла без сложных преобразований
            std::ifstream file(filePath);
            if (!file) throw std::runtime_error("File open error");

            m_dict.LoadFromFile(std::string(CT2A(filePath)));
            LoadDictionaries(); // Перезагружаем списки
            AfxMessageBox(_T("Словарь успешно загружен!"));
        }
        catch (...) {
            AfxMessageBox(_T("Ошибка загрузки словаря"));
        }
    }
}

void CDictionaryView::OnTranslateClicked() {
    CString wordCStr;
    m_editWord.GetWindowText(wordCStr);
    wordCStr.Trim();

    if (wordCStr.IsEmpty()) {
        AfxMessageBox(_T("Введите слово для перевода"));
        Logger::Instance().LogWarning("Пользователь пытается сделать перевод для пустой строки");
        return;
    }

    CString fromStr, toStr;
    m_comboFrom.GetLBText(m_comboFrom.GetCurSel(), fromStr);
    m_comboTo.GetLBText(m_comboTo.GetCurSel(), toStr);

    if (fromStr == toStr) {
        AfxMessageBox(_T("Выберите разные языки"));
        Logger::Instance().LogWarning("Попытка перевода на тот же язык. Перевод невозможен");
        return;
    }

    try {
        // Простые преобразования без CA2W/CW2A
        std::string word = std::string(CT2A(wordCStr));
        std::string from = std::string(CT2A(fromStr));
        std::string to = std::string(CT2A(toStr));

        auto results = m_dict.Translate(word, from, to);
        m_listResult.ResetContent();

        if (results.empty() || (results.size() == 1 && results[0] == "Перевод не найден")) {
            m_listResult.AddString(_T("Перевод не найден"));
            Logger::Instance().Log("Перевод не найден: " + word + " (" + from + "->" + to + ")");
        }
        else {
            for (const auto& r : results) {
                m_listResult.AddString(CString(r.c_str()));
            }
            Logger::Instance().Log("Успешный перевод: " + word + " (" + from + "->" + to + ")");
        }
    }
    catch (...) {
        AfxMessageBox(_T("Ошибка перевода"));
    }
}