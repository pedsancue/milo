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

// Those class are based in: https://github.com/clydemcqueen/tello_ros/blob/master/tello_driver/

#ifndef MILO_SOCKETS_CAMERA_H_
#define MILO_SOCKETS_CAMERA_H_

#include "milo/driver/sockets/TelloSocket.h"
#include "milo/driver/sockets/h264decoder.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <libavutil/frame.h>

namespace milo{
    class CameraSocket : public TelloSocket
    {
        public:
            CameraSocket(int _port);

            virtual ~CameraSocket();

            cv::Mat getFrame();

        private:
            void process_packet(size_t r) override;

            void decode_frames();

        private:
            std::vector<unsigned char> seq_buffer_; 
            size_t seq_buffer_next_ = 0;
            int seq_buffer_num_packets_ = 0;          

            H264Decoder decoder_;
            ConverterRGB24 converter_;

            cv::Mat frameDecoded_;

    };
}

#endif
