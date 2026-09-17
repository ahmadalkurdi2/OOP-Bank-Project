#include<iostream>
#include"clsCurrency.h"
#include "clsLoginScreen.h"

// When run the code enter Username and Password to show the main screen
// Username: User2
// Password: 1234

int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
            break;
    }
}