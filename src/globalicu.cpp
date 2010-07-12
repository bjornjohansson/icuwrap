
#include <unicode/uclean.h>

class GlobalIcu
{
public:
	GlobalIcu()
		{}
	~GlobalIcu()
		{
			u_cleanup();
		}
	
private:
} globalIcu;
