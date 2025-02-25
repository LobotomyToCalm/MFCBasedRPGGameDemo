// BusinessManDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Header.h"
#include "BusinessManDlg.h"
#include "afxdialogex.h"

#define TIMER_PAINT 1
// BusinessManDlg 对话框

IMPLEMENT_DYNAMIC(BusinessManDlg, CDialogEx)

BusinessManDlg::BusinessManDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BUSINESSDLG, pParent)
{

}

BusinessManDlg::~BusinessManDlg()
{
}

void BusinessManDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BusinessManDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// BusinessManDlg 消息处理程序


void BusinessManDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


BOOL BusinessManDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetTimer(TIMER_PAINT, 20, NULL);
	// TODO:  在此添加额外的初始化
	m_BusinessManBackGround.Load(_T("res\\BusinessManBackGround_PNG.png"));
	m_WoodBow.Load(_T("res\\WoodBow_DOWN_PNG.png"));
	m_WoodWand.Load(_T("res\\WoodWand_DOWN_PNG.png"));
	m_Apple.Load(_T("res\\Apple_PNG.png"));
	m_VioletPotion.Load(_T("res\\VioletPotion_PNG.png"));
	m_Hat1.Load(_T("res\\Hat1_DOWN_PNG.png"));
	m_Cloth1.Load(_T("res\\Cloth1_DOWN_PNG.png"));
	m_Shoes1.Load(_T("res\\Shoes1_DOWN_PNG.png"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void BusinessManDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case TIMER_PAINT:
		OnPaint();
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void BusinessManDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	for (int i = 0; i < 24; i++)
	{
		if (point.x > (i % 4) * 60 && point.x<(i % 4) * 60 + 60 &&					
			point.y>(i / 4) * 60 && point.y < (i / 4) * 60 + 60)
		{
			if (pApp->BusinessManVector[i]->Type == EQUIPMENT)									//如果商店里这东西是装备
			{
				for (int j = 0; j < 9; j++)
				{
					if (pApp->HeroBagVector[j]->Name == EMPTY)									//在背包数组里找一个空的地方
					{
						delete pApp->HeroBagVector[j];
						pApp->HeroBagVector[j] = pApp->BusinessManVector[i];					//转移到背包数组，金钱减少
						pApp->BusinessManVector[i] = new CApple(0, 0);
						pApp->BusinessManVector[i]->IniEmpty();
						pApp->Patrick.Money -= pApp->HeroBagVector[j]->Value;
						break;
					}
				}
			}
			else if (pApp->BusinessManVector[i]->Type == PROP)									//如果这玩意是个道具
			{
				for (int j = 0; j < 9; j++)
				{
					if (pApp->HeroBagVector[j]->Name == pApp->BusinessManVector[i]->Name)		//背包数组里找找有没有这个道具
					{
						pApp->Patrick.Money -= pApp->BusinessManVector[j]->Value;
						pApp->HeroBagVector[j]->Count += pApp->BusinessManVector[i]->Count;		//有的话就把数量加上，减少金钱
						pApp->BusinessManVector[i] = new CApple(0, 0);
						pApp->BusinessManVector[i]->IniEmpty();
						break;
					}
				}
				for (int j = 0; j < 9; j++)
				{
					if (pApp->HeroBagVector[j]->Name == EMPTY)								//没有的话就找个背包数组里的空地方
					{
						delete pApp->HeroBagVector[j];
						pApp->HeroBagVector[j] = pApp->BusinessManVector[i];					//转移到背包数组，减少金钱
						pApp->BusinessManVector[i] = new CApple(0, 0);
						pApp->BusinessManVector[i]->IniEmpty();
						pApp->Patrick.Money -= pApp->HeroBagVector[j]->Value;
						break;
					}
				}
			}
		}
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}


void BusinessManDlg::OnPaint()
{
	CPaintDC dc(this); 
																				//这里其实可以不用双缓冲，但是为了买东西的时候不闪屏 还是用了
	CDC *cDC = this->GetDC();   //获得当前窗口的DC									//反正我电脑能带起来....
	GetClientRect(&m_Bclient);   //获得窗口的尺寸
	//创建缓冲DC
	m_BcacheDC.CreateCompatibleDC(NULL);
	m_BcacheCBitmap.CreateCompatibleBitmap(cDC, m_Bclient.Width(), m_Bclient.Height());
	m_BcacheDC.SelectObject(&m_BcacheCBitmap);

	m_BusinessManBackGround.Draw(m_BcacheDC, m_Bclient);
	ShowItem();

	//将缓冲DC上的图贴在客户窗口区
	cDC->BitBlt(0, 0, m_Bclient.Width(), m_Bclient.Height(), &m_BcacheDC, 0, 0, SRCCOPY);

	ValidateRect(&m_Bclient);//使窗口有效
		 //释放缓冲DC										  //如果没有这两句
	m_BcacheDC.DeleteDC();								  //将会内存溢出，触发一个断点
		 //释放缓冲位图对象								  //<--------------
	m_BcacheCBitmap.DeleteObject();						  //<--------------
		 //释放显示DC
	ReleaseDC(cDC);
}


void BusinessManDlg::ShowItem()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	for (int i = 0; i < 24; i++)
	{
		switch (pApp->BusinessManVector[i]->Name)
		{
		case EMPTY:
			break;
		case WOODWAND:
			m_WoodWand.Draw(m_BcacheDC, (i % 4) * 60, (i / 4) * 60, 60, 60);
			break;
		case WOODBOW:
			m_WoodBow.Draw(m_BcacheDC, (i % 4) * 60, (i / 4) * 60, 60, 60);
			break;
		case APPLE:
			m_Apple.Draw(m_BcacheDC, (i % 4) * 60, (i / 4) * 60, 60, 60);
			break;
		case VIOLETPOTION:
			m_VioletPotion.Draw(m_BcacheDC, (i % 4) * 60, (i / 4) * 60, 60, 60);
			break;
		case HAT1:
			m_Hat1.Draw(m_BcacheDC, (i % 4) * 60, (i / 4) * 60, 60, 60);
			break;
		case CLOTH1:
			m_Cloth1.Draw(m_BcacheDC, (i % 4) * 60, (i / 4) * 60, 60, 60);
			break;
		case SHOES1:
			m_Shoes1.Draw(m_BcacheDC, (i % 4) * 60, (i / 4) * 60, 60, 60);
			break;
		}
		if (pApp->BusinessManVector[i]->Name != EMPTY)
		{
			m_BcacheDC.SetBkMode(TRANSPARENT);
			CString str;
			str.Format(_T("%d"), pApp->BusinessManVector[i]->Value);
			m_BcacheDC.TextOutW((i % 4) * 60 + 33, (i / 4) * 60 + 42, str);
		}
	}
}
