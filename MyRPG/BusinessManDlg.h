#pragma once
#include"Header.h"
#include<vector>
using std::vector;

// BusinessManDlg 对话框

class BusinessManDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BusinessManDlg)

public:
	BusinessManDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BusinessManDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUSINESSDLG };
#endif
public:
	CImage m_BusinessManBackGround;
	CImage m_WoodBow;
	CImage m_WoodWand;
	CImage m_Apple;
	CImage m_VioletPotion;
	CImage m_Hat1;
	CImage m_Cloth1;
	CImage m_Shoes1;

	CBitmap m_BcacheCBitmap;					//缓冲位图
	CDC m_BcacheDC;								//创建缓冲DC
	CRect m_Bclient;							//保存客户区大小
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
public:
	void ShowItem();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	virtual void OnOK();
};

