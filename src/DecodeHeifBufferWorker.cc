#include <DecodeHeifBufferWorker.h>

DecodeHeifBufferWorker::DecodeHeifBufferWorker(Buffer<uint8_t> &data, Function &callback) :
    AsyncWorker(callback),
    dataRef(ObjectReference::New(data, 1)),
    dataPtr(data.Data()),
    dataLength(data.Length()),
    heifCtx(0),
    imageHandle(0),
    image(0),
    resultData(0)
{
}

void DecodeHeifBufferWorker::Execute() {
    heif_error error;

    heifCtx = heif_context_alloc();

    error = heif_context_read_from_memory(heifCtx, dataPtr, dataLength, nullptr);
    if (error.code != heif_error_Ok) {
        std::string msg = "Reading heif context failed: ";
        msg.append(error.message);
        SetError(msg);
        return;
    }

    // get a handle to the primary image
    error = heif_context_get_primary_image_handle(heifCtx, &imageHandle);
    if (error.code != heif_error_Ok) {
        std::string msg = "Getting primary heif handle failed: ";
        msg.append(error.message);
        SetError(msg);
        return;
    }

    // decode the image and convert colorspace to RGB, saved as 24bit interleaved
    error = heif_decode_image(imageHandle, &image, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr);
    if (error.code != heif_error_Ok) {
        std::string msg = "Decoding heif failed: ";
        msg.append(error.message);
        SetError(msg);
        return;
    }

    resultWidth = heif_image_get_width(image, heif_channel_interleaved);
    resultHeight = heif_image_get_height(image, heif_channel_interleaved);

    resultData = heif_image_get_plane_readonly(image, heif_channel_interleaved, &resultStride);
}

void DecodeHeifBufferWorker::OnOK() {
    Buffer<uint8_t> buffer;
    int bufferStride = 3 * resultWidth;
    size_t bufferLength = bufferStride * resultHeight;
    if (bufferStride == resultStride) {
        buffer = Buffer<uint8_t>::Copy(Env(), (uint8_t*) resultData, bufferLength);
    } else {
        buffer = Buffer<uint8_t>::New(Env(), bufferLength);

        const uint8_t* srcPos = resultData;
        uint8_t* destPos = buffer.Data();
        for (int y = 0; y < resultHeight; y++, srcPos += resultStride, destPos += bufferStride) {
            memcpy(destPos, srcPos, bufferStride);
        }
    }

    //printf("## resultWidth: %d, resultHeight: %d, resultStride: %d, resultLength: %d, bufferLength: %d\n",
    //    resultWidth, resultHeight, resultStride, resultStride * resultHeight, bufferLength);

    Object result = Object::New(Env());
    result.Set("width", resultWidth);
    result.Set("height", resultHeight);
    result.Set("data", buffer);

    Callback().Call({ Env().Null(), result });
}

void DecodeHeifBufferWorker::Destroy() {
    if (image != 0) {
        heif_image_release(image);
        image = 0;
    }
    if (imageHandle != 0) {
        heif_image_handle_release(imageHandle);
        imageHandle = 0;
    }
    if (heifCtx != 0) {
        heif_context_free(heifCtx);
        heifCtx = 0;
    }
}
