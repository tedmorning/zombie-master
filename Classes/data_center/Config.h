#ifndef  __data_center_config_h___
#define  __data_center_config_h___
#include "tool.h"

class Config
{
public:
	void init(void);

	//保存到本地
	void save();

protected:
	void deserializeConfig();

	CC_SYNTHESIZE(float, m_soundVolume, SoundVolume);

};

#endif

