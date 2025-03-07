#pragma once


// ChooseOcc 对话框

class ChooseOcc : public CDialogEx
{
	DECLARE_DYNAMIC(ChooseOcc)

public:
	ChooseOcc(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ChooseOcc();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHOOSEOCC };
#endif
public:
	CImage m_ButtonFrame;						//选择按钮时边框图片
	CImage m_Hunter;							//猎人按钮图片
	CImage m_Mage;								//魔法师按钮图片
	CImage m_OK;								//确认按钮图片
	CImage m_ChooseOccBackGround;				//背景图片
	CBitmap m_CcacheCBitmap;					//缓冲位图
	CDC m_CcacheDC;								//创建缓冲DC
	CRect m_Cclient;							//保存客户区大小

	int FrameX;//选择按钮框架的x
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ShowButton();
	void ShowButtonFrame();
	void ChangeButtonFrame(int);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
