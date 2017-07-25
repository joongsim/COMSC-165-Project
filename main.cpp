
#include <stdio.h>
#include "exif.hpp"
#include <dirent.h>
#include "linklt.hpp"
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: test <dir>\n");
    }
    argv[1] = "/Users/andrey/Public/";
    linkl flist;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(argv[1]))) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            
            std::string name(ent->d_name);
            string path(argv[1]);
            string fullname = path + name;
            if(name.length() > 3 && name.substr( name.length() - 3 ) == "jpg")
            {
                // Read the JPEG file into a buffer
                FILE *fp = fopen(fullname.c_str(), "rb");
                if (!fp) {
                    printf("Can't open file.\n");
                    return -1;
                }
                fseek(fp, 0, SEEK_END);
                unsigned long fsize = ftell(fp);
                rewind(fp);
                unsigned char *buf = new unsigned char[fsize];
                if (fread(buf, 1, fsize, fp) != fsize) {
                    printf("Can't read file.\n");
                    delete[] buf;
                    return -2;
                }
                fclose(fp);
                
                // Parse EXIF
                easyexif::EXIFInfo result;
                int code = result.parseFrom(buf, fsize);
                delete[] buf;
                if (code) {
                    printf("Error parsing EXIF: code %d\n", code);
                    return -3;
                }
                listnode curpic = {result.DateTime, result.GeoLocation.Latitude, result.GeoLocation.Longitude, name};
                flist.insert(&curpic);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
    }
    flist.display();
    return 0;
}
