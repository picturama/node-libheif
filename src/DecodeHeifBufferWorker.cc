#include <DecodeHeifBufferWorker.h>
#include "libheif/heif.h"

DecodeHeifBufferWorker::DecodeHeifBufferWorker(Buffer<uint8_t> &data, Function &callback) :
    AsyncWorker(callback),
    dataRef(ObjectReference::New(data, 1)),
    dataPtr(data.Data()),
    dataLength(data.Length())
{
}

void DecodeHeifBufferWorker::Execute() {
    //printf("## fileName: %s\n", fileName.c_str());

    heif_context* ctx = heif_context_alloc();
    heif_context_read_from_memory(ctx, dataPtr, dataLength, nullptr);

    // get a handle to the primary image
    heif_image_handle* handle;
    heif_context_get_primary_image_handle(ctx, &handle);

    // decode the image and convert colorspace to RGB, saved as 24bit interleaved
    heif_image* img;
    heif_error error = heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr);
    if (error.code != heif_error_Ok) {
        SetError(error.message);
        return;
    }

    resultWidth = heif_image_get_width(img, heif_channel_interleaved);
    resultHeight = heif_image_get_height(img, heif_channel_interleaved);

    int stride;
    resultData = heif_image_get_plane_readonly(img, heif_channel_interleaved, &stride);
    resultDataLength = stride * resultHeight;

    //printf("## stride: %d, width: %d, height: %d, len: %d\n", stride, resultWidth, resultHeight, resultDataLength);
}

void DecodeHeifBufferWorker::OnOK() {
    Object result = Object::New(Env());
    result.Set("width", resultWidth);
    result.Set("height", resultHeight);
    result.Set("data", Buffer<uint8_t>::New(Env(), (uint8_t*) resultData, resultDataLength));

    Callback().Call({ Env().Null(), result });
}
