#include "Analytics.h"

int main()
{
	Analytics app;

    if (app.startup() == false)
    {
        return -1;
    }

    while (app.update() == true)
    {
        app.draw();
    }

    app.shutdown();

    return 0;
}