#include <nan.h>
#include "libheif/heif.h"


class LoadHeifFileWorker : public Nan::AsyncWorker {
public:
    std::string fileName;
    int width;
    int height;
    int len;
    const uint8_t* data;

    LoadHeifFileWorker(std::string fileName, Nan::Callback *callback) : Nan::AsyncWorker(callback) {
        this->fileName = fileName;
    }

    void Execute() {
        //printf("## fileName: %s\n", this->fileName.c_str());

        heif_context* ctx = heif_context_alloc();
        heif_context_read_from_file(ctx, this->fileName.c_str(), nullptr);

        // get a handle to the primary image
        heif_image_handle* handle;
        heif_context_get_primary_image_handle(ctx, &handle);

        // decode the image and convert colorspace to RGB, saved as 24bit interleaved
        heif_image* img;
        heif_error error = heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr);
        if (error.code != heif_error_Ok) {
            this->SetErrorMessage(error.message);
            return;
        }

        this->width    = heif_image_get_width(img, heif_channel_interleaved);
        int height = heif_image_get_height(img, heif_channel_interleaved);
        this->height = height;

        int stride;
        this->data = heif_image_get_plane_readonly(img, heif_channel_interleaved, &stride);
        this->len = stride * height;

        //printf("## stride: %d, width: %d, height: %d, len: %d\n", stride, width, height, len);
    }

    void HandleOKCallback() {
        Nan::HandleScope scope;

        v8::Local<v8::Object> result = Nan::New<v8::Object>();
        Nan::Set(result, Nan::New("width").ToLocalChecked(), Nan::New(this->width));
        Nan::Set(result, Nan::New("height").ToLocalChecked(), Nan::New(this->height));
        Nan::Set(result, Nan::New("data").ToLocalChecked(), Nan::NewBuffer((char*) this->data, this->len).ToLocalChecked());

        v8::Local<v8::Value> argv[] = {
            Nan::Null(), // no error occured
            result
        };
        Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), 2, argv);
    }

    void HandleErrorCallback() {
        Nan::HandleScope scope;
        v8::Local<v8::Value> argv[] = {
            Nan::New(this->ErrorMessage()).ToLocalChecked(),
            Nan::Null()
        };
        Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), 2, argv);
    }
};


// void LoadHeifFile(FunctionCallbackInfo<Value>& info)
NAN_METHOD(LoadHeifFile) {
    if (info.Length() != 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        return Nan::ThrowError(Nan::New("Vector::New - expected arguments: fileName: string, callback: (error, result) => void").ToLocalChecked());
    }

    Nan::AsyncQueueWorker(new LoadHeifFileWorker(
        std::string(*Nan::Utf8String(info[0])),
        new Nan::Callback(info[1].As<v8::Function>())));
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
