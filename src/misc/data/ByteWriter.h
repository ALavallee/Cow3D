#ifndef EVOSERVER_BYTEWRITER_H
#define EVOSERVER_BYTEWRITER_H

#include <string>
#include <vector>

namespace cow {

class ByteWriter {

public:

    template<class T, class C>
    size_t write(C value) {
        const T valueToWrite = static_cast<T>(value);
        const size_t size = sizeof(T);
        const size_t initialSize = mData.size();
        mData.resize(mData.size() + size);
        T *valuePtr = reinterpret_cast<T *>(&mData[initialSize]);
        *valuePtr = valueToWrite;
        return initialSize;
    }

    void writeStr(std::string &str) {
        write<int>(str.size());
        extend(str.data(), str.size());
    }

    void extend(ByteWriter &writer) {
        mData.insert(mData.end(), writer.mData.begin(), writer.mData.end());
    }

    void extend(char *data, size_t size) {
        mData.insert(mData.end(), data, data + size);
    }

    size_t size() {
        return mData.size();
    }

    void clear() {
        mData.clear();
    }

    unsigned char *data() {
        return mData.data();
    }

private:
    std::vector<unsigned char> mData;

};

}

#endif //EVOSERVER_BYTEWRITER_H
