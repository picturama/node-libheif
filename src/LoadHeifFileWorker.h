#include <napi.h>

using namespace Napi;

class LoadHeifFileWorker : public AsyncWorker
{
    public:
        LoadHeifFileWorker(std::string fileName, Function &callback);

        void Execute();

        void OnOK();

    private:
        std::string fileName;
        int resultWidth;
        int resultHeight;
        size_t resultDataLength;
        const uint8_t* resultData;

};
