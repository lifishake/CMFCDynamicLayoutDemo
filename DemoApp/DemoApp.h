
#pragma once
#include "resource.h"	



class CDemoAppApp : public CWinApp
{
public:
	CDemoAppApp();

public:
	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP()
};

extern CDemoAppApp theApp;
