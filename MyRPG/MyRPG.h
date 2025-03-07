
// MyRPG.h: MyRPG 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include <vector>
#include "Header.h"
using std::vector;


// CMyRPGApp:
// 有关此类的实现，请参阅 MyRPG.cpp
//

class CMyRPGApp : public CWinApp
{
public:
	CMyRPGApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	//该程序的全局变量

	//声明键盘响应                     
	bool KeyUp;
	bool KeyDown;
	bool KeyLeft;
	bool KeyRight;
	bool OnControl;

	//英雄相关变量
	CHero Patrick;							//英雄登场
	int OccChoose;							//英雄职业选择
	vector<CEquipment*>EquipmentVector;		//英雄身上的装备数组
	vector<CItem*>HeroBagVector;				//英雄背包数组
	vector<CItem*>BusinessManVector;			//商人物品数组

	//窗口状态
	bool BagDlgState;
	bool BusinessManDlgState;
	bool CharacterDlgState;
};

extern CMyRPGApp theApp;
