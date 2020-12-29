#include "main.h"
#include "translate.h"

Application app;
int global_lang = LANG_EN;


static int main_handler(int event_type, int param_one, int param_two)
{
	int result = 0;

	switch (event_type) {
	case EVT_INIT:
		//log_init();
		result = 1;
		break;
	case EVT_SHOW:

		try {
			app.init();
		}
		catch (const AbortApplication &e) {
			ERROR("Fatal Exception: %s => aborting application!", e.what());
			DialogSynchro(ICON_ERROR, PLOP_APPLICATION_FULLNAME, e.what(), "Close the application", NULL, NULL);

			app.deinit();
			result = 1;
		}
		app.show();

		result = 1;
		break;
	case EVT_FOREGROUND:
		app.foreground();
		break;
	case EVT_BACKGROUND:
		app.background();
		break;
	case EVT_KEYPRESS:
		app.keypressEvent(param_one);
		result = 1;
		break;
	case EVT_POINTERDOWN:
		app.touchStartEvent(param_one, param_two);
		result = 1;
		break;
	case EVT_POINTERUP:
		app.touchEndEvent(param_one, param_two);
		result = 1;
		break;
	case EVT_POINTERLONG:
		app.touchLong(param_one, param_two);
		result = 1;
		break;
	case EVT_EXIT:
		//log_close();

		app.deinit();

		result = 1;
		break;
	default:
		break;
	}

    return result;
}


int main (int argc, char* argv[])
{
    InkViewMain(main_handler);

    return 0;
}
