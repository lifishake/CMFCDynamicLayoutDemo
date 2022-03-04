#pragma once
#include <afxdialogex.h>

class CAdjustableDialogEx :
    public CDialogEx
{
public:
    CAdjustableDialogEx(UINT unIDTemplate, CWnd* pParent = NULL);
    virtual ~CAdjustableDialogEx();
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
    typedef enum _em_align_types {
        EM_ALIGN_TOPLEFT = 0,
        EM_ALIGN_RIGHT,
        EM_ALIGN_BOTTOM,
        EM_ALIGN_BOTTOMRIGHT,
        EM_ALIGN_MAX,
    }EM_ALIGN_TYPES;
    typedef enum _em_resize_types {
        EM_RESIZE_NONE = 0,
        EM_RESIZE_FULL_HEIGHT,
        EM_RESIZE_FULL_WIDTH,
        EM_RESIZE_FULL_FULL,
        EM_RESIZE_MAX,
    }EM_RESIZE_TYPES;

protected:
    virtual void FillComponentList() {};
    virtual void FillComplexComponentList(PVOID param) {};
    void ResetLayout(PVOID param = NULL);
    BOOL AddControl(
        const CWnd& cwnd,
        const EM_ALIGN_TYPES emAlign,
        const EM_RESIZE_TYPES emResize
    );
    BOOL AddControl(
        const int nID,
        const EM_ALIGN_TYPES emAlign,
        const EM_RESIZE_TYPES emResize
    );
    BOOL AddComponent(
        const HWND hwnd,
        const EM_ALIGN_TYPES emAlign,
        const EM_RESIZE_TYPES emResize
    );
private:
    CRect               m_crOriginalDlgSize;
    CMFCDynamicLayout*  m_pLayout;
};

