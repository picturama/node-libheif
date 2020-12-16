#include <napi.h>

#include <DecodeHeifFileWorker.h>
#include <DecodeHeifBufferWorker.h>

using namespace Napi;

void DecodeHeifFile(const CallbackInfo& info) {
    if (info.Length() != 2 || !info[0].IsString() || !info[1].IsFunction()) {
        napi_throw_error(info.Env(), nullptr, "DecodeHeifFile - expected arguments: fileName: string, callback: (error, result) => void");
    }

    std::string fileName = std::string(info[0].ToString());
    Function cb = info[1].As<Function>();

    DecodeHeifFileWorker *worker = new DecodeHeifFileWorker(fileName, cb);
    worker->Queue();
}

void DecodeHeifBuffer(const CallbackInfo& info) {
    if (info.Length() != 2 || !info[0].IsBuffer() || !info[1].IsFunction()) {
        napi_throw_error(info.Env(), nullptr, "DecodeHeifBuffer - expected arguments: buffer: Buffer, callback: (error, result) => void");
    }

    Buffer<uint8_t> data = info[0].As<Buffer<uint8_t>>();
    Function cb = info[1].As<Function>();

    DecodeHeifBufferWorker *worker = new DecodeHeifBufferWorker(data, cb);
    worker->Queue();
}

Object Init(Env env, Object exports) {
    exports.Set(String::New(env, "decodeHeifFile"), Function::New(env, DecodeHeifFile));
    exports.Set(String::New(env, "decodeHeifBuffer"), Function::New(env, DecodeHeifBuffer));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
