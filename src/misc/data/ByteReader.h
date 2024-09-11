#ifndef COW3D_BYTEREADER_H
#define COW3D_BYTEREADER_H

#include <string>
#include <vector>

namespace cow {

class ByteReader {

public:

    ByteReader() : mCurrent(0) {

    }

    ByteReader(unsigned char *data, size_t size) : mCurrent(0) {
        mData.insert(mData.end(), data, data + size);
    }

    explicit ByteReader(std::vector<unsigned char> &data) : mData(data), mCurrent(0) {

    }

    template<class T>
    T read() {
        const size_t size = sizeof(T);
        T *value = reinterpret_cast<T *>(&mData[mCurrent]);
        mCurrent += size;
        return *value;
    }

    std::string readStr() {
        auto strSize = read<unsigned int>();
        std::string result = std::string(mData.begin() + (int) mCurrent, mData.begin() + (int) mCurrent + strSize);
        mCurrent += strSize;
        return result;
    }

    void extend(ByteReader &reader) {
        mData.insert(mData.end(), reader.mData.begin(), reader.mData.end());
    }

    void extend(char *data, size_t dataSize) {
        mData.insert(mData.end(), data, data + dataSize);
    }

    bool atEnd() {
        return mCurrent >= mData.size();
    }

    void clear() {
        mCurrent = 0;
        mData.clear();
    }

    size_t size() {
        return mData.size();
    }

private:
    std::vector<unsigned char> mData;
    size_t mCurrent;
};

}

#endif //COW3D_BYTEREADER_H
