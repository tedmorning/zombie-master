#ifndef  __data_center_config_h___
#define  __data_center_config_h___
#include "tool.h"

class Config
{
public:
	void init(void);

	//���浽����
	void save();

protected:
	void deserializeConfig();

	CC_SYNTHESIZE(float, m_soundVolume, SoundVolume);

};

#endif

