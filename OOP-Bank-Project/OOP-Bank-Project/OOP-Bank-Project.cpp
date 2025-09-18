#include<iostream>
#include"clsCurrency.h"
#include "clsLoginScreen.h"

int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
            break;
    }
}