#include <cstdio>
#include <iostream>


#include "mainFunctions.h"

int main(){
    while(1){
        printMenu();
        int input;
        cin >> input;
        if (input == 0){
            break;
        }
        switch(input)
        {
            case 1:
                printArrayMenu();
                int arrayInput;
                cin >> arrayInput;
                if (arrayInput == 0){
                    break;
                }
                switch(arrayInput)
                {
                    case 1:
                        dynamicArrayAppend();
                        break;
                    case 2:
                        dynamicArrayPrepend();
                        break;
                    case 3:
                        dynamicArrayInsertAt();
                        break;
                    case 4:
                        dynamicArrayRemoveAt();
                        break;
                    case 5:
                        dynamicArrayGetSubSequence();
                        break;
                    case 6:
                        dynamicArrayFindSubSequence();
                        break;
                    case 7:
                        dynamicArrayConcat();
                        break;
                    default:
                    {
                        wprintf(L"Unknown command.\n");
                        break;
                    }
                }
                break;
            case 2:
                printListMenu();
                int listInput;
                cin >> listInput;
                if (listInput == 0){
                    break;
                }
                switch(listInput)
                {
                    case 1:
                        linkedListAppend();
                        break;
                    case 2:
                        linkedListPrepend();
                        break;
                    case 3:
                        linkedListInsertAt();
                        break;
                    case 4:
                        linkedListRemoveAt();
                        break;
                    case 5:
                        linkedListGetSubSequence();
                        break;
                    case 6:
                        linkedListFindSubSequence();
                        break;
                    case 7:
                        linkedListConcat();
                        break;
                    case 8:
                        linkedListMapWhereReduce();
                        break;
                    case 9:
                        linkedListIterator();
                        break;
                    default:
                    {
                        wprintf(L"Unknown command.\n");
                        break;
                    }
                }
                break;
            default:
            {
                wprintf(L"Unknown command.\n");
                break;
            }
        }


    }
    return 0;
}