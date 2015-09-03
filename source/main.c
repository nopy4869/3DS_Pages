#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <3ds.h>
#define KCFGP (void*)0x1FF80000
#define SMEMP (void*)0x1FF81000

char name1[] = {'/','p','a','g','e','s','/','k','c','f','g',' ','.','c','f','g',0x00};
char name2[] = {'/','p','a','g','e','s','/','s','m','e','m',' ','.','c','f','g',0x00};

int main(int argc, char** argv)
{
	int x;
	char usealt = 0;
	gfxInitDefault();
	consoleInit(GFX_BOTTOM, NULL);
	FILE *file = fopen("/pages/kcfg.bin","r");
	if (file != NULL)
	{
		usealt = 1;
		fclose(file);
		for(x='0';x<='9';x++)
		{
			name1[11] = x;
			name2[11] = x;
			file = fopen(name1,"r");
			if (file != NULL)
			{
				fclose(file);
			}
			else
			{
				break;
			}
		}
		if (file != NULL)
		{
			printf("All kcfg names are taken.\nHousekeeping suggested %%^)\n");
			gfxSwapBuffersGpu();
			for(x=0;x<180;x++)
			{
				gspWaitForEvent(GSPEVENT_VBlank0, false);
			}
			goto exit;
		}
	}
	if(usealt == 1)
		file = fopen(name1,"wb+");
	else
		file = fopen("/pages/kcfg.bin","wb+");
	
	if (file == NULL)
	{
		printf("Failed to open /pages/kcfg.bin for write.\n");
		gfxSwapBuffersGpu();
		for(x=0;x<180;x++)
		{
			gspWaitForEvent(GSPEVENT_VBlank0, false);
		}
		goto exit;
	}
	fwrite(KCFGP,0x072,1,file); 
	fclose(file);
	gfxSwapBuffersGpu();
	
	if(usealt == 1)
		printf("Wrote %s.\n", name1);
	else
		printf("Wrote /pages/kcfg.bin.\n");

	if(usealt == 1)
		file = fopen(name2,"wb+");
	else
		file = fopen("/pages/smem.bin","wb+");
	
	if (file == NULL)
	{
		printf("Failed to open /pages/smem.bin for write.\n");
		gfxSwapBuffersGpu();
		for(x=0;x<180;x++)
		{
			gspWaitForEvent(GSPEVENT_VBlank0, false);
		}
		goto exit;
	}
	fwrite(SMEMP,0x0C1,1,file); 
	fclose(file);
	gfxSwapBuffersGpu();
	if(usealt == 1)
		printf("Wrote %s.\n", name2);
	else
		printf("Wrote /pages/smem.bin.\n");
	
	
	for(x=0;x<60;x++)
	{
		gspWaitForEvent(GSPEVENT_VBlank0, false);
	}
	
	exit:
	gfxExit();
	return 0;
}
