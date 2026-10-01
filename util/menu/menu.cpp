/********************************************************************************************
*  _  ___   ____  __    _____         _ _  ___ _   
* | \| \ \ / /  \/  |__|_   _|__  ___| | |/ (_) |_ 
* | .` |\ V /| |\/| / -_)| |/ _ \/ _ \ | ' <| |  _|
* |_|\_| \_/ |_|  |_\___||_|\___/\___/_|_|\_\_|\__|
*                                                              
* MIT License
* 
* Copyright (c) 2026 Eric L. Yang
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* 
* https://github.com/elyyang
* elyyang@gmail.com
*
*********************************************************************************************/

#include "menu.h"
#include "assertLib.h"
#include <stdio.h>

menu_c::menu_c()
{
    mRun = true;
    mCurrentMenuIndex = 0;
    mCurrentSubMenuIndex = 0;
    mCurrentState = MAIN_MENU_STATE;
}

menu_c::~menu_c()
{
}

void menu_c::build(mainMenu project)
{
    mProject = project;
}

void menu_c::displayMenuTree()
{
    CONSOLE_PRINT("\n\n")
    displayBorder();
    CONSOLE_PRINT("[%s Menu Tree] \n", mProject.getDescription());
    displayInnerBorder();
    for (uint32_t i=0; i<mProject.getItemCount(); i++)
    {
        CONSOLE_PRINT("(%d)-%-40s \n", (i+1), mProject.getItemDescription(i));

        for (uint32_t j=0; j<mProject.getItem(i).getItemCount(); j++)
        {
            CONSOLE_PRINT("|____(%d)-%-40s \n", (j+1), mProject.getItem(i).getItemDescription(j));
        }
    }
    displayBorder();    
    displayPrompt();    
}

void menu_c::displayMainMenuItems()
{
    CONSOLE_PRINT("\n\n")
    displayBorder();
    CONSOLE_PRINT("[Main Menu] (%s) \n", mProject.getDescription());        
    displayInnerBorder();
    mProject.displayItems();
    displayBorder();    
    displayPrompt();
}

void menu_c::displayCurrentSubMenuItems()
{
    CONSOLE_PRINT("\n\n")
    displayBorder();
    CONSOLE_PRINT("[Sub Menu] (%s) \n", mProject.getItem(mCurrentMenuIndex).getDescription());        
    displayInnerBorder();
    mProject.getItem(mCurrentMenuIndex).displayItems();
    displayBorder();
    
    displayPrompt();
}

void menu_c::displayPrompt()
{
    CONSOLE_PRINT("(q)uit, (m)ain menu, (t)ree | selection: ");
}

void menu_c::displayBorder()
{
    CONSOLE_PRINT("==================================================\n");
}

void menu_c::displayInnerBorder()
{
    CONSOLE_PRINT("--------------------------------------------------\n");
}

void menu_c::clearOutput()
{
    CONSOLE_PRINT("\e[1;1H\e[2J");
}

void menu_c::execute()
{
    clearOutput();

    displayBorder();
    CONSOLE_PRINT("[Test Output] (%s) \n", mProject.getItem(mCurrentMenuIndex).getItemDescription(mCurrentSubMenuIndex));
    displayInnerBorder();
    (mCurrentTestFunction_p)(); //execute function
    displayBorder();
}

void menu_c::run()
{    
    displayMainMenuItems();    

    while (mRun)
    {
        char choice = CONSOLE_GET
        
        if (choice == 'q') //note: quit
        {            
            mRun = false;
        }
        else if (choice == 'm') //note: 'm' returns to main menu
        {
            mCurrentState = MAIN_MENU_STATE;             
        }
        else if (choice == 't')
        {
            displayMenuTree();
        }
        else if (choice == '\n') //note: '\n' displays current menu
        {
            if (mCurrentState == MAIN_MENU_STATE)
            {
                displayMainMenuItems();
            }
            else if (mCurrentState == SUB_MENU_STATE)
            {
                displayCurrentSubMenuItems();
            }
            else
            {
                NVME_DBG_ASSERT(0, "incorrect menu state!")
            }
        }
        else if (choice > '0' && choice <= '9')
        {            
            int userInput = (int)(choice - '0'); //convert char to int

            if (mCurrentState == MAIN_MENU_STATE)
            {  
                //execute if valid selection in main menu state
                if((userInput>0) && (userInput<=(int)mProject.getItemCount()))
                {
                    mCurrentMenuIndex = (userInput-1); //user input is 1-based
                    mCurrentState = SUB_MENU_STATE;
                }
            }
            else if (mCurrentState == SUB_MENU_STATE)
            {                
                //execute if valid selection in sub menu state
                if((userInput>0) && (userInput<=(int)mProject.getItem(mCurrentMenuIndex).getItemCount()))
                {
                    mCurrentSubMenuIndex = (userInput-1); //user input is 1-based
                    mCurrentTestFunction_p = mProject.getItem(mCurrentMenuIndex).getItem(mCurrentSubMenuIndex);
                    
                    execute();
                }
            }
            else
            {
                NVME_DBG_ASSERT(0, "incorrect menu state!")
            }
        }
    }
}
