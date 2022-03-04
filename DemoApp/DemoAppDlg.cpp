#include "stdafx.h"
#include "DemoApp.h"
#include "DemoAppDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDemoAppDlg::CDemoAppDlg(CWnd* pParent /*=NULL*/)
	: CAdjustableDialogEx(IDD_DEMOAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoAppDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADIO_WIDTH, m_rbMode[0]);
    DDX_Control(pDX, IDC_RADIO_HEIGHT, m_rbMode[1]);
    DDX_Control(pDX, IDC_RADIO_BOTH, m_rbMode[2]);
}

BEGIN_MESSAGE_MAP(CDemoAppDlg, CAdjustableDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_RADIO_WIDTH, &CDemoAppDlg::OnBnClickedRadioWidth)
    ON_BN_CLICKED(IDC_RADIO_HEIGHT, &CDemoAppDlg::OnBnClickedRadioHeight)
    ON_BN_CLICKED(IDC_RADIO_BOTH, &CDemoAppDlg::OnBnClickedRadioBoth)
    ON_BN_CLICKED(IDC_BUTTON_EXIT, &CDemoAppDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()

void CDemoAppDlg::FillComponentList()
{
    __super::AddControl(IDC_STATIC_HEIGHT, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_HEIGHT);
    __super::AddControl(IDC_LIST_HEIGHT, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_HEIGHT);
    __super::AddControl(IDC_BUTTON_EXIT, EM_ALIGN_BOTTOM, EM_RESIZE_NONE);

    __super::AddControl(IDC_STATIC_WIDTH, EM_ALIGN_BOTTOM, EM_RESIZE_FULL_WIDTH);

    __super::AddControl(IDC_STATIC_ADJUST, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_WIDTH);
    __super::AddControl(IDC_EDIT_ADJUST, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_WIDTH);
    __super::AddControl(m_rbMode[0], EM_ALIGN_RIGHT, EM_RESIZE_FULL_WIDTH);
    __super::AddControl(m_rbMode[1], EM_ALIGN_RIGHT, EM_RESIZE_FULL_WIDTH);
    __super::AddControl(m_rbMode[2], EM_ALIGN_RIGHT, EM_RESIZE_FULL_WIDTH);
}

void CDemoAppDlg::FillComplexComponentList(PVOID param)
{
    UINT8 ucType(0);
    if (param)
    {
        ucType = *(UINT8*)param;
    }
    __super::AddControl(IDC_STATIC_HEIGHT, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_HEIGHT);
    __super::AddControl(IDC_LIST_HEIGHT, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_HEIGHT);
    __super::AddControl(IDC_BUTTON_EXIT, EM_ALIGN_BOTTOM, EM_RESIZE_NONE);

    __super::AddControl(IDC_STATIC_WIDTH, EM_ALIGN_BOTTOM, EM_RESIZE_FULL_WIDTH);

    switch (ucType)
    {
    case 0:
    default:
        __super::AddControl(IDC_STATIC_ADJUST, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_WIDTH);
        __super::AddControl(IDC_EDIT_ADJUST, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_WIDTH);
        __super::AddControl(m_rbMode[0], EM_ALIGN_RIGHT, EM_RESIZE_NONE);
        __super::AddControl(m_rbMode[1], EM_ALIGN_RIGHT, EM_RESIZE_NONE);
        __super::AddControl(m_rbMode[2], EM_ALIGN_RIGHT, EM_RESIZE_NONE);
        break;
    case 1:
        __super::AddControl(IDC_STATIC_ADJUST, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_HEIGHT);
        __super::AddControl(IDC_EDIT_ADJUST, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_HEIGHT);
        __super::AddControl(m_rbMode[0], EM_ALIGN_BOTTOM, EM_RESIZE_NONE);
        __super::AddControl(m_rbMode[1], EM_ALIGN_BOTTOM, EM_RESIZE_NONE);
        __super::AddControl(m_rbMode[2], EM_ALIGN_BOTTOM, EM_RESIZE_NONE);
    case 2:
        __super::AddControl(IDC_STATIC_ADJUST, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_FULL);
        __super::AddControl(IDC_EDIT_ADJUST, EM_ALIGN_TOPLEFT, EM_RESIZE_FULL_FULL);
        __super::AddControl(m_rbMode[0], EM_ALIGN_BOTTOMRIGHT, EM_RESIZE_NONE);
        __super::AddControl(m_rbMode[1], EM_ALIGN_BOTTOMRIGHT, EM_RESIZE_NONE);
        __super::AddControl(m_rbMode[2], EM_ALIGN_BOTTOMRIGHT, EM_RESIZE_NONE);
    }
    
}


BOOL CDemoAppDlg::OnInitDialog()
{
    CAdjustableDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);
    m_rbMode[0].SetCheck(BST_CHECKED);
    UpdateData(FALSE);

	return TRUE;
}

void CDemoAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
        CAdjustableDialogEx::OnPaint();
	}
}

HCURSOR CDemoAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDemoAppDlg::OnBnClickedRadioWidth()
{
    ChangeLayoutMode(0);
}


void CDemoAppDlg::OnBnClickedRadioHeight()
{
    ChangeLayoutMode(1);
}


void CDemoAppDlg::OnBnClickedRadioBoth()
{
    ChangeLayoutMode(2);
}


void CDemoAppDlg::ChangeLayoutMode(UINT8 ucMode)
{
    __super::ResetLayout(&ucMode);
}

void CDemoAppDlg::OnBnClickedButtonExit()
{
    __super::OnCancel();
}
