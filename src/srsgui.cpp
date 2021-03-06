#include "srsgui/srsgui.h"
#include <stdio.h>
#include <QApplication>
#include <QMainWindow>
#include <unistd.h>

pthread_t thread;
static int sdrgui_initiated=0;

void *qt_thread(void *arg)
{
	int argc = 1;
	char* argv[] = { const_cast<char *>("libLTE Visualizer"), NULL };
  QApplication app(argc, argv);
	app.exec();
	pthread_exit(NULL);
}

int sdrgui_init()
{
  if (!sdrgui_initiated)
  {
		/** FIXME: Set attributes to detachable */
    if (pthread_create(&thread, NULL, qt_thread, NULL))
    {
			perror("phtread_create");
			return -1;
		}
		usleep(100000);
    sdrgui_initiated=1;
	}
	return 0;
}

void sdrgui_exit()
{
  if(sdrgui_initiated)
  {
    usleep(100000);
		pthread_cancel(thread);
	}
  sdrgui_initiated=0;
}
