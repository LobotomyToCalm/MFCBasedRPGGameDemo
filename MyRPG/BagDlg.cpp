// BagDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Header.h"
#include "BagDlg.h"
#include "afxdialogex.h"

#define TIMER_PAINT 1

// BagDlg 对话框

IMPLEMENT_DYNAMIC(BagDlg, CDialogEx)

BagDlg::BagDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BAGDIALOG, pParent)
{
}

BagDlg::~BagDlg()
{
}

void BagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BagDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// BagDlg 消息处理程序


BOOL BagDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_BagBackGroundImage.Load(_T("res\\BagBackGround_PNG.png"));
	// TODO:  在此添加额外的初始化
	//添加定时器
	SetTimer(TIMER_PAINT, 20, NULL);
	
	//加载物品的图片
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


void BagDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CDC *cDC = this->GetDC();   //获得当前窗口的DC   
	GetClientRect(&m_Bclient);   //获得窗口的尺寸
	// TODO: 在此处添加消息处理程序代码

	//创建缓冲DC
	m_BcacheDC.CreateCompatibleDC(NULL);
	m_BcacheCBitmap.CreateCompatibleBitmap(cDC, m_Bclient.Width(), m_Bclient.Height());
	m_BcacheDC.SelectObject(&m_BcacheCBitmap);

	m_BagBackGroundImage.Draw(m_BcacheDC, m_Bclient);
	ShowItem();
	ShowMoney();
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

void BagDlg::ShowItem()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	//CDC* pcacheDC = &m_BcacheDC;
	for (int i = 0; i < 9; i++)
	{
		switch (pApp->HeroBagVector[i]->Name)
		{
		case EMPTY:
			break;
		case WOODWAND:
			m_WoodWand.Draw(m_BcacheDC, (i % 3) * 60, (i / 3) * 60, 60, 60);
			break;
		case WOODBOW:
			m_WoodBow.Draw(m_BcacheDC, (i % 3) * 60, (i / 3) * 60, 60, 60);
			break;
		case APPLE:
			m_Apple.Draw(m_BcacheDC, (i % 3) * 60, (i / 3) * 60, 60, 60);
			break;
		case VIOLETPOTION:
			m_VioletPotion.Draw(m_BcacheDC, (i % 3) * 60, (i / 3) * 60, 60, 60);
			break;
		case HAT1:
			m_Hat1.Draw(m_BcacheDC, (i % 3) * 60, (i / 3) * 60, 60, 60);
			break;
		case CLOTH1:
			m_Cloth1.Draw(m_BcacheDC, (i % 3) * 60, (i / 3) * 60, 60, 60);
			break;
		case SHOES1:
			m_Shoes1.Draw(m_BcacheDC, (i % 3) * 60, (i / 3) * 60, 60, 60);
			break;
		}
		if (pApp->HeroBagVector[i]->Type == PROP)
		{
			m_BcacheDC.SetBkMode(TRANSPARENT);
			CString str;
			str.Format(_T("%d"), pApp->HeroBagVector[i]->Count);
			m_BcacheDC.TextOutW((i % 3) * 60+37, (i / 3) * 60+42, str);
		}
	}
}


void BagDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	for (int i = 0; i < 9; i++)
	{
		if (point.x > (i % 3) * 60 && point.x<((i % 3) * 60 + 60) &&
			point.y>(i / 3) * 60 && point.y < ((i / 3) * 60 + 60))
		{
			switch (pApp->HeroBagVector[i]->Type)
			{
			case EQUIPMENT:
				if (pApp->EquipmentVector[pApp->HeroBagVector[i]->Part - 1]->State == EQUIPON)		//如果这个部位是有装备的
				{												  //注：⬆ 这里这个 -1 可以看看
																  //    那个Item.h里，各个部位的define数字
																  //    0123是装备数组，对应define数字的1234
					CEquipment* pEquipment;
					pEquipment = (CEquipment*)pApp->HeroBagVector[i];
					if (pEquipment->FitOcc == pApp->Patrick.Occupation||
						pEquipment->FitOcc==ALLOCC)														//如果这个装备适合英雄职业或者适合全职业
					{
						pApp->HeroBagVector[i] =
							pApp->EquipmentVector[pApp->HeroBagVector[i]->Part - 1];					//交换背包数组里的和装备数组里的指向的对象
						pApp->HeroBagVector[i]->GetOff(pApp->Patrick);									//卸下原本的装备
						pApp->HeroBagVector[i]->State = EQUIPOFF;
						pApp->EquipmentVector[pApp->HeroBagVector[i]->Part - 1] = pEquipment;
						pApp->EquipmentVector[pApp->HeroBagVector[i]->Part - 1]->Equip(pApp->Patrick);	//装备上新装备
						pApp->EquipmentVector[pApp->HeroBagVector[i]->Part - 1]->State = EQUIPON;
					}
				}
				else if (pApp->EquipmentVector[pApp->HeroBagVector[i]->Part - 1]->State == EMPTY)		//如果这个部位是没有装备的
				{
					CEquipment* pEquipment;
					pEquipment = (CEquipment*)pApp->HeroBagVector[i];
					if (pEquipment->FitOcc == pApp->Patrick.Occupation ||
						pEquipment->FitOcc == ALLOCC)													//如果装备适合英雄职业
					{
						pApp->EquipmentVector[pApp->HeroBagVector[i]->Part - 1] =
							(CEquipment*)pApp->HeroBagVector[i];	
						pApp->EquipmentVector[pApp->HeroBagVector[i]->Part - 1]->Equip(pApp->Patrick);	//装备上新装备													
						pApp->EquipmentVector[pApp->HeroBagVector[i]->Part - 1]->State = EQUIPON;
						pApp->HeroBagVector[i] = new CApple(0, 0);										//初始化背包数组里该位置的东西
						pApp->HeroBagVector[i]->IniEmpty();
					}
				}
				break;
			case PROP:
				pApp->HeroBagVector[i]->Use(pApp->Patrick);								//使用物品
				if (pApp->HeroBagVector[i]->Count <= EMPTY)								//如果物品用完了
				{
					delete pApp->HeroBagVector[i];										//初始化背包数组里该位置的指向
					pApp->HeroBagVector[i] = new CApple(0, 0);
					pApp->HeroBagVector[i]->IniEmpty();
				}
				break;
			case EMPTY:																	//如果该位置没有东西 那就什么也不做
				break;
			}
		}
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}
void BagDlg::ShowMoney()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	CDC* pcacheDC = &m_BcacheDC;//缓冲DC的指针

	pcacheDC->SetBkMode(TRANSPARENT);
	pcacheDC->TextOutW(10, 190, _T("Money: "));
	CString str;
	str.Format(_T("%d"), pApp->Patrick.Money);
	pcacheDC->TextOutW(90, 190, str);
}

void BagDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case TIMER_PAINT:
		OnPaint();					//屏幕重绘定时器
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void BagDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}
