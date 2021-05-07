/**
 * 
 * 处理红外信息
 * 
 * 
 * 
 */

#ifndef _ESP_REMOTE_CONTROL_IR_
#define _ESP_REMOTE_CONTROL_IR_

#define IR_REC_TIMEOUT_S 5
#define LED_ON HIGH              //led 开
#define LED_OFF LOW              //led 关

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <IRutils.h>

class IR
{
    private:
        static IR* _ir;
        IRrecv* iRrecv;       //recObj
        IRsend* iRsend;       //sendObj
        const uint16_t khz = 38;       //红外频率,一般为38kHz
        decode_results results;    //recDataObj
        bool useLed = false;
        uint16_t ledPin = 2;
        uint8_t recCount;
        uint16_t rawLen;

        IR(uint16_t recvPin = 4, uint16_t buffSize = 200, uint16_t sendPin = 5, bool useLed = false, uint16_t ledPin = 2){
            this->iRrecv = new IRrecv(recvPin, buffSize);
            this->iRsend = new IRsend(sendPin);

            this->iRrecv->enableIRIn();   // 启用红外接收
            this->iRsend->begin();        //启用红外发送

            this->useLed = useLed;
            this->ledPin = ledPin;
            this->rawLen = 0;
        }

    public:
        
        ~IR(){
            delete iRrecv;
            iRrecv = nullptr;
            delete iRsend;
            iRsend = nullptr;
        }
        IR(IR &other) = delete;
        void operator=(const IR &) = delete;

        static IR* start(uint16_t recvPin = 4, uint16_t buffSize = 200, uint16_t sendPin = 5, bool useLed = false, uint16_t ledPin = 2){
            if(_ir == nullptr){
                _ir = new IR(recvPin, buffSize, sendPin, useLed, ledPin);
            }
            return _ir;
        }

        static IR* getIR(){
            return _ir;
        }

        void sendRaw(uint16_t buf[], uint16_t len){
            ledOn();
            iRsend->sendRaw(buf, len, khz);
            ledOff();
        }

        uint16_t* recRawArray(){
            iRrecv->resume();  //刷新
            if(!recData()){
                iRrecv->resume();  //刷新
                rawLen = 0;
                return nullptr;
            }
            iRrecv->resume();      //刷新
            rawLen = getCorrectedRawLength(&results);
            return resultToRawArray(&results);
            
        }


        String recRawString(){
            iRrecv->resume();  //刷新
            if(!recData()){
                iRrecv->resume();  //刷新
                rawLen = 0;
                return "";
            }
            iRrecv->resume();  //刷新
            rawLen = getCorrectedRawLength(&results);
            return resultToSourceCode(&results);
        }


        bool recData(){
            recCount = 0;
            ledOn();
            while (!iRrecv->decode(&results)){   //阻塞，直到获取到红外信息
                delay(1000);
                if(recCount ++ >= IR_REC_TIMEOUT_S){
                    ledOff();
                    return false;
                }
            }
            ledOff();
            return true;
        }

        void ledOn(){
            if (useLed)
            {
                digitalWrite(ledPin, LED_ON);   //打开led
            }
        }

        void ledOff(){
            if (useLed)
            {
                digitalWrite(ledPin, LED_OFF);   //关闭led
            }
        }


        IRrecv* getIRrecv(){
            return iRrecv;
        }

        IRsend* getIRsend(){
            return iRsend;
        }

        uint16_t getRawLen(){
            return rawLen;
        }
};



#endif
