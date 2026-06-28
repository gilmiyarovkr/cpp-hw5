#include <iostream>
#include "Primitive.h"
#include "Controller.h"
#include "JsonDoc.h"
#include "print_ip.h"
#include <list>

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
    // Общий вывод ip адреса
    // Строка
    print_ip(std::string{"192.168.1.1"}); // Вывод: 192.168.1.1
    // Целые числа (разного размера)
    print_ip(char(-1));                   // Вывод: 255 (потому что 0xFF)
    print_ip(short(0));                   // Вывод: 0.0
    print_ip(int(2130706433));            // Вывод: 127.0.0.1

    // Контейнеры
    print_ip(std::vector<unsigned char>{192, 168, 0, 1}); // Вывод: 192.168.0.1
    print_ip(std::list<int>{10, 0, 0, 254});              // Вывод: 10.0.0.254

    // Кортеж (Tuple)
    print_ip(std::make_tuple(172, 16, 254, 1));           // Вывод: 172.16.254.1


    // GoF
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

