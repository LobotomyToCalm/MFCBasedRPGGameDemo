
// ChildView.cpp: CChildView 类的实现
//

#include "stdafx.h"
#include "ChildView.h"
#include "Header.h"
#include "Map.h"
#include <string>
#include <stdlib.h>
#include <time.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_PAINT 0
#define TIMER_BULLET 1
#define TIMER_HEROMOVE 2
#define TIMER_BULLETOUT 3
#define TIMER_MONSTERMOVE 4
#define TIMER_MONSTERCHANGEDIREC 5
#define TIMER_MONSTERATTACK 6
#define TIMER_RESTOREHP 7
#define TIMER_BUSINESSMAN 8


// CChildView

CChildView::CChildView()
{
	
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYUP()
//	ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



//英雄登场
//Hero Patrick;

const int BulletCount = 30;						//子弹数组总量
static int BulletWaste = 0;						//主角已发射子弹数量




// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);
	
	/*--------------------------------------------------------------------------游戏初始化----------------------------------------*/
	//********************************加载图片*****************************************/
	m_BackGroundImage1.Load(_T("res\\BackGround1_PNG.png"));						//背景图片
	m_BackGroundImage2.Load(_T("res\\BackGround2_PNG.png"));
	m_BackGroundImage3.Load(_T("res\\BackGround3_PNG.png"));
	m_BackGroundImage4.Load(_T("res\\BackGround4_PNG.png"));
	m_BackGroundImage5.Load(_T("res\\BackGround5_PNG.png"));
	m_HeroImage_DOWN.Load(_T("res\\Hero_DOWN_PNG.png"));							//英雄图片
	m_HeroImage_UP.Load(_T("res\\Hero_UP_PNG.png"));
	m_HeroImage_LEFT.Load(_T("res\\Hero_LEFT_PNG.png"));
	m_HeroImage_RIGHT.Load(_T("res\\Hero_RIGHT_PNG.png"));
	m_AppleImage.Load(_T("res\\Apple_PNG.png"));									//苹果图片
	m_VioletPotionImage.Load(_T("res\\VioletPotion_PNG.png"));						//紫色药水图片
	m_WoodBowImage_UP.Load(_T("res\\WoodBow_UP_PNG.png"));							//木弓图片
	m_WoodBowImage_DOWN.Load(_T("res\\WoodBow_DOWN_PNG.png"));
	m_WoodBowImage_LEFT.Load(_T("res\\WoodBow_LEFT_PNG.png"));
	m_WoodBowImage_RIGHT.Load(_T("res\\WoodBow_RIGHT_PNG.png"));
	m_WoodWandImage_UP.Load(_T("res\\WoodWand_UP_PNG.png"));						//木法杖图片
	m_WoodWandImage_DOWN.Load(_T("res\\WoodWand_DOWN_PNG.png"));
	m_WoodWandImage_LEFT.Load(_T("res\\WoodWand_LEFT_PNG.png"));
	m_WoodWandImage_RIGHT.Load(_T("res\\WoodWand_RIGHT_PNG.png"));
	m_Hat1Image_UP.Load(_T("res\\Hat1_UP_PNG.png"));								//新手帽子图片
	m_Hat1Image_DOWN.Load(_T("res\\Hat1_DOWN_PNG.png"));
	m_Hat1Image_LEFT.Load(_T("res\\Hat1_LEFT_PNG.png"));
	m_Hat1Image_RIGHT.Load(_T("res\\Hat1_RIGHT_PNG.png"));
	m_Cloth1Image_UP.Load(_T("res\\Cloth1_UP_PNG.png"));							//新手衣服图片
	m_Cloth1Image_DOWN.Load(_T("res\\Cloth1_DOWN_PNG.png"));
	m_Cloth1Image_LEFT.Load(_T("res\\Cloth1_LEFT_PNG.png"));
	m_Cloth1Image_RIGHT.Load(_T("res\\Cloth1_RIGHT_PNG.png"));
	m_Shoes1Image_UP.Load(_T("res\\Shoes1_UP_PNG.png"));							//新手鞋子图片
	m_Shoes1Image_DOWN.Load(_T("res\\Shoes1_DOWN_PNG.png"));
	m_Shoes1Image_LEFT.Load(_T("res\\Shoes1_LEFT_PNG.png"));
	m_Shoes1Image_RIGHT.Load(_T("res\\Shoes1_RIGHT_PNG.png"));
	m_ArrowImage_UP.Load(_T("res\\Arrow_UP_PNG.png"));								//箭图片
	m_ArrowImage_DOWN.Load(_T("res\\Arrow_DOWN_PNG.png"));
	m_ArrowImage_LEFT.Load(_T("res\\Arrow_LEFT_PNG.png"));
	m_ArrowImage_RIGHT.Load(_T("res\\Arrow_RIGHT_PNG.png"));
	m_OrbImage_UP.Load(_T("res\\Orb_UP_PNG.png"));									//法球图片
	m_OrbImage_DOWN.Load(_T("res\\Orb_DOWN_PNG.png"));
	m_OrbImage_LEFT.Load(_T("res\\Orb_LEFT_PNG.png"));
	m_OrbImage_RIGHT.Load(_T("res\\Orb_RIGHT_PNG.png"));
	m_BusinessManImage.Load(_T("res\\BusinessMan_PNG.png"));						//商人图片
	m_BlackGhostBulletImage_UP.Load(_T("res\\BlackGhostBullet_UP_PNG.png"));		//黑鬼子弹图片
	m_BlackGhostBulletImage_DOWN.Load(_T("res\\BlackGhostBullet_DOWN_PNG.png"));
	m_BlackGhostBulletImage_LEFT.Load(_T("res\\BlackGhostBullet_LEFT_PNG.png"));
	m_BlackGhostBulletImage_RIGHT.Load(_T("res\\BlackGhostBullet_RIGHT_PNG.png"));
	m_MudMonsterBulletImage_UP.Load(_T("res\\MudMonsterBullet_UP_PNG.png"));		//泥怪子弹图片
	m_MudMonsterBulletImage_DOWN.Load(_T("res\\MudMonsterBullet_DOWN_PNG.png"));
	m_MudMonsterBulletImage_LEFT.Load(_T("res\\MudMonsterBullet_LEFT_PNG.png"));
	m_MudMonsterBulletImage_RIGHT.Load(_T("res\\MudMonsterBullet_RIGHT_PNG.png"));
	m_StoneImage.Load(_T("res\\Block_PNG.png"));									//石块图片
	m_WoodImage.Load(_T("res\\Wood_PNG.png"));										//木桩图片
	m_BlackGhostImage_LEFT.Load(_T("res\\BlackGhost_LEFT_PNG.png"));				//测试用黑鬼图片
	m_BlackGhostImage_RIGHT.Load(_T("res\\BlackGhost_RIGHT_PNG.png"));
	m_BlackGhostImage_UP.Load(_T("res\\BlackGhost_UP_PNG.png"));
	m_BlackGhostImage_DOWN.Load(_T("res\\BlackGhost_DOWN_PNG.png"));
	m_MudMonsterImage_DOWN.Load(_T("res\\MudMonster_DOWN_PNG.png"));				//测试用泥怪图片
	m_MudMonsterImage_UP.Load(_T("res\\MudMonster_UP_PNG.png"));
	m_MudMonsterImage_LEFT.Load(_T("res\\MudMonster_LEFT_PNG.png"));
	m_MudMonsterImage_RIGHT.Load(_T("res\\MudMonster_RIGHT_PNG.png"));
	m_BlackBackGround1.Load(_T("res\\BlackBackGround_PNG.png"));					//加载蒙版地图
	m_BlackBackGround2.Load(_T("res\\BlackBackGround_PNG.png"));
	m_BlackBackGround3.Load(_T("res\\BlackBackGround_PNG.png"));
	m_BlackBackGround4.Load(_T("res\\BlackBackGround_PNG.png"));
	m_BlackBackGround5.Load(_T("res\\BlackBackGround_PNG.png"));
	m_BagButtonImage.Load(_T("res\\BagButton_PNG.png"));							//背包按钮图像	
	m_CharacterButtonImage.Load(_T("res\\CharacterButton_PNG.png"));				//人物按钮图像
	m_UIImage.Load(_T("res\\UI_PNG.png"));											//UI图像

	//初始化地图
	CurrentMap = TOWN;										//初始化当前地图						
	m_BlackBackGround = m_BlackBackGround1;					//初始化蒙版地图
	m_BackGroundImage = m_BackGroundImage1;					//初始化背景
	IniMap(Town_Map);										//在蒙版地图上标记障碍
	IniMonster(Town_Monster);								//初始化地图怪物
	
	//初始化窗口状态
	pApp->BagDlgState = false;
	pApp->BusinessManDlgState = false;
	pApp->CharacterDlgState = false;
	//**************************************加载主角************************************/
	//登场！
	IniHeroPatrick();
	//带上一些钱
	pApp->Patrick.Money = 300;
	//拿起武器
	IniHeroEquipment(pApp->Patrick);
	//背上行囊
	IniHeroBag();
	/**************************************加载子弹**************************************/
	BulletVector.resize(30);
	for (int i = 0; i < 30; i++)
	{
		BulletVector[i].State = PREPARED;
		BulletVector[i].Type = ORB;
		BulletVector[i].Speed = 5;
	}
	/**************************************加载NPC***************************************/
	IniBusinessManItem();

	return TRUE;
}
/*----------------------------------------------------------------------开始绘制窗口----------------------------------------------*/
void CChildView::OnPaint() 
{
	//CPaintDC dc(this); // 用于绘制的设备上下文
	CDC *cDC = this->GetDC();   //获得当前窗口的DC   
	GetClientRect(&m_client);   //获得窗口的尺寸
	
	// TODO: 在此处添加消息处理程序代码


	//创建缓冲DC
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheCBitmap.CreateCompatibleBitmap(cDC, m_client.Width(), m_client.Height());
	m_cacheDC.SelectObject(&m_cacheCBitmap);

	//把背景图片贴出
	m_BackGroundImage.Draw(m_cacheDC, m_client);
	//把障碍物图片贴出
	ShowMap();
	//把UI界面贴出
	m_UIImage.Draw(m_cacheDC, m_client);
	//生成NPC
	ShowBusinessMan();
	//把子弹图片贴出
	ShowBullet();
	//把主角图片贴出
	ShowHero();
	//把主角装备贴出
	ShowHeroEquipment();
	//贴出怪物图像
	ShowMonster();
	//贴出按钮图像
	ShowButton();
	//将人物HP显示在左上角
	ShowHP();
	//将缓冲DC上的图贴在客户窗口区
	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);
	//把测试用的蒙版地图贴出
	//m_BlackBackGround.Draw(*cDC, m_client);             //当时调整蒙版地图和背景坐标一致的时候留下的
	ValidateRect(&m_client);//使窗口有效
		 //释放缓冲DC										  //如果没有这两句
	m_cacheDC.DeleteDC();								  //将会内存溢出，触发一个断点
	     //释放缓冲位图对象								  //<--------------
	m_cacheCBitmap.DeleteObject();						  //<--------------
	     //释放显示DC
	ReleaseDC(cDC);
	//ReleaseDC(&m_cacheDC);							  //触发断点后，这样尝试做，无法解决问题
	// 不要为绘制消息而调用 CWnd::OnPaint()
}
/*---------------------------------------------------------------------------OnPaint函数结束-------------------------------------*/

/*-----------------------------------------------------------------------键盘响应--------------------------------------------------*/
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)            
{ 
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
		
	case'D':
		pApp->Patrick.Direction = RIGHT;
		if (CanPass() == true)
		{
			pApp->OnControl = true;
			pApp->KeyRight = true;
		}
		else 
			pApp->Patrick.Position_x -= 2;
		
		break;
	case'W':
		pApp->Patrick.Direction = UP;
		if (CanPass() == true)
		{
			pApp->OnControl = true;
			pApp->KeyUp = true;
		}
		else 
			pApp->Patrick.Position_y += 2;
		break;
	case'A':
		pApp->Patrick.Direction = LEFT;
		if (CanPass() == true)
		{
			pApp->OnControl = true;
			pApp->KeyLeft = true;
		}
		else
			pApp->Patrick.Position_x += 2;
		break;
	case'S':
		pApp->Patrick.Direction = DOWN;
		if (CanPass() == true)
		{
			pApp->OnControl = true;
			pApp->KeyDown = true;
		}
		else
			pApp->Patrick.Position_y -= 4;
		break;
	case'J':
		IniBullet();
		break;
	case'K':
		if (BulletWaste == pApp->Patrick.BulletBox)
		{
			//Sleep(1000);										//玩家可以交钱把这行代码注释掉，算是买加速器了，呵呵...
			BulletWaste = 0;									//（其实是在尝试让换弹夹有个时间 不过后来感觉没什么意思 不做了
		}
		break;
	case 'I':
		BagButton();
		break;
	case'O':
		CharacterButton();
		break;
	case 'U':
		if (pApp->BusinessManDlgState == false)
		{
			MeetBusinessMan();
			pApp->BusinessManDlgState = true;
		}
		else if (pApp->BusinessManDlgState == true)
		{
			pBusinessManDlg->OnOK();
			pApp->BusinessManDlgState = false;
		}
		break;
	}
	//CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	switch (nChar)
	{
	case'D':
		pApp->KeyRight = false;
		pApp->OnControl = false;
		break;
	case'W':
		pApp->KeyUp = false;
		pApp->OnControl = false;
		break;
	case'A':
		pApp->KeyLeft = false;
		pApp->OnControl = false;
		break;
	case'S':
		pApp->KeyDown = false;
		pApp->OnControl = false;
		break;
	}
	//CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

/*----------------------------------------------------------------------------------------------鼠标单击响应函数-------------------*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (CRect(10, 780, 80, 830).PtInRect(point))
	{
		BagButton();
	}
	if (CRect(80, 780, 140, 830).PtInRect(point))
	{
		CharacterButton();
	}
	CWnd::OnLButtonDown(nFlags, point);
}
/*----------------------------------------------------------------------------------------------按钮点击响应函数--------------------*/
void CChildView::BagButton()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	//AfxMessageBox(_T("被点击了"));						//测试遗留
	if (pApp->BagDlgState == false)
	{
		pBagDlg = new BagDlg();
		pBagDlg->Create(IDD_BAGDIALOG);
		pBagDlg->ShowWindow(SW_SHOWNORMAL);
		pApp->BagDlgState = true;
	}
	else if (pApp->BagDlgState == true)
	{
		pBagDlg->OnOK();
		pApp->BagDlgState = false;
	}
}

void CChildView::CharacterButton()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	if (pApp->CharacterDlgState == false)
	{
		pCharacterDlg = new CharacterDlg();
		pCharacterDlg->Create(IDD_CHARACTERDLG);
		pCharacterDlg->ShowWindow(SW_SHOWNORMAL);
		pApp->CharacterDlgState = true;
	}
	else if (pApp->CharacterDlgState == true)
	{
		pCharacterDlg->OnOK();
		pApp->CharacterDlgState = false;
	}
}
/*---------------------------------------------------------------------------------------------------定时器----------------------*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case TIMER_PAINT:
		OnPaint();
		break;
	case TIMER_HEROMOVE:
		MapChange();
		if(CanPass()==true)
		pApp->Patrick.Move();
		break;
	case TIMER_BULLET:
		BulletReload();
		BulletOut();
		BulletMove();
		break;
	case TIMER_MONSTERMOVE:
		MonsterMove();
		break;
	case TIMER_MONSTERCHANGEDIREC:
		MonsterChangeDirec();
		break;
	case TIMER_MONSTERATTACK:
		MonsterAttack();
		break;
	case TIMER_RESTOREHP:
		RestoreHP(pApp->Patrick);
		break;
	case TIMER_BUSINESSMAN:
		BusinessManRenew();
		break;

	}
	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	SetTimer(TIMER_PAINT, 10, NULL);						//重绘定时器
	SetTimer(TIMER_HEROMOVE, 5, NULL);						//人物行走定时器
	SetTimer(TIMER_BULLET, 10, NULL);						//子弹定时器
	SetTimer(TIMER_MONSTERMOVE, 10, NULL);					//怪物行走定时器
	SetTimer(TIMER_MONSTERCHANGEDIREC, 3000, NULL);			//怪物改变方向定时器
	SetTimer(TIMER_MONSTERATTACK, 1700, NULL);				//怪物攻击定时器
	SetTimer(TIMER_RESTOREHP, 7000, NULL);					//自动回血定时器
	SetTimer(TIMER_BUSINESSMAN, 60000, NULL);				//商人进货定时器
	return 0;
}
/*----------------------------------------------------------------------------------------------贴出英雄图片----------------------*/
void CChildView::ShowHero()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	switch (pApp->Patrick.Direction)
	{
	case DOWN:
		m_HeroImage_DOWN.Draw
		(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
			pApp->Patrick.width, pApp->Patrick.height);
		break;
	case UP:
		m_HeroImage_UP.Draw
		(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
			pApp->Patrick.width, pApp->Patrick.height);
		break;
	case LEFT:
		m_HeroImage_LEFT.Draw
		(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
			pApp->Patrick.width, pApp->Patrick.height);
		break;
	case RIGHT:
		m_HeroImage_RIGHT.Draw
		(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
			pApp->Patrick.width, pApp->Patrick.height);
		break;
		//m_HeroImage.Draw(*cDC, m_Hero);                  //这是另一种贴出来的方法，不过没用双缓冲
	}
}
/*------------------------------------------------------------------------------------------贴出英雄装备----------------------------*/
void CChildView::ShowHeroEquipment()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	for (int i = 0; i < 4; i++)
	{
		if (pApp->EquipmentVector[i]->State == EQUIPON)
		{

			switch (pApp->EquipmentVector[i]->Name)
			{
			case WOODBOW:
				switch (pApp->Patrick.Direction)
				{
				case UP:
					m_WoodBowImage_UP.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case DOWN:
					m_WoodBowImage_DOWN.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case LEFT:
					m_WoodBowImage_LEFT.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case RIGHT:
					m_WoodBowImage_RIGHT.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				}
				break;
			case WOODWAND:
				switch (pApp->Patrick.Direction)
				{
				case UP:
					m_WoodWandImage_UP.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case DOWN:
					m_WoodWandImage_DOWN.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case LEFT:
					m_WoodWandImage_LEFT.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case RIGHT:
					m_WoodWandImage_RIGHT.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				}
				break;
			case HAT1:
				switch (pApp->Patrick.Direction)
				{
				case UP:
					m_Hat1Image_UP.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case DOWN:
					m_Hat1Image_DOWN.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case LEFT:
					m_Hat1Image_LEFT.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case RIGHT:
					m_Hat1Image_RIGHT.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				}
				break;
			case CLOTH1:
				switch (pApp->Patrick.Direction)
				{
				case UP:
					m_Cloth1Image_UP.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case DOWN:
					m_Cloth1Image_DOWN.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case LEFT:
					m_Cloth1Image_LEFT.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case RIGHT:
					m_Cloth1Image_RIGHT.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				}
				break;
			case SHOES1:
				switch (pApp->Patrick.Direction)
				{
				case UP:
					m_Shoes1Image_UP.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case DOWN:
					m_Shoes1Image_DOWN.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case LEFT:
					m_Shoes1Image_LEFT.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				case RIGHT:
					m_Shoes1Image_RIGHT.Draw(m_cacheDC, pApp->Patrick.Position_x, pApp->Patrick.Position_y,
						pApp->Patrick.width, pApp->Patrick.height);
					break;
				}
				break;
			}
		}
	}
}
/*------------------------------------------------------如果单独加入BLOCK--------------------在蒙版地图上标记障碍物的位置-------------*/
/*void CChildView::SetBlackPixel(const Block& block)
{
	for (int i = block.Position_y; i < (block.Position_y + block.height); i++)
	{
		for (int j = block.Position_x; j < (block.Position_x + block.width); j++)         //方法舍弃，直接在IniMap函数里
		{																					在蒙版地图上标记所有障碍物位置
			m_BlackBackGround.SetPixel(j, i, RGB(0, 0, 0));									放弃Block类，在OnPaint函数里直接
		}																					根据地图二维数组贴出图像
	}																						不过如果要做可以破坏的场景地图块
																							可以用Block类实现
}*/
/*-------------------------------------------------------------------------------------------判断能否通行----------------------*/
bool CChildView::CanPass()																  //CanPass函数的无参数重载
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	if (pApp->Patrick.Position_x < 10 || pApp->Patrick.Position_y < 10
		|| (pApp->Patrick.Position_x+50)>1110 || (pApp->Patrick.Position_y+70)>830)                 //判断是否出地图边界
		return false;
	switch (pApp->Patrick.Direction)																//判断是否遇到障碍
	{
	case UP:
		for (int i = pApp->Patrick.Position_x;i < (pApp->Patrick.Position_x + pApp->Patrick.width);i++)
		{
			if (m_BlackBackGround.GetPixel(i, pApp->Patrick.Position_y) == RGB(0, 0, 0))
				return false;
		}
		return true;
		break;
	case DOWN:
		for (int i = pApp->Patrick.Position_x; i < (pApp->Patrick.Position_x + pApp->Patrick.width); i++)
		{
			if (m_BlackBackGround.GetPixel(i, pApp->Patrick.Position_y+ pApp->Patrick.height) == RGB(0, 0, 0))
				return false;
		}
		return true;
		break;
	case LEFT:
		for (int i = pApp->Patrick.Position_y; i < (pApp->Patrick.Position_y + pApp->Patrick.height); i++)
		{
			if (m_BlackBackGround.GetPixel(pApp->Patrick.Position_x,i ) == RGB(0, 0, 0))
				return false;
		}
		return true;
		break;
	case RIGHT:
		for (int i = pApp->Patrick.Position_y; i < (pApp->Patrick.Position_y + pApp->Patrick.height); i++)
		{
			if (m_BlackBackGround.GetPixel(pApp->Patrick.Position_x + pApp->Patrick.width,i ) == RGB(0, 0, 0))
				return false;
		}
		return true;
		break;

	}
	
}

//CanPass函数的怪物重载
bool CChildView::CanPass(CMonster monster)
{
	if (monster.Position_x < 3 || monster.Position_y < 3
		|| (monster.Position_x + 50)>1117 || (monster.Position_y + 70)>837)                   //判断是否出地图边界
		return false;
	switch (monster.Direction)													              //判断是否遇到障碍
	{
	case UP:
		for (int i = monster.Position_x; i < (monster.Position_x + monster.width); i++)
		{
			if (m_BlackBackGround.GetPixel(i, monster.Position_y) == RGB(0, 0, 0))
				return false;
		}
		return true;
		break;
	case DOWN:
		for (int i = monster.Position_x; i < (monster.Position_x + monster.width); i++)
		{
			if (m_BlackBackGround.GetPixel(i, monster.Position_y + monster.height) == RGB(0, 0, 0))
				return false;
		}
		return true;
		break;
	case LEFT:
		for (int i = monster.Position_y; i < (monster.Position_y + monster.height); i++)
		{
			if (m_BlackBackGround.GetPixel(monster.Position_x, i) == RGB(0, 0, 0))
				return false;
		}
		return true;
		break;
	case RIGHT:
		for (int i = monster.Position_y; i < (monster.Position_y + monster.height); i++)
		{
			if (m_BlackBackGround.GetPixel(monster.Position_x + monster.width, i) == RGB(0, 0, 0))
				return false;
		}
		return true;
		break;

	}

}
/*----------------------------------------------------------------------------------初始化蒙版地图函数----------------------------------*/
void CChildView::IniMap(int MapArray[12][16])
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			switch (MapArray[j][i])
			{
			case GROUND:
				break;
			case GRASS:		//这些是原本打算画的别的地图块，但是时间关系 没有画
			case MARSH:
			case WOOD:
			case COBWEB:
			case STONE:
				for (int m = 0; m < 70; m++)
				{
					for (int n = 0; n < 70; n++)        
					{
							m_BlackBackGround.SetPixel((i*70+n), (j*70+m), RGB(0, 0, 0));									
					}																					
				}																						

				break;
			}
		}
	}
}
/*---------------------------------------------------------------------------------------------显示地图---------------------------*/
void CChildView::ShowMap()
{
	//把背景图片贴出
	//m_BackGroundImage.Draw(m_cacheDC, m_client);

	//把障碍物图片贴出
	
		switch(CurrentMap)
		{
		case TOWN:
			for (int Y = 0; Y < 16; Y++)
			{
				for (int X = 0; X < 12; X++)
				{
					switch (Town_Map[X][Y])
					{
					case GROUND:
						break;
					case GRASS:
						break;
					case MARSH:
						break;
					case WOOD:
						m_WoodImage.Draw(m_cacheDC, Y * 70, X * 70, 70, 70);
						break;
					case COBWEB:
						break;
					case STONE:
						m_StoneImage.Draw(m_cacheDC, Y * 70, X * 70, 70, 70);
						break;

					}
				}
			}
			break;
		case FIELD_1:
			for (int Y = 0; Y < 16; Y++)
			{
				for (int X = 0; X < 12; X++)
				{
					switch (Field_1_Map[X][Y])
					{
					case GROUND:
						break;
					case GRASS:
						break;
					case MARSH:
						break;
					case WOOD:
						m_WoodImage.Draw(m_cacheDC, Y * 70, X * 70, 70, 70);
						break;
					case COBWEB:
						break;
					case STONE:
						m_StoneImage.Draw(m_cacheDC, Y * 70, X * 70, 70, 70);
						break;

					}
				}
			}
			break;
		case FIELD_2:
			for (int Y = 0; Y < 16; Y++)
			{
				for (int X = 0; X < 12; X++)
				{
					switch (Field_2_Map[X][Y])
					{
					case GROUND:
						break;
					case GRASS:
						break;
					case MARSH:
						break;
					case WOOD:
						m_WoodImage.Draw(m_cacheDC, Y * 70, X * 70, 70, 70);
						break;
					case COBWEB:
						break;
					case STONE:
						m_StoneImage.Draw(m_cacheDC, Y * 70, X * 70, 70, 70);
						break;

					}
				}
			}
			break;
		case FIELD_3:
			for (int Y = 0; Y < 16; Y++)
			{
				for (int X = 0; X < 12; X++)
				{
					switch (Field_3_Map[X][Y])
					{
					case GROUND:
						break;
					case GRASS:
						break;
					case MARSH:
						break;
					case WOOD:
						m_WoodImage.Draw(m_cacheDC, Y * 70, X * 70, 70, 70);
						break;
					case COBWEB:
						break;
					case STONE:
						m_StoneImage.Draw(m_cacheDC, Y * 70, X * 70, 70, 70);
						break;

					}
				}
			}
			break;
		case FIELD_4:
			for (int Y = 0; Y < 16; Y++)
			{
				for (int X = 0; X < 12; X++)
				{
					switch (Field_4_Map[X][Y])
					{
					case GROUND:
						break;
					case GRASS:
						break;
					case MARSH:
						break;
					case WOOD:
						m_WoodImage.Draw(m_cacheDC, Y * 70, X * 70, 70, 70);
						break;
					case COBWEB:
						break;
					case STONE:
						m_StoneImage.Draw(m_cacheDC, Y * 70, X * 70, 70, 70);
						break;

					}
				}
			}
			break;

		}
}
/*-------------------------------------------------------------------------------------------------贴出按钮-----------------------*/
void CChildView::ShowButton()
{
	m_BagButtonImage.Draw(m_cacheDC, CRect(10, 780, 70, 830));				//贴出背包按钮图像
	m_CharacterButtonImage.Draw(m_cacheDC, CRect(80, 780, 140, 830));		//贴出人物按钮图像
}
/*-----------------------------------------------------------------------------------------显示人物HP------------------------------*/
void CChildView::ShowHP()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	CDC* pcacheDC = &m_cacheDC;//缓冲DC的指针

	pcacheDC->SetBkMode(TRANSPARENT);
	pcacheDC->TextOutW(70, 30, _T("HP: "));
	CString str;
	str.Format(_T("%d"), pApp->Patrick.HP);
	pcacheDC->TextOutW(105, 30, str);
}
/*-------------------------------------------------------------------------------------------------发射子弹函数-------------------*/
//发射子弹的无参数英雄重载
void CChildView::IniBullet()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	if (pApp->EquipmentVector[3]->State != EMPTY &&
		BulletWaste < pApp->Patrick.BulletBox)
	{
		BulletWaste++;
		for (int i = 0; i < BulletCount; i++)
		{
			if (BulletVector[i].State == PREPARED)
			{
				BulletVector[i].State = FLYING;
				BulletVector[i].Direction = pApp->Patrick.Direction;
				switch (pApp->Patrick.Occupation)
				{
				case HUNTER:
					BulletVector[i].Type = ARROW;
					BulletVector[i].Speed = 12;
					switch (BulletVector[i].Direction)
					{
					case UP:
						BulletVector[i].width = 20;										//这些个变量的赋值可以写构造函数用初始化列表赋
						BulletVector[i].height = 40;									//不过写完了才想起来 懒得改了
						BulletVector[i].Position_x = pApp->Patrick.Position_x + 15;
						BulletVector[i].Position_y = pApp->Patrick.Position_y - 35;
						break;
					case DOWN:
						BulletVector[i].width = 20;
						BulletVector[i].height = 40;
						BulletVector[i].Position_x = pApp->Patrick.Position_x + 15;
						BulletVector[i].Position_y = pApp->Patrick.Position_y + 35;
						break;
					case LEFT:
						BulletVector[i].width = 40;
						BulletVector[i].height = 20;
						BulletVector[i].Position_x = pApp->Patrick.Position_x - 30;
						BulletVector[i].Position_y = pApp->Patrick.Position_y + 25;
						break;
					case RIGHT:
						BulletVector[i].width = 40;
						BulletVector[i].height = 20;
						BulletVector[i].Position_x = pApp->Patrick.Position_x + 30;
						BulletVector[i].Position_y = pApp->Patrick.Position_y + 25;
						break;
					}
					break;
				case MAGE:
					BulletVector[i].Type = ORB;
					BulletVector[i].Speed = 4;
					switch (BulletVector[i].Direction)
					{
					case UP:
						BulletVector[i].width = 20;
						BulletVector[i].height = 40;
						BulletVector[i].Position_x = pApp->Patrick.Position_x + 15;
						BulletVector[i].Position_y = pApp->Patrick.Position_y - 35;
						break;
					case DOWN:
						BulletVector[i].width = 20;
						BulletVector[i].height = 40;
						BulletVector[i].Position_x = pApp->Patrick.Position_x + 15;
						BulletVector[i].Position_y = pApp->Patrick.Position_y + 35;
						break;
					case LEFT:
						BulletVector[i].width = 40;
						BulletVector[i].height = 20;
						BulletVector[i].Position_x = pApp->Patrick.Position_x - 30;
						BulletVector[i].Position_y = pApp->Patrick.Position_y + 25;
						break;
					case RIGHT:
						BulletVector[i].width = 40;
						BulletVector[i].height = 20;
						BulletVector[i].Position_x = pApp->Patrick.Position_x + 30;
						BulletVector[i].Position_y = pApp->Patrick.Position_y + 25;
						break;
					}
					break;
				}
				break;
			}
		}
	}
	
}
//发射子弹的怪物重载
void CChildView::IniBullet(CMonster monster)
{
	for (int i = 0; i < BulletCount; i++)
	{
		if (BulletVector[i].State == PREPARED)
		{
			BulletVector[i].State = FLYING;
			BulletVector[i].ATK = monster.ATK;
			if (monster.Direction != STOPMOVE)
			{
				BulletVector[i].Direction = monster.Direction;
			}
			else
			{
				BulletVector[i].Direction = monster.LateDirec;
			}
			switch (monster.Type)
			{
			case MUDMONSTER:
				BulletVector[i].Type = MUDMONSTERBULLET;
				BulletVector[i].Speed = 4;
				switch (BulletVector[i].Direction)
				{
				case UP:
					BulletVector[i].width = 20;
					BulletVector[i].height = 40;
					BulletVector[i].Position_x = monster.Position_x + 15;
					BulletVector[i].Position_y = monster.Position_y - 35;
					break;
				case DOWN:
					BulletVector[i].width = 20;
					BulletVector[i].height = 40;
					BulletVector[i].Position_x = monster.Position_x + 15;
					BulletVector[i].Position_y = monster.Position_y + 35;
					break;
				case LEFT:
					BulletVector[i].width = 40;
					BulletVector[i].height = 20;
					BulletVector[i].Position_x = monster.Position_x - 30;
					BulletVector[i].Position_y = monster.Position_y + 25;
					break;
				case RIGHT:
					BulletVector[i].width = 40;
					BulletVector[i].height = 20;
					BulletVector[i].Position_x = monster.Position_x + 30;
					BulletVector[i].Position_y = monster.Position_y + 25;
					break;
				}
				break;
			case BLACKGHOST:
				BulletVector[i].Speed = 9;
				BulletVector[i].Type = BLACKGHOSTBULLET;
				switch (BulletVector[i].Direction)
				{
				case UP:
					BulletVector[i].width = 20;
					BulletVector[i].height = 40;
					BulletVector[i].Position_x = monster.Position_x + 15;
					BulletVector[i].Position_y = monster.Position_y - 35;
					break;
				case DOWN:
					BulletVector[i].width = 20;
					BulletVector[i].height = 40;
					BulletVector[i].Position_x = monster.Position_x + 15;
					BulletVector[i].Position_y = monster.Position_y + 35;
					break;
				case LEFT:
					BulletVector[i].width = 40;
					BulletVector[i].height = 20;
					BulletVector[i].Position_x = monster.Position_x - 30;
					BulletVector[i].Position_y = monster.Position_y + 25;
					break;
				case RIGHT:
					BulletVector[i].width = 40;
					BulletVector[i].height = 20;
					BulletVector[i].Position_x = monster.Position_x + 30;
					BulletVector[i].Position_y = monster.Position_y + 25;
					break;
				}
				break;
			}
			break;
		}
	}
}
/*-------------------------------------------------------------------------------------------------贴出子弹函数--------------------*/
void CChildView::ShowBullet()								//注意现在只是测试，默认bullet是Arrow，加入职业系统之后要改的 弓手是arrow 法师是orb 用一个switch选择
{
	for (int i = 0; i < BulletCount; i++)
	{
		if (BulletVector[i].State == FLYING)
		{
			switch (BulletVector[i].Type)
			{
			case ARROW:
				switch (BulletVector[i].Direction)
				{
				case UP:
					m_ArrowImage_UP.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case DOWN:
					m_ArrowImage_DOWN.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case LEFT:
					m_ArrowImage_LEFT.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case RIGHT:
					m_ArrowImage_RIGHT.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				}
				break;
			case ORB:
				switch (BulletVector[i].Direction)
				{
				case UP:
					m_OrbImage_UP.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case DOWN:
					m_OrbImage_DOWN.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case LEFT:
					m_OrbImage_LEFT.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case RIGHT:
					m_OrbImage_RIGHT.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				}
				break;
			case MUDMONSTERBULLET:
				switch (BulletVector[i].Direction)
				{
				case UP:
					m_MudMonsterBulletImage_UP.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case DOWN:
					m_MudMonsterBulletImage_DOWN.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case LEFT:
					m_MudMonsterBulletImage_LEFT.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case RIGHT:
					m_MudMonsterBulletImage_RIGHT.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				}
				break;
			case BLACKGHOSTBULLET:
				switch (BulletVector[i].Direction)
				{
				case UP:
					m_BlackGhostBulletImage_UP.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case DOWN:
					m_BlackGhostBulletImage_DOWN.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case LEFT:
					m_BlackGhostBulletImage_LEFT.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				case RIGHT:
					m_BlackGhostBulletImage_RIGHT.Draw(m_cacheDC,
						BulletVector[i].Position_x,
						BulletVector[i].Position_y,
						BulletVector[i].width,
						BulletVector[i].height);
					break;
				}
				break;
			}
		}
	}
}
/*----------------------------------------------------------------------------子弹飞行函数------------------------------------------*/
void CChildView::BulletMove()
{
	for (int i = 0; i < BulletCount; i++)
	{
		if (BulletVector[i].State == FLYING)
		{
			if (BulletVector[i].Type == ORB ||
				BulletVector[i].Type == ARROW)
			{
				BulletHitMonster(i);
			}
			else
			{
				BulletHitHero(i);
			}
			switch (BulletVector[i].Direction)
			{
			case UP:
				BulletVector[i].Position_y -= BulletVector[i].Speed;
				break;
			case DOWN:
				BulletVector[i].Position_y += BulletVector[i].Speed;
				break;
			case LEFT:
				BulletVector[i].Position_x -= BulletVector[i].Speed;
				break;
			case RIGHT:
				BulletVector[i].Position_x += BulletVector[i].Speed;
				break;
			}
		}
	}
}
/*----------------------------------------------------------------------------子弹出界判定函数---------------------------------------*/
void CChildView::BulletOut()
{
	//CDC *cDC = this->GetDC();
	for (int i = 0; i < BulletCount ; i++)
	{
		//cDC->TextOutW(0, 0, _T("子弹没有出界"));
		//如果箭飞到了地图边界
		if (BulletVector[i].Position_x < 0 ||
			BulletVector[i].Position_y > 840 - BulletVector[i].height ||
			BulletVector[i].Position_y < 0 ||
			BulletVector[i].Position_x > 1120 - BulletVector[i].width)
		{
			if ((BulletVector[i].State == FLYING))
			{
				BulletVector[i].State = DISAPPEAR;
				//cDC->TextOutW(0, 0, _T("子弹出界"));
			}
		}
	}
	for (int count = 0; count < BulletCount; count++)
	{
		switch (BulletVector[count].Direction)													          //判断是否遇到障碍
		{
		case UP:
			if (BulletVector[count].State == FLYING)
			{
				for (int j = BulletVector[count].Position_x; j < (BulletVector[count].Position_x + BulletVector[count].width); j++)
				{
					if (m_BlackBackGround.GetPixel(j, BulletVector[count].Position_y) == RGB(0, 0, 0))
					{
						BulletVector[count].State = DISAPPEAR;
					}
					break;
				}
			}
			break;
		case DOWN:
			if (BulletVector[count].State == FLYING)
			{
				for (int j = BulletVector[count].Position_x; j < (BulletVector[count].Position_x + BulletVector[count].width); j++)
				{
					if (m_BlackBackGround.GetPixel(j, BulletVector[count].Position_y + BulletVector[count].height) == RGB(0, 0, 0))
					{
						BulletVector[count].State = DISAPPEAR;
					}
					break;
				}
			}
			break;
		case LEFT:
			if (BulletVector[count].State == FLYING)
			{
				for (int j = BulletVector[count].Position_y; j < (BulletVector[count].Position_y + BulletVector[count].height); j++)
				{
					if (m_BlackBackGround.GetPixel(BulletVector[count].Position_x, j) == RGB(0, 0, 0))
					{
						BulletVector[count].State = DISAPPEAR;
					}
					break;
				}
			}
			break;
		case RIGHT:
			if (BulletVector[count].State == FLYING)
			{
				for (int j = BulletVector[count].Position_y; j < (BulletVector[count].Position_y + BulletVector[count].height); j++)
				{
					if (m_BlackBackGround.GetPixel(BulletVector[count].Position_x + BulletVector[count].width, j) == RGB(0, 0, 0))
					{
						BulletVector[count].State = DISAPPEAR;
					}
					break;
				}
			}
			break;
		}

	}
}

/*-----------------------------------------------------------------------------子弹击中怪物判定--------------------------------------*/
void CChildView::BulletHitMonster(int BulletNum)
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	srand((unsigned)time(NULL));
	for (int i = 0; i < MonsterVector.size(); i++)
	{
		if (MonsterVector[i].Disappear == false)
		{
			if (MonsterVector[i].MonsterRect.PtInRect(CPoint(BulletVector[BulletNum].Position_x,
				BulletVector[BulletNum].Position_y)) ||
				MonsterVector[i].MonsterRect.PtInRect(CPoint(BulletVector[BulletNum].Position_x + BulletVector[BulletNum].width,
					BulletVector[BulletNum].Position_y)) ||
				MonsterVector[i].MonsterRect.PtInRect(CPoint(BulletVector[BulletNum].Position_x + BulletVector[BulletNum].width,
					BulletVector[BulletNum].Position_y + BulletVector[BulletNum].height)) ||
				MonsterVector[i].MonsterRect.PtInRect(CPoint(BulletVector[BulletNum].Position_x,
					BulletVector[BulletNum].Position_y + BulletVector[BulletNum].height)))
			{
				MonsterVector[i].HP -= pApp->Patrick.ATK - MonsterVector[i].DEF;
				BulletVector[BulletNum].State = DISAPPEAR;
				if (MonsterVector[i].HP <= 0)
				{
					MonsterVector[i].Disappear = true;
					switch (MonsterVector[i].Type)
					{
					case MUDMONSTER:
						pApp->Patrick.Money += rand() % 20 + 4;
						break;
					case BLACKGHOST:
						pApp->Patrick.Money += rand() % 10 + 5;
						break;
					}
				}
			}
		}
	}
}
/*---------------------------------------------------------------------------------------子弹击中英雄判定----------------------------*/
void CChildView::BulletHitHero(int BulletNum)
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	if (pApp->Patrick.HeroRect.PtInRect(CPoint(BulletVector[BulletNum].Position_x,
		BulletVector[BulletNum].Position_y)) ||
		pApp->Patrick.HeroRect.PtInRect(CPoint(BulletVector[BulletNum].Position_x + BulletVector[BulletNum].width,
			BulletVector[BulletNum].Position_y)) ||
		pApp->Patrick.HeroRect.PtInRect(CPoint(BulletVector[BulletNum].Position_x + BulletVector[BulletNum].width,
			BulletVector[BulletNum].Position_y + BulletVector[BulletNum].height)) ||
		pApp->Patrick.HeroRect.PtInRect(CPoint(BulletVector[BulletNum].Position_x,
			BulletVector[BulletNum].Position_y + BulletVector[BulletNum].height)))
	{
		if ((BulletVector[BulletNum].ATK - pApp->Patrick.DEF) > 0)
		{
			pApp->Patrick.HP -= BulletVector[BulletNum].ATK - pApp->Patrick.DEF;
		}
		else
		{
			pApp->Patrick.HP -= 1;
		}
		BulletVector[BulletNum].State = DISAPPEAR;
		if (pApp->Patrick.HP <= 0)
		{
			HeroReborn();
		}
	}
}
/*---------------------------------------------------------------------------------------地图上怪物的初始化--------------------------*/
void CChildView::IniMonster(int MonsterArray[][3])
{
	MonsterVector.resize(MonsterArray[0][0]);
	int Count = MonsterVector.size();
	for (int i = 0; i < Count; i++)
	{
		switch (MonsterArray[i + 1][0])
		{
		case BLACKGHOST:
			MonsterVector[i].Type = BLACKGHOST;
			MonsterVector[i].Position_x = MonsterArray[i + 1][1];
			MonsterVector[i].Position_y = MonsterArray[i + 1][2];
			MonsterVector[i].Appear();
			break;
		case MUDMONSTER:
			MonsterVector[i].Type = MUDMONSTER;
			MonsterVector[i].Position_x = MonsterArray[i + 1][1];
			MonsterVector[i].Position_y = MonsterArray[i + 1][2];
			MonsterVector[i].Appear();
			break;
		}
		

	}
}
/*----------------------------------------------------------------------------------------贴出怪物图像函数--------------------------*/
void CChildView::ShowMonster()
{
	for (int i = 0; i < MonsterVector.size(); i++)
	{
		if (MonsterVector[i].Disappear == false)
		{
			if (MonsterVector[i].Direction == STOPMOVE)
			{
				MonsterVector[i].Direction = MonsterVector[i].LateDirec;
				switch (MonsterVector[i].Type)
				{
				case BLACKGHOST:
					switch (MonsterVector[i].Direction)
					{
					case UP:
						m_BlackGhostImage_UP.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case DOWN:
						m_BlackGhostImage_DOWN.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case LEFT:
						m_BlackGhostImage_LEFT.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case RIGHT:
						m_BlackGhostImage_RIGHT.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					}
					break;
				case MUDMONSTER:
					switch (MonsterVector[i].Direction)
					{
					case UP:
						m_MudMonsterImage_UP.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case DOWN:
						m_MudMonsterImage_DOWN.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case LEFT:
						m_MudMonsterImage_LEFT.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case RIGHT:
						m_MudMonsterImage_RIGHT.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					}
					break;
				}
				MonsterVector[i].Direction = STOPMOVE;
			}
			else
			{
				switch (MonsterVector[i].Type)
				{
				case BLACKGHOST:
					switch (MonsterVector[i].Direction)
					{
					case UP:
						m_BlackGhostImage_UP.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case DOWN:
						m_BlackGhostImage_DOWN.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case LEFT:
						m_BlackGhostImage_LEFT.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case RIGHT:
						m_BlackGhostImage_RIGHT.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					}
					break;
				case MUDMONSTER:
					switch (MonsterVector[i].Direction)
					{
					case UP:
						m_MudMonsterImage_UP.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case DOWN:
						m_MudMonsterImage_DOWN.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case LEFT:
						m_MudMonsterImage_LEFT.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					case RIGHT:
						m_MudMonsterImage_RIGHT.Draw(m_cacheDC,
							MonsterVector[i].Position_x,
							MonsterVector[i].Position_y,
							MonsterVector[i].width,
							MonsterVector[i].height);
						break;
					}
					break;
				}
			}
		}
	}
}
/*-----------------------------------------------------------------------------------------------重置子弹函数----------------------*/
void CChildView::BulletReload()
{
	CDC *cDC = this->GetDC();
	for (int i = 0; i < BulletCount; i++)
	{
		if (BulletVector[i].State == DISAPPEAR)
		{
			BulletVector[i].State = PREPARED;
		}
		
	}
}
/*-----------------------------------------------------------------------------------------------实现怪物随机移动----------------------*/
void CChildView::MonsterMove()
{
	for (int i = 0; i < MonsterVector.size(); i++)
	{
		if (CanPass(MonsterVector[i]) == true)
		{
			switch (MonsterVector[i].Direction)
			{
			case UP:
				MonsterVector[i].Position_y -= MonsterVector[i].Speed;
				break;
			case DOWN:
				MonsterVector[i].Position_y += MonsterVector[i].Speed;
				break;
			case LEFT:
				MonsterVector[i].Position_x -= MonsterVector[i].Speed;
				break;
			case RIGHT:
				MonsterVector[i].Position_x += MonsterVector[i].Speed;
				break;
			case STOPMOVE:
				break;
			}
		}
		else
		{
			switch (MonsterVector[i].Direction)
			{
			case UP:
				MonsterVector[i].Direction = DOWN;
				break;
			case DOWN:
				MonsterVector[i].Direction = UP;
				break;
			case LEFT:
				MonsterVector[i].Direction = RIGHT;
				break;
			case RIGHT:
				MonsterVector[i].Direction = LEFT;
				break;
			}
		}
		MonsterVector[i].MonsterRect.top = MonsterVector[i].Position_y;
		MonsterVector[i].MonsterRect.left = MonsterVector[i].Position_x;
		MonsterVector[i].MonsterRect.bottom = MonsterVector[i].Position_y + MonsterVector[i].height;
		MonsterVector[i].MonsterRect.right = MonsterVector[i].Position_x + MonsterVector[i].width;
	}
}

void CChildView::MonsterChangeDirec()
{
	for (int i = 0; i < MonsterVector.size(); i++)
	{
		MonsterVector[i].LateDirec = MonsterVector[i].Direction;
	Ini: MonsterVector[i].Direction = (rand() % 5);
		if (MonsterVector[i].Direction==STOPMOVE &&
			MonsterVector[i].Direction == MonsterVector[i].LateDirec)
		{
			goto Ini;
		}
	}
}
/*-----------------------------------------------------------------------------------------------------怪物攻击-------------------*/
void CChildView::MonsterAttack()
{
	for (int i = 0; i < MonsterVector.size(); i++)
	{
		if(MonsterVector[i].Disappear==false)
		{
			IniBullet(MonsterVector[i]);
		}
	}
}
/*----------------------------------------------------------------------------------------------------清除怪物--------------------*/
void CChildView::KillMonster()
{
	for (int i = 0; i < MonsterVector.size(); i++)
	{
		MonsterVector[i].Disappear = true;
	}
}
/*----------------------------------------------------------------------------------------------------清除子弹---------------------*/
void CChildView::KillBullet()
{
	for (int i = 0; i < BulletCount; i++)
	{
		BulletVector[i].State = DISAPPEAR;
	}
}
/*-----------------------------------------------------------------------------------------------------地图切换-------------------*/
void CChildView::MapChange()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	switch (CurrentMap)
	{
	case TOWN:
		if (pApp->Patrick.Position_x < 770 &&
			pApp->Patrick.Position_x > 700 &&
			pApp->Patrick.Position_y < 70)
		{
			LateMap = TOWN;
			CurrentMap = FIELD_1;
			m_BlackBackGround = m_BlackBackGround2;
			m_BackGroundImage = m_BackGroundImage2;
			IniMap(Field_1_Map);
			KillMonster();
			KillBullet();
			IniMonster(Field_1_Monster);
			pApp->Patrick.Position_x = 710;
			pApp->Patrick.Position_y = 760;
			pApp->Patrick.HeroRect.top = pApp->Patrick.Position_y;
			pApp->Patrick.HeroRect.left = pApp->Patrick.Position_x;
			pApp->Patrick.HeroRect.bottom = pApp->Patrick.Position_y + pApp->Patrick.height;
			pApp->Patrick.HeroRect.right = pApp->Patrick.Position_x + pApp->Patrick.width;
		}
		break;
	case FIELD_1:
		if (pApp->Patrick.Position_x < 560 &&
			pApp->Patrick.Position_x > 490 &&
			pApp->Patrick.Position_y < 70)
		{
			LateMap = FIELD_1;
			CurrentMap = FIELD_2;
			m_BlackBackGround = m_BlackBackGround3;
			m_BackGroundImage = m_BackGroundImage3;
			IniMap(Field_2_Map);
			KillMonster();
			KillBullet();
			IniMonster(Field_2_Monster);
			pApp->Patrick.Position_x = 500;
			pApp->Patrick.Position_y = 700;
			pApp->Patrick.HeroRect.top = pApp->Patrick.Position_y;
			pApp->Patrick.HeroRect.left = pApp->Patrick.Position_x;
			pApp->Patrick.HeroRect.bottom = pApp->Patrick.Position_y + pApp->Patrick.height;
			pApp->Patrick.HeroRect.right = pApp->Patrick.Position_x + pApp->Patrick.width;
		}
		else if (pApp->Patrick.Position_x < 770 &&
			pApp->Patrick.Position_x > 700 &&
			pApp->Patrick.Position_y > 760)
		{
			LateMap = FIELD_1;
			CurrentMap = TOWN;
			m_BlackBackGround = m_BlackBackGround1;
			m_BackGroundImage = m_BackGroundImage1;
			IniMap(Town_Map);
			KillMonster();
			KillBullet();
			IniMonster(Town_Monster);
			pApp->Patrick.Position_x = 710;
			pApp->Patrick.Position_y = 76;
			pApp->Patrick.HeroRect.top = pApp->Patrick.Position_y;
			pApp->Patrick.HeroRect.left = pApp->Patrick.Position_x;
			pApp->Patrick.HeroRect.bottom = pApp->Patrick.Position_y + pApp->Patrick.height;
			pApp->Patrick.HeroRect.right = pApp->Patrick.Position_x + pApp->Patrick.width;
		}
		break;
	case FIELD_2:
		if (pApp->Patrick.Position_y < 350 &&
			pApp->Patrick.Position_y > 280 &&
			pApp->Patrick.Position_x > 1050)
		{
			LateMap = FIELD_2;
			CurrentMap = FIELD_3;
			m_BlackBackGround = m_BlackBackGround4;
			m_BackGroundImage = m_BackGroundImage4;
			IniMap(Field_3_Map);
			KillMonster();
			KillBullet();
			IniMonster(Field_3_Monster);
			pApp->Patrick.Position_x = 50;
			pApp->Patrick.Position_y = 285;
			pApp->Patrick.HeroRect.top = pApp->Patrick.Position_y;
			pApp->Patrick.HeroRect.left = pApp->Patrick.Position_x;
			pApp->Patrick.HeroRect.bottom = pApp->Patrick.Position_y + pApp->Patrick.height;
			pApp->Patrick.HeroRect.right = pApp->Patrick.Position_x + pApp->Patrick.width;
		}
		else if (pApp->Patrick.Position_x < 560 &&
			pApp->Patrick.Position_x > 490 &&
			pApp->Patrick.Position_y > 760)
		{
			LateMap = FIELD_2;
			CurrentMap = FIELD_1;
			m_BlackBackGround = m_BlackBackGround2;
			m_BackGroundImage = m_BackGroundImage2;
			IniMap(Field_1_Map);
			KillMonster();
			KillBullet();
			IniMonster(Field_1_Monster);
			pApp->Patrick.Position_x = 500;
			pApp->Patrick.Position_y = 73;
			pApp->Patrick.HeroRect.top = pApp->Patrick.Position_y;
			pApp->Patrick.HeroRect.left = pApp->Patrick.Position_x;
			pApp->Patrick.HeroRect.bottom = pApp->Patrick.Position_y + pApp->Patrick.height;
			pApp->Patrick.HeroRect.right = pApp->Patrick.Position_x + pApp->Patrick.width;
		}
		break;
	case FIELD_3:
		if (pApp->Patrick.Position_y < 560 &&
			pApp->Patrick.Position_y > 490 &&
			pApp->Patrick.Position_x > 1050)
		{
			LateMap = FIELD_3;
			CurrentMap = FIELD_4;
			m_BlackBackGround = m_BlackBackGround5;
			m_BackGroundImage = m_BackGroundImage5;
			IniMap(Field_4_Map);
			KillMonster();
			KillBullet();
			IniMonster(Field_4_Monster);
			pApp->Patrick.Position_x = 50;
			pApp->Patrick.Position_y = 495;
			pApp->Patrick.HeroRect.top = pApp->Patrick.Position_y;
			pApp->Patrick.HeroRect.left = pApp->Patrick.Position_x;
			pApp->Patrick.HeroRect.bottom = pApp->Patrick.Position_y + pApp->Patrick.height;
			pApp->Patrick.HeroRect.right = pApp->Patrick.Position_x + pApp->Patrick.width;
		}
		else if (pApp->Patrick.Position_y < 350 &&
			pApp->Patrick.Position_y > 280 &&
			pApp->Patrick.Position_x < 30)
		{
			LateMap = FIELD_3;
			CurrentMap = FIELD_2;
			m_BlackBackGround = m_BlackBackGround3;
			m_BackGroundImage = m_BackGroundImage3;
			IniMap(Field_2_Map);
			KillMonster();
			KillBullet();
			IniMonster(Field_2_Monster);
			pApp->Patrick.Position_x = 1044;
			pApp->Patrick.Position_y = 283;
			pApp->Patrick.HeroRect.top = pApp->Patrick.Position_y;
			pApp->Patrick.HeroRect.left = pApp->Patrick.Position_x;
			pApp->Patrick.HeroRect.bottom = pApp->Patrick.Position_y + pApp->Patrick.height;
			pApp->Patrick.HeroRect.right = pApp->Patrick.Position_x + pApp->Patrick.width;
		}
		break;
	case FIELD_4:
		if (pApp->Patrick.Position_y < 560 &&
			pApp->Patrick.Position_y > 490 &&
			pApp->Patrick.Position_x < 30)
		{
			LateMap = FIELD_4;
			CurrentMap = FIELD_3;
			m_BlackBackGround = m_BlackBackGround4;
			m_BackGroundImage = m_BackGroundImage4;
			IniMap(Field_3_Map);
			KillMonster();
			KillBullet();
			IniMonster(Field_3_Monster);
			pApp->Patrick.Position_x = 1044;
			pApp->Patrick.Position_y = 493;
			pApp->Patrick.HeroRect.top = pApp->Patrick.Position_y;
			pApp->Patrick.HeroRect.left = pApp->Patrick.Position_x;
			pApp->Patrick.HeroRect.bottom = pApp->Patrick.Position_y + pApp->Patrick.height;
			pApp->Patrick.HeroRect.right = pApp->Patrick.Position_x + pApp->Patrick.width;
		}
		break;
	}
}
/*-----------------------------------------------------------------------------------------------英雄自动回血函数--------------------*/
void CChildView::RestoreHP(CHero &hero)
{
	if (hero.HP < hero.MaxHP)
	{
		hero.HP += 1;
	}
}
/*-----------------------------------------------------------------------------------------------测试初始化英雄装备------------------*/
void CChildView::IniHeroEquipment(CHero &hero)
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	pApp->EquipmentVector.resize(4);
	for (int i = 0; i < 4; i++)
	{
		pApp->EquipmentVector[i] = new CArmour(0, 0, 0);				//如果不这么做则该数组里全都是空指针，会有访问冲突，随便new一个Armour了
		pApp->EquipmentVector[i]->State = EMPTY;
	}
	switch (hero.Occupation)
	{
	case HUNTER:
		delete pApp->EquipmentVector[3];
		pApp->EquipmentVector[3] = new CWeapon(WOODBOW, HUNTER, 100);
		pApp->EquipmentVector[3]->State = EQUIPON;
		pApp->EquipmentVector[3]->Equip(pApp->Patrick);
		break;
	case MAGE:
		delete pApp->EquipmentVector[3];
		pApp->EquipmentVector[3] = new CWeapon(WOODWAND, MAGE, 100);
		pApp->EquipmentVector[3]->State = EQUIPON;
		pApp->EquipmentVector[3]->Equip(pApp->Patrick);
		break;
	}
}
/*-----------------------------------------------------------------------------------------------测试初始化英雄背包------------------*/
void CChildView::IniHeroBag()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	pApp->HeroBagVector.resize(9);
	for (int i = 0; i < 9; i++)
	{
		pApp->HeroBagVector[i] = new CApple(0,0);
		pApp->HeroBagVector[i]->IniEmpty();					//各种变量都设置为零
	}
	delete pApp->HeroBagVector[6];
	pApp->HeroBagVector[6] = new CApple(5,20);
	
}
/*-------------------------------------------------------------------------------------------------初始化英雄-----------------------*/
void CChildView::IniHeroPatrick()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	//英雄在哪里出现
	pApp->Patrick.Position_x = 140;
	pApp->Patrick.Position_y = 140;
	pApp->Patrick.width = 40;
	pApp->Patrick.height = 60;
	//英雄的出生
	pApp->Patrick.ATK = 5;
	pApp->Patrick.DEF = 0;
	pApp->Patrick.Direction = DOWN;
	pApp->Patrick.HP = 50;
	pApp->Patrick.MaxHP = 50;
	//pApp->Patrick.Money = 200;
	pApp->Patrick.Speed = 5;
	pApp->Patrick.Occupation = pApp->OccChoose;
	pApp->Patrick.BulletBox = 5;
}
/*---------------------------------------------------------------------------------------------------初始化商人--------------------*/
void CChildView::IniBusinessManItem()
{
	BusinessManRenew();
}
/*-------------------------------------------------------------------------------------------------------英雄重生------------------*/
void CChildView::HeroReborn()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	/*************英雄重新出现在地图位置****************/
	pApp->Patrick.Position_x = 140;
	pApp->Patrick.Position_y = 140;
	pApp->Patrick.HP = 10;
	/************失去一定金钱*************************/
	pApp->Patrick.Money -= 100;
	if (pApp->Patrick.Money < 0)
	{
		pApp->Patrick.Money = 0;
	}
	/***********在城镇重生***************************/
	LateMap = CurrentMap;
	CurrentMap = TOWN;
	m_BlackBackGround = m_BlackBackGround1;
	m_BackGroundImage = m_BackGroundImage1;
	KillMonster();
	KillBullet();
}
/*--------------------------------------------------------------------------------------贴出商人图片---------------------------------*/
void CChildView::ShowBusinessMan()
{
	if(CurrentMap==TOWN)
	m_BusinessManImage.Draw(m_cacheDC, 100, 580, 150, 130);
}
/*--------------------------------------------------------------------------------------遇到商人------------------------------------*/
void CChildView::MeetBusinessMan()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	if (CurrentMap == TOWN)
	{
		if (
			CRect(100, 580, 250, 710).PtInRect
			(CPoint(pApp->Patrick.Position_x, pApp->Patrick.Position_y)) ||
			CRect(100, 580, 250, 710).PtInRect
			(CPoint(pApp->Patrick.Position_x + 150, pApp->Patrick.Position_y + 130)) ||
			CRect(100, 580, 250, 710).PtInRect
			(CPoint(pApp->Patrick.Position_x + 150, pApp->Patrick.Position_y)) ||
			CRect(100, 580, 250, 710).PtInRect
			(CPoint(pApp->Patrick.Position_x, pApp->Patrick.Position_y + 130))
			)
		{
			pBusinessManDlg = new BusinessManDlg();
			pBusinessManDlg->Create(IDD_BUSINESSDLG);
			pBusinessManDlg->ShowWindow(SW_SHOWNORMAL);
		}
	}
}
/*--------------------------------------------------------------------------------------商人更新物品---------------------------------*/
void CChildView::BusinessManRenew()
{
	CMyRPGApp *pApp = (CMyRPGApp*)AfxGetApp();
	srand((unsigned)time(NULL));
	pApp->BusinessManVector.resize(24);
	for (int i = 0; i < 24; i++)
	{
		pApp->BusinessManVector[i] = new CApple(0,0);
		pApp->BusinessManVector[i]->IniEmpty();
	}
	for (int i = 0; i < 18; i++)
	{
		delete pApp->BusinessManVector[i];
		int name = rand() % 8;
		switch (name)
		{
		case EMPTY:
			pApp->BusinessManVector[i] = new CApple(0,0);
			pApp->BusinessManVector[i]->IniEmpty();
			break;
		case APPLE:
			pApp->BusinessManVector[i] = new CApple(5,20);
			break;
		case VIOLETPOTION:
			pApp->BusinessManVector[i] = new CVioletPotion(5, 50);
			break;
		case WOODBOW:
			pApp->BusinessManVector[i] = new CWeapon(WOODBOW, HUNTER, 100);
			pApp->BusinessManVector[i]->State = EQUIPOFF;
			break;
		case WOODWAND:
			pApp->BusinessManVector[i] = new CWeapon(WOODWAND, MAGE, 100);
			pApp->BusinessManVector[i]->State = EQUIPOFF;
			break;
		case HAT1:
			pApp->BusinessManVector[i] = new CHelmet(HAT1, ALLOCC, 50);
			pApp->BusinessManVector[i]->State = EQUIPOFF;
			break;
		case CLOTH1:
			pApp->BusinessManVector[i] = new CArmour(CLOTH1, ALLOCC, 80);
			pApp->BusinessManVector[i]->State = EQUIPOFF;
			break;
		case SHOES1:
			pApp->BusinessManVector[i] = new CShoes(SHOES1, ALLOCC, 30);
			pApp->BusinessManVector[i]->State = EQUIPOFF;
			break;
		}

	}
}








//2018年的2018行code 