#include <iostream>
using namespace std;
#include "linklt.hpp"
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
int a = strcmp("a", "b");


string formatPlacemark(listnode*);

int main()
{
	// ofstream object for writing kml file
	ofstream handle;

	// Throw an exception on failure to open the file or on a write error.
	handle.exceptions(std::ofstream::failbit | std::ofstream::badbit);

	// Open the KML file for writing:
	handle.open("ProjectSample.kml");

	// Write to the KML file:
	handle << "<?xml version='1.0' encoding='utf-8'?>\n";
	handle << "<kml xmlns='http://www.opengis.net/kml/2.2'>\n";

	handle << formatPlacemark(test1);

	handle << "</kml>\n";
	handle.close();
	
	return 0;
}

string formatPlacemark(listnode *point)
{
	listnode *nodePtr = point;		// to traverse linked list
	int placeCounter = 1;			// counter variable for pushpin name
	ostringstream ss;
	ss << "<Document>\n"
		<< "<name>Test.kml</name>\n"
		<< "<StyleMap id=\"m_ylw-pushpin\">\n"
		<< "<Pair>\n"
		<< "<key>normal</key>\n"
		<< "<styleUrl>#s_ylw-pushpin</styleUrl>\n"
		<< "</Pair>\n"
		<< "<Pair>\n"
		<< "<key>highlight</key>\n"
		<< "<styleUrl>#s_ylw-pushpin_hl0</styleUrl>\n"
		<< "</Pair>\n"
		<< "</StyleMap>\n"
		<< "<Style id =\"s_ylw-pushpin\">\n"
		<< "<IconStyle>\n"
		<< "<scale>1.1</scale>\n"
		<< "<Icon>\n"
		<< "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>\n"
		<< "</Icon>\n"
		<< "<hotSpot x = \"20\" y = \"2\" xunits = \"pixels\" yunits = \"pixels\"/>\n"
		<< "</IconStyle>\n"
		<< "<ListStyle>\n"
		<< "</ListStyle>\n"
		<< "</Style>\n"
		<< "<Style id=\"s_ylw-pushpin_hl\">\n"
		<< "<IconStyle>\n"
		<< "<scale>1.3</scale>\n"
		<< "<Icon>\n"
		<< "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>\n"
		<< "</Icon>\n"
		<< "<hotSpot x = \"20\" y = \"2\" xunits = \"pixels\" yunits = \"pixels\"/>\n"
		<< "</IconStyle>\n"
		<< "</Style>\n"
		<< "<Style id=\"s_ylw-pushpin0\">\n"
		<< "<IconStyle>\n"
		<< "<scale>1.1</scale>\n"
		<< "<Icon>\n"
		<< "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>\n"
		<< "</Icon>\n"
		<< "<hotSpot x=\"20\" y =\"2\" xunits=\"pixels\" yunits=\"pixels\"/>\n"
		<< "</IconStyle>\n"
		<< "</Style>"
		<< "<Style id=\"s_ylw-pushpin_hl0\">\n"
		<< "<IconStyle>\n"
		<< "<scale>1.3</scale>\n"
		<< "<Icon>\n"
		<< "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>\n"
		<< "</Icon>\n"
		<< "<hotSpot x=\"20\" y=\"2\" xunits=\"pixels\" yunits=\"pixels\"/>\n"
		<< "</IconStyle>\n"
		<< "<ListStyle>\n"
		<< "</ListStyle>\n"
		<< "</Style>\n"
		<< "<StyleMap id=\"m_ylw-pushpin0\">\n"
		<< "<Pair>\n"
		<< "<key>normal</key>\n"
		<< "<styleUrl>#s_ylw-pushpin0</styleUrl>\n"
		<< "</Pair>\n"
		<< "<Pair>\n"
		<< "<key>highlight</key>\n"
		<< "<styleUrl>#s_ylw-pushpin_hl</styleUrl>\n"
		<< "</Pair>\n"
		<< "</StyleMap>\n"
		<< "<Folder>\n"
		<< "<name>Test</name>\n"
		<< "<open>1</open>\n"
		<< "<Placemark>\n"
		<< "<name>Path</name>\n"
		<< "<styleUrl>#m_ylw-pushpin0</styleUrl>\n"
		<< "<LineString>\n"
		<< "<tessellate>1</tessellate>\n"
		<< "<coordinates>\n";
		
	while (nodePtr)	// While node exists
	{
		ss << nodePtr->latitude << "," << nodePtr->longitude << ",0\n";	// Writes list of coordinates
		nodePtr = nodePtr->next;										// Traverse list
	}
	nodePtr = point;
	ss << "</coordinates>\n"
		<< "</LineString>\n"
		<< "</Placemark>\n"
		<< "<Folder>\n"
		<< "<name>Pictures</name>\n"
		<< "<open>1</open>\n";

// Begin loop to traverse list
	while (nodePtr)		// While loop exists, write
	{
		ss << "<Placemark>\n"
			<< "<name>Place " << placeCounter << "</name>\n"	// numbers push pins
			<< "<description><![CDATA[<img style = \"max-width:500px;\" src=\"file:///"
			<< nodePtr->fname			// Writes image file path
			<< "\">" << nodePtr->time << "]]></description>\n"
			<< "<styleUrl>#m_ylw-pushpin</styleUrl>\n"
			<< "<Point>\n"
			<< "<altitudeMode>relativeToGround</altitudeMode>\n"
			<< "<gx:drawOrder>1</gx:drawOrder>\n"
			<< "<coordinates>\n"
			<< nodePtr->latitude << "," << nodePtr->longitude << ",0\n"		// Writes coordinates of placemark
			<< "</coordinates>\n"
			<< "</Point>\n"
			<< "</Placemark>\n";
		nodePtr = nodePtr->next;			// Traverse list
		placeCounter++;						// Increment counter name
	}
// End loop
ss << "</Folder>\n"
<< "</Folder>\n"
<< "</Document>\n";

	return ss.str();
}

linkl::linkl()
{
    head = nullptr;
}

void linkl::insert(listnode* a)
{
    listnode* newnode= new listnode;
    newnode->time = a->time;
    newnode->latitude = a->latitude;
    newnode->longitude = a->longitude;
    newnode->fname = a->fname;
    newnode->next = nullptr;
    listnode* nodeptr;
    listnode* prevnode = nullptr;
    if (!head)
    {
        head = newnode;
    }
    else
    {
        nodeptr = head;
        while (nodeptr != nullptr && (strcmp(nodeptr->time.c_str(), newnode->time.c_str()) < 0))
        {
            prevnode = nodeptr;
            nodeptr = nodeptr->next;
        }
        if (prevnode == nullptr)
        {
            head = newnode;
            newnode->next = nodeptr;
        }
        else
        {
            prevnode->next = newnode;
            newnode->next = nodeptr;
        }
    }
}
void linkl::display()
{
    listnode* nodeptr = head;
    while(nodeptr)
    {
        cout << nodeptr->time << endl;
        nodeptr = nodeptr->next;
    }
    cout << "\n";
}

void linkl::tofile(char* filename)
{
    listnode* nodeptr = head;
    while(nodeptr)
    {
        //kml stuff goes here
        cout << nodeptr->time;
        //kml stuff ends
        nodeptr = nodeptr->next;
    }
}
