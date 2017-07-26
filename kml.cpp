#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "linklt.hpp"
#include "kml.hpp"
using namespace std;


string formatPlacemark(listnode*);
void writekml(const string&, listnode*);

int testmain()
{
	// Test listnode structure
	listnode* test1 = new listnode;
	test1->latitude = 33.3421;
	test1->longitude = 34.134;
	test1->time = "2017:07:22 12:22:33";
	test1->fname = "C:/Users/joonj/Documents/COMSC 165/Project/Project/Test.jpg";
	
	listnode* test2 = new listnode;
	test2->latitude = 35.34;
	test2->longitude = 36.3;
	test2->time = "2017:02:11 12:34:33";
	test2->fname = "C:/Users/joonj/Downloads/dXmULbx.jpg";

	listnode* test3 = new listnode;
	test3->latitude = 34.3;
	test3->longitude = 35;
	test3->time = "2012:03:12 12:22:44";
	test3->fname = "C:/Users/joonj/Downloads/VBEK8HY.jpg.";

	test1->next = test2;
	test2->next = test3;
	test3->next = nullptr;
    
    writekml("ProjectSample.kml", test1);
	
	return 0;
}

void writekml(const string& filename, listnode* pointer)
{
    // ofstream object for writing kml file
    ofstream handle;
    
    // Throw an exception on failure to open the file or on a write error.
    handle.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    
    // Open the KML file for writing:
    handle.open(filename);
    
    // Write to the KML file:
    handle << "<?xml version='1.0' encoding='utf-8'?>\n";
    handle << "<kml xmlns='http://www.opengis.net/kml/2.2'>\n";
    
    handle << formatPlacemark(pointer);
    
    handle << "</kml>\n";
    handle.close();
}

string formatPlacemark(listnode *point)
{
	listnode* nodePtr = point;		// to traverse linked list
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
		ss << nodePtr->longitude << "," << nodePtr->latitude << ",0\n";	// Writes list of coordinates
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
			<< "<description><![CDATA[<img style = \"max-width:500px;\" src=\"file://"
			<< nodePtr->fname			// Writes image file path
			<< "\">" << nodePtr->time << "]]></description>\n"
			<< "<styleUrl>#m_ylw-pushpin</styleUrl>\n"
			<< "<Point>\n"
			<< "<altitudeMode>relativeToGround</altitudeMode>\n"
			<< "<gx:drawOrder>1</gx:drawOrder>\n"
			<< "<coordinates>\n"
			<< nodePtr->longitude << "," << nodePtr->latitude << ",0\n"		// Writes coordinates of placemark
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
