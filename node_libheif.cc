#include <nan.h>
#include "libheif/heif.h"

// void LoadHeifFromFile(FunctionCallbackInfo<Value>& info)
NAN_METHOD(LoadHeifFile) {
    if(info.Length() != 1) {
        return Nan::ThrowError(Nan::New("Vector::New - expected argument fileName").ToLocalChecked());
    }

    std::string fileName = std::string(*Nan::Utf8String(info[0]));
    //printf("## fileName: %s\n", fileName.c_str());

    heif_context* ctx = heif_context_alloc();
    heif_context_read_from_file(ctx, fileName.c_str(), nullptr);

    // get a handle to the primary image
    heif_image_handle* handle;
    heif_context_get_primary_image_handle(ctx, &handle);

    // decode the image and convert colorspace to RGB, saved as 24bit interleaved
    heif_image* img;
    heif_error error = heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr);
    if (error.code != heif_error_Ok) {
        return Nan::ThrowError(Nan::New(error.message).ToLocalChecked());
    }

    int width  = heif_image_get_width(img, heif_channel_interleaved);
    int height = heif_image_get_height(img, heif_channel_interleaved);

    int stride;
    const uint8_t* data = heif_image_get_plane_readonly(img, heif_channel_interleaved, &stride);
    int len = stride * height;

    //printf("## stride: %d, width: %d, height: %d, len: %d\n", stride, width, height, len);

    v8::Local<v8::Object> responseJson = Nan::New<v8::Object>();
    Nan::Set(responseJson, Nan::New("width").ToLocalChecked(), Nan::New(width));
    Nan::Set(responseJson, Nan::New("height").ToLocalChecked(), Nan::New(height));
    Nan::Set(responseJson, Nan::New("data").ToLocalChecked(), Nan::NewBuffer((char*) data, len).ToLocalChecked());

    info.GetReturnValue().Set(responseJson);
}

// void Init(Local<Object> target)
NAN_MODULE_INIT(InitModule) {
    Nan::Set(
        target,
        Nan::New<v8::String>("loadHeifFile").ToLocalChecked(),
        Nan::GetFunction(Nan::New<v8::FunctionTemplate>(LoadHeifFile)).ToLocalChecked()); 
}

// First argument would be the entry file's name
NODE_MODULE(libheif, InitModule);
