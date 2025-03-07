#pragma once
#ifndef MAP_H
#define MAP_H

#define GROUND 0
#define GRASS 1
#define MARSH 2
#define WOOD 3
#define COBWEB 4
#define STONE 5

#define TOWN 0
#define FIELD_1 1
#define FIELD_2 2
#define FIELD_3 3
#define FIELD_4 4

#include "Monster.h"
#include "Block.h"

//初始化地图
	int Town_Map[12][16] = 
	{
		5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,
		5,0,0,0,0,0,5,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,5,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,5,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,5,5,0,0,0,0,0,5,5,5,5,
		5,0,0,0,0,5,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,5,0,0,0,0,5,
		5,5,5,5,5,0,0,0,0,0,5,0,0,0,0,5,
		0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,5,
		0,0,0,0,0,5,0,0,0,0,5,0,0,0,0,5,
		0,0,0,0,0,5,0,0,0,0,5,0,0,0,0,5,
		0,0,0,0,0,5,5,5,5,5,5,5,5,5,5,5
	};
	//地图怪物数组 这个数组的第一行用来确定有几个怪物的，只有[0][0]有意义,[0][1]与[0][2]无意义
	//后面的就是 第一个参数是怪物类型，第二第三个参数是怪物从哪产生,也可以在后面多加一个维度，记录面向方向，不过懒得加了
	int Town_Monster[][3]=
	{
		0,0,0,
	};
	int Field_1_Map[12][16] =
	{
		3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,
		3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,3,
		3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,3,
		3,0,0,0,0,0,3,3,3,3,3,0,0,0,0,3,
		3,0,0,0,3,0,0,3,0,0,0,0,0,0,0,3,
		3,0,0,3,3,0,0,3,0,0,0,3,0,0,0,3,
		3,0,0,0,0,0,0,3,0,0,0,3,3,3,3,3,
		3,0,0,0,0,0,0,3,0,0,0,3,0,0,0,3,
		3,0,0,3,0,0,0,3,0,0,0,0,0,0,0,3,
		3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,3,
		3,0,0,3,0,0,0,0,0,0,0,0,0,0,0,3,
		5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5
	};
	int Field_1_Monster[][3] =
	{
		5,0,0,
		BLACKGHOST,300,140,
		BLACKGHOST,910,700,
		MUDMONSTER,140,140,
		BLACKGHOST,570,550,
		MUDMONSTER,700,100
	};
	int Field_2_Map[12][16] =
	{
		5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
		5,0,0,0,5,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,5,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,5,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,
		5,0,0,5,5,5,5,5,5,5,0,0,0,0,0,5,
		5,0,0,5,0,0,0,0,0,5,5,5,5,5,5,5,
		5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,5,0,0,5,5,5,5,5,5,0,0,0,5,
		5,0,0,5,0,0,5,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,5,0,0,0,0,0,0,0,0,5,
		5,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5
	};
	int Field_2_Monster[][3] =
	{
		6,0,0,
		BLACKGHOST,910,630,
		BLACKGHOST,490,490,
		BLACKGHOST,210,700,
		BLACKGHOST,140,210,
		BLACKGHOST,420,140,
		BLACKGHOST,840,140
	};
	int Field_3_Map[12][16] =
	{
		5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
	};
	int Field_3_Monster[][3] =
	{
		9,0,0,
		BLACKGHOST,140,140,
		BLACKGHOST,900,255,
		BLACKGHOST,420,140,
		BLACKGHOST,140,270,
		BLACKGHOST,330,360,
		BLACKGHOST,420,330,
		BLACKGHOST,565,700,
		BLACKGHOST,120,700,
		BLACKGHOST,1000,698,
	};
	int Field_4_Map[12][16] =
	{
		5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
		5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5
	};
	int Field_4_Monster[][3] =
	{
		0,0,0,
	};
	

#endif // !MAP_H
