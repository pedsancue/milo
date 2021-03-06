//---------------------------------------------------------------------------------------------------------------------
//  MILO
//---------------------------------------------------------------------------------------------------------------------
//  Copyright 2020 Manuel Pérez Jiménez (a.k.a. manuoso) manuperezj@gmail.com
//---------------------------------------------------------------------------------------------------------------------
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
//  and associated documentation files (the "Software"), to deal in the Software without restriction, 
//  including without limitation the rights to use, copy, modify, merge, publish, distribute, 
//  sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial 
//  portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
//  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES 
//  OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//---------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <thread>
#include <chrono>

#include "milo/milo.h"

int main(int _argc, char **_argv){

    milo::MILO *drone = nullptr;
    drone = milo::MILO::create(true, true);

    drone->command()->setControl();
    while(drone->command()->isWaiting()){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    if(drone->command()->isRespond()){
        std::cout << "Received TRUE" << std::endl;
    }else{
        std::cout << "Received FALSE" << std::endl;
    }

    drone->command()->setCamera(true);
    while(drone->command()->isWaiting()){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    if(drone->command()->isRespond()){
        std::cout << "Received TRUE" << std::endl;
    }else{
        std::cout << "Received FALSE" << std::endl;
    }

    std::thread thread = std::thread(
        [&]()
        {
            while(drone->camera()->isReceiving()){
                cv::Mat img = drone->camera()->getImage();

                if(img.empty())
                    continue;

                // Display
                cv::imshow("Tello Camera", img);
                cv::waitKey(1);
            }

            std::cout << "Finish Camera Stream" << std::endl;
        });

    int cont = 0;
    while(true){
        int bat = drone->telemetry()->getBattery();
        std::cout << "Battery: " << bat << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cont++;
        if(cont == 10){
            drone->camera()->timeout();
        }
    }

    return 0;
}