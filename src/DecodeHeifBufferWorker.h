#include <napi.h>
#include "libheif/heif.h"

using namespace Napi;

class DecodeHeifBufferWorker : public AsyncWorker
{
    public:
        DecodeHeifBufferWorker(Buffer<uint8_t> &data, Function &callback);

    protected:
        void Execute();
        void OnOK();
        void Destroy();

    private:
        ObjectReference dataRef;
        uint8_t *dataPtr;
        size_t dataLength;

        heif_context* heifCtx;
        heif_image_handle* imageHandle;
        heif_image* image;

        int resultStride;
        int resultWidth;
        int resultHeight;
        const uint8_t* resultData;

};
