
#include "stdafx.h"
#include "AdjustableDialogEx.h"
#include <afxlayout.h>


CAdjustableDialogEx::CAdjustableDialogEx(UINT unIDTemplate, CWnd* pParent)
    : CDialogEx(unIDTemplate, pParent)
    , m_pLayout(NULL)
    , m_crOriginalDlgSize(0, 0, 0, 0)
{
}

CAdjustableDialogEx::~CAdjustableDialogEx()
{
}

BEGIN_MESSAGE_MAP(CAdjustableDialogEx, CDialogEx)
    ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


BOOL CAdjustableDialogEx::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    this->GetWindowRect(m_crOriginalDlgSize);
    this->ResetLayout();

    return TRUE;

}

void CAdjustableDialogEx::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    lpMMI->ptMinTrackSize.x = m_crOriginalDlgSize.Width();
    lpMMI->ptMinTrackSize.y = m_crOriginalDlgSize.Height();
    CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CAdjustableDialogEx::ResetLayout(PVOID param)
{
    if (this->IsDynamicLayoutEnabled())
    {
        this->EnableDynamicLayout(FALSE);
        m_pLayout = NULL;
    }
    this->EnableDynamicLayout(TRUE);
    m_pLayout = this->GetDynamicLayout();
    if (!m_pLayout)
    {
        return;
    }
    m_pLayout->Create(this);
    if (param)
    {
        FillComplexComponentList(param);
    }
    else
    {
        FillComponentList();
    }
    if (m_pLayout->IsEmpty())
    {
        this->EnableDynamicLayout(FALSE);
        m_pLayout = NULL;
    }
}

BOOL CAdjustableDialogEx::AddControl(
    const CWnd& cwnd,
    const EM_ALIGN_TYPES emAlign,
    const EM_RESIZE_TYPES emResize
)
{
    return AddComponent(
        cwnd.GetSafeHwnd(),
        emAlign,
        emResize);
}

BOOL CAdjustableDialogEx::AddControl(
    const int nID,
    const EM_ALIGN_TYPES emAlign,
    const EM_RESIZE_TYPES emResize
)
{
    return AddComponent(
        this->GetDlgItem(nID)->GetSafeHwnd(),
        emAlign,
        emResize);
}

BOOL CAdjustableDialogEx::AddComponent(
    const HWND hwnd, 
    const EM_ALIGN_TYPES emAlign,
    const EM_RESIZE_TYPES emResize
)
{
    if (!::IsWindow(hwnd) || !m_pLayout)
    {
        return FALSE;
    }
    if (m_pLayout->HasItem(hwnd))
    {
        return TRUE;
    }
    CMFCDynamicLayout::MoveSettings ms = CMFCDynamicLayout::MoveNone();
    CMFCDynamicLayout::SizeSettings ss = CMFCDynamicLayout::SizeNone();
    switch (emAlign)
    {
    case EM_ALIGN_RIGHT:
        ms = CMFCDynamicLayout::MoveHorizontal(100);
        break;
    case EM_ALIGN_BOTTOM:
        ms = CMFCDynamicLayout::MoveVertical(100);
        break;
    case EM_ALIGN_BOTTOMRIGHT:
        ms = CMFCDynamicLayout::MoveHorizontalAndVertical(100, 100);
        break;
    default:
        //SizeNone
        break;
    }
    switch (emResize)
    {
    case EM_RESIZE_FULL_HEIGHT:
        ss = CMFCDynamicLayout::SizeVertical(100);
        break;
    case EM_RESIZE_FULL_WIDTH:
        ss = CMFCDynamicLayout::SizeHorizontal(100);
        break;
    case EM_RESIZE_FULL_FULL:
        ss = CMFCDynamicLayout::SizeHorizontalAndVertical(100, 100);
        break;
    default:
        //MoveNone
        break;
    }

    return m_pLayout->AddItem(hwnd, ms, ss);
}