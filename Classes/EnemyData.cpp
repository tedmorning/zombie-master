#include "EnemyData.h"
#include "tool.h"

EnemyData* EnemyData::data = NULL;

EnemyData::~EnemyData()
{
}

EnemyData*  EnemyData::createWithID(int id,bool isrepeat)
{
	EnemyData *pRet = new EnemyData();
	pRet -> sceneID = id;
	pRet -> currentLevel = id;
	pRet -> isrepeatGame = isrepeat;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool EnemyData::init()
{
	data = this;
	repeatTimes = 0;
	////////////////////\u03A9\u00A9\u00A0\u00A8\u2202\u00D8\u00AA\u2260\u00B5\u0192\u00F7\u00B0\u00A0\u02DD\u00A1\u00F8//////////////////////////////
	short framec[ZombieCount][ZombieAnimationQuantity] =
		//\u00D5\u02D8\u0153\u00AC\u221A\u00CA\u2248\u2039\u00A3\u00A8 \u00D5\u02D8\u25CA\u00DB\u201D\u201C\u2248\u2039, \u00D5\u02D8\u0153\u00AC\u03C0\u2022\u00AA\u02DC, \u00D5\u02D8\u25CA\u00DB\u201D\u201C\u03C0\u2022\u00AA\u02DC, \u00C0\u00BF\u00D5\u02C6
	{ { 4, 4, 3, 3, 8},  //1 ÆÕÍ¨½©Ê¬
	{4,4,2,2,0},
	{ 4, 5, 0, 0, 8 },
	{ 4, 4, 3, 3, 3},
	{ 4, 4, 3, 3, 0},
	{4,4,2,2,0},
	{10,10,2,2,0},           // 7 ½©Ê¬·¨Ê¦
	{4,4,3,3,0},
	{ 4, 4, 0, 0, 0 },        // 9 ±©¾ý
	{4,4,2,2,0},
	{4, 4, 3, 3, 0},     
	{3,3,6,6,0},
	{3,3,3,3,5},
	{4, 4, 4, 4, 6},      // ±©¾ý±äÉí
	{4,4,3,3,0},
	{4,3,3,3,0},
	};
	for (int i = 0; i < ZombieCount; ++i)
	{
		for (int j = 0; j < ZombieAnimationQuantity; ++j)
		{
			frameCount[i][j] = framec[i][j];
		}
	}

	/////////////////\u03A9\u00A9\u00A0\u00A8\u00B5\u0192\u2014\u2122\u00C3\u0131\u2206\u00B4\u201C\u2206\u00F7\u00B5////////////////////////////////
	CCPoint offset[ZombieCount] = 
	{
		ccp(-25, 60),
		ccp(-20, 50),
		ccp(-25, 50),
		ccp(-20, 60),  // 4
		ccp(-25, 60),
		ccp(-20, 60),
		ccp(-20, 50),
		ccp(-20, 70),
		ccp(-20, 75), // 9 ±©¾ý1
		ccp(-20, 75),
		ccp(-20, 85),
		ccp(-20, 90),
		ccp(0, 50),

		ccp(-20, 75), // 2
		ccp(-20, 75),
		ccp(-20, 75),
	};
	for (short i = 0; i < ZombieCount; ++i)
	{
		zombieHpOffset[i] = offset[i];
	}

	//\u2265\u0131\u00A0\u00BA\u00AA\u00D8\u00B1\u00E6\u03C0\u00FF\u00F8\u00AE\u00B5\u00FF\u00D5\u00BA\u00A0\u02DD\u00E6\u203A
	analyTXT();

	//\u2265\u0131\u00A0\u00BA\u00AA\u00D8\u00F7\u2019\u00B5\u201E\u0152\u00AA\u00F7\u221A
	terminalPoint[0] = ccp(10, 7);
	terminalPoint[1] = ccp(9, 7);
	terminalPoint[2] = ccp(9, 8);
	terminalPoint[3] = ccp(9, 9);
	terminalPoint[4] = ccp(9, 10);
	terminalPoint[5] = ccp(9, 11);
	terminalPoint[6] = ccp(9, 12);
	terminalPoint[7] = ccp(9, 13);
	terminalPoint[8] = ccp(10, 13);

	zombieBloodCount[0] = 90 * 1.5;
	zombieBloodCount[1] = 70 * 1.5;
	zombieBloodCount[2] = 100 * 1.5;
	zombieBloodCount[3] = 200 * 1.5;
	zombieBloodCount[4] = 150 * 1.5;
	zombieBloodCount[5] = 100 * 1.5;
	zombieBloodCount[6] = 100 * 1.5;
	zombieBloodCount[7] = 500 * 1.5;
	zombieBloodCount[8] = 1500 * 1.5;  //±©¾ý   
	zombieBloodCount[9] = 2500 * 1.5;
	zombieBloodCount[10] = 1500 * 1.5;
	zombieBloodCount[11] = 2000 * 1.5;
	zombieBloodCount[12] = 4000 * 1.5;
	zombieBloodCount[13] = 1000 * 1.5;  // ±©¾ý2
	zombieBloodCount[14] = 1500 * 1.5;
	zombieBloodCount[15] = 1500 * 1.5;

	zombieAttackCount[0] = 10;
	zombieAttackCount[1] = 8;
	zombieAttackCount[2] = 50;
	zombieAttackCount[3] = 10;
	zombieAttackCount[4] = 15;
	zombieAttackCount[5] = 0;    // 6 Ò½Éú
	zombieAttackCount[6] = 0;    // 7 ÕÙ»½
	zombieAttackCount[7] = 20;
	zombieAttackCount[8] = 80;  //±©¾ý
	zombieAttackCount[9] = 80;
	zombieAttackCount[10] = 120;
	zombieAttackCount[11] = 40;
	zombieAttackCount[12] = 100;
	zombieAttackCount[13] = 60;
	zombieAttackCount[14] = 60;
	zombieAttackCount[15] = 80;

	zombieMoveSpeed[0] = 0.5;
	zombieMoveSpeed[1] = 0.8;
	zombieMoveSpeed[2] = 0.6;
	zombieMoveSpeed[3] = 0.5;
	zombieMoveSpeed[4] = 0.6;
	zombieMoveSpeed[5] = 0.4;
	zombieMoveSpeed[6] = 0.5;
	zombieMoveSpeed[7] = 0.5;
	zombieMoveSpeed[8] = 0.6;  //±©¾ý
	zombieMoveSpeed[9] = 0.6;
	zombieMoveSpeed[10] = 0.6;
	zombieMoveSpeed[11] = 0.6;
	zombieMoveSpeed[12] = 0.7;
	zombieMoveSpeed[13] = 0.6;
	zombieMoveSpeed[14] = 0.6;
	zombieMoveSpeed[15] = 0.6;

	sumZombieCount[0] = 0.0;
	sumZombieCount[1] = 0.0;
	sumZombieCount[2] = 0.25;
	sumZombieCount[3] = 0.15;
	sumZombieCount[4] = 0.2;
	sumZombieCount[5] = 0.4;
	sumZombieCount[6] = 0.25;
	sumZombieCount[7] = 0.25;
	sumZombieCount[8] = 0.5;
	sumZombieCount[9] = 0.3;
	sumZombieCount[10] = 0.35;
	sumZombieCount[11] = 0.6;
	sumZombieCount[12] = 0.0;

	for (int i = 0; i < ZombieCount;i++)
	{
		zombieAttackDuration[i] = 1.0;
		zombieWorthGold[i] = i*5 + 5;
	}


	countAllRoute();
	return true;
}

void EnemyData::analyTXT()
{//\u2202\u00A1\u00BB\u00B0\u03C0\u00FF\u00F8\u00AE\u00AC\u2211\u0153\uFB02\u201D\u00CE\u00B5\u00FF\u00D5\u00BA\u00A0\u02DD\u00E6\u203A

	if (sceneID <= 4 && sceneID > 0) 
	{
		sceneID = 0;
	}
	else if (sceneID > 4 && sceneID <= 8)
	{
		sceneID = 1;
	}
	else if (sceneID > 8 && sceneID <= 12)
	{
		sceneID = 2;
	}
	TString mapname;
	mapname += "map";
	mapname += sceneID;
	mapname += ".txt";
	string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(mapname.data());

	unsigned char* pBuffer = NULL;
	unsigned long bufferSize = 0;

	pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &bufferSize);

	unsigned long index = 14;
	string str;
	routeQuantity = stringChangeInt(str += pBuffer[index]);
	index += 2;

	///////////////\u00AA\u00D2\u00BB\u00B0\u00AC\u2211\u0153\uFB02\u00B5\u0192\u2265\u0131\u00A0\u00BA\u0152\u00AA\u00F7\u221A\u00A0\u02DD\u00E6\u203A////////////////////////////////
	index += 11;
	str = "";
	CCLOG("%d", pBuffer[index]);
	short routeStartIndex = -1;
	short routeStartSpace = 0; //\u00F8\u00FF\u00F7\u2206\u2206\u00B4\u201C\u2206
	CCPoint point;
	while (pBuffer[index] != '\n')
	{
		if (pBuffer[index] == '{')
		{
			routeStartIndex++;
			index++;
			continue;
		}
		if (pBuffer[index] == '}')
		{
			point.y = stringChangeInt(str);
			routeStartPoint.push_back(ccp(point.x, point.y));
			index++;
			if (pBuffer[index] == '\n')
				break;
			index ++;
			str = "";
			continue;
		}
		if (pBuffer[index] == ',')
		{
			//point = new CCPoint();
			point.x = stringChangeInt(str);
			str = "";
		}
		else if (pBuffer[index] != ' ' && pBuffer[index] != '=')
		{
			str += pBuffer[index];
		}
		index++;
	}

	CCLOG("%d", routeStartPoint.size());

	//////////////////\u00AA\u00D2\u00B5\u221A\u00B5\u00FF\u00D5\u00BA\u00A0\u02DD\u25CA\u00C8\u00A0\u02DD\u00E6\u203A//////////////////////////////
	str = "";
	index++;
	short colIndex = 0; //\u2013\u2013\u0153\u00AC\u00B1\u00CD
	short rowIndex = 0; //\u00A1\u2013\u0153\u00AC\u00B1\u00CD
	while (pBuffer[index] != 'e')
	{
		if (pBuffer[index] == '\n')
		{
			colIndex++;
			rowIndex = 0;
			index++;
			continue;
		}
		if (pBuffer[index] == '{' || pBuffer[index] == ' ')
		{
			index++;
			continue;
		}
		if (pBuffer[index] == ',' || pBuffer[index] == '}')
		{
			mapData[colIndex][rowIndex] = stringChangeInt(str);
			CCLOG("%d, \u884C=%d, \u5217=%d", mapData[colIndex][rowIndex], colIndex, rowIndex);
			str = "";
			rowIndex++;
		}
		else if(pBuffer[index] != '\r')
		{
			str += pBuffer[index];
		}
		index++;
	}
	//    for (short i=0; i<mapCol; ++i) {
	//        for (short j=0; j<mapRow; ++i) {
	//            CCLOG("%d", mapData[i][j]);
	//        }
	//        CCLOG("---------------");
	//    }
}

void EnemyData::countAllRoute()
{
	allRoute = new RoutePoint[routeQuantity][TerminaQuantity];
}

RoutePoint *EnemyData::getRoute(short routeId)
{
	short id = getRandom(0, TerminaQuantity);
	//\u00BB\u00C1\u03C0\u02DA\u00AC\u2211\u00E6\u2202\u00BF\u00D4\u221A\u00CA\u00B5\u0192\u00B5\u2044\u201C\u00AA\u220F\u02C6\u0152\u00AA\u00F7\u221A\u0152\u2122-1\u0192\u00AB\u221A\u00A5\u2019\u201A\u00C3\u0131\u00AC\u2211\u00E6\u2202\u00AA\u03C0\u221A\u00AA\u201D\u2013\u00BA\u2206\u00C0\u201E\u2265\u02C6\u00BF\u00A5
	if (allRoute[routeId][id].pathData.size() == 0)
	{
		countRoute(routeId, &allRoute[routeId][id].pathData);
	}

	return &allRoute[routeId][id];
}

void EnemyData::countRoute(short routeIndex, vector<CCPoint> *pathData)
{
	CCPoint tpoint = EnemyData::data->getTerminalPoint();
	CCPoint endPoint;
	endPoint.x = tpoint.x;
	endPoint.y = tpoint.y;
	list<PathNode*> openList;
	list<PathNode*> closeList;

	//0.\u00F8\u2019\u00B5\u0192  1.\u2018\u2044close\u00BF\u00D4\u221A\u00CA  2.\u2018\u2044open\u00BF\u00D4\u221A\u00CA
	short closeData[mapCol][mapRow];
	for (short i = 0; i < mapCol; ++i)
	{
		for (short j = 0; j < mapRow; ++j)
		{
			closeData[i][j] = 0;
		}
	}

	PathNode *panode = NULL;

	panode = new PathNode(routeStartPoint[routeIndex].x, routeStartPoint[routeIndex].y);
	panode->set(0, fabs(panode->col - endPoint.x) + fabs(panode->row - endPoint.y));
	panode->setFather(NULL);
	openList.push_back(panode);
	short col = 0;
	short row = 0;
	//\u2248\u2013\u2202\u0153\u00A0\u00AB\u2211\u00D2\u2019\u201C\u00B5\u03A9\u00AC\u2211\u00E6\u2202\u00A1\u00C0
	bool is = false;
	//\u25CA\u00D3\u00F7\u2019\u00B5\u201E
	PathNode *end = NULL;
	while (!openList.empty())
	{
		PathNode *node = openList.front();
		openList.pop_front();
		closeList.push_back(node);
		closeData[node->col][node->row] = 1;
		col = node->col;
		row = node->row;

		PathNode *node1;
		if (row - 1 >= 0) //\u25CA\u00DB\u00B1\uFB02
		{
			if (EnemyData::data->mapData[col][row - 1] != 1
				&& closeData[col][row - 1] != 1)
			{
				if (closeData[col][row - 1] != 2) //\u2248\u2013\u2202\u0153\u00A0\u00AB\u2211\u00D2\u2018\u2044Open\u00BF\u00D4\u221A\u00CA
				{
					node1 = new PathNode(col, row - 1);
					node1->set(node->G + 1, fabs(node1->col - endPoint.x) + fabs(node1->row - endPoint.y)); //\u2026\u00CB\u00F7\u221AFGH
					node1->setFather(node); //\u2026\u00CB\u00F7\u221A\u220F\u220F\u03A9\u2044\u00B5\u201E\u0152\u00AA\u00F7\u221A
					openList.push_back(node1);
					closeData[col][row - 1] = 2;
					if (node1->col == endPoint.x && node1->row == endPoint.y)
					{
						is = true;
						end = node1;
						break;
					}
				}
			}
		}
		if (row + 1 < mapRow) //\u25CA\u00DB\u00B1\uFB02
		{
			if (EnemyData::data->mapData[col][row + 1] != 1
				&& closeData[col][row + 1] != 1)
			{
				if (closeData[col][row + 1] != 2) //\u2248\u2013\u2202\u0153\u00A0\u00AB\u2211\u00D2\u2018\u2044Open\u00BF\u00D4\u221A\u00CA
				{
					node1 = new PathNode(col, row + 1);
					node1->set(node->G + 1, fabs(node1->col - endPoint.x) + fabs(node1->row - endPoint.y)); //\u2026\u00CB\u00F7\u221AFGH
					node1->setFather(node); //\u2026\u00CB\u00F7\u221A\u220F\u220F\u03A9\u2044\u00B5\u201E\u0152\u00AA\u00F7\u221A
					openList.push_back(node1);
					closeData[col][row + 1] = 2;
					if (node1->col == endPoint.x && node1->row == endPoint.y)
					{
						is = true;
						end = node1;
						break;
					}
				}
			}
		}
		if (col - 1 >= 0) //\u2026\u0153\u00B1\uFB02
		{
			if (EnemyData::data->mapData[col - 1][row] != 1
				&& closeData[col - 1][row] != 1)
			{
				if (closeData[col - 1][row] != 2)
				{
					node1 = new PathNode(col - 1, row);
					node1->set(node->G + 1, fabs(node1->col - endPoint.x) + fabs(node1->row - endPoint.y)); //\u2026\u00CB\u00F7\u221AFGH
					node1->setFather(node); //\u2026\u00CB\u00F7\u221A\u220F\u220F\u03A9\u2044\u00B5\u201E\u0152\u00AA\u00F7\u221A
					openList.push_back(node1);
					closeData[col - 1][row] = 2;
					if (node1->col == endPoint.x && node1->row == endPoint.y)
					{
						is = true;
						end = node1;
						break;
					}
				}
			}
		}
		if (col + 1 < mapCol) //\u0153\u00AC\u00B1\uFB02
		{
			if (EnemyData::data->mapData[col + 1][row] != 1
				&& closeData[col + 1][row] != 1)
			{
				if (closeData[col + 1][row] != 2)
				{
					node1 = new PathNode(col + 1, row);
					node1->set(node->G + 1, fabs(node1->col - endPoint.x) + fabs(node1->row - endPoint.y)); //\u2026\u00CB\u00F7\u221AFGH
					node1->setFather(node); //\u2026\u00CB\u00F7\u221A\u220F\u220F\u03A9\u2044\u00B5\u201E\u0152\u00AA\u00F7\u221A
					openList.push_back(node1);
					closeData[col + 1][row] = 2;
					if (node1->col == endPoint.x && node1->row == endPoint.y)
					{
						is = true;
						end = node1;
						break;
					}
				}
			}
		}

		openList.sort(Cmpare());
	}
	pathData->push_back(ccp(end->col, end->row));
	while (true)
	{
		if (end->father == NULL)
		{
			break;
		}
		pathData->push_back(ccp(end->father->col, end->father->row));
		end = end->father;
	}

	while (!openList.empty())
	{
		PathNode * pa = openList.front();
		delete pa;
		openList.pop_front();
	}
	while (!closeList.empty())
	{
		PathNode *pa = closeList.front();
		delete pa;
		closeList.pop_front();
	}
}

CCPoint EnemyData::getTerminalPoint()
{
	return terminalPoint[getRandom(0, 9)];
}

bool EnemyData::isZombieRemote(ZombieType type)
{
	switch (type)
	{
	case ZombieOrdinary:
		break;


	}
	return false;
}

PathNode::PathNode(short col, short row)
{
	this->col = col;
	this->row = row;
}

PathNode::~PathNode()
{

}

void PathNode::set(short g, short h)
{
	G = g;
	H = h;
	F = G + H;
}

void PathNode::setFather(PathNode *fath)
{
	father = fath;
}

void PathNode::setPos(short co, short ro)
{
	col = co;
	row = ro;
}

bool Cmpare::operator()(const PathNode *st1, const PathNode *st2) const
{
	return st1->F < st2->F;
}