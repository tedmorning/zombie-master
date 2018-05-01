 #include "EnemyManage.h"
#include "tool.h"
#include "TString.h"
#include "Bullet.h"
#include "data_center\RunningData.h"
#include "GiftLayer.h"
EnemyManage *EnemyManage::oneself = NULL;

EnemyManage::EnemyManage():
buildZombieTimeAxis(0),
quantity(0),
waveIndex(0),
waveQuantity1(1),
waveQuantity2(1),
waveQuantity3(1),
waveRouteIndex1(0),
waveRouteIndex2(0),
waveRouteIndex3(0),
waveFinish1(false),
waveFinish2(false),
waveFinish3(false),
buildZombieFinished(false),
isrepeatGame(false),
istest(false)
{
	oneself = this;
}

EnemyManage::~EnemyManage()
{

}

EnemyManage* EnemyManage::create(BattleManage *bat,int level,bool isrepeat)
{
	EnemyManage *em = new EnemyManage();
	em -> currentLevel = level;
	em -> isrepeatGame = isrepeat;
	if (em->init(bat))
	{
		em->autorelease();
		return em;
	}
	CC_SAFE_DELETE(em);
	return NULL;
}

bool EnemyManage::init(BattleManage *bat)
{
	battle = bat;
	//istest = true;  // ���Թؿ�����  1~13�Ľ�ʬ
	zombieZorder = 10000;
	repeatTimes = 0;
	repeatCountTime = 0.0f;

	initStageData();

	schedule(schedule_selector(EnemyManage::updateZombieZorder),1.0f);

	return true;
}

void EnemyManage::initStageData()
{
	if (!isrepeatGame)
	{
		if (!istest)
		{
			TString stagename;
			stagename += "stage";
			stagename += currentLevel;
			stagename += ".txt";
			string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(stagename.data());

			unsigned char* pBuffer = NULL;
			unsigned long bufferSize = 0;

			pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &bufferSize);

			analyTXT(pBuffer, bufferSize);
		}
		else
		{
			string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("stage0.txt");

			unsigned char* pBuffer = NULL;
			unsigned long bufferSize = 0;

			pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &bufferSize);

			analyTXT(pBuffer, bufferSize);
		}
	}
	else
	{
		TString str;
		str += "stagerepeat";
		if (repeatTimes > 4 || repeatTimes < 0)
		{
			repeatTimes = 0;
		}
		str += repeatTimes;
		str += ".txt";
		string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(str.data());
		//string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("stage2.txt");

		repeatTimes ++;

		unsigned char* pBuffer = NULL;
		unsigned long bufferSize = 0;

		pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &bufferSize);

		analyTXT(pBuffer, bufferSize);
	}
}

void EnemyManage::analyTXT(unsigned char *buffer, unsigned long size)
{
	unsigned long index = 3;
	string str;
	while (buffer[index] != '\n')
	{
		str += buffer[index];
		index++;
		if (buffer[index] == '\n')
		{
			break;
		}
		
	}
	CCLOG("wave init:%s",str.c_str());
	//��ò���
	if (!isrepeatGame)
	{
		if(currentLevel == 1)
			wave = 12;
		else if (currentLevel >= 2 && currentLevel <= 4)
		{
			if (currentLevel == 3)
				wave = 8;
			else
				wave = 7;
		}
		else
		{
			if (currentLevel == 6 || currentLevel == 9 || currentLevel == 12)
			{
				wave = 7;
			}
			else
				wave = 6;
		}
	}
	else
		wave = 6;
	if (istest)
	{
		wave = 13;
	}
	
	CCLOG("wave init:%d",wave);
	//Ϊ����ʱ����������С
	waveTime = new short[wave];
	//�������潩ʬ����
	waveZombieType = new short[wave][WaveZombieType];
	//ÿ����ʬ��������
	waveZombieQuantity = new short[wave][WaveZombieType];
	//ÿ����ʬ·��
	routeData = new short[wave][WaveZombieType][WaveRoute];
	//��ȡ����ʱ��
	readStageTime(buffer, &index);
	//��ȡÿ�����Ľ�ʬ����
	readStageType(buffer, &index);
	//��ȡÿ�����Ľ�ʬ����
	readStageQuantity(buffer, &index);
	//��ȡÿ�����Ľ�ʬ·��
	readStageRoute(buffer, &index);
}

void EnemyManage::readStageTime(unsigned char *buffer, unsigned long *index)
{
	//�Ƿ��ȡ����
	bool readNumber = false;
	string str;
	//��ʱ��������±�
	short waveIndex = 0;
	while (buffer[*index] != 'n')
	{
        //CCLOG("%d", *index);
		if (readNumber)
		{//��ȡʱ��
			if (buffer[*index] == ',' || buffer[*index] == '}')
			{
				waveTime[waveIndex] = stringChangeInt(str);
				waveIndex++;
				str = "";
			}
			else if (buffer[*index] != ' ')
			{
				str += buffer[*index];
			}
		}
		else if (buffer[*index] == '{')
		{
			readNumber = true;
		}
		if (buffer[*index] == '}')
		{
			(*index)++;
			break;
		}
		(*index)++;
	}
    for (short i=0; i<wave; ++i) {
        CCLOG("%d", waveTime[i]);
    }
}

void EnemyManage::readStageType(unsigned char *buffer, unsigned long *index)
{
	//�Ƿ��ȡ����
	bool readNumber = false;
	string str;
	//����ʬ����������±�
	short waveIndex = 0;

	short waveIndex2 = 0;

	while (buffer[*index] != 'n')
	{
		if (readNumber)
		{
			if (buffer[*index] == '{')
			{
				while (true)
				{
					if (buffer[*index] == ',' || buffer[*index] == '}')
					{
						waveZombieType[waveIndex][waveIndex2] = stringChangeInt(str);
						short aa = waveZombieType[waveIndex][waveIndex2];
						waveIndex2++;
                        if(waveIndex2 < 3) {
                            waveZombieType[waveIndex][waveIndex2] = -2;
                        }
						
						str = "";
					}
					else if (buffer[*index] != ' ' && buffer[*index] != '{')
					{
						str += buffer[*index];
					}
					if (buffer[*index] == '}')
					{
						(*index)++;
						waveIndex++;
						waveIndex2 = 0;
						break;
					}
					(*index)++;
				}
			}
			else if (buffer[*index] == ',' || buffer[*index] == '}')
			{
				waveZombieType[waveIndex][waveIndex2] = stringChangeInt(str);
				waveZombieType[waveIndex][waveIndex2 + 1] = -2;
				waveIndex++;
				str = "";
			}
			else if (buffer[*index] != ' ')
			{
				str += buffer[*index];
			}
		}
		else if (buffer[*index] == '{')
		{
			readNumber = true;
		}

		if (buffer[*index] == '}')
		{
			(*index)++;
			break;
		}
		(*index)++;
	}

	for (short i = 0; i < wave; ++i)
	{
		for (short j = 0; j < WaveZombieType; ++j)
		{
			CCLOG("%d,", waveZombieType[i][j]);
		}
	}
}

void EnemyManage::readStageQuantity(unsigned char *buffer, unsigned long *index)
{
	//�Ƿ��ȡ����
	bool readNumber = false;
	string str;
	//����ʬ����������±�
	short waveIndex = 0;

	short waveIndex2 = 0;

	while (true)
	{
		if (readNumber)
		{
			if (buffer[*index] == '{')
			{
				while (true)
				{
					if (buffer[*index] == ',' || buffer[*index] == '}')
					{
						waveZombieQuantity[waveIndex][waveIndex2] = stringChangeInt(str);
						waveIndex2++;
                        if (waveIndex2 < 3) {
                            waveZombieQuantity[waveIndex][waveIndex2] = -2;
                        }
						str = "";
					}
					else if (buffer[*index] != ' ' && buffer[*index] != '{')
					{
						str += buffer[*index];
					}
					if (buffer[*index] == '}')
					{
						(*index)++;
						waveIndex++;
						waveIndex2 = 0;
						break;
					}
					(*index)++;
				}
			}
			else if (buffer[*index] == ',' || buffer[*index] == '}')
			{
				waveZombieQuantity[waveIndex][waveIndex2] = stringChangeInt(str);
				waveZombieQuantity[waveIndex][waveIndex2 + 1] = -2;
				waveIndex++;
				str = "";
			}
			else if (buffer[*index] != ' ')
			{
				str += buffer[*index];
			}
		}
		else if (buffer[*index] == '{')
		{
			readNumber = true;
		}

		if (buffer[*index] == '}')
		{
			(*index)++;
			break;
		}
		(*index)++;
	}

	for (short i = 0; i < wave; ++i)
	{
		for (short j = 0; j < WaveZombieType; ++j)
		{
			CCLOG("%d,", waveZombieQuantity[i][j]);
		}
	}
}

void EnemyManage::readStageRoute(unsigned char *buffer, unsigned long *index)
{
	//�Ƿ��ȡ����
	bool readNumber = false;
	string str;
	//����ʬ����������±�
	short waveIndex = 0;

	short waveIndex2 = 0;

	short waveIndex3 = 0;
    
    
    TString strs;

	while (buffer[(*index) + 1] != 'n')
	{
        strs = "";
        strs += (char)buffer[*index];
		if (readNumber)
		{
			if (buffer[*index] == '}')
			{
				routeData[waveIndex][waveIndex2][waveIndex3] = stringChangeInt(str);
				waveIndex3++;
				str = "";
				(*index)++;
				if (buffer[*index] == '\n' || buffer[*index] == '\r')
				{
					if (waveIndex3 < WaveRoute - 1)
					{
						routeData[waveIndex][waveIndex2][waveIndex3] = -2;
					}
					waveIndex++;
					waveIndex2 = 0;
					waveIndex3 = 0;
					if (waveIndex >= wave)
					{
						break;
					}
				}
				else if (buffer[*index] == ',')
				{
					if (waveIndex3 < WaveRoute - 1)
					{
						routeData[waveIndex][waveIndex2][waveIndex3] = -2;
					}
					waveIndex2++;
					waveIndex3 = 0;
				}
			}
			else if (buffer[*index] == ',')
			{
				routeData[waveIndex][waveIndex2][waveIndex3] = stringChangeInt(str);
				waveIndex3++;
				str = "";
			}
			else if (buffer[*index] != '{' && buffer[*index] != ',' && buffer[*index] != ' ' && buffer[*index] != '\n')
			{
				str += buffer[*index];
			}
		}
		else if (buffer[*index] == '{')
		{
			readNumber = true;
		}
		(*index)++;
	}

	for (short i = 0; i < wave; ++i)
	{
		for (short j = 0; j < 3; ++j)
		{
			for (short k = 0; k < 7; ++k)
			{
				CCLog("%d", routeData[i][j][k]);
			}
		}
		CCLog("---------------");
	}
}

void EnemyManage::updata(float dt)
{
	buildZombie(dt);

	for (unsigned int i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i]->life)
		{
			enemyList[i]->updata(dt);
		}
		else
		{
			removeChild(enemyList[i]);
			vector<Enemy*>::iterator it = enemyList.begin() + i;
			enemyList.erase(it);
		}
	}
}

void EnemyManage::updateZombieZorder(float dt)
{
	for (unsigned int i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i]->life)
		{
			//���ݵ�ǰ��Y���꣨ͼƬ���·���λ�ã�����zorder 
			enemyList[i] -> setZOrder(10000 + enemyList[i] -> getContentSize().height/2 + ( 480 - enemyList[i] -> getPositionY()));
		}
	}
}

void EnemyManage::buildZombie(float dt)
{
	if (waveIndex == wave)
	{
		if (!isrepeatGame)
		{
			buildZombieFinished = true;
		}
		else
		{
			if (getEnemySize() < 1)
			{
				EnemyData::data -> repeatTimes += 1;
				reLoadData();
				initStageData();
			}
		}
        
		return;
	}

	if (repeatCountTime > waveTime[waveIndex])// ������ʬ  �ֶ�����  ���ݶ���û���⣡ ���ǽ�ʬ��������������
	{
		repeatCountTime = 0.0f;
		waveFinish1 = true;
		waveFinish2 = true;
		waveFinish3 = true;
	}

	repeatCountTime += dt;
	buildZombieTimeAxis += dt;

	//�����ļ��
	float timeInterval = (float)waveTime[waveIndex] / waveZombieQuantity[waveIndex][0];
	if (!waveFinish1 && buildZombieTimeAxis >= timeInterval * waveQuantity1)
	{
		buildZombie(0, &waveQuantity1, &waveRouteIndex1, &waveFinish1);
		if (waveZombieQuantity[waveIndex][1] <= 0)
		{
			waveFinish2 = true;
			waveFinish3 = true;
		}
	}
	
	if (waveZombieQuantity[waveIndex][1] > 0)
	{
		timeInterval = (float)waveTime[waveIndex] / waveZombieQuantity[waveIndex][1];
		if (!waveFinish2&& buildZombieTimeAxis >= timeInterval * waveQuantity2)
		{//�ڶ��ֽ�ʬ
			buildZombie(1, &waveQuantity2, &waveRouteIndex2, &waveFinish2);
			if (waveZombieQuantity[waveIndex][2] <= 0)
			{
				waveFinish3 = true;
			}

			if (waveZombieQuantity[waveIndex][2] > 0)
			{
				timeInterval = (float)waveTime[waveIndex] / waveZombieQuantity[waveIndex][2];
				if (!waveFinish3&& buildZombieTimeAxis >= timeInterval * waveQuantity3)
				{//�����ֽ�ʬ
					buildZombie(2, &waveQuantity3, &waveRouteIndex3, &waveFinish3);
				}
			}
		}
	}
	if (waveFinish1 && waveFinish2 && waveFinish3)
	{
		waveIndex++;

	

// 		if (waveIndex == 2)
// 		{	
// 			//�������������
// 			RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
// 			Role& role = rs.m_roleInfos[k_ironmen];
// 			if (!role.available)
// 			{
// 				GiftLayer * giftLayer = GiftLayer::create(k_pay_supergift);
// 				CCDirector::sharedDirector()->pushScene(GiftLayer::scene(giftLayer));
// 			}
// 
// 		}
// 		else if (waveIndex == 3)
// 		{
// 			//�������
// 			RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
// 			Role& role = rs.m_roleInfos[k_blackwidow];
// 			if (!role.available)
// 			{
// 				GiftLayer * giftLayer = GiftLayer::create(k_pay_newgift);
// 				CCDirector::sharedDirector()->pushScene(GiftLayer::scene(giftLayer));
// 			}
// 		}

		if (!isrepeatGame)  // ����Ͻ���������  ���ڶ�ȡtxt�ļ�ʱ�����⣡��
		{
			float progress = (float)waveIndex;
			float totalProgress = (float)wave;
			CCLOG("progress:%f",progress);
			CCLOG("total:%f",totalProgress);
			BattleManage::oneself -> setProgressBar((progress/totalProgress) * 100);
			BattleManage::oneself -> addTipsWords(waveIndex);
		}

		repeatCountTime = 0.0f;
		waveFinish1 = false;
		waveFinish2 = false;
		waveFinish3 = false;
		waveQuantity1 = 1;
		waveQuantity2 = 1;
		waveQuantity3 = 1;
		waveRouteIndex1 = 0;
		waveRouteIndex2 = 0;
		waveRouteIndex3 = 0;
		buildZombieTimeAxis = 0;
	}
}

void EnemyManage::buildZombie(short waveType, short *waveQuantity, short *waveRouteIndex, bool *waveFinish)
{
	//��ȡ�����ʬ��·��
	short route = getStatuZombieRoute(waveType, waveRouteIndex);
	//��ȡ�����ʬ������
	short type = waveZombieType[waveIndex][waveType];
	Enemy * enemy = NULL;
	enemy = Enemy::create(battle);
	enemy->buildZombie(type - 1, route - 1);

	if (currentLevel == 1)
	{
		enemy->setHP(0.8);
	}
	//addChild(enemy, 0); // �ᵼ�º���ĵ�סǰ���
	addChild(enemy,zombieZorder--);
	enemyList.push_back(enemy);

	(*waveQuantity)++;
	//���ˢ����ʬ�ĸ�����������������ô����
	if ((*waveQuantity) >= waveZombieQuantity[waveIndex][waveType])
	{
		*waveFinish = true;
	}
}

short EnemyManage::getStatuZombieRoute(short waveType, short *waveRouteID)
{
	short temp = routeData[waveIndex][waveType][*waveRouteID];
	if (temp == -2)
	{
		*waveRouteID = 0;
		temp = routeData[waveIndex][waveType][*waveRouteID];
	}
	
	if (temp == -1)
	{//���
		temp = getRandom(1, EnemyData::data->routeQuantity);
	}

	(*waveRouteID)++;
	return temp;
}

bool EnemyManage::bulletAndEnemyCollision(CCRect rect, Bullet *bullet)
{
	for (unsigned int i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i]->checkCollision(rect, bullet) && !enemyList[i] -> isBulletThrough)
		{
			return true;
		}
	}
	return false;
}

void EnemyManage::reduceEnemyHPAngleAndDis(float angle,float dis,float hurt)
{
	for (unsigned int i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i] != NULL)
		{
			float bulletAngle = angle/PI * 180;
			float twoPointAngle = twoPoint(ccp(400, 50), enemyList[i] -> getPosition())/PI * 180;
			bool inangle =  (twoPointAngle > bulletAngle - 10) && (twoPointAngle < bulletAngle + 10);
			bool inangle1 = (twoPointAngle > bulletAngle - 30) && (twoPointAngle < bulletAngle + 30);
			if ((ccpDistance(enemyList[i] -> getPosition(),ccp(400, 50)) <= (dis + 30) && inangle) || (ccpDistance(enemyList[i] -> getPosition(),ccp(400, 50)) <= 60 && inangle1))
			{
				enemyList[i] -> reduceHp(hurt);
				enemyList[i] -> updataHpSprite();
			}
		}
	}
}

void EnemyManage::reduceEnemyHpInRect(float angle,float dis,float hurt)
{
	for (unsigned int i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i] != NULL)
		{
			float bulletAngle = angle/PI * 180;
			float twoPointAngle = twoPoint(ccp(400, 50), enemyList[i] -> getPosition())/PI * 180;
			bool inangle =  (twoPointAngle > bulletAngle - 10) && (twoPointAngle < bulletAngle + 10);
			bool inangle1 = (twoPointAngle > bulletAngle - 30) && (twoPointAngle < bulletAngle + 30);
			if ((ccpDistance(enemyList[i] -> getPosition(),ccp(400, 50)) <= (dis + 30) && inangle) || (ccpDistance(enemyList[i] -> getPosition(),ccp(400, 50)) <= 60 && inangle1))
			{
				enemyList[i] -> reduceHp(hurt);
				enemyList[i] -> updataHpSprite();
			}
		}
	}
}

void EnemyManage::reduceEnemyHpInDistance(CCPoint pos,int distance,float hurt)
{
	for (unsigned int i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i] != NULL)
		{
			if (ccpDistance(enemyList[i] -> getPosition(),pos) <= distance)
			{
				enemyList[i] -> reduceHp(hurt);
				enemyList[i] -> updataHpSprite();
			}
		}
	}
}

void EnemyManage::cureZombieInDistance(CCPoint pos,int dis,int cureCount)
{
	for (unsigned int i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i] != NULL)
		{
			if (ccpDistance(enemyList[i] -> getPosition(),pos) <= 100)
			{
				enemyList[i] -> reduceHp(-cureCount);
				enemyList[i] -> updataHpSprite();
			}
		}
	}
}

void EnemyManage::showCallAnimation(Enemy* zombie)
{
	buildCalledZombie(zombie);
	CCArray *animaArray = CCArray::createWithCapacity(9);
	for (int j = 1; j <= 9; j++)
	{
		TString str;
		str += "callanimation";
		str += j;
		str += ".png";
		CCSpriteFrame *frame = 
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
		animaArray->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.1f);
	CCAnimate* animate = CCAnimate::create(animation);
	CCSprite* call = CCSprite::createWithSpriteFrameName("callanimation1.png");
	call -> setPosition(zombie -> getNextPoint());
	addChild(call,zombie ->getZOrder() + 1);
	call -> runAction(CCSequence::create(animate,CCCallFuncO::create(this,callfuncO_selector(EnemyManage::removeCallAnimation),call),NULL));
}

void EnemyManage::removeCallAnimation(CCObject* pSender)
{
	CCSprite* temp = (CCSprite*)pSender;
	if (temp)
	{
		temp -> removeFromParent();
	}
}

void EnemyManage::buildCalledZombie(Enemy* zombie)
{
	Enemy * enemy = Enemy::create(battle);
	enemy->buildZombie(ZombieOrdinary, zombie -> getRouteIndex());
	enemy -> setNextPoint(zombie -> getNextPoint());
	enemy -> setRouteData(zombie -> getRouteData());
	enemy -> setPathIndex(zombie -> getPathIndex());
	enemy -> setMoveState(zombie -> getMoveState());
	enemy -> setPosition(zombie -> getPosition());
	enemy -> buildHpImage(true);
	addChild(enemy, zombie -> getZOrder() + 1); 
	enemyList.push_back(enemy);
}

void EnemyManage::reLoadData()
{
	buildZombieTimeAxis = 0;
	quantity = 0;
	waveIndex = 0;
	waveQuantity1 = 1;
	waveQuantity2 = 1;
	waveQuantity3 = 1;
	waveRouteIndex1 = 0;
	waveRouteIndex2 = 0;
	waveRouteIndex3 = 0;
	waveFinish1 = false;
	waveFinish2 = false;
	waveFinish3 = false;
	buildZombieFinished = false;
}