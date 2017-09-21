#include <iostream>
#include <dirent.h>
#include <fstream>
#include <string>

#include "kml.hpp"
#include "exif.hpp"
#include "linklt.hpp"
#include "twitclient.hpp"

using namespace std;
int main(int argc, char *argv[]) {
    int count = 0, fcount = 0; //pics with and without exif data
    if (argc < 2) {
        cout << "Usage: COMSC165 <dir>\n";
    }
    linkl flist;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(argv[1]))) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            string name(ent->d_name);
            string path(argv[1]);
            string fullname = path + name;
            if(name.length() > 3 && name.substr( name.length() - 3 ) == "jpg")
            {
                // Read the JPEG file into a buffer
                // cout << "Processing file " <<  fullname << endl;
                ifstream file;
                file.open(fullname, ios::binary);
                if(!file)
                {
                    cout << "can't open file\n";
                    return -1;
                }
                fcount++;
                file.seekg(0, ios_base::end);
                unsigned long fsize = file.tellg();
                file.seekg(0, ios_base::beg);
                char *buf = new char[fsize];
                file.read(buf, fsize); //failure sets fail bit
                if (!file) {
                    delete[] buf;
                    cout << "can't read file\n";
                    return -1;
                }
                file.close();
                // Parse EXIF
                easyexif::EXIFInfo result;
                int code = result.parseFrom(reinterpret_cast<unsigned char*>(buf), static_cast<int>(fsize));
                delete[] buf;
                if (code)
                    cout <<"Error parsing EXIF: code " << code << endl;
                else
                {
                    string time;
                    if (strcmp(result.DateTime.c_str(), result.DateTimeOriginal.c_str()) < 0) //sometimes only one of these is populated, so we pick the bigger one
                        time = result.DateTimeOriginal;
                    else
                        time = result.DateTime;
                    if (result.GeoLocation.Latitude != 0 || result.GeoLocation.Longitude != 0) //to catch pictures with no coordinates. sorry equator-dwellers
                    {
                        listnode curpic = {time, result.GeoLocation.Latitude, result.GeoLocation.Longitude, fullname};
                        flist.insert(&curpic);
                        count++;
                    }
                }
            }
        }
        closedir (dir);
    }
    else
    {
        cout << "failed to open dir\n";
        return -1;
    }
    //flist.display();
    writekml("test.kml", flist.showhead());
    cout << "using " << count << " of " << fcount << " pictures\n";
  
    listnode* pictime = flist.showhead();
    string firstpicdate = pictime->time.substr(0, 10);
    while(pictime->next)
        pictime = pictime->next;
    string lastpicdate = pictime->time.substr(0, 10);
    string picinterval;
    if (firstpicdate == lastpicdate)
        picinterval = "on " + firstpicdate.substr();
    else
        picinterval = "from " + firstpicdate + " to " + lastpicdate + ".";
  
    OauthTwitPass pass;
    tweetauth(pass);
    tweet("I made a kml file with " + to_string(count) + "pictures! They were taken " + picinterval, pass);
    return 0;
}
