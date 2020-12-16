#include <napi.h>

using namespace Napi;

class DecodeHeifBufferWorker : public AsyncWorker
{
    public:
        DecodeHeifBufferWorker(Buffer<uint8_t> &data, Function &callback);

        void Execute();

        void OnOK();

    private:
        ObjectReference dataRef;
        uint8_t *dataPtr;
        size_t dataLength;

        int resultWidth;
        int resultHeight;
        size_t resultDataLength;
        const uint8_t* resultData;

};
