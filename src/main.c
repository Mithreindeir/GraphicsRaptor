#include "../include/grWindow.h"
#include <velocityraptor\VelocityRaptor.h>
int
main(void)
{
	grInit();
	grWindow* wind = grWindowInit(grWindowAlloc(), 640, 640);
	grMainLoop(wind);
	grDestroy(wind);
	return 1;
}
