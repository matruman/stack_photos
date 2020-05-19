#include <iostream>
#include <cstdio>
#include <fstream>
#include <cmath>

using namespace std;

int height = 4160;
int width = 3120;

int main(int argc, char** argv) {

    ifstream ifs;
	ifs.open("bimgs/50.bmp", ifstream::binary);
	int size = width * height * 3;
    char header[54];
    ifs.read(header, 54);
	uint8_t *buff = new uint8_t[size];
    int *intbuff = new int[size];
    ifs.seekg(54);
    ifs.read((char *)buff, size);
    for (int i = 0; i < size; i++) {
        intbuff[i] = buff[i];
    }
    ifs.close();
    char namebuff[20];

     int count = 50;
    // for (int i = 2; i < count + 1; i++) {
    //     sprintf(namebuff, "bimgs/%d.bmp", i);
    //     string name(namebuff);
    //     ifs.open(name, ifstream::binary);
    //     ifs.seekg(54);
    //     ifs.read((char *)buff, size);
    //     cout << i << endl;
    //     for (int j = 0; j < size; j++) {
    //         intbuff[j] = intbuff[j] + (int)buff[j];
    //     }
    //     ifs.close();
    // }

    ifs.open("int_stack", ifstream::binary);
    ifs.read((char *)intbuff, 4 * size);
    ifs.close();

    float noize_r = 2.5 * count;
    float noize_g = 2.0 * count;
    float noize_b = 3.2 * count;

    float coeff;
    float sd;
    for (int i = 0; i < size; i += 3 ) {

        int val = i / 3;
        sd = powf(val % width - width/2, 2) + powf(val / width - height/2, 2);
        coeff = 1.0 + sqrtf(sd) / (float)(height / 2);
        coeff = 0 * powf(coeff, 2.0);

        int divider = 70;

        int tmp;
        tmp = (intbuff[i] - (noize_r * coeff)) / divider;
        if (tmp < 0)
            tmp = 0;
        buff[i] = tmp < 256 ? tmp : 255;
        tmp = (intbuff[i + 1] - (noize_g * coeff)) / divider;
        if (tmp < 0)
            tmp = 0;
        buff[i + 1] = tmp < 256 ? tmp : 255;
        tmp = (intbuff[i + 2] - (noize_b * coeff)) / divider;
        if (tmp < 0)
            tmp = 0;
        buff[i + 2] = tmp < 256 ? tmp : 255; 
    }
    cout << coeff << endl;
    ofstream ofs;
    ofs.open("result_stack.bmp", ofstream::binary);
    ofs.write(header, 54);
    ofs.write((char *)buff, size);
    ofs.flush();
    ofs.close();
    // ofs.open("int_stack", ofstream::binary);
    // ofs.write((char *)intbuff, 4 * size);
    // ofs.flush();
    // ofs.close();
    return 0;
}

