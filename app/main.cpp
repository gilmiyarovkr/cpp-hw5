#include <iostream>
#include "Primitive.h"
#include "Controller.h"
#include "JsonDoc.h"

//---------------------------------------------------------------------------
Controller ctrl;

//---------------------------------------------------------------------------
// GUI
//---------------------------------------------------------------------------
void GUI_CreateDocument(const std::string& file) { ctrl.HandleSaveFile(file); }
void GUI_ExportDocument(const std::string& file) { ctrl.HandleSaveFile(file); }
void GUI_ImportDocument(const std::string& file){ ctrl.HandleLoadFile(file); }

void GUI_AddLineElement(){ ctrl.CreatePrimitive(std::make_shared<Line>()); }
void GUI_AddCircleElement(){ ctrl.CreatePrimitive(std::make_shared<Circle>()); }
void GUI_DeleteElement(uint32_t ID){ ctrl.DeletePrimitive(ID); }

//---------------------------------------------------------------------------
int main()
{
    ctrl.RegisterFormat(".json", []() {return std::make_unique<JsonDoc>();});
    // TODO ctrl.RegisterFormat(".csv", [](){return std::make_unique<CsvDoc>();});

    // FIXME имитация работы GUI
    int enter = 0;
    while(true)
    {
        std::cout << "Draw: \n"
                  << "1 - Line \n"
                  << "2 - Circle \n"
                  << "0 - Exit \n";

        std::cin >> enter;

        if(enter == 0)
            break;

        switch(enter)
        {
            case 1: GUI_AddLineElement();
                break;
            case 2: GUI_AddCircleElement();
                break;
            default:
                break;
        }
    }
    return 0;
}

