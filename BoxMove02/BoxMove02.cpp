// BoxMove02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
using namespace std;

class IntArray2D
{
public:
    IntArray2D(int size0, int size1) :
        mArray(0),
        mSize0(size0),
        mSize1(size1)
    {
        mArray = new int[size0 * size1];
    }

    ~IntArray2D()
    {
        delete[] mArray;
        mArray = 0;
    }

    int& operator()(int index0, int index1)
    {
        return mArray[index1 * mSize0 + index0];
    }

    const int& operator()(int index0, int index1) const
    {
        return mArray[index1 * mSize0 + index0];
    }

private:
    int* mArray;
    const int mSize0;
    const int mSize1;

}

void readMapFromData(const char* filePath)
{
    ifstream inputFile(filePath, ifstream::binary);
    inputFile.seekg(0, ifstream::end);

    int fileSize = static_cast<int>(inputFile.tellg());
    inputFile.seekg(0, ifstream::beg);
    char* mapImage = new char[fileSize];
    inputFile.read(mapImage, fileSize);
    
    cout.write(mapImage, fileSize);
}

int main()
{
    readMapFromData("stageData");
}