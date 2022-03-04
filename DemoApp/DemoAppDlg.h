#pragma once
#include "..\class\AdjustableDialogEx.h"
#include "afxwin.h"

class CDemoAppDlg : public CAdjustableDialogEx
{

public:
	CDemoAppDlg(CWnd* pParent = NULL);


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEMOAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
    void FillComponentList();
    void FillComplexComponentList(PVOID param);
public:
    afx_msg void OnBnClickedRadioWidth();
    afx_msg void OnBnClickedRadioHeight();
    afx_msg void OnBnClickedRadioBoth();
    afx_msg void OnBnClickedButtonExit();
    CButton m_rbMode[3];
private:
    void ChangeLayoutMode(UINT8 ucMode);
};
